#include <string.h>
#include <getopt.h>
#include <pthread.h>

#include <automate_stdio.h>
#include <coords_stdio.h>

/*
 * \file automate_asynchrone_memoire_stdio.c
 * \brief Exécution d'un Automate Asynchrone avec Mémoire sur sortie standard.
 * Les cellules sont gérées indépendamment par des threads
 */

/*
 * Verifie si toutes les coordonnées d'une liste appartiennent à un automate
 */
static
int verifier_cellules( const int hauteur , const int largeur , const coords_t * const liste_coords )
{
  coord_t coord ;
  int i , l , c ;
  int nb = 0 ;

  if( liste_coords == NULL )
    return(CORRECT) ;

  nb = coords_nb_get(liste_coords) ;
  
  for(i=0;i<nb;i++)
    {
      coord = coords_get( liste_coords , i ) ;
      l = coord_lig_get(&coord) ;
      c = coord_col_get(&coord) ;
      if( (l<0) || (l>= hauteur) || (c<0) || (c>=largeur) )
	{
	  fprintf( stderr ,"verifier_cellules : la coordonnées [%d,%d] n'appartient pas à l'automate de dim %dX%d\n" , l, c , hauteur , largeur ) ;
	  return(ERR_DIM) ;
	}
    }
  
  return(CORRECT) ; 
}

/*
 * Programme Principal 
 */

//Parametres pour les threads cellules
typedef struct params_cellules_s {
  int i;
  int j;
  booleen_t verbose;
  automate_t* automate;
  cellule_regles_t * regles;
  pthread_mutex_t * mutex;
  int * gen;
  int nb_gen;
  pthread_barrier_t * barriere;
  int nb_cellules;
  int * cellules_evolue;
} params_cellules_t;

//Parametres pour le thread de gestion des generations
typedef struct params_gestion_gen_s {
  pthread_mutex_t * mutex;
  int * gen;
  int nb_gen;
  pthread_barrier_t * barriere;
  int * cellules_evolue;
} params_gestion_gen_t;

//Fonction pour les threads cellules
void generation(void * args){

  params_cellules_t * params = (params_cellules_t *)args; 
  if( params->verbose) printf(" Evolution de la cellule [%d,%d]\n" , params->i, params->j ) ;

  booleen_t fini = FAUX;

  while(fini == FAUX){

    usleep(random()%10000);
    
    pthread_mutex_lock(params->mutex);

    if (*(params->gen) <= params->nb_gen)
    {
      automate_cellule_evoluer(params->automate, automate_get(params->automate, params->i, params->j), params->regles);
      *(params->cellules_evolue) += 1;

      system("clear") ;
	      printf("ASYNCHRONE AVEC MEMOIRE : Generation %d (%d/%d)\n" , *(params->gen) , *(params->cellules_evolue) , params->nb_cellules ) ; 
      automate_print(stdout, params->automate);
      usleep(10000);

      automate_generer(params->automate);
    }
    else{
      fini = VRAI;
    }
      
    pthread_mutex_unlock(params->mutex);

    //On se bloque sur la barriere pour signaler qu'on a fait notre generation
    pthread_barrier_wait(params->barriere);
  }

  pthread_exit(NULL);
}

//fonction pour le thread de generation des cellules
void gestion_gen(void * args){
  params_gestion_gen_t * params = (params_gestion_gen_t *)args;

  while (*(params->gen) <= params->nb_gen)
  {
    
    //Attente que toutes les cellules aient passee leur tour
    pthread_barrier_wait(params->barriere);

    pthread_mutex_lock(params->mutex);

    *(params->gen) += 1;
    *(params->cellules_evolue) = 0;

    pthread_mutex_unlock(params->mutex);
  }

  pthread_barrier_wait(params->barriere);
  
  pthread_exit(NULL);
}

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <hauteur> <largeur> <nb generations>\n" , nomprog ) ; 
  printf( "options:\n" ) ; 
  printf( "\t--verbose : trace des principales actions (defaut = desactive)\n" ) ; 
  printf( "\t--help    : affiche cette aide\n" ) ; 
  printf( "\t--fichier <fichier initialisation> : initialisation de l'automate avec un fichier\n") ;
  printf( "\t--case <l,c> : initialisation de la case [l,c] de l'automate avec une cellule vivante\n" ) ;
  printf( "\t--naissance <nb> : nombre de voisins pour la naissance d'une cellule (defaut %d)\n" , NAISSANCE ) ;
  printf( "\t--isolement <nb> : nombre de voisins minimum en dessous duquel la cellule meurt isolee (defaut %d)\n" , ISOLEMENT ) ;
  printf( "\t--etouffement <nb> : nombre de voisins maximum au dessus duquel la cellule meurt etouffee (defaut %d)\n" , ETOUFFEMENT ) ; 
}

