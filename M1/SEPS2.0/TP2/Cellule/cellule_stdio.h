#ifndef _CELLULE_STDIO_H_
#define _CELLULE_STDIO_H_

#include <cellule.h>
#include <coords_stdio.h>

/*! 
 * \file  cellule_stdio.h
 * \brief Affichages d'une cellule sur la sortie standard
 */

/*!
 * \fn void cellule_map( FILE * const stream, const cellule_t * const cellule ) 
 * \brief Affichage de toutes les caracteristiques d'une cellule sur la sortie donnée en paramètre
 * \param[in] stream : descripteur de sortie (stdout, descripteur de fichier...)

 * \param[in] cellule : cellule à afficher
 */
extern void cellule_map( FILE * const stream,
			 const cellule_t * const cellule ) ;

/*!
 * \fn void cellule_print(FILE * const stream , const cellule_t * const cellule ) 
 * \brief Affichage synthétique d'une cellule sur sortie standard
 * \param[in] stream : descripteur de sortie (stdout, descripteur de fichier...)
 * \param[in] cellule : cellule à afficher
 */

extern 
void cellule_print(FILE * const stream ,
		   const cellule_t * const cellule ) ;

#endif


