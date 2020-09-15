#include <stdio.h>

void fileCreate() //Ecrit une suite de nombres dans le fichier choisi
{
    printf("Entrez le nom du fichier à creer : ");
    char fileName[20];
    scanf("%s", &fileName);

    printf("Entrez une suite de nombres (-1) pour finir : ");
    FILE *file;
    file = fopen(fileName, "w");

    int number;
    scanf("%i", &number);

    while (number != -1)
    {
        fprintf(file, "%i ", number);
        scanf("%i", &number);
    }

    fclose(file);
}

void filePrint() //Affiche le contenu du fichier choisi
{

    printf("Entrez le nom du fichier à ouvrir : ");
    char fileName[20];
    scanf("%s", &fileName);

    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Error!");
        return;
    }

    while (!feof(file))
    {
        int numberRead;
        fscanf(file, "%i", &numberRead);
        printf("%i ", numberRead);
    }
}

int main()
{
    fileCreate();
    filePrint();
    return 0;
}