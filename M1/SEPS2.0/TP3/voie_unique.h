#ifndef _VOIE_UNIQUE_H_
#define _VOIE_UNIQUE_H_

#include <train.h>

/* 
 * Definitions des structures
 */

typedef enum zone_s { OUEST=0 , UNIQUE=2, EST=3 } zone_t ;
typedef enum zone_id_s { ZONE_ID_OUEST_OE=0, ZONE_ID_OUEST_EO=1, ZONE_ID_UNIQUE=2, ZONE_ID_EST_OE=3, ZONE_ID_EST_EO=4 } zone_id_t ; 

typedef struct voie_unique_s
{
  train_id_t cpt[5] ;		/* Nombre de trains dans chaque sections */
  train_t zone[5][MAX_TRAINS] ; /* Trains dans chaque section */
} voie_unique_t ;

/* 
 * Definitions des fonctions 
 */

/* Creation structure voie unique */
extern voie_unique_t * voie_unique_creer() ; 
/* Destruction structure voie unique */
extern int voie_unique_detruire( voie_unique_t ** voie_unique ) ; 

/*
 * - Verif collisions 
 *   retour : -1 si collisions
 *             0 sinon 
 */
extern int voie_unique_collision_verifier( voie_unique_t * const voie_unique ) ; 

/* Insertion d'un train dans une zone d'une voie unique */
extern int voie_unique_inserer( voie_unique_t * voie ,	/* voie unique */      
				const train_t tn ,	/* train a inserer */
				const zone_t z ,	/* zone de la voie unique dans laquelle on insere le train */
				const sens_t s );	/* sens du train */   

extern int voie_unique_extraire( voie_unique_t * voie ,	/* voie unique */           
				 const train_t tn ,	/* train a extraire */   
				 const zone_t z,	/* zone de la voie unique depuis laquelle on extrait le train */             
				 const sens_t s ) ;	/* sens du train */             

#endif
