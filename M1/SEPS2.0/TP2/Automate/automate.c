#include <automate.h>

/*
 * Fonctions set/get
 */

extern
int automate_hauteur_get( const automate_t * const automate )
{
  return(automate->hauteur) ; 
}

extern
int automate_largeur_get( const automate_t * const automate )
{
  return(automate->largeur) ; 
}

extern
err_t automate_dim_get( const automate_t * const automate ,
		      int * hauteur ,
		      int * largeur )
{
  (*hauteur) = automate_hauteur_get(automate);
  (*largeur) = automate_largeur_get(automate);
  return(CORRECT) ; 
}

extern
err_t automate_hauteur_set( automate_t * const automate ,
			  const int hauteur )
{
  automate->hauteur = hauteur ; 
  return(CORRECT) ; 
}

extern
err_t automate_largeur_set( automate_t * const automate ,
			  const int largeur )
{
  automate->largeur = largeur ; 
  return(CORRECT) ; 
}

extern
err_t automate_dim_set( automate_t * const automate ,
		      const int hauteur ,
		      const int largeur )
{
  err_t noerr = CORRECT ;
  
  if( (noerr = automate_hauteur_set(automate , hauteur ) ) )
    return(noerr) ; 
  if( (noerr = automate_largeur_set(automate , largeur ) ) )
    return(noerr) ;
  
  return(CORRECT) ; 
}


extern
cellule_t * automate_get( const automate_t * const automate ,
			  const int i ,
			  const int j )
{
  if( automate == NULL )
    return(NULL);
  
  if( ( i < 0 ) || ( i >= automate_hauteur_get(automate) ) )
    {
      fprintf( stderr , "automate_get: Mauvaise coord ligne %d , devrait etre dans [0..%d]\n" ,
	       i , automate_hauteur_get(automate)-1 ) ;
      return(NULL) ;
    }

  if( ( j < 0 ) || ( j >= automate_largeur_get(automate) ) )
    {      
      fprintf( stderr , "automate_get: Mauvaise coord colonne %d , devrait etre dans [0..%d]\n" ,
	       j , automate_largeur_get(automate)-1 ) ;
      return(NULL) ;
    }
  
  int largeur = automate_largeur_get(automate) ; 
  return(*(automate->tab+i*largeur+j)) ; 
}

extern
err_t automate_set( automate_t * const automate ,
		  const int i ,
		  const int j ,
		  cellule_t * const cellule )
{

  /* Assertions */
  
  if( ( i < 0 ) || ( i >= automate_hauteur_get(automate) ) )
    return(ERR_DIM) ;

  if( ( j < 0 ) || ( j >= automate_largeur_get(automate) ) )
    return(ERR_DIM) ;

  /* Affectation cellule à la case [i,j] de l'automate par reference */
  int largeur = automate_largeur_get(automate) ; 
  *(automate->tab+i*largeur+j) = cellule ;
  
  return(CORRECT) ; 
}

/* 
 * Creation d'un automate  
 */

extern
automate_t * automate_new(const int hauteur , const int largeur , coords_t * coords_init )
{
  err_t noerr = CORRECT ;
  automate_t * automate = NULL ; 
  int i,j ; 
  
  /* Creation stucture de l'automate */
  if( ( automate = malloc( sizeof(automate_t) ) ) == NULL )
    {
      fprintf( stderr , "automate_new: debordement memoire structure automate, %lu octets demandes\n" , sizeof(automate_t) ) ;
      return(NULL) ; 
    }

   if( ( automate->tab = malloc( sizeof(cellule_t*) * hauteur * largeur ) ) == NULL )
    {
      fprintf( stderr , "automate_new: debordement memoire cases de l'automate, %lu octets demandes\n" , sizeof(cellule_t*)*hauteur*largeur ) ;
      return(NULL) ; 
    }

   /* Affectation des attributs */
   automate_hauteur_set(automate,hauteur);
   automate_largeur_set(automate,largeur);

   /* Creation et Affectation des cellules aux cases de l'automate */  
   for(i=0;i<hauteur;i++)
     {
       for(j=0;j<largeur;j++)
	 {	
	   if( (noerr = automate_set( automate ,  i , j , cellule_initialiser( i , j , coords_init ) ) ) )
	     {
	       fprintf( stderr , "automate_new: pb affectation case [%d,%d], code erreur %d\n" , i , j , noerr ) ;
	       return(NULL) ; 
	     }
	 }
     }
   
   return(automate) ;  
}

