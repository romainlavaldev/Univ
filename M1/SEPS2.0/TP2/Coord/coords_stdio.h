#ifndef _COORDS_STDIO_H_
#define _COORDS_STDIO_H_

/*!
 * \file coords_stdio.h
 * \brief Primitives d'E/S standard d'une liste de coordonnées 
 */


#include <coord_stdio.h>
#include <coords.h>


/* 
 * Primitives 
 */

/*!
 * \fn void coords_print( FILE * const stream, const coords_t * const liste_coords )
 * \brief Sortie d'une liste de coords sur le descripteur coords_print#stream 
 * \param[in] stream : descripteur de sortie (stdout, descripteur de fichier...)
 * \param[in] liste_coords : liste des coordonnées à afficher
 */
extern void coords_print( FILE * const stream,
			  const coords_t * const liste_coords );


/*!
 * \fn err_t coords_scan( const char * const nom_fichier, coords_t * const liste_coords ) 
 * \brief Entree d'une liste de coords a partir d'un fichier. 
 * \brief La liste de coordonnées doit être créée avant l'appel de cette fonction. Cette fonction complète donc la liste des coordonnées mais ne la crée pas. 
 * \param[in] nom_fichier : nom du fichier source dans lequel on capture les coordonnées
 * \param[in,out] liste_coords :  liste des coordonnées à compléter.
 * - En donnée : liste de coordonnées éventuellment vide (créée mais sans aucun élément)
 * - En résultat : liste de coordonnées complétée avec celles du fichier
 */
extern err_t coords_scan( const char * const nom_fichier , coords_t * const liste_coords ) ;

#endif


