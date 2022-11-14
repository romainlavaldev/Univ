#ifndef _COORD_H_
#define _COORD_H_

#include <commun.h>
/*!
 * \file coord.h
 * \brief Définitions Structure et Primitives d'une coordonnée
 */

/* 
 *===================================================
 * Realisation du TDA coord (coordonnees d'une case) 
 *=================================================== 
 */

/*! 
 * \struct coord_t
 * \brief Type d'une coordonnée 
 */
typedef struct 
{
  int l ;		/*!< numero ligne   */
  int c ;		/*!< numero colonne */
} coord_t ;

/*! \def COORD_VIDE
 * \brief Valeur d'une coordonnée à l'état initial
 * \fn coord_t coord_vide()
 * \brief fonction renvoyant la valeur initiale d'une coordonnée
 */
#define COORD_VIDE coord_vide()
extern coord_t coord_vide() ;


/* 
 *===================================================
 * Primitives du TDA coord 
 *=================================================== 
 */

/*! 
 * Ecriture des coordonnees d'une case 
 */
extern err_t  coord_set( coord_t * const coord , 
			 const int ligne,
			 const int colonne ) ; 

/*!
 * Lecture des coordonnees d'une case 
 */

extern
err_t coord_get( const coord_t * const coord , 
		 int * ligne,
		 int * colonne);
/*! Obtention du numéro de ligne d'une coordonnée */
extern int coord_lig_get( const coord_t * const coord ) ;
/*! Obtention du numéro de colonne d'une coordonnée */
extern int coord_col_get( const coord_t * const coord ) ; 

/*! 
 * Création d'une coord 
 */
extern coord_t * coord_new(const int ligne, const int colonne ) ;

/*! 
 * Destruction d'une coord 
 */
extern err_t coord_destroy( coord_t ** coord ) ;

/*! 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */
extern int coord_comparer( const coord_t * c1, const coord_t * c2 );
/*! Fonciton générique de comparaison */
extern int coord_comparer_cb( const void * c1, const void * c2 ) ;

/*! 
 * Copie de coordonnées
 * Les coordonnees doivent exister avant l'appel 
 */
extern err_t coord_copier( coord_t * const coord_cible,
			   const coord_t * const coord_source ) ; 
/*!
 * Transformation coord en chaine de caracteres
 * ATTENTION : reservation memoire 
 */

extern char * coord_2_string( const coord_t * const coord ) ;

#endif
