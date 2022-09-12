#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <mer.h>


/* 
 * Affichage d'une case/cellule de la mer 
 */

extern
void
mer_case_printf( case_t cellule )
{
     printf( "%c" , cellule );
}

/* 
 * Affichage de la mer
 */

extern 
int
mer_afficher( const int fd )
{
     
     int nb_lig = 0 ; 
     int nb_col = 0 ;
     int nb_bateaux = 0 ; 
     char cellule = MER_CASE_LIBRE ;
     int l,c ; 
     char mess[MESS_LONGUEUR];

     /*----------*/

     /* 
      * Lecture des dimensions de la mer 
      */

     mer_dim_lire( fd, &nb_lig, &nb_col );

     /* 
      * Positionnement debut mer 
      */

     if( lseek( fd , MER_DEBUT_NB_BATEAUX , SEEK_SET ) == -1 )
     {
	  sprintf( mess , "mer_afficher : Pb lseek positionnement debut fichier mer (fd=%d)\n" , 
		   fd );
	  perror(mess);
	  return(ERREUR) ;
     }
     
     if( read( fd , &nb_bateaux , sizeof(int)) == -1 )
       {
	 sprintf( mess , "mer_afficher : erreur sur lecture nb_bateaux\n");
	 perror(mess);
	 return(ERREUR) ;
       }
#ifdef _DEBUG_ 
     printf("mer_afficher --> affichage de la mer [%d,%d]\n", 
	    nb_lig , nb_col );
#endif

     /* 
      * Affichage du nombre de bateaux
      */

     fprintf( stdout , "    Nb bateaux = %d\n" , nb_bateaux ) ; 

     /* 
      * Affichage de l'aire de jeu
      */

     /* Affichage 1ere ligne */
     fprintf( stdout , "    " ) ; for( c=0 ; c<nb_col ; c++ ) fprintf( stdout , "|%2d " , c ); fprintf(stdout , "|\n");
     fprintf( stdout , "----" ) ; for( c=0 ; c<nb_col ; c++ ) fprintf( stdout , "|---" ) ; fprintf(stdout , "|\n");

     /* Affichage corps */
     for( l=0 ; l<nb_lig; l++ )
     {
	  fprintf( stdout , " %2d " , l ) ;
	  for( c=0 ; c<nb_col ; c++ )
	  {
	       if( read( fd , &cellule, sizeof(char)) == -1 )
	       {
		    sprintf( mess , "mer_afficher : erreur sur lecture aire[%i,%i]\n",l,c);
		    perror(mess);
		    return(ERREUR) ;
	       }
	       fprintf( stdout , "| " );
	       mer_case_printf(  cellule );
	       fprintf( stdout , " " );
	  }
	  
	  fprintf(stdout , "|\n");
	  fprintf( stdout , "----" ) ; for( c=0 ; c<nb_col ; c++ ) fprintf( stdout , "|---" ); fprintf(stdout , "|\n");
     }

     /* Affichage derniere ligne */
     fprintf(stdout , "\n");

     return(CORRECT);
}

/* 
 * Initialisation du fichier de la mer
 */

extern 
int 
mer_initialiser( const char * fich_mer , 
		 const int nb_lig , 
		 const int nb_col )
{
     int fd ;
     int l,c ;
     int nb_bateaux ;
     case_t tcl = MER_CASE_LIBRE ;
     char mess[MESS_LONGUEUR] ;

     /*----------*/

#ifdef _DEBUG_ 
     printf("mer_init --> debut initialisation mer %s[%d,%d]\n", 
	    fich_mer , nb_lig , nb_col );
#endif

     /* 
      * Ouverture fichier mer
      */
     if( ( fd = open( fich_mer , O_WRONLY | O_CREAT , 0666)) == -1 )
     {
	  sprintf( mess, "Pb open sur %s\n", fich_mer);
	  perror(mess);
	  return(ERREUR);
     }

     /* 
      * Ecriture des dimensions 
      */
     
     if( write( fd , &nb_lig , sizeof(int)) == -1 )
     {
	  sprintf( mess , "mer_init : erreur sur ecriture nb lignes=%i\n", nb_lig );
	  perror(mess);
	  return(ERREUR) ;
     }

     if( write( fd , &nb_col , sizeof(int)) == -1 )
     {
	  sprintf( mess , "mer_init : erreur sur ecriture nb colonnes=%i\n", nb_col);
	  perror(mess);
	  return(ERREUR) ;
     }

     /*
      * Ecriture du nombre de bateaux 
      */

     nb_bateaux = 0 ;
     if( write( fd , &nb_bateaux , sizeof(int)) == -1 )
     {
	  sprintf( mess , "mer_init : erreur sur ecriture nb colonnes=%i\n", nb_col);
	  perror(mess);
	  return(ERREUR) ;
     }

     /* 
      * Ecriture de l'aire de jeu vide
      */

     for( l=0 ; l<nb_lig ; l++ )
     {
	  for( c=0 ; c<nb_col ; c++ )
	  {
	       if( write( fd , &tcl , MER_TAILLE_CASE) == -1 )
	       {
		    sprintf( mess , "mer_init : erreur sur ecriture %s[%i,%i]\n",fich_mer, l,c);
		    perror(mess);
		    return(ERREUR) ;
	       }
	  }
     }

     /*
      * Fermeture fichier mer
      */
     close(fd);

#ifdef _DEBUG_ 
     printf("mer_init --> fin initialisation mer %s\n", fich_mer);
#endif
     
     return(CORRECT);
}


/* 
 * Lecture du nombre de bateaux dans la mer
 */

extern 
int 
mer_nb_bateaux_lire( const int fd, /* descritpteur fichier mer */
		     int * nb_bateaux      ) /* Nombre de bateaux */
{

     char mess[MESS_LONGUEUR] ;

     /*----------*/

     /* 
      * Positionnement sur le nombre de bateaux 
      * (saut des dimensions depuis le bedut du fichier)
      */

     if( lseek(fd, MER_DEBUT_NB_BATEAUX , SEEK_SET) == -1 )
     {
	  sprintf( mess, "mer_nb_bateaux_lire : Pb lseek positionnement nombre de bateaux dans fd %d",
		   fd );
	  perror(mess);
 	  return(ERREUR) ;
     }

     /* 
      * Lecture du nombre de bateaux 
      */

     if( read( fd , nb_bateaux , sizeof(int)) == -1 )
     {
	  perror("mer_nb_bateaux_lire : Pb read sur lecture nb bateaux");
	  return(ERREUR) ;
     }

     return(CORRECT);
}


