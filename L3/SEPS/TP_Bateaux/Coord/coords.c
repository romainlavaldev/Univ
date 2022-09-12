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
coord_t coords_coord_get( const coords_t * const liste_coords  , const int ind_coord )
{
#ifdef _DEBUG_
  int nbcoords = coords_nb_get(liste_coords) ;
  if( (ind_coord < 0) || (ind_coord >  nbcoords-1) )
    {
      fprintf( stderr , "coords_coord_get: mauvais indice de coord [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(COORD_VIDE);
    }
#endif

  return( liste_coords->coords[ind_coord] ) ;
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
extern int coords_coord_set( coords_t * const liste_coords , 
			     const int ind_coord , 
			     const coord_t coord ) 
{
#ifdef _DEBUG_
  int nbcoords = coords_nb_get(liste_coords) ;
  if( (ind_coord < 0) || (ind_coord >  nbcoords-1) )
    {
      fprintf( stderr , "coords_coord_set: mauvais indice de coord [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(-1);
    }
#endif

  /* Affectation du coord a la  position */
  liste_coords->coords[ind_coord] = coord ;

  return(0) ;
}

/* 
 * Ajout d'une coord dans une liste de coords 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern int coords_coord_add( coords_t * const liste_coords , 
			     const coord_t coord ) 
{
  int nbcoords = coords_nb_get(liste_coords) ; 
 
  if( nbcoords == 0 ) 
    {
      if( ( liste_coords->coords = malloc( sizeof(coord_t) ) ) == NULL ) 
	{
	  fprintf( stderr , "coords_coord_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t) ) ;
	  return(-1) ; 
	} 
    }
  else
    {
      if( ( liste_coords->coords = realloc( liste_coords->coords , sizeof(coord_t) * (nbcoords+1) ) ) == NULL ) 
	{
	  fprintf( stderr , "coords_coord_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t) * (nbcoords+1) ) ;
	  return(-1) ; 
	} 
    }

  /* Affectation du coord a la derniere position */
  liste_coords->coords[nbcoords] = coord ;

  /* Mise a jour du nombre de coords */
  liste_coords->nb++ ; 
 
  return(0) ;
}


/* 
 * Deletion d'une coord dans une liste de coord 
 */
extern 
int coords_coord_del( coords_t * const liste_coords , 
		      const int ind_coord ) 
{
  int nbcoords = 0 ; 
  int i = 0 ;

  /* --- Assertions --- */
  if( liste_coords == NULL  ) 
    {
      fprintf( stderr , "coords_coord_del: liste de coords inexistante\n");
      return(-1) ;
    }

  nbcoords = coords_nb_get(liste_coords) ; 

  if( (ind_coord < 0) || (ind_coord > nbcoords-1 ) )
    {
      fprintf( stderr , "coords_coord_del: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind_coord , 0 , nbcoords-1 );
      return(-1);
    }

  /* ----------------- */

  /* Decalage des pointeurs depuis la position d'extraction jusqu'a la fin */
  for( i=ind_coord ; i<nbcoords-1 ; i++ ) 
    {
      liste_coords->coords[i] = liste_coords->coords[i+1] ;
    }

 /* Mise a jour de la taille du coordsleau */
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
	  fprintf( stderr , "coords_coord_del: debordement memoire %lu octets demandes\n" ,
		   sizeof(coord_t) * nbcoords ) ;
	  return(-1) ; 
	} 
    }

  return(0) ; 
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
int coords_destroy( coords_t ** liste_coords )
{
  
  if( (*liste_coords) == NULL )
    return(0) ;

  /* 
   * Destruction globale des elements de la liste
   * (stockage direct)
   */

  free( (*liste_coords)->coords ) ;
  free( (*liste_coords) ) ;
  (*liste_coords) = (coords_t *)NULL ;

  return(0) ;
}

/*
 * Affichage d'une liste de coords sur la sortie standard 
 */
extern 
void coords_printf( const coords_t * const liste_coords )
{
  int ind_coord ;
  int  nbcoords ; 

  if( liste_coords == NULL )
    {
      printf("(Liste coords vide)\n");
      return ;
    }

  nbcoords = coords_nb_get(liste_coords) ;

  printf( "Nombre de coords = %d\n" , nbcoords ) ;
  printf( "Liste des coords:\n");
  for( ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      coord_printf(coords_coord_get( liste_coords , ind_coord ) ) ;
      printf("\n");
    }
}

/*
 * Affichage d'une liste de coords 
 */
extern 
void coords_fprintf( FILE * restrict stream , const coords_t * const liste_coords )
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
      coord_fprintf(stream , coords_coord_get( liste_coords , ind_coord ) ) ;
      fprintf( stream , "\n");
    }
}

