#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <coords.h>

#define FICH_COORDS "fich_test_coords" 

int
main( int nb_arg , char * tab_arg[] )
{
  coord_t coord ;
  int i ; 
  coords_t * liste_coords = (coords_t *) NULL ; /* ATTENTION a bien initialiser la liste des coords */
  int ind ; 
  int noerr = 0 ; 
  int nbcoords = 0 ; 
  int fd ;

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
      printf( "Creation coord numero %d\n" , i ) ;      
      if( ( noerr = coord_set( &coord , 
			       random()%nbcoords,
			       random()%nbcoords,
			       random()%nbcoords*1000 ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  exit(0) ; 
	}

      printf( "Ajout coord numero %d\n" , i ) ; 
      if( ( noerr = coords_coord_add( liste_coords, coord ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  exit(0) ; 
	}

    }

  printf("Affichage liste des coords\n");
  coords_printf(liste_coords);

  printf("Sauvegarde d'une liste de coords dans un fichier\n");
  fd = open( FICH_COORDS , O_CREAT | O_WRONLY , 0666 ) ;
  if( ( noerr = coords_write( fd , liste_coords  ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  close(fd) ; 

  printf("Destruction liste\n");
  if( ( noerr = coords_destroy(&liste_coords) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }

  printf("Restauration fichier dans liste de coords\n");
  fd = open( FICH_COORDS , O_RDONLY , 0666 ) ;
  if( ( noerr = coords_read( fd , &liste_coords ) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  close(fd) ; 
  coords_printf( liste_coords ) ;

  if( nbcoords > 0 ) 
    {
      coord = coords_coord_get(liste_coords,nbcoords-1) ;
      printf("Recherche positive de la coord ") ; 
      coord_printf(coord) ; 
      printf(" dans la liste de coords\n" ) ;
      
      ind = coords_coord_seek( liste_coords, coord , coord_comparer ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'une coord vide dans la liste\n" ); 
      coord = COORD_VIDE ;
      ind = coords_coord_seek( liste_coords, coord , coord_comparer ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;
    }


  printf("Destruction d'une coord dans la liste\n" ) ; 
  ind = random()%(coords_nb_get(liste_coords)-1) ; 
  printf("Destruction coord numero %d\n" , ind ) ;
  coords_coord_del( liste_coords , ind ) ; 
  coords_printf( liste_coords ) ;

  printf("Destruction de tous les coords un par un\n" ) ; 
  ind = coords_nb_get(liste_coords)-1 ; 
  while( coords_nb_get(liste_coords) )
    {
      printf("Destruction coord numero %d\n" , ind ) ;
      coords_coord_del( liste_coords , ind ) ; 
      ind-- ; 
    }
  coords_printf( liste_coords ) ;

  printf("Restauration dans une liste existante\n"); 
  fd = open( FICH_COORDS , O_RDONLY , 0666 ) ; 
  if( ( noerr = coords_read( fd , &liste_coords ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  close(fd) ; 
  coords_printf(liste_coords) ; 

  printf("Copie de liste\n"); 
  coords_t * copie_liste_coords = NULL ;
  if( ( noerr = coords_copier( &copie_liste_coords , liste_coords ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  coords_printf(copie_liste_coords) ; 

  printf( "Destruction globale d'une liste de coords\n");      
  if( ( noerr = coords_destroy(&liste_coords) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  coords_printf(liste_coords) ; 


printf( "Destruction globale de la liste copiee\n");
  if( ( noerr = coords_destroy(&copie_liste_coords) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  coords_printf(copie_liste_coords) ; 



  
  exit(0);
}
