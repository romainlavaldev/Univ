#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "listesF.h"
#include "file.h"

#define VRAI 1
#define FAUX 0

#define DIMX 40 // Dimensions du plateau
#define DIMY 60

#define VIDE 0 // Codage des elements fixes du plateau
#define MARE -1
#define FEUILLE -2

#define PAUSE 100000	  // Duree de pause entre deux tours
#define SEUIL_PONTE 20	  // Seuil min d'energie de la reine
#define NB_MARES 50		  // Nombre de mares sur le plateau
#define NB_FEUILLES 20	  // Nombre initial de feuilles
#define PROBA_FEUILLE 100 // Proba de chute de feuille
#define PROBA_PONTE 10	  // Proba que la reine ponde
#define MAX_TOUR 20		  // Plafonne la duree de la partie

// La quantite initiale d'energie d'une fourmi
// est calculee en fonction de la taille du plateau
#define ENERGIE (DIMX + DIMY)

int possible(int x, int y, int P[DIMX][DIMY])
{
	// Vrai si une case est atteignable: sur plateau, hors mare
	return (x >= 0 && x < DIMX && y >= 0 && y < DIMY &&
			P[x][y] != MARE);
}

int libre(int x, int y, int P[DIMX][DIMY])
{
	// Vrai si une case est libre: sur plateau, ni mare ni feuille
	return (x >= 0 && x < DIMX && y >= 0 && y < DIMY &&
			P[x][y] != MARE && P[x][y] != FEUILLE);
}

void nouvelles_feuilles(int P[DIMX][DIMY])
{
	// Chute aleatoire d'une feuille
	// tous les PROBA_FEUILLE tours (en moyenne)

	int xfeuille, yfeuille;
	if (rand() % PROBA_FEUILLE == 0)
	{
		do
		{
			xfeuille = rand() % (DIMX - 3) + 1;
			yfeuille = rand() % (DIMY - 3) + 1;
		} while (!libre(xfeuille, yfeuille, P));
		P[xfeuille][yfeuille] = FEUILLE;
	}
}

void afficherPlateau(int P[DIMX][DIMY], t_liste *R, t_liste *N)
{
	// Affiche l'etat du plateau de jeu avec les fourmis
	// Attention: une case de lab = deux caracteres a l'ecran

	// Codage des differentes classes de fourmis
	// selon leur couleur, statut, XP, transport de feuille
	typedef enum
	{
		vide,
		reine_rouge,
		reine_noire,
		ouvriere_rouge,
		ouvriere_noire,
		rouge_feuille,
		noire_feuille,
		rougeXP,
		noireXP,
		rougeXPfeuille,
		noireXPfeuille
	} t_classe_fourmi;

	int i, j;
	t_fourmi fourmi;

	// Pause et effacement de l'ecran
	usleep(PAUSE);
	system("cls");

	// Placement des fourmis rouges
	en_queue(R);
	while (!hors_liste(R))
	{
		valeur_elt(R, &fourmi);
		if (fourmi.statut == reine)
			P[fourmi.x][fourmi.y] = reine_rouge;
		else if (!(fourmi.feuille) && !(fourmi.expe))
			P[fourmi.x][fourmi.y] = ouvriere_rouge;
		else if (fourmi.feuille && !(fourmi.expe))
			P[fourmi.x][fourmi.y] = rouge_feuille;
		else if (!(fourmi.feuille))
			P[fourmi.x][fourmi.y] = rougeXP;
		else
			P[fourmi.x][fourmi.y] = rougeXPfeuille;

		precedent(R);
	}

	// Placement des fourmis noires
	en_queue(N);
	while (!hors_liste(N))
	{
		valeur_elt(N, &fourmi);
		if (fourmi.statut == reine)
			P[fourmi.x][fourmi.y] = reine_noire;
		else if (!(fourmi.feuille) && !(fourmi.expe))
			P[fourmi.x][fourmi.y] = ouvriere_noire;
		else if (fourmi.feuille && !(fourmi.expe))
			P[fourmi.x][fourmi.y] = noire_feuille;
		else if (!(fourmi.feuille))
			P[fourmi.x][fourmi.y] = noireXP;
		else
			P[fourmi.x][fourmi.y] = noireXPfeuille;
		precedent(N);
	}

	// Affichage du plateau avec les fourmis

	for (j = 0; j <= 2 * (DIMY + 1); j++)
		printf("-");
	printf("\n");

	for (i = 0; i < DIMX; i++)
	{
		printf("| ");
		for (j = 0; j < DIMY; j++)
			switch (P[i][j])
			{
			case vide:
				printf("  ");
				break;
			case reine_rouge:
				printf("RR");
				break;
			case reine_noire:
				printf("RN");
				break;
			case ouvriere_rouge:
				printf("r ");
				break;
			case ouvriere_noire:
				printf("n ");
				break;
			case rouge_feuille:
				printf("r*");
				break;
			case noire_feuille:
				printf("*n");
				break;
			case rougeXP:
				printf("R ");
				break;
			case noireXP:
				printf("N ");
				break;
			case rougeXPfeuille:
				printf("R*");
				break;
			case noireXPfeuille:
				printf("*N");
				break;
			case MARE:
				printf("@@");
				break;
			case FEUILLE:
				printf("* ");
				break;
			default:
				printf("!!");
			}
		printf("|\n");
	}

	for (j = 0; j <= 2 * (DIMY + 1); j++)
		printf("-");
	printf("\n");
}

