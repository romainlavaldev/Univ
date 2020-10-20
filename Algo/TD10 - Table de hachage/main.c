#include <stdio.h>
#include <stdlib.h>

#define N 50

int table[N];

int h(int x)
{
    return x % N;
}

void initialiser()
{
}

void ajouter(int n)
{
    table[h(n)] = n;
}

int estPresent(int n)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (table[i] == n)
            return 1;
    }
    return 0;
}

int main()
{
    return 0;
}