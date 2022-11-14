/*
 * Primitives d'affichage d'une liste de coords sur les E/S standard
 */

#include <coords_stdio.h>

/*
 * Affichage d'une liste de coords 
 */
extern 
void coords_print( FILE * restrict stream , const coords_t * const liste_coords )
{
  int ind_coord ;
  int  nbcoords ; 
  
  if( liste_coords == NULL )
    {
      fprintf( stream , "(Liste coords vide)\n");
      return ;
    }

  nbcoords = coords_nb_get(liste_coords) ;

  fprintf( stream , "Nombre de coords = %d\n" , nbcoords ) ;
  fprintf( stream , "Liste des coords:\n");
  for( ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      coord_print(stream , coords_adr_get( liste_coords , ind_coord ) ) ;
      fprintf( stream , "\n");
    }
}

/*!
 * Saisie d'une liste de coords a partir d'un fichier
 * La liste des coordonnées doit être créée
 */
extern 
err_t coords_scan( const char * const nom_fichier , coords_t * const liste_coords )
{
  err_t noerr = CORRECT ; 
  coord_t coord ;
  int  cpt_coords = 0 ;
  FILE * fd = NULL ;

  if( liste_coords == NULL )
    {
      fprintf( stderr , "coords_scan: liste de coordonnées inexistante\n") ;
      return(ERR_NULL) ; 
    }
  
  /* Pas d'initialisation si pas de fichier */
  if( nom_fichier == NULL )
    return(CORRECT) ; 

  if( (fd = fopen( nom_fichier , "r" )) == NULL )
    {
      fprintf( stderr , "coords_scan: ouverture de %s en lecture impossible\n", nom_fichier );
      return(ERR_NULL) ;
    }

 
  
  while( !feof(fd) )
    {
      cpt_coords++;
      
      if( (noerr = coord_scan( fd , &coord ) ) )
	{
	  fprintf( stderr , "coords_scan: probleme lors de la lecture de la coord #%d dans le fichier %s\n",
		   cpt_coords , nom_fichier ) ;
	  return(noerr) ; 
	}
      if( !feof(fd) )
	{
	  if( (noerr = coords_add( liste_coords , coord ) ) )
	    {
	      fprintf( stderr , "coords_scan: probleme lors de l'ajout coord #%d dans la liste de coords\n",
		       cpt_coords ) ;
	      return(noerr) ; 
	    }
	}
    }
      
  fclose(fd) ;
  return(CORRECT) ; 
}
