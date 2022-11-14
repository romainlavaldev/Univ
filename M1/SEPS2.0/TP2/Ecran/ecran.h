#ifndef _ECRAN_H_
#define _ECRAN_H_

#include <ncurses.h>
#include <unistd.h>

#include <coord.h>

/* 
 * Dans certain UBUNTU 
 * #include <ncurses/ncurses.h>
 */

/*! 
 * \file  ecran.h
 * \brief Structures et Primitives de l'&eacute;cran 
 * 
 * L'ecran est g&eacute;r&eacute; par les primitives de la biblioth&egrave;que "curses"  
 * L'ecran est divise en 2 fenetres : 
 * \li la fenetre d'affichage 
 * \li la fenetre des messages
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
 * \def ECRAN_TEMPS_BREF
 * \brief Pause sur affichage durant un bref instant
 */
#define ECRAN_TEMPS_BREF 500000

/*
 * MACROS
 */
/*!
 * \def  ecran_lc_wprint0( ecran , l , c , mess ) 
 * Raccourci pour <code>ecran_lc_wprint( ecran , l , c , mess , 0 , ECRAN_NORMAL ) </code>
 * \def  ecran_lc_wprint1( ecran , l , c , mess , temps ) </code>
 * Raccourci pour <code>ecran_lc_wprint( ecran , l , c , mess , temps , ECRAN_NORMAL )  </code>
 * \def  ecran_lc_wprint2( ecran , l , c , mess , temps , mode ) 
 * Raccourci pour <code>ecran_lc_wprint( ecran , l , c , mess , temps , mode )  </code>
 * \def  ecran_coord_wprint0( ecran , coord , mess ) 
 * Raccourci pou <code>ecran_coord_wprint( ecran , coord , mess , 0 , ECRAN_NORMAL )</code>
 * \def  ecran_coord_wprint1( ecran , coord , mess , temps ) 
 * Raccourci pour <code>ecran_coord_wprint( ecran , coord , mess , temps , ECRAN_NORMAL )</code>
 * \def  ecran_coord_wprint2( ecran , coord , mess , temps , mode ) 
 * Raccourci pour <code>ecran_coord_wprint( ecran , coord , mess , temps , mode )</code>
 */

#define ecran_lc_wprint0( ecran , l , c , mess ) ecran_lc_wprint( ecran , l , c , mess , 0 , ECRAN_NORMAL )  
#define ecran_lc_wprint1( ecran , l , c , mess , temps ) ecran_lc_wprint( ecran , l , c , mess , temps , ECRAN_NORMAL )  
#define ecran_lc_wprint2( ecran , l , c , mess , temps , mode ) ecran_lc_wprint( ecran , l , c , mess , temps , mode )  

#define ecran_coord_wprint0( ecran , coord , mess ) ecran_coord_wprint( ecran , coord , mess , 0 , ECRAN_NORMAL )
#define ecran_coord_wprint1( ecran , coord , mess , temps ) ecran_coord_wprint( ecran , coord , mess , temps , ECRAN_NORMAL )
#define ecran_coord_wprint2( ecran , coord , mess , temps , mode ) ecran_coord_wprint( ecran , coord , mess , temps , mode )

/*
 * TYPES
 */


/*!
 * \struct ecran_t
 * \brief Type d'&eacute;cran
 */
typedef struct
{
  WINDOW * affichage ;		/*!< Fenetre d'affichage */
  WINDOW * messages ;		/*!< Fenetre des messages */
  int largeur ;		        /*!< Largeur des fenetres */
  int y_messages ;		/*!< Ordonnee de la fenetre des messages */
  char * nom_err ;		/*!< Nom du fichier d'erreurs */
} ecran_t ; 

/*!
 * \typedef ecran_mode_t
 * \brief Mode video de l'ecran
 */
typedef enum {
  ECRAN_NORMAL=0 , /*!< Ecran en mode normal */
  ECRAN_REVERSE=1  /*!< Ecran en mode inverse vidéo */
} ecran_mode_t ;

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*!
 * \fn  WINDOWS * ecran_affichage_get( const ecran_t * const ecran ) 
 * \brief Acces &agrave; la fenetre d'affichage
 * \param[in] ecran : ecran 
 */
extern WINDOW * ecran_affichage_get( const ecran_t * const ecran ) ;
/*!
 * \fn  WINDOW * ecran_messages_get( const ecran_t * const ecran ) 
 * \brief Acces &agrave; la fenetre des messages
 * \param[in] ecran : ecran d'affichage 
 */
extern WINDOW * ecran_messages_get( const ecran_t * const ecran ) ;

/*!
 * \fn ecran_affichage_id_t  ecran_y_messages_get( const ecran_t * const ecran ) 
 * \brief Acces au numero de la affichage (l'ordonnee y) ou commence la fenetre des messages. 
 * \param[in] ecran : ecran d'affichage 
 */
extern int ecran_y_messages_get( const ecran_t * const ecran ) ; 