void afficherStats(t_liste *R, t_liste *N, t_etat etatR, t_etat etatN)
{
	// Affiche les statistiques des colonies en bas du plateau

	t_fourmi fourmi;

	printf("NOIRES\t\t\tROUGES\n");
	printf("Fourmis: %i\t\tFourmis: %i\n", taille(N), taille(R));

	if (etatN.presenceReine)
	{
		en_tete(N);
		valeur_elt(N, &fourmi);
		printf("Energie reine: %i", fourmi.energie);
	}
	else
		printf("Reine morte      ");

	if (etatR.presenceReine)
	{
		en_tete(R);
		valeur_elt(R, &fourmi);
		printf("\tEnergie reine: %i\n", fourmi.energie);
	}
	else
		printf("\tReine morte\n");

	printf("Stock: %i\t\tStock: %i\n", etatN.stock, etatR.stock);

	printf("Naissances: %i\t\tNaissances: %i\n", etatN.naissance, etatR.naissance);

	printf("Deces: %i\t\tDeces: %i\n", etatN.deces, etatR.deces);
}

void afficher(int P[DIMX][DIMY], t_liste *R, t_liste *N, t_etat etatR, t_etat etatN)
{
	// Affiche le plateau et les statistiques du jeu

	int M[DIMX][DIMY];
	int i, j;

	// Recopie les elements fixes du plateau
	// dans une lab intermediaire
	for (i = 0; i < DIMX; i++)
		for (j = 0; j < DIMY; j++)
			M[i][j] = P[i][j];

	// Ajoute les fourmis sur la lab intermediaire
	// et affiche cette lab puis les statistiques
	afficherPlateau(M, R, N);
	afficherStats(R, N, etatR, etatN);
}

void initialiser(int P[DIMX][DIMY], t_liste *rouges, t_liste *noires)
{
	// Initialise chaque colonie avec une reine
	// Initialise le plateau avec des mares et des feuilles
	// placees de maniere aleatoire

	int i, j, xMare, yMare, xfeuille, yfeuille;

	t_fourmi reineRouge =
		{rouge, reine, DIMX - 1, DIMY - 1, ENERGIE, FAUX, FAUX, nord};

	t_fourmi reineNoire =
		{noire, reine, 0, 0, ENERGIE, FAUX, FAUX, nord};

	init_liste(rouges);
	ajout_droit(rouges, reineRouge);

	init_liste(noires);
	ajout_droit(noires, reineNoire);

	srand(time(0));

	// Creation aleatoire de NB_MARES mares
	for (i = 1; i <= NB_MARES / 2; i++)
	{

		// Mare horizontale 2x8 a l'ecran
		xMare = rand() % (DIMX - 3) + 1;
		yMare = rand() % (DIMY - 9) + 1;
		for (j = 0; j < 4; j++)
		{
			P[xMare][yMare + j] = MARE;
			P[xMare + 1][yMare + j] = MARE;
		}

		// Mare verticale 4x4 a l'ecran
		xMare = rand() % (DIMX - 9) + 1;
		yMare = rand() % (DIMY - 3) + 1;
		for (j = 0; j < 4; j++)
		{
			P[xMare + j][yMare] = MARE;
			P[xMare + j][yMare + 1] = MARE;
		}
	}

	// Chute aleatoire de NB_FEUILLES feuilles
	// sur des cases libres
	for (i = 1; i <= NB_FEUILLES; i++)
	{
		do
		{
			xfeuille = rand() % (DIMX - 4) + 2;
			yfeuille = rand() % (DIMY - 4) + 2;
		} while (!libre(xfeuille, yfeuille, P));
		P[xfeuille][yfeuille] = FEUILLE;
	}
}

