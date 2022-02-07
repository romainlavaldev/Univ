#include <stdio.h>

int main()
{
    FILE *baseFile, *posFile, *negFile;
    baseFile = fopen("releves.txt", "r");
    negFile = fopen("negatif.txt", "w");
    posFile = fopen("positif.txt", "w");

    int numberRead;

    fscanf(baseFile, "%i", &numberRead);
    int max = numberRead;
    int min = numberRead;

    while (!feof(baseFile))
    {

        if (numberRead < 0)
        {
            fprintf(negFile, "%i ", numberRead);
            if (numberRead < min)
                min = numberRead;
        }
        else
        {

            fprintf(posFile, "%i ", numberRead);
            if (numberRead > max)
                max = numberRead;
        }

        fscanf(baseFile, "%i", &numberRead);
    }

    printf("Le max : %i     ", max);
    printf("Le min : %i", min);

    return 0;
}