#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <voie_unique_stdio.h>

int 
main( int nb_arg , char * tab_arg[] )
{
  voie_unique_t * voie_unique ;
  train_t t[6];
  int cr ;

  /*-----*/

  if( nb_arg != 1 )
    {
      fprintf( stderr , "%s : test affichage voie unique sur stdio\n" , tab_arg[0]);
      fprintf( stderr , "usage : %s \n" , tab_arg[0] );
      exit(-1);
    }

  printf("\n----- Debut %s -----\n" , tab_arg[0] );

  srandom(getpid());

  train_set( &t[0] , OUEST_EST , 'A' );
  train_set( &t[1] , EST_OUEST , 'B' );
  train_set( &t[2] , OUEST_EST , 'C' );
  train_set( &t[3] , EST_OUEST , 'D' );
  train_set( &t[4] , OUEST_EST , 'E' );
  train_set( &t[5] , EST_OUEST , 'F' );

  /* Creation voie unique */
  if( ( voie_unique = voie_unique_creer() ) == NULL )
    {
      fprintf( stderr , "Erreur voie_unique_initialiser\n");
      exit(1);
    }

  printf("Affichage voie vide\n") ; 
  voie_unique_print( voie_unique ) ;


  /* Insertion trains */
  voie_unique_inserer( voie_unique ,  t[0] , OUEST  , OUEST_EST ); 
  voie_unique_inserer( voie_unique ,  t[1] , OUEST  , EST_OUEST ); 
  voie_unique_inserer( voie_unique ,  t[2] , UNIQUE , OUEST_EST ); 
  voie_unique_inserer( voie_unique ,  t[4] , EST    , OUEST_EST ); 
  voie_unique_inserer( voie_unique ,  t[5] , EST    , EST_OUEST ); 

  printf("Affichage sans collision\n") ;
  voie_unique_print( voie_unique ) ;
  if( voie_unique_collision_verifier( voie_unique ) == -1 )
    {
      printf( "Erreur : COLLISION detectee\n"  ) ; 
    }
  else
    {
      printf( " ----- OK -----\n"  ) ; 
    }

  voie_unique_inserer( voie_unique ,  t[3] , UNIQUE , EST_OUEST ); 
  printf("Affichage avec collision\n") ;
  voie_unique_print( voie_unique ) ;
  if( voie_unique_collision_verifier( voie_unique ) == -1 )
    {
      printf( " OK : COLLISION detectee \n"  ) ; 
    }
  else
    {
      printf( "Erreur : Collision non detectee !!!!! "  ) ; 
    }

  voie_unique_extraire( voie_unique ,  t[0] , OUEST  , OUEST_EST ); 
  voie_unique_extraire( voie_unique ,  t[1] , OUEST  , EST_OUEST ); 
  voie_unique_extraire( voie_unique ,  t[2] , UNIQUE , OUEST_EST ); 
  voie_unique_extraire( voie_unique ,  t[3] , UNIQUE , EST_OUEST ); 
  voie_unique_extraire( voie_unique ,  t[4] , EST    , OUEST_EST ); 
  voie_unique_extraire( voie_unique ,  t[5] , EST    , EST_OUEST ); 

  printf( "Apres Extractions de tous les trains"  ) ; 
  voie_unique_print( voie_unique ) ;


  if( (cr = voie_unique_detruire( &voie_unique )))
    {
      fprintf( stderr , "Erreur voie_unique_fermer\n");
      exit(cr);
    }
     

  printf(  "\n------ Fin %s ------\n\n" , tab_arg[0] );
     
  exit(0);
}
