#include <coord.h>

/*
 * Fonctions get/set des attributs d'une coordonnee
 *=================================================
 */

extern 
int coord_ligne_get( const coord_t c )
{
  return(c.l) ;
}
extern 
int coord_ligne_set( coord_t * const c , 
		      const int ligne )
{
  c->l = ligne ;
  return(0) ;
}

extern 
int coord_colonne_get( const coord_t c )
{
  return(c.c) ;
}
extern 
int coord_colonne_set( coord_t * const c , 
			const int colonne )
{
  c->c = colonne ;
  return(0);
}
extern 
off_t coord_position_get( const coord_t c )
{
  return(c.pos) ;
}
extern 
int coord_position_set( coord_t * const c , 
			const off_t position )
{
  c->pos = position  ;
  return(0);
}

/* 
 * Ecriture/Lecture globale d'une coordonnee
 */

extern
int coord_set( coord_t * const coord , 
	       const int ligne,
	       const int colonne,
	       const off_t position )
{
  int noerr = 0 ; 

  if( ( noerr = coord_ligne_set(coord,ligne) ) )
    return(noerr) ; 
  if( ( noerr = coord_colonne_set(coord,colonne) ) )
    return(noerr) ;
  if( ( noerr = coord_position_set(coord,position) ) )
    return(noerr) ;
  return(0) ;
}


extern
int coord_get( const coord_t coord , 
		int * ligne,
		int * colonne,
		off_t * position )
{
  (*ligne)    = coord_ligne_get(coord) ;
  (*colonne)  = coord_colonne_get(coord) ;
  (*position) = coord_position_get(coord) ;
  return(0) ; 
}


/*
 *===========================================
 * Realisations des primitives des sous-types
 *===========================================
 */

extern
char *
coord_ori2string( const orientation_t ori )
{
     switch( ori )
     {
	case VERTICAL : 
	     return("VERTICALE");
	     break;
	case HORIZONTAL :
	     return("HORIZONTALE");
	     break;
	default :
	     return("inconnue");
	     break;
     }
}


extern
char *
coord_dir2string( const direction_t dir )
{
     switch( dir )
     {
	case NORD :
	     return("NORD");
	     break ;
	case EST :
	     return("EST");
	     break ;
	case SUD :
	     return("SUD");
	     break ;
	case OUEST :
	     return("OUEST");
	     break ;
	default :
	     return("inconnue");
	     break ;
     }
}

/* 
 * Affichage sur la sortie standard
 */

extern
void 
coord_printf( const coord_t coord )
{
  printf( "[%d,%d](%lld)" , 
	  coord_ligne_get(coord) , 
	  coord_colonne_get(coord) ,
	  coord_position_get(coord) );
}

extern
void 
coord_fprintf( FILE * restrict stream, 
	       const coord_t coord )
{
  fprintf( stream , "[%d,%d](%lld)" , 
	   coord_ligne_get(coord) , 
	   coord_colonne_get(coord) ,
	   coord_position_get(coord) );
}

/*
 * Ecriture dans un fichier 
 */
extern
int coord_write( const int fd , /* Descriteur du fichier */
		 const coord_t coord )
{
  coord_t coord_w = coord ; 
  const size_t taille = sizeof(coord_t) ;
  ssize_t nb_ecrits = 0 ; 

  if( ( nb_ecrits= write( fd , &coord_w , taille ) != taille ) )
    {
      char mess[256] ;
      sprintf( mess , "coord_write: pb write : %lu octets ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(-1) ; 
    } 
  return(0);
}

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture 
 * le parametre "coord" doit pointer sur une zone suffisante pour stocker une coord_t 
 */
extern
int coord_read( const int fd , /* Descriteur du fichier */
		coord_t * const coord )
{
  const size_t taille = sizeof(coord_t) ;
  ssize_t nb_lus = 0 ; 

  if( coord == NULL ) 
    {
      fprintf( stderr, "coord_read: coord inexistante\n") ; 
      return(-1)  ;
    }

  if( ( nb_lus = read( fd , coord, taille ) != taille ) )
    {
      char mess[256] ;
      sprintf( mess , "coord_read: pb read : %lu octets lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(-1) ; 
    } 
  return(0);
}



/* 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */

/* Comparaison globale */

extern 
int coord_comparer( const coord_t c1,
		    const coord_t c2 )
{
     int cmp_l = c1.l - c2.l ;
     int cmp_c = c1.c - c2.c ;
     int cmp_pos = (int)(c1.pos - c2.pos) ;

     /*----------*/

     if( cmp_l )
	  return(cmp_l);
     else
     {
	  if( cmp_c )
	       return(cmp_c);
	  else
	       return(cmp_pos) ;
     }		    
}

/* Comparaison sur ligne/colonne */

extern 
int coord_xy_comparer( const coord_t c1,
		       const coord_t c2 )
{
     int cmp_l = c1.l - c2.l ;
     int cmp_c = c1.c - c2.c ;

     /*----------*/

     if( cmp_l )
	  return(cmp_l);
     else
       return(cmp_c);
}

/* Comparaison sur offset (position dans le fichier) */

extern 
int coord_pos_comparer( const coord_t c1,
			const coord_t c2 )
{
     int cmp_pos = (int)(c1.pos - c2.pos) ;

     /*----------*/

     return(cmp_pos);
}



/* 
 * Affectation des coordonnees d'une case 
 */

extern
int
coord_copier( coord_t * const coord_cible,
	      const coord_t coord_source )
{
  int noerr = 0 ; 

  if( ( noerr = coord_ligne_set( coord_cible , 
				 coord_ligne_get(coord_source) ) ) )
    return(noerr) ;
  
  if( ( noerr = coord_colonne_set( coord_cible , 
				   coord_colonne_get(coord_source) ) ) )
    return(noerr) ;
  
  if( ( noerr = coord_position_set( coord_cible , 
				    coord_position_get(coord_source) ) ) )
    return(noerr) ;
  
  return(noerr) ;
}


/* 
 * Determination de l'orientation de 2 coordonnees
 */

extern
orientation_t
coord_orientation_donner( const coord_t c1 ,
			  const coord_t c2 )
{
 
     if( c1.l == c2.l )
     {
	  return( HORIZONTAL );
     }
     else
     {
       return( VERTICAL );
     }
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
  coord.pos = -1 ; 
  return(coord) ; 
}
