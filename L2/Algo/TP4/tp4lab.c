// TP4 - Recherche du chemin le plus court avec une file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "file.h"
#include "pilepoint.h"
#define VRAI 1
#define FAUX 0
#define N 25
#define M 55
#define COULOIR 0
#define MUR -1
#define CHEMIN -2

void afficher_lab(int lab[N][M])
{
	// Affiche le labyrintheint i, j;
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (lab[i][j] == -1)
				printf("@ ");
			else if (lab[i][j] == -2)
			{
				printf(". ");
			}
			else
				printf("  ");
		}
		printf("%c", '\n');
	}
}

void init_lab(int lab[N][M])
{
	//Initialise le labyrinthe avec des murs
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			lab[i][j] = MUR;
}

//******************************
// Partie cr�ation du labyrinthe
//******************************

int valides(int i, int j)
{
	// renvoie VRAI si i et j d�signent une case de la matrice
	return (i >= 0 && i < N && j >= 0 && j < M);
}

int est_vide(int i, int j, int lab[N][M])
{
	// renvoie VRAI si i et j d�signent une case couloir
	return (valides(i, j) && lab[i][j] == COULOIR);
}

int est_mur(int i, int j, int lab[N][M])
{
	// renvoie VRAI si i et j d�signent une case mur
	return (valides(i, j) && lab[i][j] == MUR);
}

int blocage(int i, int j, int lab[N][M])
{
	// renvoie VRAI si aucune case voisine n'est un mur
	return (!est_mur(i + 2, j, lab) && !est_mur(i - 2, j, lab) && !est_mur(i, j + 2, lab) && !est_mur(i, j - 2, lab));
}

int creer_lab(int lab[N][M])
{
	// Cree le labyrinthe de maniere aleatoire avec une pile

	int termine = FAUX;
	int trouve = FAUX;
	int i, j, alea;

	init_lab(lab);
	initPile();

	i = 0,
	j = 0;
	lab[0][0] = COULOIR;

	while (!termine)
	{

		if (blocage(i, j, lab))
		{
			if (!pileVide())
			{
				depiler(&j);
				depiler(&i);
			}
			else
				termine = VRAI;
		}
		else
		{
			trouve = FAUX;
			while (!trouve)
			{
				alea = rand() % 4;
				switch (alea)
				{
				case 0:
					if (est_mur(i + 2, j, lab))
					{
						empiler(i);
						empiler(j);
						lab[i + 1][j] = COULOIR;
						lab[i + 2][j] = COULOIR;
						i = i + 2;
						trouve = VRAI;
						break;
					}
				case 1:
					if (est_mur(i - 2, j, lab))
					{
						empiler(i);
						empiler(j);
						lab[i - 1][j] = COULOIR;
						lab[i - 2][j] = COULOIR;
						i = i - 2;
						trouve = VRAI;
						break;
					}
				case 2:
					if (est_mur(i, j + 2, lab))
					{
						empiler(i);
						empiler(j);
						lab[i][j + 1] = COULOIR;
						lab[i][j + 2] = COULOIR;
						j = j + 2;
						trouve = VRAI;
						break;
					}
				case 3:
					if (est_mur(i, j - 2, lab))
					{
						empiler(i);
						empiler(j);
						lab[i][j - 1] = COULOIR;
						lab[i][j - 2] = COULOIR;
						j = j - 2;
						trouve = VRAI;
					}
				}
			}
		}
	}
}

//***************************
// Partie recherche de chemin
//***************************
int valide(int x, int y)
{
	return ((x < M && x >= 0) && (y < N && y >= 0));
}

int estVide(int matrice[N][M], int x, int y)
{
	return (valide(x, y) && (matrice[y][x] == 0));
}

int chercher_chemin(int matrice[N][M], int xd, int yd, int xa, int ya)
{
	initFile();
	int marqueur = 1;
	int trouve = 0;
	matrice[yd][xd] = marqueur;
	ajouter(yd);
	ajouter(xd);

	int yc, xc;
	while (!fileVide())
	{

		retirer(&yc);
		retirer(&xc);
		if (yc == ya && xc == xa)
		{
			trouve = 1;
		}
		else
		{
			marqueur = matrice[yc][xc];
			int j = xc, i = yc;
			if (valide(j, i - 1) && estVide(matrice, j, i - 1))
			{
				matrice[i - 1][j] = marqueur + 1;
				ajouter(i - 1);
				ajouter(j);
			}
			if (valide(j, i + 1) && estVide(matrice, j, i + 1))
			{
				matrice[i + 1][j] = marqueur + 1;
				ajouter(i + 1);
				ajouter(j);
			}
			if (valide(j - 1, i) && estVide(matrice, j - 1, i))
			{
				matrice[i][j - 1] = marqueur + 1;
				ajouter(i);
				ajouter(j - 1);
			}
			if (valide(j + 1, i) && estVide(matrice, j + 1, i))
			{
				matrice[i][j + 1] = marqueur + 1;
				ajouter(i);
				ajouter(j + 1);
			}
		}
	}

	return trouve;
}

void marquer_chemin(int matrice[N][M], int xa, int ya, int *lgmin)
{
	// Marque le chemin le plus court a partir de lab[x][y]
	// Renvoie sa taille dans lgmin
	while (matrice[ya][xa] != 1)
	{
		sleep(0.8);
		system("cls");
		afficher_lab(matrice);
		if (valide(xa, ya - 1) && matrice[ya - 1][xa] == matrice[ya][xa] - 1)
		{
			matrice[ya][xa] = -2;
			xa = xa;
			ya = ya - 1;
		}
		else if (valide(xa, ya + 1) && matrice[ya + 1][xa] == matrice[ya][xa] - 1)
		{
			matrice[ya][xa] = -2;
			xa = xa;
			ya = ya + 1;
		}
		else if (valide(xa - 1, ya) && matrice[ya][xa - 1] == matrice[ya][xa] - 1)
		{
			matrice[ya][xa] = -2;
			xa = xa - 1;
			ya = ya;
		}
		else if (valide(xa + 1, ya) && matrice[ya][xa + 1] == matrice[ya][xa] - 1)
		{
			matrice[ya][xa] = -2;
			xa = xa + 1;
			ya = ya;
		}
		*lgmin = *lgmin + 1;
	}
	matrice[ya][xa] = -2;
}

void nettoyer(int lab[N][M])
{
	// Nettoyage des couloirs (facultatif pour ce TP)
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (lab[i][j] > 0)
				lab[i][j] = 0;
		}
	}
}

//****************************************************
// Programme principal
// Cree le labyrinthe, cherche le chemin et l'affiche
//****************************************************

int main()
{
	int labyrinthe[N][M];
	int lgmin = 0;

	srand(time(0));

	creer_lab(labyrinthe);
	afficher_lab(labyrinthe);

	chercher_chemin(labyrinthe, M - 1, N - 1, 0, 0);

	marquer_chemin(labyrinthe, 0, 0, &lgmin);
	system("cls");
	afficher_lab(labyrinthe);

	printf("Chemin le plus court de longueur %i\n", lgmin);
	nettoyer(labyrinthe);
	system("pause");
}