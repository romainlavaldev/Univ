#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ecran.h>

int 
main( int nb_arg , char * tab_arg[] )
{
  ecran_t * ecran = ECRAN_NULL ; 
  int i = 0 ; 
  char * compte[6] = { "ZERO" , "UN" , "DEUX" , "TROIS" , "QUATRE" , "CINQ" } ;

  if( nb_arg != 1 )
    {
      fprintf( stderr , "%s : test du TDA ecran\n" , tab_arg[0]);
      fprintf( stderr , "usage : %s \n" , tab_arg[0] );
      exit(-1);
    }

  printf("\n----- Debut %s -----\n" , tab_arg[0] );
  ecran = ecran_creer() ; 
  wrefresh( ecran_ligne_get(ecran) ) ;
  wrefresh( ecran_messages_get(ecran) ) ;

  /* Calcul milieu ecran */
  int L = ecran_largeur_get(ecran) ; 
  for( i=5 ; i>=0 ; i-- )
    {
      mvwprintw( ecran_ligne_get(ecran), 
		 2 , (int) L/2 , 
		 "%1d", i );
      wrefresh( ecran_ligne_get(ecran) ) ;
      ecran_message_pause_afficher( ecran , compte[i] ) ; 
    }

  ecran_detruire(&ecran) ;
  printf("\n------ Fin %s -----\n\n" , tab_arg[0] );
     
  exit(0);
}
