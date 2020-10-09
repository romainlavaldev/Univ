#include <stdio.h>

typedef struct element
{
    int valeur;
    struct element *suivant;
} t_element;

t_element *pile;

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
    t_element *nouv;

    nouv = malloc(sizeof(t_element));
    nouv->valeur = n;
    nouv->suivant = pile;
    pile = nouv;
}

void depiler(int *n)
{
    t_element *sommet;
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
