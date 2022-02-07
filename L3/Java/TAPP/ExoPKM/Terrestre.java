package pkm;

abstract class Terrestre extends Pokemon{
    protected int pattes;
    protected int taille;

    protected Terrestre(String nom, int poids, int pattes, int taille){
        super(nom, poids);
        this.pattes = pattes;
        this.taille = taille;
    }

    private int vitesse() {
        return taille*pattes*2/poids;
    }

    public String toString() {
        return super.toString() + String.format("et j'ai %d pattes, je fais %dcm, je vais à %dkm/h ", pattes, taille, vitesse());
    }
    
}
