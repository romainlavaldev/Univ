#include <cellule_ecran.h>
#include <signal.h>

/*! 
 * \file  test_cellule_ecran.c
 * \brief Test des primitives d'une cellule avec sortie sur écran
 */

/*! Variable globale de l'écran d'affichage (car utilisation d'un handler) */
ecran_t * ecran = ECRAN_NULL ;

/*! Handler pour interruption du programme */
void hand_arret( int sig ) 
{
  ecran_detruire(&ecran) ;
  exit(0); 
}

/*! Programme principal */

int 
main( int argc , char * argv[] )
{

  char mess[STRING_LG_MAX] ;
  cellule_t * cellule = NULL ;
  char NomProg[256] ; 
  strcpy( NomProg , argv[0] ) ;
  
  ecran_t * ecran = ECRAN_NULL ; 

  if( argc != 5 )
    {
      fprintf( stderr , "%s : test du TDA cellule sur sortie ecran\n" , NomProg);
      fprintf( stderr , "usage : %s <Hauteur ecran> <Largeur ecran> <lig cellule> <col cellule>\n" , NomProg);
      exit(-1);
    }

  int Hauteur = atoi(argv[1]) ;
  int Largeur = atoi(argv[2]) ;
  int Lig     = atoi(argv[3]) ;
  int Col     = atoi(argv[4]) ;

  /* Assertions */
  if( ( Lig<0) || (Lig>=Hauteur) )
    {
      fprintf( stderr , "Erreur coord ligne %d doit etre dans [0..%d]\n" , Lig , Hauteur-1 );
      exit(-1);
   }

   if( ( Col<0) || (Col>=Largeur) )
    {
      fprintf( stderr , "Erreur coord colonne %d doit etre dans [0..%d]\n" , Col , Largeur-1 );
      exit(-1);
   }

   /* ---------- */
    /*! <ol> */
  
  signal( SIGINT , hand_arret ) ; 

  printf("\n----- Debut %s -----\n" , NomProg );

  /*! <li> Creation d'un écran , Taille de l'ecran = taille du terrain + bordure */
  if( ( ecran = ecran_creer( Hauteur , Largeur ) ) == NULL )
    {
      fprintf( stderr , "Erreur creation ecran\n" );
      exit(-1);
   }
  wrefresh( ecran_affichage_get(ecran) ) ;
  wrefresh( ecran_messages_get(ecran) ) ;

  /*! <li> Test de Création d'une cellule*/
  cellule = cellule_new( Lig , Col , INIT ) ;

  /*! <li> Tests des affichages sur écran selon les différents états d'une cellule */
  cellule_etat_t etat , etat_next ;
  for( etat=INIT ; etat<=VIVANTE ; etat++ )
    {
      cellule_etat_set(cellule , etat );
      
      for( etat_next=INIT ; etat_next<=VIVANTE ; etat_next++ )
	{
	  cellule_etat_next_set(cellule , etat_next );
	  
	  cellule_wprint( ecran , Lig , Col , cellule , VRAI ) ;
	  
	  sprintf( mess , "%s/%s" ,
		   cellule_etat_2_string(cellule_etat_get(cellule)) ,
		   cellule_etat_2_string(cellule_etat_next_get(cellule)) ) ;
	  ecran_message_pause_afficher( ecran , mess ) ;
	}
    }

  ecran_message_pause_afficher( ecran , "Fin Test" ) ;

  /*! <li> Destruction de l'écran */
  ecran_detruire(&ecran) ;

  /*! </ol> */
  
  printf("\n------ Fin %s -----\n\n" , NomProg );
     
  exit(0);
}


