// L2 info - TP5 listes
#include <stdio.h>
#include <stdlib.h>
#include "listePoint.h"

// Fonctions de manipulation de la liste

void afficher(void)
{
    // Affiche les valeurs de la liste

    int elem;

    if (listeVide())
        printf("La liste est vide\n");
    else
    {
        printf("\nLa liste contient: ");
        enTete();
        while (!horsListe())
        {
            elem = valeurElt();
            printf("%i ", elem);
            suivant();
        }
        printf("\n");
    }
}

void inserer(void)
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

void afficher_multiples(void)
{
    int nbLu;
    printf("Nbr ? : ");
    scanf("%i", &nbLu);
    if (!listeVide())
    {
        enTete();
        while (!horsListe())
        {
            if (valeurElt() % nbLu == 0)
                printf("| %i |", valeurElt());
            suivant();
        }
    }
    else
    {
        printf("Liste vide\n");
    }
}

void compter(void)
{
    if (!listeVide())
    {
        int nbLu;
        printf("Nbr ? : ");
        scanf("%i", &nbLu);
        int cpt = 0;
        enTete();
        while (!horsListe())
        {
            if (valeurElt() == nbLu)
                cpt++;
            suivant();
        }
        printf("il y à %i fois le nombre %i dans la liste.\n", cpt, nbLu);
    }
    else
        printf("Liste vide");
}

void supprimer(void)
{
    if (!listeVide())
    {
        int nbLu;
        printf("Nbr ? : ");
        scanf("%i", &nbLu);
        enQueue();
        while (!horsListe())
        {
            if (valeurElt() == nbLu)
                oterElt();
            else
                precedent();
        }
    }
    else
        printf("Liste vide");
}

void vider_liste(void)
{
    enQueue();
    while (!listeVide())
    {
        oterElt();
    }
}

//	Programme principal
int main(void)
{
    int choix;

    // Initialisation de la liste d'entiers
    initListe();

    do
    {
        // Affichage du menu et saisie du choix
        printf("\nMenu :\n");
        printf(" 1 - Inserer une valeur\n");
        printf(" 2 - Afficher les multiples\n");
        printf(" 3 - Compter les occurrences d'une valeur\n");
        printf(" 4 - Supprimer une valeur\n");
        printf(" 5 - Vider la liste\n");
        printf(" 6 - Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix)
        {
        case 1:
            inserer();
            afficher();
            break;
        case 2:
            afficher_multiples();
            afficher();
            break;
        case 3:
            compter();
            afficher();
            break;
        case 4:
            supprimer();
            afficher();
            break;
        case 5:
            vider_liste();
            afficher();
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