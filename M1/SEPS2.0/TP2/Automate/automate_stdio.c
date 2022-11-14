#include <automate_stdio.h>

/*
 * Affiche l'automate sur la sortie standard
 */

extern 
void automate_print(FILE * stream , automate_t * automate )
{
  int i,j;

  /* Assertion */
  if( automate == NULL )
    {
      fprintf( stderr , "Automate inexistant\n") ;
      return;
    }

  /* Affichage */
  int hauteur = automate_hauteur_get(automate);
  int largeur = automate_largeur_get(automate);
  
  for(i=0;i<hauteur;i++)
    {
      for(j=0;j<largeur;j++)
	{
	  
	  cellule_print( stream , automate_get( automate , i , j ) ) ;
	  
	}
      printf("\n");	
    }
}
