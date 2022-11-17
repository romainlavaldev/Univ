#include <stdio.h>
#include <stdlib.h>

#include <ligne.h>

/* 
 * Creation d'une ligne 
 */
extern
ligne_t * ligne_creer() 
{
  ligne_t * ligne = NULL ; 
  if( ( ligne = malloc( sizeof( ligne_t ) ) ) == NULL )
    {
      fprintf( stderr , "ligne_creer : debordement memoire (%lu octets demandes)\n" , 
	       sizeof( ligne_t ) ) ;
      return(NULL) ;
    }
  
  ligne->nb = 0 ; 
  return(ligne) ; 
}

/* 
 * Destruction d'une ligne 
 */

extern 
int ligne_detruire( ligne_t ** ligne ) 
{
  moniteur_voie_unique_id_t i = 0 ; 
  moniteur_voie_unique_id_t nb = ligne_nb_get((*ligne)) ; 
  int noerr = 0 ; 
  moniteur_voie_unique_t * moniteur = NULL ;

  /* Destruction des moniteurs composants la ligne */
  for( i=0 ; i < nb ; i++ ) 
    {
      moniteur = ligne_moniteur_get( (*ligne) , i ) ;
      if( ( noerr = moniteur_voie_unique_detruire(&moniteur) ) )
	{
	  fprintf( stderr , "ligne_detruire : erreur dans la destruction du moniteur %d\n" , i ) ;
	  return(noerr) ; 
	}
    }

  /* Destruction de la structure de la ligne */
  free((*ligne)) ; 
  (*ligne) = NULL ; 

  return(0) ; 
}

/* 
 * Initialisation d'une ligne 
 * La ligne doit etre creee avant son initailisation 
 */
extern int
ligne_initialiser( ligne_t * ligne ) 
{
  if( ligne == NULL )
    {
      fprintf( stderr , "ligne_initialiser: erreur , initialisation d'une ligne inexistante\n" ) ; 
      return(-1) ; 
    }

  ligne->nb = 0 ; 
  return(0) ; 
}

/*
 * Ajout d'une voie en fin de ligne 
 * Stockage indirect: la ligne contient des references sur les voies 
 * La ligne et la voie doivent etre existantes 
 */
extern int
ligne_moniteur_ajouter( ligne_t * ligne , 
			moniteur_voie_unique_t * moniteur ) 
{
  
  if( ligne == NULL )
    {
      fprintf( stderr , "ligne_voie_ajouter: erreur , ajout dans une ligne inexistante\n" ) ; 
      return(-1) ; 
    }
  if( moniteur == NULL )
    {
      fprintf( stderr , "ligne_voie_ajouter: erreur , ajout d'un moniteur inexistant\n" ) ; 
      return(-2) ; 
    }
  
  if( ligne->nb == MAX_MONITEURS_VOIES_UNIQUES )
    {
      fprintf( stderr , "ligne_voie_ajouter: erreur , ajout d'un moniteur dans une ligne pleine (max moniteurs = %d)\n" , 
	       MAX_MONITEURS_VOIES_UNIQUES ) ; 
      return(-3) ; 
    }

  ligne->moniteurs[ligne->nb] = moniteur ;
  ligne->nb++ ; 
  return(0) ; 
}

/*
 * Fonction get/ser 
 */

extern 
moniteur_voie_unique_t * ligne_moniteur_get( ligne_t * const ligne , const moniteur_voie_unique_id_t i )
{
  return( ligne->moniteurs[i] ) ;
}

extern 
moniteur_voie_unique_id_t ligne_nb_get( ligne_t * const ligne )
{
  return( ligne->nb ) ;
}


