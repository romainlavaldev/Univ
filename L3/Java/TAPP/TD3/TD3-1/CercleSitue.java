/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:57:40 CET 2022
*
*/
public class CercleSitue extends ObjetGeometrique2DSitue{

	private double r;
	private double x;
	private double y;
	
	public CercleSitue(double r, double x, double y){
		this.r = r;
		this.x = x;
		this.y = y;
	}

	public double perimetre(){
		return 2*3.14*r;
	}

	public double surface(){
		return 3.14*r*r;
	}

	public String toString(){
		return "CercleSitue rayon:"+r+" ("+x+";"+y+")";
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