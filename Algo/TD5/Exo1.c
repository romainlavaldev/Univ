#include <stdio.h>
#include <ctype.h>

//PILE
#define t_max 50
int pile[t_max];
int sommet;

void initPile()
{
    sommet = -1;
}

void empiler(int i)
{
    if (sommet < t_max - 1)
    {
        sommet++;
        pile[sommet] = i;
    }
}

void depiler(int *i)
{
    if (sommet > -1)
    {
        *i = pile[sommet];
        sommet--;
    }
}

int pileVide()
{
    return (sommet == -1);
}
//PILE

int convertir(char c)
{
    return (int)(c - '0');
}

void traiterVcour(char c)
{
    int nbLu;

    if (isdigit(c))
    {
        nbLu = convertir(c);
        empiler(nbLu);
    }
    else
    {
        int nb1, nb2;
        depiler(&nb2);
        depiler(&nb1);
        switch (c)
        {
        case '+':
            empiler(nb1 + nb2);
            break;
        case '-':
            empiler(nb1 - nb2);
            break;
        case '*':
            empiler(nb1 * nb2);
            break;
        case '/':
            empiler(nb1 / nb2);
            break;
        }
    }
}

int main()
{
    initPile();
    char charLu;
    do
    {
        scanf("%c", &charLu);
        if (charLu != '\n')
        {
            traiterVcour(charLu);
            printf("%i", sommet);
        }
    } while (charLu != '\n');

    int res = 22;
    depiler(&res);
    printf("resultat : %i", res);
    return 0;
}