#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <mer.h>


int
main( int nb_arg , char * tab_arg[] )
{
     
  char nomprog[128] ;

  int fd_mer ;
  char fich_mer[128] ;

  int nb_bateaux = 0 ; 

  int no_err = CORRECT ;

  coords_t * liste_voisins = NULL ;

  bateau_t * bateau = NULL ;
  booleen_t ok = VRAI ;

  int b ;

  coord_t cible ;
  booleen_t acquisition ;

  /*----------*/

  if( nb_arg != 3 )
    {
      fprintf( stderr , "Usage : %s <nom fichier mer> <nb bateaux>\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  strcpy( nomprog , tab_arg[0] );
  strcpy( fich_mer , tab_arg[1] ) ;
  nb_bateaux = atoi(tab_arg[2] ) ; 
     
  /* 
   * Ouverture fichier mer
   */

  if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 )
    {
      fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_mer);
      exit(-1);
    }

  printf(" Mer initiale: \n");

  if( (no_err = mer_afficher(fd_mer) )) 
    {
      fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
	       nomprog , no_err );
      exit(no_err) ;
    }
     
     
  srandom(getpid()) ;

  for( b=0 ; b < nb_bateaux ; b++ ) 
    {
	 
      /* 
       * Test initialisation des bateaux 
       */
      bateau = bateau_new( NULL , 
			   'A'+b , 
			   100+b ) ;

      if( (no_err = mer_bateau_initialiser( fd_mer , 
					    bateau)) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_bateau_initialiser\n",
		   nomprog , no_err );
	  if( no_err == ERREUR )
	    {
	      fprintf( stderr, "\t(mer_bateau_initialiser n'a pas pu placer le bateau \"%c\" dans la mer)\n" ,
		       bateau_marque_get(bateau) );
	    }
	  exit(no_err) ;
	}
     
      if( (no_err = mer_afficher(fd_mer) )) 
	{
	  fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
		   nomprog , no_err );
	  exit(no_err) ;
	}

      /* 
       * Test deplacement des bateaux 
       */

      if( (no_err = mer_voisins_rechercher( fd_mer,
					    bateau,
					    &liste_voisins )) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_voisins_rechercher\n",
		   nomprog , no_err );
	  exit(no_err) ;
	}

      printf( "Liste des voisins :\n");
      coords_printf( liste_voisins );
      printf("\n\n");

      if( (no_err = mer_bateau_deplacer( fd_mer,
					 bateau,
					 liste_voisins,
					 &ok )) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_bateau_deplacer\n",
		   nomprog , no_err );
	  exit(no_err) ;
	}

      coords_destroy(&liste_voisins); 
	
      if( ok )
	{
	  printf( "Deplacement reussi\n");
	}
      else
	{
	  printf(" Deplacement impossible\n");
	}
	  

      if( (no_err = mer_afficher(fd_mer) )) 
	{
	  fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
		   nomprog , no_err );
	  exit(no_err) ;
	}

      if( b > 1 )
	{
	  /* 
	   * Test de tir 
	   */

	  if( (no_err = mer_bateau_cible_acquerir( fd_mer,
						   bateau,
						   &acquisition,
						   &cible )) )
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
	    }
	  else
	    {
	      printf("Pas d'acquisition de cible pour le bateau \n");
	      bateau_printf( bateau );
	      printf( "\n");
	    }

	  if( (no_err = mer_bateau_cible_tirer( fd_mer,
						cible)) )
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",
		       nomprog , no_err );
	      exit(no_err) ;
	    }
	       
	  if( (no_err = mer_afficher(fd_mer) )) 
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
		       nomprog , no_err );
	      exit(no_err) ;
	    }
	}
	  
    }

  close(fd_mer); 

  exit(0);

}
