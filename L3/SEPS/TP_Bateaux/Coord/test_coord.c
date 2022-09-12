#include <string.h>
#include <fcntl.h> /* open */

#include <coord.h>

int
main( int nb_arg , char * tab_arg[] )
{
  int noerr = 0 ; 
  coord_t c , c2 , c3 ;
  int ligne , colonne  ;
  off_t position ;
  int cmp , diff1 , diff2 , diff3 ;
  int fd ;
  
  /*----------*/

  if( nb_arg != 4 )
    {
      fprintf( stderr , "\n%s: Test du TDA coord\n\n" , tab_arg[0] );
      fprintf( stderr , "Usage : %s <ligne> <colonne> <position>\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  sscanf( tab_arg[1] , "%d" , &ligne ) ;
  sscanf( tab_arg[2] , "%d" , &colonne ) ;
  sscanf( tab_arg[3] , "%lld" , &position ) ;

  /* Initialisation generation nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  /* Test ecriture dans une case */
  coord_set( &c,
	     ligne,		
	     colonne,		
	     position );

  coord_ligne_set( &c3 , ligne );
  coord_colonne_set( &c3 , colonne );
  coord_position_set( &c3 , position );


  /* Test affichage d'une case */
  printf("\nAffichage structure case affectee globalement: ");
  coord_printf( c ); 
  printf("\n\n");


  printf("\nAffichage structure case affectee attribut par attribut: ");
  coord_printf( c3 ); 
  printf("\n\n");

  /* Test lecture d'une case */
  coord_get( c,		
	      &ligne,	              
	      &colonne,	            
	      &position);	

  printf("\nAffichage des caracteristiques de la case affectee globalement:\n");
  printf("\tligne    = %d\n"  , ligne );
  printf("\tcolonne  = %d\n"  , colonne );
  printf("\tposition = %lld\n" , position );
  printf("\n\n");

  ligne = coord_ligne_get(c3);
  colonne = coord_colonne_get(c3);
  position = coord_position_get(c3);

  printf("\nAffichage des caracteristiques de la case affectee attribut par attribut:\n");
  printf("\tligne    = %d\n"  , ligne );
  printf("\tcolonne  = %d\n"  , colonne );
  printf("\tposition = %lld\n" , position );
  printf("\n\n");

  /* Test comparaison de 2 coordonnees */
  diff1 = (int)(random()%3) ; diff1 = diff1 - 1 ; 
  diff2 = (int)(random()%3) ; diff2 = diff2 - 1 ; 
  diff3 = (int)(random()%3) ; diff3 = diff3 - 1 ; 

  coord_set( &c2 ,
		ligne+diff1 ,
		colonne+diff2,
		position+diff3 ) ;
     
  cmp = coord_comparer( c , c2 );
  coord_printf( c ); 
  if( cmp < 0 )
    {
      printf( " est inferieure a ") ;
    }
  else
    {
      if( cmp > 0 )
	printf( " est superieure a ");
      else
	printf( " est egale a ");
    }
  coord_printf( c2 ); 
  printf( "\n\n");

  /* Test affectation */
  coord_copier( &c2 , c );
  cmp = coord_comparer( c , c2 );
  coord_printf( c ); 
  if( cmp < 0 )
    {
      printf( " est inferieure a ") ;
    }
  else
    {
      if( cmp > 0 )
	printf( " est superieure a ");
      else
	printf( " est egale a ");
    }
  coord_printf( c2 ); 
  printf( "\n\n");


  /* Tests avec fichier */

 
  printf("Coord a sauver:\n");
  coord_printf(c) ; printf("\n") ; 
  
  printf( "Sauvegarde coord " ) ;  fflush(stdout); 

 if( ( fd = open( "fich_test_coord.bin" , O_CREAT | O_WRONLY , 0666 ) ) == -1 )
    {
      perror("Pb sur Creation en ecriture de fich_test_coord.bin") ; 
      exit(-1) ; 
      
    }
  if( ( noerr = coord_write( fd , c ) ) )
    
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(-1) ;       
    }
  close(fd) ;

  
  c = COORD_VIDE ;
  printf( "restauration coord " ) ; fflush(stdout); 
  if( ( fd = open( "fich_test_coord.bin" , O_RDONLY , 0666 ) ) == -1 )
    {
      perror("Pb sur ouverture en lecture de fich_test_coord.bin") ; 
      exit(-1) ;       
    }
  printf("OK\n") ; 
 
  if( ( noerr = coord_read( fd , &c ) ) )
    {
      perror("Pb sur ouverture en lecture de fich_test_coord.bin") ; 
      exit(-1) ;       
    }
  printf("OK\n") ;
  printf("Coord restauree:\n");
  coord_printf(c) ; printf("\n") ; 
  
  unlink("fich_test_coord.bin");
 
 exit(0); 
}
