#include <stdio.h>

//PILE
#define t_max 50
int pile[t_max];
int sommet;

void initPile()
{
    sommet = -1;
}

void empiler(int i)
{
    if (sommet < t_max - 1)
    {
        sommet++;
        pile[sommet] = i;
    }
}

void depiler(int *i)
{
    if (sommet > -1)
    {
        *i = pile[sommet];
        sommet--;
    }
}

int pileVide()
{
    return (sommet == -1);
}
//PILE

int main()
{
    initPile();
    int nbLu;
    scanf("%i", &nbLu);

    int nbLuSave = nbLu;

    while (nbLu != 0)
    {
        empiler(nbLu % 2);
        nbLu = nbLu / 2;
    }

    int nbPile;
    while (!pileVide())
    {
        depiler(&nbPile);
        printf("%i ", nbPile);
    }

    convertirBase(nbLuSave, 4);

    return 0;
}

void convertirBase(int nb, int base)
{
    printf("\n\n");
    while (nb != 0)
    {
        empiler(nb % base);
        nb = nb / base;
    }

    int nbPile;
    while (!pileVide())
    {
        depiler(&nbPile);
        printf("%i ", nbPile);
    }
}