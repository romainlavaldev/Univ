#include <stdio.h>

int main()
{
    printf("Entrez un nombre strictement positif : ");
    int nbrUser;
    scanf("%i", &nbrUser);

    FILE *fich = fopen("diviseur.txt", "w");

    for (int i = 0; i < nbrUser; i++)
    {
        if (nbrUser % i == 0)
            fprintf(fich, "%i ", i);
    }

    fclose(fich);
}
