#include <commun.h>

/*
 * Affichage des messages d'erreurs sur la sortie erreur standard
 */

extern
void err_print( err_t code )
{
  switch(code)
    {
    case CORRECT    : fprintf( stderr , "Terminaison correcte, pas d'erreur \n") ; break ; 
    case ERREUR     : fprintf( stderr , "Erreur générique \n") ; break ; 
    case PAS_TROUVE : fprintf( stderr , "Recherche négative d'un élément, élément inconnu \n") ; break ; 
    case ERR_NULL   : fprintf( stderr , "Reference inexistante \n") ; break ; 
    case ERR_FILE   : fprintf( stderr , "Erreur relative à un fichier (inexistant, lecture/écritrure impossible...) \n") ; break ; 
    case ERR_DIM    : fprintf( stderr , "Erreur dans une dimension donnée: indice de ligne et/ou de colonne incorrect \n") ; break ;  
    case ERR_MEM    : fprintf( stderr , "Fuire mémoire \n") ; break ; 
    case ERR_SCAN   : fprintf( stderr , "Erreur lors de la capture d'un élement par un scanf, read ... \n") ; break ; 
    default         : fprintf( stderr , "Code erreur inconnu %d\n" , code ) ; break ; 
    }
}

void Pause( char * mess )
{
  printf("%s" ,mess ) ; fflush(stdout);
  getchar() ;
}
