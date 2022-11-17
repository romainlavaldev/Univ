#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <ecran.h>
int Ecran_Nb_Ref;
/*
 * Lecture dimensions de la console 
 */ 
static
void ecran_dim_console_get(int *col, int * lig)
{
  struct winsize win;
 
#ifdef _MAC_OS
   ioctl(0, TIOCGSIZE, &win); 
#else
   ioctl(0, TIOCGWINSZ, &win); 
#endif

   /*   C'est la meme chose */
   *col = win.ws_col;
   *lig = win.ws_row;
}

/*
 * Methodes d'acces 
 */
extern 
WINDOW * ecran_ligne_get( const ecran_t * const ecran ) 
{
  return( ecran->ligne ) ; 
}

extern 
WINDOW * ecran_messages_get( const ecran_t * const ecran ) 
{
  return( ecran->messages ) ; 
}

extern 
ecran_ligne_id_t  ecran_y_messages_get( const ecran_t * const ecran ) 
{
  return( ecran->y_messages ) ; 
}

extern 
int ecran_largeur_get( const ecran_t * const ecran ) 
{
  return( ecran->largeur ) ; 
}



/*
 * Creation fenetre du ligne 
 */

extern 
ecran_t * ecran_creer( ) 
{
  ecran_t * ecran = ECRAN_NULL ;
  static boolean_t first = B_TRUE ; 

  if( first ) 
    {
      /* Initialisation compteur de references sur les objets ecran */
      Ecran_Nb_Ref = 0 ; 

      /* Initialisation de la bibliothèque curses */
      initscr() ;	/* Init de l'ecran */
      curs_set(0) ;	/* Curseur invisible (si supporte) */

      first = B_FALSE ; 
    }

  /* Incrementation des references sur un objet ecran  */
  Ecran_Nb_Ref++ ; 

  if( (ecran = (ecran_t *)malloc(sizeof(ecran_t))) == NULL )
    {
      fprintf( stderr , "ecran_creer: pd d'llaocation memoire (%lu octets demandes)\n",
	       (long unsigned int)sizeof(ecran_t) ) ;
      return(NULL) ; 	       
    }

  int H  ; /* Hauteur Console */
  int L  ; /* Largeur Console */
  ecran_dim_console_get( &L , &H ) ; 

  /*
   * Creation fenetre de la ligne 
   *
   * Hauteur fenetre =  
   *   - ligne 0      : bord haut fenetre (.)
   *   - ligne 1      : ligne vide 
   *   - ligne 2      : sections sens Ouest --> Est 
   *   - ligne 3      : sections voies uniques
   *   - ligne 4      : sections sens Est --> Ouest 
   *   - ligne 5      : ligne vide
   *   - ligne 6      : bord bas fenetre (.)
   *
   * Largeur fenetre =  meme largeur que la console 
   *   - col 0       : bord gauche fenetre (.)
   *   - col 1       : colonne vide 
   *   - col 2 a L-3 : affichage de la ligne
   *   - col L-2     : colonne vide 
   *   - col L-1     : bord droit fenetre  (.)
   * 
   * Placement       = en haut et a gauche de l'ecran 
   */
  ecran->ligne =  newwin( 7 , L , 0 , 0 );
  box( ecran->ligne , ACS_VLINE , ACS_HLINE ) ;

  ecran->largeur = L-2 ; 
  /* 
   * Creation fenetre des messages 
   * Hauteur fenetre = 1 ligne message 
   *                 + 2 lignes pour le cadre (bords haut et bas)
   * Largeur fenetre = meme largeur que la console 
   * Placement       = en dessous la fenetre du ligne 
   */
  ecran->y_messages = 7  ;
  ecran->messages = newwin( 3 , L , ecran->y_messages , 0 );
  box( ecran->messages , ACS_VLINE , ACS_HLINE ) ;
  
  /* 
   * Redirection de la sortie erreur standard pour 
   * afficher les erreurs dans la fenetre des messages 
   */
  /* - creation fichier */
  char nom_err[1024] ; 
  int fd_err ; 
  sprintf( nom_err , "%d_stderr" , getpid() ) ;
  ecran->nom_err = (char*)malloc( strlen(nom_err)+1 * sizeof(char) ) ;
  strcpy( ecran->nom_err , nom_err );
  if( ( fd_err = open( nom_err , O_RDWR | O_CREAT , 0666 ) ) == -1 )
    {
      char mess[1024] ; 
      sprintf( mess , "ecran_creer: impossible d'ouvrir %s\n" , nom_err );
      perror( mess ) ; 
      return(ECRAN_NULL) ;
    }
  
  /* - redirection */
  close(2) ;
  dup(fd_err) ;
  close(fd_err) ; 

  return(ecran) ; 
}

/*
 * Destruction fenetre de la ligne 
 */

