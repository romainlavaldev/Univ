#include <stdio.h>
#include <stdlib.h>

#include <ligne_stdio.h>

int 
main( int argc , char * argv[] )
{

  ligne_t * ligne = NULL ;
  int noerr = 0 ; 
  int i = 0 ; 

  moniteur_voie_unique_t * tab_moniteur[MAX_MONITEURS_VOIES_UNIQUES] ;

  if( argc != 2 )
    {
      fprintf( stderr , "%s : test du TDA ligne\n" , argv[0] );
      fprintf( stderr , "usage : %s <nb sections a voie unique>\n" , argv[0] );
      exit(-1);
     }

  moniteur_voie_unique_id_t Nb_Voies = atoi(argv[1]) ; 

  /*-----*/

  for( i=0 ; i<Nb_Voies ; i++ ) 
    {
      tab_moniteur[i] = moniteur_voie_unique_creer(i+1) ; 
    }
  
  printf("\n----- Debut %s -----\n" , argv[0] );
     
  
  printf( "Creation ligne\n" ) ;
  if( ( ligne = ligne_creer() ) == NULL )
    {
      printf( "--> sortie erreur\n" ) ;
      exit(0) ; 
    }

  printf( "Ajout d'une voie en fin de ligne\n" ) ;
  for( i=0 ; i< Nb_Voies ; i++ ) 
    {
      if( ( noerr = ligne_moniteur_ajouter( ligne , 
					    tab_moniteur[i] ) ) )
	{
	  printf( "--> sortie erreur %d\n" , noerr) ;
	  exit(0) ; 
	}
    }

  printf( "Affichage structure de la ligne\n" ) ; 
  ligne_mapper( ligne ) ;
  printf( "Affichage de la ligne\n" ) ; 
  ligne_print( ligne ); 
  
  printf( "Destruction de la ligne\n") ;
  if( ( noerr = ligne_detruire( &ligne ) ) )
    {
      printf( "--> sortie erreur %d\n" , noerr) ;
      exit(0) ; 
    }
  
  printf(  "------ Fin %s -----\n\n" , argv[0] );
     
  exit(0);
}
