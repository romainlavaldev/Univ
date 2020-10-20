#include <stdio.h>
#include "listePoint.c"

void afficher()
{
    enTete();
    while (!horsListe())
    {
        printf("%i - ", valeurElt());
        suivant();
    }
}

void eleverCarre()
{
    enTete();
    while (!horsListe())
    {
        modifElt(valeurElt() * valeurElt());
        suivant();
    }
}

void inserer()
{
    int nbLu;
    printf("Nbr à ajouter ? : ");
    scanf("%i", &nbLu);
    if (!listeVide())
    {
        enQueue();
        if (nbLu >= valeurElt())
        {
            ajoutDroit(nbLu);
        }
        else
        {
            enTete();
            while (nbLu > valeurElt())
            {
                suivant();
            }
            ajoutGauche(nbLu);
        }
    }
    else
    {
        ajoutDroit(nbLu);
    }
}

int somme()
{
    int res = 0;
    enTete();
    while (!horsListe())
    {
        res += valeurElt();
        suivant();
    }
    return res;
}

void supprimer()
{
    int nbLu;
    printf("\nNbr à supprimer ? : ");
    scanf("%i", &nbLu);
    enTete();
    while (!horsListe())
    {
        if (valeurElt() == nbLu)
            oterElt();
        suivant();
    }
}

void viderListe(int version)
{
    if (version == 2)
    {
        enQueue();
        while (!listeVide())
        {
            oterElt();
        }
    }
    else
    {
        while (!listeVide())
        {
            enTete();
            oterElt();
        }
    }
}

int main()
{
    initListe();
    enTete();
    ajoutDroit(1);
    ajoutDroit(3);
    ajoutDroit(5);
    ajoutDroit(9);
    afficher();
    printf("\nLa somme de la liste vaut %i\n", somme());
    eleverCarre();
    inserer();
    afficher();
    supprimer();
    afficher();
    viderListe(1);
    afficher();
    return 0;
}
