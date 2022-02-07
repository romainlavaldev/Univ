package pkm;

public class Sportif extends Terrestre {
    private int fc;

    public Sportif(String nom, int poids, int pattes, int taille, int fc){
        super(nom, poids, pattes, taille);
        this.fc = fc;
    }
    
    public String toString(){
        return super.toString() + String.format("et j'ai une FC de %d BPM", fc);
    }
}
