#include <stdio.h>
#include <stdlib.h>

#include <ligne_ncurses.h>

/*
 * Affichage d'une ligne 
 */
extern void
ligne_wprint( ecran_t * const ecran ,			/* Ecran sur lequel on affiche                */
	      const ligne_t * const ligne ,		/* Section a voie unique a afficher           */
	      const train_id_t nb_total_trains )	/* Nb total de trains circulant sur la ligne  */

{
  int i ; 
  moniteur_voie_unique_id_t nb_sections = ligne->nb ; 
  int x_debut = 0 ; 

  /*----------*/
 
  x_debut = 2 ; 
  for( i=0 ; i < nb_sections ; i++ ) 
    {
      voie_unique_wprint( ecran , 
			  moniteur_voie_unique_get(ligne->moniteurs[i]) ,	
			  nb_total_trains ,
			  moniteur_max_trains_get(ligne->moniteurs[i]),
			  &x_debut ) ;
    }

  /* Rafraichissement ecran */
  wrefresh( ecran_ligne_get(ecran) ) ;
 
}