int feuilleProche(int P[DIMX][DIMY], int x, int y, int xp, int *nx, int *ny)
{
	// Vrai si la fourmi est proche d'une feuille
	// La fourmi detecte les feuilles
	// - a une case de distance, dans 8 directions
	// - et aussi a deux cases (dans 4 directions)
	//	si elle a de l'experience

	*nx = x;
	*ny = y;

	if (possible(x - 1, y, P) && P[x - 1][y] == FEUILLE)
		(*nx)--;
	else if (possible(x + 1, y, P) && P[x + 1][y] == FEUILLE)
		(*nx)++;
	else if (possible(x, y + 1, P) && P[x][y + 1] == FEUILLE)
		(*ny)++;
	else if (possible(x, y - 1, P) && P[x][y - 1] == FEUILLE)
		(*ny)--;
	else if (possible(x - 1, y - 1, P) && P[x - 1][y - 1] == FEUILLE)
	{
		(*nx)--;
		(*ny)--;
	}
	else if (possible(x + 1, y + 1, P) && P[x + 1][y + 1] == FEUILLE)
	{
		(*nx)++;
		(*ny)++;
	}
	else if (possible(x - 1, y + 1, P) && P[x - 1][y + 1] == FEUILLE)
	{
		(*nx)--;
		(*ny)++;
	}
	else if (possible(x + 1, y - 1, P) && P[x + 1][y - 1] == FEUILLE)
	{
		(*nx)++;
		(*ny)--;
	}
	else if (!xp)
		return FAUX;
	else
	{ // xp vrai
		if ((possible(x - 2, y, P) && P[x - 2][y] == FEUILLE))
			(*nx) = (*nx) - 2;

		else if ((possible(x + 2, y, P) && P[x + 2][y] == FEUILLE))
			(*nx) = (*nx) + 2;

		else if ((possible(x, y + 2, P) && P[x][y + 2] == FEUILLE))
			(*ny) = (*ny) + 2;

		else if ((possible(x, y - 2, P) && P[x][y - 2] == FEUILLE))
			(*ny) = (*ny) - 2;

		else
			return FAUX;
	}
	return VRAI;
}

void un_pas(t_direction dir, int x, int y, int *nx, int *ny)
{
	// Deplacement d'une case dans la direction dir
	// a partir de la position (x,y) pour aller en (nx,ny)
	*nx = x;
	*ny = y;
	switch (dir)
	{
	case nord:
		(*nx)--;
		break;
	case est:
		(*ny)++;
		break;
	case sud:
		(*nx)++;
		break;
	case ouest:
		(*ny)--;
		break;
	}
}

int est_dans_colonie(t_fourmi *f)
{
	// Vrai si la fourmi est dans sa propre colonie
	return ((f->couleur == rouge && f->x == DIMX - 1 && f->y == DIMY - 1) || (f->couleur == noire && f->x == 0 && f->y == 0));
}

int est_chez_adversaire(t_fourmi *f)
{
	// Vrai si la fourmi est dans la colonie adverse
	return ((f->couleur == noire && f->x == DIMX - 1 && f->y == DIMY - 1) || (f->couleur == rouge && f->x == 0 && f->y == 0));
}

void lignedroite(t_fourmi *f, int P[DIMX][DIMY])
{
	// Effectue un deplacement de la fourmi vers sa colonie
	int x, y, depl;

	if (f->couleur == rouge)
		depl = +1;
	else
		depl = -1;

	x = (f->x) * depl;
	y = (f->y) * depl;

	if (x < y)
	{
		if (possible(depl + f->x, f->y, P))
			(f->x) += depl;
		else if (possible(f->x, depl + f->y, P))
			(f->y) += depl;
		else if (possible(depl + f->x, depl + f->y, P))
		{
			(f->x) += depl;
			(f->y) += depl;
		}
		else if (possible(f->x, depl - f->y, P))
			(f->y) -= depl;
		else if (possible(depl - f->x, f->y, P))
			(f->x) -= depl;
	}
	else
	{ // x<y
		if (possible(f->x, depl + f->y, P))
			(f->y) += depl;
		else if (possible(depl + f->x, f->y, P))
			(f->x) += depl;
		else if (possible(depl + f->x, depl + f->y, P))
		{
			(f->x) += depl;
			(f->y) += depl;
		}
		else if (possible(depl - f->x, f->y, P))
			(f->x) -= depl;
		else if (possible(f->x, depl - f->y, P))
			(f->y) -= depl;
	}
}

