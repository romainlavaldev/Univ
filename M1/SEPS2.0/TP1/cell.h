#ifndef _CELL_H_
#define _CELL_H_

#include <unistd.h>
#include <commun.h>

/* Definition des types de base */

typedef struct cell_s 
{
  pid_t pid ;
  char marque ;
} cell_t ;

/*
 * Definition des fonctions 
 */

/* Affichage d'une case */
extern void
cell_afficher( const cell_t cellule );
extern void
cell_marque_afficher( const cell_t cellule );

/* Affectation d'une case */
extern void
cell_pid_affecter( cell_t * cell ,
		   const pid_t pid );
extern void
cell_marque_affecter( cell_t * cell ,
		      const char marque ) ;

/* Lecture d'une case */
extern pid_t
cell_pid_lire( const cell_t cell );

extern char
cell_marque_lire( const cell_t cell );

/*
 * Comparaison de 2 cases 
 * Retour < 0 si p1 < p2  
 *        = 0 si p1 = p2
 *        > 0 si p1 > p2
 */

extern
int
cell_comparer( const cell_t c1 , const cell_t c2 ) ;


/*
 * Test d'une case libre
 * Retour VRAI si libre
 *        FAUX sinon
 */

extern booleen_t
cell_libre( const cell_t  cell );

/*
 * Test d'une case occupee
 * Retour VRAI si occupee
 *        FAUX sinon
 */

extern booleen_t
cell_occupee( const cell_t cell );

#endif
