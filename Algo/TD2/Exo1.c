#include <stdio.h>

typedef enum 
{
    As,Deux,Trois,Quatre,Cinq,Six,Sept,Huit,Neuf,Dix,Valet,Cavalier,Dame,Roi
} t_hauteur;

typedef enum 
{
    Carreau, Coeur, Trefle, Pique
} t_couleur;

typedef struct 
{
    t_hauteur hauteur;
    t_couleur couleur;
} t_carte;

typedef union
{
    int atout;
    t_carte carte;
} t_taro;



int main() {
    t_taro petit;
    petit.atout = 1;
    t_taro cavalierPique;
    cavalierPique.carte.couleur = Pique;
    cavalierPique.carte.hauteur = Cavalier;

    printf("Hauteur : %i", petit.atout);
    return 0;
}