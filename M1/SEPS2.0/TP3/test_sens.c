#include <stdio.h>
#include <stdlib.h>
#include <sens_stdio.h>
#include <sens_string.h>

int 
main( int nb_arg , char * tab_arg[] )
{

     sens_t s ;

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s : test du TDA sens\n" , tab_arg[0]);
	  fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	  exit(-1);
     }

     printf("\n----- Debut %s -----\n" , tab_arg[0] );
     printf( "test affichage sens OUEST-->EST : [") ;
     s = OUEST_EST ;
     sens_print( s ) ;
     printf( "]\ntest affichage sens OUEST<--EST : [") ;
     s = EST_OUEST ;
     sens_print( s ) ;
     printf( "]\ntest affichage sens blanc : [") ;
     sens_blanc_print() ;
     printf("]\n") ; 

     s = OUEST_EST ;
     printf( "test affichage sens string OUEST-->EST : [%s]\n" , sens_string(s) ) ;
     s = EST_OUEST ;
     printf( "test affichage sens string OUEST<--EST : [%s]\n" , sens_string(s) ) ;
     printf( "test affichage sens string blanc : [%s]" , sens_blanc_string() ) ;

     printf("\n------ Fin %s -----\n\n" , tab_arg[0] );
     
     exit(0);
}
