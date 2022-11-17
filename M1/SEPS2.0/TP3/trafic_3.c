/*
 * Trafic des trains sur une ligne avec plusieurs sections a voie unique 
 * L'affichage du trafic se fait sur un ecran "ncurses"
 * --> ecran : ressource critique supplementaire
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ligne_ncurses.h>
#include <sens_string.h>

#define TAILLE_MARQUES 26
#define trafic_attente() sleep(random()%1+1)


/* Variables partag�es */

ecran_t * ecran = ECRAN_NULL ;
ligne_t * ligne = LIGNE_NULL ; 
train_id_t Nb_Trains = 0 ; /* [Parametre] : Nombre de trains circulants sur la ligne */

/* 
 *  Avancement d'un train sur une ligne dans l'un des 2 sens
 *  Fonction destinee a etre executee par un thread
 */

static void trafic_train_deplacer( train_t * train ) 
{
  moniteur_voie_unique_id_t i ; 
  moniteur_voie_unique_id_t nb_voies = ligne_nb_get(ligne) ;
  char mess[ECRAN_LG_MESS] ;

  /*----------*/

  /* 
   * Depart du train 
   */
  
  if( train->sens == OUEST_EST )
    {

      sprintf( mess , "Depart Ouest train %c%s"  , train_marque_get(train) , sens_string(train_sens_get(train)) ) ;
      ecran_message_afficher( ecran , mess );

      /* 
       * Depart zone OUEST
       */
      
      for( i=0 ; i<nb_voies ; i++ ) 
	{
	  moniteur_voie_unique_inserer( ligne_moniteur_get(ligne,i) , train, OUEST );

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  /*
	   * Ligne zone Ouest 
	   */

	  trafic_attente(); /* temps trajet zone Ouest */
	  
	  /* 
	   * Ligne voie unique 
	   */

	  moniteur_voie_unique_entree_ouest(ligne_moniteur_get(ligne,i)) ;

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, OUEST   );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, UNIQUE  );

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  trafic_attente(); /* temps trajet voie unique */

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, UNIQUE );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, EST    );

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  moniteur_voie_unique_sortie_est(ligne_moniteur_get(ligne,i)) ;

	  /*
	   * Ligne zone EST 
	   */

	  trafic_attente(); /* temps trajet zone Est */
	  
	  /* 
	   * Arrivee zone EST
	   */

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, EST );	

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;
	}

      sprintf( mess , "Arrivee Est train %c%s"  , train_marque_get(train) , sens_string(train_sens_get(train)) ) ;
      ecran_message_droite_afficher( ecran , mess );

    }
  else
    {		/* Sens == EST_OUEST */

      sprintf( mess , "Depart Est train %c%s"  , train_marque_get(train) , sens_string(train_sens_get(train)) ) ;
      ecran_message_droite_afficher( ecran , mess );

      /* 
       * Depart zone EST
       */
      for( i=nb_voies-1 ; i>=0  ; i-- ) 
	{
	  moniteur_voie_unique_inserer( ligne_moniteur_get(ligne,i), train, EST );

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  /*
	   * Ligne zone Est 
	   */

	  trafic_attente(); /* temps trajet zone Est */
	  
	  /* 
	   * Ligne sens unique 
	   */
	  moniteur_voie_unique_entree_est(ligne_moniteur_get(ligne,i)) ;

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, EST    );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, UNIQUE );

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  trafic_attente(); /* temps trajet voie unique */

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, UNIQUE );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, OUEST  );

	  moniteur_voie_unique_sortie_ouest(ligne_moniteur_get(ligne,i)) ;

	  /*
	   * Ligne zone Ouest 
	   */
	  
	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  trafic_attente(); /* temps trajet zone Ouest */

	  /* 
	   * Arrivee
	   */
	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, OUEST );	
	}

	  ligne_wprint(ecran , ligne , Nb_Trains ) ;

	  sprintf( mess , "Arrivee Ouest train %c%s"  , train_marque_get(train) , sens_string(train_sens_get(train)) ) ;
      ecran_message_afficher( ecran , mess );

    }

  pthread_exit(NULL);
}

/* 
 * Thread principale
 */


