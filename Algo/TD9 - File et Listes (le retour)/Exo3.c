#include <stdio.h>
#include <stdlib.h>

typedef union
{
    int nbr;
    char carac;
} t_union;

typedef struct el
{
    t_union valeur;
    struct el *pred;
    struct el *succ;
} t_element;

typedef struct
{
    t_element *drapeau;
    t_element *ec;
} t_liste;

int main()
{
    t_liste nb1;
    initListe(&nb1);
    enTete(&nb1);
    ajouterDroit(&nb1, 5);
    ajouterDroit(&nb1, 'F');
    return 0;
}