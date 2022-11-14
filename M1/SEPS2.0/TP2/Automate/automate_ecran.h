#ifndef _AUTOMATE_ECRAN_H_
#define _AUTOMATE_ECRAN_H_

#include <automate.h>
#include <cellule_ecran.h>


/*!
 * \file automate_ecran.h
 * \brief Primitives d'affichage d'un automate sur un ecran 
 */

/*
 * TYPES 
 */

 /*!
 * \name Affichage automate sur un ecran existant
 * @{
 */

/*! 
 * \fn ecran_t * automate_ecran_creer(const automate_t * const automate ) 
 * \brief Creation d'un ecran pour l'affichage d'un automate 
 * \param[in] automate  : l'automate a afficher
 * \return une structure #ecran_t instanciée
 */
extern ecran_t * automate_ecran_creer( const automate_t * const automate );

/*! 
 * \fn void automate_wprint( ecran_t * const ecran , const automate_t * const automate )
 * \brief Affichage normal d'un automate 
 * \param[in] ecran   : ecran sur lequel on affiche le automate
 * \param[in] automate  : le automate a afficher
 */

extern void automate_wprint( ecran_t * const ecran , const automate_t * const automate )  ;

 /*!
 * @}
 */
#endif
