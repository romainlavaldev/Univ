#ifndef _VOIE_UNIQUE_NCURSES_H_
#define _VOIE_UNIQUE_NCURSES_H_

#include <voie_unique.h>
#include <train_ncurses.h>


/* 
 * Definitions des fonctions d'affichage sur ecran ncurses
 */

/* Affichage voie unique */
extern 
void voie_unique_wprint( ecran_t * const ecran ,		/* Ecran sur lequel on affiche                */
			 voie_unique_t * const voie_unique ,	/* Section a voie unique a afficher           */
			 const train_id_t nb_total_trains ,	/* Nb total de trains circulant sur la ligne  */
			 const train_id_t nb_max_trains ,	/* Max trains sur la voie unique              */
			 int * x_debut ) ;			/* Numero de la colonne de depart/fin  d'affichage */


#endif
