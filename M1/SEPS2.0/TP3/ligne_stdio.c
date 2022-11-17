#include <stdio.h>
#include <stdlib.h>

#include <ligne_stdio.h>

/* 
 * Affichage de la structure d'une ligne 
 */
extern void
ligne_mapper( const ligne_t * const ligne ) 
{
  int i = 0 ; 
  int nb_lignes = ligne->nb ; 

  printf("\nNombre de sections a voie unique: %d\n" , nb_lignes ) ; 
  for( i=0 ; i < nb_lignes ; i++ )
    {
      printf( "\n***** section %d *****\n" , i ) ; 
      voie_unique_mapper( moniteur_voie_unique_get(ligne->moniteurs[i]) ) ;
      printf( "\n") ; 
    }
}


/*
 * Affichage d'une ligne 
 */
extern void
ligne_print( const ligne_t * const ligne ) 
{
  int i ; 
  moniteur_voie_unique_id_t nb_sections = ligne->nb ; 

  /*----------*/

  printf("\n") ; 
  /* Affichage du sens Ouest --> Est de toutes les sections */
  for( i=0 ; i < nb_sections ; i++ ) 
    {
      voie_unique_ligne_1_print( moniteur_voie_unique_get(ligne->moniteurs[i]) ) ;
    }
  printf("\n") ; 

  /* Affichage des voies uniques de toutes les sections */
   for( i=0 ; i < nb_sections ; i++ ) 
    {
      voie_unique_ligne_2_print( moniteur_voie_unique_get(ligne->moniteurs[i]) ) ;
    }
  printf("\n") ; 

   /* Affichage du sens Est --> Ouest  de toutes les sections */
   for( i=0 ; i < nb_sections ; i++ ) 
    {
      voie_unique_ligne_3_print( moniteur_voie_unique_get(ligne->moniteurs[i]) ) ;
    }
  printf("\n") ; 

  /* Verif collisions pour toutes les sections */
   for( i=0 ; i < nb_sections ; i++ ) 
    {
      if( voie_unique_collision_verifier( moniteur_voie_unique_get(ligne->moniteurs[i]) ) == -1 )
	exit(-1) ;
    }
  
#ifdef DEBUG
     printf("\n\t--- OK ---\n\n");
#endif
}
