#include <string.h>
#include <fcntl.h> /* open */

#include <bateau.h>

#define FICH_BATEAU "fich_test_bateau.bin" 

int
main( int nb_arg , char * tab_arg[] )
{
  int noerr = 0 ; 
  int fd ;
  char mess[128] ; 

  bateau_t * bateau = BATEAU_NULL ; 
  coords_t * coords = NULL ; 
  coord_t coord = COORD_VIDE ;

  int i ; 

  /*----------*/

  if( nb_arg != 1 )
    {
      fprintf( stderr , "\n%s: Test du TDA bateau\n\n" , tab_arg[0] );
      fprintf( stderr , "Usage : %s\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  /* Initialisation generation nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());


  printf("\tCreation corps\n") ;
  coords = coords_new() ; 
  for( i=0 ; i<BATEAU_TAILLE ; i++ ) 
    {
      printf("\t\tCreation coord %d\n" , i ) ;
      coord_set( &coord , 
		 1+random()%10 ,
		 10+random()%10 , 
		 100+random()%10 ) ;
	     
      coords_coord_add( coords , coord ) ; 
    }
  printf("Creation bateau\n") ;
  if( ( bateau = bateau_new( coords , 
			     'A'+random()%26 , 
			     getpid() ) ) == BATEAU_NULL ) 
    {
      printf("Sortie erreur\n") ; 
      exit(-1) ;
    }

  printf("\tDestruction corps\n") ;
  coords_destroy(&coords) ;


  /* Test affichage d'un bateau */
  printf("\nAffichage structure bateau: ");
  bateau_printf( bateau ); 
  printf("\n\n");

  /* Tests avec fichier */
 
  printf("Bateau a sauver:\n");
  bateau_printf(bateau) ; printf("\n") ; 
  
  printf( "Sauvegarde bateau " ) ;  fflush(stdout); 

 if( ( fd = open( FICH_BATEAU , O_CREAT | O_WRONLY , 0666 ) ) == -1 )
    {
      sprintf( mess, "Pb sur Creation en ecriture de %s" , FICH_BATEAU ) ; 
      perror(mess) ; 
      exit(-1) ; 
      
    }
  if( ( noerr = bateau_write( fd , bateau ) ) )
    
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(-1) ;       
    }
  close(fd) ;

  bateau_destroy( &bateau ) ; 

  printf( "restauration bateau " ) ; fflush(stdout); 
  if( ( fd = open(  FICH_BATEAU , O_RDONLY , 0666 ) ) == -1 )
    {
      sprintf( mess , "Pb sur ouverture en lecture de %s" , FICH_BATEAU ) ; 
      perror(mess) ; 
      exit(-1) ;       
    }
 
  if( ( noerr = bateau_read( fd , &bateau ) ) )
    {
      sprintf( mess , "Pb sur ouverture en lecture de %s" , FICH_BATEAU ) ; 
      perror(mess) ; 
      exit(-1) ;       
    }
  printf("OK\n") ;

  printf("Bateau restaure:\n");
  bateau_printf(bateau) ; printf("\n") ; 
  
  unlink(FICH_BATEAU);
 
 exit(0); 
}
