#include <stdio.h>

int main()
{
}

void count(FILE *file, int *charCount, int *lineCount)
{
    char charLu;
    fscanf(file, "%c", &charLu);

    while (!feof(file))
    {
        if (charLu == "\n")
            (*lineCount)++;
        else
            (*charCount)++;
        fscanf(file, "%c", &charLu);
    }
}
