#include <stdio.h>
#include <elem.h>
#include <sys/sem.h>

/* Fonctions d'affections */

extern 
void 
elem_cell_affecter( elem_t * elem,
		    const cell_t cell )
{
  elem->cell = cell ; /* en C ANSI */
}

extern
void
elem_etat_affecter( elem_t * elem ,
		    const etat_t etat )
{
     elem->etat = etat ; 
}

extern 
int
elem_sem_creer( elem_t * elem )
{
  char msgerr[265] ;

  /* Creation La cle externe ens. semaphore = pid du cheval */
  int cle = cell_pid_lire(elem_cell_lire( (*elem) )) ;

  /* Creation ensemble de semaphores*/
  if( ( elem->sem = semget( cle , 1 , IPC_CREAT | 0666 )) == -1 )
    {
      sprintf( msgerr , "elem_sem_creer: Pb sur semget avec cle = %d" , cle );
      perror(msgerr);
      return(-1);
    }

  /* Semaphore individuel numero 0 <-- 1 */
  if( semctl( elem->sem , 0 , SETVAL , (int)1 ) == -1 )
    {
      sprintf( msgerr , "elem_sem_creer: Pb sur semctl\ncle externe= %d\noperation SETVAL\nvaleur 1" , cle );
      perror(msgerr);
      return(-1);
    }

  return(0) ;
}

extern 
int
elem_sem_verrouiller( elem_t * elem )
{
  struct sembuf op_P = { 0 , -1 , SEM_UNDO };

  if( semop(  elem->sem , &op_P , 1 ) == -1 )
  {
    perror("elem_sem_verrouiller: Pb semop " );
    return(-1);
  }

  return(0) ;
}

extern 
int
elem_sem_deverrouiller( elem_t * elem )
{
  struct sembuf op_V = { 0 , +1 , SEM_UNDO };
  
  if( semop(  elem->sem , &op_V , 1 ) == -1 )
  {
    perror("elem_sem_deverrouiller: Pb semop " );
    return(-1);
  }

  return(0) ;
}


extern 
int
elem_sem_detruire( elem_t * elem )
{

  /* Destruction ensemble de semaphores*/
  if( semctl( elem->sem , 0 , IPC_RMID , 0 ) == -1 )
    {
      perror("elem_sem_detruire: Pb semctl " );
      return(-1);
    }

  return(0) ;
}

/* Fonctions de lectures */

/* - des infos */
extern 
cell_t
elem_cell_lire( const elem_t elem )
{
  return(elem.cell) ;
}

/* - de l'etat */
extern
etat_t
elem_etat_lire( const elem_t elem )
{
  return(elem.etat) ; 
}

/* - du semaphore */
extern 
int 
elem_sem_lire( const elem_t elem )
{
  char msgerr[256];
  int val ;
  if( (val = semctl( elem.sem , 0 , GETVAL )) == -1 )
    {
      sprintf( msgerr , "elem_sem_lire: Pb semctl avec cellule [%c,%d] --> %d\n, operation GETVAL\n" ,
	       cell_marque_lire(elem_cell_lire(elem)) , 
	       cell_pid_lire(elem_cell_lire(elem)) ,
	       val ) ;
      perror(msgerr);
      return(-1);
    }

  return(val) ;
}

/* Fonctions d'affichage */

extern 
void
elem_afficher( const elem_t elem )
{
  cell_afficher( elem.cell ) ;
  printf(" ") ;
  commun_afficher_etat( elem.etat ) ;
}

/*
 * Test d'un element decanille
 * Retour VRAI si decanille 
 *        FAUX sinon
 */

extern
booleen_t
elem_decanille( const elem_t  elem )
{
  if( elem.etat == DECANILLE ) 
    return(VRAI) ;
  else
    return(FAUX) ;
}


/*
 * Comparaison de 2 elements e1 et e2
 * retour < 0 si e1 < e2
 *        = 0 si e1 = e2
 *        > 0 si e1 > e2 
 */

extern 
int
elem_comparer( const elem_t e1 , const elem_t e2 ) 
{
  return( cell_comparer( e1.cell , e2.cell ) ) ;
}
