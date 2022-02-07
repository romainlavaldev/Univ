/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 19 14:19:49 CET 2022
*
*/
public class Document {
	private Auteur auteur;
	private String titre;
	private boolean emprunte;

	public Document(Auteur auteur, String titre){
		this.auteur = auteur;
		this.titre = titre;
		emprunte = false;
	}

	public String getTitre(){
		return titre;
	}

	
	public void setEmprunte(boolean e){
		emprunte = e;
	}

	public boolean getEmprunte(){
		return emprunte;
	}

	public Auteur getAuteur(){
		return auteur;
	}
	
	@Override
	public String toString(){
		return titre + " par " + auteur.getNom();
	}

	@Override
	public boolean equals(Object o){
		Document oDocument;
		if (o instanceof Document){ 
			oDocument = (Document)o;
		}
		else{
			throw new ClassCastException("Can't compare Document with a non-Document obj");
		}

		return ( this.titre == oDocument.titre && this.auteur.equals(oDocument.auteur));
	}
}