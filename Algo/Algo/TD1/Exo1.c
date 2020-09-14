#include <stdio.h>

int main()
{
    FILE *fich;

    char nomFichier[20];
    scanf("%s", &nomFichier);

    fich = fopen(nomFichier, "r");
    if (fich == NULL)
    {
        printf("Erreur");
        return -1;
    }

    int nbrPair = 0;

    int nbrLu;

    while (!feof(fich))
    {
        fscanf(fich, "%i", &nbrLu);
        if (nbrLu % 2 == 0)
            nbrPair++;
    }
    fclose(fich);
    printf("Le fichier contient %i nombres paires", nbrPair);
}
