#ifndef _LISTE_H_
#define _LISTE_H_

#include <commun.h>
#include <elem.h>


/*
 * Definition des constantes
 */

#define LISTE_MAX 50

/* 
 * Definition des types 
 */


typedef struct liste_s 
{
  elem_id_t nb ;
  elem_t liste[LISTE_MAX] ;
} liste_t ;

typedef elem_id_t liste_id_t ;

/*
 * Definitions des fonctions 
 */

/* Fonctions de lectures */

extern 
elem_id_t 
liste_nb_lire( liste_t * const liste );

extern 
elem_t * 
liste_liste_lire( liste_t * const liste ) ;

extern 
elem_t 
liste_elem_lire( liste_t * const liste ,
		 const liste_id_t i ) ;


/* Fonctions d'affectations */

extern 
void
liste_nb_affecter( liste_t * liste ,
		   const elem_id_t nb );

extern 
void
liste_liste_affecter( liste_t * liste ,
		      elem_t * const l );

extern 
void
liste_elem_affecter( liste_t * liste ,
		     const liste_id_t i ,
		     const elem_t e );

/* Recherche sur le contenu d'une cellule d'un element dans la liste */

extern
booleen_t
liste_elem_rechercher( int * ind_recherche ,
		       liste_t * const liste,
		       const elem_t elem );


/* 
 * Suppression d'un element dans la liste 
 * Les autres elements sont decales 
 */

extern
int
liste_elem_supprimer( liste_t * liste ,
		      int ind_suppression ) ;

/* Ajout d'un coureur en fin de liste */

extern
int
liste_elem_ajouter( liste_t * liste,
		    const elem_t elem );

/* Affichage d'une liste */

extern
int
liste_afficher( liste_t * const liste );

/* Initialisation de la liste */

extern 
int 
liste_initialiser( liste_t * liste ) ;

/* 
 * Decanillage d'un cheval:
 */
extern 
int
liste_elem_decaniller( liste_t * liste ,
		       const elem_id_t ind_cheval ) ;

/*
 * Comparaison de 2 listes l1 et l2
 * Retour < 0 si l1 < l2  
 *        = 0 si l1 = l2
 *        > 0 si l1 > l2
 */
extern
int
liste_comparer( liste_t * const l1 , liste_t * const l2 ) ;

/* 
 * Affectation d'une liste : l1 <-- l2
 * l1 doit etre creee avant l'appel a cette fonction 
 */

extern 
void 
liste_affecter( liste_t * l1 , liste_t * const l2 ) ;

#endif
