#ifndef _MER_H_
#define _MER_H_

#include <commun.h>
#include <coord.h>
#include <bateau.h>

/* 
 *==================================================
 * Realisation du TDA mer 
 *==================================================
 */

/*
 * Definitions des constantes 
 */

#define MER_TAILLE_CASE sizeof(char)
#define MER_TAILLE_ENTETE (sizeof(int)*3)
#define MER_CASE_LIBRE ' ' 
#define MER_CASE_BOULET '@' 
#define MER_DEBUT_NB_BATEAUX (2*sizeof(int))
#define MER_TAILLE_NB_BATEAUX sizeof(int)

/*
 *  Definition des structures
 */

/*
 *==================================================
 * Primitives du TDA mer 
 *==================================================
 */

/* 
 * Affichage de la mer
 */

extern int mer_afficher( const int ); /* Descripteur fichier mer */

/* 
 * Initialisation de la mer 
 */

extern int mer_initialiser( const char *,	/* Reference du fichier mer */
			    const int,		/* Nb lignes   */
			    const int) ;	/* Nb colonnes */

/* 
 * Lecture du nombre de bateaux dans la mer
 */

extern int mer_nb_bateaux_lire( const int,	/* Descritpteur fichier mer */
				int * );	/* Nombre de bateaux */


/* 
 * Ecriture du nombre de bateaux dans la mer
 */

extern int mer_nb_bateaux_ecrire( const int,	/* Descritpteur fichier mer */
				  const int );	/* Nombre de bateaux */


/*
 * Recherche des cases voisines d'un bateau dans la mer 
 */

extern int mer_voisins_rechercher( const int,		/* Descripteur fichier mer */
				   const bateau_t * const ,		/* Bateau */
				   coords_t **) ;	/* Liste des coordonnees des cases voisines */

/*
 * Affichage du contenu d'une liste de cases dans la mer 
 */

extern void mer_voisins_afficher( const int fd,			/* Fichier mer */
				  coords_t * const liste_cases ) ;


/*
 * Pose aleatoire d'un bateau sur la mer
 * Si la fonction peut trouver de la place pour initialiser le bateau alors:
 * - Retour de la fonction --> CORRECT
 * - Ecriture des positions d'un bateau dans une zone libre de la mer
 * - Ecrit dans le fichier la marque du bateau dans les cases choisies aleatoirement
 * - Met a jour dans la structure bateau les coordonnees de ces cases
 * Sinon :
 * - Retour de la fonction --> ERREUR
 * - Pas d'ecriture dans le fichier mer
 * - Pas d'affectation de la structure bateau 
 */

extern int mer_bateau_initialiser( const int,		/* Fichier mer */
				   bateau_t * );	/* Bateau */

/* 
 * Deplacement d'un bateau sur la mer :
 * - choix aleatoire d'une direction de deplacement dans les cases voisines
 * - ecriture dans les cases des nouvelles positions 
 * - effacement du contenu des cases des anciennes positions
 */

extern int mer_bateau_deplacer( const int,		/* Fichier mer */
				bateau_t *,		/* Bateau a deplacer */
				coords_t * const,	/* Liste des cases voisines du bateau */
				booleen_t * );		/* Indique si le deplacement s'est effectue */


/* 
 * Lecture des dimensions du mer
 */

extern int mer_dim_lire( const int,	/* Descripteur fichier mer */
			 int *,		/* Nombre de lignes */
			 int * );	/* Nombre de colonnes */

/*
 * Conversion de coordonnees [x,y] en position dans le fichier
 */

extern int mer_lc2pos( const int,	/* Descripteur fichier mer */
		       const int,	/* Ligne   dans le tableau mer */  
		       const int,	/* Colonne dans le tableau mer */
		       off_t * );	/* Position dans le fichier mer */


/*
 * Conversion d'une position dans le fichier en coordonnees [x,y]
 */

extern int mer_pos2lc( const int,	/* Descripteur fichier mer */
		       const off_t,	/* Position dans le fichier mer */
		       int *,		/* Ligne  dans le tableau mer */  
		       int *);		/* Colonne dans le tableau mer */

/*
 * Lecture d'une case dans la mer
 */ 

extern int mer_case_lire( const int,		/* Descripteur du fichier mer */
			  const coord_t,	/* Coordonnees de la case a lire */
			  case_t * );		/* Contenu de la case a lire */

/* 
 * Ecriture d'une case dans la mer
 */

extern int mer_case_ecrire( const int,		/* fd fichier mer */
			    const coord_t,	/* coordonnees : [x,y] + position */
			    const case_t) ;	/* contenu de la case */

		   
/* 
 * Acquisition d'une cible par bateau sur la mer 
 * Choix aleatoire d'une case de la mer 
 * - sur laquelle il y a un bateau 
 * - qui ne soit pas celui d'ou vient le coup
 * Si la recherche se passe bien 
 * - retour --> CORRECT 
 * - si une cible est trouvee :
 *   - affectation des coordonnees de la cible (une case de la mer) dans le parametre <cible>
 *   - <acquisition> est a VRAI
 * - si on ne peux acquerir aucune cible 
 *   - <cible> est a NULL
 *   - <acquisition> est a FAUX
 */

extern int mer_bateau_cible_acquerir( const int,	/* Mer */
				      const bateau_t * const ,	/* Bateau */
				      booleen_t *,	/* Cible trouvee ? */
				      coord_t *);	/* Coordonnees de la case choisie */

/* 
 * Envoie du boulet dans une case
 */

extern int  mer_bateau_cible_tirer( const int,
				    const coord_t) ;

/*
 * Verifie si un bateau a ete touche
 */

extern int mer_bateau_est_touche( const int,		/* fd */
				  const bateau_t * const ,		/* bateau */
				  booleen_t * );		/* Touche ? */


/* 
 * Coule/efface un bateau de la mer
 */

extern int mer_bateau_couler( const int,		/* fd */
			      const bateau_t * const		/* bateau */ );
#endif

