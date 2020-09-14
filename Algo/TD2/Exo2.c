#include <stdio.h>
#define NB_CARTES 52
#define TAILLE_MAIN 13
#include <stdlib.h>

typedef enum
{
    Deux,
    Trois,
    Quatre,
    Cinq,
    Six,
    Sept,
    Huit,
    Neuf,
    Dix,
    Valet,
    Dame,
    Roi,
    As
} t_hauteur;

typedef enum
{
    Carreau,
    Coeur,
    Trefle,
    Pique
} t_couleur;

typedef struct
{
    t_hauteur hauteur;
    t_couleur couleur;
} t_carte;

void initialiser(t_carte jeu[])
{
    int j = 0;
    int i;
    int k;
    for (i = 0; i < 4; i++)
    {
        for (k = 0; k < 13; k++)
        {
            jeu[j].couleur = i;
            jeu[j].hauteur = k;
            j++;
        }
    }
}

void melanger(t_carte jeu[])
{
    int i;
    for (i = 0; i < NB_CARTES; i++)
    {
        t_carte save = jeu[i];
        int random = rand() % 52;
        jeu[i] = jeu[random];
        jeu[random] = save;
    }
}

void distribuer(t_carte jeu[], t_carte j1[], t_carte j2[], t_carte j3[], t_carte j4[])
{
    int i;
    int j = 0;
    for (i = 0; i < NB_CARTES; i += 4)
    {
        j1[j] = jeu[i];
        j2[j] = jeu[i + 1];
        j3[j] = jeu[i + 2];
        j4[j] = jeu[i + 3];
        j++;
    }
}

int estInferieur(t_carte carte1, t_carte carte2)
{
    return carte1.hauteur < carte2.hauteur;
}

void trier(t_carte main[])
{
    int fini = 0;

    while (!fini)
    {
        fini = 1;
        int i;
        for (i = 0; i < TAILLE_MAIN - 1; i++)
        {
            if (main[i].couleur > main[i + 1].couleur)
            {
                t_carte save = main[i + 1];
                main[i + 1] = main[i];
                main[i] = save;

                fini = 0;
            }
            else if (main[i].couleur == main[i + 1].couleur && main[i].hauteur > main[i + 1].hauteur)
            {
                t_carte save = main[i + 1];
                main[i + 1] = main[i];
                main[i] = save;

                fini = 0;
            }
        }
    }
}

void afficherCarte(t_carte carte)
{
    switch (carte.hauteur)
    {
    case Deux:
        printf("Deux");
        break;
    case Trois:
        printf("Trois");
        break;
    case Quatre:
        printf("Quatre");
        break;
    case Cinq:
        printf("Cinq");
        break;
    case Six:
        printf("Six");
        break;
    case Sept:
        printf("Sept");
        break;
    case Huit:
        printf("Huit");
        break;
    case Neuf:
        printf("Neuf");
        break;
    case Dix:
        printf("Dix");
        break;
    case Valet:
        printf("Valet");
        break;
    case Dame:
        printf("Dame");
        break;
    case Roi:
        printf("Roi");
        break;
    case As:
        printf("As");
        break;
    }

    printf(" de ");

    switch (carte.couleur)
    {
    case Carreau:
        printf("Carreau");
        break;
    case Trefle:
        printf("Trefle");
        break;
    case Pique:
        printf("Pique");
        break;
    case Coeur:
        printf("Coeur");
        break;
    }

    printf("\n");
}

void afficherMain(t_carte main[])
{
    int i;
    for (i = 0; i < TAILLE_MAIN; i++)
    {
        afficherCarte(main[i]);
    }
}

int main()
{
    srand(time(NULL));

    t_carte jeu[52];
    initialiser(jeu);
    melanger(jeu);
    t_carte j1[TAILLE_MAIN], j2[TAILLE_MAIN], j3[TAILLE_MAIN], j4[TAILLE_MAIN];
    distribuer(jeu, j1, j2, j3, j4);
    trier(j1);
    afficherMain(j1);
    return 0;
}