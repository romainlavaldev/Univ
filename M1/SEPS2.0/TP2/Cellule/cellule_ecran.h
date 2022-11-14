#ifndef _CELLULE_ECRAN_H_
#define _CELLULE_ECRAN_H_

#include <ecran.h>
#include <cellule.h>

/*! 
 * \file  cellule_ecran.h
 * \brief Affichages d'une cellule sur un ecran   
 */

/*! 
 * \fn void cellule_wprint( ecran_t * const ecran, 
 *                          const int lig, 
 *                          const int col, 
 *                          const cellule_t * const cellule, 
 *                          const booleen_t dynamique )
 * \brief Affichage d'un cellule sur un ecran
 * \param[in] ecran : ecran sur lequel on affiche. On suppose que l'ecran contient deja l'affichage d'un automate
 * \param[in] lig : numero ligne de l'ecran ou afficher
 * \param[in] col : numero colonne de l'ecran ou afficher
 * \param[in] cellule : le cellule a afficher
 * \param[in] dynamique : <ul>
 * <li> VRAI : animation des cellules qui naissent et qui meurent
 * <li> FAUX : pas d'animation
 * </ul>
 */
extern
void cellule_wprint( ecran_t * const ecran ,
		     const int lig ,
		     const int col ,
		     const cellule_t * const cellule ,
		     const booleen_t dynamique ) ;

#endif 
