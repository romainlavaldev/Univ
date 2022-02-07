package pkm;


public class Casanier extends Terrestre{
	private int tempsTV;

	public Casanier(String nom, int poids, int pattes, int taille, int tempsTV){
		super(nom, poids, pattes, taille);
		this.tempsTV = tempsTV;
	}

	public String toString(){
		return super.toString() + String.format("et je passe %dh devant la télé", tempsTV);
	}
}