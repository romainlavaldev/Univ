#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <bateaux.h>

#define FICH_BATEAUX "fich_test_bateaux.bin" 

int
main( int nb_arg , char * tab_arg[] )
{
  bateau_t * bateau = BATEAU_NULL ;
  int b , c ; 
  bateaux_t * liste_bateaux = (bateaux_t *) NULL ; /* ATTENTION a bien initialiser la liste des bateaux */
  int ind ; 
  int noerr = 0 ; 
  coords_t * corps = NULL ; 
  coord_t coord ; 
  int nbbateaux = 0 ; 
  pid_t pid ; 
  case_t marque ;

  /*----------*/

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <nb bateaux>\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  srandom(getpid()) ;

  nbbateaux = atoi( tab_arg[1] ) ; 
     
  printf("Creation liste\n");
  liste_bateaux = bateaux_new() ; 

  printf("Ajout de bateaux dans la liste\n");
  for( b=0 ; b<nbbateaux ; b++ )
    {
      printf( "Creation bateau numero %d\n" , b ) ; 

      corps = coords_new() ;
      for( c=0 ; c<BATEAU_TAILLE ; c++ ) 
	{
	  coord_set( &coord ,
		     random()%nbbateaux,
		     random()%nbbateaux, 
		     random()%nbbateaux*100) ;

	  coords_coord_add( corps , coord ) ;
	}
     
      if( ( bateau = bateau_new( corps ,
				 'A'+b,
				 random()%1000 ) ) == BATEAU_NULL )
	{
	  printf("Sortie erreur \n" ) ; 
	  exit(0) ; 
	}

      coords_destroy( &corps ) ; 

      printf( "Ajout bateau numero %d\n" , b ) ; 
      if( ( noerr = bateaux_bateau_add( liste_bateaux, bateau ) ) )
	{
	  printf("Sortie erreur = %d\n" , noerr ) ; 
	  exit(0) ; 
	}

    }

  printf("Affichage liste des bateaux\n");
  bateaux_printf(liste_bateaux);

  printf("Sauvegarde d'une liste de bateaux dans un fichier\n");
  if( ( noerr = bateaux_save( liste_bateaux , FICH_BATEAUX ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }

  printf("Destruction liste\n");
  if( ( noerr = bateaux_destroy(&liste_bateaux) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }

  printf("Restauration fichier dans liste de bateaux\n");
  if( ( noerr = bateaux_load( &liste_bateaux, FICH_BATEAUX ) ) ) 
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  bateaux_printf( liste_bateaux ) ;

  if( nbbateaux > 0 ) 
    {
      pid = bateau_pid_get(bateaux_bateau_get(liste_bateaux,nbbateaux-1)) ;
      printf("Recherche positive d'un bateau dans la liste sur pid %d\n" , pid ) ;
      ind = bateaux_pid_seek( liste_bateaux, pid ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'un bateau dans la liste pid 999\n" ); 
      ind = bateaux_pid_seek( liste_bateaux, 999 ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;
 
      marque = bateau_marque_get(bateaux_bateau_get(liste_bateaux,nbbateaux-1)) ;
      printf("Recherche positive d'un bateau dans la liste sur marque %c\n" , marque ) ;
      ind = bateaux_marque_seek( liste_bateaux, marque ) ;
      if( ind != -1 ) 
	printf( "OK trouve indice %d \n", ind ) ;
      else
	printf( "!!! KO pas trouve !!!\n" ) ;

      printf("Recherche negative d'un bateau dans la liste marque '*' \n" ); 
      ind = bateaux_marque_seek( liste_bateaux, '*' ) ;
      if( ind == -1 ) 
	printf( "OK pas trouve\n" ) ;
      else
	printf( "!!! KO trouve avec indice %d !!! \n", ind ) ;



    }


  printf("Destruction d'un bateau dans la liste\n" ) ; 
  ind = random()%(bateaux_nb_get(liste_bateaux)-1) ; 
  printf("Destruction bateau numero %d\n" , ind ) ;
  bateaux_bateau_del( liste_bateaux , ind ) ; 
  bateaux_printf( liste_bateaux ) ;

  printf("Destruction de tous les bateaux un par un\n" ) ; 
  ind = bateaux_nb_get(liste_bateaux)-1 ; 
  while( bateaux_nb_get(liste_bateaux) )
    {
      printf("Destruction bateau numero %d\n" , ind ) ;
      bateaux_bateau_del( liste_bateaux , ind ) ; 
      ind-- ; 
    }
  bateaux_printf( liste_bateaux ) ;

  printf("Restauration dans une liste existante\n"); 
  if( ( noerr = bateaux_load( &liste_bateaux, FICH_BATEAUX ) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  bateaux_printf(liste_bateaux) ; 

  printf( "Destruction globale d'une liste de bateaux\n");      
  if( ( noerr = bateaux_destroy(&liste_bateaux) ) )
    {
      printf("Sortie erreur = %d\n" , noerr ) ; 
      exit(0) ; 
    }
  bateaux_printf(liste_bateaux) ; 
  
  exit(0);
}
