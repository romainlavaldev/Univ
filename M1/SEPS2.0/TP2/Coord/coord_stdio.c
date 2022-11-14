#include <coord_stdio.h>

/*
 *===========================================
 * Primitives d'E/S standard du TDA coord
 *===========================================
 */

/* 
 * Sortie des coordonnees d'une case 
 */

extern
void coord_print( FILE * const stream,
			 const coord_t * const coord )
{
  fprintf( stream , "[%d,%d]" , 
	   coord->l , 
	   coord->c );
}

/*  
 * Entree des coordonnees d'une case 
 */

extern
err_t coord_scan( FILE * const stream,
		coord_t * const coord )
{
  if( coord == NULL )
    {
      fprintf( stderr , "coord_scan: coordonnee cible inexistante\n" ); 
      return(ERR_NULL) ; 
    }

  if( feof(stream) ) return(CORRECT) ; 

  int nb_lus = 0 ; 
  if( (nb_lus = fscanf(stream , "%d%d" , &(coord->l) , &(coord->c))) != 2 )
    {
      switch(nb_lus)
	{
	case 0 :   fprintf( stderr , "coord_scan: erreur de lecture d'une coordonnee ...[?,?]\n" ); break ;
	case 1 :   fprintf( stderr , "coord_scan: erreur de lecture d'une coordonnee ...[%d,?]\n" , coord->l ); break ;
	case EOF : return(CORRECT) ; break ; 
	default :  fprintf( stderr , "probleme inconnu (code erreur %d)\n" , nb_lus ); break ; 
	}   
      return(ERR_SCAN) ; 
    }
  return(CORRECT) ; 
}

