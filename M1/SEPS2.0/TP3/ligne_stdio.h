#ifndef _LIGNE_STDOUT_H_
#define _LIGNE_STDOUT_H_

#include <voie_unique_stdio.h>
#include <ligne.h>

/* 
 * Affichage de la structure d'une ligne 
 */
extern void ligne_mapper( const ligne_t * const ligne ) ;

/*
 * Affichage d'une ligne 
 */
extern void ligne_print( const ligne_t * const ligne ) ;

#endif