/* 
 * Ecriture du nombre de bateaux dans la mer
 */

extern 
int 
mer_nb_bateaux_ecrire( const int fd, /* descritpteur fichier mer */
		       const int nb_bateaux ) /* Nombre de bateaux */
{
     int nb = nb_bateaux ;
     char mess[MESS_LONGUEUR] ;

     /*----------*/

     /* 
      * Positionnement sur le nombre de bateaux 
      * (saut des dimensions depuis le bedut du fichier)
      */

     if( lseek(fd, MER_DEBUT_NB_BATEAUX , SEEK_SET) == -1 )
     {
	  sprintf( mess , "mer_nb_bateaux_lire : Pb lseek positionnement nombre de bateaux dans fd=%d",
		   fd );
	  perror(mess);
 	  return(ERREUR) ;
     }

     /* 
      * Ecriture du nombre de bateaux 
      */

     if( write( fd , &nb , sizeof(int)) == -1 )
     {
	  perror("mer_nb_bateaux_lire : Pb read sur lecture nb bateaux");
	  return(ERREUR) ;
     }

     return(CORRECT);
}

/*
 * Recherche des cases voisines d'un bateau dans la mer 
 * La liste des voisins est creee
 */

extern
int 
mer_voisins_rechercher( const int fd,		  /* Fichier mer */
			const bateau_t * const bateau,	  /* Bateau */
			coords_t ** liste_voisins) /* Coordonnees des cases voisines */
{
     /* Mer */
     int nb_lig , nb_col  ;			/* Dimensions tableau */
     size_t taille_entete = MER_TAILLE_ENTETE ; /* Caracteristiques fichier */
     size_t taille_case =  MER_TAILLE_CASE ;
     size_t taille_ligne ;

     /* Bateau */
     int proue_lig , proue_col ;	/* Coord proue */
     off_t proue_pos ;
     orientation_t orientation ;	
     coord_t coord_voisin ;

     /*----------*/

     /* Liste des voisins =
      * - si bateau vertical : une case au dessus de la proue, une case au dessous de la poupe, cases colonne d'avant et colonne d'apres
      * - si bateau horizontal : une case a gauche de la proue, une case a droite de la poupe, cases ligne du dessus et ligne du dessous
      */

     /* 
      * Lecture des dimensions de la mer 
      */

     mer_dim_lire( fd , &nb_lig , &nb_col );

/* #ifdef _DEBUG_  */
/*      printf("mer_voisins_rechercher --> recherche des voisins du bateau\n"); */
/*      bateau_printf( bateau ); */
/*      printf("dans la mer[%d,%d]\n", nb_lig , nb_col ); */
/* #endif */

     taille_ligne = (size_t)(nb_col*taille_case) ;

     /* 
      * Determination de l'orientation du bateau 
      */
     
     orientation = coord_orientation_donner(  coords_coord_get( bateau_corps_get(bateau) , 0 ),
					      coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ) ;
     
     /* 
      * Creation liste des coordonnees des voisins 
      */
     coord_get( coords_coord_get( bateau_corps_get( bateau ) , 0 ) , 
		&proue_lig , &proue_col , &proue_pos );

     if( ( (*liste_voisins) = coords_new() ) == NULL )
       return(-1) ; 
     
     switch( orientation )
     {
	case VERTICAL : 
	     {
		  int l ; /* indice de ligne */
		  int poupe_lig = proue_lig + BATEAU_TAILLE - 1 ;

		  /*-----*/

		  /* une case au NORD de la proue */
		  if( proue_lig > 0 )
		  {
		       coord_set( &coord_voisin , proue_lig-1 , proue_col , 
				  (off_t)(taille_entete + ((proue_lig-1)*taille_ligne) + (proue_col*taille_case)) ) ;
		       coords_coord_add( (*liste_voisins) , coord_voisin );
		  }

		  /* cases a l'EST et a l'OUEST du corps */
		  for( l = 0 ; l < BATEAU_TAILLE ; l++ )
		  {
		       if( proue_lig+l < nb_lig )
		       {
			    if( proue_col > 0 )
			    {
				 coord_set( &coord_voisin , proue_lig+l , proue_col-1 , 
					    (off_t)(taille_entete + ((proue_lig+l)*taille_ligne) + ((proue_col-1)*taille_case)) ) ;
				 coords_coord_add( (*liste_voisins) , coord_voisin );
			    }

			    if( proue_col < nb_col-1 )
			    {
				 coord_set( &coord_voisin , proue_lig+l , proue_col+1 , 
					    (off_t)(taille_entete + ((proue_lig+l)*taille_ligne) + ((proue_col+1)*taille_case)) ) ;
				 coords_coord_add( (*liste_voisins) , coord_voisin );
			    }
		       }
		  }
		  
		  /* une case au SUD de la poupe */
		  if( poupe_lig+1 < nb_lig )
		  {
		       coord_set( &coord_voisin , poupe_lig+1 , proue_col , 
				  (off_t)(taille_entete + ((poupe_lig+1)*taille_ligne) + (proue_col*taille_case)) ) ;
		       coords_coord_add( (*liste_voisins) , coord_voisin );
		  }

		  break ;
	     }
	case HORIZONTAL : 
	     {
		  int c ; /* Indice de colonne */
		  int poupe_col = proue_col + BATEAU_TAILLE - 1 ;

		  /*-----*/

		  /* une case a l'OUEST de la proue */
		  if( proue_col > 0 )
		  {
		       coord_set( &coord_voisin , proue_lig , proue_col-1 , 
				  (off_t)(taille_entete + (proue_lig*taille_ligne) + ((proue_col-1)*taille_case)) ) ;
		       coords_coord_add( (*liste_voisins) , coord_voisin );
		  }

		  /* cases au NORD et au SUD du corps */
		  for( c = 0 ; c < BATEAU_TAILLE ; c++ )
		  {
		       if( proue_col+c < nb_col )
		       {
			    if( proue_lig > 0 )
			    {
				 coord_set( &coord_voisin , proue_lig-1 , proue_col+c , 
					       (off_t)(taille_entete + ((proue_lig-1)*taille_ligne) + ((proue_col+c)*taille_case)) ) ;
				 coords_coord_add( (*liste_voisins) , coord_voisin );
			    }
			    if( proue_lig < nb_lig-1 )
			    {
				 coord_set( &coord_voisin , proue_lig+1 , proue_col+c , 
					       (off_t)(taille_entete + ((proue_lig+1)*taille_ligne) + ((proue_col+c)*taille_case)) ) ;
				 coords_coord_add( (*liste_voisins) , coord_voisin );
			    }
		       }
		  }
		  
		  /* une case a l'EST de la poupe */
		  if( poupe_col+1 < nb_col )
		  {
		       coord_set( &coord_voisin , proue_lig , poupe_col+1 , 
				     (off_t)(taille_entete + ((proue_lig)*taille_ligne) + ((poupe_col+1)*taille_case)) ) ;
		       coords_coord_add( (*liste_voisins) , coord_voisin );
		  }

		  break ;
	     }
	default : 
	     {
		  fprintf( stderr , "mer_voisins_rechercher: mauvaise orientation du bateau\n");
		  bateau_printf( bateau );
		  return(ERREUR);
	     }
     }
     
     return(CORRECT) ;
}

