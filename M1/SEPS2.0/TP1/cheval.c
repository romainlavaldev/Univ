#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <commun.h>
#include <liste.h>
#include <piste.h>

int 
main( int nb_arg , char * tab_arg[] )
{     

  int cle_piste;
  piste_t * piste = NULL;

  int cle_liste;
  liste_t * liste = NULL ;

  char marque;

  booleen_t fini = FAUX ;
  piste_id_t deplacement = 0 ;
  piste_id_t depart = 0 ;
  piste_id_t arrivee = 0 ;

  
  cell_t cell_cheval ;


  elem_t elem_cheval ;



  /*-----*/

  if( nb_arg != 4 )
    {
      fprintf( stderr, "usage : %s <cle de piste> <cle de liste> <marque>\n" , tab_arg[0] );
      exit(-1);
    }
  
  if( sscanf( tab_arg[1] , "%d" , &cle_piste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de piste (%s)\n" , 
	       tab_arg[0]  , tab_arg[1] );
      exit(-2);
    }


  if( sscanf( tab_arg[2] , "%d" , &cle_liste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de liste (%s)\n" , 
	      tab_arg[0]  , tab_arg[2] );
      exit(-2);
    }

  if( sscanf( tab_arg[3] , "%c" , &marque) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise marque de cheval (%s)\n" , 
	       tab_arg[0]  , tab_arg[3] );
      exit(-2);
    }
     

  marque = *tab_arg[3];

  /* Init de l'attente */
  commun_initialiser_attentes() ;


  /* Init de la cellule du cheval pour faire la course */
  cell_pid_affecter( &cell_cheval  , getpid());
  cell_marque_affecter( &cell_cheval , marque );

  /* Init de l'element du cheval pour l'enregistrement */
  elem_cell_affecter(&elem_cheval , cell_cheval ) ;
  elem_etat_affecter(&elem_cheval , EN_COURSE ) ;

  /* Recuperation ressources partagés */
  cle_piste = atoi(tab_arg[1]);
  int pisteId = shmget(cle_piste, sizeof(piste_t), 0666);
  piste = shmat(pisteId, NULL, 0);

  cle_liste = atoi(tab_arg[2]);
  int listeId = shmget(cle_liste, sizeof(liste_t), 0666);
  liste = shmat(listeId, NULL, 0);

  /* Recuperation du semaphore liste*/
  int listeSemId = semget(cle_liste, 1, 0666);

  /* Recuperation du semaphore piste*/
  int pisteSemId = semget(cle_piste, PISTE_LONGUEUR, 0666);

  /* 
   * Enregistrement du cheval dans la liste
   */

  struct sembuf op;
  op.sem_num = 1;
  op.sem_op = -1;
  op.sem_flg = 0;
  
  /*Réservation de la ressource liste*/
  semop(listeSemId, &op, 1);
  liste_elem_ajouter(liste, elem_cheval);

  /*Libération de la ressource liste*/
  op.sem_op = 1;
  semop(listeSemId, &op, 1);

  while( ! fini )
    {
      /* Attente entre 2 coup de de */
      commun_attendre_tour() ;

      /* 
       * Verif si pas decanille 
       */
      if (elem_etat_lire(elem_cheval) == DECANILLE){
        fini = VRAI;
        break;
        printf("je suis decanillé");
      }

      /*Blocage de la case actuelle jusqu'a la fin du deplacement*/
      op.sem_num = depart;
      op.sem_op = -1;
      semop(pisteSemId, &op, 1);

      /*
       * Avancee sur la piste
       */

      /* Coup de de */
      deplacement = commun_coup_de_de() ;
#ifdef _DEBUG_
      printf(" Lancement du De --> %d\n", deplacement );
#endif

      arrivee = depart+deplacement ;

      if( arrivee > PISTE_LONGUEUR-1 )
	{
	  arrivee = PISTE_LONGUEUR-1 ;
	  fini = VRAI ;
	}

      if( depart != arrivee )
	{

	  /* 
	   * Si case d'arrivee occupee alors on decanille le cheval existant 
	   */

    /*On attend que la case d'arrivé soit libre et on la prend pour decaniller si besoin*/
    op.sem_num = arrivee;
    op.sem_op = -1;
    semop(pisteSemId, &op, 1);


    
    if (piste_cell_occupee(piste, arrivee) == VRAI){
      /*Blocage de la liste pour modification de l'état*/
      op.sem_num = 1;
      op.sem_op = -1;
      semop(listeSemId, &op, 1);

      struct cell_s c;
      piste_cell_lire(piste, arrivee, &c);
      liste_elem_decaniller(liste, cell_pid_lire(c));

       /*Délocage de la liste*/
      op.sem_op = 1;
      semop(listeSemId, &op, 1);
    }

	  /* 
	   * Deplacement: effacement case de depart, affectation case d'arrivee 
	   */

    struct cell_s cA;
    
    struct cell_s cD;
    piste_cell_affecter(piste, depart, cD);

    cA.pid = getpid();
    cA.marque = marque;
    piste_cell_affecter(piste, arrivee, cA);

    /*Liberation des cases*/
    op.sem_num = depart;
    op.sem_op = 1;
    semop(pisteSemId, &op, 1);

    op.sem_num = arrivee;
    op.sem_op = 1;
    semop(pisteSemId, &op, 1);

#ifdef _DEBUG_
	  printf("Deplacement du cheval \"%c\" de %d a %d\n",
		 marque, depart, arrivee );
#endif

	  
	} 
      /* Affichage de la piste  */
      piste_afficher_lig( piste );
     
      depart = arrivee ;
    }

  printf( "Le cheval \"%c\" A FRANCHIT LA LIGNE D ARRIVEE\n" , marque );

 
     
  /* 
   * Suppression du cheval de la liste 
   */

  /*Blocage de la liste pour se retirer*/
      op.sem_num = 1;
      op.sem_op = -1;
      semop(listeSemId, &op, 1);

      liste_elem_supprimer(liste, getpid());


      op.sem_num = arrivee;
      op.sem_op = -1;
      semop(pisteSemId, &op, 1);

      struct cell_s c;
      piste_cell_affecter(piste, arrivee, c);

      op.sem_num = arrivee;
      op.sem_op = 1;
      semop(pisteSemId, &op, 1);

       /*Délocage de la liste*/
      op.sem_op = 1;
      semop(listeSemId, &op, 1);
  
  exit(0);
}