static struct option longopts[] =
  {
    {"verbose", no_argument, NULL, (int)'v'},
    {"help", no_argument, NULL, (int)'h'},
    {"fichier", required_argument, NULL, (int)'f'},
    {"case", required_argument, NULL, (int)'c'},
    {"naissance", required_argument, NULL, (int)'n'},
    {"isolement", required_argument, NULL, (int)'i'},
    {"etouffement", required_argument, NULL, (int)'e'},
    {0, 0, 0, 0}
  };


int
main( int argc , char * argv[] )
{
  err_t noerr = CORRECT ;
  
  /* --- Gestion des options --- */
  int opt ; 
  char nomprog[STRING_LG_MAX] ;
  booleen_t  verbose = FAUX ;

  /* --- Options --- */
  char * fichier_init = NULL ;  
  coords_t * coords_init = coords_new() ;

   /* --- Automate --- */
  automate_t * automate = NULL ; 
  cellule_regles_t regles = cellule_regles_default() ;
  
  /*----------*/
  

  /*  Captures des options et des paramètres */
  
  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vhf:c:n:i:e:", longopts, NULL)) != -1 )
    {
      switch(opt)
	{
	case 'c' : /* --case d'initialisation */
	  {
	    int l , c ;
	    coord_t coord ;
	    sscanf( optarg , "%d,%d" , &l , &c ) ;
	    coord_set( &coord , l , c ) ; 
	    
	    if( (noerr = coords_add( coords_init , coord ) ) )
	      {
		fprintf( stderr , "%s: pb ajout case %d,%d dans liste des coordonnées d'initialisation, sortie erreur %d\n" , nomprog , l , c , noerr ) ;
		err_print(noerr) ; exit(0) ; 
	      }
	    break ;
	  }
	  
	case 'f':  /* --fichier d'initialisation */
	  fichier_init = malloc( strlen(optarg)+1 ) ; 
	  strcpy(fichier_init,optarg) ;
	  break;
	  
	case 'n':  /* --naissance */
	  cellule_regles_naissance_set(&regles, atoi(optarg) ) ; 
	  break;

	case 'i':  /* --isolement */
	  cellule_regles_isolement_set(&regles, atoi(optarg) ) ; 
	  break;

	case 'e':  /* --etouffement */
	  cellule_regles_etouffement_set(&regles, atoi(optarg) ) ; 
	  break;
	  
	case 'v' :  /* --verbose */
	  verbose = VRAI ;
	  break ; 

	case 'h': /* --help */
	  usage(nomprog) ;
	  exit(0);
	  break;

	case '?':
	  usage(nomprog) ;
	  exit(0);
	  break;

	default:
	  usage(nomprog) ;
	  exit(0);
	  break;
	}
    }
  argc -= optind ;
  argv += optind ;

  /* --- Parametres ---*/
  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */
  
  if( argc != 3 )
    {
      printf("%s : Nombre de parametres incorrect : %d (3 attendus)\n\n" , nomprog , argc ) ; 
      usage(nomprog) ; 
      exit(-1) ;
    }

  int hauteur = atoi(argv[0]) ;
  int largeur = atoi(argv[1]) ;
  int nb_generations = atoi(argv[2]) ; 

  /* ---------- */
  
  srandom( (unsigned int)getpid() );

  if( verbose ) printf("\n----- Debut %s  Automate %dX%d %d generations -----\n" ,
		       nomprog , hauteur , largeur , nb_generations  );
  
  /*  Création de l'automate avec les coordonnées des cellules vivantes entrées dans les options -c et -f */

  if( verbose ) printf("Lecture des coordonnees initiales\n");
  if( (noerr = coords_scan( fichier_init , coords_init ) ) )
    {
      fprintf( stderr ,"%s : Pb chargement liste des coords initiales a partir de %s\n" , nomprog , fichier_init ) ;
      err_print(noerr) ; exit(0) ; 
    }
  if( verbose ) coords_print( stdout , coords_init ) ; 

  if( verbose ) printf("Vérification des coordonnées des cellules intiales\n") ;
  if( (noerr = verifier_cellules( hauteur , largeur , coords_init ) ) )
    {
      fprintf( stderr ,"%s : Coordonnées initiales incorrectes, sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ; 
    }
  
  if( verbose ) printf("Creation automate\n") ; 
  if( (automate = automate_new( hauteur , largeur , coords_init ) ) == NULL )
    {
      fprintf( stderr , "%s : erreur\n" , nomprog ) ;
      exit(1) ; 
    }
  automate_print( stdout , automate ) ;

  /* ----- */

  /********************************/
  /* Gestion des cellules A FAIRE */
  /********************************/

  //Variables generales pour la gestion par threads
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_t thread_id[hauteur][largeur];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  int gen_act = 1;
  int n_cellules = hauteur * largeur;
  int cellules_evolue = 0;


  //Parametres des threads cellules
  pthread_barrier_t barriere;
  //+1 important pour compter aussi le thread de gestion
  pthread_barrier_init(&barriere, NULL, hauteur * largeur + 1);

  params_cellules_t params_tab[hauteur][largeur];
  params_cellules_t params;

  params.verbose = verbose;
  params.automate = automate;
  params.regles = &regles;
  params.mutex = &mutex;
  params.gen = &gen_act;
  params.nb_gen = nb_generations;
  params.barriere = &barriere;
  params.nb_cellules = n_cellules;
  params.cellules_evolue = &cellules_evolue;



  //Lancement threads cellules
  for (int i = 0; i < hauteur; i++)
  {
    for (int j = 0; j < largeur; j++)
    {
      params.i = i;
      params.j = j;
      params_tab[i][j] = params;

      pthread_create(&thread_id[i][j], &attr, (void *)generation, &params_tab[i][j]);
    }
  }

  //Parametres pour le thread de gestion
  pthread_t thread_id_gestion_gen;
  params_gestion_gen_t params_gestion_gen;
  params_gestion_gen.barriere = &barriere;
  params_gestion_gen.gen = &gen_act;
  params_gestion_gen.mutex = &mutex;
  params_gestion_gen.nb_gen = nb_generations;
  params_gestion_gen.cellules_evolue = &cellules_evolue;

  //Lancement gestion des generations
  pthread_create(&thread_id_gestion_gen, &attr, (void *)gestion_gen, &params_gestion_gen);


  //Attente des threads
  for(int i = 0; i < hauteur; i++){
    for(int j = 0; j < largeur; j++){

      pthread_join(thread_id[i][j], NULL);

    }
  }

  //Attente thread gestion des generations
  pthread_join(thread_id_gestion_gen, NULL);

  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&mutex);
  
  /* ----- */

  /*  Destruction des variables: liste des coordonnées initiales, des cellules et de l'automate */
  
  if( verbose ) printf("Destruction liste de coordonnées d'initialisation\n") ;
  if( ( noerr = coords_destroy( &coords_init ) ) )
    {
      fprintf( stderr ,"%s : Pb destruction des coords d'initialisation, sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ; 
    }
  
  if( verbose ) printf("Destruction automate\n") ; 
  if( (noerr = automate_destroy( &automate ) ) )
    {
      fprintf( stderr , "%s : sortie erreur %d\n" , nomprog , noerr ) ;
      err_print(noerr) ; exit(0) ;  
    }

  exit(0); 
}
