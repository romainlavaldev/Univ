/*
 * Realisation des primitives du TDA cellule  
 */

#include <commun.h>
#include <cellule.h>

/*
 *=============================================================
 * Fonctions de gestion d'une cellule 
 *=============================================================
 */

extern
char * cellule_etat_2_string( cellule_etat_t etat )
{
  switch( etat )
    {
    case INIT : return("-") ; 
    case MORTE : return("MORTE") ;
    case VIVANTE : return("VIVANTE") ;
    default : return("?") ; 
    }
}


/* 
 * Ecriture des caracteristiques completes d'une cellule 
 */
extern
err_t cellule_set( cellule_t * const cellule,
		 const coord_t * const coords ,
		 const cellule_etat_t etat )
{
  err_t noerr = CORRECT ;
  
  if( ( noerr = cellule_coords_set( cellule  , coords ) ) ) 
    return(noerr) ;

  if( ( noerr = cellule_etat_set( cellule , etat ) ) )
    return(noerr) ;

  if(( noerr = cellule_etat_next_set( cellule, INIT ) ) )
    return(noerr) ; 
  
  return(CORRECT);
}

/*
 * Lecture/Ecriture du corps de la  cellule 
 */

extern 
coord_t * cellule_coords_get( const cellule_t * const cellule ) 
{ 
  return( cellule->coords ) ; 
}


extern 
err_t cellule_coords_set( cellule_t * const cellule , 
			const coord_t * const coords) 
{ 
  return(coord_copier( cellule->coords , coords ) ) ;
}

/*
 * Lecture/Ecriture de l'etat d'une cellule 
 */

extern
cellule_etat_t cellule_etat_get( const cellule_t * const cellule  ) 
{ 
     return(cellule->etat) ; 
}
extern 
err_t cellule_etat_set( cellule_t * const cellule , 
		       const cellule_etat_t etat) 
{ 
    cellule->etat = etat ;
    return(CORRECT);
}

extern
cellule_etat_t cellule_etat_next_get( const cellule_t * const cellule  ) 
{ 
     return(cellule->etat_next) ; 
}
extern 
err_t cellule_etat_next_set( cellule_t * const cellule , 
			   const cellule_etat_t etat) 
{ 
    cellule->etat_next = etat ;
    return(CORRECT);
}

extern 
err_t cellule_tuer( cellule_t * const cellule ) 
{ 
  return( cellule_etat_set( cellule , MORTE ) );
}

extern 
err_t cellule_naitre( cellule_t * const cellule ) 
{ 
  return( cellule_etat_set( cellule , VIVANTE ) );
}

extern 
err_t cellule_next_tuer( cellule_t * const cellule ) 
{ 
  return( cellule_etat_next_set( cellule , MORTE ) );
}

extern 
err_t cellule_next_naitre( cellule_t * const cellule ) 
{ 
  return( cellule_etat_next_set( cellule , VIVANTE ) );
}

/*
 * Lecture/Ecriture du numero de generation d'une cellule 
 */

extern
int cellule_generation_get( const cellule_t * const cellule  ) 
{ 
     return(cellule->generation) ; 
}
extern 
err_t cellule_generation_set( cellule_t * const cellule , 
			   const int generation ) 
{ 
    cellule->generation = generation ;
    return(CORRECT);
}

/*
 * Creation d'une cellule 
 */

extern
cellule_t * cellule_new( const int lig , const int col , const cellule_etat_t etat )
{
  err_t noerr = CORRECT ;
  cellule_t * cellule = NULL ; 
		      
  /* Reservation memoire */
  if( ( cellule = malloc( sizeof(cellule_t) ) )  == NULL )
    {
      fprintf( stderr , "cellule_new: debordement memoire structure cellule, %lu octets demandes\n" , sizeof(cellule_t) ) ;
      return(NULL) ; 
    }

  /* Affectation attributs */
  if( ( cellule->coords = coord_new( lig , col ) ) == NULL )
    {
      fprintf( stderr , "cellule_new: erreur affectation coordonnees [%d,%d]\n" , lig , col ) ;
      return(NULL) ; 
    }

  if(( noerr = cellule_etat_set( cellule, etat ) ) )
     {
      fprintf( stderr , "cellule_new: erreur affectation etat, code erreur %d\n" , noerr ) ;
      return(NULL) ; 
    }

   if(( noerr = cellule_etat_next_set( cellule, INIT ) ) )
     {
      fprintf( stderr , "cellule_new: erreur affectation etat de la prochaine generation, code erreur %d\n" , noerr ) ;
      return(NULL) ; 
    }

     if(( noerr = cellule_generation_set( cellule, 0 ) ) )
     {
      fprintf( stderr , "cellule_new: erreur affectation etat de la prochaine generation, code erreur %d\n" , noerr ) ;
      return(NULL) ; 
    }

  /* Retour resultat */
  return(cellule) ; 
}

extern
cellule_t * cellule_coord_new( const coord_t * const coords , const cellule_etat_t etat )
{
  return( cellule_new( coord_lig_get(coords),
		       coord_col_get(coords),
		       etat ) ) ;
}

