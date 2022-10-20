#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <piste.h>

/*
 * Affichage d'une case
 */

extern
void
cell_afficher( const cell_t cellule )
{
  if( cellule.pid ) 
  {
#ifdef _SOLARIS_
    printf( "%c (%l5d)" , cellule.marque , cellule.pid ) ;
#else
       printf( "%c (%5d)" , cellule.marque , cellule.pid ) ;
#endif
  }
  else
       printf( "         " );
}

extern
void
cell_marque_afficher( const cell_t cellule )
{
  if( cellule.pid ) 
    printf( "%c" , cellule.marque ) ;
  else
    printf( "  " );
}

/*
 * Affectation d'une case 
 */

extern
void
cell_pid_affecter( cell_t * cell ,
		   const pid_t pid )
{
     cell->pid = pid ; 
}

extern
void
cell_marque_affecter( cell_t * cell ,
		      const char marque )
{
     cell->marque = marque  ; 
}

/*
 * Lecture d'une case 
 */

extern
pid_t
cell_pid_lire( const cell_t cell )
{
  return(cell.pid) ; 
}

extern
char
cell_marque_lire( const cell_t cell )
{
  return(cell.marque) ; 
}

/*
 * Comparaison de 2 cases 
 * Retour < 0 si p1 < p2  
 *        = 0 si p1 = p2
 *        > 0 si p1 > p2
 */

extern
int
cell_comparer( const cell_t c1 , const cell_t c2 )
{
     int r1 = c1.pid - c2.pid ;
     if( r1 )
	  return( r1 ) ;
     else
	  return( c1.marque - c2.marque ) ;
}

/*
 * Test d'une case libre
 * Retour VRAI si libre
 *        FAUX sinon
 */

extern
booleen_t
cell_libre( const cell_t  cell )
{
  if( cell.pid == 0 ) 
    return(VRAI) ;
  else
    return(FAUX) ;
}

/*
 * Test d'une case occupee
 * Retour VRAI si occupee
 *        FAUX sinon
 */

extern
booleen_t
cell_occupee( const cell_t cell )
{
  if( cell.pid != 0 ) 
    return(VRAI) ;
  else
    return(FAUX) ;
}

