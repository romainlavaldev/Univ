#include <stdio.h>

int main()
{
    FILE* fich;

    char fileName[20];
    printf("Enter file name : ");
    scanf("%s", &fileName);

    fich = fopen(fileName, "r");
    if (fich == NULL)
    {
        printf("Error");
        return -1;
    }

    int nbrPair = 0;

    int nbrLu;

    while (!feof(fich))
    {
        fscanf(fich, "%i", &nbrLu);
        if (nbrLu % 2 == 0){
            nbrPair++;
        }
    }
    fclose(fich);
    printf("Le fichier contient %i nombres paires", nbrPair);
}
