#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdarg.h>

#include <ecran.h>

/*
 * Lecture dimensions de la console 
 */ 
static
void ecran_dim_console_get(int *col, int * lig)
{
  struct winsize win;

#ifdef _MAC_OS_
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
WINDOW * ecran_affichage_get( const ecran_t * const ecran ) 
{
  return( ecran->affichage ) ; 
}

extern 
WINDOW * ecran_messages_get( const ecran_t * const ecran ) 
{
  return( ecran->messages ) ; 
}

extern 
int ecran_y_messages_get( const ecran_t * const ecran ) 
{
  return( ecran->y_messages ) ; 
}

extern 
int ecran_largeur_get( const ecran_t * const ecran ) 
{
  return( ecran->largeur ) ; 
}

extern 
int ecran_hauteur_get( const ecran_t * const ecran ) 
{
  return( ecran->y_messages-2 ) ; 
}

/*
 * Creation d'un ecran 
 * On ne peut avoir qu'un ecran par console/terminal 
 * si H_affichage = 0 --> hauteur ecran = hauteur console 
 * si L_affichage = 0 --> largeur ecran = largeur console
 */

extern 
ecran_t * ecran_creer( const int H_affichage , const int L_affichage ) 
{
  ecran_t * ecran = ECRAN_NULL ;
  int H_affichage_W = H_affichage ; 
  int L_affichage_W = L_affichage ;

  /* Initialisation de la bibliotheque curses */
  initscr() ;	/* Init de l'ecran */
  curs_set(0) ;	/* Curseur invisible (si supporte) */

  
  if( (ecran = (ecran_t *)malloc(sizeof(ecran_t))) == NULL )
    {
      fprintf( stderr , "ecran_creer: pd d'allocation memoire (%lu octets demandes)\n",
	       (long unsigned int)sizeof(ecran_t) ) ;
      return(NULL) ; 	       
    }

  int H_console  ; /* Hauteur Console */
  int L_console  ; /* Largeur Console */
  ecran_dim_console_get( &L_console , &H_console ) ; 

  /*
   * Creation fenetre d'affichage 
   *
   * Hauteur fenetre =  
   *   - ligne  0                  : bord haut fenetre (.)
   *   - lignes [1..H_affichage-1] : fenetre affichage 
   *   - ligne  H_affichage        : bord bas fenetre (.)
   *
   * Largeur fenetre =  meme largeur que la console 
   *   - col 0                 : bord gauche ecran (.)
   *   - col 1 a L_affichage-1 : fenetre d'affichage
   *   - col L_affichage       : bord droit ecran  (.)
   * 
   * Placement       = en haut et a gauche de l'ecran 
   */

  /* 
   * Largeur par defaut = largeur de la console 
   *                      - bords fenetre affichage droit / gauche 
   */
  if( L_affichage == 0 ) 
    L_affichage_W = L_console-2 ;

  /* 
   * Hauteur par defaut = hauteur de la console 
   *                      - bords fenetre affichage haut / bas (2)
   *                      - hauteur fenetre messages (3)  
   */
  if( H_affichage == 0 ) 
    H_affichage_W = H_console-5;

  if( (H_affichage_W > H_console) || (L_affichage_W > L_console) )
    {
      fprintf( stderr , "ecran_creer: Dimensions ecran demandees > Dimensions console \n" ) ;
      fprintf( stderr , "             Hauteur demandee ecran = %hu / Hauteur console = %hu \n", (unsigned short)H_affichage_W , (unsigned short)H_console ) ; 
      fprintf( stderr , "             Largeur demandee ecran = %hu / Largeur console = %hu \n", (unsigned short)L_affichage_W , (unsigned short)L_console ) ; 
      return(NULL) ; 
    }

  ecran->affichage =  newwin( H_affichage_W+2 , L_affichage_W+2 , 0 , 0 );
  box( ecran->affichage , ACS_VLINE , ACS_HLINE ) ;

  ecran->largeur = L_affichage_W ; 
  /* 
   * Creation fenetre des messages 
   * Hauteur fenetre = 1 ligne message 
   *                 + 2 lignes pour le cadre (bords haut et bas)
   * Largeur fenetre = meme largeur que la console 
   * Placement       = en dessous la fenetre d'affichage 
   */
  ecran->y_messages = H_affichage_W+2 ;
  ecran->messages = newwin( 3 , L_affichage_W+2 , ecran->y_messages , 0 );
  box( ecran->messages , ACS_VLINE , ACS_HLINE ) ;
  
  /* 
   * Redirection de la sortie erreur standard pour 
   * afficher les erreurs dans la fenetre des messages 
   */
  /* - creation fichier */
  char nom_err[512] ; 
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
 * Destruction d'un ecran 
 */

extern 
err_t ecran_detruire( ecran_t ** ecran ) 
{
  if( ecran_existe((*ecran)) )
    {
      /* Destruction des fenetres */
      delwin((*ecran)->affichage) ;
      delwin((*ecran)->messages) ;

      /* Fermeture bibliotheque curses */
      endwin() ; 

      /* Retablissement de la sortie erreur standard a l'ecran */
      close(2) ; 
      char c ;
      int fd_err = -1 ;
      if( ( fd_err = open((*ecran)->nom_err , O_RDONLY , 0666 ) ) == -1 )
	{
	  fprintf( stderr , "ecran_detruire: pb ouverture fichier %s\n" , (*ecran)->nom_err ) ;
	  return(ERR_FILE) ; 
	}
      
      while( read( fd_err , &c , 1 ) )
	{
	  write( 1 , &c , 1 ) ; 
	}
      close(fd_err) ;
      
      unlink( (*ecran)->nom_err) ;
      free( (*ecran)->nom_err ) ;

      /* Liberation structure ecran */
      free((*ecran)) ; 

      (*ecran) = NULL ;
    }
  
  return(CORRECT) ; 
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
  static booleen_t first = VRAI ;
  const int Largeur = ecran_largeur_get(ecran) ; 
  const int nb_blancs = Largeur-strlen(mess) ;  

 /* -------- */
  if( first )
    {
      int i = 0 ; 
      for( i=0 ; i<ECRAN_LG_MESS ; i++ ) 
	blancs[i] = ' ' ;
      first = FAUX ;
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

extern
void ecran_message_stop_afficher( ecran_t * const ecran , char * const mess )
{
  WINDOW * messages = ecran_messages_get(ecran) ;
  char str[2] ;
  
  ecran_message_display( ecran , mess ) ;
  wmove( messages, 1 , 1 );
  wchgat( messages , strlen(mess)+1 , A_BLINK, 0, NULL);
  wrefresh(messages);
  wgetstr(messages , str );
}

/*
 * Tests
 */

extern 
booleen_t  ecran_existe( const ecran_t * const ecran ) 
{
  if( ecran == NULL )
    return(FAUX) ; 
  else
    return(VRAI) ; 
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

/* 
 * Affichages d'une chaine de caracteres dans la fenetre d'affichage de l'ecran 
 */

extern 
void ecran_lc_wprint( ecran_t * const ecran , 
		      const int lig , 
		      const int col , 
		      char * const mess , 
		      unsigned int micro_seconds ,
		      ecran_mode_t video_mode )  
{
  WINDOW * fenetre = ecran_affichage_get(ecran) ;
  int H = ecran_hauteur_get(ecran) ;
  int L = ecran_largeur_get(ecran) ;

  /* Assertion */

  if( ( lig < 0 ) || (lig >= H ) )
    {
      fprintf( stderr, "ecran_lc_wprint: mauvais indice de ligne %d, devrait etre dans [0..%d]\n" ,
	       lig , H-1 );
      return ; 
    }

  if( ( col < 0 ) || ( col >= L ) )
    {
      fprintf( stderr, "ecran_lc_wprint: mauvais indice de colonne %d, devrait etre dans [0..%d]\n" ,
	       col, L-1 );
      return ; 
    }

  /*-----------*/
  
  if( video_mode == ECRAN_REVERSE ) wattron(  fenetre , A_STANDOUT ) ;

  mvwprintw( fenetre ,
	     lig+1 ,  /* decalage du bord haut   */
	     col+1 ,  /* decalage du bord gauche */
	     mess );
  wrefresh( fenetre ) ;

  if( video_mode == ECRAN_REVERSE ) wattroff( fenetre , A_STANDOUT ) ;

  if( micro_seconds > 0 ) usleep(micro_seconds) ;
}

extern 
void ecran_coord_wprint( ecran_t * const ecran , 
			 const coord_t * const coord,
			 char * const mess , 
			 unsigned int micro_seconds ,
			 ecran_mode_t video_mode )  
{
  ecran_lc_wprint( ecran , 
		   coord_lig_get(coord) ,
		   coord_col_get(coord) ,
		   mess ,
		   micro_seconds ,
		   video_mode )  ;
}




