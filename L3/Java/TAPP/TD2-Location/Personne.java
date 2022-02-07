/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Fri Jan 14 18:24:51 CET 2022
*
*/
public class Personne {
	private String nom;
	private int age;
	private int salaire;
	private boolean permis;

	public Personne(String nom, int age, int salaire, boolean permis){
		this.nom = nom;
		this.age = age;
		this.salaire = salaire;
		this.permis = permis;
	}

	public String getNom(){
		return nom;
	}
	
	public int getAge(){
		return age;
	}

	public int getSalaire(){
		return salaire;
	}

	public boolean hasPermis(){
		return permis;
	}
}