#ifndef _COORD_STDIO_H_
#define _COORD_STDIO_H_

#include <coord.h>

/*!
 * \file coord_stdio.h
 * \brief Fonctions d'E/S standards d'une coordonnée
 */

/*!  
 * Affichage d'une coordonnée sur une sortie 
 */
extern void coord_print( FILE * const stream,
				const coord_t * const coord ) ;
/*!  
 * Capture des coordonnees d'une case 
 */

extern err_t coord_scan( FILE * const stream,
			 coord_t * const coord )  ;

#endif
