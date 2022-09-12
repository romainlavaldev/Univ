
#include <stdio.h>
#include <unistd.h>
#include <time.h> 
#include <stdlib.h>

int nbProcs;


//TOUT LES TEMPS SONT EN MICROSECONDES

int main(int argc, char const *argv[])
{
    
    nbProcs = strtol(argv[3], NULL, 10);

    int tabTubes[nbProcs][2]; //Tableau de la forme [ tube[0] ][ tube[1] ]


    //Creation des processus fils
    int pid;
    for (int i = 0; i < nbProcs; i++)
    {

        //On ouvre le tube pour le fils qui va etre créer        
        pipe(tabTubes[i]);

        printf("Creation fils %d\n", i);
        switch (pid = fork())
        {
        //fils
        case 0:
            //On ferme la lecture
            close(tabTubes[i][0]);
            
            clock_t start, end;
            unsigned long chrono = 0;
            int nbFois = strtol(argv[1], NULL, 10);

            printf("fils %d, je demare la commande %d fois\n", i, nbFois);
            start = clock();
            for (int j = 0; j < nbFois; j++)
            {
                //Execution de la commande
                system(argv[2]);
            }
            end = clock();

            chrono = (end - start) * 1000000 / CLOCKS_PER_SEC;
            printf("fils %d, j'ai fini. Temps total : %ld\n", i, chrono);

            //Envoi dans le tube
            write(tabTubes[i][1], &chrono, sizeof(long));

            close(tabTubes[i][1]);
            exit(0);
            break;
        
        //Pere
        default:

            //On ferme l'écriture
            close(tabTubes[i][1]);

            break;
        }
    }

    //Attente fin des processus

    //Lecture des moyennes
    unsigned long moyLus = 0;
    unsigned long tpsLu;
    unsigned long nbFois = strtol(argv[1], NULL, 10);
    for (int i = 0; i < nbProcs; i++)
    {
        read(tabTubes[i][0], &tpsLu, sizeof(long));
        close(tabTubes[i][0]);
        printf("Pere : j'ai recu %ld de fils %d\n", tpsLu, i);
        moyLus = moyLus + (tpsLu / nbFois);
        printf("tpsLu (%ld) / nbFois (%ld) : %ld || MoyLu = %ld\n\n",tpsLu, nbFois, tpsLu / nbFois, moyLus);
    }
    
    
    unsigned long moy = moyLus / nbProcs;
    printf("Moyenne pour la commande : %s -> %ld microsecondes\n",argv[2] ,moy);

    return 0;
}
