#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <mer.h>


int
main( int nb_arg , char * tab_arg[] )
{
     int no_err = 0 ;
     char fich_mer[256] ;
     char nomprog[128] ;
     int nb_lig = 0 ;
     int nb_col = 0 ;

     /*----------*/

     if( nb_arg != 4 )
     {
	  fprintf( stderr , "Usage : %s <nom fichier mer> <nombre lignes> <nombre colonnes>\n",
		   tab_arg[0] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );
     sscanf( tab_arg[2] , "%d" , &nb_lig );
     sscanf( tab_arg[3] , "%d" , &nb_col );

#ifdef _DEBUG_
     printf( "%s --> Initialisation de %s[%d,%d]\n",
	     nomprog , fich_mer, nb_lig, nb_col) ;
#endif
     /*
      * Creation mer 
      */

     if( (no_err = mer_initialiser( fich_mer,nb_lig,nb_col)) )
     {
	  fprintf( stderr, "%s : erreur %d dans mer_initialiser : impossible de creer %s[%d,%d]\n",
		   nomprog , no_err , fich_mer , nb_lig , nb_col );
	  exit(no_err) ;
     }

 
#ifdef _DEBUG_
     {
	  int fd_mer ;

	  /* Ouverture fichier aire de jeu */
	  if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 )
	  {
	       fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_mer);
	       exit(-1);
	  }

	  /* Affichage aire de jeu */
	  if( (no_err = mer_afficher(fd_mer) )) 
	  {
	       fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
			nomprog , no_err );
	       exit(no_err) ;
	  }

	  /* Fermeture fichier aire de jeu */
	  close(fd_mer); 
     }

     printf( "%s --> Initialisation de %s[%d,%d] Reussie\n",
	     nomprog , fich_mer, nb_lig, nb_col) ;
#endif

     exit(0);

}
