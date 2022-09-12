
#include <stdio.h>
#include <unistd.h>
#include <time.h> 
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int nbFois = 1000;
    int i = 1;
    clock_t start, end;

    printf("fils %d, je demare la commande %d fois\n", i, nbFois);
            start = clock();
            printf("%ld\n",start);
            for (int j = 0; j < nbFois; j++)
            {
                //Execution de la commande
                system(argv[2]);
            }
            end = clock();

            unsigned long chrono = (end -  start) * 1000 / CLOCKS_PER_SEC;
            printf("fils %d, j'ai fini. Temps total : %ld\n", i, chrono);
    return 0;
}
