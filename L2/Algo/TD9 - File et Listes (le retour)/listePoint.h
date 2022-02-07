void initListe();
int listeVide();
int horsListe();
void enTete();
void enQueue();
void suivant();
void precedent();
int valeurElt();
void modifElt(int);
void oterElt();
void ajoutDroit(int);
void ajoutGauche(int);
typedef struct el
{
    int entier;
    struct el *pred;
    struct el *succ;
} t_element;

typedef struct
{
    t_element *drapeau;
    t_element *ec;
} t_liste;
