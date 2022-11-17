#include <stdio.h>
#include <stdlib.h>

#include <voie_unique_stdio.h>

/* Procedures internes */

static
void voie_unique_voie_vide_print()
{
     printf("..........");
}

static
void voie_unique_voie_blanc_print()
{
     printf("          ");
}

/* ----- Procedures externes ----- */

extern void voie_unique_mapper( voie_unique_t * const voie_unique )
{
     int z , t ;

     printf("\t--------------------\n");

     /* Affichage des 5 zones */
     for( z=0 ; z<5 ; z++ )
     {
	  switch( z )
	  {
	     case 0 :
		  printf( "zone OUEST  sens OUEST_EST\n");
		  break ;
	     case 1 :
		  printf( "zone OUEST  sens EST_OUEST\n");
		  break ;
	     case 2 :
		  printf( "zone UNIQUE\n");
		  break ;
	     case 3 :
		  printf( "zone EST  sens OUEST_EST\n");
		  break ;
	     case 4 :
		  printf( "zone EST  sens EST_OUEST\n");
		  break ;
	  }
	  printf( "Nb trains = %d \n" , voie_unique->cpt[z] );
	  for(t=0 ; t<voie_unique->cpt[z] ; t++ )
	  {
	       printf(" train[%d] = " , t );
	       train_print( &(voie_unique->zone[z][t]) );
	       printf("\n");
	  }
     }

     printf("\t--------------------\n");
}

/* 
 * Affochage 1ere ligne : Affichage OUEST VERS EST 
 *------------------------------------------------
 */
extern void voie_unique_ligne_1_print( voie_unique_t * const voie_unique )
{
  int i ;

  /*--------------------*/
  
  /* 
   * Affichage zone Ouest : trains allant de A vers B
   */
  
  if( voie_unique->cpt[ZONE_ID_OUEST_OE] + voie_unique->cpt[ZONE_ID_OUEST_EO]  == 0 )
    {
      /* Affichage voie minimale si pas de train */
      voie_unique_voie_vide_print();
      
    }
  else
    {
      /* Affichage zone ouest sens A vers B */
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_OUEST_OE] ; i++ )
	{
	  train_print( &(voie_unique->zone[ZONE_ID_OUEST_OE][i]) );
	}
      for(i=voie_unique->cpt[ZONE_ID_OUEST_OE] ; i<voie_unique->cpt[ZONE_ID_OUEST_EO] ; i++ )
	{	  
	  train_vide_print();
	}
    }

  /* 
   * Affichage blanc du sens unique 
   */
  if( voie_unique->cpt[ZONE_ID_UNIQUE] == 0 )
    {
      /* Affichage minimal si pas de train */
      voie_unique_voie_blanc_print();
    }
  else
    {
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_UNIQUE] ; i++ )
	{
	  train_blanc_print();
	}
    }
  
  /* 
   * Affichage zone Est : trains allant dans le sens A vers B 
   */
  if( voie_unique->cpt[ZONE_ID_EST_OE] + voie_unique->cpt[ZONE_ID_EST_EO] == 0 )
    {
      /* Affichage minimal si pas de train */
      voie_unique_voie_vide_print();
    }
  else
    {
      /* Affichage zone Est sens A vers B */
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_EST_OE] ; i++ )
	{
	  train_print( &(voie_unique->zone[ZONE_ID_EST_OE][i]) );
	}
      for(i=voie_unique->cpt[ZONE_ID_EST_OE] ; i<voie_unique->cpt[ZONE_ID_EST_EO] ; i++ )
	{	  
	  train_vide_print();
	}     
    }
}


/* 
 * Affichage 2ieme ligne : Affichage SENS UNIQUE
 *----------------------------------------------
 */
extern void
voie_unique_ligne_2_print( voie_unique_t * const voie_unique ) 
{
  int i ;
  int max_cpt ;
  
  /* Affichage blanc zone ouest */
  if( voie_unique->cpt[ZONE_ID_OUEST_OE]+voie_unique->cpt[ZONE_ID_OUEST_EO] == 0 )
    {
      voie_unique_voie_blanc_print();
    }
  else
    {
      max_cpt = max( voie_unique->cpt[ZONE_ID_OUEST_OE] , voie_unique->cpt[ZONE_ID_OUEST_EO] );
      for(i=0 ; i< max_cpt ; i++ )
	{
	  train_blanc_print();	  
	}
    }

  /* Affichage des trains dans la voie unique */
  if( voie_unique->cpt[ZONE_ID_UNIQUE] == 0 )
    {
      voie_unique_voie_vide_print();
    }
  else
    {
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_UNIQUE] ; i++ )
	{
	  train_print( &(voie_unique->zone[ZONE_ID_UNIQUE][i]));
	}
    }
  
  /* Affichage blanc zone est */
  if( voie_unique->cpt[ZONE_ID_EST_OE]+voie_unique->cpt[ZONE_ID_EST_EO] == 0 )
    {
      voie_unique_voie_blanc_print();
    }
  else
    {
      max_cpt = max( voie_unique->cpt[ZONE_ID_EST_OE] , voie_unique->cpt[ZONE_ID_EST_EO] );
      
      for(i=0 ; i< max_cpt ; i++ )
	{
	  train_blanc_print();
	}
    }
}

/* 
 * Affichage 3ieme ligne : Affichage EST VERS OUEST
 *-------------------------------------------------
 */

extern void
voie_unique_ligne_3_print( voie_unique_t * const  voie_unique ) 
{
  int i ; 

  /* Affichage zone Ouest sens B vers A */
  if( voie_unique->cpt[ZONE_ID_OUEST_EO]+voie_unique->cpt[ZONE_ID_OUEST_OE] == 0 )
    {
      voie_unique_voie_vide_print();
    }
  else
    {
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_OUEST_EO] ; i++ )
	{
	  train_print( &(voie_unique->zone[ZONE_ID_OUEST_EO][i]) );
	}
      for(i=voie_unique->cpt[ZONE_ID_OUEST_EO] ; i<voie_unique->cpt[ZONE_ID_OUEST_OE] ; i++ )
	{	  
	  train_vide_print();
	}
    }

  /* Affichage blanc du sens unique */
  if( voie_unique->cpt[ZONE_ID_UNIQUE] == 0 )
    {
      voie_unique_voie_blanc_print();
    }
  else
    {
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_UNIQUE] ; i++ )
	{
	  train_blanc_print();
	}
    }

  /* Affichage zone Est sens B vers A */
  if( voie_unique->cpt[ZONE_ID_EST_EO]+voie_unique->cpt[ZONE_ID_EST_OE] == 0 )
    {
      voie_unique_voie_vide_print();
    }
  else
    {
      for(i=0 ; i<voie_unique->cpt[ZONE_ID_EST_EO] ; i++ )
	{
	  train_print( &(voie_unique->zone[ZONE_ID_EST_EO][i]) );
	}
      for(i=voie_unique->cpt[ZONE_ID_EST_EO] ; i<voie_unique->cpt[ZONE_ID_EST_OE] ; i++ )
	{	  
	  train_vide_print();
	}
    }
}

extern void voie_unique_print( voie_unique_t * const voie_unique )
{
  /* Affichage de la section a voie unique */
  printf("\n\n");
  voie_unique_ligne_1_print(voie_unique) ; 
  printf("\n");
  voie_unique_ligne_2_print(voie_unique) ; 
  printf("\n");
  voie_unique_ligne_3_print( voie_unique ) ; 
  printf("\n\n\n");
}

