#include <coords_stdio.h>

/*!
 * \file test_coords_stdio.c
 * \brief Test des fonctions de gestion d'une liste de coordonnnées avec affichage des résultats sur la sortie standard
 */

/*!\def FICHIER_TEST_COORDS
 * Fichier contenant une liste de coordonnées de test
 */
#define FICHIER_TEST_COORDS "../Fichiers/fichier_test_coords.txt" 

/*! Programme Principal */
int
main( int nb_arg , char * tab_arg[] )
{
  coord_t coord ;
  int i ; 
  coords_t * liste_coords = NULL ; /* ATTENTION a bien initialiser la liste des coords */
  int ind ; 
  err_t noerr = 0 ; 
  int nbcoords = 0 ; 

  /*----------*/

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <nb coords>\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  srandom(getpid()) ;

  nbcoords = atoi( tab_arg[1] ) ; 
     
  printf("Creation liste\n");
  liste_coords = coords_new() ; 

  printf("Ajout de coords dans la liste\n");
  for( i=0 ; i<nbcoords ; i++ )
    {
      printf( "Creation coord numero %d [%i,%i](%d)\n" , i , i+1 , i+2 , nbcoords+i*1000 ) ;      
      if( ( noerr = coord_set( &coord , 
			       i+1 ,
			       i+2 ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  err_print(noerr) ; exit(0) ;  
	}

      printf( "Ajout coord numero %d\n" , i ) ; 
      if( ( noerr = coords_add( liste_coords, coord ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  err_print(noerr) ; exit(0) ;  
	}

    }

  printf("Affichage liste des coords\n");
  coords_print(stdout, liste_coords);

  if( nbcoords > 0 ) 
    {
      coord = coords_get(liste_coords,nbcoords-1) ;
      printf("Recherche positive de la coord ") ; 
      coord_print( stdout , &coord) ; 
      printf(" dans la liste de coords\n" ) ;
      
      ind = coords_seek( liste_coords, &coord , coord_comparer ) ;
      if( ind != PAS_TROUVE ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'une coord vide dans la liste\n" ); 
      coord = COORD_VIDE ;
      ind = coords_seek( liste_coords, &coord , coord_comparer ) ;
      if( ind == PAS_TROUVE ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;
    }


  printf("Destruction d'une coord dans la liste\n" ) ; 
  ind = random()%(coords_nb_get(liste_coords)) ; 
  printf("Destruction coord numero %d\n" , ind ) ;
  coords_del( liste_coords , ind ) ; 
  coords_print( stdout , liste_coords ) ;

  printf("Destruction de tous les coords un par un\n" ) ; 
  ind = coords_nb_get(liste_coords)-1 ; 
  while( coords_nb_get(liste_coords) )
    {
      printf("Destruction coord numero %d\n" , ind ) ;
      coords_del( liste_coords , ind ) ; 
      ind-- ; 
    }
  coords_print( stdout , liste_coords ) ;

  printf("Destruction de la liste vide\n" ) ; 
  if( ( noerr = coords_destroy(&liste_coords) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      err_print(noerr) ; exit(0) ;  
    }
  
  printf("Lecture d'une liste de coords dans le fichier %s\n" ,FICHIER_TEST_COORDS );
  liste_coords = coords_new() ; 
  if( ( noerr = coords_scan( FICHIER_TEST_COORDS , liste_coords ) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      err_print(noerr) ; exit(0) ;  
    }
  coords_print( stdout , liste_coords ) ;
  
  printf("Copie de liste\n"); 
  coords_t * copie_liste_coords = NULL ;
  if( ( noerr = coords_copier( &copie_liste_coords , liste_coords ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      err_print(noerr) ; exit(0) ;  
    }
  coords_print(stdout , copie_liste_coords) ; 

  printf( "Destruction globale d'une liste de coords\n");      
  if( ( noerr = coords_destroy(&liste_coords) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      err_print(noerr) ; exit(0) ;  
    }
  coords_print(stdout , liste_coords) ; 


  printf( "Destruction globale de la liste copiee\n");
  if( ( noerr = coords_destroy(&copie_liste_coords) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      err_print(noerr) ; exit(0) ;  
    }
  coords_print(stdout , copie_liste_coords) ;

  exit(0);
}
