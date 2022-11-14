#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <automate_ecran.h>
#include <coords_stdio.h>
/*!
 * \file test_automate_ecran.c
 * \brief Test des fonctions de gestion d'un automate avec sortie sur un écran géré par <code>ncurses</code> 
 */


/*!
 * \def FICHIER_INIT 
 * Fichier d'initialisation des cellules
 * \def HAUTEUR 
 * Hauteur de l'automate 
 * \def LARGEUR 
 * Largeur de l'automate
 * \def NB_GENERATIONS_SYNCHRONE 
 * Nombre de générations pour le test de l'automate synchrone 
 * \def NB_GENERATIONS_ASYNCHRONE 
 * Nombre de générations pour le test de l'automate asynchrone sans mémoire 
 * \def NB_GENERATIONS_ASYNCHRONE_MEMOIRE 
 * Nombre de générations pour le test de l'automate asynchrone avec mémoire 
 */
#define FICHIER_INIT "../Fichiers/planeurs.txt"
#define HAUTEUR 10
#define LARGEUR 10
#define NB_GENERATIONS_SYNCHRONE 16
#define NB_GENERATIONS_ASYNCHRONE 200
#define NB_GENERATIONS_ASYNCHRONE_MEMOIRE 5


/*!
 * \file test_automate_ecran.c
 * \brief Test des fonctions de gestion d'un automate avec sortie sur un écran géré par <code>ncurses</code>
 */

/*! \brief Variable globale pointant sur l'écran d'affichage */
ecran_t * ecran = ECRAN_NULL ;


/*! Handler de capture du signal d'arrêt SIGINT */
static
void hand_arret( int sig ) 
{
  ecran_detruire(&ecran) ; 
  exit(0); 
}

