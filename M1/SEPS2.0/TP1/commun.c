#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <commun.h>

/*
 * Initialisation de l'attente de son tour
 */
extern
void
commun_initialiser_attentes() 
{
  srandom(getpid()) ;
}

/* 
 * Attente entre 2 tours de jeu
 */
extern
void
commun_attendre_tour() 
{
#ifdef _DEBUG_
     unsigned int t = random()%TEMPS_TOUR ;
     printf("Attente tour de %u secondes\n", t) ;
     sleep(t) ;
#else
     sleep(random()%TEMPS_TOUR) ;
#endif

}

/* 
 * Duree du saut entre depart et arrive 
 */
extern
void
commun_attendre_fin_saut() 
{
#ifdef _DEBUG_
     unsigned int t = random()%TEMPS_SAUT ;
     printf("Duree du saut de %u secondes\n", t) ;
     sleep(t) ;
#else
     sleep(random()%TEMPS_SAUT) ;
#endif

}

/* 
 * Coup de De: renvoie un nombre entre 1 et 6 
 */
extern 
int
commun_coup_de_de()
{
  return( (int)(random()%6)+1 );
}

/*
 * Affichage de l'etat 
 */

extern 
void 
commun_afficher_etat( const etat_t etat )
{
  switch( etat ) 
    {
    case EN_COURSE : 
      printf("EN COURSE");
      break ; 
    case ARRIVE : 
      printf("ARRIVE");
      break;
    case DECANILLE :
      printf("DECANILLE");
      break ;
    default :
      printf("<inconnu (%d)>" , etat) ;
      break ; 
    }
}

extern 
char * 
commun_etat2string( const etat_t etat )
{
  switch( etat ) 
    {
    case EN_COURSE : 
      return("EN COURSE");
      break ; 
    case ARRIVE : 
      return("ARRIVE   ");
      break;
    case DECANILLE :
      return("DECANILLE");
      break ;
    default :
      return("<inconnu>") ;
      break ; 
    }
}
