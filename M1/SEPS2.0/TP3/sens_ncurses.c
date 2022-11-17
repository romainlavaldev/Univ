#include <stdio.h>
#include <sens_ncurses.h>

extern
void sens_wprint( ecran_t * const ecran , const int y , const int x , const sens_t s )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 

  switch( s )
    {
    case OUEST_EST : 
      mvwprintw( fenetre , y , x , "->" ) ;
      break ;
    case EST_OUEST : 
      mvwprintw( fenetre , y , x , "<-" ) ;
      break ;
    default : 
      mvwprintw( fenetre , y , x , "??" ) ;
      break ;
    }
}

extern
void sens_blanc_wprint( ecran_t * const ecran , const int y , const int x )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 
  mvwprintw( fenetre , y , x , "  " ) ;
}

extern
void sens_vide_wprint( ecran_t * const ecran , const int y , const int x )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 
  mvwprintw( fenetre , y , x , ".." ) ;
}
