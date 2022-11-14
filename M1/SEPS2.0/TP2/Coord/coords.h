#ifndef _COORDS_H_
#define _COORDS_H_

/*!
 * \file coords.h
 * \brief Définitions Structure et Primitives d'une liste de coordonnées
 */

#include <coord.h>

/*
 * Type
 */

/*! 
 * \struct coords_t
 * \brief Type d'une liste de coordonnées
 */
typedef struct
{
  int nb ;		/*!< Nombre de coordonnées dans la liste */
  coord_t * coords ;	/*!< Liste des coordonnées */
} coords_t ;		

/*
 * Methodes set/get
 */


/*! Acces au nombre de coords dans la liste */
extern int coords_nb_get( const coords_t * const l );
/*! Acces a une coord dans la liste */
extern coord_t coords_get( const coords_t * const l  , const int ind_coord );
/*! Acces a l'adresse d'une coord dans la liste */
extern coord_t * coords_adr_get( const coords_t * const l  , const int ind_coord );
/*!
 * \fn err_t coords_set( coords_t * const liste_coords, const int ind_coord,  const coord_t coord ) 
 * \brief Affectation d'une coord dans une liste de coords 
 * \brief La position de la coord doit exister
 * \brief Si elle existe, l'ancienne valeur à l'indice ind_coord est écrasée 
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 * \param[in] liste_coords : liste des coordonnées dans laquelle on affecte l'élément
 * \param[in] ind_coord : indice de la liste auquel on ajoute la nouvelle coordonnée
 * \param[in] coord : l'élément coordonnée qu el'on ajoute
 * \return code erreur err_t
 */
extern err_t coords_set( coords_t * const liste_coords , 
			 const int ind_coord , 
			 const coord_t coord )  ;

/* 
 * Primitives 
 */

/*!
 * Creation d'une liste de coords
 * Stockage direct des éléments coord_t 
 */
extern coords_t * coords_new() ;

/*!
 *  Destruction d'une liste de coords 
 */

extern err_t coords_destroy( coords_t ** liste_coords ) ;

/*!
 * \name Affichage d'une liste de coords
 * @{‘
 */
/*! - sur la sortie standard */
extern void coords_printf( const coords_t * const liste_coords );
/*! - dans un fichier */ 
extern void coords_fprintf( FILE * restrict stream , const coords_t * const liste_coords ) ;
/*! @} */

/*! 
 * Copie d'une liste de coordonnees
 */
extern err_t coords_copier( coords_t ** coords_cible,
			    const coords_t * const coords_source ) ;
/*! 
 * Ajout d'une coord dans une liste de coords 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern err_t coords_add( coords_t * const liste_coords , 
			 const coord_t coord ) ;

/*! 
 * Deletion d'une coord dans une liste de coords 
 */
extern err_t coords_del( coords_t * const liste_coords , 
			 const int ind_coord )  ;

/*
 * Methode de recherche d'un element 
 */

/*!
 * \fn err_t coords_seek( const coords_t * const liste_coords, coord_t * const coord, int (*comparer) (const coord_t *, const coord_t * ) ) 
 * \brief Recherche d'une coord dans une liste de coords 
 * \param[in] liste_coords : liste de coordonnées dans lmaquelle on recherche l'élément
 * \param[in] coord : élément coordonnée qu el'on recherche dans la liste
 * \param[in] comparer : fonction de comparaison de 2 pointeurs de coordonnées
 * \return 
 * - CORRECT  : dans le cas d'une recherche positive
 * - PAS_TROUVE : dans le cas d'une recherche négative
 * - sinon autre code erreur err_t
 */

extern 
err_t coords_seek( const coords_t * const liste_coords,
		   coord_t * const coord ,
		   int (*comparer) (const coord_t *, const coord_t * ) ) ;

#endif


