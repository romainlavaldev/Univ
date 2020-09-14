#include <stdio.h>

int main()
{
    printf("Entrez un nombre strictement positif : ");
    int nbrUser;
    scanf("%i", &nbrUser);

    FILE *file = fopen("diviseur.txt", "w");

    for (int i = 1; i <= nbrUser; i++) {
        if (nbrUser % i == 0) {
            fprintf(file, "%i ", i);

        }
    }

    fclose(file);
}
