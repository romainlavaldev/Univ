// Mise en oeuvre d'une file d'entiers par pointeurs

#include <stdlib.h>

typedef struct element
{
    int nombre;
    struct element *suivant;
} t_element;

typedef struct
{
    t_element *tete;
    t_element *queue;
} t_file;

void initFile(t_file *f)
{
    f->tete = NULL;
    f->queue = NULL;
}

int fileVide(t_file f)
{
    return f.tete == NULL;
}

void ajouter(t_file *f, int v)
{
    t_element *nouv;

    nouv = malloc(sizeof(t_element));
    nouv->nombre = v;
    nouv->suivant = NULL;
    if (fileVide(*f))
        f->tete = nouv;
    else
        f->queue->suivant = nouv;
    f->queue = nouv;
}

int retirer(t_file *f)
{
    t_element *premier;

    if (!fileVide(*f))
    {
        premier = f->tete;
        int v = premier->nombre;
        f->tete = premier->suivant;
        free(premier);
        return v;
    }
    return -1;
}
