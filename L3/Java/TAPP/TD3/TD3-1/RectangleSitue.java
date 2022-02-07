/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 14:01:02 CET 2022
*
*/
public class RectangleSitue extends ObjetGeometrique2DSitue{
	private double lon;
	private double lar;
	private double x;
	private double y;

	public RectangleSitue(double lon, double lar, double x, double y){
		this.lon = lon;
		this.lar = lar;
		this.x = x;
		this.y = y;
	}

	public double perimetre(){
		return 2*lon+2*lar;
	}

	public double surface(){
		return lon*lar;
	} 

	public String toString(){
		return "rect lon:"+lon+" lar:"+lar+"("+x+";"+y+")";
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