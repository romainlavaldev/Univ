// L2 info - TP 1 - Base de donnees sur des personnages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

// Definition du type categorie
typedef enum
{
    elfe,
    dragon,
    nain,
    titan
} t_categ;

// Definition du type position (ligne, colonne)
typedef struct
{
    int x, y;
} t_posit;

// Definition du type personnagee (nom, categorie, coordonnnees, points de vie)
typedef struct
{
    char nom[20];
    t_categ categ;
    t_posit posit;
    int pdv;
} t_pers;

void afficher_base(t_pers *pers, int nb_pers)
{

    int i;
    for (i = 0; i < nb_pers; i++)
    {
        printf("Personnage %i : %s \n", i + 1, pers[i].nom);
        switch (pers[i].categ)
        {
        case 0:
            printf("Categorie : Elfe\n");
            break;
        case 1:
            printf("Categorie : Dragon\n");
            break;
        case 2:
            printf("Categorie : Nain\n");
            break;
        case 3:
            printf("Categorie : Titan\n");
            break;
        }

        printf("Position : x -> %i  y -> %i\n", pers[i].posit.x, pers[i].posit.y);
        printf("Points de Vie : %i\n\n", pers[i].pdv);
    }
}

void afficher_nombre(t_pers *pers, int nb_pers)
{
    int nbElfe = 0;
    int nbDragon = 0;
    int nbTitan = 0;
    int nbNain = 0;
    int i;
    for (i = 0; i < nb_pers; i++)
    {
        switch (pers[i].categ)
        {
        case 0:
            nbElfe++;
            break;
        case 1:
            nbDragon++;
            break;
        case 2:
            nbNain++;
            break;
        case 3:
            nbTitan++;
            break;
        }
    }

    printf("Il y a %i Elfe(s), %i Dragon(s), %i Nain(s) et %i Titan(s)\n", nbElfe, nbDragon, nbNain, nbTitan);
}

void afficher_max(t_pers *pers, int nb_pers)
{
    int max = 0;
    int i;
    for (i = 1; i < nb_pers; i++)
    {
        if (pers[i].pdv > pers[i].pdv)
            max = i;
    }
    printf("%s à le plus de points de vie (%i)\n", pers[max].nom, pers[max].pdv);
}

void sauvegarder(t_pers *pers, int nb_pers)
{
    FILE *saveFile = fopen("base.txt", "w");
    int i;
    for (i = 0; i < nb_pers; i++)
    {
        fprintf(saveFile, "%s\n %i\n %i %i\n %i\n", pers[i].nom, pers[i].categ, pers[i].posit.x, pers[i].posit.y, pers[i].pdv);
    }
    fclose(saveFile);
}

void charger(t_pers *pers, int *nb_pers)
{
    FILE *saveFile = fopen("base.txt", "r");

    int i = 0;

    int cat;
    fscanf(saveFile, "%s", pers[i].nom);

    while (!feof(saveFile))
    {
        fscanf(saveFile, "%i", &cat);
        pers[i].categ = (t_categ)cat;
        fscanf(saveFile, "%i", &(pers[i].posit.x));
        fscanf(saveFile, "%i", &(pers[i].posit.y));
        fscanf(saveFile, "%i", &(pers[i].pdv));
        i++;
        fscanf(saveFile, "%s", pers[i].nom);
    }
    *nb_pers = i;
}

void ajouter(t_pers *pers, int *nb_pers)
{
    char nom[20];
    printf("Veuillez entrer le nom du personnage : ");
    scanf("%s", nom);
    int i;
    int trouve = 0;
    for (i = 0; i < *nb_pers; i++)
    {

        if (*nom == *(pers[i].nom))
        {
            trouve = 1;
        }
    }
    if (trouve)
    {
        printf("Ce personnage existe déja !\n");
    }
    else
    {
        printf("%s", nom); //debug
        pers[*nb_pers].nom = nom;
        printf("Entrez la categorie du personnage (0,1,2,3) : ");
        scanf("%i", &(pers[*nb_pers].categ));
        printf("Entrez la position X du personnage : ");
        scanf("%i", &(pers[*nb_pers].posit.x));
        printf("Entrez la position Y du personnage : ");
        scanf("%i", &(pers[*nb_pers].posit.y));
        printf("Entrez le nombre de points de vie du personnage : ");
        scanf("%i", &(pers[*nb_pers].pdv));
        printf("%s à été ajouté !", nom);

        *nb_pers += 1;
    }
}

void supprimer(t_pers *pers, int *nb_pers)
{

    char nomPerso[20];
    printf("Quelle personnage voulez vous supprimer ? : ");
    scanf("%s", nomPerso);
    int i;
    int indiceSuppr = -1;
    for (i = 0; i < *nb_pers; i++)
    {

        if (*nomPerso == *(pers[i].nom))
        {
            indiceSuppr = i;
        }
    }

    printf("%i\n", *nb_pers);
    if (indiceSuppr != -1) // 0 2 2
    {
        int j = indiceSuppr;
        *nb_pers -= 1;
        for (j; j < *nb_pers; j++)
        {
            pers[j] = pers[j + 1];
        }
        printf("%s à été supprimé\n", nomPerso);
    }
    else
    {
        printf("Personnage inconnu !");
    }
}

// Programme principal
int main(void)
{
    int choix; // Choix de l'utilisateur

    // Declaration de la base de donnees,
    // de taille maximale 50 et de taille utile nb_pers

    t_pers pers[N];

    int nb_pers = 0;

    do
    { // Affichage du menu
        printf("\nMenu :\n");
        printf(" 1 - Afficher tous les personnages\n");
        printf(" 2 - Afficher le nombre de personnages par categorie\n");
        printf(" 3 - Afficher le nom du personnage qui a le plus de points de vie\n");
        printf(" 4 - Sauvegarder la base\n");
        printf(" 5 - Charger la base depuis le fichier\n");
        printf(" 6 - Quitter\n");
        printf(" 7 - Supprimer un personnage\n");
        printf(" 8 - Ajouter un personnage\n");
        printf("Votre choix : ");
        scanf("%i", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix)
        {
        case 1:
            afficher_base(pers, nb_pers);
            break;
        case 2:
            afficher_nombre(pers, nb_pers);
            break;
        case 3:
            afficher_max(pers, nb_pers);
            break;
        case 4:
            sauvegarder(pers, nb_pers);
            break;
        case 5:
            charger(pers, &nb_pers);
            break;
        case 6:
            break;
        case 7:
            supprimer(pers, &nb_pers);
            break;
        case 8:
            ajouter(pers, &nb_pers);
            break;
        default:
            printf("Erreur: votre choix doit etre compris entre 1 et 8\n");
        }
    } while (choix != 6);
    printf("Au revoir !\n");
    return EXIT_SUCCESS;
}