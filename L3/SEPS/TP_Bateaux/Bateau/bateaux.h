#ifndef _BATEAUX_H_
#define _BATEAUX_H_

/*
 * Definition d'une liste de bateaux 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <bateau.h>

/*
 * Type
 */

typedef struct bateaux_s
{
  int nb ;
  bateau_t ** bateaux ;
} bateaux_t ;

/*
 * Methodes set/get
 */


/*! Acces au nombre de bateaux dans la liste */
extern int bateaux_nb_get( const bateaux_t * const liste_bateaux );
/*! Acces a un bateau dans la liste */
extern bateau_t * bateaux_bateau_get( const bateaux_t * const liste_bateaux  , const int ind_bateau );
/* 
 * Affectation d'un bateau dans une liste de bateaux 
 * La position du bateau doit exister
 * L'ancienne valeur du bateau est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans bateau_t
 */
extern int bateaux_bateau_set( bateaux_t * const liste_bateaux , 
			       const int ind_bateau , 
			       const bateau_t * const bateau )  ;

/* 
 * Primitives 
 */

/*
 * Creation d'une liste de bateaux
 * Stockage direct des Les elements bateau_t 
 */
extern bateaux_t * bateaux_new() ;

/*
 *  Destruction d'une liste de bateaux 
 */

extern int bateaux_destroy( bateaux_t ** liste_bateaux ) ;

/*!
 * Affichages d'une liste de bateaux 
 */

/* - sur la sortie standard */ 
extern void bateaux_printf( const bateaux_t * const liste_bateaux );

/* - dans un fichier */
extern void bateaux_fprintf( FILE * restrict stream , const bateaux_t * const liste_bateaux ) ;

/* 
 * Ajout d'un bateau dans une liste de bateaux 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans bateau_t
 */
extern int bateaux_bateau_add( bateaux_t * const liste_bateaux , 
			       const bateau_t * const bateau ) ;

/* 
 * Deletion d'un bateau dans une liste de bateaux 
 */
extern int bateaux_bateau_del( bateaux_t * const liste_bateaux , 
			       const int ind_bateau )  ;

/*
 * Methodes sauvegarde/restauration
 */

/*!
 * Chargement d'une liste de bateaux a partir d'un fichier 
 */
extern int bateaux_load( bateaux_t ** liste_bateaux  , /* structure liste bateaux a charger */
			 char * nom_fichier ) ;  /* fichier de restauration */


/*!
 * Ecriture du contenu d'une liste de bateaux dans un fichier
 */

extern int bateaux_save( const bateaux_t * const liste_bateaux  ,  /* structure liste bateaux a saubateau */
			 char * nom_fichier ) ;   /* fichier de sauvegarde */


/*
 * Methode de recherche d'un element 
 */

/*
 * Recherche d'un bateau sur son pid 
 * Valeur retournee : indice du bateau dans la liste si il existe  
 *                    -1 sinon 
 */

extern int bateaux_pid_seek( const bateaux_t * const liste_bateaux,
			     const pid_t pid_bateau ) ;

/*
 * Recherche d'un bateau sur sa marque
 * Valeur retournee : indice du premier bateau trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern int bateaux_marque_seek( const bateaux_t * const liste_bateaux,
				const case_t marque_bateau ) ;

/*
 * Recherche d'un bateau sur une coord de son corps 
 * Valeur retournee : indice du premier bateau trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern int bateaux_coord_seek( const bateaux_t * const liste_bateaux,
			       const coord_t coord ) ;

#endif


