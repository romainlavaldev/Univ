#ifndef _LIGNE_H_
#define _LIGNE_H_

#include <moniteur_voie_unique.h>

typedef struct ligne_s
{
  moniteur_voie_unique_id_t nb ;					/* Nombre de voies uniques dans la ligne */
  moniteur_voie_unique_t * moniteurs[MAX_MONITEURS_VOIES_UNIQUES] ;	/* Voies uniques composants la ligne */
} ligne_t ;

#define LIGNE_NULL NULL 

/* 
 * Creation d'une ligne 
 */
extern ligne_t * ligne_creer() ;

/* 
 * Destruction d'une ligne 
 */
extern int ligne_detruire( ligne_t ** ligne ) ;

/* 
 * Initialisation d'une ligne 
 * La ligne doit etre creee avant son initailisation 
 */
extern int ligne_initialiser( ligne_t * ligne ) ;

/*
 * Ajout d'une voie en fin de ligne 
 * Stockage indirect: la ligne contient des references sur les voies 
 * La ligne et la voie doivent etre existantes 
 */
extern int ligne_moniteur_ajouter( ligne_t * ligne , 
				   moniteur_voie_unique_t * moniteur ) ;


/*
 * Fonction get/ser 
 */
extern moniteur_voie_unique_t * ligne_moniteur_get( ligne_t * const ligne , 
						    const moniteur_voie_unique_id_t i ) ; 

extern moniteur_voie_unique_id_t ligne_nb_get( ligne_t * const ligne ) ; 

#endif

