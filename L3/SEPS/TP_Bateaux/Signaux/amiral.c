/*
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ;
bateaux_t* listeBateaux;
int energie[256];
char derniereMarque = '@';
int fdMer;
int no_err = CORRECT ;
/*
 * FONCTIONS LOCALES
 */

void handlerDeplacement(int sig, siginfo_t *info, void *context){

     //Récuperation pid (identifiant du bateau)
     pid_t pid = info->si_pid;
     printf("pid : %d\n", pid);


     //On fouille la liste de bateaux avec l'identifiant
     int indBateau = bateaux_pid_seek(listeBateaux, pid);
     printf("indice du bateau : %d\n", indBateau);


     if(indBateau == -1){

          //Ajout nouveau bateau
          bateau_t* bateau = bateau_new(NULL, ++derniereMarque, pid);
          mer_bateau_initialiser(fdMer, bateau);
          bateaux_bateau_add(listeBateaux, bateau);
     }
     //bateaux_printf(listeBateaux);

     //On fouille la liste de bateaux avec l'identifiant
     indBateau = bateaux_pid_seek(listeBateaux, pid);
     printf("indice du bateau : %d\n", indBateau);

     bateau_t* b = bateaux_bateau_get(listeBateaux, indBateau);

     if (b->marque == '0')
          return;

     //Check bateau mort
     booleen_t touche;
     mer_bateau_est_touche(fdMer, b, &touche);
     if(touche) {
          
          printf("J'suis dead...");
          mer_bateau_couler(fdMer, b);
          b->marque = '0';
    }


     //Deplacement du bateau

          //VOISINS
          coords_t * liste_voisins = NULL ;

          if((no_err = mer_voisins_rechercher(fdMer, b, &liste_voisins )))
          {
               fprintf(stderr, "%d : erreur %d dans mer_voisins_rechercher\n", pid, no_err );
               exit(no_err) ;
          }

          printf( "Liste des voisins :\n");
          
          coords_printf(liste_voisins);
          printf("\n\n");


          booleen_t ok;
          if( (no_err = mer_bateau_deplacer(fdMer, b, liste_voisins, &ok)))
          {
               fprintf(stderr, "%d : erreur %d dans mer_bateau_deplacer\n", pid, no_err);
               exit(no_err) ;
          }

          if( ok )
          {
               printf( "Deplacement reussi\n");
          }
               else
          {
               printf(" Deplacement impossible\n");
          }
}

void handlerTir(int sig, siginfo_t *info, void *context){

     //Récuperation pid (identifiant du bateau)
     pid_t pid = info->si_pid;
     printf("pid : %d\n", pid);

     //On fouille la liste de bateaux avec l'identifiant
     int indBateau = bateaux_pid_seek(listeBateaux, pid);
     printf("indice du bateau : %d\n", indBateau);

     bateau_t* b = bateaux_bateau_get(listeBateaux, indBateau);

     if (b->marque == '0')
               return;
     //TIRER 

     booleen_t acquisition ;
     coord_t cible ;
     if( (no_err = mer_bateau_cible_acquerir(fdMer, b, &acquisition, &cible ))){

          fprintf( stderr, "%d : erreur %d dans mer_bateau_cible_acquerir\n",
          pid , no_err );
          exit(no_err) ;
     }

     if( acquisition ) {

          printf("Acquisition d'une cible par le bateau \n");
          bateau_printf( b );
          printf( "\n-->La cible choisie est la case ");
          coord_printf( cible );
          printf( "\n\n");
          if( (no_err = mer_bateau_cible_tirer( fdMer,
               cible)) )
          {
               fprintf( stderr, "%d : erreur %d dans mer_bateau_cible_tirer\n",
               pid , no_err );
               exit(no_err) ;
          }
     }
     else{
          printf("Pas d'acquisition de cible pour le bateau \n");
          bateau_printf( b );
          printf( "\n");
     }

}

int main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;

     /*----------*/

     /*
      * Capture des parametres
      */

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> \n",
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );

     /*
      * Affichage pid bateau amiral
      */

     printf(" PID bateau amiral = %d\n" , getpid() ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());


     
     listeBateaux = bateaux_new();

     //Ouverture du fichier mer
     strcpy( fich_mer , tab_arg[1] );
     fdMer = open( fich_mer , O_RDWR , 0644 );



     //Redirection signaux
     struct sigaction leSigaction;

     sigemptyset(&leSigaction.sa_mask);

     sigaddset(&leSigaction.sa_mask, SIGUSR1);
     sigaddset(&leSigaction.sa_mask, SIGUSR2);
     leSigaction.sa_flags = SA_SIGINFO;

     //Redirection pour création + déplacement
     leSigaction.sa_handler = handlerDeplacement;
     sigaction(SIGUSR1, &leSigaction, NULL);
     
     //Redirection pour Tir
     leSigaction.sa_handler = handlerTir;
     sigaction(SIGUSR2, &leSigaction, NULL);





     //JEU
     while(1);



     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}