/*
 * Affichage du contenu d'une liste de cases dans la mer 
 */

extern
void
mer_voisins_afficher( const int fd,			/* Fichier mer */
		      coords_t * const liste_cases ) 	/* Coordonnees des cases voisines */
{
     int i ;
     case_t c ;
     const int nb_cases = coords_nb_get(liste_cases) ; 

     /*--------------------*/

     for( i=0 ; i<nb_cases ; i++ )
     {
       coord_printf( coords_coord_get( liste_cases , i ) );
       printf( "--> ");
       mer_case_lire( fd , 
		      coords_coord_get(liste_cases , i )  , 
		      &c ); 
       mer_case_printf( c );
       printf( " <--\n");
     }
}


/*
 * Pose aleatoire d'un bateau sur la mer
 * Si la fonction peut trouver de la place pour initialiser le bateau alors:
 * - Retour de la fonction --> CORRECT
 * - Ecriture des positions d'un bateau dans une zone libre de la mer
 * - Ecrit dans le fichier la marque du bateau dans les cases choisies aleatoirement
 * - Met a jour dans la structure bateau les coordonnees de ces cases
 * Sinon :
 * - Retour de la fonction --> ERREUR
 * - Pas d'ecriture dans le fichier mer
 * - Pas d'affectation de la structure bateau 
 */

extern
int
mer_bateau_initialiser( const int fd,			/* Fichier mer */
			bateau_t * bateau )		/* Bateau */
{
     int nb_lig    , nb_col   ; /* Dimension de la mer */
     int init_lig  , init_col ; /* Coord. de depart */
     int cpt_lig   , cpt_col  ; /* Compteurs ligne/colonne */
     int lig       , col      ; /* Coord.  courantes */
     int sauv_lig  , sauv_col ; /* Sauvegardes ligne/colonne */

     int cpt_orientation       ; /* Compteur d'orientation */
     orientation_t orientation ; /* Orientation ocurante */

     int i ; 
     int no_err = CORRECT ;
     off_t pos ;
    

     coords_t * corps = NULL ;
     coord_t coord_mer ;
     case_t case_mer ;

     booleen_t trouve = FAUX ;
     booleen_t fin_orientation = FAUX ;
     booleen_t fin_corps = FAUX ;

     /*--------------------*/

     /* 
      * Lecture des dimensions de la mer
      */

     mer_dim_lire(fd, &nb_lig, &nb_col) ;

     /*
      * Creation d'un corps vide 
      */

     corps = coords_new() ; 
     for( i=0 ; i<BATEAU_TAILLE ; i++ ) 
       coords_coord_add( corps , COORD_VIDE ) ; 

     /* 
      * Choix aleatoire d'une case de depart 
      */

     /* Choix aleatoire des coordonnees de la case de depart */
     init_lig = (int)(random() %  nb_lig ) ;
     init_col = (int)(random() %  nb_col ) ;
    
     /* 
      * Parcours cyclique des cases du fichier mer
      */
     trouve = FAUX ;

     /* Initialisations lignes */
     lig = init_lig ;
     cpt_lig = 0 ; 
     while( (cpt_lig < nb_lig) && (!trouve) )
       {
	 /* Initialisations colonnes */
	  col = init_col;
	  cpt_col = 0 ;

	  while( (cpt_col < nb_col) && (!trouve) )
	  {
	    /* Initialisations orientation */
	    /* Sauvegarde position de depart */
	    sauv_lig = lig ;
	    sauv_col = col ; 
	    /* Choix aleatoire d'un bateau horizontal ou vertical */
	    orientation = (int)(random() % 2) ;
	    cpt_orientation = 0 ; 
	    fin_orientation = FAUX ; 
	    
	    while( (cpt_orientation < 2) && (!trouve) )
	      {
		/* Test si bateau tient dans la mer */
		switch( orientation ) 
		  {
		  case HORIZONTAL :
		    if( col+BATEAU_TAILLE > nb_col )  
		      {
			orientation = (orientation+1)%2 ;
			cpt_orientation++ ; 
			continue ; 
		      }
		    break ;
		  case VERTICAL : 
		    if( lig+BATEAU_TAILLE > nb_lig )  
		      {
			orientation = (orientation+1)%2 ;
			cpt_orientation++ ;
			continue ;
		      }
		    break ;
		  }

		/* Initialisations corps */
	       i=0 ;
	       fin_corps = FAUX ;
	       while( (i<BATEAU_TAILLE) && (!fin_corps) )
	       {

		 mer_lc2pos( fd , lig , col , &pos ) ;
		 coord_set( &coord_mer , lig , col , pos ) ;
		 mer_case_lire( fd , coord_mer , &case_mer );
		 if( case_mer == MER_CASE_LIBRE )
		   { 
		     coords_coord_set( corps , i , coord_mer ) ; 
		     switch( orientation ) 
		       {
		       case HORIZONTAL :
			 col++ ; 
			 break ;
		       case VERTICAL : 
			 lig++ ;
			 break ;
		       }
		   }
		 else
		   {
		     fin_corps = VRAI ; 
		   }
		 
		 i++ ;      
	       } /* Fin corps */

	       if( !fin_corps )
		 {
		   trouve = VRAI ;
		 }
	       else
		 {
		   /* Restauration position de depart */
		   lig = sauv_lig ; 
		   col = sauv_col ;
		   /* Passage orientation suivante */
		   orientation = (orientation+1)%2 ;
		   cpt_orientation++ ; 
		 }

	      } /* Fin orientation */
		 

	    /* Passage colonne suivante */
	    if(!trouve)
	      { 
		col = (col+1) % nb_col ;
		cpt_col++ ; 
	      }
	  } /* Fin colonnes */

	  /* Passage ligne suivante */
	  if( !trouve) 
	    {	     
	      lig = (lig+1) % nb_lig ;
	      cpt_lig++ ;
	    }
       }

     if( trouve )
       {
	 /* Ecriture du bateau dans le fichier mer */
	 for( i=0 ; i<BATEAU_TAILLE ; i++ )
	   {
	     if( (no_err = mer_case_ecrire( fd,
					    coords_coord_get( corps , i ),
					    bateau_marque_get(bateau) ) ) )
	       return(no_err) ;
	   }

	 /* Affectation des coordonnees du corps du bateau */
	 bateau_corps_set( bateau , corps );
       }
     else
       {
	 no_err = ERREUR ; 
       }

     /* destruction variable de travail */
     coords_destroy(&corps) ; 

     /* Gestion retour */
     return(no_err); 

}

