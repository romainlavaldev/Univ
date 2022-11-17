#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <tests.h>

#include <voie_unique_ncurses.h>



int 
main( int nb_arg , char * tab_arg[] )
{
  voie_unique_t * voie_unique ;
  ecran_t * ecran ; 
  train_t t[6];
  int cr ;
  char mess[ECRAN_LG_MESS] ; 

     /*-----*/

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s : test affichage voie unique avec ncurses\n" , tab_arg[0]);
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

     /* Creation ecran */
     ecran = ecran_creer() ; 
     wrefresh( ecran_ligne_get(ecran) ) ;
     wrefresh( ecran_messages_get(ecran) ) ;

     int x = 2 ;
     voie_unique_wprint( ecran , voie_unique , 6 , 3 , &x ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     sprintf( mess , "Affichage voie vide, aff_fin = %d "  , x ) ; 
     ecran_message_pause_afficher( ecran , mess ) ; 
     sleep(TEMPS_VOIR) ;

     /* Insertion trains */
     voie_unique_inserer( voie_unique ,  t[0] , OUEST  , OUEST_EST ); 
     voie_unique_inserer( voie_unique ,  t[1] , OUEST  , EST_OUEST ); 
     voie_unique_inserer( voie_unique ,  t[2] , UNIQUE , OUEST_EST ); 
     voie_unique_inserer( voie_unique ,  t[4] , EST    , OUEST_EST ); 
     voie_unique_inserer( voie_unique ,  t[5] , EST    , EST_OUEST ); 

     x=2 ;
     voie_unique_wprint( ecran , voie_unique , 6 , 3 , &x ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     if( voie_unique_collision_verifier( voie_unique ) == -1 )
       {
	 ecran_message_pause_afficher( ecran ,"Erreur : COLLISION detectee"  ) ; 
       }
     else
       {
	 ecran_message_pause_afficher( ecran ,"OK"  ) ; 
       }
     sleep(TEMPS_VOIR) ;

     voie_unique_inserer( voie_unique ,  t[3] , UNIQUE , EST_OUEST ); 

     voie_unique_wprint( ecran , voie_unique , 6 , 3 , &x ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     if( voie_unique_collision_verifier( voie_unique ) == -1 )
       {
	 ecran_message_pause_afficher( ecran ,"COLLISION"  ) ; 
       }
     else
       {
	 ecran_message_pause_afficher( ecran ,"Erreur : Collision non detectee"  ) ; 
       }
     sleep(TEMPS_VOIR) ;

     voie_unique_extraire( voie_unique ,  t[0] , OUEST  , OUEST_EST ); 
     voie_unique_extraire( voie_unique ,  t[1] , OUEST  , EST_OUEST ); 
     voie_unique_extraire( voie_unique ,  t[2] , UNIQUE , OUEST_EST ); 
     voie_unique_extraire( voie_unique ,  t[3] , UNIQUE , EST_OUEST ); 
     voie_unique_extraire( voie_unique ,  t[4] , EST    , OUEST_EST ); 
     voie_unique_extraire( voie_unique ,  t[5] , EST    , EST_OUEST ); 

     x=2 ;
     voie_unique_wprint( ecran , voie_unique , 6 , 3 , &x ) ;
     wrefresh( ecran_ligne_get(ecran) ) ;
     sprintf( mess , "Extraction de tous les trains , aff_fin = %d "  , x) ; 
     ecran_message_pause_afficher( ecran , mess ) ; 

     if( (cr = voie_unique_detruire( &voie_unique )))
     {
	  fprintf( stderr , "Erreur voie_unique_fermer\n");
	  exit(cr);
     }
     
     ecran_detruire(&ecran) ;

     printf(  "\n------ Fin %s ------\n\n" , tab_arg[0] );
     
     exit(0);
}
