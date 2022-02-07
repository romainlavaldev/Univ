#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 5
#define VRAI 1
#define FAUX 0

int debog = VRAI; // mettre a faux apres debogage

// Declarations necessaires a la table
typedef struct
{
    int valeur;
    int suivant;
} doublet;
doublet table[N + M];
int libre = N;

int hachage(int entier)
{
    return entier % N;
}

void initialiser(void)
{
    doublet init = {-1, -1};
    int i;
    for (i = 0; i < N + M; i++)
    {
        table[i] = init;
    }
}

void ajouter(int entier)
{
    int i = hachage(entier);
    if (table[i].valeur == -1)
        table[i].valeur = entier;
    else if (libre < N + M)
    {
        table[libre].valeur = entier;
        table[libre].suivant = table[i].suivant;
        table[i].suivant = libre;
        libre++;
    }
    else
    {
        printf("Plus de place dans la table\n");
    }
}

int est_present(int entier)
{
    int i = hachage(entier);
    while (table[i].valeur != -1 && table[i].valeur != entier)
    {
        i = table[i].suivant;
    }
    return (table[i].valeur == entier);
}

void insertion(void)
{
    int nbr;
    printf("Que voulez vous ajouter ? : ");
    do
    {
        scanf("%i", &nbr);
    } while (nbr < 0);

    if (!est_present(nbr))
        ajouter(nbr);
    else
        printf("%i est déja dans la table !\n", nbr);
}

void recherche(void)
{
    int nbr;
    printf("Que voulez vous chercher ? : ");

    scanf("%i", &nbr);

    if (est_present(nbr))
        printf("%i est dans la table\n", nbr);
    else
        printf("%i n'est pas dans la table\n", nbr);
}

void afficher_table(void)
{
    int i;

    for (i = 0; i < N + M; i++)
        printf("table[%i] = %i  %i\n", i, table[i].valeur, table[i].suivant);
    printf("\n");
}

int main()
{
    int rep; // Choix de l'utilisateur [1-3]

    initialiser();

    do
    {
        printf("\n  Menu:\n");
        printf("1) Ajouter un element dans la table\n");
        printf("2) Rechercher un element dans la table\n");
        printf("3) Quitter\n\n");

        // Lecture et v�rification du choix de l'utilisateur
        do
        {
            printf("Votre choix [1-3] ? ");
            scanf("%d", &rep);
            if (rep < 1 || rep > 3)
                printf("Votre choix doit etre compris entre 1 et 3\n");
        } while (rep < 1 || rep > 3);

        // Traitement du choix de l'utilisateur
        switch (rep)
        {
        case 1:
            insertion();
            break;
        case 2:
            recherche();
            break;
        case 3:
        {
            printf("Au revoir!\n");
            break;
        }
        }

        if (debog)
            afficher_table();
    } while (rep != 3);

    return EXIT_SUCCESS;
}
