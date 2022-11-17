#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <sens.h>
#include <train.h>
#include <moniteur_voie_unique.h>

/*---------- MONITEUR ----------*/

extern moniteur_voie_unique_t * moniteur_voie_unique_creer( const train_id_t nb )
{
  moniteur_voie_unique_t * moniteur = NULL ; 

  /* Creation structure moniteur */
  if( ( moniteur = malloc( sizeof(moniteur_voie_unique_t) ) ) == NULL  )
    {
      fprintf( stderr , "moniteur_voie_unique_creer: debordement memoire (%lu octets demandes)\n" , 
	       sizeof(moniteur_voie_unique_t) ) ;
      return(NULL) ; 
    }

  /* Creation de la voie */
  if( ( moniteur->voie_unique = voie_unique_creer() ) == NULL )
    return(NULL) ; 
  
  /* Initialisations du moniteur */

  /***********/
  /* A FAIRE */
  /***********/
  pthread_cond_t cond_init = PTHREAD_COND_INITIALIZER;
  moniteur->cond_est = cond_init;
  moniteur->cond_ouest = cond_init;

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  moniteur->mutex_monitor = mutex;

  moniteur->cpt_est = 0;
  moniteur->cpt_ouest = 0;

  moniteur->nb_max = nb;

  moniteur->cpt_waiting_est = 0;
  moniteur->cpt_waiting_ouest = 0;

  return(moniteur) ; 
}

extern int moniteur_voie_unique_detruire( moniteur_voie_unique_t ** moniteur )
{
  int noerr ; 

  /* Destructions des attribiuts du moniteur */

  /***********/
  /* A FAIRE */
  /***********/
  pthread_cond_destroy(&((*moniteur)->cond_est));
  pthread_cond_destroy(&((*moniteur)->cond_ouest));
  pthread_mutex_destroy(&((*moniteur)->mutex_monitor));

  /* Destruction de la voie */
  if( ( noerr = voie_unique_detruire( &((*moniteur)->voie_unique) ) ) )
    return(noerr) ;

  /* Destruction de la strcuture du moniteur */
  free( (*moniteur) );

  (*moniteur) = NULL ; 

  return(0) ; 
}

extern void moniteur_voie_unique_entree_ouest( moniteur_voie_unique_t * moniteur ) 
{
  /***********/
  /* A FAIRE */
  /***********/
  pthread_mutex_lock(&(moniteur->mutex_monitor));

  while(moniteur->cpt_ouest >= moniteur->nb_max || moniteur->cpt_est > 0){
    moniteur->cpt_waiting_ouest += 1;
    pthread_cond_wait(&(moniteur->cond_ouest), &(moniteur->mutex_monitor));
    pthread_cond_signal(&(moniteur->cond_ouest));
    moniteur->cpt_waiting_ouest -= 1;
  }
  
  moniteur->cpt_ouest += 1;

  pthread_mutex_unlock(&(moniteur->mutex_monitor));
}

extern void moniteur_voie_unique_sortie_est( moniteur_voie_unique_t * moniteur ) 
{
  /***********/
  /* A FAIRE */
  /***********/
  pthread_mutex_lock(&(moniteur->mutex_monitor));

  if(moniteur->cpt_ouest == 1){
    //pthread_cond_broadcast(&(moniteur->cond_est));

    if(moniteur->cpt_waiting_est > 0){
      pthread_cond_signal(&(moniteur->cond_est));
    }else{
      pthread_cond_signal(&(moniteur->cond_ouest));
    }

  }else{
    pthread_cond_signal(&(moniteur->cond_ouest));
  }

  moniteur->cpt_ouest -= 1;

  pthread_mutex_unlock(&(moniteur->mutex_monitor));
}

extern void moniteur_voie_unique_entree_est( moniteur_voie_unique_t * moniteur ) 
{
  /***********/
  /* A FAIRE */
  /***********/
  pthread_mutex_lock(&(moniteur->mutex_monitor));

  while(moniteur->cpt_est >= moniteur->nb_max || moniteur->cpt_ouest > 0){
    moniteur->cpt_waiting_est += 1;
    pthread_cond_wait(&(moniteur->cond_est), &(moniteur->mutex_monitor));
    pthread_cond_signal(&(moniteur->cond_est));
    moniteur->cpt_waiting_est -= 1;
  }
  
  moniteur->cpt_est += 1;

  pthread_mutex_unlock(&(moniteur->mutex_monitor));
}

extern void moniteur_voie_unique_sortie_ouest( moniteur_voie_unique_t * moniteur ) 
{
  /***********/
  /* A FAIRE */
  /***********/
   pthread_mutex_lock(&(moniteur->mutex_monitor));

  if(moniteur->cpt_est == 1){
    //pthread_cond_broadcast(&(moniteur->cond_est));

    if(moniteur->cpt_waiting_ouest > 0){
      pthread_cond_signal(&(moniteur->cond_ouest));
    }else{
      pthread_cond_signal(&(moniteur->cond_est));
    }

  }else{
    pthread_cond_signal(&(moniteur->cond_est));
  }

  moniteur->cpt_est -= 1;

  pthread_mutex_unlock(&(moniteur->mutex_monitor));
}

/*
 * Fonctions set/get 
 */

extern 
voie_unique_t * moniteur_voie_unique_get( moniteur_voie_unique_t * const moniteur )
{
  return( moniteur->voie_unique ) ; 
}


extern 
train_id_t moniteur_max_trains_get( moniteur_voie_unique_t * const moniteur )
{
  /***********/
  /* A FAIRE */
  /***********/
  return( 1 ) ; /* valeur arbitraire ici */
}

/*
 * Fonction de deplacement d'un train 
 */

extern
int moniteur_voie_unique_extraire( moniteur_voie_unique_t * moniteur , train_t * train , zone_t zone  ) 
{
  return( voie_unique_extraire( moniteur->voie_unique, 
				(*train), 
				zone , 
				train_sens_get(train) ) ) ; 
}

extern
int moniteur_voie_unique_inserer( moniteur_voie_unique_t * moniteur , train_t * train , zone_t zone ) 
{ 
  return( voie_unique_inserer( moniteur->voie_unique, 
			       (*train), 
			       zone, 
			       train_sens_get(train) ) ) ;
}