/*
 * Initialisation d'une cellule 
 * Verifie si les coordonnees d'une cellule a creer sont dans une liste de coordonnees d'initialisation .
 * Si oui alors la cellule est creee vivante
 * sinon elle est creee comme morte
 */
extern
cellule_t * cellule_initialiser( const int lig , const int col , const coords_t * const liste_coords)
{
  err_t noerr = CORRECT ; 
  cellule_etat_t etat = VIVANTE ; 
  coord_t coord ;

  
  if( (noerr = coord_set( &coord , lig , col ) ) )
    return(NULL) ;
  
  if( coords_seek( liste_coords, &coord , coord_comparer ) == PAS_TROUVE )
    etat = MORTE ;
  else
    etat = VIVANTE ;
  
  return( cellule_new( lig , col , etat ) ) ;
}

/*
 * Evolution d'une cellule selon le nombre de ses voisins
 */
extern
err_t cellule_evoluer( cellule_t * const cellule , const int nb_voisins  , const cellule_regles_t * const regles )
{
  err_t noerr = CORRECT ;
  
  if( cellule_vivante(cellule) )
    {
      if( (nb_voisins < cellule_regles_isolement_get(regles) ) || (nb_voisins > cellule_regles_etouffement_get(regles) ) )
	{
	  if( (noerr = cellule_next_tuer(cellule) ) )
	    return(noerr) ;
	}
      else
	{
	  if( (noerr = cellule_next_naitre(cellule) ) )
	    return(noerr) ;
	}
    }
  else
    {
      if( nb_voisins == cellule_regles_naissance_get(regles) )
	{
	  if( (noerr = cellule_next_naitre(cellule) ) )
	    return(noerr) ;
	}
      else
	{
	  if( (noerr = cellule_next_tuer(cellule) ) )
	    return(noerr) ;
	}
    }

  return(CORRECT) ; 
}

/*
 * Prise en compte de la nouvelle generation d'une cellule 
 */
extern
err_t cellule_generer( cellule_t * const cellule )
{
  err_t noerr = CORRECT ;


  if( cellule_etat_next_get( cellule ) != INIT )
    {
      if( (noerr = cellule_etat_set( cellule ,
				     cellule_etat_next_get(cellule) ) ) )
	return(noerr);
	  
      if( (noerr = cellule_etat_next_set( cellule , INIT ) ) )
	return(noerr);
    }
  
  return(CORRECT) ; 
}


/*
 * Destruction une cellule 
 */

extern
err_t cellule_destroy( cellule_t ** cellule )
{
  err_t noerr = CORRECT ;
  
  if( ( noerr = coord_destroy( &((*cellule)->coords) ) ) )
    return(noerr) ;
  free( (*cellule) ) ;
  (*cellule) = NULL ;
  
  return(CORRECT) ; 
}

/*
 * Tests
 */

extern 
booleen_t cellule_vivante( const cellule_t * const cellule ) 
{ 
  return( cellule_etat_get(cellule) == VIVANTE );
}

extern 
booleen_t cellule_morte( const cellule_t * const cellule ) 
{ 
  return( cellule_etat_get(cellule) == MORTE );
}

extern 
booleen_t cellule_existe( const cellule_t * const cellule ) 
{ 
  return( cellule != NULL );
}

/*
 *=============================================================
 * Primitives gestions de cellule_regles_t
 *=============================================================
 */

extern
cellule_regles_t cellule_regles_default()
{
  cellule_regles_t regles ; 
  regles.naissance   = NAISSANCE   ; 
  regles.isolement   = ISOLEMENT   ; 
  regles.etouffement = ETOUFFEMENT ;
  return(regles) ; 
}

extern
err_t cellule_regles_initialiser(cellule_regles_t * const regles)
{
  if( regles == NULL )
    {
      fprintf( stderr , "cellule_regles_initialiser: structure de regles inexistante\n" ) ;  
      return(ERR_NULL);
    }
  
  regles->naissance   = NAISSANCE   ; 
  regles->isolement   = ISOLEMENT   ; 
  regles->etouffement = ETOUFFEMENT ;
  
  return(CORRECT) ; 
}

extern
int cellule_regles_naissance_get(const cellule_regles_t * const regles)
{
  return(regles->naissance) ;
}
extern
err_t cellule_regles_naissance_set(cellule_regles_t * const regles , const int naissance )
{
  regles->naissance = naissance ;
  return(CORRECT) ;
}

extern
int cellule_regles_isolement_get(const cellule_regles_t * const regles)
{
  return(regles->isolement) ;
}
extern
err_t cellule_regles_isolement_set(cellule_regles_t * const regles , const int isolement )
{
  regles->isolement = isolement ;
  return(CORRECT) ;
}

extern
int cellule_regles_etouffement_get(const cellule_regles_t * const regles)
{
  return(regles->etouffement) ;
}
extern
err_t cellule_regles_etouffement_set(cellule_regles_t * const regles , const int etouffement )
{
  regles->etouffement = etouffement ;
  return(CORRECT) ;
}
