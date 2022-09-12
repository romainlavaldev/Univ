#ifndef _COORDS_H_
#define _COORDS_H_

/*
 * Definition d'une liste de coords 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <coord.h>

/*
 * Type
 */

typedef struct coords_s
{
  int nb ;
  coord_t * coords ;
} coords_t ;

/*
 * Methodes set/get
 */


/*! Acces au nombre de coords dans la liste */
extern int coords_nb_get( const coords_t * const l );
/*! Acces a une coord dans la liste */
extern coord_t coords_coord_get( const coords_t * const l  , const int ind_coord );
/* 
 * Affectation d'une coord dans une liste de coords 
 * La position du coord doit exister
 * L'ancienne valeur du coord est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern int coords_coord_set( coords_t * const liste_coords , 
			     const int ind_coord , 
			     const coord_t coord )  ;

/* 
 * Primitives 
 */

/*
 * Creation d'une liste de coords
 * Stockage direct des Les elements coord_t 
 */
extern coords_t * coords_new() ;

/*
 *  Destruction d'une liste de coords 
 */

extern int coords_destroy( coords_t ** liste_coords ) ;

/*!
 * Affichage d'une liste de coords 
 */
/* - sur la sortie standard */
extern void coords_printf( const coords_t * const liste_coords );
/* - dans un fichier */ 
extern void coords_fprintf( FILE * restrict stream , const coords_t * const liste_coords ) ;

/* 
 * Copie d'une liste de coordonnees
 */
extern int coords_copier( coords_t ** coords_cible,
			  const coords_t * const coords_source ) ;
/* 
 * Ajout d'une coord dans une liste de coords 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern int coords_coord_add( coords_t * const liste_coords , 
			     const coord_t coord ) ;

/* 
 * Deletion d'une coord dans une liste de coords 
 */
extern int coords_coord_del( coords_t * const liste_coords , 
			 const int ind_coord )  ;

/*
 * Methodes sauvegarde/restauration
 */

/*!
 * Chargement d'une liste de coords a partir d'un fichier 
 * Le descripteur "fd" doit correspondre a un fichier ouvert en lecture
 * la liste "liste_coords" est creee 
 */
extern 
int coords_read(  const int fd ,  /* descripteur fichier de restauration */
		  coords_t ** liste_coords ) ; /* structure liste coords a charger */

/*!
 * Ecriture du contenu d'une liste de coords dans un fichier
 * Le descripteur doit coorespondre a un fichier ouvert en ecriture
 */
extern 
int coords_write(  const int fd ,  /* descripteur fichier de restauration */
		   const coords_t * const liste_coords ) ; /* structure liste coords a charger */

/*
 * Methode de recherche d'un element 
 */

/*
 * Recherche d'une coord dans une liste de coords 
 * Valeur retournee : indice du premier coord trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int coords_coord_seek( const coords_t * const liste_coords,
		       const coord_t coord ,
		       int (*comparer) (const coord_t , const coord_t) ) ;

#endif


