
//3-b
int main()
{
    char[20] nomFichier;
    printf("Quelle est le nom du fichier ?");
    scanf("%s", &nomFichier);
    FILE *fich = fopen(nomFichier, "r");

    int nbrLu;
    int somme = 0;
    fscanf(fich, "%i", &nbrLu);
    while (!feof(fich))
    {
        somme += nbrLu;
        fscanf(fich, "%i", &nbrLu);
    }
    fclose(fich);

    fich = fopen(nomFichier, "a");
    fprintf(fich, "%i ", somme);
    fclose(fich);
}

//Exo4
int main()
{
    printf("Donner les points marqués par Leia : ");
    int ptsLeia;
    scanf("%i", &ptsLeia);

    printf("Donner les points marqués par Luke : ");
    int ptsLuke;
    scanf("%i", &ptsLuke);

    FILE *fich = fopen("scores.txt", "r");

    if (fich != NULL)
    { //Affiche les anciens points et calcule les nouveaux score si le fichier existe
        int oldPtsLeia;
        int oldPtsLuke;

        fscanf(fich, "%i", &oldPtsLeia);
        fscanf(fich, "%i", &oldPtsLuke);

        printf("Les anciens scores sont : %i pour Leia, %i pour Luke.", oldPtsLeia, oldPtsLuke);
        ptsLeia += oldPtsLeia;
        ptsLuke += oldPtsLuke;
    }
    else
        printf("C'est votre première partie ! Les scores sont à 0.")
            fclose(fich);

    fich = fopen("score.txt", "w");
    printf("Les nouveaux scores sont : %i pour Leia, %i pour Luke.", &ptsLeia, &ptsLuke);

    fprintf("%i %i", ptsLeia, ptsLuke); //Sauvegarde des scores sous la forme "PtsLeia PtsLuke"
    fclose(fich);
}

//Exo5
//5-a
int main()
{
    char[20] nomFichier;
    printf("Nommez votre fichier !");
    scanf("%s", &nomFichier);

    int nbrChoisi;
    scanf("%i", &nbrChoisi);
    while (nbrChoisi <= 0)
        scanf("%i", &nbrChoisi);
    ;

    FILE *fich = fopen(nomFichier, "w");
    for (int i = 0; i < nbrChoisi; i++)
    {
        fprintf("%i ", rand());
    }
}

//5-b
int main()
{
    char[20] nomFichier;
    printf("Nommez votre fichier !");
    scanf("%s", &nomFichier);

    printf("Choisissez borne inf");
    int bInf;
    scanf("%i", &bInf);
    while (bInf < 0)
    {
        scanf("%i", &bInf);
    }

    printf("Choisissez borne supp");
    int bSupp;
    scanf("%i", &bSupp);
    while (bSupp <= bInf)
    {
        scanf("%i", &bSupp);
    }

    int nbrChoisi;
    scanf("%i", &nbrChoisi);
    while (nbrChoisi <= 0)
        scanf("%i", &nbrChoisi);
    ;

    FILE *fich = fopen(nomFichier, "w");
    for (int i = 0; i < nbrChoisi; i++)
    {
        fprintf("%i ", rand() % (bSupp - bInf) + bInf + 1);
    }
}

//5-Lecture
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fich;
    int N = 20;

    for (int i = 0; i < N; i++)
    {
        fich = fopen("lapin1.txt", "r");
        char charLu;
        fscanf(fich, "%c", &charLu);
        while (feof(fich))
        {
            printf(charLu);
            fscanf(fich, "%c", &charLu);
        }
        fclose(fich);
        sleep(1);
        system("clear");

        fich = fopen("lapin1.txt", "r");
        char charLu;
        fscanf(fich, "%c", &charLu);
        while (feof(fich))
        {
            printf(charLu);
            fscanf(fich, "%c", &charLu);
        }
        fclose(fich);
        sleep(1);
        system("clear");
    }
}