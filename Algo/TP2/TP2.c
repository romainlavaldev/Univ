#include <stdio.h>
#define N 45
#include <stdlib.h>
#include <unistd.h>

void printMat(int mat[N][N]) //Affiche la matrice (* pour cellule vivante)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (mat[i][j] == 1)
                printf("* ");
            else
                printf("  ");
        }
        printf("%c", '\n');
    }
    //   printf("__________________________________________________________\n\n"); DEBUG
}

int estValide(int i, int j) //Verifie si la case est dans la matrice
{
    return (i < N && i >= 0) && (j < N && j >= 0);
}

void initMat(int mat[N][N]) //Initialise la matrice à 0 et place les cellules fournis dans le fichier data
{
    FILE *f;

    char fileName[20];
    do
    {
        printf("Choisissez le fichier à initialiser : ");
        scanf("%s", fileName);
        f = fopen(fileName, "r");
    } while (f == NULL);

    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            mat[i][j] = 0;
        }
    }

    int xLu, yLu;
    fscanf(f, "%i", &xLu);

    while (!feof(f))
    {
        fscanf(f, "%i", &yLu);
        mat[yLu][xLu] = 1;
        fscanf(f, "%i", &xLu);
    }
}

int main()
{

    int nbGene;

    int matrice[N][N];

    initMat(matrice);

    printf("Choisissez le nombre de générations à afficher : ");
    scanf("%i", &nbGene);

    int x, i, j;
    int saveMat[N][N];
    system("cls");
    printMat(matrice);
    system("pause");
    for (x = 1; x < nbGene; x++)
    {
        sleep(0.4);
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                //Compte des 8 cases voisines
                int nbVoisin = 0;
                if (estValide(i - 1, j) && matrice[i - 1][j] == 1)
                    nbVoisin++;
                if (estValide(i + 1, j) && matrice[i + 1][j] == 1)
                    nbVoisin++;
                if (estValide(i, j - 1) && matrice[i][j - 1] == 1)
                    nbVoisin++;
                if (estValide(i, j + 1) && matrice[i][j + 1] == 1)
                    nbVoisin++;
                if (estValide(i - 1, j - 1) && matrice[i - 1][j - 1] == 1)
                    nbVoisin++;
                if (estValide(i - 1, j + 1) && matrice[i - 1][j + 1] == 1)
                    nbVoisin++;
                if (estValide(i + 1, j - 1) && matrice[i + 1][j - 1] == 1)
                    nbVoisin++;
                if (estValide(i + 1, j + 1) && matrice[i + 1][j + 1] == 1)
                    nbVoisin++;

                //Action en fonction du nombre de voisins (énoncé)
                if (!(nbVoisin == 2 || nbVoisin == 3) && (matrice[i][j] == 1))
                    saveMat[i][j] = 0;
                else if (nbVoisin == 3 && matrice[i][j] == 0)
                    saveMat[i][j] = 1;
                else
                    saveMat[i][j] = matrice[i][j];
            }
        }

        //Mise a jour de la matrice pour la prochaine génération
        int k, l;
        for (k = 0; k < N; k++)
        {
            for (l = 0; l < N; l++)
            {
                matrice[k][l] = saveMat[k][l];
            }
        }

        system("cls");
        printMat(matrice);
    }

    return 0;
}