int estVide(int matrice[DIMX][DIMY], int x, int y)
{
	return (possible(x, y, matrice) && (matrice[y][x] == 0));
}

void plus_court(int lab[DIMX][DIMY], int xd, int yd, int xa, int ya, int *x1, int *y1)
{
	initFile();
	int marqueur = 1;
	int trouve = 0;
	lab[yd][xd] = marqueur;
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
			marqueur = lab[yc][xc];
			int j = xc, i = yc;
			if (possible(j, i - 1, lab) && estVide(lab, j, i - 1))
			{
				lab[i - 1][j] = marqueur + 1;
				ajouter(i - 1);
				ajouter(j);
			}
			if (possible(j, i + 1, lab) && estVide(lab, j, i + 1))
			{
				lab[i + 1][j] = marqueur + 1;
				ajouter(i + 1);
				ajouter(j);
			}
			if (possible(j - 1, i, lab) && estVide(lab, j - 1, i))
			{
				lab[i][j - 1] = marqueur + 1;
				ajouter(i);
				ajouter(j - 1);
			}
			if (possible(j + 1, i, lab) && estVide(lab, j + 1, i))
			{
				lab[i][j + 1] = marqueur + 1;
				ajouter(i);
				ajouter(j + 1);
			}
		}
	}
}

int evolution(t_fourmi *f, int P[DIMX][DIMY], t_etat *etat)
{
	// Calcule l'evolution de la fourmi f puis modifie
	// les champs de la structure f selon cette evolution
	// Met a jour l'etat du jeu si necessaire
	// Renvoie evol qui vaut:
	//     -1 si la fourmi meurt
	//     +1 si la fourmi est une reine et qu'elle pond
	//     0 sinon

	int alea, evol = 0;
	int nouvx, nouvy;

	if (f->statut == ouvriere)
	{

		// la fourmi commence par se deplacer

		// Cas 1: il y a une feuille sur une case voisine
		// et elle n'en transporte pas deja, elle y va
		if (!(f->feuille) && feuilleProche(P, f->x, f->y, f->expe, &nouvx, &nouvy))
		{
			f->x = nouvx;
			f->y = nouvy;
		}
		else if (!(f->feuille))
		{
			// Cas 2: la fourmi cherche une feuille
			// en se deplacant de maniere aleatoire

			// une fois sur cinq, elle change de direction
			alea = rand() % 10;
			if (alea == 0)
				f->dir = (f->dir + 1) % 4; // Tourne a droite
			else if (alea == 1)
				f->dir = (f->dir + 3) % 4; // Tourne a gauche

			un_pas(f->dir, f->x, f->y, &nouvx, &nouvy);

			// tant qu'elle est bloquee par un obstacle
			// elle essaye de tourner pour l'eviter
			while (!possible(nouvx, nouvy, P))
			{
				alea = rand() % 2;
				if (alea == 0)
					f->dir = (f->dir + 1) % 4;
				else if (alea == 1)
					f->dir = (f->dir + 3) % 4;
				un_pas(f->dir, f->x, f->y, &nouvx, &nouvy);
			}

			// le deplacement est possible:
			// les coord. de la fourmi sont modifiees
			f->x = nouvx;
			f->y = nouvy;

			// le deplacement coute un point d'energie
			(f->energie)--;
		}
		else
		{
			// Cas 3: la fourmi revient a la colonie
			// au plus vite, avec la feuille qu'elle a trouvee

			// Version "recherche du chemin le plus court"
			/*
			if(f->couleur==rouge)
				plus_court(P,f->x,f->y,DIMX-1,DIMY-1,&nouvx,&nouvy);
			else
				plus_court(P,f->x,f->y,0,0,&nouvx,&nouvy);

			f->x = nouvx;
			f->y = nouvy;
*/
			// Fin de la version "recherche du chemin le plus court"

			// Version "chemin en ligne droite"
			lignedroite(f, P);
			// Fin de la version "chemin en ligne droite"

			// le deplacement coute de l'energie:
			// un point si elle ne transporte rien
			// deux points si elle est chargee
			if (!f->feuille)
				(f->energie) -= 1;
			else
				(f->energie) -= 2;
		}

		// apres le deplacement de la fourmi

		if (est_dans_colonie(f) && f->feuille)
		{
			// la fourmi est de retour avec une feuille:
			// elle l'ajoute au stock de la colonie
			// elle reprend des forces
			// elle a acquis de l'experience
			f->feuille = FAUX;
			(etat->stock) += (9 * ENERGIE) / 10;
			f->energie = ENERGIE * 4;
			f->expe = VRAI;
		}
		else if (est_chez_adversaire(f) || f->energie <= 0)
		{
			// si la fourmi arrive dans la colonie adverse
			// ou si elle n'a plus d'energie
			// l'issue est fatale
			evol = -1;
			(etat->deces)++;

			// la feuille transportee est abandonnee
			if (f->feuille)
				P[f->x][f->y] = FEUILLE;
		}
		else if (!(f->feuille) && P[f->x][f->y] == FEUILLE)
		{
			// la fourmi a trouve une feuille:
			// elle s'en empare pour la ramener a la colonie
			f->feuille = VRAI;
			P[f->x][f->y] = VIDE;
		}
	}
	else
	{ // la fourmi est une reine

		// Son metabolisme consomme un point d'energie
		if (f->energie > 0)
			(f->energie)--;

		// Si la reine a assez d'energie, elle peut pondre
		if (f->energie > SEUIL_PONTE)
		{
			alea = rand() % PROBA_PONTE;
			if (alea == 0)
			{
				evol = 1; // Naissance d'une fourmi
				(etat->naissance)++;
			}
		}

		// Si la reine n'a plus du tout d'energie
		if (f->energie <= 0)
			// s'il reste de la nourriture, elle mange
			// la moitie du stock de la colonie
			if ((etat->stock) > 0)
			{
				f->energie = (etat->stock + 1) / 2;
				(etat->stock) -= (etat->stock + 1) / 2;
			}
			// sinon, elle meurt
			else
			{
				evol = -1;
				(etat->presenceReine) = FAUX;
			}
	}
	return evol;
}

