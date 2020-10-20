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

void initFile(t_file *);
void ajouter(t_file *, int);
int retirer(t_file *);
int fileVide(t_file);
