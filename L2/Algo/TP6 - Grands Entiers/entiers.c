#include <stdio.h>
#include <stdlib.h>
#include "listes.c"
#define MAX_LISTE 11
#define VRAI 1
#define FAUX 0

void vider_liste()
{
    int i;
    for (i = 1; i < MAX_LISTE; i++)
        init_liste(i);
}

int taille(int n)
{
    en_tete(n);
    int i = 0;
    while (!hors_liste(n))
    {
        i++;
        suivant(n);
    }
    return i;
}

void saisie()
{

    int iliste, entier;
    printf("Quelle liste ? : ");
    scanf("%i", &iliste);
    init_liste(iliste);
    printf("Veuillez entrer un nombre entier par entier (-1 = fin): ");
    en_tete(iliste);
    scanf("%i", &entier);
    while (entier != -1)
    {

        ajout_droit(iliste, entier);
        scanf("%i", &entier);
    }
}

void affichage()
{
    int iliste;
    printf("Quelle liste ? : ");
    scanf("%i", &iliste);

    printf("entier numéro %i : ", iliste);
    en_tete(iliste);
    int nbrLu;
    while (!hors_liste(iliste))
    {
        valeur_elt(iliste, &nbrLu);
        printf("%i", nbrLu);
        suivant(iliste);
    }
}

void affectation(void)
{
    int ilisteSource, ilisteDest;
    printf("Quelle liste ? : ");
    scanf("%i", &ilisteSource);
    printf("Dans quelle liste ? : ");
    scanf("%i", &ilisteDest);

    if (taille(ilisteSource) == 0)
        printf("liste vide");

    else if (taille(ilisteSource) < taille(ilisteDest))
    {
        init_liste(ilisteDest);

        en_tete(ilisteSource);
        en_tete(ilisteDest);
        int vec;
        while (!hors_liste(ilisteSource))
        {
            valeur_elt(ilisteSource, &vec);
            modif_elt(ilisteDest, vec);
            suivant(ilisteSource);
            suivant(ilisteDest);
        }
    }
}

void comparaison(void)
{
}

void addition(void)
{
}

int main(void)
{
    // Programme principal
    int choix; // choix de l'utilisateur
    int i;

    for (i = 1; i < MAX_LISTE; i++)
        init_liste(i);

    do
    {
        // Affichage du menu
        printf("\nMenu :\n");
        printf(" 1 - Saisir un entier\n");
        printf(" 2 - Afficher un entier\n");
        printf(" 3 - Affecter un entier\n");
        printf(" 4 - Comparer deux entiers\n");
        printf(" 5 - Additionner deux entiers\n");
        printf(" 6 - Quitter\n");
        printf("Votre choix : ");
        scanf("%i", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix)
        {
        case 1:
            saisie();
            break;
        case 2:
            affichage();
            break;
        case 3:
            affectation();
            break;
        case 4:
            comparaison();
            break;
        case 5:
            addition();
            break;
        case 6:
            break;
        default:
            printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
        }
    } while (choix != 6);
    printf("Au revoir !\n");
    return EXIT_SUCCESS;
}