/*!
 * \fn int ecran_largeur_get( const ecran_t * const ecran ) 
 * \brief Largeur de la fenetre de la affichage  
 * \param[in] ecran : ecran d'affichage 
 */
extern int ecran_largeur_get( const ecran_t * const ecran ) ; 

/*!
 * \fn int ecran_hauteur_get( const ecran_t * const ecran ) 
 * \brief Largeur de la fenetre de la affichage  
 * \param[in] ecran : ecran d'affichage 
 */
extern int ecran_hauteur_get( const ecran_t * const ecran ) ; 

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
extern booleen_t  ecran_existe( const ecran_t * const ecran ) ; 
/*! @} */

  ;
/*!
 * \fn ecran_t * ecran_creer( const int H_affichage , const int L_affichage )
 * 
 * \param[in] H_affichage : hauteur demandée pour l'écran 
 * \param[in] L_affichage : largeur demandée pour l'écran 
 * 
 * \brief Creation d'un ecran type "ncurses"
 * \brief On ne peut avoir qu'un ecran par console/terminal 
 * - si H_affichage = 0 --> hauteur ecran = hauteur console 
 * - si L_affichage = 0 --> largeur ecran = largeur console
 * <P>
 * La sortie erreur standard est redirig&eacute;e dans un fichier pour 
 * afficher les erreurs dans la fenetre des messages et ne pas polluer l'affichage de l'ecran
 * \return la structure #ecran_t instanciée
 */
extern ecran_t * ecran_creer( const int H_affichage , const int L_affichage ) ;

/*!
 * \fn err_t ecran_detruire( ecran_t ** ecran )
 * \brief Destruction fenetre de l'affichage 
 * \param[in,out] ecran:  fenetre &agrave; d&eacute;truire
 * \return code erreur err_t
 */
extern err_t ecran_detruire( ecran_t ** ecran )  ; 

/*!
 * \fn void ecran_message_afficher( ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_pause_afficher( ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message avec une pause de ECRAN_PAUSE_MESS seconde(s) avant qu'il ne soit &eacute;ventuellment effac&eacute; 
 * dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_pause_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_droite_afficher( ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message justifi&eacute; &agrave; droite dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_droite_afficher( ecran_t * const ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_droite_pause_afficher( ecran_t * const ecran , char * const mess ) 
 * \brief Affichage d'un message justifi&eacute; &agrave; droite avec une pause de ECRAN_PAUSE_MESS seconde(s) avant qu'il ne soit &eacute;ventuellment effac&eacute; 
 * dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_droite_pause_afficher( ecran_t * const ecran , char * const mess ) ; 


/*!
 * \fn void ecran_stderr_afficher( ecran_t * ecran ) 
 * \brief Affichage de la sortie standard d'erreurs sur l'ecran 
 * dans la fenetre des messages 
 * \param[in] ecran : ecran dans lequel on affiche
 */

extern void ecran_stderr_afficher( ecran_t * const ecran )  ; 

/*!
 * \fn void ecran_lc_wprint( ecran_t * const ecran , 
 *			     const int lig , const int col , 
 *			     char * const mess   , 
 *			     unsigned int micro_seconds ,
 *			     ecran_mode_t video_mode ) 
 * \brief Inscription d'une chaine de caracteres dans la fenetre d'affichage de l'ecran 
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 * \param[in] lig : numero de la ligne d'affichage du message 
 * \param[in] col : numero de colonne 
 * \param[in] micro_seconds : temps de pause du message en microsecondes
 * \param[in] video_mode : mode ecran pour afficher le message
 */
extern void ecran_lc_wprint( ecran_t * const ecran , 
			     const int lig , const int col , 
			     char * const mess   , 
			     unsigned int micro_seconds ,
			     ecran_mode_t video_mode ) ;


/*!
 * \fn void ecran_coord_wprint( ecran_t * const ecran , 
 *				const coord_t * const coord , 
 *				char * const mess ,
 *				unsigned int micro_seconds ,
 *				ecran_mode_t video_mode )  
 * \brief Inscription d'une chaine de caracteres dans la fenetre d'affichage de l'ecran 
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 * \param[in] coord : coordonnees d'affichage du message 
 * \param[in] micro_seconds : temps de pause du message en microsecondes
 * \param[in] video_mode : mode ecran pour afficher le message
 */
extern void ecran_coord_wprint( ecran_t * const ecran , 
				const coord_t * const coord , 
				char * const mess ,
				unsigned int micro_seconds ,
				ecran_mode_t video_mode )  ;

/*!
 * \fn void ecran_message_stop_afficher( ecran_t * const ecran , char * const mess )
 * \brief Stop l'affichage jusqu'a l'entree d'une touche avec inscription d'une chaine de caracteres dans la fenetre d'affichage de l'ecran en clignotant
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_stop_afficher( ecran_t * const ecran , char * const mess ) ;

#endif
