#ifndef _PISTE_H_
#define _PISTE_H_

#define PISTE_LONGUEUR 20

#include <stdlib.h>

#include <cell.h>

/* Definition des types de base */

typedef unsigned int piste_lg_t ;
typedef struct piste_s
{
  cell_t cell[PISTE_LONGUEUR];
} piste_t ;

typedef unsigned int piste_id_t ;

/*
 * Definition des fonctions 
 */

/* Affectation d'une case de la piste */
extern void 
piste_cell_affecter( piste_t * piste ,
		     const piste_id_t indice,
		     const cell_t cell );

/* Lecture d'une case de la piste */
extern int
piste_cell_lire( piste_t * piste ,
		 const piste_id_t indice,
		 cell_t * cell ) ;

/*
 * Test d'une case libre
 * Retour VRAI si libre
 *        FAUX sinon
 */

extern booleen_t 
piste_cell_libre( piste_t * piste ,
		  const piste_id_t indice);

/*
 * Test d'une case occupee
 * Retour VRAI si occupee
 *        FAUX sinon
 */

extern booleen_t
piste_cell_occupee( piste_t * piste ,
		    const piste_id_t indice);

/*
 * Test d'une case d'un cheval decanille
 * Retour VRAI si le cheval est decanille
 *        FAUX sinon
 */

extern
booleen_t
piste_cell_decanillee( piste_t * piste ,
		       const piste_id_t indice) ;

/* Effacement d'une case de la piste */
extern void
piste_cell_effacer( piste_t * piste ,
		    const piste_id_t indice ) ;

/* Affichage de la piste */
extern void
piste_afficher_lig( piste_t * const piste );
extern void
piste_afficher_col( piste_t * const piste );

/* Initialisation de la piste (effacement de tous les chevaux) */
extern int
piste_initialiser( piste_t * piste );

/*
 * Comparaison de 2 pistes p1 et p2
 * Retour < 0 si p1 < p2  
 *        = 0 si p1 = p2
 *        > 0 si p1 > p2
 */
extern int
piste_comparer( piste_t * const p1 , piste_t * const p2 )  ;

/* 
 * Affectation d'une piste : p1 <-- p2
 * p1 doit etre creee avant l'appel a cette fonction 
 */
extern void
piste_affecter( piste_t * p1 , piste_t * const p2 );

#endif
