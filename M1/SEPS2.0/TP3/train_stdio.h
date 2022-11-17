#ifndef _TRAIN_STDIO_H_
#define _TRAIN_STDIO_H_

#include <sys/types.h>
#include <train.h>
#include <sens_stdio.h>


/*
 * Affichage train sur stdout 
 */

extern void train_marque_print( train_t * const t );
extern void train_marque_blanc_print();
extern void train_marque_vide_print();

extern void train_print( train_t * const t ) ;
extern void train_blanc_print( ) ;
extern void train_vide_print( ) ;

#endif
