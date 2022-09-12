#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

/* 
 *  Programme principal 
 */

int main( int nb_arg , char * tab_arg[] )
{
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;
  float seuil = 30;
  int no_err = CORRECT ;
  booleen_t ok = VRAI ;
  booleen_t touche = FAUX;
  int nbBat;


  coord_t cible ;
  booleen_t acquisition ;

  /*----------*/

  strcpy( nomprog , tab_arg[0] ) ;

  if( nb_arg != 4 )
    {
      fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n", 
	       nomprog );
      exit(-1);
    }

  if( strlen(tab_arg[2]) !=1 ) 
    {
      fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
	       nomprog , tab_arg[2] );
      exit(-1) ;
    }


  strcpy( fich_mer , tab_arg[1] );
  marque = tab_arg[2][0] ;
  sscanf( tab_arg[3] , "%f" , &energie );
  
  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );


  // INIT
  bateau_t * bateau = NULL;

  bateau = bateau_new(NULL, marque, getpid()); //On creer le bateau

  int fd_mer = open( fich_mer , O_RDWR , 0644 );

  mer_bateau_initialiser(fd_mer, bateau); //Placer le bateau dans l'eau

 while(energie >= 5){
    mer_bateau_est_touche(fd_mer, bateau, &touche);
    if(touche) {
      if (energie >= seuil) printf("Bouclié activé ! Le bateau n'est pas touché");
      else
      {
        printf("J'suis dead...");
        mer_bateau_couler(fd_mer, bateau);
        exit(0);
      }
    }

    mer_nb_bateaux_lire(fd_mer, &nbBat);
    printf("\nNb Bateaux : %d\n", nbBat);
    if(nbBat == 1){
      printf("\n\n");
      bateau_printf( bateau );
      printf("J'AIIIIII GAGNNNNNNEEEEEEEEEEEEEEEEEEEEEEEEEE");

      exit(0);
    }


    //VOISINS
    coords_t * liste_voisins = NULL ;

    if((no_err = mer_voisins_rechercher(fd_mer, bateau, &liste_voisins )))
    {
      fprintf(stderr, "%s : erreur %d dans mer_voisins_rechercher\n", nomprog, no_err );
      exit(no_err) ;
    }

    printf( "Liste des voisins :\n");
    
    coords_printf(liste_voisins);
    printf("\n\n");


    //Verrouilage des voisins

    struct flock verrouDeplacement;

    int nbcoords = coords_nb_get(liste_voisins);
    for(int ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      coord_t coord = coords_coord_get(liste_voisins, ind_coord);

      verrouDeplacement.l_type = F_WRLCK;
      verrouDeplacement.l_whence = 0;
      verrouDeplacement.l_start = coord_position_get(coord);
      verrouDeplacement.l_len = 1;

      fcntl(fd_mer, F_SETLKW, &verrouDeplacement);
    }

    //DEPLACEMENT DU BATEAU
  
 
    if( (no_err = mer_bateau_deplacer(fd_mer, bateau, liste_voisins, &ok)))
    {
      fprintf(stderr, "%s : erreur %d dans mer_bateau_deplacer\n", nomprog, no_err);
      exit(no_err) ;
    }

    if( ok )
    {
      printf( "Deplacement reussi\n");
      energie -= 5;
      printf( "5L de fuel on été uttilisés, reste %fL de fuel\n", energie);
    }
        else
    {
      printf(" Deplacement impossible\n");
    }

    for(int ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      coord_t coord = coords_coord_get(liste_voisins, ind_coord);

      verrouDeplacement.l_type = F_UNLCK;
      verrouDeplacement.l_whence = 0;
      verrouDeplacement.l_start = coord_position_get(coord);
      verrouDeplacement.l_len = 1;

      fcntl(fd_mer, F_SETLKW, &verrouDeplacement);
    }

    //TIRER
      if( (no_err = mer_bateau_cible_acquerir(fd_mer, bateau, &acquisition, &cible )))
        {
          fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_acquerir\n",
            nomprog , no_err );
          exit(no_err) ;
        }

      if( acquisition ) 
        {
          printf("Acquisition d'une cible par le bateau \n");
          bateau_printf( bateau );
          printf( "\n-->La cible choisie est la case ");
          coord_printf( cible );
          printf( "\n\n");
          if( (no_err = mer_bateau_cible_tirer( fd_mer,
              cible)) )
          {
            fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",
              nomprog , no_err );
            exit(no_err) ;
          }
          

          
        }
      else
        {
          printf("Pas d'acquisition de cible pour le bateau \n");
          bateau_printf( bateau );
          printf( "\n");
        }

      
    
    sleep(random()%2+1);
    
  }
  


  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );

  exit(0);
}
