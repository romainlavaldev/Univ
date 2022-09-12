/*
 * Gestion de la liste des bateaux 
 */

#include <bateaux.h>

/*! Acces au nombre de bateaux dans la liste */
extern 
int bateaux_nb_get( const bateaux_t * const liste_bateaux )
{
  return(liste_bateaux->nb) ; 
}

/*! Acces a un bateau dans la liste */
extern 
bateau_t * bateaux_bateau_get( const bateaux_t * const liste_bateaux  , const int ind_bateau )
{
#ifdef _DEBUG_
  int nbbateaux = bateaux_nb_get(liste_bateaux) ;
  if( (ind_bateau < 0) || (ind_bateau >  nbbateaux-1) )
    {
      fprintf( stderr , "bateaux_bateau_get: mauvais indice de bateau [%d] (devrait etre dans [%d..%d])\n",
	       ind_bateau , 0 , nbbateaux-1 );
      return(BATEAU_NULL);
    }
#endif

  return( liste_bateaux->bateaux[ind_bateau] ) ;
}

/*
 * Methodes set
 */


/* 
 * Affectation d'un bateau dans une liste de bateaux 
 * La position du bateau doit exister
 * L'ancienne valeur du bateau est ecrasee  
 */
extern int bateaux_bateau_set( bateaux_t * const liste_bateaux , 
			       const int ind_bateau , 
			       const bateau_t * const bateau ) 
{
   int noerr = 0 ; 

  /*----------*/

#ifdef _DEBUG_
  int nbbateaux = bateaux_nb_get(liste_bateaux) ;
  if( (ind_bateau < 0) || (ind_bateau >  nbbateaux-1) )
    {
      fprintf( stderr , "bateaux_bateau_set: mauvais indice de bateau [%d] (devrait etre dans [%d..%d])\n",
	       ind_bateau , 0 , nbbateaux-1 );
      return(-1);
    }
#endif

  /* Affectation du bateau a la  position */
  if( ( noerr = bateau_copier( &(liste_bateaux->bateaux[ind_bateau]) , 
			       bateau ) ) )
    return(noerr) ; 

  return(0) ;
}

/* 
 * Ajout d'un bateau dans une liste de bateaux 
 * L'affectation se fait par copie  
 */
