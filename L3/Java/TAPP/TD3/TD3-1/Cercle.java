/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:37:30 CET 2022
*
*/
public class Cercle extends ObjetGeometrique2D{
	private double r;
	
	public Cercle(double r){
		this.r = r;
	}

	public double perimetre(){
		return 2*3.14*r;
	}

	public double surface(){
		return 3.14*r*r;
	}

	public String toString(){
		return "Cercle rayon:"+r;
	}

	public void agrandir(double facteur) throws IllegalZoomFactorException{
		super.agrandir(facteur);
		r = r*facteur;
	}
	
	public void reduire(double facteur) throws IllegalZoomFactorException{
		super.reduire(facteur);
		r = r/facteur;
	}
}