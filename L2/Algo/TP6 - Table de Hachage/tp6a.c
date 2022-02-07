#include <stdio.h>
#include <stdlib.h>
#define N 10
#define VRAI 1
#define FAUX 0

int debog = VRAI; // mettre a faux apres debogage

// Declarations necessaires a la table
int table[N];

int hachage(int entier)
{
    return entier % N;
}

void initialiser(void)
{
    int i;
    for (i = 0; i < N; i++)
    {
        table[i] = -1;
    }
}

void ajouter(int entier)
{
    int i = hachage(entier);
    while (table[i] != -1)
    {
        i = (i + 1) % N;
    }
    table[i] = entier;
}

int est_present(int entier)
{
    int i = hachage(entier);
    while (table[i] != -1 && table[i] != entier)
    {
        i = (i + 1) % N;
    }

    return table[i] == entier;
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

    for (i = 0; i < N; i++)
        printf("table[%i] = %i\n", i, table[i]);
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

        // Lecture et verification du choix de l'utilisateur
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
