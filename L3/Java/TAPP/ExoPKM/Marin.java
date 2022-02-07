package pkm;

public class Marin extends Pokemon{
	protected int nageoires;

	public Marin(String nom, int poids, int nageoires){
		super(nom, poids);
		this.nageoires = nageoires;
	}

	protected int vitesse(){
		return nageoires*poids*2;
	}

	public String toString(){
		return super.toString() + String.format(", j'ai %d nageoires et je vais à %dkm/h", nageoires, vitesse());
	}
}