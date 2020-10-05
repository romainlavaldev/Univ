int fibo(int n)
{
    if (n == 0 || n == 1)
        return n;
    else
    {
        return fibo(n - 1) + fibo(n - 2);
    }
}

int suite[50];
int fibo2(int n)
{
    suite[0] = 0;
    suite[1] = 1;

    int i;
    for (i = 0; i < n; i++)
    {
        suite[i] = suite[i - 1] + suite[i - 2];
    }
    return suite[n];
}

int fibo3(int n)
{
    int i, v0, v1 = 1, v2 = 0;

    if (n == 0 || n == 1)
        return n;
    else
        for (i = 2; i < n; i++)
        {
            v0 = v1 + v2;
            v2 = v1;
            v1 = v0;
        }
    return v0;
}