/*
 * Deplacement d'un bateau vertical dans une direction donnee
 * le booleen <deplacement> est positionne a FAUX si le deplacement n'est pas possible
 */

static
int
mer_bateau_vertical_deplacer( const int fd,			/* Fichier mer */ 
			      bateau_t * bateau,		/* Bateau qui va se deplacer */
			      const direction_t direction,	/* Direction du deplacement */
			      coords_t * const liste_voisins,	/* Liste des cases voisines */
			      booleen_t * deplacement )		/* Indique si le deplacement s'est realise */
{
     (*deplacement) = VRAI ;
    
     switch( direction )
     {
	case NORD :
	     {
		  coord_t criteres_nord ;
		  case_t case_nord ;
		  int id_nord ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ) , 
			     &l, &c, &p );
		  coord_set( &criteres_nord , l-1 , c , -1 );
		  if( ( id_nord = coords_coord_seek( liste_voisins,criteres_nord , coord_xy_comparer ) ) == -1 )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  mer_case_lire( fd, 
				 coords_coord_get( liste_voisins , id_nord ) , 
				 &case_nord);
		  if( case_nord != MER_CASE_LIBRE )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  /* Ecriture deplacement dans le fichier mer */
				 
		  mer_case_ecrire( fd, 
				   coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ,
				   MER_CASE_LIBRE );
		  mer_case_ecrire( fd, 
				   coords_coord_get( liste_voisins , id_nord ) ,
				   bateau_marque_get(bateau) );

		  /* Mise a jour deplacement dans le bateau */

		  for( i=BATEAU_TAILLE-1 ; i>0 ; i-- )
		  {
		    coords_coord_set( bateau_corps_get(bateau) , 
				      i ,
				      coords_coord_get( bateau_corps_get(bateau) , i-1 ) ) ;
		  }
		  coords_coord_set( bateau_corps_get(bateau) , 
				      0 ,
				    coords_coord_get( liste_voisins , id_nord ) ) ;
		  break ;
	     }
	case EST :
	     {
		  coord_t criteres_est ;
		  case_t case_est ;
		  int id_est ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ),
			     &l, &c, &p );
		  i=0 ;
		  while( ((*deplacement)) && (i<BATEAU_TAILLE) )
		  {
		       coord_set( &criteres_est , l+i , c+1 , -1 );
		       if( ( id_est = coords_coord_seek( liste_voisins, criteres_est , coord_xy_comparer ) ) == -1 )
		       {
			    (*deplacement) = FAUX ;
		       }
		       else
		       {
			    mer_case_lire( fd, 
					   coords_coord_get( liste_voisins , id_est ), 
					   &case_est);
			    if( case_est != MER_CASE_LIBRE )
				 (*deplacement) = FAUX ;
			    else
				 i++;
		       }

		  }

		  if( !(*deplacement) )
		       break ;
				 
		  /* Deplacement */

		  for( i=0 ; i<BATEAU_TAILLE ; i++ )
		  {
		    coord_get( coords_coord_get( bateau_corps_get(bateau) , i ) ,
			       &l, &c, &p );
		       coord_set( &criteres_est , l , c+1 , -1 );
		       id_est = coords_coord_seek( liste_voisins, criteres_est , coord_xy_comparer ) ;

		       /* Ecriture deplacement dans le fichier mer */
		       mer_case_ecrire( fd , 
					coords_coord_get(liste_voisins,id_est),
					bateau_marque_get(bateau) );

		       mer_case_ecrire( fd , 
					coords_coord_get( bateau_corps_get(bateau) , i ) ,
					MER_CASE_LIBRE );

		       /* Mise a jour deplacement dans le bateau */
		       coords_coord_set( bateau_corps_get(bateau) , 
					 i ,
					 coords_coord_get( liste_voisins , id_est ) ) ;

		  }

		  break;
	     }
	case SUD :
	     {
		  coord_t critere_sud ;
		  case_t case_sud ;
		  int id_sud ;
		  int l , c , i ;
		  off_t p ;

		  /*--------------------*/

		  /* Verification de la position sud */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ,
			     &l, &c, &p );
		  coord_set( &critere_sud , l+1 , c , -1 );
		  if( ( id_sud = coords_coord_seek( liste_voisins, critere_sud , coord_xy_comparer ) ) == -1 )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  mer_case_lire( fd, 
				 coords_coord_get( liste_voisins , id_sud ) , 
				 &case_sud);
		  if( case_sud != MER_CASE_LIBRE )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  /* Ecriture deplacement dans le fichier mer */
				 
		  mer_case_ecrire( fd,
				   coords_coord_get( bateau_corps_get(bateau) , 0 ),
				   MER_CASE_LIBRE );

		  mer_case_ecrire( fd, 
				   coords_coord_get(liste_voisins , id_sud ),
				   bateau_marque_get(bateau) );

		  /* Mise a jour deplacement dans le bateau */

		  for( i=0 ; i<BATEAU_TAILLE-1; i++ )
		  {
		    coords_coord_set( bateau_corps_get(bateau) , 
				      i ,
				      coords_coord_get( bateau_corps_get(bateau) , i+1 ) ) ;
		  }
		  coords_coord_set( bateau_corps_get(bateau) , 
				    BATEAU_TAILLE-1 ,
				    coords_coord_get( liste_voisins , id_sud ) ) ;
		  break ;
	     }
	case OUEST :
	     {
		  coord_t criteres_ouest ;
		  case_t case_ouest ;
		  int id_ouest ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ),
			      &l, &c, &p );
		  i=0 ;
		  while( ((*deplacement)) && (i<BATEAU_TAILLE) )
		  {
		       coord_set( &criteres_ouest , l+i , c-1 , -1 );
		       if( ( id_ouest = coords_coord_seek( liste_voisins, criteres_ouest , coord_xy_comparer ) ) == -1 )
		       {
			    (*deplacement) = FAUX ;
		       }
		       else
		       {
			    mer_case_lire( fd, 
					   coords_coord_get( liste_voisins , id_ouest ) , 
					   &case_ouest);
			    if( case_ouest != MER_CASE_LIBRE )
				 (*deplacement) = FAUX ;
			    else
				 i++;
		       }

		  }

		  if( !(*deplacement) )
		       break ;
				 
		  /* Deplacement */

		  for( i=0 ; i<BATEAU_TAILLE ; i++ )
		  {
		    coord_get( coords_coord_get( bateau_corps_get(bateau) , i ),
				&l, &c, &p );
		       coord_set( &criteres_ouest , l , c-1 , -1 );
		       id_ouest = coords_coord_seek( liste_voisins , criteres_ouest , coord_xy_comparer ) ;

		       /* Ecriture deplacement dans le fichier mer */
		       mer_case_ecrire( fd ,
					coords_coord_get( liste_voisins , id_ouest ) ,
					bateau_marque_get(bateau) );

		       mer_case_ecrire( fd ,
					coords_coord_get( bateau_corps_get(bateau) , i ),
					MER_CASE_LIBRE );

		       /* Mise a jour deplacement dans le bateau */
		       coords_coord_set( bateau_corps_get(bateau) , 
					 i ,
					 coords_coord_get( liste_voisins , id_ouest ) ) ;
		  }

		  break;
	     }
	default : 
	     {
		  fprintf(stderr , "mer_bateau_vertical_deplacer: mauvaise direction bateau : %s <%d>\n",
			  coord_dir2string(direction) , direction );
		  return(ERREUR);
	     }
     }
	       
     return(CORRECT);
}
		

