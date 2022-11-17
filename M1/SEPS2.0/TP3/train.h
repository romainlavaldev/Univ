#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <sys/types.h>
#include <sens.h>
#include <commun.h>

#define MAX_TRAINS 100

#define TRAIN_VIDE (train_t){OUEST_EST , '*'} 

typedef char marque_t  ;
typedef int train_id_t ;

/*
 * Structure parametres fonction train 
 */

typedef struct train_s
{
     sens_t sens ;
     marque_t marque ;
} train_t ;

extern sens_t train_sens_get( train_t * const t ) ;
extern void train_sens_set( train_t * t  , const sens_t s ) ;

extern marque_t train_marque_get( train_t * const t );
extern void train_marque_set( train_t * t  , const marque_t m ) ;

extern void train_set( train_t * t ,
		       const sens_t s ,
		       const marque_t m ) ;

extern int train_compare( train_t * t1 , train_t * t2 );

extern boolean_t train_vide( train_t * const t ) ;
#endif