void miseAjour(int P[DIMX][DIMY], t_couleur coul, t_liste *colonie, t_etat *etat)
{
	// Met a jour les fourmis de la colonie de couleur coul

	t_fourmi fourmi; // Element courant de la liste

	int evol; // Valeur d'evolution de la fourmi

	t_fourmi ouvriereRouge =
		{rouge, ouvriere, DIMX - 2, DIMY - 2, ENERGIE, FAUX, FAUX, ouest};

	t_fourmi ouvriereNoire =
		{noire, ouvriere, 1, 1, ENERGIE, FAUX, FAUX, est};

	// A FAIRE: ecrire le corps de la fonction
	en_tete(colonie);
	while (!hors_liste(colonie))
	{
		switch (evolution(&fourmi, P, etat))
		{
		case -1:
			oter_elt(colonie);
			break;
		case 1:
			if (coul == rouge)
				ajout_droit(colonie, ouvriereRouge);
			else
				ajout_droit(colonie, ouvriereNoire);
			break;
		default:
			break;
		}
	}
}

int main(void)
{

	int plateau[DIMX][DIMY] = {{VIDE}}; // Plateau de jeu
	t_liste rouges;						// Fourmis rouges
	t_liste noires;						// Fourmis noires
	t_etat etatR = {100, VRAI, 0, 0};	// Etat colonie R
	t_etat etatN = {100, VRAI, 0, 0};	// Etat colonie N
	int tour = 0;						// Nb tours de jeu

	initialiser(plateau, &rouges, &noires);

	afficher(plateau, &rouges, &noires, etatR, etatN);

	// Evolution jusqu'a disparition d'une colonie
	while (!liste_vide(&noires) && !liste_vide(&rouges))
	{

		miseAjour(plateau, rouge, &rouges, &etatR);
		miseAjour(plateau, noire, &noires, &etatN);
		nouvelles_feuilles(plateau);

		afficher(plateau, &rouges, &noires, etatR, etatN);

		tour++;

		// Pour interrompre la partie apres MAX-TOUR tours
		if (tour >= MAX_TOUR)
			break;
	}

	// Une colonie gagne si sa reine est toujours vivante
	// alors que l'autre colonie a entierement trepasse

	if (liste_vide(&rouges) && etatN.presenceReine)
		printf("\nLes noires gagnent en %i tours\n", tour);
	else if (liste_vide(&noires) && etatR.presenceReine)
		printf("\nLes rouges gagnent en %i tours\n", tour);
	else if (tour == MAX_TOUR)
	{
		printf("Partie stoppee au bout de %i tours\n", tour);
		printf("(modifier la variable MAX_TOUR pour changer ce seuil)\n");
	}
	else // les deux reines sont mortes
		printf("C'est l'apocalypse: pas de gagnant\n");

	return EXIT_SUCCESS;
}
