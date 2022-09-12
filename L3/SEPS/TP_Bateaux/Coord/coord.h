#ifndef _COORD_H_
#define _COORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <commun.h> 


/* 
 *===================================================
 * Realisation du TDA coord (coordonnees d'une case) 
 *=================================================== 
 */

typedef struct coord_s
{
     int l ;		/* numero ligne   */
     int c ;		/* numero colonne */
     off_t pos ;	/* position dans le fichier */
} coord_t ;

/*
 * Definitions des constantes 
 */
 
#define COORD_VIDE coord_vide() 

/* Sous-type direction */

typedef enum { NORD , EST , SUD , OUEST } direction_t ;

/* Sous-type orientation */

typedef enum { VERTICAL , HORIZONTAL } orientation_t ;

/*
 * Fonctions get/set des attributs d'une coordonnee
 *=================================================
 */

extern coord_t coord_vide() ; 

extern int coord_ligne_get( const coord_t c ) ;
extern int coord_ligne_set( coord_t * const c , 
			    const int ligne );
extern int coord_colonne_get( const coord_t c );
extern int coord_colonne_set( coord_t * const c , 
			      const int colonne ) ;

extern off_t coord_position_get( const coord_t c ) ;
extern int coord_position_set( coord_t * const c , 
			       const off_t position ) ;

extern int coord_set( coord_t * const coord , 
		      const int ligne,
		      const int colonne,
		      const off_t position ) ;

extern int coord_get( const coord_t coord , 
		      int * ligne,
		      int * colonne,
		      off_t * position ) ;

/* 
 * Affichages
 */

extern void coord_printf( const coord_t coord ) ;
extern void coord_fprintf( FILE * restrict stream, const coord_t coord ) ; 

/*
 * Ecriture dans un fichier 
 */
extern int coord_write( const int fd , /* Descriteur du fichier */
			const coord_t coord ) ;

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture 
 * le parametre "coord" doit pointer sur une zone suffisante pour stocker une coord_t 
 */
extern
int coord_read( const int fd , /* Descriteur du fichier */
		coord_t * const coord ) ;

/* 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */

/* Comparaison globale */
extern int coord_comparer( const coord_t c1,
			   const coord_t c2 ) ;

/* Comparaison sur ligne/colonne */
extern int coord_xy_comparer( const coord_t c1,
			      const coord_t c2 ) ;

/* Comparaison sur offset (position dans le fichier) */

extern int coord_pos_comparer( const coord_t c1,
			       const coord_t c2 ) ;

/* 
 * Affectation des coordonnees d'une case 
 */

extern int coord_copier( coord_t * const coord_cible,
			 const coord_t coord_source ) ;


/* 
 * Determination de l'orientation de 2 coordonnees
 */

extern orientation_t coord_orientation_donner( const coord_t c1 ,
					       const coord_t c2 ) ;

/*
 *===========================================
 * Realisations des primitives des sous-types
 *===========================================
 */

/* Transformation d'une orientation en chaine de caracteres */
extern char * coord_ori2string( const orientation_t ori ) ;

/* Transformation d'une direction en chaine de caracteres */
extern char * coord_dir2string( const direction_t dir ) ;


#endif
