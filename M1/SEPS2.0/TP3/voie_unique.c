#include <stdio.h>
#include <stdlib.h>

#include <sens_stdio.h>
#include <train.h>
#include <train_stdio.h> 
#include <voie_unique.h>

#define max(a,b) (a>b ? a : b )



/* ----- Procedures ----- */

extern voie_unique_t * 
voie_unique_creer()
{
     int z , t ;
     voie_unique_t * voie_unique = NULL ; 

     /*----------*/
     if( ( voie_unique = malloc( sizeof(voie_unique_t) ) ) == NULL  )
       {
	 fprintf( stderr , "voie_unique_creer: debordement memoire (%lu octets demandes)\n" , 
		  sizeof(voie_unique_t) ) ;
	 return(NULL) ; 
       }

     /* Initialisation des variables */
     for( z=0 ; z<5 ; z++)
     {
	  voie_unique->cpt[z] = 0 ;
	  for(t=0; t<MAX_TRAINS ; t++)
	       voie_unique->zone[z][t] = TRAIN_VIDE ;
     }

     return(voie_unique);
}

extern int
voie_unique_detruire( voie_unique_t ** voie_unique )
{
  free( (*voie_unique) ) ; 
  (*voie_unique) = NULL ; 

  return(0) ; 
}

/*
 * Verif collisions 
 * retour : -1 si collisions
 *           0 sinon 
 */
extern int 
voie_unique_collision_verifier( voie_unique_t * const voie_unique )
{
  int i ;

  /* Verification des collisions */
  if( voie_unique->cpt[ZONE_ID_UNIQUE] > 1 )
    {
      sens_t sens_prem = train_sens_get(&(voie_unique->zone[ZONE_ID_UNIQUE][0])) ;

      for(i=1 ; i<voie_unique->cpt[ZONE_ID_UNIQUE] ; i++ )
	{
	  if( sens_prem != train_sens_get(&(voie_unique->zone[ZONE_ID_UNIQUE][i])) )
	    {
	      return(-1);
	    }
	}
    }

  return(0) ; 
}

/*
 * Recherche d'un train dans toutes les zones d'une voie unique
 */ 
static int
voie_unique_train_rechercher( voie_unique_t * const vu,	/* voie_unique */
			      train_t tn ,		/* train a rechercher */
			      const zone_id_t z,	/* zone de recherche */
			      train_id_t * train_id )	/* indice resultat */
{
  int i = 0 ;
  boolean_t trouve = B_FALSE ;
     
  /*----------*/

  (*train_id) = -1 ;

  while( (i<vu->cpt[z]) && (!trouve) )
  {
    if( ! train_compare( &tn , &(vu->zone[z][i]) ) )
      trouve = B_TRUE ;
    else
      i++ ;
  }

  if( trouve )
  {
    (*train_id) = i ;
     return(0);
  }
  else
    return(-1);
}

/*
 * Effacement d'un train dans une zone par decalage a gauche 
 */
static int 
voie_unique_zone_decaler( voie_unique_t * const vu,	/* voie_unique */
			  const zone_id_t z,		/* zone a decaler */
			  const train_id_t id_debut )	/* indice debut decalage */
{
  int i ;
  /*----------*/

  for(i=id_debut; i<vu->cpt[z]-1 ; i++ )
    vu->zone[z][i] = vu->zone[z][i+1] ;
  return(0);
}

/*
 * Ajout d'un train a la fin d'une zone
 */
extern int
voie_unique_inserer( voie_unique_t * voie,	/* voie_unique */      
		     const train_t tn ,		/* train a inserer */
		     const zone_t z,		/* zone */        
		     const sens_t s )		/* sens */        
{
  sens_t s_l = s ;

  /*----------*/
  
  if( z == UNIQUE ) s_l = OUEST_EST ;
 
  voie->zone[z+s_l][voie->cpt[z+s_l]] = tn ;
  voie->cpt[z+s_l]++ ;
     
  return(0) ;
}

/*
 * Effacement d'un train d'une zone 
 */
extern int
voie_unique_extraire( voie_unique_t * voie ,    /* voie_unique */           
		      const train_t tn ,	/* train a extraire */   
		      const zone_t z,		/* zone */             
		      const sens_t s )          /* sens */             
{
  train_id_t train_id ;
  int cr ;
  train_t tn_l = tn ;
  sens_t s_l = s ;

  /*---------------------*/

  if( z == UNIQUE ) s_l = OUEST_EST ;

  if( (cr = voie_unique_train_rechercher( voie , tn_l , z+s_l, &train_id )) )
  {
    fprintf( stderr, "voie_unique_extraire: Erreur train de marque %c inconnu dans la voie\n" ,
	     train_marque_get(&tn_l) );
    return(cr);
  }

  voie_unique_zone_decaler( voie, z+s_l, train_id) ;
  voie->cpt[z+s_l]-- ;

  return(0) ;
}
