/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Fri Jan 14 18:29:34 CET 2022
*
*/

public class Voiture implements Louable{
	private float prixLoc;
	private String modele;

	public Voiture(String modele, float prixLoc){
		this.modele = modele;
		this.prixLoc = prixLoc;
	}

	public float prixLocation(){
		return prixLoc;
	}

	public void setPrixLoc(float p){
		prixLoc = p;
	}

	public boolean peutEtreLoue(Personne loueur){
		return (loueur.hasPermis()) && (prixLoc <= loueur.getSalaire() / 2);
	}


	public String toString(){
		return ("Voiture : "+modele+" | Prix de location : "+prixLoc);
	}
}