/*
 * Deplacement d'un bateau horizontal dans une direction donnee
 * le booleen <deplacement> est positionne a FAUX si le deplacement n'est pas possible
 */

static
int
mer_bateau_horizontal_deplacer( const int fd,			/* Fichier mer */ 
				bateau_t * bateau,		/* Bateau qui va se deplacer */
				const direction_t direction,	/* Direction du deplacement */
				coords_t * const liste_voisins,	/* Liste des cases voisines */
				booleen_t * deplacement )	/* Indique si le deplacement s'est realise */
{
     (*deplacement) = VRAI ;
    
     switch( direction )
     {
	case NORD :
	     {
		  coord_t criteres_nord ;
		  case_t case_nord ;
		  int id_nord ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ),
			      &l, &c, &p );
		  i=0 ;
		  while( ((*deplacement)) && (i<BATEAU_TAILLE) )
		  {
		       coord_set( &criteres_nord , l-1 , c+i , -1 );
		       if( ( id_nord = coords_coord_seek( liste_voisins, criteres_nord , coord_xy_comparer ) ) == -1 )
		       {
			    (*deplacement) = FAUX ;
		       }
		       else
		       {
			    mer_case_lire( fd, 
					   coords_coord_get( liste_voisins , id_nord ) , 
					   &case_nord);
			    if( case_nord != MER_CASE_LIBRE )
				 (*deplacement) = FAUX ;
			    else
				 i++;
		       }
		  }

		  if( !(*deplacement) )
		       break ;
				 
		  /* Deplacement */

		  for( i=0 ; i<BATEAU_TAILLE ; i++ )
		  {
		    coord_get( coords_coord_get( bateau_corps_get(bateau) , i ) ,
				&l, &c, &p );
		       coord_set( &criteres_nord , l-1 , c , -1 );
		       id_nord = coords_coord_seek( liste_voisins , criteres_nord , coord_xy_comparer ) ;

		       /* Ecriture deplacement dans le fichier mer */
		       mer_case_ecrire( fd , 
					coords_coord_get( liste_voisins , id_nord ) ,
					bateau_marque_get(bateau) );

		       mer_case_ecrire( fd , 
					coords_coord_get( bateau_corps_get(bateau) , i ) ,
					MER_CASE_LIBRE );

		       /* Mise a jour deplacement dans le bateau */
		       coords_coord_set( bateau_corps_get(bateau) , 
					 i ,
					 coords_coord_get( liste_voisins , id_nord ) ) ;
		  }
		  break;
	     }
	case EST :
	     {
		  coord_t criteres_est ;
		  case_t case_est ;
		  int id_est ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ,
			      &l, &c, &p );
		  coord_set( &criteres_est , l , c+1 , -1 );
		  if( ( id_est = coords_coord_seek( liste_voisins, criteres_est , coord_xy_comparer ) ) == -1 )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  mer_case_lire( fd, 
				 coords_coord_get( liste_voisins , id_est ) , 
				 &case_est);
		  if( case_est != MER_CASE_LIBRE )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  /* Ecriture deplacement dans le fichier mer */
				 
		  mer_case_ecrire( fd, 
				   coords_coord_get( liste_voisins , id_est ) , 
				   bateau_marque_get(bateau) ) ;

		  mer_case_ecrire( fd, 
				   coords_coord_get( bateau_corps_get(bateau) , 0 ),
				   MER_CASE_LIBRE );

		  /* Mise a jour deplacement dans le bateau */

		  for( i=0; i<BATEAU_TAILLE-1 ; i++ )
		  {
		    coords_coord_set( bateau_corps_get(bateau) , 
				      i ,
				      coords_coord_get( bateau_corps_get(bateau) , i+1 ) ) ;
		  }
		  coords_coord_set( bateau_corps_get(bateau) , 
				      BATEAU_TAILLE-1 ,
				    coords_coord_get( liste_voisins , id_est ) ) ;
		  break ;
	     }
	
	case SUD :
	     {
		  coord_t criteres_sud ;
		  case_t case_sud ;
		  int id_sud ;
		  int l , c , i;
		  off_t p ;

		  /*--------------------*/

		  /* Verification des positions */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ),
			      &l, &c, &p );
		  i=0 ;
		  while( ((*deplacement)) && (i<BATEAU_TAILLE) )
		    {
		       coord_set( &criteres_sud , l+1 , c+i , -1 );
		       if( ( id_sud = coords_coord_seek( liste_voisins, criteres_sud , coord_xy_comparer ) ) == -1 )
		       {
			    (*deplacement) = FAUX ;
		       }
		       else
		       {
			    mer_case_lire( fd, 
					   coords_coord_get( liste_voisins , id_sud ), 
					   &case_sud);
			    if( case_sud != MER_CASE_LIBRE )
				 (*deplacement) = FAUX ;
			    else
				 i++;
		       }
		  }

		  if( !(*deplacement) )
		       break ;
				 
		  /* Deplacement */

		  for( i=0 ; i<BATEAU_TAILLE ; i++ )
		  {
		    coord_get( coords_coord_get( bateau_corps_get(bateau) , i ) ,
				&l, &c, &p );
		       coord_set( &criteres_sud , l+1 , c , -1 );
		       id_sud = coords_coord_seek( liste_voisins, criteres_sud , coord_xy_comparer ) ;

		       /* Ecriture deplacement dans le fichier mer */
		       mer_case_ecrire( fd , 
					coords_coord_get( liste_voisins , id_sud ) ,
					bateau_marque_get(bateau) );

		       mer_case_ecrire( fd , 
					coords_coord_get( bateau_corps_get(bateau) , i ), 
					MER_CASE_LIBRE );

		       /* Mise a jour deplacement dans le bateau */
		       coords_coord_set( bateau_corps_get(bateau) , 
					 i ,
					 coords_coord_get( liste_voisins , id_sud ) ) ;
		  }

		  break;
	     }

	case OUEST :
	     {
		  coord_t critere_ouest ;
		  case_t case_ouest ;
		  int id_ouest ;
		  int l , c , i ;
		  off_t p ;

		  /*--------------------*/

		  /* Verification de la position ouest */

		  coord_get( coords_coord_get( bateau_corps_get(bateau) , 0 ),
			      &l, &c, &p );
		  coord_set( &critere_ouest , l , c-1 , -1 );
		  if( ( id_ouest = coords_coord_seek( liste_voisins, critere_ouest , coord_xy_comparer ) ) == -1 )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  mer_case_lire( fd, 
				 coords_coord_get( liste_voisins , id_ouest ), 
				 &case_ouest);
		  if( case_ouest != MER_CASE_LIBRE )
		  {
		       (*deplacement) = FAUX ;
		       break ;
		  }

		  /* Ecriture deplacement dans le fichier mer */
				 
		  mer_case_ecrire( fd, 
				   coords_coord_get( liste_voisins , id_ouest ) ,
				   bateau_marque_get(bateau) );

		  mer_case_ecrire( fd, 
				   coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ,
				   MER_CASE_LIBRE );

		  /* Mise a jour deplacement dans le bateau */

		  for( i=BATEAU_TAILLE-1 ; i>0 ; i-- )
		  {
		    coords_coord_set( bateau_corps_get(bateau) , 
				      i ,
				      coords_coord_get( bateau_corps_get(bateau) , i-1 ) ) ;
		  }
		  coords_coord_set( bateau_corps_get(bateau) , 
				    0 ,
				    coords_coord_get( liste_voisins , id_ouest ) ) ;
		  break ;
	     }

	default : 
	     {
		  fprintf(stderr , "mer_bateau_horizontal_deplacer: mauvaise direction bateau : %s <%d>\n",
			  coord_dir2string(direction) , direction );
		  return(ERREUR);
	     }
     }
	       
     return(CORRECT);
}
				    
