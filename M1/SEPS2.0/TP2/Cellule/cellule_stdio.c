/*
 * Primitives entree/sortie standard du TDA cellule  
 */

#include <cellule_stdio.h>

/* 
 * Affichage de toutes les caracteristiques d'une cellule sur la sortie standard
 */

extern
void cellule_map( FILE * const stream,
		  const cellule_t * const cellule )
{

  /*--------------------*/
  
  /* Affichage position corps de la cellule */

  fprintf( stream , "{ coords = " );
  coord_print( stream ,
	       cellule_coords_get(cellule) );
    
  /* Affichage des autres caracteristiques */

  fprintf( stream , " ; etat = %s ; next = %s ; gen = %d }",
	   cellule_etat_2_string(cellule_etat_get(cellule)) ,
	   cellule_etat_2_string(cellule_etat_next_get(cellule)) ,
	   cellule_generation_get(cellule) );
}


/*
 * Affichage cellule sur sortie standard
 */

extern 
void cellule_print(FILE * const stream ,
		   const cellule_t * const cellule )
{

  cellule_etat_t etat = INIT ;
  cellule_etat_t etat_next = INIT ;
  

  if( ! cellule_existe( cellule ) )
    {
      printf(": ");
      return ;
    }
	  
  etat = cellule_etat_get(cellule) ;
  etat_next = cellule_etat_next_get(cellule) ;
  switch( etat )
    {
    case INIT    : 
      {
	switch( etat_next )
	  {
	  case INIT    : fprintf( stream , "II") ; break ;
	  case VIVANTE : fprintf( stream , "IV" ) ; break ;
	  case MORTE   : fprintf( stream , "IM" ) ; break ;
	  default      : fprintf( stream , "? " ) ; break ;
	  }
	break ; 
      }
	      
    case VIVANTE : 
      {
	switch( etat_next )
	  {
	  case INIT    : fprintf( stream , "O " ) ; break ; /* Pas encore evoluee */
	  case VIVANTE : fprintf( stream , "O " ) ; break ;
	  case MORTE   : fprintf( stream , "+ " ) ; break ;
	  default      : fprintf( stream , "? " ) ; break ;
	  }
	break ; 
      }
	      
    case MORTE   : 
      {
	switch( etat_next )
	  {
	  case INIT    : fprintf( stream , ". " ) ; break ; /* Pas encore evoluee */
	  case VIVANTE : fprintf( stream , "0 " ) ; break ;
	  case MORTE   : fprintf( stream , ". " ) ; break ;
	  default      : fprintf( stream , "? " ) ; break ;
	  }
	break ;
      }
    default      : fprintf( stream, "? " ) ; break ;
    }

}
