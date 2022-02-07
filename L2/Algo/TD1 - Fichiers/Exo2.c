#include <stdio.h>


void count(FILE *file, int *charCount, int *lineCount)
{
    char charLu;
    fscanf(file, "%c", &charLu);

    while (!feof(file))
    {
        if (charLu == '\n')
            (*lineCount)++;
        else
            (*charCount)++;
        fscanf(file, "%c", &charLu);
    }
}


int main()
{
    FILE* fich;

    char fileName[20];
    printf("Enter file name : ");
    scanf("%s", &fileName);

    fich = fopen(fileName, "r");

    int charCount = 0;
    int lineCount = 0;

    count(fich, &charCount, &lineCount);

    printf("Il y a %i char et %i lignes", charCount, lineCount);
}
