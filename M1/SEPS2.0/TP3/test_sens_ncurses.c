#include <stdio.h>
#include <stdlib.h>

#include <sens_ncurses.h>
#include <ecran.h>

int 
main( int nb_arg , char * tab_arg[] )
{
  ecran_t * ecran = ECRAN_NULL ; 
  sens_t s ;

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s : test du TDA sens sur un ecran\n" , tab_arg[0]);
	  fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	  exit(-1);
     }

     printf("\n----- Debut %s -----\n" , tab_arg[0] );
     ecran = ecran_creer() ; 
     wrefresh( ecran_ligne_get(ecran) ) ;
     wrefresh( ecran_messages_get(ecran) ) ;

     int L = ecran_largeur_get(ecran) ; 
     
     s = OUEST_EST ;
     sens_wprint( ecran , 2 , L/2 , s ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage sens OUEST-->EST" ) ; 

     s = EST_OUEST ;
     sens_wprint( ecran , 2 , L/2 , s ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage sens OUEST<--EST") ;

     sens_blanc_wprint(ecran , 2 , L/2 ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage sens blanc") ;

     sens_vide_wprint(ecran , 2 , L/2 ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     ecran_message_pause_afficher( ecran , "test affichage sens vide") ;
     
     ecran_detruire(&ecran) ;
     printf("\n------ Fin %s -----\n\n" , tab_arg[0] );
     
     exit(0);
}
