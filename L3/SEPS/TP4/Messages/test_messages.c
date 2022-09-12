#include <messages.h>
#include <unistd.h>

int
main( int nb_arg , char * tab_arg[] ) 
{
  requete_t requete ;
  reponse_t reponse ;

  printf("\n------ Debut %s -----\n\n" , tab_arg[0] );
  
  requete.type = PC_COURSE ; 
  requete.corps.dossard = getpid() ;
  requete.corps.etat = EN_COURSE ;
  requete.corps.num_message = 10 ;

  messages_afficher_requete( &requete ) ;

  reponse.type = getpid() ;
  reponse.corps.compte_rendu = OK ;
  reponse.corps.etat         = EN_COURSE ;
  reponse.corps.nb_coureurs  = 6 ;
  int i ; 
  for(i=0 ; i<5 ; i++ )
    {
      reponse.corps.tab_coureurs[i].dossard = 1234+i ;
      reponse.corps.tab_coureurs[i].distance = 10+i ;
    }  
  reponse.corps.tab_coureurs[5].dossard = getpid() ;
  reponse.corps.tab_coureurs[5].distance = 99 ;
      
  messages_afficher_reponse( &reponse ) ;

  printf("\n------ Fin %s -----\n\n" , tab_arg[0] );

  return(0) ; 
}
