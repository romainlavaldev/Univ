#include <stdio.h>

int fibo(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    printf("%i  - ", n);
    return fibo(n - 1) + fibo(n - 2);
}

int fiboIt(int n)
{
    int res;
    int res1 = 1;
    int res2 = 0;
    int i;
    for (i = 2; i <= n; i++)
    {
        printf("%i - ", i);
        res = res1 + res2;
        res2 = res1;
        res1 = res;
    }
    return res;
}

int main()
{

    int nbr;
    scanf("%i", &nbr);
    printf("\n\n%i", fibo(nbr));

    return 0;
}