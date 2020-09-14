#include <stdio.h>

int main()
{
    char fileName[20];
    printf("Nommez votre fichier !");
    scanf("%s", &fileName);
    FILE *file = fopen(fileName, "a");

    int number;
    printf("Choisissez le number à ajouter au fichier : ");
    scanf("%i", &number);
    fprintf(file, "%i ", number);

    fclose(file);
}
