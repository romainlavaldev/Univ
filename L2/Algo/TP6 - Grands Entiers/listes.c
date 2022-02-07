// Mise en oeuvre dynamique d'un tableau de listes d'entiers

#define MAX_LISTE 11
#include <stdio.h>
#include <stdlib.h>

// Definition du type d'un element de liste
typedef struct element
{
    int valeur;
    struct element *pred;
    struct element *succ;
} t_element;

// Declaration des listes (drapeau et element courant)
t_element *drapeau[MAX_LISTE];
t_element *ec[MAX_LISTE];

// Primitives de manipulation des listes

void init_liste(int n)
{
    if (n > 0 && n < MAX_LISTE)
    {
        drapeau[n] = malloc(sizeof(t_element));
        drapeau[n]->pred = drapeau[n];
        drapeau[n]->succ = drapeau[n];
        ec[n] = drapeau[n];
    }
}

int liste_vide(int n)
{
    if (n > 0 && n < MAX_LISTE)
        return drapeau[n]->pred == drapeau[n];
}

int hors_liste(int n)
{
    if (n > 0 && n < MAX_LISTE)
        return ec[n] == drapeau[n];
}

void en_tete(int n)
{
    if (n > 0 && n < MAX_LISTE)
        if (!liste_vide(n))
            ec[n] = drapeau[n]->succ;
}

void en_queue(int n)
{
    if (n > 0 && n < MAX_LISTE)
        if (!liste_vide(n))
            ec[n] = drapeau[n]->pred;
}

void precedent(int n)
{
    if (n > 0 && n < MAX_LISTE)
        if (!hors_liste(n))
            ec[n] = ec[n]->pred;
}

void suivant(int n)
{
    if (n > 0 && n < MAX_LISTE)
        if (!hors_liste(n))
            ec[n] = ec[n]->succ;
}

void valeur_elt(int n, int *v)
{
    if (n > 0 && n < MAX_LISTE)
        if (!hors_liste(n))
            *v = ec[n]->valeur;
}

void modif_elt(int n, int v)
{
    if (n > 0 && n < MAX_LISTE)
        if (!hors_liste(n))
            ec[n]->valeur = v;
}

void oter_elt(int n)
{
    t_element *temp;

    if (n > 0 && n < MAX_LISTE)
        if (!hors_liste(n))
        {
            (ec[n]->succ)->pred = ec[n]->pred;
            (ec[n]->pred)->succ = ec[n]->succ;
            temp = ec[n];
            ec[n] = ec[n]->pred;
            free(temp);
        }
}

void ajout_droit(int n, int v)
{
    t_element *nouv;

    if (n > 0 && n < MAX_LISTE)
        if (liste_vide(n) || !hors_liste(n))
        {
            nouv = malloc(sizeof(t_element));
            nouv->valeur = v;
            nouv->pred = ec[n];
            nouv->succ = ec[n]->succ;
            (ec[n]->succ)->pred = nouv;
            ec[n]->succ = nouv;
            ec[n] = nouv;
        }
}

void ajout_gauche(int n, int v)
{
    t_element *nouv;

    if (n > 0 && n < MAX_LISTE)
        if (liste_vide(n) || !hors_liste(n))
        {
            nouv = malloc(sizeof(t_element));
            nouv->valeur = v;
            nouv->succ = ec[n];
            nouv->pred = ec[n]->pred;
            (ec[n]->pred)->succ = nouv;
            ec[n]->pred = nouv;
            ec[n] = nouv;
        }
}
