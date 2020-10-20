#include <stdio.h>
#include <stdlib.h>

typedef struct el
{
    int entier;
    struct el *pred;
    struct el *succ;
} t_element;

typedef struct
{
    t_element *drapeau;
    t_element *ec;
} t_liste;

void inserer(t_liste *l, int x);

void trier(t_liste *li)
{
    t_liste lInter;
    initListe(&lInter);
    enQueue(li);
    while (!horsListe(li))
    {
        inserer(&lInter, oterElt(li));
        precedent(li);
    }
    li = &lInter;
}

int main()
{
    return 0;
}
