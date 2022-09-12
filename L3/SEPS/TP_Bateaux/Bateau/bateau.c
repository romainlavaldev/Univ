/*
 * Realisation des primitives du TDA bateau  
 */

#include <bateau.h>


/*
 *=============================================================
 * Fonctions de gestion d'un bateau 
 *=============================================================
 */

/*
 * Valeur bateau vide 
 */

extern 
bateau_t bateau_vide() 
{
  bateau_t bateau ;
 
  bateau.corps  = NULL ;
  bateau.marque = '?' ;
  bateau.pid    = -1 ; 

  return(bateau) ; 
}

/*
 * Creation d'un bateau 
 */
extern 
bateau_t * bateau_new( const coords_t * const coords,
		       const case_t marque,
		       const pid_t pid ) 
{
  bateau_t * bateau ;

  if( ( bateau = malloc( sizeof(bateau_t) ) ) == NULL )
    {
      fprintf( stderr , "bateau_new: debordement memoire (%lu octets demandes)\n" , 
	       sizeof(bateau_t) ); 
      return(NULL) ; 
    }

  (*bateau) = BATEAU_VIDE ; 

  if( bateau_set( bateau, coords, marque, pid ) == -1 )
      return(NULL) ;

  return(bateau) ; 
}

extern 
int bateau_destroy( bateau_t ** bateau ) 
{
  int noerr = 0  ;
  
  if(( noerr = coords_destroy( &((*bateau)->corps) ) ) )
    return(noerr) ; 

  free((*bateau)) ; 
  (*bateau) = NULL ;

  return(0) ; 
}


/*
 * Methodes  get/set 
 */


/*
 * Lecture/Ecriture du corps du bateau 
 */

extern 
coords_t * bateau_corps_get( const bateau_t * const bateau ) 
{ 
  return( bateau->corps ) ; 
}

extern 
int bateau_corps_set( bateau_t * const bateau ,    /* Bateau */
		      const coords_t * const coords)  /* Tableau de BATEAU_TAILLE coords composant le corps du bateau */
{ 
     int noerr = 0 ; 

     /*----------*/

     /* La liste des anciennes coordonnees est ecrasee */
     if( ( noerr = coords_copier( &(bateau->corps) ,
				  coords ) ) )
       return(noerr) ; 

     return(0);
}

/*
 * Lecture/Ecriture du signe distinctif du bateau 
 */

extern 
case_t bateau_marque_get( const bateau_t * const bateau ) 
{ 
     return(bateau->marque) ; 
}
extern 
int bateau_marque_set( bateau_t * const bateau , 
		       const case_t m) 
{ 
    bateau->marque = m ;
    return(0); 
}


/*
 * Lecture/Ecriture du pid du processus qui execute le bateau 
 */

extern 
pid_t bateau_pid_get( const bateau_t * const bateau ) 
{ 
     return(bateau->pid) ; 
}
extern 
int bateau_pid_set( bateau_t * const bateau , 
		    const pid_t pid) 
{ 
  bateau->pid = pid ;
  return(0) ; 
}

/* 
 * Ecriture des caracteristiques completes d'un bateau 
 * Le bateau doit etre cree
 */
extern
int
bateau_set( bateau_t * bateau,
	    const coords_t * const coords,
	    const case_t marque,
	    const pid_t pid )
{
  int noerr = 0 ; 

  /*----------*/

  if( bateau == BATEAU_NULL ) 
    {
      fprintf( stderr , "bateau_set: affectation d'un bateau inexistant\n") ; 
      return(-1) ;
    }

  if( ( noerr = bateau_corps_set( bateau , coords) ) )
    return(noerr) ;
     
  if( ( noerr = bateau_marque_set( bateau ,  marque ) ) )
    return(noerr) ; 

  if( ( noerr = bateau_pid_set( bateau , pid ) ) )
    return(noerr) ; 

  return(CORRECT);
}

/*
 * Copie d'un bateau 
 * "bateau_cible" est cree ; s'i existait deja alors il est efface puis re-cree
 */

extern 
int bateau_copier( bateau_t ** bateau_cible , const bateau_t * const bateau_source ) 
{ 
  int noerr = 0 ; 

  /*----------*/

  if( (*bateau_cible) != BATEAU_NULL ) 
    {
      if( ( noerr = bateau_destroy( bateau_cible ) ) )
	return(noerr) ; 
    }

  if( ( (*bateau_cible) = bateau_new( bateau_corps_get(bateau_source) ,
				      bateau_marque_get(bateau_source) ,
				      bateau_pid_get(bateau_source) ) ) == BATEAU_NULL )
    return(-1) ; 

  return(0) ; 
}