/* 
 * Deplacement d'un bateau sur la mer :
 * - choix aleatoire d'une direction de deplacement dans les cases voisines
 * - ecriture dans les cases des nouvelles positions 
 * - effacement du contenu des cases des anciennes positions
 */

extern 
int
mer_bateau_deplacer( const int fd ,			/* Fichier mer */
		     bateau_t * bateau,			/* Bateau a deplacer */
		     coords_t * const liste_voisins ,	/* Liste des cases voisines du bateau */
		     booleen_t * deplacement )		/* Indique si le deplacement s'est effectue */
{
     direction_t direction_initiale = NORD ;
     direction_t direction = NORD ;
     int noerr = CORRECT ;
     orientation_t orientation = coord_orientation_donner( coords_coord_get( bateau_corps_get(bateau) , 0 ),
							   coords_coord_get( bateau_corps_get(bateau) , BATEAU_TAILLE-1 ) ); 
     static booleen_t first = VRAI ; 
     booleen_t cycle = FAUX ;
     const int nb_voisins = coords_nb_get(liste_voisins) ; 

     /*----------*/
    
     /* 
      * Test liste vide 
      */

     if( nb_voisins == 0 )
     {
	  (*deplacement) = FAUX ;
	  return(CORRECT) ;
     }

     /* 
      * Traitement liste au moins un voisin 
      */


     /* Initialisation de la fonction random */  
     if( first )
     {
	  srandom((unsigned int)time((time_t *)NULL)) ;
	  first = FAUX ;
     }

     /* Choix aleatoire de la direction de depart */
     direction_initiale = (int)(random() % 4 ) ;

     /* Parcours cyclique des 4 points cardinaux */
	  
     direction = direction_initiale ;
     (*deplacement) = FAUX ;
     cycle = FAUX ;
     while( (!cycle) && (! (*deplacement) ) )
     {
	
	  switch( orientation )
	  {
	     case VERTICAL :
		  {
		       if( (noerr = mer_bateau_vertical_deplacer(fd,
								 bateau,
								 direction,
								 liste_voisins,
								 deplacement)) )
			    return(noerr) ;

		       break ;
		  }
	     case HORIZONTAL :
		  {
		       if( (noerr = mer_bateau_horizontal_deplacer(fd,
								   bateau,
								   direction,
								   liste_voisins,
								   deplacement)) )
			    return(noerr) ;

		       break ;
		  }
	     default :
		  {
		       fprintf( stderr ,"mer_bateau_deplacer: mauvaise orientation du bateau : %s (%d)\n",
				coord_ori2string(orientation) , orientation );
		       return(ERREUR);
		  }

	  }

#ifdef _DEBUG_
	  printf( "navire_deplacer : essai deplacement direction %s --> " ,
		  coord_dir2string(direction)  );
	  if( (*deplacement) )
	       printf( "OK\n");
	  else
	       printf( "KO\n");
#endif

	  if( !(*deplacement) )
	  {
	       /* Essai avec une autre direction */
	       direction = (direction+1) % 4 ;
	  }
	  if( direction == direction_initiale )
	       cycle = VRAI ;
     }

     return(CORRECT);
}

