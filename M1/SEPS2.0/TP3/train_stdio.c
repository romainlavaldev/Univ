#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <train_stdio.h>

/*
 * Affichage  train sur stdout 
 */

extern 
void train_marque_print( train_t * const t )
{
     printf( "%c" , t->marque );
}

extern 
void train_marque_blanc_print()
{
     printf( " " );
}

extern 
void train_marque_vide_print()
{
     printf( "." );
}

extern 
void train_print( train_t * const t )
{
     
     if( ! train_vide( t ) )
     {
	  train_marque_print( t );
	  sens_print( t->sens );
	  printf(" ");
     }
}

extern
void train_blanc_print( )
{
     train_marque_blanc_print();
     sens_blanc_print();
     printf(" ");
}

extern
void train_vide_print( )
{
     train_marque_vide_print();
     sens_vide_print();
     printf(".");
}
