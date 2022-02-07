#include <stdio.h>
#include <ctype.h>
#include "pilePoint.h"

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
        }
    } while (charLu != '\n');

    int res = 22;
    depiler(&res);
    printf("resultat : %i", res);
    return 0;
}