/* 
 * Lecture des dimensions de la mer
 */

extern 
int
mer_dim_lire( const int fd,	/* descripteur fichier mer */
	      int * nb_lig,	/* nombre de lignes */
	      int * nb_col)	/* nombre de colonnes */
{

     char mess[MESS_LONGUEUR] ;

     /*----------*/

     /* 
      * Initialisation des resultats 
      */
     (*nb_lig) = 0 ; 
     (*nb_col) = 0 ; 

     /* 
      * Mise de la position courante au debut du fichier
      */

     if( lseek(fd, (off_t)0, SEEK_SET) == -1 )
     {
	  sprintf( mess , "mer_afficher : Pb lseek debut fichier fd=%d\n",
		   fd );
	  perror(mess);
	  return(ERREUR) ;
     }

     /* 
      * Lecture des dimensions du mer 
      */
     
     if( read( fd , nb_lig , sizeof(int)) == -1 )
     {
	  perror("mer_afficher : Pb read sur lecture nb lignes");
	  return(ERREUR) ;
     }

     if( read( fd , nb_col , sizeof(int)) == -1 )
     {
	  perror( "mer_afficher : Pb read sur lecture nb colonnes");
	  return(ERREUR) ;
     }

     return(CORRECT);
}


/*
 * Conversion de coordonnees [x,y] en position dans le fichier
 */

extern
int
mer_lc2pos( const int fd, /* descripteur fichier mer */
	    const int l,  /* ligne   dans le tableau mer */  
	    const int c,  /* colonne dans le tableau mer */
	    off_t * pos ) /* position dans le fichier mer */
{

     int nb_lig ;
     int nb_col ; 

     /*--------------------*/

     /* 
      * Lecture des dimensions de la mer 
      */
     
     mer_dim_lire( fd , &nb_lig , &nb_col );

     /* 
      * Calcul position fichier
      */

     (*pos) = MER_TAILLE_ENTETE + ( l*MER_TAILLE_CASE*nb_col ) + (c*MER_TAILLE_CASE) ;

     return(CORRECT);
}

/*
 * Conversion d'une position dans le fichier en coordonnees [x,y]
 */

extern
int
mer_pos2lc( const int fd,	/* Descripteur fichier mer */
	    const off_t pos,	/* Position dans le fichier mer */
	    int * l,		/* Ligne   dans le tableau mer */  
	    int * c)		/* Colonne dans le tableau mer */

{
     int taille_lig = 0 ;
     int nb_lig = 0 ;
     int nb_col = 0 ;     
     int pos_w = pos - MER_TAILLE_ENTETE ;

     /*--------------------*/

     /*
      * Initialisation des resultats 
      */

     (*l) = -1 ;
     (*c) = -1 ;

     /* 
      * Lecture des dimensions de la mer 
      */
     
     mer_dim_lire( fd , &nb_lig , &nb_col );

     taille_lig = nb_col * MER_TAILLE_CASE ;

     (*l) = (int)(pos_w / taille_lig) ;
     (*c) = (int)(pos_w - ((*l) * taille_lig) ) ;

     return(CORRECT) ;
}


/*
 * Lecture d'une case de la mer
 */ 

extern 
int 
mer_case_lire( const int fd,		/* descripteur du fichier mer */
	       const coord_t coord,	/* coordonnees de la case a lire */
	       case_t * contenu )	/* contenu de la case a lire */
{

     /*--------------------*/

     if( lseek( fd, coord.pos , SEEK_SET) == -1 )
     {
	  fprintf(stderr , "mer_case_lire : Pb lseek (dans fichier fd=%d) sur case " ,
		  fd );
	  coord_fprintf( stderr , coord );
	  fprintf(stderr, "\n");
	  perror("Pb lseek") ;
	  return(ERREUR) ;
     }
     
     if( read( fd , contenu , MER_TAILLE_CASE ) == -1 )
     {
	  fprintf( stderr , "mer_case_lire : Pb read sur lecture de la case " );
	  coord_fprintf( stderr , coord );
	  perror("Pb read");
	  return(ERREUR) ;
     }

     return(CORRECT);
}


/* 
 * Ecriture d'une case de la mer
 */

extern
int 
mer_case_ecrire( const int fd,
		 const coord_t coord,
		 const case_t contenu )
{
     case_t m = contenu ;
     char mess[MESS_LONGUEUR] ;

     /*----------*/

/* #ifdef _DEBUG_  */
/*      printf( "mer_case_ecrire --> ecriture " ); */
/*      mer_case_printf( contenu ); */
/*      printf( " a la case "); */
/*      coord_printf( coord ); */
/*      printf( "\n"); */
/* #endif */

     if( lseek( fd, coord.pos, SEEK_SET ) == -1 )
     {
	  sprintf( mess , "mer_case_ecrire : erreur dans deplacement a la position %lld dans le fichier mer (fd=%d)\n",
		   coord.pos , fd );
	  perror(mess);
	  return(ERREUR) ;
     }

     write(fd, &m, MER_TAILLE_CASE) ;

     return(CORRECT) ;
}
		   
