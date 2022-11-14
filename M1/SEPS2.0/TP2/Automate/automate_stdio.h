#ifndef _AUTOMATE_STDIO_H_
#define _AUTOMATE_STDIO_H_


#include <automate.h>
#include <cellule_stdio.h>

/*!
 * \file automate_stdio.h
 * \brief Primitives d'affichage d'un automate sur la sortie standard
 */

/*!
 * \fn void automate_print(FILE * stream , automate_t * automate )
 * \brief Affiche l'automate sur la sortie donnée par le paramètre stream
 * \param[in] stream : sortie d'affichage (par exemple stdout)
 * \param[in] automate : automate à afficher
 */

extern void automate_print(FILE * stream , automate_t * automate ) ; 

#endif
