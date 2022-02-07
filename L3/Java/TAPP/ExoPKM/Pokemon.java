package pkm;

public abstract class Pokemon {
    private String nom;
    protected int poids;

    protected Pokemon(String nom, int poids){
        this.nom = nom;
        this.poids = poids;
    }

    public String toString() {
        return String.format("Je suis %s ", nom);
    }

    public static void testPKM(){
        System.out.println("TEST START");

        Pokemon pika = new Sportif("Pikachu", 15, 4, 80, 122);
        Pokemon ronflex = new Casanier("Ronflex", 480, 4, 240, 21);
        Pokemon poissirene = new Marin("Poissirène", 4, 3);
        Pokemon magicarpe = new Croisiere("Magicarpe", 4, 3);

        System.out.println(pika);
        System.out.println(ronflex);
        System.out.println(poissirene);
        System.out.println(magicarpe);

        System.out.println("TEST END");
    }
}