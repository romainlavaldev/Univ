#include <stdio.h>
#include <stdlib.h>
#include <sens_stdio.h>
#include <train_stdio.h>

int 
main( int nb_arg , char * tab_arg[] )
{

     train_t t1 , t2 , t3 ;
     marque_t m ;
     sens_t s ;


     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s : test du TDA train\n" , tab_arg[0]);
	  fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	  exit(-1);
     }

     printf("\n----- Debut test -----\n");

     train_sens_set( &t1  , OUEST_EST ) ;
     train_sens_set( &t2  , EST_OUEST ) ;
     train_marque_set( &t1  , 'A' ) ;
     train_marque_set( &t2  , 'B' ) ;
     train_set( &t3 , OUEST_EST, 'C' ) ;

     printf( "Sens du train [");
     m = train_marque_get( &t1 );
     train_marque_print( &t1 ) ;
     printf( "] = [");
     s = train_sens_get( &t1 ) ;
     sens_print( s ) ;
     printf("]\n");

     printf( "Sens du train [");
     m = train_marque_get( &t2 );
     train_marque_print( &t2 ) ;
     printf( "] = [");
     s = train_sens_get( &t2 ) ;
     sens_print( s ) ;
     printf("]\n");

     printf( "Test affichage train [");
     train_print( &t3 ) ;
     printf( "]\n");

     printf( "Test affichage blanc train [");
     train_marque_blanc_print();     
     printf( "]\n");


     printf("Les trains ") ;
     train_print( &t1 ) ;
     printf(" et ") ;
     train_print( &t2 ) ;
     printf(" sont  ") ;
     if( train_compare( &t1 , &t2 ) )
     {
	  printf( "differents --> OK \n");
     }
     else
     {
	  printf( "identiques --> KO \n");
     }

     printf("Les trains ") ;
     train_print( &t2 ) ;
     printf(" et ") ;
     train_print( &t2 ) ;
     printf(" sont  ") ;
     if( train_compare( &t2 , &t2 ) )
     {
	  printf( "differents --> KO \n");
     }
     else
     {
	  printf( "identiques --> OK \n");
     }
     train_compare( &t2 , &t2 );
     printf(  "------ Fin test- -----\n\n");
     
     exit(0);
}
