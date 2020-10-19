// Mise en oeuvre d'une file d'entiers par pointeurs

#include <stdlib.h>

typedef struct element
{
    int nombre;
    struct element *suivant;
} t_element;
t_element *tete;
t_element *queue;

void initFile(void)
{
    tete = NULL;
    queue = NULL;
}

int fileVide(void)
{
    return tete == NULL;
}

void ajouter(int v)
{
    t_element *nouv;

    nouv = malloc(sizeof(t_element));
    nouv->nombre = v;
    nouv->suivant = NULL;
    if (fileVide())
        tete = nouv;
    else
        queue->suivant = nouv;
    queue = nouv;
}

void retirer(int *v)
{
    t_element *premier;

    if (!fileVide())
    {
        premier = tete;
        *v = premier->nombre;
        tete = premier->suivant;
        free(premier);
    }
}
