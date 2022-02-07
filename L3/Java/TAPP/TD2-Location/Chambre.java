/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Fri Jan 14 18:35:36 CET 2022
*
*/
public class Chambre implements Louable{
	private float prixLoc;
	private int numero;

	public Chambre(int num, float prixLoc){
		numero = num;
		this.prixLoc = prixLoc;
	}

	public float prixLocation(){
		return prixLoc;
	}

	public boolean peutEtreLoue(Personne loueur){
		return loueur.getAge() >= 18 && loueur.getSalaire() > 1000 && loueur.getSalaire() * 0.2 > prixLoc;
	}

	public String toString(){
		return ("Chambre : "+numero+" | Prix de location : "+prixLoc);
	}
}