#ifndef _CELLULE_H_
#define _CELLULE_H_

#include <commun.h>
#include <coords.h>
/*! 
 * \file  cellule.h
 * \brief Type et primitives du type cellule_t
 */


/*
 *=============================================================
 * Constantes du TDA cellule
 *=============================================================
 */

/*!
 * \typedef cellule_etat_t
 * \brief Type de l'etat d'une cellule
 */
typedef enum { INIT  , /*!< Etat initial d'une cellule */
               MORTE , /*!< Cellule morte  */
               VIVANTE /*!< Cellule vivante */
} cellule_etat_t ;

/*
 *=============================================================
 * Realisation du TDA cellule 
 *=============================================================
 */

/*!
 * \struct cellule_t
 * \brief Type d'une cellule
 */
typedef struct
{
  coord_t * coords ;		/*!< Coordonnees de la cellule */
  cellule_etat_t  etat   ;	/*!< Etat de la cellule pour la generation courante  */
  cellule_etat_t  etat_next   ;	/*!< Etat de la cellule pour la generation prochaine */
  int generation ;		/*!< Numero de la generation de la cellule */
} cellule_t ;

/*!
 * \struct cellule_regles_t
 * \brief Type contenant les règles de naissance et de mort d'une cellule
 */
typedef struct 
{
  int naissance    ; /*!< Nombre de voisins pour donner naissance a une cellule */
  int isolement    ; /*!< Nombre de voisins minimum en dessous duquel la cellule meurt isolee */
  int etouffement  ; /*!< Nombre de voisins maximum au dessus duquel la cellule meurt etouffee */
} cellule_regles_t ;



/*
 *=============================================================
 * Primitives du TDA cellule 
 *=============================================================
 */


/*!
 * \name Fonctions get/set 
 * @{
 */
/*! 
 * Affectation des caracteristiques complètes d'une cellule 
 */
extern err_t cellule_set( cellule_t * const cellule,
			const coord_t * const coords ,
			const cellule_etat_t etat ) ;

/*!
 * Obtention des coordonnees d'une cellule 
 */
extern coord_t * cellule_coords_get( const cellule_t * const cellule ) ;
/*!
 * Affectation des coordonnees d'une cellule 
 */
extern err_t cellule_coords_set( cellule_t * const cellule , 
			       const coord_t * const coord) ;

/*! Obtention de l'état d'une cellule à la génération courante */
extern cellule_etat_t cellule_etat_get( const cellule_t * const cellule  )  ;
/*! Affectation de l'état d'une cellule à la génération courante */
extern err_t cellule_etat_set( cellule_t * const cellule , const cellule_etat_t etat)  ;
/*! Obtention de l'état d'une cellule à la prochiane génération */
extern cellule_etat_t cellule_etat_next_get( const cellule_t * const cellule  )  ;
/*! Affectation de l'état d'une cellule à la prochiane génération */
extern err_t cellule_etat_next_set( cellule_t * const cellule , const cellule_etat_t etat)  ;
/*! Affectation de l'état #MORTE à une cellule pour la génération courante */
extern err_t cellule_tuer( cellule_t * const cellule )  ;
/*! Affectation de l'état #VIVANTE  à une cellule pour la génération courante */
extern err_t cellule_naitre( cellule_t * const cellule )  ;
/*! Affectation de l'état #MORTE à une cellule pour la prochaine génération */
extern err_t cellule_next_tuer( cellule_t * const cellule )  ;
/*! Affectation de l'état #VIVANTE  à une cellule pour la prochaine génération */
extern err_t cellule_next_naitre( cellule_t * const cellule )  ;

/*! Obtention du numero de generation d'une cellule */
extern int cellule_generation_get( const cellule_t * const cellule  ) ;
/*! Affectation du numero de generation d'une cellule */
extern err_t cellule_generation_set( cellule_t * const cellule , const int generation ) ;
/* !  @} */



/*!
 * \name Constructeur/Destructeur d'une cellule 
 * @{
 */
/*! Création d'une cellule à partir des indices ligne/colonnes */
extern cellule_t * cellule_new( const int lig , const int col,  const cellule_etat_t etat ) ;
/*! Création d'une cellule à partir d'une coordonnée */
extern cellule_t * cellule_coord_new( const coord_t * const coords , const cellule_etat_t etat ) ;

/*! Destruction une cellule */
extern err_t cellule_destroy( cellule_t ** cellule ) ;

/*! @} */

/*!
 * \name Gestion d'une cellule 
 * @{
 */

/*!
 * Initialisation d'une cellule.
 * Verifie si les coordonnees d'une cellule a creer sont dans une liste de coordonnees d'initialisation.
 * Si oui alors creation d'une cellule vivante
 * sinon creation d'une cellule  morte
 */
extern cellule_t * cellule_initialiser( const int lig , const int col , const coords_t * const liste_coords) ;

/*!
 *  Calcul de la nouvelle génération d'une cellule en fonction de ses voisins
 */
extern err_t cellule_evoluer( cellule_t * const cellule , const int nb_voisins , const cellule_regles_t * const regles );

/*!
 * Prise en compte de la nouvelle generation d'une cellule: la prochaine génération devient la génération actuelle/courante
 */
extern err_t cellule_generer( cellule_t * const cellule ) ; 

/*! @} */


/*!
 * \name Transformation
 * @{ 
 */

/*!
 * Transformation d'une cellule en ue chaine de caracteres
 */
extern char * cellule_etat_2_string( cellule_etat_t etat ) ;
/*! @} */

/*!
 * \name Tests
 * @{ 
 */

/*! Teste si une cellule est vivante */
extern booleen_t cellule_vivante( const cellule_t * const cellule )  ;
/*! Teste si une cellule est morte */
extern booleen_t cellule_morte( const cellule_t * const cellule ) ;
/*! Teste si une cellule existe */
extern booleen_t cellule_existe( const cellule_t * const cellule ) ;
/*! @} */


/*
 *=============================================================
 * Primitives gestions de cellule_regles_t
 *=============================================================
 */

/*! 
 * \name Initialisations
 * @{ 
 */

/*! Fournit une structure des regles avec les valeurs par défaut */
extern cellule_regles_t cellule_regles_default() ;
/*! Initialise une structure de règles avec les valeurs par défaut */
extern err_t cellule_regles_initialiser(cellule_regles_t * const regles); 

/*! @} */

/*! 
 * \name Fonctions get/set
 * @{
 */

/*! Obtention du nombre de voisins pour faire naître une cellule */
extern int cellule_regles_naissance_get(const cellule_regles_t * const regles) ;
/*! Affectation du nombre de voisins pour faire naître une cellule */
extern err_t cellule_regles_naissance_set(cellule_regles_t * const regles , const int naissance ) ;

/*! Obtention du nombre de voisins au dessous duquel une cellule meurt isolée */
extern int cellule_regles_isolement_get(const cellule_regles_t * const regles) ;
/*! Affectation du nombre de voisins au dessous duquel une cellule meurt isolée */
extern err_t cellule_regles_isolement_set(cellule_regles_t * const regles , const int isolement ) ;

/*! Obtention du nombre de voisins au dessus duquel une cellule meurt étouffée */
extern int cellule_regles_etouffement_get(const cellule_regles_t * const regles) ;
/*! Affectation du nombre de voisins au dessus duquel une cellule meurt étouffée */
extern err_t cellule_regles_etouffement_set(cellule_regles_t * const regles , const int etouffement ) ;

/*! @} */
/*! @} */

#endif
