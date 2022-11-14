#include <string.h>
#include <automate_stdio.h>
#include <coords_stdio.h>

/*!
 * \file test_automate_stdio.c
 * \brief Test des fonctions de gestion d'un automate avec affichage des résultats sur la sortie standard
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
#define NB_GENERATIONS_ASYNCHRONE_MEMOIRE 3

/*! Programme Principal */

int
main( int argc , char * argv[] )
{
  automate_t * automate = NULL ;
  err_t noerr = CORRECT ;
  char nomprog[512] ;

  
  /*----------*/

  /*! <ol> */
  strcpy( nomprog , argv[0] ) ;
  
  if( argc != 1 )
    {
      printf( "Role  : Test des fonctions de generations pour\n" ) ;
      printf( "        - un automate SYNCHRONE (avec %d generations)\n" , NB_GENERATIONS_SYNCHRONE ) ;
      printf( "        - un automate ASYNCHRONE sans memoire (avec %d generations)\n" , NB_GENERATIONS_ASYNCHRONE ) ;
      printf( "        - un automate ASYNCHRONE avec memoire (avec %d generations)\n" , NB_GENERATIONS_ASYNCHRONE_MEMOIRE ) ;
      printf( "        Avec le fichiers test d'initialisation %s\n" , FICHIER_INIT ) ; 
      printf( "Usage : %s\n" , nomprog ) ;
      exit(0) ;
    }

  srandom( (unsigned int)getpid() );

  /*! <li> Initialisation des regles avec les valeurs par defaut  */
  cellule_regles_t regles = cellule_regles_default() ; 

  /*! <li> Lecture des coordonnées des cellules vivantes */
  printf("Lecture des coordonnees initiales\n");
  coords_t * coords_init = coords_new() ;  ; 
  if( (noerr = coords_scan( FICHIER_INIT , coords_init )) )
    {
      printf("%s : Pb chargement liste des coords initiales a partir de %s\n" , nomprog , FICHIER_INIT ) ;
      exit(1) ;
    }
  coords_print( stdout , coords_init ) ;
  
  /*! <li> Creation de l'automate + cellules */
  printf("Creation automate\n") ; 
  if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init ) ) == NULL )
    {
      printf( "%s : erreur\n" , nomprog ) ;
      exit(1) ; 
    }
  automate_print( stdout , automate ) ;

  /*! <li> Evolution synchrone de l'automate : pour chaque génération */

  printf("Evolution synchrone de l'automate\n") ;
  int n = 0 ;
  int i , j ;

  for( n=1 ; n<NB_GENERATIONS_SYNCHRONE ; n++ )
    {
      /*! <ul> */
      /*! <li> Calcul de la génération n+1 pour toutes les cellules */
      for(i=0;i<HAUTEUR;i++)
	for(j=0;j<LARGEUR;j++)
	  {	
	    if( (noerr = automate_cellule_evoluer( automate , automate_get( automate , i , j ) , &regles ) ) )
	      {
		printf("%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		err_print(noerr) ; exit(0) ; 
	      }
	  } 
      
      /*! <li> Affichage de l'automate en fonction des generation n et n+1 */
      system("clear") ;
      printf("SYNCHRONE : Generation %d\n" , n ) ; 
      automate_print( stdout , automate ) ;
      usleep(100000);

      /*! <li> Passage à la prochaine génération : n <-- n+1  */
      if( (noerr = automate_generer( automate ) ) )
	{
	  printf("%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}
      /*! </ul> */
    }

  /*! <li> Destruction de l'automate */
  printf("Destruction automate\n") ; 
  if( (noerr = automate_destroy( &automate ) ) )
    {
      printf( "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }

  Pause("Tapez sur <Entree> pour continuer...") ;

  /* ---------- */

  /*! <li> Re-création de l'automate + cellules */
  printf("Creation automate\n") ; 
  if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init ) ) == NULL )
    {
      printf( "%s : erreur\n" , nomprog ) ;
      exit(1) ; 
    }
  automate_print( stdout , automate ) ;
  
  /*! <li> Evolution asynchrone sans memoire de l'automate: à chaque génération */
  printf("Evolution asynchrone sans memoire de l'automate\n") ;


  for( n=1 ; n<NB_GENERATIONS_ASYNCHRONE ; n++ )
    {
      /*! <ul> */  
      /*! <li> Une cellule est choisie au hasard  */
      i = random() % HAUTEUR ;
      j = random() % LARGEUR ; 
      printf(" Evolution de la cellule [%d,%d]\n" , i, j ) ;

      /*! <li> Calcul de la generation suivante pour cette cellule  */
      if( (noerr = automate_cellule_evoluer( automate , automate_get( automate , i , j ) , &regles ) ) )
	{
	  printf("%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}

      /*! <li> Affichage de l'automate en tenant compte des generations n et n+1  */
      system("clear") ;
      printf("ASYNCHRONE SANS MEMOIRE : Generation %d\n" , n ) ; 
      automate_print( stdout , automate ) ;
      usleep(100000);

      /*! <li> Passage à la génération suivante */
      if( (noerr = automate_generer( automate ) ) )
	{
	  printf("%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
	  err_print(noerr) ; exit(0) ; 
	}
      /*! </ul> */
    }

  /*!	<li> Destruction automate + cellules */
  printf("Destruction automate\n") ; 
  if( (noerr = automate_destroy( &automate ) ) )
    {
      printf( "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }

  Pause("Tapez sur <Entree> pour continuer...") ;
  
  /* ---------- */

  /*! <li> Re-création de l'automate + cellules */
  printf("Creation automate\n") ; 
  if( (automate = automate_new( HAUTEUR , LARGEUR , coords_init ) ) == NULL )
    {
      printf( "%s : erreur\n" , nomprog ) ;
      exit(1) ; 
    }
  automate_print( stdout , automate ) ;
  
  /*! <li> Evolution asynchrone avec memoire de l'automate: une cellule est choisie au hasard mais elle ne doit pas encore avoir evoluée dans la génération courante.
   * Pour chaque génération 
   */

  printf("Evolution asynchrone avec memoire de l'automate\n") ;
  const int Nb_Cellules = HAUTEUR * LARGEUR ;
  int nb_cell_evoluees = 0 ;
  cellule_t * cellule = NULL ;

  for( n=1 ; n<=NB_GENERATIONS_ASYNCHRONE_MEMOIRE ; n++ )
    {
      /*! <ul> */      
       printf( "---Passage Generation %d\n" , n ) ;
      /*! <li> Toutes les N itérations */
      nb_cell_evoluees = 0 ; 
      while( nb_cell_evoluees < Nb_Cellules )
	{
	  /*! <ul> */
	  /*! <li> Choix d'une cellule au hasard */
	  i = random() % HAUTEUR ;
	  j = random() % LARGEUR ;
	  cellule = automate_get( automate , i, j ) ;

	  if( n > 1 )
	    {
	      printf( "---Generation %d :" , n ) ;
	      cellule_map(stdout , cellule) ;
	      printf("\n") ;		      
	    }

	  /*! <li> Si la cellule n'a pas déjà évoluée pour la génération courante */
	  if( cellule_generation_get(cellule) < n )
	    {
	      /*! <ul> */
	      /*! <li> Calcul de la génération n+1 pour cette cellule */
	      printf(" Evolution de la cellule [%d,%d]\n" , i, j ) ;
	      nb_cell_evoluees++ ;
	      
	      if( (noerr = automate_cellule_evoluer( automate , automate_get( automate , i , j ) , &regles ) ) )
		{
		  printf("%s : Pb evolution  cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		  err_print(noerr) ; exit(0) ; 
		}

	      /*! <li> Mise à jour du numéro de la génération pour cette cellule */
	      if( (noerr = cellule_generation_set( cellule ,
						   cellule_generation_get(cellule) + 1 ) ) )
		{
		  printf("%s : Pb incrementation de la generation de la cellule [%d,%d], sortie erreur %d\n" , nomprog , i, j , noerr ) ;
		  err_print(noerr) ; exit(0) ; 
		}

	      /*! <li>Affichage de l'automate en fonction des générations n et n+1 */
	      system("clear") ;
	      printf("ASYCHRONE AVEC MEMOIRE : Generation %d (%d/%d)\n" , n , nb_cell_evoluees , Nb_Cellules ) ; 
	      automate_print( stdout , automate ) ;
	      usleep(100000);

	      /*! <li>Passage à la génération suivante de l'automate */
	      if( (noerr = automate_generer( automate ) ) )
		{
		  printf("%s : Pb prise en compte nouvelle generation automate, sortie erreur %d\n" , nomprog , noerr ) ;
		  err_print(noerr) ; exit(0) ; 
		}
	      /*! </ul> */
	    }
	  /*! </ul> */
	}
      /*! </ul> */ 
    }
  
  /*! <li> Destruction de l'automate + cellules */
  printf("Destruction automate\n") ; 
  if( (noerr = automate_destroy( &automate ) ) )
    {
      printf( "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }

  Pause("Tapez sur <Entree> pour continuer...") ; 
  
  /*! </ol> */
  exit(0); 
}
