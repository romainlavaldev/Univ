#ifndef _AUTOMATE_H_
#define _AUTOMATE_H_

#include <unistd.h>

#include <cellule.h>
#include <coords.h>

/*!
 * \file automate.h
 * \brief Définitions Structure et Primitives d'un automate
 */

/*
 *=============================================================
 * Constantes du TDA automate
 *=============================================================
 */



/*
 *=============================================================
 * Realisation du TDA automate 
 *=============================================================
 */

/*!
 * \struct automate_t
 * \brief Type d'un automate
 */
typedef struct 
{
  int hauteur ;		/*!< Hauteur de l'automate */
  int largeur ;		/*!< Largeur de l'automate */
  cellule_t ** tab  ;	/*!< Tableau contenant les cellules l'automate */
} automate_t ;

/*
 *=============================================================
 * Primitives du TDA automate 
 *=============================================================
 */



/*!
 * \name Fonctions set/get
 * @{
 */

/*! Obtention de la hauteur */
extern int automate_hauteur_get( const automate_t * const automate ) ;
/*! Obtention de la largeur */
extern int automate_largeur_get( const automate_t * const automate ) ;
/*! Obtention de la hauteur et la largeur */
extern err_t automate_dim_get( const automate_t * const automate, int * hauteur, int * largeur ) ;
/*! Affectation de la hauteur */
extern err_t automate_hauteur_set( automate_t * const automate, const int hauteur ) ;
/*! Affectation de la largeur */
extern err_t automate_largeur_set( automate_t * const automate, const int largeur ) ;
/*! Affectation de la hauteur et la largeur */
extern err_t automate_dim_set( automate_t * const automate, const int hauteur, const int largeur ) ; 

/*! 
 * \fn cellule_t * automate_get( const automate_t * const automate, const int i, const int j ) 
 * \brief Obtention d'une cellule 
 * \param[in] automate : automate 
 * \param[in] i : indice de ligne 
 * \param[in] j : indice de colonne 
 * \return pointeur sur la #cellule_t de la case [i,j] de l'automate 
 */
extern cellule_t * automate_get( const automate_t * const automate , 
				 const int i ,			
				 const int j ) ;		

/*! 
 * \fn err_t automate_set( automate_t * const automate, const int i, const int j, cellule_t * const cellule )
 * \brief Affectation d'une cellule 
 * \param[in,out] automate : automate 
 * \param[in] i : indice de ligne 
 * \param[in] j : indice de colonne
 * \param[in] cellule : valeur de cellule a affecter
 * \return code erreur #err_t 
 */
extern err_t automate_set( automate_t * const automate ,	
			   const int i ,			
			   const int j ,			
			   cellule_t * const cellule ) ;	
/*! @} */

/*!
 * \name Constructeur/Destructeur
 * @{
 */

/*! 
 * \fn automate_new(const int hauteur , const int largeur , coords_t * coords_init )
 * \brief Creation d'un automate : 
 * 1. Création des cases de l'automate
 * 2. Création des cellules de l'automate en fonction des coordonnées d'initialisation. 
 *   - Si les coordonnées d'une cellule sont dans la liste des coordonnées d'initialisation alors celle-ci est créée vivante
 *   - sinon elle est créée morte
 * 3. Affectation des cellules à l'automate
 * \param[in] hauteur : nombre de lignes de l'automate
 * \param[in] largeur : nombre de colonnes de l'automate
 * \param[in] coords_init : liste des coordonnées d'initialisation
 * \return une instance de automate_t
 */
extern automate_t * automate_new(const int hauteur , const int largeur , coords_t * coords_init );

/*!
 * Destruction d'un automate 
 */

extern err_t automate_destroy( automate_t ** automate ) ;
/*! @} */

/*!
 * \name Gestion d'un automate
 * @{
 */

/*!
 * \fn err_t automate_nb_voisins_get( automate_t * automate , coord_t * coord, int * nb_voisins ) 
 * \param[in] automate : automate contenant la cellule 
 * \param[in] coord : coordonnées de la cellule dont on veut calculer le nombre de voisins
 * \param[out] nb_voisins : nombre de voisins de la cellule
 * \brief Calcul du nombre de cellules vivantes autour d'une case de l'automate
 * \return code erreur #err_t 
 */

extern err_t automate_nb_voisins_get( automate_t * automate ,
				      coord_t * coord,
				      int * nb_voisins ) ;

/*!
 * \fn err_t automate_cellule_evoluer( automate_t * automate , cellule_t * cellule , const cellule_regles_t * const regles ) 
 * \brief Calcul de la nouvelle generation d'une cellule dans un automate en fonction de ses voisins
 * \param[in] automate : automate contenant la cellule 
 * \param[in,out] cellule : cellule à faire évoluer
 * \param[in] regles : règles de vie/mort d'une cellule
 * \return code erreur #err_t
 */

extern err_t automate_cellule_evoluer( automate_t * automate ,
				       cellule_t * cellule ,
				       const cellule_regles_t * const regles ) ;

/*!
 * \fn err_t automate_generer( automate_t * automate )
 * \brief Prise en compte de la nouvelle generation d'un automate: pour chaque cellule, la génération prochaine devient la génération courante
 * \param[in] automate : automate 
 * \return code erreur #err_t
 */

extern err_t automate_generer( automate_t * automate ) ;
/*! @} */


#endif



