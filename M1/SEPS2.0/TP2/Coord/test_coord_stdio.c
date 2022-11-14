#include <coord_stdio.h>

/*!
 * \file test_automate_stdio.c
 * \brief Test des fonctions de gestion d'un automate avec affichage des résultats sur la sortie standard
 */

/*! \def FICHIER_TEST_COORD 
 * Fichier contenant une coordonnée de test
 */
#define FICHIER_TEST_COORD "../Fichiers/fichier_test_coord.txt"

int
main( int nb_arg , char * tab_arg[] )
{
  err_t noerr = CORRECT ;
  coord_t c , c2 ;
  int ligne , colonne  ;
  int cmp , diff1 , diff2 ;

  /*----------*/

  if( nb_arg != 3 )
    {
      fprintf( stderr , "\n%s: Test du TDA coord\n\n" , tab_arg[0] );
      fprintf( stderr , "Usage : %s <ligne> <colonne> \n",
	       tab_arg[0] );
      exit(-1) ;
    }

  sscanf( tab_arg[1] , "%d" , &ligne ) ;
  sscanf( tab_arg[2] , "%d" , &colonne ) ;

  /* Initialisation generation nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  /* Test ecriture dans une case */
  coord_set( &c,
	     ligne,		
	     colonne);

  /* Test affichage d'une case */
  printf("\nAffichage structure case : ");
  coord_print( stdout, &c ); 
  printf("\n\n");

  /* Test lecture d'une case */
  coord_get( &c,		
	     &ligne,	              
	     &colonne);	
     
  printf("\nAffichage des caracteristiques de la case:\n");
  printf("\tligne    = %d\n" , ligne );
  printf("\tcolonne  = %d\n" , colonne );
  printf("\n\n");


  /* Test comparaison de 2 coordonnees */
  diff1 = (int)(random()%3) ; diff1 = diff1 - 1 ; 
  diff2 = (int)(random()%3) ; diff2 = diff2 - 1 ; 

  coord_set( &c2 ,
	     ligne+diff1 ,
	     colonne+diff2 ) ;
     
  cmp = coord_comparer( &c , &c2 );
  coord_print( stdout, &c ); 
  if( cmp < 0 )
    {
      printf( " est inferieure a ") ;
    }
  else
    {
      if( cmp > 0 )
	printf( " est superieure a ");
      else
	printf( " est egale a ");
    }
  coord_print( stdout, &c2 ); 
  printf( "\n\n");

  /* Test affectation */
  coord_copier( &c2 , &c );
  cmp = coord_comparer( &c , &c2 );
  coord_print( stdout, &c ); 
  if( cmp < 0 )
    {
      printf( " est inferieure a ") ;
    }
  else
    {
      if( cmp > 0 )
	printf( " est superieure a ");
      else
	printf( " est egale a ");
    }
  coord_print( stdout, &c2 ); 
  printf( "\n\n");

  printf("Test lecture d'une coord dans le fichier %s\n" , FICHIER_TEST_COORD ) ;
  FILE * fd = fopen( FICHIER_TEST_COORD , "r" ) ;
  if( (noerr = coord_scan( fd , &c ) ) )
    {
      printf("Erreur dans la lecture d'une coordonnee dans %s, sortie erreur %d\n" , FICHIER_TEST_COORD , noerr ) ;
      err_print(noerr) ; exit(0) ;  	 
    }
  coord_print( stdout , &c ) ;
  printf("\n") ;
     
  fclose(fd) ; 
     
  exit(0); 
}
