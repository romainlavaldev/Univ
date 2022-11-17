#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <train.h>

/*
 * Gestion train
 */

/* --- Sens --- */
extern
sens_t train_sens_get( train_t * const t )
{
     return( t->sens);
}
extern
void train_sens_set( train_t * t  , const sens_t s )
{
     t->sens = s;
}

/* --- Attribut Marque --- */
extern
marque_t train_marque_get( train_t * const t )
{
     return( t->marque);
}
extern
void train_marque_set( train_t * t  , const marque_t m )
{
     t->marque = m;
}

/* --- Objet Train entier --- */
extern 
void train_set( train_t * t ,
		const sens_t s ,
		const marque_t m )
{
     t->sens = s ;
     t->marque = m ;
}

extern 
int train_compare( train_t * t1 , train_t * t2 )
{
     /* On suppose qu'un train a une marque unique */
     return( t2->marque - t1->marque ) ;
}

extern 
boolean_t train_vide( train_t * const t )
{
     if( t->marque == '*' )
	  return( B_TRUE );
     else
	  return( B_FALSE );
}
