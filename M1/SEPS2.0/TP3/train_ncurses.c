#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <train_ncurses.h>

/*
 * Affichage  train sur stdout 
 */

extern 
void train_marque_wprint( ecran_t * const ecran , const int y , const int x , train_t * const t )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 
  mvwprintw( fenetre , y , x , "%c" , t->marque );
}

extern 
void train_marque_blanc_wprint( ecran_t * const ecran , const int y , const int x )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 
  mvwprintw( fenetre , y , x , " " );
}

extern 
void train_marque_vide_wprint( ecran_t * const ecran , const int y , const int x )
{
  WINDOW * fenetre = ecran_ligne_get(ecran) ; 
  mvwprintw( fenetre , y , x , "." );
}

extern 
void train_wprint( ecran_t * const ecran , const int y , const int x , train_t * const t )
{
  if( ! train_vide( t ) )
    {
      train_marque_wprint( ecran , y , x , t );
      sens_wprint( ecran , y , x+1 , t->sens );
    }
}

extern
void train_blanc_wprint( ecran_t * const ecran , const int y , const int x )
{
  train_marque_blanc_wprint( ecran , y , x );
  sens_blanc_wprint( ecran , y , x+1 );
}

extern
void train_vide_wprint( ecran_t * const ecran , const int y , const int x )
{
  train_marque_vide_wprint( ecran , y , x );
  sens_vide_wprint( ecran , y , x+1 );
}
