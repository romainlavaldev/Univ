#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <cell.h>
#include <piste.h>

/*
 * Affectation d'une case de la piste 
 */

extern
void
piste_cell_affecter( piste_t * piste ,
		     const piste_id_t indice,
		     const cell_t cell )
{
  piste->cell[indice] = cell ; 
}

/*
 * Lecture d'une case de la piste 
 */

extern
int
piste_cell_lire( piste_t * piste ,
		 const piste_id_t indice,
		 cell_t * cell )
{
  (*cell) = piste->cell[indice] ; 

  return(1);
}

/*
 * Test d'une case libre
 * Retour VRAI si libre
 *        FAUX sinon
 */

extern
booleen_t
piste_cell_libre( piste_t * piste ,
		  const piste_id_t indice)
{
  return( cell_libre(piste->cell[indice]) ) ;
}

/*
 * Test d'une case occupee
 * Retour VRAI si occupee
 *        FAUX sinon
 */

extern
booleen_t
piste_cell_occupee( piste_t * piste ,
		    const piste_id_t indice)
{
  return( cell_occupee(piste->cell[indice]) ) ;
}

/*
 * Effacement d'une case de la piste 
 */

extern
void
piste_cell_effacer( piste_t * piste ,
		    const piste_id_t indice)
{
  cell_pid_affecter( &(piste->cell[indice]) , 0 ) ; 
}

/* 
 * Affichage de la piste
 */

extern
void
piste_afficher_lig( piste_t * const piste )
{
  piste_id_t i ;
  
  /*----------*/
  
  printf("\n-*-" ) ; for( i=PISTE_LONGUEUR ; i > 0; i--) printf("--") ; printf("*--\n" );

  if( piste != (piste_t *)NULL ) 
    {
      printf(" | " ) ;
      for( i=PISTE_LONGUEUR  ; i>0 ; i-- )
	{
	  cell_marque_afficher( piste->cell[i-1] ) ;
	}
      printf("   \n" ) ;
    }

  printf("-*-" ) ; for( i=PISTE_LONGUEUR ; i > 0; i--) printf("--") ; printf("*--\n\n" );
 }

extern
void
piste_afficher_col( piste_t * const piste )
{
  piste_id_t i ;
  
  /*----------*/
  
  printf("\t*-----*----------*\n");
  printf("\t|     |  Chevaux |\n");
  printf("\t*-----*----------*\n");
  for( i=0 ; i<PISTE_LONGUEUR ; i++ )
    {
      printf("\t| %3d |" , i ) ;
      cell_afficher( piste->cell[i] ) ;
      printf(" |\n");
    }
  printf("\t*-----*----------*\n\n");
 }

/*
 * Initialisation de la piste 
 */

extern 
int
piste_initialiser( piste_t * piste )
{
  piste_id_t i ;

  for( i=0 ; i<PISTE_LONGUEUR ; i++ )
  {
       cell_pid_affecter( &(piste->cell[i]) , 0 );
  }
  return( 1 ) ;
}



/*
 * Comparaison de 2 pistes p1 et p2
 * Retour < 0 si p1 < p2  
 *        = 0 si p1 = p2
 *        > 0 si p1 > p2
 */
extern
int
piste_comparer( piste_t * const p1 , piste_t * const p2 ) 
{
     piste_id_t i ;

     i=0;
     while( (i<PISTE_LONGUEUR) && (cell_comparer(p1->cell[i],p2->cell[i]) == 0)  )
	  i++;

     if( i>= PISTE_LONGUEUR )
	  return(0) ;
     else
	  return( cell_comparer(p1->cell[i],p2->cell[i]) ) ;
}


/* 
 * Affectation d'une piste : p1 <-- p2
 * p1 doit etre creee avant l'appel a cette fonction 
 */

extern
void
piste_affecter( piste_t * p1 , piste_t * const p2 )
{
     piste_id_t i ;
     
     for( i=0 ; i<PISTE_LONGUEUR ; i++ )
	  p1[i] = p2[i];
}