/* 
 * Acquisition d'une cible par bateau sur la mer 
 * Choix aleatoire d'une case de la mer 
 * - sur laquelle il y a un bateau 
 * - qui ne soit pas celui d'ou vient le coup
 * Si la recherche se passe bien 
 * - retour --> CORRECT 
 * - si une cible est trouvee :
 *   - affectation des coordonnees de la cible (une case de la mer) dans le parametre <cible>
 *   - <acquisition> est a VRAI
 * - si on ne peux acquerir aucune cible 
 *   - <cible> est a NULL
 *   - <acquisition> est a FAUX
 */

extern
int
mer_bateau_cible_acquerir( const int fd,		/* Mer */
			   const bateau_t * const bateau,	/* Bateau */
			   booleen_t * acquisition,     /* Cible trouvee ? */
			   coord_t * cible )		/* Coordonnees de la case choisie */
{
     int nb_lig   , nb_col   ;	/* dimensions de la mer */
     int init_lig , init_col ;	/* Ligne et Colonne de depart parcours mer */
     int lig      , col      ;	/* Ligne et colonne courantes parcours mer */
     off_t   pos ;		/* Position dans la mer */
     coord_t coord_mer ;	/* Coordonnees case */
     case_t  case_mer ;		/* Contenu d'une case */
     int id ;			/* Indice dans liste */
     booleen_t trouve = FAUX ;	/* Indicateur d'arret du parcours */

     static booleen_t first = VRAI ; 

     char mess[MESS_LONGUEUR] ;

     /*--------------------*/
     
     /* 
      * Lecture des dimensions de la mer 
      */
     
     mer_dim_lire( fd , &nb_lig , &nb_col );
     
     /* 
      * Positionnement au bord de la mer 
      */

     if( lseek(fd, MER_TAILLE_ENTETE , SEEK_SET) == -1 )
     {
	  sprintf( mess , "mer_afficher : Pb lseek saut <nombre de bateaux> dans fichier mer (fd=%d)\n",
		   fd );
	  perror(mess);
	  return(ERREUR) ;
     }

     /* 
      * Choix aleatoire d'une case de depart 
      */

     /* Initialisation de la fonction random */  
     if( first )
     {
	  srandom((unsigned int)time((time_t *)NULL)) ;
	  first = FAUX ;
     }

     /* Choix aleatoire des coordonnees de la case de depart */
     init_lig = (int)(random() %  nb_lig ) ;
     init_col = (int)(random() %  nb_col ) ;
     mer_lc2pos( fd ,  init_lig , init_col , &pos ) ;


     /* Parcours cyclique des cases du fichier mer*/
     trouve = FAUX ;
     lig = (init_lig+1) % nb_lig ;
     while( (lig != init_lig) && (!trouve) )
     {
	  col = (init_col+1) % nb_col ;
	  while( (col != init_col) && (!trouve) )
	  {
	       mer_lc2pos( fd , lig , col , &pos ) ;
	       coord_set( &coord_mer , lig , col , pos );
	       if( ( id = coords_coord_seek( bateau_corps_get(bateau) , 
					     coord_mer , 
					     coord_xy_comparer ) ) == -1 )
		 {
		    /* Le bateau ne se tire pas dessus */
		    mer_case_lire( fd , coord_mer , &case_mer );
		    if( case_mer != MER_CASE_LIBRE )
		    {
			 /* La case n'est pas dans l'eau */
			 trouve = VRAI ;
		    }
	       }
	       col = (col+1) % nb_col ;
	  }
	  lig = (lig+1) % nb_lig ;
     }

     if( trouve )
     {
	  coord_copier( cible , coord_mer );
     }
     (*acquisition) = trouve ;
     
     return(CORRECT);
}
			   
/* 
 * Envoie du boulet dans une case
 */

extern
int 
mer_bateau_cible_tirer( const int fd,
			const coord_t coord )
{
     case_t m = MER_CASE_BOULET ;
     char mess[MESS_LONGUEUR] ;

     /*----------*/

#ifdef _DEBUG_ 
     printf( "mer_bateau_cible_tirer --> ecriture " );
     mer_case_printf( MER_CASE_BOULET );
     printf( " a la case ");
     coord_printf( coord );
     printf( "\n");
#endif

     if( lseek( fd, coord.pos, SEEK_SET ) == -1 )
     {
	  sprintf( mess , "mer_case_ecrire : erreur dans deplacement a la position %lld dans le fichier mer (fd=%d)\n",
		   coord.pos , fd );
	  perror(mess);
	  return(ERREUR) ;
     }

     write(fd, &m, MER_TAILLE_CASE) ;

     return(CORRECT) ;
}


/*
 * Verifie si un bateau a ete touche
 */

extern
int 
mer_bateau_est_touche( const int fd,
		       const bateau_t * const bateau ,
		       booleen_t * touche )
{
     case_t case_bateau ;
     int i = 0 ;
     int no_err = CORRECT ;

     /*----------*/

     (*touche) = FAUX ;
     while( (i<BATEAU_TAILLE) && (!(*touche)) )
     {
	  if( (no_err = mer_case_lire( fd,
				       coords_coord_get( bateau_corps_get(bateau) , i ) ,
				       &case_bateau ) ) )
	       return(no_err);

	  if( case_bateau == MER_CASE_BOULET )
	       (*touche) = VRAI ;
	  else
	       i++ ;
     }

     return(CORRECT);
}


/* 
 * Coule/efface un bateau de la mer
 */

extern
int 
mer_bateau_couler( const int fd,
		   const bateau_t * const bateau )
{
     int i = 0 ;
     int no_err = CORRECT ;

     /*----------*/

     for( i=0 ; i<BATEAU_TAILLE ; i++ )
     {
	  if( (no_err = mer_case_ecrire( fd, 
					 coords_coord_get( bateau_corps_get(bateau) , i ),
					 MER_CASE_LIBRE ) ) )
	       return(no_err);

     }
     return(CORRECT);
}



