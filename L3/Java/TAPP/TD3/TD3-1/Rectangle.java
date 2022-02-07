/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:39:38 CET 2022
*
*/
public class Rectangle extends ObjetGeometrique2D{

	private double lon;
	private double lar;

	public Rectangle(double lon, double lar){
		this.lon = lon;
		this.lar = lar;
	}

	public double perimetre(){
		return 2*lon+2*lar;
	}

	public double surface(){
		return lon*lar;
	} 

	public String toString(){
		return "rect lon:"+lon+" lar:"+lar;
	}

	public void agrandir(double facteur) throws IllegalZoomFactorException{
		super.agrandir(facteur);
		lon = lon*facteur;
		lar = lar*facteur;
	}
	
	public void reduire(double facteur) throws IllegalZoomFactorException{
		super.reduire(facteur);
		lon = lon/facteur;
		lar = lar/facteur;
	}
}