/* 
 * Copie d'une liste de coordonnees
 */

extern
int
coords_copier( coords_t ** coords_cible,
	      const coords_t * const coords_source )
{
  int noerr = 0 ; 
  int i = 0 ; 

  /* Destruction eventuelle de l'ancienne copie */
  if( (*coords_cible) != NULL ) 
    {
      if( ( noerr = coords_destroy( coords_cible ) ) )
	return(noerr) ; 
    }

  /* Cas de la source vide */
  if( coords_source == NULL )
	return(0) ; 

  /* Creation de la copie */
  if( ( (*coords_cible) = coords_new() ) == NULL ) 
    return(-1) ; 

  /* Copie des coordonnees */
  int nbcoords = coords_nb_get(coords_source) ;
  for( i=0 ; i<nbcoords ; i++ ) 
    {
      if( ( noerr = coords_coord_add( (*coords_cible) ,
				      coords_coord_get( coords_source , i ) ) ) )
	return(noerr) ; 
    }

  return(0) ;   
}


/*
 * Chargement d'une liste de coords a partir d'un fichier 
 */
extern 
int coords_read(  const int fd ,  /* descripteur fichier de restauration */
		  coords_t ** liste_coords ) /* structure liste coords a charger */
{
  int noerr ;
  int ind_coord  ;
  int nbcoords ;
  coord_t coord ; 

  /* Destruction de la liste si elle existe deja */
  if( (*liste_coords) != NULL )
    {
      coords_destroy( liste_coords ) ;
    }

  /* Lecture du nombre de coords */
  read( fd , &nbcoords , sizeof(int) ) ;

  /* Creation de la liste */
  (*liste_coords) = coords_new() ;

  for( ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      read( fd , &coord , sizeof(coord_t) ) ; 
      if( ( noerr = coords_coord_add( (*liste_coords) , coord ) ) )
	return(noerr) ; 

    }

  return(0) ;
}


/*
 * Ecriture du contenu d'une liste de coords dans un fichier
 */

extern 
int coords_write( const int fd ,    /* descripteur fichier de sauvegarde */
		  const coords_t * const liste_coords  )  /* structure liste coords a saucoord */
			 
{
  int ind_coord  ;
  int nbcoords ;
  coord_t coord ; 
  
  /* Destruction de la liste si elle existe deja */
  if( liste_coords == NULL )
    {
      fprintf( stderr , "WARNING : coords_fichier_save: la liste de coords est inexistante\n") ;
      return(0) ;
    }
 
  nbcoords = coords_nb_get(liste_coords) ;
  
  /* Ecriture du nombre de coords */
  write( fd , &nbcoords , sizeof(int) ) ;
  
  /* Parcours de la liste */
  for( ind_coord=0 ; ind_coord<nbcoords ; ind_coord++ )
    {
      coord = coords_coord_get( liste_coords , ind_coord ) ;
      write( fd , &coord , sizeof(coord_t) ) ; 

    }
 
  return(0) ;

}

/*
 * Recherches d'une coord dans une liste de coords 
 * Valeur retournee : indice du premier coord trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int coords_coord_seek( const coords_t * const liste_coords,
		       const coord_t coord , 
		       int (*comparer) (const coord_t , const coord_t) ) 
{
  int ind_coord = 0  ;
  booleen_t trouve = FAUX ;
  int nbcoords= coords_nb_get(liste_coords) ;
 
  while( (ind_coord<nbcoords) && (!trouve) ) 
    {
      if( comparer( coord , coords_coord_get(liste_coords , ind_coord)) == 0 )
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
      return(-1) ;
    }
}
