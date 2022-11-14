#include <commun.h>
/*!
 * \file test_commun.c
 * \brief Test des fonctions communes à tout le TP
 */

/*! Programme Principal */
int
main( int nb_arg , char * tab_arg[] )
{
  err_t noerr = CORRECT ;

  /*----------*/

  if( nb_arg != 1 )
    {
      fprintf( stderr , "\n%s: Test du TDA err\n\n" , tab_arg[0] );
      fprintf( stderr , "Usage : %s\n",
	       tab_arg[0] );
      exit(-1) ;
    }

  for( noerr = -ERR_NB ; noerr<=0 ; noerr++ )
    {
      printf( "Affichage du code erreur %d : ", noerr ) ; fflush(stdout) ; 
      err_print( noerr ) ;
    }
     
  exit(0); 
}
