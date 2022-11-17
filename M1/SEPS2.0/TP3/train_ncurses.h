#ifndef _TRAIN_NCURSES_H_
#define _TRAIN_NCURSES_H_

#include <sys/types.h>
#include <train.h>
#include <sens_ncurses.h>

#define TAILLE_TRAIN_NCURSES 3
/*
 * Affichage train sur ecran gere par ncurses
 */

extern void train_marque_wprint( ecran_t * const ecran , const int y , const int x , train_t * const t );
extern void train_marque_blanc_wprint( ecran_t * const ecran , const int y , const int x );
extern void train_marque_vide_wprint( ecran_t * const ecran , const int y , const int x );

extern void train_wprint( ecran_t * const ecran , const int y , const int x , train_t * const t ) ;
extern void train_blanc_wprint( ecran_t * const ecran , const int y , const int x ) ;
extern void train_vide_wprint( ecran_t * const ecran , const int y , const int x
 ) ;

#endif
