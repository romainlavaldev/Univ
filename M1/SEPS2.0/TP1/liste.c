#include <stdio.h>
#include <stdlib.h>
#include <liste.h>


/* Fonctions de lectures */

extern 
elem_id_t 
liste_nb_lire( liste_t * const liste )
{
  return( liste->nb ) ;
}

extern 
elem_t * 
liste_liste_lire( liste_t * const liste )
{
  return( liste->liste ) ;
}

extern 
elem_t 
liste_elem_lire( liste_t * const liste ,
		 const liste_id_t i )
{
  return( liste->liste[i] ) ;
}

/* Fonctions d'affectations */

extern 
void
liste_nb_affecter( liste_t * liste ,
		   const elem_id_t nb )
{
  liste->nb = nb  ;
}

extern 
void
liste_liste_affecter( liste_t * liste ,
		      elem_t * const l )
{
  elem_id_t i ;
  for( i=0 ; i<LISTE_MAX ; i++ )
    liste->liste[i] = l[i] ;
}

extern 
void
liste_elem_affecter( liste_t * liste ,
		     const liste_id_t i ,
		     const elem_t e )
{
    liste->liste[i] = e ;
}


/* Recherche sur le contenu d'une cellule d'un element dans la liste */

extern
booleen_t
liste_elem_rechercher( int * ind_recherche ,
		       liste_t * const liste,
		       const elem_t elem)
{
  int i=0 ;
  booleen_t trouve = FAUX ;
  elem_id_t nb_elems = liste->nb ; 

  /*----------*/

  (*ind_recherche) = -1 ;

  while( (i<nb_elems) && (!trouve) ) 
    {
      if( elem_comparer( liste->liste[i] , elem ) == 0 )
	trouve = VRAI ;
      else
	i++ ;
    }

  if( trouve )
    (*ind_recherche = i );
 
  return(trouve) ;
}


/* Effacement d'un element dans la liste */

extern
int
liste_elem_supprimer( liste_t * liste,
		      int ind_suppression )
{
  int i ;
  elem_id_t nb = liste->nb ;

  /* Ecrasement de l'element a effacer */
  for( i=ind_suppression ; i < nb-1 ; i++ ) 
    {
      liste->liste[i] = liste->liste[i+1] ;
    }

  /* Maj du nb de coureurs */
  liste->nb-- ;

  return(0) ;
}

/* Ajout d'un coureur dans la liste */

extern
int
liste_elem_ajouter( liste_t * liste,
		    const elem_t elem )
{
  
  /* Ajout a  la derniere elem */
  liste->liste[liste->nb] = elem ;

  /* Maj du nb de coureurs */
  liste->nb++ ;

  return(0) ;
}

/* Affichage d'une liste */

extern
int
liste_afficher( liste_t * const liste )
{
  printf("\n-----------------------------------------\n");
  if( liste != (liste_t *)NULL )
    {
      int i ;
      elem_id_t nb_elems = liste->nb ;

      printf("\tNombre de chevaux repertories = %d\n\n" , nb_elems );
      for( i=0 ; i < nb_elems ; i++ )
	{
	  printf("\t\t");
	  elem_afficher( liste->liste[i] ) ;
	  printf("\n") ;
	}
    }
  printf("-----------------------------------------\n\n");

  return(0) ;
}

/*
 * Initialisation d'une liste 
 */

extern 
int
liste_initialiser( liste_t * liste )
{
  liste->nb = 0 ;
  return(1) ;
}

/* 
 * Decanillage d'un cheval:
 * Mettre son etat a decanille
 */
extern 
int
liste_elem_decaniller( liste_t * liste ,
		       const elem_id_t ind_cheval )
{
  if( ( ind_cheval < 0 ) || ( ind_cheval >= liste->nb ) )
    {
      fprintf( stderr , "liste_elem_decaniller: liste_elem_decaniller: indice de cheval incorrect (%d) [0..%d]\n",
	       ind_cheval , liste->nb ) ; 
      return(-1) ;
    }
  elem_etat_affecter( &(liste->liste[ind_cheval]) , DECANILLE ) ;

  return(0) ;
}


/*
 * Comparaison de 2 listes l1 et l2
 * Retour < 0 si l1 < l2  
 *        = 0 si l1 = l2
 *        > 0 si l1 > l2
 */
extern
int
liste_comparer( liste_t * const l1 , liste_t * const l2 ) 
{
     liste_id_t i ;
     int cmp = l1->nb - l2->nb ;

     if( cmp != 0 ) 
       return(cmp) ;
	 
     i=0;
     while( (i<l1->nb) && (elem_comparer(l1->liste[i],l2->liste[i]) == 0)  )
	  i++;

     if( i>= l1->nb )
	  return(0) ;
     else
	  return( elem_comparer(l1->liste[i],l2->liste[i]) ) ;
}



/* 
 * Affectation d'une liste : l1 <-- l2
 * l1 doit etre creee avant l'appel a cette fonction 
 */

extern
void
liste_affecter( liste_t * l1 , liste_t * const l2 )
{
     liste_id_t i ;
     
     l1->nb = l2->nb ; 
     for( i=0 ; i<l2->nb ; i++ )
	  l1->liste[i] = l2->liste[i];
}
