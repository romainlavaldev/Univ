/*
 * Gestion de la liste des coords 
 */

#include <coords.h>

/*! Acces au nombre de coords dans la liste */
extern 
int coords_nb_get( const coords_t * const liste_coords )
{
  return(liste_coords->nb) ; 
}

/*! Acces a un coord dans la liste */
extern 
coord_t coords_get( const coords_t * const liste_coords  , const int ind_coord )
{
  int nbcoords = coords_nb_get(liste_coords) ;
  if( (ind_coord < 0) || (ind_coord >  nbcoords-1) )
    {
      fprintf( stderr , "coords_get: mauvais indice de coord [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(COORD_VIDE);
    }

  return( liste_coords->coords[ind_coord] ) ;
}

extern 
coord_t * coords_adr_get( const coords_t * const liste_coords  , const int ind_coord )
{
  int nbcoords = coords_nb_get(liste_coords) ;
  if( (ind_coord < 0) || (ind_coord >  nbcoords-1) )
    {
      fprintf( stderr , "coords_get: mauvais indice de coord [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(NULL);
    }

  return( &(liste_coords->coords[ind_coord]) ) ;
}

/*
 * Methodes set
 */


/* 
 * Affectation d'une coord dans une liste de coords 
 * La position du coord doit exister
 * L'ancienne valeur du coord est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern err_t coords_set( coords_t * const liste_coords , 
		       const int ind_coord , 
		       const coord_t coord ) 
{
#ifdef _DEBUG_
  int nbcoords = coords_nb_get(liste_coords) ;
  if( (ind_coord < 0) || (ind_coord >  nbcoords-1) )
    {
      fprintf( stderr , "coords_set: mauvais indice de coord [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(ERR_DIM);
    }
#endif

  /* Affectation du coord a la  position */
  liste_coords->coords[ind_coord] = coord ;

  return(CORRECT) ;
}

/* 
 * Ajout d'une coord dans une liste de coords 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern err_t coords_add( coords_t * const liste_coords , 
		       const coord_t coord ) 
{
  int nbcoords = coords_nb_get(liste_coords) ; 
 
  if( nbcoords == 0 ) 
    {
      if( ( liste_coords->coords = malloc( sizeof(coord_t) ) ) == NULL ) 
	{
	  fprintf( stderr , "coords_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t*) ) ;
	  return(ERR_MEM) ; 
	} 
    }
  else
    {
      if( ( liste_coords->coords = realloc( liste_coords->coords , sizeof(coord_t) * (nbcoords+1) ) ) == NULL ) 
	{
	  fprintf( stderr , "coords_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t) * (nbcoords+1) ) ;
	  return(ERR_MEM) ; 
	} 
    }

  /* Affectation du coord a la derniere position */
  liste_coords->coords[nbcoords] = coord ;

  /* Mise a jour du nombre de coords */
  liste_coords->nb++ ; 
 
  return(CORRECT) ;
}


/* 
 * Deletion d'une coord dans une liste de coord 
 */
extern 
err_t coords_del( coords_t * const liste_coords , 
		const int ind_coord ) 
{
  int nbcoords = 0 ; 
  int i = 0 ;

  /* --- Assertions --- */
  if( liste_coords == NULL  ) 
    {
      fprintf( stderr , "coords_del: liste de coords inexistante\n");
      return(ERR_NULL) ;
    }

  nbcoords = coords_nb_get(liste_coords) ; 

  if( (ind_coord < 0) || (ind_coord > nbcoords-1 ) )
    {
      fprintf( stderr , "coords_del: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(ERR_DIM);
    }

  /* ----------------- */

  /* Decalage des pointeurs depuis la position de suppression jusqu'a la fin */
  for( i=ind_coord ; i<nbcoords-1 ; i++ ) 
    {
      liste_coords->coords[i] = liste_coords->coords[i+1] ;
    }

  /* Mise a jour de la taille de la liste de coords */
  nbcoords-- ; 
  liste_coords->nb = nbcoords ; 
 
  if( nbcoords == 0 ) 
    {
      free(liste_coords->coords) ; 
      liste_coords->coords = NULL ; 
    }
  else
    {
      if( ( liste_coords->coords = realloc( liste_coords->coords , sizeof(coord_t) * nbcoords ) ) == NULL ) 
	{
	  fprintf( stderr , "coords_del: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t) * nbcoords ) ;
	  return(ERR_MEM) ; 
	} 
    }

  return(CORRECT) ; 
}


/*
 * Creation d'une liste de coords
 * Stockage direct des elements coord_t 
 */
extern 
coords_t * coords_new()
{
  coords_t * liste ;

  if( (liste=(coords_t *)malloc(sizeof(coords_t))) == NULL )
    {
      fprintf( stderr , "coords_creer: debordement memoire lors de la creation d'une liste de coords\n");
      return((coords_t *)NULL);
    }
  
  liste->nb = 0 ;
  liste->coords = (coord_t *)NULL ;

  return(liste) ;
}

/*
 *  Destruction d'une liste de coords 
 */

extern 
err_t coords_destroy( coords_t ** liste_coords )
{
  
  if( (*liste_coords) == NULL )
    return(CORRECT) ;

  /* 
   * Destruction globale des elements de la liste
   * (stockage direct)
   */

  free( (*liste_coords)->coords ) ;
  free( (*liste_coords) ) ;
  (*liste_coords) = (coords_t *)NULL ;

  return(CORRECT) ;
}

/* 
 * Copie d'une liste de coordonnees
 */

extern
err_t
coords_copier( coords_t ** coords_cible,
	       const coords_t * const coords_source )
{
  err_t noerr = 0 ; 
  int i = 0 ; 

  /* Destruction eventuelle de l'ancienne copie */
  if( (*coords_cible) != NULL ) 
    {
      if( ( noerr = coords_destroy( coords_cible ) ) )
	return(noerr) ; 
    }

  /* Cas de la source vide */
  if( coords_source == NULL )
    return(CORRECT) ; 

  /* Creation de la copie */
  if( ( (*coords_cible) = coords_new() ) == NULL ) 
    return(ERR_MEM) ; 

  /* Copie des coordonnees */
  int nbcoords = coords_nb_get(coords_source) ;
  for( i=0 ; i<nbcoords ; i++ ) 
    {
      if( ( noerr = coords_add( (*coords_cible) ,
				coords_get( coords_source , i ) ) ) )
	return(noerr) ; 
    }

  return(CORRECT) ;   
}


/*
 * Recherches d'une coord dans une liste de coords 
 * Valeur retournee : indice du premier coord trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
err_t coords_seek( const coords_t * const liste_coords,
		 coord_t * const coord , 
		 int (*comparer) (const coord_t * , const coord_t *  ) ) 
{
  int ind_coord = 0  ;
  booleen_t trouve = FAUX ;
  int nbcoords= coords_nb_get(liste_coords) ;
 
  while( (ind_coord<nbcoords) && (!trouve) ) 
    {
      if( comparer( coord , coords_adr_get(liste_coords , ind_coord)) == 0 )
	trouve = VRAI ;
      else
	ind_coord++ ;
    }
  
  if( trouve ) 
    {
      return(ind_coord);
    }
  else
    {
      return(PAS_TROUVE) ;
    }
}
