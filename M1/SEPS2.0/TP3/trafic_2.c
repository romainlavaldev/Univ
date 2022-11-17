/*
 * Trafic des trains sur une ligne avec plusieurs  sections a voie unique 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ligne_stdio.h>


#define TAILLE_MARQUES 26
#define trafic_attente() sleep(1)

/* Variables partag�es */

ligne_t * ligne = NULL ;
moniteur_voie_unique_t * tab_moniteurs_voies_uniques[MAX_MONITEURS_VOIES_UNIQUES] ; 
moniteur_voie_unique_id_t nb_sections ;


/* 
 *  Avancement d'un train sur une ligne dans l'un des 2 sens
 *  Fonction destinee a etre executee par un thread
 */


static void trafic_train_deplacer( train_t * train ) 
{
  moniteur_voie_unique_id_t i ; 

     /*----------*/
  
     /* 
      * Depart du train 
      */
     if( train->sens == OUEST_EST )
     {
	  
	  /* 
	   * Depart zone OUEST
	   */

       for( i=0 ; i<nb_sections ; i++ ) 
	 {
	   moniteur_voie_unique_inserer( ligne_moniteur_get(ligne,i) , train, OUEST );
	   ligne_print(ligne) ;	  

	  /*
	   * Ligne zone Ouest 
	   */
	  trafic_attente();
	  
	  /* 
	   * Ligne sens unique 
	   */

	  moniteur_voie_unique_entree_ouest(ligne_moniteur_get(ligne,i)) ;

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, OUEST   );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, UNIQUE  );

	  ligne_print(ligne) ;
	  trafic_attente(); 

	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, UNIQUE );	
	  moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, EST    );

	  moniteur_voie_unique_sortie_est(ligne_moniteur_get(ligne,i)) ;

	  /*
	   * Ligne zone EST 
	   */
	  ligne_print(ligne) ;
	  trafic_attente();
	  
	  /* 
	   * Arrivee zone EST
	   */
	  moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, EST );	
	  ligne_print(ligne) ;
	 }
 
     }
     else
       {		/* Sens == EST_OUEST */
	  
	 /* 
	  * Depart zone EST
	  */
	 for( i=nb_sections-1 ; i>=0  ; i-- ) 
	   {
	     moniteur_voie_unique_inserer( ligne_moniteur_get(ligne,i), train, EST );
	     ligne_print(ligne) ;

	     /*
	      * Ligne zone Est 
	      */

	     trafic_attente();
	  
	     /* 
	      * Ligne sens unique 
	      */
	     moniteur_voie_unique_entree_est(ligne_moniteur_get(ligne,i)) ;

	     moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, EST    );	
	     moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, UNIQUE );

	     ligne_print(ligne) ;
	     trafic_attente();

	     moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, UNIQUE );	
	     moniteur_voie_unique_inserer(  ligne_moniteur_get(ligne,i), train, OUEST  );

	     moniteur_voie_unique_sortie_ouest(ligne_moniteur_get(ligne,i)) ;

	     /*
	      * Ligne zone Ouest 
	      */
	  
	     ligne_print(ligne) ;
	     trafic_attente();

	     /* 
	      * Arrivee
	      */
	     moniteur_voie_unique_extraire( ligne_moniteur_get(ligne,i), train, OUEST );	
	     ligne_print(ligne) ;
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
  int noerr = 0 ; 

  pthread_t tid_train[MAX_TRAINS] ; /* identite des threads train */
  train_t t[MAX_TRAINS] ;
  int nb_trains = 0 ;
  train_id_t tab_max_trains[MAX_TRAINS] ;

  
  int i ;

  static char tab_marques[TAILLE_MARQUES] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ;

  /*----------*/

  if( argc < 3 )
  {
       printf( "usage : %s <nb total trains> <nb sections a voie unique> <max train section 1> <max train section 2>...\n" , argv[0] );
       exit(-1);
  }

  /* --- Capture des parametres --- */
  if( strlen(argv[0]) < LG_MAX_NOMPROG )
    strcpy( nomprog , argv[0] ) ;
  else
    {
       fprintf( stderr, "Erreur : nom de programme trop long\n[%s]\n",
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

  /* -- nb sections */
  if( sscanf( argv[2] , "%d" , &nb_sections ) != 1 ) 
    {
      fprintf( stderr, "Erreur %s  : le nombre de sections est incorrect (%s)\n",
	       nomprog , argv[2] );
      return(-1);
    }

  if( argc != nb_sections + 3 )
    {
      fprintf( stderr, "Erreur %s  : nombre de parametres incorrect. Pour %d sections l'invocation de la commande devrait etre\n",
	       nomprog , nb_sections );
      fprintf( stderr , "%s <nb trains=%d> <nb sections=%d> " , nomprog , nb_trains , nb_sections ) ; 
      for( i=0 ; i<nb_sections ; i++ ) fprintf( stderr , "<max section %d> " , i+1 ) ; 
      fprintf( stderr , "\n" ) ;
      fprintf( stderr , "au lieu de \n%s " , nomprog ) ; 
      for( i=1 ; i<argc ; i++ ) fprintf( stderr , "<%s> " , argv[i] ) ; 
      fprintf( stderr , "\n" ) ;
      return(-1);
    }
  
  /* -- les max de trains pour chaque section */
  for( i=0 ; i<nb_sections ; i++ )
    {
      if( sscanf( argv[3+i] , "%d" , &tab_max_trains[i] ) != 1 ) 
	{
	  fprintf( stderr, "Erreur %s  : le max de trains pour la section %d est incorrect (%s)\n",
		   nomprog , i+1 , argv[3+i] );
	  return(-1);
	}

      if( tab_max_trains[i] > MAX_TRAINS )
	{
	  fprintf( stderr, "Erreur %s  : le maximum de trains %d de la section %d depasse la limite autorisee (%d)\n",
		   nomprog , tab_max_trains[i] , i+1 , MAX_TRAINS );
	  return(-1);
	}
    }

  /* ------------------------------ */

  srandom(getpid());

#ifdef DEBUG
  printf("\n ----- Debut %s : Nb trains %d , Nb section %d max={" , 
	 nomprog,
	 nb_trains , 
	 nb_sections );
  for( i=0 ; i<nb_sections ; i++ ) printf( " %d", tab_max_trains[i] ) ; 
  printf( " } -----\n" ) ; 
#endif
  
  /* Creation de la ligne avec les sections a voie unique */
  if( ( ligne = ligne_creer() ) == NULL ) 
    {
      fprintf( stderr , "%s : erreur lors de la creation de la ligne\n" , nomprog ) ; 
      exit(1) ; 
    }

  for( i=0 ; i<nb_sections ; i++ ) 
    {
      tab_moniteurs_voies_uniques[i] = moniteur_voie_unique_creer( tab_max_trains[i] ) ;
      if( ( noerr = ligne_moniteur_ajouter( ligne , tab_moniteurs_voies_uniques[i] ) ) )
	exit(noerr) ; 
    }
  
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

  /* Destruction de la ligne */
  if( ( noerr = ligne_detruire( &ligne ) ) ) 
    {
      fprintf( stderr , "%s : erreur lors de la destruction de la ligne\n" , nomprog ) ; 
      exit(noerr) ; 
    }


#ifdef DEBUG
     printf("\n ----- Fin %s  -----\n" , 
	    nomprog );
#endif

  exit(0);
}
