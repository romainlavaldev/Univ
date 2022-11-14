#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*!
 * \file test_ecran.c
 * \brief Test des fonctions de gestion d'un écran géré par <code>ncurses</code> 
 */

#include <ecran.h>

/*! Programme Principal de test */
int 
main( int nb_arg , char * tab_arg[] )
{
  ecran_t * ecran = ECRAN_NULL ; 
  int i = 0 ; 
  char * compte[6] = { "ZERO" , "UN" , "DEUX" , "TROIS" , "QUATRE" , "CINQ" } ;
  int NbLignes   = 0 ; 
  int NbColonnes = 0 ; 
  coord_t coord ; 

  if( nb_arg != 3 )
    {
      fprintf( stderr , "%s : test du TDA ecran\n" , tab_arg[0]);
      fprintf( stderr , "usage : %s <nb lignes> <nb colonnes> \n" , tab_arg[0] );
      exit(-1);
    }


  sscanf(  tab_arg[1] , "%d" , &NbLignes ) ; 
  sscanf(  tab_arg[2] , "%d" ,  &NbColonnes) ; 

  printf("\n----- Debut %s -----\n" , tab_arg[0] );

  /*! -# Creation et affichage d'un écran */
  if( ( ecran = ecran_creer( NbLignes , NbColonnes ) ) == NULL )
    {
      fprintf( stderr , "Erreur creation ecran %dX%d\n" , NbLignes , NbColonnes );
      exit(-1);
   }

  wrefresh( ecran_affichage_get(ecran) ) ;
  wrefresh( ecran_messages_get(ecran) ) ;

  /*! -# Numerotation des lignes */
  int H = ecran_hauteur_get(ecran) ; 
  char mess[256] ; 
  sprintf( mess , "Hauteur ecran = %d" , H) ; 
  ecran_message_pause_afficher( ecran , mess ) ;
  for( i=0 ; i<H ; i++ )
    {
      sprintf( mess , "%d" , i ) ; 
      ecran_lc_wprint0( ecran , i , 0 , mess ) ; 
      ecran_message_pause_afficher( ecran , "." ) ;
    }

  /*! -# Numerotation des colonnes */
  int L = ecran_largeur_get(ecran) ;
  sprintf( mess , "Largeur ecran = %d" , L) ; 
  ecran_message_pause_afficher( ecran , mess ) ;
  for( i=0 ; i<L ; i++ )
    {
      sprintf( mess , "%d" , i%10) ; 
      ecran_lc_wprint0( ecran , 0 , i , mess ) ; 
    }

  /*! -# Affichage milieu ecran */
  for( i=5 ; i>=0 ; i-- )
    {
      sprintf( mess , "%d" , i) ; 
      ecran_lc_wprint0( ecran , H/2 , L/2 , mess ) ;
      ecran_message_pause_afficher( ecran , compte[i] ) ;
    }

  /*! -# Affichage d'un caractere par coordonnees */
  int j = 0 ;
  for( i=0 ; i<H ; i++ )
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  sprintf( mess , "Coord [%d,%d]" , i , j ) ;
	  ecran_message_afficher( ecran , mess ) ; 
	  coord_set( &coord  , i , j ) ;
	  ecran_coord_wprint0( ecran , &coord , "." ) ;
	}
    } 

  /*! -# Affichage d'un caractere par coordonnees + pause */
  for( i=0 ; i<H ; i++ )
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  sprintf( mess , "Coord [%d,%d]" , i , j ) ;
	  ecran_message_afficher( ecran , mess ) ; 
	  coord_set( &coord  , i , j ) ;
	  ecran_coord_wprint1( ecran , &coord , "X" , 5000 ) ;
	}
    } 

  /*! -# Affichage d'un caractere par coordonnees + pause + reverse-video */
  for( i=0 ; i<H ; i++ )
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  sprintf( mess , "Coord [%d,%d]" , i , j ) ;
	  ecran_message_afficher( ecran , mess ) ; 
	  coord_set( &coord  , i , j ) ;
	  ecran_coord_wprint( ecran , &coord , " " , 5000 , ECRAN_REVERSE ) ;
	}
    } 


 /*! -# Affichage d'un caractere par coordonnees + pause + video normale */
  for( i=0 ; i<H ; i++ )
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  sprintf( mess , "Coord [%d,%d]" , i , j ) ;
	  ecran_message_afficher( ecran , mess ) ; 
	  coord_set( &coord  , i , j ) ;
	  sprintf( mess , "%d", j%10 ) ;
	  ecran_coord_wprint( ecran , &coord , mess , 5000 , ECRAN_NORMAL ) ;
	}
    } 

  sleep(1) ;

  /*! -# Test de la pause ecran */
  ecran_message_stop_afficher( ecran , "Tapez <Entree>..." );

  
  ecran_message_pause_afficher( ecran , "ecriture hors ecran" );
  ecran_lc_wprint0( ecran , H , L , "X" ) ; 
  
  ecran_detruire(&ecran) ;
  printf("\n------ Fin %s -----\n\n" , tab_arg[0] );
     
  exit(0);
}