/*! Programme Principal : même principe que test_automate_stdio.c */ 
int 
main( int nb_arg , char * tab_arg[] )
{
  err_t noerr = CORRECT ;
  
  char nomprog[STRING_LG_MAX] ; 
  char mess[STRING_LG_MAX] ;
  automate_t * automate  = NULL ; 

  strcpy( nomprog , tab_arg[0] ) ;
  if( nb_arg != 1 )
    {
      printf( "Role  : Test des fonctions de generations sur un ecran pour\n" ) ;
      printf( "        - un automate SYNCHRONE (avec %d generations)\n" , NB_GENERATIONS_SYNCHRONE ) ;
      printf( "        - un automate ASYNCHRONE sans memoire (avec %d generations)\n" , NB_GENERATIONS_ASYNCHRONE ) ;
      printf( "        - un automate ASYNCHRONE avec memoire (avec %d generations)\n" , NB_GENERATIONS_ASYNCHRONE_MEMOIRE ) ;
      printf( "        Avec le fichiers test d'initialisation %s\n" , FICHIER_INIT ) ; 
      printf( "Usage : %s\n" , nomprog ) ;
      exit(0) ;
    }
  
  signal( SIGINT , hand_arret ) ;
  
  srandom(getpid()) ;
  /*! -# Initialisation des regles avec les valeurs par defaut  */
  cellule_regles_t regles = cellule_regles_default() ;

  /*! -# Capture des coordonnées des cellules vivantes initiales  */
  printf("Lecture des coordonnees initiales\n");
  coords_t * coords_init = coords_new() ;  ; 
  if( (noerr = coords_scan( FICHIER_INIT , coords_init )) )
    {
      fprintf( stderr ,"%s : Pb chargement liste des coords initiales a partir de %s\n" , nomprog , FICHIER_INIT ) ;
      exit(1) ;
    }
  coords_print( stdout , coords_init ) ;
  
  printf("\n----- Debut %s -----\n" , nomprog  );

  /*! -# Creation du premier automate */
   if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init )) == NULL )
    {
      fprintf( stderr , "%s : Erreur creation automate\n" , nomprog );
      exit(-1);
    }
   
  /*! -# Creation de l'écran pour affichage de cet automate */
  printf("Creation ecran\n");
  if( (ecran = automate_ecran_creer(automate))  == ECRAN_NULL ) 
    {
      fprintf( stderr , "%s : Erreur creation ecran\n" , nomprog );
      exit(-1);
    }

  int n = 0 ;
  int i , j ;
  
  /* ----- SYNCHRONE ----- */
  /*! -# Gestion d'un automate SYNCHRONE */

  automate_wprint( ecran , automate ) ;
  ecran_message_pause_afficher( ecran , "SYNC" ) ;
  
  for( n=1 ; n<=NB_GENERATIONS_SYNCHRONE ; n++ )
    {
      for(i=0;i<HAUTEUR;i++)
	for(j=0;j<LARGEUR;j++)
	  {	
	    if( (noerr = automate_cellule_evoluer( automate , automate_get( automate , i , j ) , &regles ) ) )
	      {
		fprintf( stderr ,"%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		err_print(noerr) ; exit(0) ; 
	      }
	  } 
     
      sprintf( mess , "SYNC %d" , n ) ;
      ecran_message_afficher( ecran , mess ) ;

      automate_wprint( ecran , automate ) ;
      //usleep(50000);

      if( (noerr = automate_generer( automate ) ) )
	{
	  fprintf( stderr ,"%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}
    }

  if( (noerr = automate_destroy( &automate ) ) )
    {
      fprintf( stderr , "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }
  
  ecran_message_stop_afficher( ecran , "<Entree>" ) ;

  /* ----- ASYNCHRONE ----- */
  /*! -# Gestion d'un automate ASYNCHRONE SANS MEMOIRE */
  
  cellule_t * cellule = NULL ;

  if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init )) == NULL )
    {
      fprintf( stderr , "%s : Erreur creation automate\n" , nomprog );
      exit(-1);
    }
  automate_wprint( ecran , automate ) ;
  ecran_message_pause_afficher( ecran , "ASYNC" ) ;
  
  for( n=1 ; n<NB_GENERATIONS_ASYNCHRONE ; n++ )
    {
      /* Choix d'une cellule au hasard */
      i = random() % HAUTEUR ;
      j = random() % LARGEUR ; 
      sprintf(mess , "%d [%d,%d]" , n , i, j ) ;
      ecran_message_afficher( ecran , mess ) ;
      cellule = automate_get( automate , i , j ) ;
       
      if( (noerr = automate_cellule_evoluer( automate , cellule , &regles ) ) )
	{
	  fprintf( stderr ,"%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}
      
      cellule_wprint( ecran , i , j , cellule , VRAI ) ;
      usleep(100000);

      if( (noerr = automate_generer( automate ) ) )
	{
	  fprintf(stderr , "%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}
    }

  if( (noerr = automate_destroy( &automate ) ) )
    {
      fprintf( stderr , "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }
   
  ecran_message_stop_afficher( ecran , "<Entree>" ) ; 
  
  /* ----- ASYNCHRONE avec MEMOIRE ----- */
  /*! -# Gestion d'un automate ASYNCHRONE AVEC MEMOIRE */
  
  const int Nb_Cellules = HAUTEUR * LARGEUR ;
  int nb_cell_evoluees = 0 ;

  if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init )) == NULL )
    {
      fprintf( stderr , "%s : Erreur creation automate\n" , nomprog );
      exit(-1);
    }
  automate_wprint( ecran , automate ) ;
  ecran_message_pause_afficher( ecran , "ASYNC MEM" ) ;
  
  for( n=1 ; n<NB_GENERATIONS_ASYNCHRONE_MEMOIRE ; n++ )
    {
      /* Choix d'une cellule au hasard  mais qui n'a pas encore evoluee dans cette generation */
      nb_cell_evoluees = 0 ; 
      while( nb_cell_evoluees < Nb_Cellules )
	{
	  i = random() % HAUTEUR ;
	  j = random() % LARGEUR ; 
	  sprintf(mess , "%d: %d/%d" , n , nb_cell_evoluees , Nb_Cellules ) ;
	  ecran_message_afficher( ecran , mess ) ;
	  cellule = automate_get( automate , i , j ) ;

	   if( cellule_generation_get(cellule) < n )
	    {
	      nb_cell_evoluees++ ;
	      
	      if( (noerr = automate_cellule_evoluer( automate , cellule , &regles ) ) )
		{
		  fprintf( stderr ,"%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		  err_print(noerr) ; exit(0) ; 
		}

	       if( (noerr = cellule_generation_set( cellule ,
						   cellule_generation_get(cellule) + 1 ) ) )
		{
		  fprintf( stderr , "%s : Pb incrementation de la generation de la cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		  err_print(noerr) ; exit(0) ; 
		}
      
	       cellule_wprint( ecran , i , j , cellule , VRAI ) ;
	       usleep(100000);

	       if( (noerr = automate_generer( automate ) ) )
		 {
		   fprintf(stderr , "%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
		   err_print(noerr) ; exit(0) ; 
		 }
	    }
	}
    }

  if( (noerr = automate_destroy( &automate ) ) )
    {
      fprintf( stderr , "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }
  ecran_message_pause_afficher( ecran , "--FIN--" ) ; 
 
  /* ---------- */

  /*! -# Destruction ecran */
   
  if( (noerr = ecran_detruire(&ecran) ) )
    {
      fprintf( stderr ,"%s : Pb destruction ecran, sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ; 
    }
 
  printf("\n------ Fin %s -----\n\n" , nomprog );
     
  exit(0);
}
