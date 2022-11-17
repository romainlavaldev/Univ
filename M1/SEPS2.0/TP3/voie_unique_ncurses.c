#include <stdio.h>
#include <stdlib.h>

#include <voie_unique_ncurses.h>

/* 
 * Affichage voie unique sur ncurses
 *-----------------------------------
 */
extern 
void voie_unique_wprint( ecran_t * const ecran ,		/* Ecran sur lequel on affiche                */
			 voie_unique_t * const voie_unique ,	/* Section a voie unique a afficher           */
			 const train_id_t nb_total_trains ,	/* Nb total de trains circulant sur la ligne  */
			 const train_id_t nb_max_trains ,	/* Max trains sur la voie unique              */
			 int * x_debut )			/* Numero de la colonne de depart/fin d'affichage */
{
  int i ;
  int x ; 

  /*--------------------*/
  
  /* 
   * Affichage zone Ouest Sens A vers B
   */
 
  for(i=0 , x=(*x_debut) ; i<voie_unique->cpt[ZONE_ID_OUEST_OE] ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {
      train_wprint( ecran , 2 , x , &(voie_unique->zone[ZONE_ID_OUEST_OE][i]) );
    }
  for(i=voie_unique->cpt[ZONE_ID_OUEST_OE] ; i<nb_total_trains ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {	  
      train_vide_wprint( ecran , 2 , x );
    }

  /* 
   * Affichage du sens unique 
   */

  for(i=0 ; i<voie_unique->cpt[ZONE_ID_UNIQUE] ; i++ ,  x=x+TAILLE_TRAIN_NCURSES )
    {
      train_wprint( ecran , 3 , x , &(voie_unique->zone[ZONE_ID_UNIQUE][i]) );
    }
   for( i=voie_unique->cpt[ZONE_ID_UNIQUE] ; i<nb_max_trains ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {	  
      train_vide_wprint( ecran , 3 , x );
    }

   const int x_debut_Est = x ; 
   
   /* 
    * Affichage zone Est Sens A vers B 
    */
   
   for(i=0 ; i<voie_unique->cpt[ZONE_ID_EST_OE] ; i++ , x=x+TAILLE_TRAIN_NCURSES )
     {
       train_wprint( ecran , 2 , x , &(voie_unique->zone[ZONE_ID_EST_OE][i]) );
     }
   for(i=voie_unique->cpt[ZONE_ID_EST_OE] ; i<nb_total_trains ; i++ ,  x=x+TAILLE_TRAIN_NCURSES )
     {	  
       train_vide_wprint( ecran , 2 , x );
     }     

   /* 
   * Affichage zone Ouest Sens B vers A
   */
 
   for(i=0 , x=(*x_debut) ; i<voie_unique->cpt[ZONE_ID_OUEST_EO] ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {
      train_wprint( ecran , 4 , x , &(voie_unique->zone[ZONE_ID_OUEST_EO][i]) );
    }
  for(i=voie_unique->cpt[ZONE_ID_OUEST_EO] ; i<nb_total_trains ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {	  
      train_vide_wprint( ecran , 4 , x );
    }

  /* 
   * Affichage zone Est Sens B vers A 
   */
  
  for(i=0 , x=x_debut_Est ; i<voie_unique->cpt[ZONE_ID_EST_EO] ; i++ , x=x+TAILLE_TRAIN_NCURSES )
    {
      train_wprint( ecran , 4 , x , &(voie_unique->zone[ZONE_ID_EST_EO][i]) );
    }
  for(i=voie_unique->cpt[ZONE_ID_EST_EO] ; i<nb_total_trains ; i++ ,  x=x+TAILLE_TRAIN_NCURSES )
    {	  
      train_vide_wprint( ecran , 4 , x );
    } 

  (*x_debut) = x ; 
}