extern int bateaux_bateau_add( bateaux_t * const liste_bateaux , 
			       const bateau_t * const bateau ) 
{
  int noerr = 0 ; 
  int nbbateaux = bateaux_nb_get(liste_bateaux) ; 
 
  if( nbbateaux == 0 ) 
    {
      if( ( liste_bateaux->bateaux = malloc( sizeof(bateau_t *) ) ) == NULL ) 
	{
	  fprintf( stderr , "bateaux_bateau_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(bateau_t *) ) ;
	  return(-1) ; 
	} 
    }
  else
    {
      if( ( liste_bateaux->bateaux = realloc( liste_bateaux->bateaux , sizeof(bateau_t *) * (nbbateaux+1) ) ) == NULL ) 
	{
	  fprintf( stderr , "bateaux_bateau_add: debordement memoire %lu octets demandes\n" ,
		   sizeof(bateau_t *) * (nbbateaux+1) ) ;
	  return(-1) ; 
	} 
    }

  /* Initialisation de la case du nouveau bateau */
  liste_bateaux->bateaux[nbbateaux] = NULL ; 

  /* Affectation du bateau a la derniere position */
  if( ( noerr = bateau_copier( &(liste_bateaux->bateaux[nbbateaux]),
			       bateau ) ) ) 
    return(noerr) ;
  
  /* Mise a jour du nombre de bateaux */
  liste_bateaux->nb++ ; 
 
  return(0) ;
}


/* 
 * Deletion d'un bateau dans une liste de bateaux
 */
extern 
int bateaux_bateau_del( bateaux_t * const liste_bateaux , 
			const int ind_bateau ) 
{
  int noerr = 0 ; 
  int nbbateaux = 0 ; 
  int i = 0 ;

  /* --- Assertions --- */
  if( liste_bateaux == NULL  ) 
    {
      fprintf( stderr , "bateaux_bateau_del: liste de bateaux inexistante\n");
      return(-1) ;
    }

  nbbateaux = bateaux_nb_get(liste_bateaux) ; 

  if( (ind_bateau < 0) || (ind_bateau > nbbateaux-1 ) )
    {
      fprintf( stderr , "bateaux_bateau_del: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind_bateau , 0 , nbbateaux-1 );
      return(-1);
    }

  /* ----------------- */

  /* Destruction du bateau */
  if( ( noerr = bateau_destroy( &(liste_bateaux->bateaux[ind_bateau]) ) ) )
    return(noerr) ; 

  /* Decalage des pointeurs depuis la position d'extraction jusqu'a la fin */
  for( i=ind_bateau ; i<nbbateaux-1 ; i++ ) 
    {
      liste_bateaux->bateaux[i] = liste_bateaux->bateaux[i+1] ;
    }

 /* Mise a jour de la taille de la liste */
  nbbateaux-- ; 
  liste_bateaux->nb = nbbateaux ; 
 
  if( nbbateaux == 0 ) 
    {
      free(liste_bateaux->bateaux) ; 
      liste_bateaux->bateaux = NULL ; 
    }
  else
    {
      if( ( liste_bateaux->bateaux = realloc( liste_bateaux->bateaux , sizeof(bateau_t) * nbbateaux ) ) == NULL ) 
	{
	  fprintf( stderr , "bateaux_bateau_del: debordement memoire %lu octets demandes\n" ,
		   sizeof(bateau_t) * nbbateaux ) ;
	  return(-1) ; 
	} 
    }

  return(0) ; 
}


/*
 * Creation d'une liste de bateaux
 * Stockage indirect des elements bateau_t 
 */
extern 
bateaux_t * bateaux_new()
{
  bateaux_t * liste ;

  if( (liste = malloc(sizeof(bateaux_t))) == NULL )
    {
      fprintf( stderr , "bateaux_creer: debordement memoire lors de la creation d'une liste de bateaux\n");
      return((bateaux_t *)NULL);
    }
  
  liste->nb = 0 ;
  liste->bateaux = (bateau_t **)NULL ;

  return(liste) ;
}

/*
 *  Destruction d'une liste de bateaux 
 */

extern 
int bateaux_destroy( bateaux_t ** liste_bateaux )
{
  
  int i = 0 ; 
  int nb = 0 ;
  int noerr = 0 ; 

  /*----------*/

  if( (*liste_bateaux) == NULL )
    return(0) ;

  nb = bateaux_nb_get( (*liste_bateaux) )  ;

  /* 
   * Destruction un par un  des elements de la liste
   * (stockage indirect)
   */
  for( i=0 ; i<nb ; i++ ) 
    {
      if( ( noerr = bateau_destroy( &((*liste_bateaux)->bateaux[i]) ) ) )
	return(noerr) ; 
    }
  /* Destruction liste */
  free( (*liste_bateaux)->bateaux ) ;
  /* Destruction structure */
  free( (*liste_bateaux) ) ;
  /* Mise a jour du pointeur */
  (*liste_bateaux) = (bateaux_t *)NULL ;

  return(0) ;
}

/*
 * Affichage d'une liste de bateaux sur la sortie standard 
 */
extern 
void bateaux_printf( const bateaux_t * const liste_bateaux )
{
  int b ;
  int  nbbateaux ; 

  if( liste_bateaux == NULL )
    {
      printf("(Liste bateaux vide)\n");
      return ;
    }

  nbbateaux = bateaux_nb_get(liste_bateaux) ;

  printf( "Nombre de bateaux = %d\n" , nbbateaux ) ;
  printf( "Liste des bateaux:\n");
  for( b=0 ; b<nbbateaux ; b++ )
    {
      bateau_printf(bateaux_bateau_get( liste_bateaux , b ) ) ;
      printf("\n");
    }
  printf("\n");
}

/*
 * Affichage d'une liste de bateaux dans un fichier 
 */
extern 
void bateaux_fprintf( FILE * restrict stream , const bateaux_t * const liste_bateaux )
{
  int b ;
  int  nbbateaux ; 

  if( liste_bateaux == NULL )
    {
      fprintf( stream , "(Liste bateaux vide)\n");
      return ;
    }

  nbbateaux = bateaux_nb_get(liste_bateaux) ;

  fprintf( stream , "Nombre de bateaux = %d\n" , nbbateaux ) ;
  fprintf( stream , "Liste des bateaux:\n");
  for( b=0 ; b<nbbateaux ; b++ )
    {
      bateau_fprintf( stream , bateaux_bateau_get( liste_bateaux , b ) ) ;
      fprintf( stream , "\n");
    }
  fprintf( stream , "\n");
}

/*
 * Chargement d'une liste de bateaux a partir d'un fichier 
 */
extern 
int bateaux_load( bateaux_t ** liste_bateaux  , /* structure liste bateaux a charger */
		  char * nom_fichier )  /* fichier de restauration */
{
  int noerr ;
  int fd ;
  int ind_bateau  ;
  int nbbateaux ;
  bateau_t * bateau = BATEAU_NULL ; 

  /* Destruction de la liste si elle existe deja */
  if( (*liste_bateaux) != NULL )
    {
      bateaux_destroy( liste_bateaux ) ;
    }


  /* Oubateauture du fichier des bateaux */
  if( (fd = open( nom_fichier , O_RDONLY , 0666 )) == -1 )
    {
      fprintf( stderr , "bateaux_load: impossible d'ouvrir le fichier [%s] en lecture\n",
	       nom_fichier ) ;
      return(-1);
    }

  /* Lecture du nombre de bateaux */
  read( fd , &nbbateaux , sizeof(int) ) ;

  /* Creation de la liste */
  (*liste_bateaux) = bateaux_new() ;

  for( ind_bateau=0 ; ind_bateau<nbbateaux ; ind_bateau++ )
    {
      if( ( noerr = bateau_read( fd , &bateau  ) ) )
	return(noerr) ; 

      if( ( noerr = bateaux_bateau_add( (*liste_bateaux) , bateau ) ) )
	return(noerr) ; 
    }

  /* Fermeture du fichier des bateaux */
  close(fd) ;

  return(0) ;
}


/*
 * Ecriture du contenu d'une liste de bateaux dans un fichier
 */

extern 
int bateaux_save( const bateaux_t * const liste_bateaux  ,  /* structure liste bateaux a saubateau */
		  char * nom_fichier )    /* fichier de sauvegarde */
{
  int noerr = 0 ; 
  int fd = -1 ;
  int ind_bateau  = 0 ;
  int nbbateaux = 0 ;
  bateau_t * bateau = BATEAU_NULL ; 

  /* Destruction de la liste si elle existe deja */
  if( liste_bateaux == NULL )
    {
      fprintf( stderr , "WARNING : bateaux_save: la liste de bateaux est inexistante\n") ;
      return(0) ;
    }
 
  /* Ouverture du fichier des sauvegardes */
  if( (fd = open( nom_fichier , O_CREAT | O_WRONLY , 0666 )) == -1 )
    {
      fprintf( stderr , "bateaux_fichier_saubateau: impossible d'ouvrir le fichier [%s] en lecture\n",
	       nom_fichier ) ;
      return(-1);
    }

  nbbateaux = bateaux_nb_get(liste_bateaux) ;
  
  /* Ecriture du nombre de bateaux */
  write( fd , &nbbateaux , sizeof(int) ) ;
  
  /* Parcours de la liste */
  for( ind_bateau=0 ; ind_bateau<nbbateaux ; ind_bateau++ )
    {
      bateau = bateaux_bateau_get( liste_bateaux , ind_bateau ) ;
      if( ( noerr = bateau_write( fd , bateau ) ) )
	return(noerr) ; 
    }

  /* Fermeture du fichier de sauvegarde */
  close(fd) ;

  return(0) ;

}



/*
 * Recherche d'un bateau sur son pid 
 * Valeur retournee : indice du bateau dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int bateaux_pid_seek( const bateaux_t * const liste_bateaux,
		   const pid_t pid_bateau ) 
{
  int ind_bateau = 0  ;
  booleen_t trouve = FAUX ;
  int nbbateaux = 0  ;
 
  if( liste_bateaux == NULL ) 
    return(-1) ; 

  nbbateaux= bateaux_nb_get(liste_bateaux); 

  while( (ind_bateau<nbbateaux) && (!trouve) ) 
    {
      if( pid_bateau ==  bateau_pid_get(bateaux_bateau_get(liste_bateaux , ind_bateau)) )
	  trouve = VRAI ;
      else
	  ind_bateau++ ;
    }
  
  if( trouve ) 
    {
      return(ind_bateau);
    }
  else
    {
      return(-1) ;
    }
}


/*
 * Recherche d'un bateau sur sa marque
 * Valeur retournee : indice du premier bateau trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int bateaux_marque_seek( const bateaux_t * const liste_bateaux,
		      const case_t marque_bateau ) 
{
  int ind_bateau = 0  ;
  booleen_t trouve = FAUX ;
  int nbbateaux = 0 ;
 
   if( liste_bateaux == NULL ) 
    return(-1) ; 

  nbbateaux= bateaux_nb_get(liste_bateaux); 

  while( (ind_bateau<nbbateaux) && (!trouve) ) 
    {
      if( marque_bateau ==  bateau_marque_get(bateaux_bateau_get(liste_bateaux , ind_bateau)) )
	  trouve = VRAI ;
      else
	  ind_bateau++ ;
    }
  
  if( trouve ) 
    {
      return(ind_bateau);
    }
  else
    {
      return(-1) ;
    }
}


/*
 * Recherche d'un bateau sur une coord de son corps 
 * Valeur retournee : indice du premier bateau trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int bateaux_coord_seek( const bateaux_t * const liste_bateaux,
			const coord_t coord ) 
{
  int ind_bateau = 0  ;
  booleen_t trouve = FAUX ;
  int nbbateaux = 0 ;
  coords_t * corps = NULL ; 

  if( liste_bateaux == NULL ) 
    return(-1) ; 
  
  nbbateaux= bateaux_nb_get(liste_bateaux); 

  while( (ind_bateau<nbbateaux) && (!trouve) ) 
    {

      corps = bateau_corps_get(bateaux_bateau_get( liste_bateaux , ind_bateau ) ) ;

      if( coords_coord_seek( corps , coord , coord_comparer ) != -1 )
	  trouve = VRAI ;
      else
	  ind_bateau++ ;
    }
  
  if( trouve ) 
    {
      return(ind_bateau);
    }
  else
    {
      return(-1) ;
    }
}
