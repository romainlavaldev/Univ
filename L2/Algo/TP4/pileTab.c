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
