int permuter(int T[], int i, int j)
{
}

int partition(int *T, int i_deb, int i_fin)
{
    int temp, i, j, pivot = T[i_deb];
    i = i_deb + 1;
    j = i_fin;

    while (i < j)
    {
        while (T[i] <= pivot)
            i++;
        while (T[j] > pivot)
            j++;
        if (i < j)
            permuter(T, i, j);
    }
    permuter(T, i_deb, j);
    return j;
}

int quicksort(int *T, int debut, int fin)
{
    int milieu;

    if (debut < fin)
    {
        milieu = partition(T, debut, fin);
        quicksort(T, debut, milieu - 1);
        quicksort(T, milieu + 1, fin);
    }
}