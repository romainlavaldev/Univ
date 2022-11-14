#ifndef _COMMUN_H_
#define _COMMUN_H_
/*!
 * \file commun.h
 * \brief Définitions Structure et Primitives communes à tout le TP
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

/*! \name Codes Erreurs
 * @{
 * \typedef err_t
 * \brief Type des codes erreurs
*/

typedef enum {
  CORRECT     =  0, /*!< Terminaison correcte, pas d'erreur */
  ERREUR      = -1, /*!< Erreur générique */
  PAS_TROUVE  = -2, /*!< Recherche négative d'un élément, élément inconnu */
  ERR_NULL    = -3, /*!< Reference inexistante */
  ERR_FILE    = -4, /*!< Erreur relative à un fichier (inexistant, lecture/écritrure impossible...) */
  ERR_DIM     = -5, /*!< Erreur dans une dimension donnée: indice de ligne et/ou de colonne incorrect */ 
  ERR_MEM     = -6, /*!< Fuire mémoire */
  ERR_SCAN    = -7, /*!< Erreur lors de la capture d'un élement par un scanf, read ... */
  ERR_ECRAN_NULL = -8  /*!< Reference sur un ecran inexistant */
} err_t ;

/*! \def ERR_NB
 * Nombre de codes erreur
 */
#define ERR_NB 9

/*! @} */

/*! 
 * \name Constantes générales
 * @{
 * \def STRING_LG_MAX
 * Longueur maximale d'une chaine de caractères
 */
#define STRING_LG_MAX 1024

/*! \typedef booleen_t
 * Type booleen 
 */
typedef enum
  {
    FAUX , /*!< Faux/False */
    VRAI   /*!< Vrai/True  */
  } booleen_t ;

/*!
 * @}
 */

/*!
 * \name Definition des règles par défaut de naissance/mort d'une cellule 
 * @{
 * \def NAISSANCE 
 * Nombre de voisins pour donner naissance a une cellule  
 * \def ISOLEMENT 
 * Nombre de voisins minimum en dessous duquel la cellule meurt isolee 
 * \def ETOUFFEMENT 
 * Nombre de voisins maximum au dessus duquel la cellule meurt etouffee 
 * @}
 */
#define NAISSANCE 3 
#define ISOLEMENT 2 
#define ETOUFFEMENT 3 

/*
 * FONCTIONS
 */

/*!
 * Affichage des messages d'erreurs sur la sortie erreur standard
 */
extern void err_print( err_t code ) ;

/*!
 * Entree d'un caractere au clavier 
 */
void Pause( char * mess ) ; 


#endif
