#ifndef _LIGNE_NCURSES_H_
#define _LIGNE_NCURSES_H_

#include <voie_unique_ncurses.h>
#include <ligne.h>


/*
 * Affichage d'une ligne 
 */
extern void
ligne_wprint( ecran_t * const ecran ,			/* Ecran sur lequel on affiche                */
	      const ligne_t * const ligne ,		/* Section a voie unique a afficher           */
	      const train_id_t nb_total_trains ) ;	/* Nb total de trains circulant sur la ligne  */

#endif
