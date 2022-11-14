#include <automate_ecran.h>


/*
 * Creation de l'ecran d'affichage d'un automate 
 */
extern 
ecran_t * automate_ecran_creer( const automate_t * const automate )
{
  ecran_t * ecran = ECRAN_NULL ; 

  if( ( ecran = ecran_creer( automate_hauteur_get(automate) , automate_largeur_get(automate) ) ) == NULL )
    {
      fprintf( stderr , "automate_ecran_creer: Erreur creation ecran %dX%d\n" , automate_hauteur_get(automate)  , automate_largeur_get(automate) );
      return(ECRAN_NULL) ; 
    }

 return(ecran) ; 
}

/*
 * Affichages d'un automate sur un ecran
 */

/* Affichage normal */

extern 
void automate_wprint( ecran_t * const ecran , const automate_t * const automate ) 
{
  if( automate == NULL )
    {
      ecran_message_pause_afficher( ecran , "automate_wprint: automate inexistant") ;
      return ;
    }

  if( ! ecran_existe(ecran) )
    {
      ecran_message_pause_afficher( ecran , "automate_wprint: ecran inexistant") ;
      return ;
    }
  const int H = automate_hauteur_get(automate) ;
  const int L = automate_largeur_get(automate) ;
  int i = 0 ;
  int j = 0 ;
  
  /*
   * Affichage de toutes les cellules de l'automate 
   */
  for( i=0 ; i<H ; i++ ) 
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  cellule_wprint( ecran , i , j , automate_get( automate , i , j )  , FAUX ) ;
	}
    }
}





