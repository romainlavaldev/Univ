int puissance(int x, int n)
{
    if (n == 0)
        return 1;
    else
        return puissance(x, n - 1);
}

//b.
int puissanceRec(int x, int n, int res)
{
    if (n == 0)
    {
        return res;
    }
    else
    {
        return puissanceRec(x, n - 1, res * x);
    }
}

//c.
int puissanceIt(int x, int n)
{
    int res = 1;
    while (n != 0)
    {
        n--;
        res *= x;
    }
    return res;
}