#ifndef _COMMUN_H_
#define _COMMUN_H_

#define CORRECT 0
#define ERREUR -1 
#define PAS_TROUVE -2 

#define TEMPS_LONG 10
#define TEMPS_MOYEN 5
#define TEMPS_COURT 1 

#define MESS_LONGUEUR 256 

/* Realisation du TDA booleen */

typedef enum { FAUX , VRAI } booleen_t ;

/* Realisation du TDA case : cellule dans le quadrillage de la mer */

typedef char case_t ;

#define CASE_VIDE ' ' 

#endif
