#include <stdio.h>
#include <stdlib.h>
#define N 10

int debog = 1; // mettre a faux apres deboguage

// Declarations necessaires a la table
typedef struct elem
{
    int valeur;
    struct elem *suivant;
} t_element;
t_element *table[N];

int hachage(int entier)
{
    return entier % N;
}

void initialiser(void)
{
    int i;
    for (i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

void ajouter(int entier)
{
    t_element *nouv;
    int i = hachage(entier);
    nouv = malloc(sizeof(t_element));
    nouv->suivant = table[i];
    nouv->valeur = entier;
    table[i] = nouv;
}

int est_present(int entier)
{
    int i;
    t_element *p;
    i = hachage(entier);
    p = table[i];
    while (p != NULL)
    {
        if (p->valeur == entier)
            return 1;
        p = p->suivant;
    }
    return 0;
}

void supprimer(int entier)
{
    int i = hachage(entier);
    t_element *p = table[i];
    if (est_present(entier))
    {
        while (p->suivant->valeur != entier)
        {
            p = p->suivant;
        }
        p->suivant = p->suivant->suivant;
    }
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
    t_element *p;

    for (i = 0; i < N; i++)
    {
        if (table[i] == NULL)
            printf("table[%i] est vide\n", i);
        else
        {
            p = table[i];
            printf("table[%i] contient :", i);
            while (p != NULL)
            {
                printf(" %i", p->valeur);
                p = p->suivant;
            }
            printf("\n");
        }
    }
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

        printf("3) Supprimer une valeur\n");
        printf("4) Quitter\n\n");

        // lecture et v�rification du choix de l'utilisateur
        do
        {
            printf("Votre choix [1-4] ? ");
            scanf("%d", &rep);
            if (rep < 1 || rep > 4)
                printf("Votre choix doit etre compris entre 1 et 4\n");
        } while (rep < 1 || rep > 4);

        // traitement du choix de l'utilisateur
        switch (rep)
        {
        case 1:
            insertion();
            break;
        case 2:
            recherche();
            break;
        case 4:
        {
            printf("Au revoir!\n");
            break;
        }
        case 3:
            printf("Quelle valeur suppr ? : ");
            int nbr;
            scanf("%i", &nbr);
            supprimer(nbr);
            break;
        }

        if (debog)
            afficher_table();
    } while (rep != 4);

    return EXIT_SUCCESS;
}
