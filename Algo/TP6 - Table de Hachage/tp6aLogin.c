#include <stdio.h>
#include <stdlib.h>
#define N 10

int debog = 1; // mettre a faux apres debogage

// Declarations necessaires a la table
char table[N][8];

int hachage(char login[])
{
    int r = 0, i;
    for (i = 0; i < 8; i++)
    {
        r += (int)login[i];
    }
    return r % N;
}

void initialiser(void)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < 8; j++)
        {
            table[i][j] = ' ';
        }
    }
}

void ajouter(char login[])
{
    int i = hachage(login);
    int j;
    while (table[i][0] != ' ')
    {
        i = (i + 1) % N;
    }
    for (j = 0; j < 8; j++)
    {
        table[i][j] = login[j];
    }
}

int est_present(char login[])
{
    int i = hachage(login);
    while (table[i] != login && table[i][0] != ' ')
    {
        i = (i + 1) % N;
    }

    return table[i] == login;
}

void insertion(void)
{
    char login[8];
    printf("Que voulez vous ajouter ? : ");
    do
    {
        scanf("%s", &login);
    } while (login[0] != ' ');

    if (!est_present(login))
        ajouter(login);
    else
        printf("%s est déja dans la table !\n", login);
}

void recherche(void)
{
    char login[8];
    printf("Que voulez vous chercher ? : ");

    scanf("%s", &login);

    if (est_present(login))
        printf("%s est dans la table\n", login);
    else
        printf("%s n'est pas dans la table\n", login);
}

void afficher_table(void)
{
    int i;

    for (i = 0; i < N; i++)
        printf("table[%i] = %s\n", i, table[i]);
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
