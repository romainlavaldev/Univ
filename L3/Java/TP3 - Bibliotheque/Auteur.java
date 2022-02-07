/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 19 14:00:29 CET 2022
*
*/
public class Auteur{
	private String nom;
	private Date naissance;
	private Date deces;

	public Auteur(String nom, Date naissance){
		this.nom = nom;
		this.naissance = naissance;
	}
	
	public Auteur(String nom, Date naissance, Date deces){
		this.nom = nom;
		this.naissance = naissance;
		this.deces = deces;
	}

	public Date getNaissance(){
		return naissance;
	}

	public Date getDeces() throws NullPointerException{
		if (deces == null){
			throw new NullPointerException();
		}
		
		return deces;
	}

	public String getNom(){
		return nom;
	}

	@Override
	public String toString(){
		return nom + ", naissance : " + naissance + ", deces : " + deces; 
	}

	@Override
	public boolean equals(Object o){
		Auteur oAuteur;
		if (o instanceof Auteur){ 
			oAuteur = (Auteur)o;
		}
		else{
			throw new ClassCastException("Can't compare Auteur with a non-Auteur obj");
		}

		boolean sameDeces;
		if (this.deces == null){
			sameDeces = oAuteur.deces == null ? true:false;
		}else{
			sameDeces = this.deces.compareTo(oAuteur.deces) == 0;
		}

		return (
			this.nom == oAuteur.nom &&
			this.naissance.compareTo(oAuteur.naissance) == 0 &&
			sameDeces			
				);
	}
}