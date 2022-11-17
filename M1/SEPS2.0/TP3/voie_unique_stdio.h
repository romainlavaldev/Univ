#ifndef _VOIE_UNIQUE_STDIO_H_
#define _VOIE_UNIQUE_STDIO_H_

#include <voie_unique.h>
#include <train_stdio.h>


/* 
 * Definitions des fonctions d'affichage sur stdout 
 */

/* Affichage voie unique */
/* - 1iere ligne */
extern void voie_unique_ligne_1_print( voie_unique_t * const voie_unique );
/* - 2ieme ligne */
extern void voie_unique_ligne_2_print( voie_unique_t * const voie_unique ) ;
/* - 3ieme ligne */
extern void voie_unique_ligne_3_print( voie_unique_t * const  voie_unique ) ;
/* - global avec verif */
extern void voie_unique_print( voie_unique_t * const voie_unique ) ;


/* Affichage de la structure d'une voie unique */
extern void voie_unique_mapper( voie_unique_t * const voie_unique ) ;

#endif
