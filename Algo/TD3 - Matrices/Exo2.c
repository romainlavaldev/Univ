#include <stdio.h>
#define N 7
#define M 11

int valide(int x, int y)
{
    return ((x < M && x >= 0) && (y < N && y >= 0));
}

int estVide(int matrice[N][M], int x, int y)
{
    return (valide(x, y) && (matrice[y][x] == 0));
}

void afficheMat(int matrice[N][M])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%i ", matrice[i][j]);
        }
        printf("%c", '\n');
        printf("%c", '\n');
    }
}

void afficherLab(int lab[N][M])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (lab[i][j] == -1)
                printf("%c ", '*');
            else if (lab[i][j] == -2)
            {
                printf("%c ", '-');
            }
            else
                printf("  ");
        }
        printf("%c", '\n');
    }
}

void marquerChemin(int matrice[N][M], int xa, int ya)
{
    while (matrice[ya][xa] != 1)
    {
        if (valide(xa, ya - 1) && matrice[ya - 1][xa] == matrice[ya][xa] - 1)
        {
            matrice[ya][xa] = -2;
            xa = xa;
            ya = ya - 1;
        }
        else if (valide(xa, ya + 1) && matrice[ya + 1][xa] == matrice[ya][xa] - 1)
        {
            matrice[ya][xa] = -2;
            xa = xa;
            ya = ya + 1;
        }
        else if (valide(xa - 1, ya) && matrice[ya][xa - 1] == matrice[ya][xa] - 1)
        {
            matrice[ya][xa] = -2;
            xa = xa - 1;
            ya = ya;
        }
        else if (valide(xa + 1, ya) && matrice[ya][xa + 1] == matrice[ya][xa] - 1)
        {
            matrice[ya][xa] = -2;
            xa = xa + 1;
            ya = ya;
        }
    }
    matrice[ya][xa] = -2;
}

void chercherChemin(int matrice[N][M], int xd, int yd, int xa, int ya)
{
    int marqueur = 1;
    matrice[yd][xd] = marqueur;

    int i = 0;
    int j = 0;

    while (matrice[ya][xa] == 0)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                if (matrice[i][j] == marqueur)
                {
                    if (valide(j, i - 1) && estVide(matrice, j, i - 1))
                        matrice[i - 1][j] = marqueur + 1;
                    if (valide(j, i + 1) && estVide(matrice, j, i + 1))
                        matrice[i + 1][j] = marqueur + 1;
                    if (valide(j - 1, i) && estVide(matrice, j - 1, i))
                        matrice[i][j - 1] = marqueur + 1;
                    if (valide(j + 1, i) && estVide(matrice, j + 1, i))
                        matrice[i][j + 1] = marqueur + 1;
                }
            }
        }
        marqueur++;
    }
    marquerChemin(matrice, xa, ya);
}

void nettoyer(int matrice[N][M])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (matrice[i][j] > 0)
                matrice[i][j] = 0;
        }
    }
}

int main()
{
    int lab[N][M] = {{0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0}, {0, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0}, {0, 0, 0, 0, 0, -1, 0, 0, 0, -1, 0}, {-1, -1, -1, -1, 0, -1, -1, -1, 0, -1, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, -1, 0, -1, -1, -1, -1, -1, 0, -1, 0}, {0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0}};
    chercherChemin(lab, 8, 0, 0, 6);
    nettoyer(lab);
    afficheMat(lab);
    afficherLab(lab);
    return 0;
}
