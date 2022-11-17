/*
 * Trafic des trains sur une ligne avec 1 seule section a voie unique 
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <voie_unique_stdio.h>
#include <moniteur_voie_unique.h>

#define TAILLE_MARQUES 26
#define trafic_attente() sleep(1)

/* Variables partag�es */

moniteur_voie_unique_t * moniteur ; 


/* 
 *  Avancement d'un train sur une ligne dans l'un des 2 sens
 *  Fonction destinee a etre executee par un thread
 */


static void trafic_train_deplacer( train_t * train ) 
{

  /*----------*/

  /* 
   * Depart du train 
   */
  if( train->sens == OUEST_EST )
    {
	  
      /* 
       * Depart zone OUEST
       */
      moniteur_voie_unique_inserer( moniteur , train , OUEST );


      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 
      

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}

      /*
       * Voie_Unique zone Ouest 
       */
      trafic_attente();
	  
      /* 
       * Voie_Unique sens unique 
       */

      moniteur_voie_unique_entree_ouest(moniteur) ;

      moniteur_voie_unique_extraire( moniteur, train, OUEST  );	
      moniteur_voie_unique_inserer(  moniteur, train, UNIQUE );

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}


      trafic_attente(); 

      moniteur_voie_unique_extraire( moniteur, train, UNIQUE );	
      moniteur_voie_unique_inserer(  moniteur, train, EST    );

      moniteur_voie_unique_sortie_est(moniteur) ;

      /*
       * Voie_Unique zone EST 
       */

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}


      trafic_attente();
	  
      /* 
       * Arrivee zone EST
       */
      moniteur_voie_unique_extraire( moniteur, train, EST );	

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}

 
    }
  else
    {		/* Sens == EST_OUEST */
	  
      /* 
       * Depart 
       */
      moniteur_voie_unique_inserer( moniteur, train, EST );

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ;       

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}


      /*
       * Voie_Unique zone Est 
       */

      trafic_attente();
	  
      /* 
       * Voie_Unique sens unique 
       */
      moniteur_voie_unique_entree_est(moniteur) ;

      moniteur_voie_unique_extraire( moniteur, train, EST    );	
      moniteur_voie_unique_inserer(  moniteur, train, UNIQUE );

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}


      trafic_attente();
	  
      moniteur_voie_unique_extraire( moniteur, train, UNIQUE );	
      moniteur_voie_unique_inserer(  moniteur, train, OUEST  );

      moniteur_voie_unique_sortie_ouest(moniteur) ;

      /*
       * Voie_Unique zone Ouest 
       */

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ;       

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier(moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}


      trafic_attente();

      /* 
       * Arrivee
       */
      moniteur_voie_unique_extraire( moniteur, train, OUEST );	

      /* Affichage de la section a voie unique */
      voie_unique_print( moniteur->voie_unique ) ; 

      /* Verif collisions: arret de toutes les threads si collisions */
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(moniteur) ) == -1 )
	{
	  printf(" --- COLLISIONS --- \n" ) ; 
	  exit(-1) ; 
	}

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
  pthread_t tid_train[MAX_TRAINS] ; /* identite des threads train */
  train_t t[MAX_TRAINS] ;
  int nb_trains = 0 ;
  train_id_t max_trains ;
  
  int i ;

  static char tab_marques[TAILLE_MARQUES] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ;

  /*----------*/

  if( argc != 3 )
    {
      printf( "usage : %s <nb trains> <max trains>\n" , argv[0] );
      exit(-1);
    }

  /* --- Capture des parametres --- */

  if( strlen(argv[0]) < LG_MAX_NOMPROG )
    strcpy( nomprog , argv[0] ) ;
  else
    {
      fprintf( stderr, "Erreur : Nom de programme trop long\n[%s]\n",
	       argv[0] );
      return(-1);
    }

  /* -- nb trains */
  if( sscanf( argv[1] , "%d" , &nb_trains ) != 1 ) 
    {
      fprintf( stderr, "Erreur %s  : le nombre de trains est incorrect (%s)\n",
	       nomprog , argv[1] );
      return(-1);
    }

  if( nb_trains > MAX_TRAINS )
    {
      fprintf( stderr, "Erreur %s  : le nombre de trains %d depasse la limite autorisee (%d)\n",
	       nomprog , nb_trains , MAX_TRAINS );
      return(-1);
    }
 
  /* -- max de trains */
  if( sscanf( argv[2] , "%d" , &max_trains ) != 1 ) 
    {
      fprintf( stderr, "Erreur %s  : le maximum de trains est incorrect (%s)\n",
	       nomprog , argv[2] );
      return(-1);
    }
  
  if( max_trains > MAX_TRAINS )
    {
      fprintf( stderr, "Erreur %s  : le maximum de trains %d epasse la limite autorisee (%d)\n",
	       nomprog , max_trains , MAX_TRAINS );
      return(-1);
    }

  /* ------------------------------ */

  srandom(getpid());

#ifdef DEBUG
  printf("\n ----- Debut %s : Nb trains %d , Max trains %d -----\n" , 
	 nomprog,
	 nb_trains , 
	 max_trains );
#endif
  
  /* Creation de la section a voie unique */
  moniteur = moniteur_voie_unique_creer( max_trains ) ;
  
  /* mettre tous les trains en concurrence */
  //pthread_setconcurrency(nb_trains);

  /* Creation des threads train */
  for( i=0 ; i<nb_trains ; i++)
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
#ifdef DEBUG
      printf("Lancement du train ");
      train_print(&t[i]);
      printf("\n");
#endif

      pthread_create(&tid_train[i], NULL, (void *)trafic_train_deplacer, (void *)&t[i]);
    }

  /* Attente fin des threads */
  for(i=0 ; i<nb_trains ; i++ )
    pthread_join( tid_train[i] , NULL );

  /* Destruction de la section a voie unique */
  moniteur_voie_unique_detruire( &moniteur ) ; 

#ifdef DEBUG
  printf("\n ----- Fin %s  -----\n" , 
	 nomprog );
#endif

  exit(0);
}
