// Mise en oeuvre par pointeurs de listes de fourmis

// Définition des types

typedef enum {rouge, noire} t_couleur;
typedef enum {reine, ouvriere} t_statut;
typedef enum {nord, est, sud, ouest} t_direction;
typedef struct {t_couleur couleur; t_statut statut; int x,y,energie,feuille,expe; t_direction dir;} t_fourmi;

typedef struct element {t_fourmi f; struct element* pred; struct element* succ;} t_element;
typedef struct {t_element* drapeau; t_element* ec;} t_liste;

typedef struct {int stock, presenceReine, naissance, deces;} t_etat;

// Primitives de listes 

void init_liste(t_liste *l);
int liste_vide(t_liste *l);
int hors_liste(t_liste *l);
void en_tete(t_liste *l);
void en_queue(t_liste *l);
void suivant(t_liste *l);
void precedent(t_liste *l);
void valeur_elt(t_liste *l, t_fourmi * f);
void modif_elt(t_liste *l, t_fourmi  f);
void oter_elt(t_liste *l);
void ajout_droit(t_liste *l, t_fourmi  f);
void ajout_gauche(t_liste *l, t_fourmi  f);
int taille(t_liste *l);
