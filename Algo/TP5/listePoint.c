#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int valeur;
    struct element *pre;
    struct element *suc;
} t_element;

t_element *drapeau;
t_element *ec;

void initListe()
{
    drapeau = malloc(sizeof(t_element));
    drapeau->pre = drapeau;
    drapeau->suc = drapeau;
    ec = drapeau;
}

int listeVide()
{
    return (drapeau->pre == drapeau);
}

int horsListe()
{
    return (ec == drapeau);
}

void enTete()
{
    if (!listeVide())
        ec = drapeau->suc;
}

void enQueue()
{
    if (!listeVide())
        ec = drapeau->pre;
}

void suivant()
{
    if (!horsListe())
        ec = ec->suc;
}

void precedent()
{
    if (!horsListe())
        ec = ec->pre;
}

int valeurElt()
{
    if (!horsListe())
        return ec->valeur;
}

void modifElt(int v)
{
    if (!horsListe())
        ec->valeur = v;
}

void oterElt()
{
    if (!horsListe())
    {
        ec->pre->suc = ec->suc;
        ec->suc->pre = ec->pre;
        t_element *old = ec;
        ec = ec->pre;
        free(old);
    }
}

void ajoutDroit(int v)
{
    if (!horsListe() || listeVide())
    {
        t_element *nouv = malloc(sizeof(t_element));
        nouv->valeur = v;
        nouv->pre = ec;
        nouv->suc = ec->suc;
        ec->suc->pre = nouv;
        ec->suc = nouv;
        ec = nouv;
    }
}

void ajoutGauche(int v)
{
    if (!horsListe() || listeVide())
    {
        t_element *nouv = malloc(sizeof(t_element));
        nouv->valeur = v;
        nouv->pre = ec->pre;
        nouv->suc = ec;
        ec->pre->suc = nouv;
        ec->pre = nouv;
        ec = nouv;
    }
}