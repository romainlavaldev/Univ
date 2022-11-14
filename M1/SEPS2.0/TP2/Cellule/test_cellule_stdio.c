#include <cellule_stdio.h>

/*! 
 * \file  test_cellule_stdio.c
 * \brief Test des primitives d'une cellule avec affichage des résultats sur la sortie standard
 */

/*! \def FICHIER_TEST_COORDS
 * Nom du fichier contenant les coordonnées pour les tests
 */
#define FICHIER_TEST_COORDS "../Fichiers/fichier_test_coords.txt"

/*! Programme Principal */
int
main( int nb_arg , char * tab_arg[] )
{
  err_t noerr = CORRECT ; 
  cellule_t * cell = NULL ;
  int nb_cellules , taille_ligne ;
  coord_t coord ;
  int i ;
  int l , c ;
  cellule_etat_t etat = VIVANTE ;
     
  /*----------*/

  if( nb_arg != 3 )
    {
      fprintf( stderr , "Role  : Test creations de <nb cellules> cellules pour un tableau de <taille ligne> colonnes\n"); 
      fprintf( stderr , "Usage : %s <nb cellules> <taille ligne>\n",
	       tab_arg[0] );
      exit(-1) ;
    }
     
  sscanf( tab_arg[1] , "%d" , &nb_cellules ) ;
  sscanf( tab_arg[2] , "%d" , &taille_ligne ) ;
     
  srandom( (unsigned int)getpid() );

  printf( "Affichage cellules:\n" );
  for( i=0 ; i<nb_cellules ; i++ )
    {
      /*! -# Test des fonctions get and set */
      l=random()%100 ;
      c=random()%taille_ligne ;
      coord_set( &coord , l , c ) ;

      if( random()%2 ) 
	etat = VIVANTE ;
      else
	etat = MORTE ;
	 
      if( (cell = cellule_coord_new( &coord , etat )) == NULL )
	{
	  printf( "Erreur lors de la creation de la cellule #%d\n" , i ) ;
	  exit(1) ; 
	}
	 
      printf(" #%d : " , i ) ; 
      cellule_map( stdout, cell )  ;
      printf("\n") ;

      if( (noerr = cellule_destroy( &cell ) ) )
	{
	  printf( "Erreur lors de la destruction de la cellule #%d, sortie erreur %d\n" , i , noerr ) ;
	  err_print(noerr) ; exit(0) ;  
	}
    }
  

  coords_t * coords_init = coords_new() ;
  
  /*! -# Test du chargement des coordonnées initiales à partir d'un fichier */
  printf("Chargement coordonnees initiales\n"); 
  if( (noerr = coords_scan( FICHIER_TEST_COORDS , coords_init ) ) )
    {
      printf( "Pb creation liste des coords initiales a partir du fichier %s, sortie erreur %d\n" , FICHIER_TEST_COORDS , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }
  coords_print(stdout , coords_init ) ; 
  printf("\n") ;
  
  /*! -# Test d'initialisations de cellule */
  printf("Test initialisation cellule a [8,0]..." ) ; fflush(stdout) ; 
  cell = cellule_initialiser(8 , 0 , coords_init ) ;
  /*! -# Test des fonctions de test */
  if( cellule_vivante(cell) )
    printf(" OK : ");
  else
    printf(" KO !!! : ") ;
  cellule_map(stdout , cell) ;
  printf("\n") ;
  /*! -# Test destruction d'une cellule */
  cellule_destroy(&cell) ; 

  printf("Test initialisation cellule a [1,1]..." ) ; fflush(stdout) ; 
  cell = cellule_initialiser(1 , 1 , coords_init ) ;
  if( cellule_morte(cell) )
    printf(" OK : ");
  else
    printf(" KO !!! : ") ;
  cellule_map(stdout , cell) ;
  printf("\n") ;
  cellule_destroy(&cell) ; 
  
  
  exit(0); 
}