/*
 * Destruction d'un automate 
 */

extern
err_t automate_destroy( automate_t ** automate )
{
  int noerr = CORRECT ;
  int i , j ;
  int hauteur = automate_hauteur_get((*automate)) ;
  int largeur = automate_largeur_get((*automate)) ;
  cellule_t * cellule = NULL ;
  
  /* 
   * Destruction des cellules de l'automate 
   */
  for(i=0;i<hauteur;i++)
    {
      for(j=0;j<largeur;j++)
	{
	  cellule = automate_get( (*automate) , i , j ) ;
	  if( (noerr = cellule_destroy(&cellule)) )
	    {
	      fprintf( stderr ,"automate_destroy: Pb destruction cellule [%d,%d]\n" , i, j ) ;
	      return(ERREUR);
	    }
	}
    }
  
  /* 
   * Destruction des cases de l'automate 
   */
  free( (*automate)->tab ) ;
  
  /* Destruction structure automate */
  free( (*automate) );

  (*automate) = NULL ;
  
  return(CORRECT) ; 
}

/*
 * Calcul du nombre de cellules vivantes autour d'une case de coordonnee <coord>
 */

extern
err_t automate_nb_voisins_get( automate_t * automate ,
			     coord_t * coord,
			     int * nb_voisins )
{

  /* Assertions */
  if( automate == NULL )
    {
      fprintf( stderr , "automate_nb_voisins_get: automate inexistant\n") ;
      return(ERR_NULL) ;
    }
  
  if( coord == NULL )
    {
      fprintf( stderr , "automate_nb_voisins_get: coordonnee case inexistante\n") ;
      return(ERR_NULL) ;
    }

  /* Initialisation des resultats */
  (*nb_voisins) = 0 ;

  /* Recherche des voisins */
  int hauteur = automate_hauteur_get(automate);
  int largeur = automate_largeur_get(automate);
  int l = coord_lig_get(coord) ;
  int c = coord_col_get(coord) ;
  int i , j ;
  
  for( i = (l-1 < 0 ? 0 : l-1) ; i <= (l+1 > hauteur-1 ? hauteur-1 : l+1) ; i ++ )
    {
      for( j = (c-1 < 0 ? 0 : c-1) ; j <= (c+1 > largeur-1 ? largeur-1 : c+1) ; j ++ )
	{
	  if( (i == l) && (j ==c) ) continue ;

	  if( cellule_vivante( automate_get( automate, i , j ) ) )
	    (*nb_voisins)++ ; 	   
	}
    }

  return(CORRECT) ; 
}


/*
 * Evolution d'une cellule dans un automate
 */

extern
err_t automate_cellule_evoluer( automate_t * automate ,
			      cellule_t * cellule ,
			      const cellule_regles_t * const regles )
{
  int noerr = CORRECT ;
  int nb_voisins = 0 ;
  
  if( (noerr = automate_nb_voisins_get( automate ,
					cellule_coords_get(cellule),
					&nb_voisins ) ) )
    return(noerr) ;

  if( (noerr = cellule_evoluer( cellule , nb_voisins , regles ) ) )
    return(noerr) ;
  
  return(CORRECT) ;
}

/*
 * Prise en compte de la nouvelle generation d'un automate
 */

extern
err_t automate_generer( automate_t * automate )
{
  err_t noerr = CORRECT ;
  int hauteur = automate_hauteur_get(automate) ;
  int largeur = automate_largeur_get(automate) ;
  int i , j ;
  for(i=0;i<hauteur;i++)
    for(j=0;j<largeur;j++)
      {	
	if( (noerr = cellule_generer( automate_get( automate , i , j ) ) ) )
	  return(noerr) ;
      }
  
  return(CORRECT) ;
}
