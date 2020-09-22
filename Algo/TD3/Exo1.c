#include <stdio.h>
#define N 8

void init_matrice(char matrice[N][N])
{
    int i;
    for (i = 0; i < N; i++)
    {
        int j;
        for (j = 0; j < N; j++)
        {
            matrice[i][j] = '.';
        }
    }
}

void afficheMat(char matrice[N][N])
{
    int i;
    int j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%c  ", matrice[i][j]);
        }
        printf("%c", '\n');
    }
}

int valide(int x, int y)
{
    return ((x < N && x >= 0) && (y < N && y >= 0));
}

void placerCavalier(char matrice[N][N], int y, int x)
{
    matrice[x][y] = 'c';
    if (valide(x - 1, y - 2))
        matrice[x - 1][y - 2] = '*';
    if (valide(x + 1, y - 2))
        matrice[x + 1][y - 2] = '*';
    if (valide(x - 1, y + 2))
        matrice[x - 1][y + 2] = '*';
    if (valide(x + 1, y + 2))
        matrice[x + 1][y + 2] = '*';
    if (valide(x + 2, y - 1))
        matrice[x + 2][y - 1] = '*';
    if (valide(x + 2, y + 1))
        matrice[x + 2][y + 1] = '*';
    if (valide(x - 2, y - 1))
        matrice[x - 2][y - 1] = '*';
    if (valide(x - 2, y + 1))
        matrice[x - 2][y + 1] = '*';
}

int main()
{
    char plateau[N][N];
    init_matrice(plateau);
    printf("Selectionnez coordonnés tour : ");
    int tourX, tourY;
    scanf("%i", &tourX);
    scanf("%i", &tourY);
    int i;
    /*for (i = 0; i < N; i++)
    {
        plateau[tourY - 1][i] = '*';
        plateau[i][tourX - 1] = '*';
    }

    plateau[tourY - 1][tourX - 1] = 't';*/
    placerCavalier(plateau, tourX - 1, tourY - 1);

    afficheMat(plateau);

    return 0;
}
