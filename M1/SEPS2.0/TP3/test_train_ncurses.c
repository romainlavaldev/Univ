#include <stdio.h>
#include <stdlib.h>

#include <train_ncurses.h>
#include <ecran.h>

int 
main( int nb_arg , char * tab_arg[] )
{
  ecran_t * ecran = ECRAN_NULL ; 
  train_t t1 , t2 ;

  if( nb_arg != 1 )
    {
      fprintf( stderr , "%s : test du TDA train sur un ecran\n" , tab_arg[0]);
      fprintf( stderr , "usage : %s \n" , tab_arg[0] );
      exit(-1);
     }

  printf("\n----- Debut %s -----\n" , tab_arg[0] );
     ecran = ecran_creer() ; 
     int L = ecran_largeur_get(ecran) ; 
     wrefresh( ecran_ligne_get(ecran) ) ;
     wrefresh( ecran_messages_get(ecran) ) ;

     train_set( &t1  , OUEST_EST , 'A' ) ;
     train_set( &t2  , EST_OUEST , 'B' ) ;

     train_wprint( ecran , 2 , L/2 , &t1 ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage train A" ) ; 

     train_wprint( ecran , 2 , L/2 , &t2 ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage train B") ;
    
     ecran_detruire(&ecran) ;
     printf("\n------ Fin %s -----\n\n" , tab_arg[0] );
     
     exit(0);
}
