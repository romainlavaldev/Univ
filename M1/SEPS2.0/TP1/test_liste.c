#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <commun.h>
#include <liste.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
  liste_t liste ;

  elem_id_t nb ;
  cell_t c ;
  elem_t e ;
  elem_id_t ind_del , ind_rech ;

  int i ;
  
  /*-----*/

  /* Initialisation de la liste (effacement de tous les chevaux) */
  printf("Creation de la liste:\n");
  liste_initialiser(&liste);
  liste_afficher( &liste );


  printf("Affection par champs de 10 elements \n");
  for( i=0 ; i <10 ; i++ )
    {
      cell_pid_affecter( &c , getpid()+i ) ;
      cell_marque_affecter( &c , 'A'+i ) ;
      elem_cell_affecter( &e , c ) ;
      elem_etat_affecter( &e , EN_COURSE ) ;
      
      liste_elem_affecter( &liste , i , e );
    }
  liste_nb_affecter( &liste , 10 );

  printf("Affichage par champs des elements affectes\n");
  nb = liste_nb_lire( &liste ) ;
  printf("Nombre d'elements dans la liste = %d\n" ,  nb ) ;
  for(i=0; i<nb ; i++ ) 
    {
      printf("Valeur de l'element: ") ;
      elem_afficher( liste_elem_lire(&liste , i ) ) ;
      printf("\n") ;
    }

  printf("Ajout de 10 elements dans la liste\n");
  for( i=0 ; i <10 ; i++ )
    {
      cell_pid_affecter( &c , getpid()+10+i ) ;
      cell_marque_affecter( &c , 'K'+i ) ;
      elem_cell_affecter( &e , c ) ;
      elem_etat_affecter( &e , EN_COURSE ) ;

      liste_elem_ajouter( &liste, e );
    }
  liste_afficher( &liste );

    printf("Suppression de 5 elements dans la liste\n");
    for( i=0 ; i <5 ; i++ )
      {
	nb = liste_nb_lire(&liste) ;
	ind_del = random()%nb ; 
	printf("\tEffacement de la positon %d\n" , ind_del ) ;
	liste_elem_supprimer( &liste , ind_del ) ;
      }
  liste_afficher( &liste );


    printf("Decanillage de 5 elements dans la liste\n");
    nb = liste_nb_lire(&liste) ;
    for( i=0 ; i <5 ; i++ )
      {
	ind_del = random()%nb ; 
	printf("\tDecanillage de la positon %d\n" , ind_del ) ;
	liste_elem_decaniller( &liste , ind_del ) ;
      }
  liste_afficher( &liste );

  printf("Recherche d'elements dans la liste\n") ;

  booleen_t ok = FAUX ; 
  while( ! ok ) 
    {
      i = random()%nb ;
      cell_pid_affecter( &c , getpid()+i ) ;
      cell_marque_affecter( &c , 'A'+i ) ;
      elem_cell_affecter( &e , c ) ;
      elem_etat_affecter( &e , EN_COURSE ) ;
      printf("Recherche de ");
      elem_afficher(e) ;
      if( liste_elem_rechercher( &ind_rech ,
				 &liste, e ) ) 
	{
	  ok = VRAI ;
	  printf("--> indice %d\n" , ind_rech ) ;
	}
      else
	printf("--> inconnu\n" ) ;
    }

  cell_pid_affecter( &c , getpid() ) ;
  cell_marque_affecter( &c , 'Z' ) ;
  elem_cell_affecter( &e , c ) ;
  elem_etat_affecter( &e , EN_COURSE ) ;
  printf("Recherche de ");
  elem_afficher(e) ;
  if( liste_elem_rechercher( &ind_rech ,
			     &liste, e ) ) 
    printf("--> indice %d\n" , ind_rech ) ;
  else
    printf("--> inconnu\n" ) ;
  
  exit(0);
}
