#ifndef _CHEVAL_H_
#define _CHEVAL_H_

#include <commun.h>
#include <cell.h>

/* Definition des types de base */

typedef struct elem_s 
{
  cell_t cell ; /* Infos sur le cheval (cellule de piste) */ 
  etat_t etat ; /* Etat du cheval (EN_COURSE, DECANILLE,...) */
  int    sem  ; /* Semaphore sur le cheval (1=en attente , 0=en train de se déplacer) */
} elem_t ;

typedef int elem_id_t ;

/*
 * Definition des fonctions 
 */

/* Fonctions d'affections */

/* - des infos */
extern 
void 
elem_cell_affecter( elem_t * elem,
		    const cell_t cell );

/* - de l'etat */
extern
void
elem_etat_affecter( elem_t * elem ,
		    const etat_t etat );

/* - du semaphore 
 *   Les fonction retournent 0 si OK -1 sinon  
 */
extern 
int
elem_sem_creer( elem_t * elem ) ;

extern 
int
elem_sem_verrouiller( elem_t * elem ) ; 

extern 
int
elem_sem_deverrouiller( elem_t * elem ) ; 

extern 
int
elem_sem_detruire( elem_t * elem ) ; 

/* Fonctions de lectures */

extern 
cell_t
elem_cell_lire( const elem_t elem );

extern
etat_t
elem_etat_lire( const elem_t elem );

/* - du semaphore 
 *   Renvoi valeur du semaphore si OK -1 sinon 
 */
extern 
int 
elem_sem_lire( const elem_t elem ) ;

/* Fonctions d'affichage */

extern 
void
elem_afficher( const elem_t elem );


/*
 * Test d'un element decanille
 * Retour VRAI si decanille 
 *        FAUX sinon
 */

extern
booleen_t
elem_decanille( const elem_t  elem );


/*
 * Comparaison de 2 elements e1 et e2
 * retour < 0 si e1 < e2
 *        = 0 si e1 = e2
 *        > 0 si e1 > e2 
 */

extern 
int
elem_comparer( const elem_t e1 , const elem_t e2 ) ;

#endif
