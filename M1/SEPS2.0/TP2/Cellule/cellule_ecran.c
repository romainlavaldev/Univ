#include <cellule_ecran.h>

/* 
 * Affichage d'un cellule sur un ecran  
 */

static
void cellule_ecran_desintegrer( ecran_t * const ecran , 
			        const cellule_t * const cellule ) 
{

  WINDOW * fenetre = ecran_affichage_get(ecran) ;
  coord_t * coord = cellule_coords_get(cellule) ; 
  int lig = coord_lig_get(coord) ; 
  int col = coord_col_get(coord) ;
  int H = ecran_hauteur_get(ecran) ;
  int L = ecran_largeur_get(ecran) ; 

  char ch_expl[3][3] = { { '\\' , '|' , '/' } ,
			 { '-'  , ' ' , '-' } ,
			 { '/'  , '|' , '\\'} } ;
  char ch_sauv[3][3] ;

  /* Prise en compte des bordures du cadre */
  lig++ ;
  col++ ;
  
  /* Explosion 1er cercle */
  int debut_lig = ( lig-1 < 1 ? 1 : lig-1 ) ;
  int fin_lig   = ( lig+1 > H ? H : lig+1 ) ;
  int debut_col = ( col-1 < 1 ? 1 : col-1 ) ;
  int fin_col   = ( col+1 > L ? L : col+1 ) ;
  int l , c , i , j ; 

  for( l=debut_lig , i=0 ; l<=fin_lig ; l++ , i++ )
    {
      for( c=debut_col , j=0 ; c<=fin_col ; c++ , j++ )
	{
	  wmove( fenetre , l , c ) ;
	  ch_sauv[i][j] = winch( fenetre ) ;
	  waddch( fenetre , ch_expl[i][j] ) ;
	}
    }
    
  wrefresh( fenetre ) ;
  usleep(ECRAN_TEMPS_BREF) ;

  for( l=debut_lig , i=0 ; l<=fin_lig ; l++ , i++ )
    {
      for( c=debut_col , j=0 ; c<=fin_col ; c++ , j++ )
	{
	  wmove( fenetre , l , c ) ;
	  waddch( fenetre , ch_sauv[i][j] ) ;
	}
    }

  wrefresh( fenetre ) ;
  return ;
}


extern
void cellule_wprint( ecran_t * const ecran ,
		     const int lig,
		     const int col, 
		     const cellule_t * const cellule ,
		     const booleen_t dynamique ) 
{

  if( ! cellule_existe( cellule ) )
    {
      ecran_lc_wprint0( ecran , lig , col , ":" ) ;
      return ;
    }

  cellule_etat_t etat = INIT ;
  cellule_etat_t etat_next = INIT ;

  etat = cellule_etat_get(cellule) ;
  etat_next = cellule_etat_next_get(cellule) ;
  switch( etat )
    {
    case INIT    : 
      {
	switch( etat_next )
	  {
	  case INIT    : ecran_lc_wprint0( ecran , lig , col , "I" ) ; break ; /* Erreur : passage etat INIT-->INIT */
	  case VIVANTE : ecran_lc_wprint0( ecran , lig , col , "V" ) ; break ; /* Erreur : passage etat INIT-->VIVANTE */
	  case MORTE   : ecran_lc_wprint0( ecran , lig , col , "M" ) ; break ; /* Erreur : passage etat INIT-->MORTE */
	  default      : ecran_lc_wprint0( ecran , lig , col , "?" ) ; break ; /* Etat inconnu */
	  }
	break ; 
      }
	      
    case VIVANTE : 
      {
	switch( etat_next )
	  {
	  case INIT    : ecran_lc_wprint0( ecran , lig , col , "O" ) ; break ; /* Pas encore evoluee */
	  case VIVANTE : ecran_lc_wprint0( ecran , lig , col , "O" ) ; break ; /* Reste vivante */
	  case MORTE   :                                                       /* Deces */
	    {
	      if( dynamique ) cellule_ecran_desintegrer( ecran , cellule );
	      ecran_lc_wprint0( ecran , lig , col   , "." ) ; 
	      break ;
	    }
	  default      : ecran_lc_wprint0( ecran , lig , col , "?" ) ; break ; /* Etat inconnu */
	  }
	break ; 
      }
	      
    case MORTE   : 
      {
	switch( etat_next )
	  {
	  case INIT    : ecran_lc_wprint0( ecran , lig , col , "." ) ; break ; /* Pas encore evoluee */
	  case VIVANTE :                                                       /* Naissance */
	    {
	      if( dynamique )
		{
		  ecran_lc_wprint( ecran , lig , col , "O" , 0 , ECRAN_REVERSE ) ;
		  usleep(ECRAN_TEMPS_BREF) ;
		}
	      ecran_lc_wprint0( ecran , lig , col , "O" ) ; 
	      break ;
	    }
	  case MORTE   : ecran_lc_wprint0( ecran , lig , col , "." ) ; break ; /* Reste morte */
	  default      : ecran_lc_wprint0( ecran , lig , col , "?" ) ; break ; /* Etat inconnu */
	  }
	break ;
      }
      
    default      : ecran_lc_wprint0( ecran , lig , col , "?" ) ; break ;
    }

  wrefresh( ecran_affichage_get(ecran) ) ;
  return ;
}
