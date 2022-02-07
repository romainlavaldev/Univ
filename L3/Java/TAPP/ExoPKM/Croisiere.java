package pkm;


public class Croisiere extends Marin{
	public Croisiere(String nom, int poids, int nageoires){
		super(nom, poids, nageoires);
	}

	protected int vitesse(){
		return super.vitesse()/2;
	}
	
}