#ifndef _COMMUN_H_
#define _COMMUN_H_

#define TEMPS_TOUR 5 
#define TEMPS_SAUT 2

/* Definition des types de base */

typedef enum booleen_s { FAUX , VRAI } booleen_t ; 
typedef enum etat_s { EN_COURSE , ARRIVE , DECANILLE } etat_t ; 

/* Initialisation de l'attente de son tour */
extern void
commun_initialiser_attentes() ;

/* Attente entre 2 coup de de */
extern void
commun_attendre_tour() ;

/* Duree du saut entre depart et arrive */
extern void
commun_attendre_fin_saut() ;

/* Coup de De: renvoie un nombre entre 1 et 6 */
extern int 
commun_coup_de_de() ;


/* Affichage de l'etat */
extern void commun_afficher_etat( const etat_t etat ) ; 
extern char * commun_etat2string( const etat_t etat ) ;

#endif
