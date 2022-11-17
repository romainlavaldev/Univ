#ifndef _ECRAN_H_
#define _ECRAN_H_

#include <commun.h>
#include <ncurses.h>

#include <pthread.h>

/* 
 * Dans certain UBUNTU 
 * #include <ncurses/ncurses.h>
 */

/*! 
 * \file  ecran.h
 * \brief Structures et Primitives de l'&eacute;cran 
 * 
 * L'ecran est g&eacute;r&eacute; par les primitives de la biblioth&egrave;que "curses"  
 * L'ecran est divise en 2 zones : 
 * \li la zone d'affichage de la ligne
 * \li la zone d'affichage des messages
 */

/* 
 * Partage de l'ecran entre plusieurs trains : 
 * A FAIRE
 */ 

/*
 * CONSTANTES
 */
/*!
 * \def ECRAN_NULL
 * \brief Valeur d'un ecran inexistant
 */
#define ECRAN_NULL NULL

/*!
 * \def ECRAN_LG_MESS
 * \brief Longueur max d'un message 
 */
#define ECRAN_LG_MESS 256

/*!
 * \def ECRAN_PAUSE_MESS
 * \brief Nombre de secondes minimum pendant lesquelles un message reste affiche 
 */
#define ECRAN_PAUSE_MESS 1

/*
 * VARIABLES GLOBALES 
 */

/*!
 * \var Ecran_Nb_Ref
 * \brief Compteur de r&eacute;f&eacute;rences sur un objet ecran
 */
/*
 * TYPES
 */

/*!
 * \typedef ecran_ligne_id_t 
 * \brief type d'un index de ligne d'ecran 
 */
typedef unsigned int ecran_ligne_id_t ; 

/*!
 * \struct ecran_t 
 * \brief Type de la structure d'&eacute;cran 
 */
typedef struct ecran_s
{
  WINDOW * ligne ;		/*!< Fenetre de la ligne de chemin de fer */
  int largeur ;			/*!< Largeur de la fenetre de la ligne */
  WINDOW * messages ;		/*!< Fenetre des messages */
  ecran_ligne_id_t y_messages ;	/*!< Ordonnee de la fenetre des messages */
  char * nom_err ;		/*!< Nom du fichier d'erreurs */
} ecran_t ; 

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*!
 * \fn  WINDOWS * ecran_ligne_get( const ecran_t * const ecran ) 
 * \brief Acces &agrave; la fenetre de l'ligne
 * \param[in] ecran : ecran d'affichage 
 */
extern WINDOW * ecran_ligne_get( const ecran_t * const ecran ) ;
/*!
 * \fn  WINDOW * ecran_messages_get( const ecran_t * const ecran ) 
 * \brief Acces &agrave; la fenetre des messages
 * \param[in] ecran : ecran d'affichage 
 */
extern WINDOW * ecran_messages_get( const ecran_t * const ecran ) ;

/*!
 * \fn ecran_ligne_id_t  ecran_y_messages_get( const ecran_t * const ecran ) 
 * \brief Acces au numero de la ligne (l'ordonnee y) ou commence la fenetre des messages. 
 * \param[in] ecran : ecran d'affichage 
 */
extern ecran_ligne_id_t  ecran_y_messages_get( const ecran_t * const ecran ) ; 

/*!
 * \fn int ecran_largeur_get( const ecran_t * const ecran ) 
 * \brief Largeur de la fenetre de la ligne  
 * \param[in] ecran : ecran d'affichage 
 */
extern int ecran_largeur_get( const ecran_t * const ecran ) ; 

/*! @} */

/*!
 * \name Tests 
 * @{
 */

/*!
 * \fn boolean_t  ecran_existe( const ecran_t * const ecran ) 
 * \brief Test d'exsiatnce d'un ecran 
 * \param[in] ecran : un ecran
 */
extern boolean_t  ecran_existe( const ecran_t * const ecran ) ; 
/*! @} */

  ;
/*!
 * \fn ecran_t * ecran_creer( )
 * \brief Creation fenetre  
 *
 * La sortie erreur standard est redirig&eacute;e dans un fichier pour 
 * afficher les erreurs dans la fenetre des messages et ne pas polluer l'affichage de l'ecran
 * \return une fenetre dans laquelle on peut afficher la ligne
 */
extern ecran_t * ecran_creer( ) ;

/*!
 * \fn err_t ecran_detruire( ecran_t ** ecran )
 * \brief Destruction fenetre de l'ligne 
 * \param[in,out] ecran:  fenetre &agrave; d&eacute;truire
 */
extern int ecran_detruire( ecran_t ** ecran )  ; 

/*!
 * \fn void ecran_message_afficher( const ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_pause_afficher( const ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message avec une pause de ECRAN_PAUSE_MESS seconde(s) avant qu'il ne soit &eacute;ventuellment effac&eacute; 
 * dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_pause_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_droite_afficher( const ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message justifi&eacute; &agrave; droite dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_droite_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_droite_pause_afficher( const ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message justifi&eacute; &agrave; droite avec une pause de ECRAN_PAUSE_MESS seconde(s) avant qu'il ne soit &eacute;ventuellment effac&eacute; 
 * dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_droite_pause_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_effacer( const ecran_t * const ecran ) 
 * \brief Efface le contenu de la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 */
/* extern void ecran_message_effacer( const ecran_t * const ecran ) ; */

/*!
 * \fn void ecran_stderr_afficher( ecran_t * ecran ) 
 * \brief Affichage de la sortie standard d'erreurs sur l'ecran 
 * dans la fenetre des messages 
 * \param[in] ecran : ecran dans lequel on affiche
 */

extern void ecran_stderr_afficher( ecran_t * const ecran )  ; 

#endif
