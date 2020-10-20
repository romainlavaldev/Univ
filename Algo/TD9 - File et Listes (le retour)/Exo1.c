#include <stdio.h>
#include <stdlib.h>
#include "fileMulti.c"

t_file pair;
t_file impair;

int main()
{
    initFile(&pair);
    initFile(&impair);

    int nbLu;
    do
    {
        printf("Ajouter un nombre : ");
        scanf("%i", &nbLu);
        if (nbLu != -1)
        {
            if (nbLu % 2 == 0)
                ajouter(&pair, nbLu);
            else
                ajouter(&impair, nbLu);
            system("cls");
        }
    } while (nbLu != -1);

    printf("Pairs : ");
    while (!fileVide(pair))
    {
        printf("%i  ", retirer(&pair));
    }
    printf("\nImpairs : ");
    while (!fileVide(impair))
    {
        printf("%i  ", retirer(&impair));
    }

    return 0;
}