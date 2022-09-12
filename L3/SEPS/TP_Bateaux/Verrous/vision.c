#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
 
     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );


     int fd;

     struct stat fstat;
     stat(fich_mer, &fstat);

     time_t lastModificationDate = fstat.st_mtime;

     while (1){

          stat(fich_mer, &fstat);

/*
          printf("\n\n");          
          printf("lastModificationDate : ");
          printf(ctime(&lastModificationDate));
          printf("\n new time : ");
          printf(ctime(&fstat.st_mtime));
*/


          if (difftime(fstat.st_mtime, lastModificationDate)){
               printf("Ouverture fichier Mer\n");
               fd = open( fich_mer , O_RDONLY , 0644 );
               if (!fd) printf("KO\n");
               else printf("OK\n");

               struct flock verrou;

               verrou.l_type = F_RDLCK;
               verrou.l_whence = 0;
               verrou.l_start = 0;
               verrou.l_len = 0;

               fcntl(fd, F_SETLKW, &verrou);
    
               mer_afficher(fd);
               verrou.l_type = F_UNLCK;
               fcntl(fd, F_SETLKW, &verrou);
               close(fd);
               lastModificationDate = fstat.st_mtime;
          }
     }

     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
