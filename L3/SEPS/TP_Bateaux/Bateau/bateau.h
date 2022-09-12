#ifndef _BATEAU_H_
#define _BATEAU_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <coords.h>

/*
 *=============================================================
 * Constantes du TDA bateau
 *=============================================================
 */

#define BATEAU_TAILLE  4
#define BATEAU_SEUIL_BOUCLIER 10
#define BATEAU_MAX_ENERGIE 500
#define BATEAU_DELAI_VAINQUEUR 5

#define BATEAU_NULL NULL 
#define BATEAU_VIDE bateau_vide()

/*
 *=============================================================
 * Realisation du TDA bateau 
 *=============================================================
 */

typedef struct bateau_s
{
  coords_t   * corps ;  /* liste de BATEAU_TAILLE coords */
  case_t       marque ; /* 1 caractere identifiant le bateau */
  pid_t        pid ;    /* PID du processus bateau */
} bateau_t ;


/*
 *=============================================================
 * Primitives du TDA bateau 
 *=============================================================
 */
/*
 * Valeur bateau vide 
 */

extern bateau_t bateau_vide() ;

/*
 * Methodes creation/destruction 
 */
extern bateau_t * bateau_new(const coords_t * const coords,
			     const case_t marque,
			     const pid_t pid )  ; 
extern int bateau_destroy( bateau_t ** bateau )  ;

/*
 * Methodes  get/set 
 */

extern coords_t * bateau_corps_get( const bateau_t * const bateau )  ; 
extern int bateau_corps_set( bateau_t * const bateau ,    /* Bateau */
			     const coords_t * const coords) ; /* Tableau de BATEAU_TAILLE coords composant le corps du bateau */

extern case_t bateau_marque_get( const bateau_t * const bateau )  ; 
extern int bateau_marque_set( bateau_t * const bateau , 
			      const case_t m)  ;

extern pid_t bateau_pid_get( const bateau_t * const bateau )  ;
extern int bateau_pid_set( bateau_t * const bateau , 
			   const pid_t pid) ;
extern int bateau_set( bateau_t * bateau,
		       const coords_t * const coords,
		       const case_t marque,
		       const pid_t pid );

/*
 * Copie d'un bateau 
 * "bateau_cible" est cree ; s'i existait deja alors il est efface puis re-cree
 */

extern int bateau_copier( bateau_t ** bateau_cible , const bateau_t * const bateau_source ) ;

/* 
 * Affichages de toutes les caracteristiques d'un bateau 
 */

/* - sur la sortie standard */

extern void bateau_printf( const bateau_t * const bateau ) ;

/* - dans un fichier */

extern void bateau_fprintf( FILE * restrict stream , const bateau_t * const bateau ) ; ;

/*
 * Ecriture dans un fichier 
 */
extern int bateau_write( const int fd , /* Descriteur du fichier */
			 const bateau_t * const bateau ) ;

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture 
  * Le bateau "bateau" est cree 
  */
extern int bateau_read( const int fd , /* Descriteur du fichier */
			bateau_t ** bateau ) ;
#endif


