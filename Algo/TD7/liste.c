// Mise en oeuvre contigue d'une liste d'entiers
#define TAILLE_MAX 100
#include <stdio.h>

// Declaration du tableau contenant les elements de liste
int liste[TAILLE_MAX];
// Declaration des indices de queue et d'element courant
int queue, ec;

void initListe(void)
{
    // Initialise la liste a vide

    queue = -1;
    ec = -1;
}

int listeVide(void)
{
    // Rend vrai si la liste est vide, faux sinon

    return (queue == -1);
}

int horsListe(void)
{
    // Rend vrai si l'elt courant est hors de la liste, faux sinon

    return (ec < 0 || ec > queue);
}

void enTete(void)
{
    // Positionne en tete de la liste

    if (!listeVide())
        ec = 0;
}

void enQueue(void)
{
    // Positionne en queue de la liste

    if (!listeVide())
        ec = queue;
}

void precedent(void)
{
    // Positionne sur l'elt precedent

    if (!horsListe())
        ec--;
}

void suivant(void)
{
    // Positionne sur l'elt suivant

    if (!horsListe())
        ec++;
}

int valeurElt()
{
    // Renvoie dans v la valeur de l'elt courant

    if (!horsListe())
        return liste[ec];
}

void modifElt(int v)
{
    // Affecte v a l'elt courant

    if (!horsListe())
        liste[ec] = v;
}

void oterElt(void)
{
    // Supprime l'elt courant et positionne sur le precedent

    int i;
    if (!horsListe())
    {
        for (i = ec; i < queue; i++)
            liste[i] = liste[i + 1];
        ec--;
        queue--;
    }
}

void ajoutDroit(int v)
{
    // Ajoute v a droite de l'elt courant

    int i;

    if (listeVide() || !horsListe())
    {
        for (i = queue; i > ec; i--)
            liste[i + 1] = liste[i];
        liste[ec + 1] = v;
        ec++;
        queue++;
    }
}

void ajoutGauche(int v)
{
    // Ajoute v a gauche de l'elt courant

    int i;

    if (listeVide())
        ec++;

    if (listeVide() || !horsListe())
    {
        for (i = queue; i >= ec; i--)
            liste[i + 1] = liste[i];
        liste[ec] = v;
        queue++;
    }
}