extern 
int ecran_detruire( ecran_t ** ecran ) 
{
  if( ecran_existe((*ecran)) )
    {
      /* Destrcution des fenetres */
      delwin((*ecran)->ligne) ;
      delwin((*ecran)->messages) ;

      /* Retablissement de la sortie erreur standard a l'ecran */
      close(2) ; 
      dup(1) ; 
      unlink( (*ecran)->nom_err) ;
      free( (*ecran)->nom_err ) ;
 
      /* Liberation structure ecran */
      free((*ecran)) ; 

      (*ecran) = NULL ;
    }
 /* Decrementation compteur de references */
  Ecran_Nb_Ref-- ; 

  /* Fermeture bibliotheque curses */
  if( Ecran_Nb_Ref == 0 )
    {
      endwin() ; 
    }
 
  return(OK) ; 
}

/*
 * Effacement d'un message
 */
static
void ecran_message_effacer( ecran_t * const ecran )
{  
  werase( ecran->messages ) ; 
  box( ecran->messages ,  ACS_VLINE , ACS_HLINE ) ;

  wrefresh( ecran->messages ) ; 
}

/*
 * Affichage d'un message en bas de la fenetre
 */
static
void ecran_message_display( ecran_t * const ecran , char * const mess )
{
  size_t lg_mess = strlen(mess) ; 

  if( lg_mess > ECRAN_LG_MESS ) 
    {
      /* Affichage du message directement */
      mvwprintw( ecran->messages , 1 , 2 , mess ) ; 
    }
  else
    {
      /* Effacement d'un eventuel message precedent */
      ecran_message_effacer( ecran ) ; 

      /* Affichage sur la fenetre */
      mvwprintw( ecran->messages , 1 , 2 , mess ) ; 
    }
  wrefresh( ecran->messages ) ; 
}

static
void ecran_message_droite_display( ecran_t * const ecran , char * const mess )
{
  char mess_w[ECRAN_LG_MESS] ; 
  static char blancs[ECRAN_LG_MESS] ; 
  static boolean_t first = B_TRUE ;
  const int Largeur = ecran_largeur_get(ecran) ; 
  const int nb_blancs = Largeur-strlen(mess) ;  

 /* -------- */
  if( first )
    {
      int i = 0 ; 
      for( i=0 ; i<ECRAN_LG_MESS ; i++ ) 
	blancs[i] = ' ' ;
      first = B_FALSE ;
    }
 /* -------- */
 
  strncpy( mess_w , blancs , nb_blancs ) ;
  mess_w[nb_blancs-1] = '\0' ;
  strcat( mess_w , mess ) ;

  /* Affichage sur la fenetre */
  mvwprintw( ecran->messages , 1 , 2 , mess_w ) ; 

  wrefresh( ecran->messages ) ; 
}

extern
void ecran_message_afficher( ecran_t * const ecran , char * const mess )
{
  ecran_message_display( ecran , mess ) ; 
}

extern
void ecran_message_pause_afficher( ecran_t * const ecran , char * const mess )
{
  ecran_message_display( ecran , mess ) ;
  sleep(ECRAN_PAUSE_MESS) ;
}

extern
void ecran_message_droite_afficher( ecran_t * const ecran , char * const mess )
{
  ecran_message_droite_display( ecran , mess ) ; 
}

extern
void ecran_message_droite_pause_afficher( ecran_t * const ecran , char * const mess )
{
  ecran_message_droite_display( ecran , mess ) ;
  sleep(ECRAN_PAUSE_MESS) ;
}



/*
 * Tests
 */

extern 
boolean_t  ecran_existe( const ecran_t * const ecran ) 
{
  if( ecran == NULL )
    return(B_FALSE) ; 
  else
    return(B_TRUE) ; 
}


/* 
 * Affichage de la sortie standard d'erreurs sur l'ecran 
 * dans la fenetre des messages 
 */

extern 
void ecran_stderr_afficher( ecran_t * const ecran ) 
{
  int fd_err ; 
  char buffer[ECRAN_LG_MESS+1] ;
  int nb_lus ;

  /* Ouverture fichier erreurs */
  if(  ( fd_err = open( ecran->nom_err , O_RDONLY , 0666 ) ) == -1 ) 
    {
      char mess[1024] ; 
      sprintf( mess , "Impossible d'ouvrir le fichier %s" , ecran->nom_err ) ;
      ecran_message_pause_afficher( ecran , mess ) ;
      return ; 
    }

  /* Affichage du contenu */
  while( ( nb_lus = read( fd_err , buffer , ECRAN_LG_MESS ) ) )
    {
      buffer[nb_lus] = '\0' ;
      ecran_message_pause_afficher( ecran , buffer ) ;
    }

  /* Fermeture fichier erreurs */
  close(fd_err) ; 

}