/* 
 * Affichage de toutes les caracteristiques d'un bateau sur la sortie standard 
 */

extern
void
bateau_printf( const bateau_t * const bateau )
{

  /*--------------------*/
  
  if( bateau == BATEAU_NULL ) 
    {
      printf("(bateau inexistant)\n");
      return ;
    }
  
  /* Affichage position corps du bateau */
  
  printf( "{-----\n" );
  printf( "  corps =\n" );
  coords_printf( bateau->corps);
  printf( "\n" );
  
  /* Affichage des autres caracteristiques */
  printf( "  marque= %c\n", bateau->marque);
  printf( "  pid   = %d\n", bateau->pid);
  printf( "-----}\n" );
}


/* 
 * Affichage de toutes les caracteristiques d'un bateau dans un fichier
 */

extern
void
bateau_fprintf( FILE * restrict stream , const bateau_t * const bateau )
{

  /*--------------------*/
  
  if( bateau == BATEAU_NULL ) 
    {
      fprintf( stream , "(bateau inexistant)\n");
      return ;
    }
  
  /* Affichage position corps du bateau */
  
  fprintf( stream , "{-----\n" );
  fprintf( stream , "  corps =\n" );
  coords_fprintf( stream , bateau->corps);
  fprintf( stream , "\n" );
  
  /* Affichage des autres caracteristiques */
  fprintf( stream , "  marque= %c\n", bateau->marque);
  fprintf( stream , "  pid   = %d\n", bateau->pid);
  fprintf( stream , "-----}\n" );
}


/*
 * Ecriture dans un fichier 
 */
extern
int bateau_write( const int fd , /* Descriteur du fichier */
		  const bateau_t * const bateau )
{
  size_t taille = 0 ;
  ssize_t nb_ecrits = 0 ; 
  case_t marque = CASE_VIDE ;
  pid_t pid = -1 ; 

  /* Ecriture du corps */
  if( coords_write( fd , 
		    bateau_corps_get(bateau) ) == -1 )
    {
      fprintf( stderr , "bateau_write: pb sauvegarde du corps\n" );
      return(-1) ; 
    } 

  /* Ecriture de la marque */
  taille = sizeof(case_t) ;
  marque = bateau_marque_get(bateau) ;
  if( ( nb_ecrits = write( fd , 
			   &marque , 
			   taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "bateau_write: pb sauvegarde de la marque : %lu octet(s) ecrit(s) / %lu octet(s) attendu(s)\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(-1) ; 
    } 
  
  /* Ecriture du pid */
  taille = sizeof(pid_t) ; 
  pid = bateau_pid_get(bateau) ; 
  if( ( nb_ecrits = write( fd , 
			  &pid ,  
			  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "bateau_write: pb sauvegarde du pid  : %lu octet(s) ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(-1) ; 
    } 
 
  return(0);
}

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture
 * Le bateau "bateau" est cree 
 */
extern
int bateau_read( const int fd , /* Descriteur du fichier */
		 bateau_t ** bateau )
{
  size_t taille = 0 ;
  ssize_t nb_lus = 0 ; 
  int noerr = 0 ; 
  coords_t * corps = NULL ; 
  case_t marque = CASE_VIDE ; 
  pid_t pid = -1 ; 

  if( (*bateau) != BATEAU_NULL ) 
    {
      if( ( noerr = bateau_destroy( bateau ) ) )
	return(noerr);
    }
 
  /* Lecture du corps */
  if( coords_read( fd , &corps ) == -1 )
    {
      fprintf( stderr , "bateau_read: pb read sur le corps\n" );
      return(-1) ; 
    } 

  /* Lecture de la marque */
  taille = sizeof(case_t) ; 
  if( ( nb_lus = read( fd , &marque , taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "bateau_read: pb read sur la marque : %lu octet(s) lu(s) / %lu octet(s) attendu(s)\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(-1) ; 
    } 
  
  /* Lecture du pid */
  taille = sizeof(pid_t) ; 
  if( ( nb_lus = read( fd , &pid ,  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "bateau_read: pb read sur le pid  : %lu octet(s) lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(-1) ; 
    } 

  /* Creation du bateau */
  if( ( (*bateau) = bateau_new( corps , marque, pid ) ) == NULL )
      return(-1) ;

  
  /* Destruction variables de travail */
  if( ( noerr = coords_destroy( &corps ) ) )
    return(noerr) ; 

  return(0);
}
