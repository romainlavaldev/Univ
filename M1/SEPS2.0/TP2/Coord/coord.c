#include <coord.h>

/*
 *===========================================
 * Realisations des primitives du TDA coord
 *===========================================
 */

/*! 
 * Ecriture des coordonnees d'une case 
 */

extern
err_t coord_set( coord_t * const coord , 
	       const int ligne,
	       const int colonne)
{
     coord->l = ligne ;
     coord->c = colonne ;
     return(CORRECT) ; 
}

/*! 
 * Lecture des coordonnees d'une case 
 */

extern
err_t coord_get( const coord_t * const coord , 
		int * ligne,
		int * colonne)
{
  (*ligne)   = coord->l ;
  (*colonne) = coord->c ;
  return(CORRECT) ; 
}

extern
int coord_lig_get( const coord_t * const coord )
{
  return(coord->l) ;
}

extern
int coord_col_get( const coord_t * const coord )
{
  return(coord->c) ;
}

/* 
 * Creation d'une coord 
 */
extern
coord_t * coord_new(const int ligne,
		    const int colonne )
{
  err_t noerr = CORRECT ; 
  coord_t * coord = NULL ;

  if( (coord = malloc( sizeof( coord_t ) ) ) == NULL )
    {
      fprintf( stderr , "coord_new: debordement memoire %lu octets demandes\n" , sizeof(coord_t) ) ;
      return(NULL) ; 
    }

  if( (noerr = coord_set( coord , ligne, colonne)))    
    {
      fprintf( stderr , "coord_new: pb affectation attributs\n" ) ;
      return(NULL) ; 
    }

  return(coord) ;
}
  
/* 
 * Destruction d'une coord 
 */


extern
err_t coord_destroy( coord_t ** coord )
{
  free( (*coord) );
  (*coord) = NULL ;
  
  return(CORRECT) ; 
}

/* 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */

extern 
int coord_comparer( const coord_t * c1,
		    const coord_t * c2 )
{
     int cmp_l = c1->l - c2->l ;
     int cmp_c = c1->c - c2->c ;

     /*----------*/

     if( cmp_l )
       return(cmp_l);
     else
       return(cmp_c);	 
}

extern 
int coord_comparer_cb( const void * c1,
		       const void * c2 )
{
  return( coord_comparer( c1 , c2 ) ) ;
}


/* 
 * Copie de coordonnees
 */

extern
err_t coord_copier( coord_t * const coord_cible,
		  const coord_t * const coord_source )
{
  if( coord_cible == NULL )
    return(ERR_NULL) ;

  if( coord_source == NULL )
    return(ERR_NULL) ;
  
  return( coord_set ( coord_cible ,
		      coord_lig_get(coord_source) ,
		      coord_col_get(coord_source) ) ) ;
}


/* 
 * Renvoie d'une coordonnee vide 
 */
extern
coord_t coord_vide() 
{
  coord_t coord ; 

  coord.l = -1 ;
  coord.c = -1 ;
  return(coord) ; 
}


/*
 * Transformation coord en chaine de caracteres
 * ATTENTION : reservation memoire 
 */

extern
char * coord_2_string( const coord_t * const coord )
{
  char W[STRING_LG_MAX] ;
  
  sprintf( W , "[%d,%d]" , coord_lig_get(coord) , coord_col_get(coord) );
  char * string = malloc( strlen(W) + 1 ) ;
  strcpy( string , W ) ;
  return(string) ; 
}
