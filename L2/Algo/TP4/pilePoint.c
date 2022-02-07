#include <stdlib.h>

typedef struct elementPile
{
    int valeur;
    struct elementPile *suivant;
} t_elementPile;

t_elementPile *pile;

void initPile()
{
    pile = NULL;
}

int pileVide()
{
    return (pile == NULL);
}

void empiler(int n)
{
    t_elementPile *nouv;

    nouv = malloc(sizeof(t_elementPile));
    nouv->valeur = n;
    nouv->suivant = pile;
    pile = nouv;
}

void depiler(int *n)
{
    t_elementPile *sommet;
    if (pile != NULL)
    {
        *n = pile->valeur;
        sommet = pile;
        pile = sommet->suivant;
        free(sommet);
    }
}

void sommetPile(int *n)
{
    if (pile != NULL)
        *n = pile->valeur;
}
