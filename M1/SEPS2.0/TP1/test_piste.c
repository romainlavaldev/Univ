#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <commun.h>
#include <cell.h>
#include <piste.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
  piste_t * piste = (piste_t *)malloc( sizeof(piste_t) ) ;
  cell_t cheval ;

  /*-----*/

  /* Initialisation de l'attente de son tour */
  commun_initialiser_attentes() ;

  /* Initialisation de la piste (effacement de tous les chevaux) */
  printf(" Initialisation de la piste:\n");
  piste_initialiser( piste );
  /*piste_afficher_col( piste );*/
  piste_afficher_lig( piste );

  /* Bloc test deplacement */
  {
    int deplacement = 0 ;
    int depart = 0 ;
    int arrivee = 0 ;


    cell_pid_affecter( &cheval , getpid() );
    cell_marque_affecter( &cheval , 'X' );

    while( arrivee<PISTE_LONGUEUR ) 
      {
	/* Attente entre 2 coup de de */
	commun_attendre_tour() ;

	/* Coup de de */
	deplacement = commun_coup_de_de() ;
	printf(" Lancement de --> %d\n", deplacement ),
	arrivee = depart+deplacement ;

	if( arrivee > PISTE_LONGUEUR )
	  {
	    arrivee = PISTE_LONGUEUR ;
	  }

	/* Deplacement d'un cheval */
#ifdef _SOLARIS_
	printf("Deplacement du cheval (\"%c\" %ld) de %d a %d\n",
	       cell_marque_lire( cheval ),  cell_pid_lire( cheval ), 
	       depart, arrivee );
#else
	printf("Deplacement du cheval (\"%c\" %d) de %d a %d\n",
	       cell_marque_lire( cheval ),  cell_pid_lire( cheval ), 	       
	       depart, arrivee );
#endif
	piste_cell_effacer( piste , depart) ;
	commun_attendre_fin_saut() ;
	piste_cell_affecter( piste , arrivee , cheval );

	/* piste_afficher_col( piste );*/
	piste_afficher_lig( piste );

	depart = arrivee ;
      }

    piste_cell_effacer( piste , arrivee) ;
  } /* Fin bloc */
  
  exit(0);
}
