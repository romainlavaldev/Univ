#include <stdio.h>
#include <stdlib.h>

/*Il y des system("cls") qui ne fonctionnent pas sous linux !*/

void initJeu(int grille[6][7], char j1[20], char j2[20]) //mise à zero de toutes les cases de la grille
{
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            grille[i][j] = 0;
        }
    }

    printf("Quel est le nom du joueur 1 ? : ");
    scanf("%s", j1);
    printf("Quel est le nom du joueur 2 ? : ");
    scanf("%s", j2);
}

void afficherGrille(int grille[6][7]) //X = joueur 1, O = joueur 2, . = case vide
{

    system("cls");
    printf("0 1 2 3 4 5 6\n");
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (grille[i][j] == 0)
                printf(". ");
            if (grille[i][j] == 1)
                printf("X ");
            if (grille[i][j] == 2)
                printf("O ");
        }
        printf("\n");
    }
    printf("\n");
}
void afficherGrilleINT(int grille[6][7]) //DEBUG
{
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            printf("%i ", grille[i][j]);
        }
        printf("\n");
    }
}

int placerPion(int grille[6][7], int joueur, int col) //place un nouveau pion et retourne si l'ajout à fonctionné | joueur : 1 -> j1   2 -> j2
{
    if (col >= 0 && col < 7)
    {
        int i = -1;
        while (grille[i + 1][col] == 0 && i + 1 < 6)
        {
            i++;
        }

        if (i == -1)
        {
            printf("Colonne déjà pleine !\n");
            return 0;
        }
        grille[i][col] = joueur;
        return 1;
    }
    printf("Colonne non valide !\n");
    return 0;
}

int caseValide(int i, int j)
{
    return ((i >= 0 && i < 6) && (j >= 0 && j < 7));
}

int verifierGrille(int grille[6][7]) //Verifie si la grille actuelle contient un gagnant (Beacoup d'appels mais plus facile a coder/comprendre)
{
    int i, j, compteurZero = 0; //Verifie si la grille est pleine
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (grille[i][j] == 0)
                compteurZero++;
        }
    }
    if (compteurZero == 0)
        return -1;

    for (i = 0; i < 6; i++) //verifie si une ligne contient 4 jetons de la même "couleur" et les uns à la suite des autres
    {
        int compteur = 1;
        for (j = 1; j < 7; j++)
        {
            if (grille[i][j] == grille[i][j - 1] && grille[i][j] != 0)
                compteur++;
            else
                compteur = 1;

            if (compteur == 4)
                return 1;
        }
    }

    for (j = 0; j < 7; j++) //verifie si une colonne contient 4 jetons de la même "couleur" et les uns à la suite des autres
    {
        int compteur = 1;
        for (i = 1; i < 6; i++)
        {
            if (grille[i][j] == grille[i - 1][j] && grille[i][j] != 0)
                compteur++;
            else
                compteur = 1;

            if (compteur == 4)
                return 1;
        }
    }

    for (i = 0; i < 6; i++) //Verifie les diagonnales
    {
        for (j = 0; j < 7; j++)
        {
            if (grille[i][j] != 0)
            {
                if (caseValide(i - 1, j - 1) && caseValide(i - 2, j - 2) && caseValide(i - 3, j - 3)) //Diagonnale supérieur gauche
                {
                    if (grille[i - 1][j - 1] == grille[i][j] && grille[i - 2][j - 2] == grille[i][j] && grille[i - 3][j - 3] == grille[i][j])
                        return 1;
                }

                if (caseValide(i - 1, j + 1) && caseValide(i - 2, j + 2) && caseValide(i - 3, j + 3)) //Diagonnale supérieur droite
                {
                    if (grille[i - 1][j + 1] == grille[i][j] && grille[i - 2][j + 2] == grille[i][j] && grille[i - 3][j + 3] == grille[i][j])
                        return 1;
                }
            }
        }
    }

    return 0;
}

void save(int grille[6][7], char j1[20], char j2[20]) //Place la grille dans un fichier (sous forme d'une suite d'entier, un saut de ligne pour facilité la lecture puis les noms des joueurs)
{
    FILE *f = fopen("partie.txt", "w");
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            fprintf(f, "%i ", grille[i][j]);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "%s ", j1);
    fprintf(f, "%s", j2);
    fclose(f);
}

void load(int grille[6][7], char j1[20], char j2[20]) //Initialise la grille avec les valeurs sauvegardées
{
    FILE *f = fopen("partie.txt", "r");
    int i, j;
    int nbrLu;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            fscanf(f, "%i ", &nbrLu);
            grille[i][j] = nbrLu;
        }
    }
    fscanf(f, "%s", j1);
    fscanf(f, "%s", j2);
    fclose(f);
}

int main()
{
    int grille[6][7];
    char j1[20];
    char j2[20];

    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Bienvenue dans le super Puissance 4 ! (il est génial)\n");
    printf("-----------------------------------------------------\n\n");
    printf("1 - Nouvelle partie\n2 - Reprendre la partie\n Choix : ");
    int choix;
    do
    {
        scanf("%i", &choix);
    } while (choix < 1 || choix > 2);

    switch (choix)
    {
    case 1:
        initJeu(grille, j1, j2);
        break;

    default:
        load(grille, j1, j2);
        break;
    }
    afficherGrille(grille);

    while (1)
    {
        int col;
        printf("%s (X), c'est à toi ! dans quelle colonne veut tu mettre un pion ? : ", j1);
        scanf("%i", &col);
        while (placerPion(grille, 1, col) != 1)
        {
            scanf("%i", &col);
        }
        afficherGrille(grille);

        if (verifierGrille(grille) == 1)
        {
            printf("Bravo %s, c'est gagné !", j1);
            break;
        }

        printf("%s (O), c'est à toi ! dans quelle colonne veut tu mettre un pion ? : ", j2);
        scanf("%i", &col);
        while (placerPion(grille, 2, col) != 1)
        {
            scanf("%i", &col);
        }
        afficherGrille(grille);

        if (verifierGrille(grille) == 1)
        {
            printf("Bravo %s, c'est gagné !", j2);
            break;
        }
        if (verifierGrille(grille) == -1) //Verification du match nul seulement pour le joueur 2 car le joueur 1 ne peut pas remplir la grille
        {
            printf("Match nul !");
            break;
        }

        save(grille, j1, j2);
    }

    return 0;
}