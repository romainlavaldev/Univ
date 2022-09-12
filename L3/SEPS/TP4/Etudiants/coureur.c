#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/msg.h>
#include <messages.h>


/* Variable globales */
int Dossard ;

/* Programme Principal */
int 
main( int nb_arg , char * tab_arg[] )
{     
  int file_cle ;
  
  /*-----*/

  Dossard = getpid() ; 

  if( nb_arg != 2 )
    {
      fprintf( stderr, "usage : %s <cle de file>\n" , tab_arg[0] );
      exit(-1);
    }

  if( sscanf( tab_arg[1] , "%d" , &file_cle) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de file (%s)\n" , 
	       tab_arg[0]  , tab_arg[1] );
      exit(-2);
    }

  
  exit(0);
}