int
main(  int argc , char * argv[] )
{
  char nomprog[LG_MAX_NOMPROG] ;
  int noerr = 0 ; 

  /* Variables trains */
  pthread_t tid_train[MAX_TRAINS] ; /* identite des threads train */
  train_t t[MAX_TRAINS] ; /* instances des trains */
  train_id_t Max_Trains[MAX_TRAINS] ; /* [Parametres] : Maximums de trains pour chaque voie unique */
  train_id_t som_max = 0 ; /* Somme des maximums des trains */
  static char tab_marques[TAILLE_MARQUES] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ;

  /* Variables moniteurs */
  moniteur_voie_unique_t * tab_moniteur[MAX_MONITEURS_VOIES_UNIQUES] ; /* Instances des moniteurs */
  moniteur_voie_unique_id_t Nb_Voies = 0 ; /* [Parametes] : Nombre de voie uniques = nb moniteurs */

  /* Variables de travail */
  int i = 0 ; 

  /* ----- */
  if( strlen(argv[0]) < LG_MAX_NOMPROG )
    strcpy( nomprog , argv[0] ) ; 
  else
    {
      fprintf( stderr , "Erreur : nom de programme trop long\n[%s]\n" , argv[0] );
      exit(-1);
    }

  if( argc < 4 )
    {
      fprintf( stderr , "%s : test affichage d'une ligne avec ncurses\n" , nomprog );
      fprintf( stderr , "usage : %s <Nb total trains>  <nb sections a voie unique> <Max trains voie 1> <Max trains voie 2>...\n" , nomprog );
      exit(-1);
    }

  Nb_Trains = atoi(argv[1]) ; 
  Nb_Voies  = atoi(argv[2]) ; 

  if( Nb_Voies == 0 ) 
    {
      printf( "%s : trafic impossible sur ligne vide \n" , nomprog ) ; 
      exit(1) ; 
    }

  if( argc != 3+Nb_Voies )
    {
      printf( "%s : Nombre de parametres incorrect pour %d sections a voie unique\n" , 
	      nomprog , Nb_Voies ) ;
      printf(  "Format attendu : %s <Nb Total trains> %d" , nomprog , Nb_Voies ) ;
      for( i=0 ; i<Nb_Voies ; i++ ) printf( "<Max trains voie %d> " , i+1 ) ; 
      printf("\n") ; 
      exit(1) ; 
    } 

  for( i=0 ; i<Nb_Voies ; i++ ) 
    {
      Max_Trains[i] = atoi(argv[i+3]) ; 
      som_max += Max_Trains[i] ;
    }

  /*-----*/

  /* Creation voies uniques */
  for( i=0 ; i<Nb_Voies ; i++ ) 
    {
      tab_moniteur[i] = moniteur_voie_unique_creer(Max_Trains[i]) ; 
    }

#ifdef _DEBUG_
  printf("\n ----- Debut %s : Nb trains %d , Nb sections %d max={" , 
	 nomprog,
	 Nb_Trains , 
	 Nb_Voies );
  for( i=0 ; i<Nb_Voies ; i++ ) printf( " %d", Max_Trains[i] ) ; 
  printf( " } -----\n" ) ; 
#endif


#ifdef _DEBUG_
  printf( "Creation ligne\n" ) ;
#endif
  if( ( ligne = ligne_creer() ) == NULL )
    {
      printf( "%s --> sortie erreur\n" , nomprog ) ;
      exit(1) ; 
    }

#ifdef _DEBUG_  
  printf( "Ajout des voies en fin de ligne\n" ) ;
#endif
  for( i=0 ; i< Nb_Voies ; i++ ) 
    {
      if( ( noerr = ligne_moniteur_ajouter( ligne , 
					    tab_moniteur[i] ) ) )
	{
	  printf( "%s --> sortie erreur %d , moniteur %d \n" , nomprog , noerr , i ) ;
	  exit(noerr) ; 
	}
    }
  
  /* Creation ecran */
#ifdef _DEBUG_
  printf( "Creation ecran\n" ) ;
#endif
  ecran = ecran_creer() ; 
  wrefresh( ecran_ligne_get(ecran) ) ;
  wrefresh( ecran_messages_get(ecran) ) ;

  /* Test depassement de l'ecran */
  int L = ecran_largeur_get(ecran) ;
  if( ((Nb_Trains * (Nb_Voies*2) + som_max) * TAILLE_TRAIN_NCURSES) > (L-4) )
    {
      ecran_detruire(&ecran) ;

      printf( "%s : L'affichage de la ligne depasse la taille de l'ecran\n" ,
	      nomprog ) ;
      printf( "\t- Largeur ecran = %d\n " , L-4 ) ;
      printf( "\t- taille affichage de la ligne = %d\n" , (Nb_Trains * (Nb_Voies*2) + som_max) * TAILLE_TRAIN_NCURSES ) ;
      printf( "\t\t- Nb trains = %d\n" , Nb_Trains  ) ;
      printf( "\t\t- Taille affichage d'un train = %d\n" ,  TAILLE_TRAIN_NCURSES ) ;
      printf( "\t\t- Nb Voies  = %d\n" , Nb_Voies ) ;
      printf( "\t\t- Somme des max trains = %d\n" , som_max ) ;
      for( i=0 ; i<Nb_Voies ; i++ ) printf( "\t\t\t- Max trains voie %d = %d\n" ,  i , Max_Trains[i] ) ;
      exit(1) ;      
    }

  /* Affichage ligne vide */
  ligne_wprint( ecran ,
		ligne ,	
		Nb_Trains ) ;
  sleep(1) ; 

  /* Creation des trains */
  srandom(getpid()) ; 
  for( i=0 ; i<Nb_Trains ; i++)
    {
      if( random()%2 )
	{
	  train_sens_set( &t[i]  , OUEST_EST );
	}
      else
	{
	  train_sens_set( &t[i]  , EST_OUEST );
	}       
      train_marque_set( &t[i]  , tab_marques[i%TAILLE_MARQUES] ) ;
    }

  /* Lancement des threads/trains */
  //pthread_setconcurrency(Nb_Trains);
  for(i=0 ; i<Nb_Trains ; i++ )
    pthread_create(&tid_train[i], NULL, (void *)trafic_train_deplacer, (void *)&t[i]);

  /* Attente fin des threads */
  for(i=0 ; i<Nb_Trains ; i++ )
      pthread_join( tid_train[i] , NULL );

  sleep(1) ; 

  /* Destruction ecran */
  ecran_detruire(&ecran) ;

  /* Destruction ligne */
#ifdef _DEBUG_
  printf( "Destruction de la ligne\n") ; 
#endif 
  if( ( noerr = ligne_detruire( &ligne ) ) )
    {
      printf( "--> sortie erreur %d\n" , noerr) ;
      exit(noerr) ; 
    }
  

#ifdef _DEBUG_
  printf(  "------ Fin %s -----\n\n" , nomprog );
#endif
     
  exit(0);
}
