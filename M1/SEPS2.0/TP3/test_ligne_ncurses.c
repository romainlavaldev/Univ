#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <tests.h>

#include <ligne_ncurses.h>


int 
main( int argc , char * argv[] )
{

  ligne_t * ligne = NULL ;
  int noerr = 0 ; 
  int i = 0 ; 

  ecran_t  * ecran = ECRAN_NULL ; 
  char mess[ECRAN_LG_MESS] ; 

  moniteur_voie_unique_t * tab_moniteur[MAX_MONITEURS_VOIES_UNIQUES] ;

  if( argc < 4 )
    {
      fprintf( stderr , "%s : test affichage d'une ligne avec ncurses\n" , argv[0] );
      fprintf( stderr , "usage : %s <Nb total trains>  <nb sections a voie unique> <Max trains voie 1> <Max trains voie 2>...\n" , argv[0] );
      exit(-1);
     }

  train_id_t Nb_Trains                = atoi(argv[1]) ; 
  moniteur_voie_unique_id_t Nb_Voies  = atoi(argv[2]) ; 

  if( Nb_Voies == 0 ) 
    {
      printf( "%s : trafic impossible sur ligne vide \n" , argv[0] ) ; 
      exit(1) ; 
    }

  if( argc != 3+Nb_Voies )
    {
      printf( "%s : Nombre de parametres incorrect pour %d sections a voie unique\n" , 
	      argv[0] , Nb_Voies ) ;
      printf(  "Format attendu : %s <Nb Total trains> %d" , argv[0] , Nb_Voies ) ;
      for( i=0 ; i<Nb_Voies ; i++ ) printf( "<Max trains voie %d> " , i+1 ) ; 
      printf("\n") ; 
      exit(1) ; 
    } 

  train_id_t * max_trains = malloc( sizeof(train_id_t) * Nb_Voies ) ;
  train_id_t som_max = 0 ; 

  for( i=0 ; i<Nb_Voies ; i++ ) 
    {
      max_trains[i] = atoi(argv[i+3]) ; 
      som_max += max_trains[i] ;
    }

  /*-----*/
 
  /* Creation voies uniques */
  for( i=0 ; i<Nb_Voies ; i++ ) 
    {
      tab_moniteur[i] = moniteur_voie_unique_creer(max_trains[i]) ; 
    }

  printf("\n----- Debut %s -----\n" , argv[0] );

  printf( "Initialisation ligne\n" ) ;
  if( ( ligne = ligne_creer() ) == NULL )
    {
      printf( "--> sortie erreur\n") ;
      exit(0) ; 
    }
  
 printf( "Ajout des voies en fin de ligne\n" ) ;
 for( i=0 ; i< Nb_Voies ; i++ ) 
   {
     if( ( noerr = ligne_moniteur_ajouter( ligne , 
					   tab_moniteur[i] ) ) )
       {
	 printf( "--> sortie erreur %d\n" , noerr) ;
	 exit(0) ; 
       }
   }

 /* Creation ecran */
 printf( "Creation ecran\n" ) ;
 ecran = ecran_creer() ; 
 wrefresh( ecran_ligne_get(ecran) ) ;
 wrefresh( ecran_messages_get(ecran) ) ;

 /* Test depassement de l'ecran */
 int L = ecran_largeur_get(ecran) ;
 if( ((Nb_Trains * (Nb_Voies*2) + som_max) * TAILLE_TRAIN_NCURSES) > (L-4) )
   {
     ecran_detruire(&ecran) ;

     printf( "%s : L'affichage de la ligne depasse la taille de l'ecran\n" ,
	     argv[0] ) ;
     printf( "\t- Largeur ecran = %d\n " , L-4 ) ;
     printf( "\t- taille affichage de la ligne = %d\n" , (Nb_Trains * (Nb_Voies*2) + som_max) * TAILLE_TRAIN_NCURSES ) ;
     printf( "\t\t- Nb trains = %d\n" , Nb_Trains  ) ;
     printf( "\t\t- Taille affichage d'un train = %d\n" ,  TAILLE_TRAIN_NCURSES ) ;
     printf( "\t\t- Nb Voies  = %d\n" , Nb_Voies ) ;
     printf( "\t\t- Somme des max trains = %d\n" , som_max ) ;
     for( i=0 ; i<Nb_Voies ; i++ ) printf( "\t\t\t- Max trains voie %d = %d\n" ,  i , max_trains[i] ) ;
     exit(1) ;      
   }

 /* Affichage de la ligne */
 ligne_wprint( ecran ,	
	       ligne ,	
	       Nb_Trains ) ;
 sprintf( mess , "Affichage ligne avec Nb trains = %d, Nb sections = %d" , Nb_Trains , Nb_Voies ) ; 
 ecran_message_pause_afficher( ecran , mess ) ;

 sleep(TEMPS_VOIR) ; 

 /* Destruction ecran */
 ecran_detruire(&ecran) ;

 /* Destruction de la ligne */
 printf( "Destruction de la ligne\n") ; 
 if( ( noerr = ligne_detruire( &ligne ) ) )
   {
     printf( "--> sortie erreur %d\n" , noerr) ;
     exit(0) ; 
   }
 
  printf(  "------ Fin %s -----\n\n" , argv[0] );
     
  exit(0);
}
