#include <stdio.h>

void tailleFeuille(int *L, int *l, int n)
{
    if (n == 0)
    {
        *L = 1189;
        *l = 841;
        return;
    }

    tailleFeuille(l, L, n - 1);
    *l = *l / 2;
}

int main()
{
    int l = 0, L = 0;
    int format;
    printf("Choisissez un format (0-9) : ");
    scanf("%i", &format);

    tailleFeuille(&L, &l, format);

    printf("Une feuille A%i fait %i par %i", format, L, l);

    return 0;
}