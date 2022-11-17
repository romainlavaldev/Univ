#ifndef _SENS_NCURSES_H_
#define _SENS_NCURSES_H_

/* Types */

#include <sens.h>
#include <ecran.h>

/* Fonctions */

extern void sens_wprint( ecran_t * const ecran , const int y , const int x , const sens_t s ) ;
extern void sens_blanc_wprint( ecran_t * const ecran , const int y , const int x ) ;
extern void sens_vide_wprint( ecran_t * const ecran , const int y , const int x ) ;

#endif
