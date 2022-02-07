/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:48:09 CET 2022
*
*/
public class Cylindre extends ObjetGeometrique3D{
	private double r;
	private double h;

	public Cylindre(double r, double h){
		this.r = r;
		this.h = h;
	}

	public double surface(){
		return 2*3.14*r*h;
	}
	
    public double volume(){
    	return 3.14*r*r*h;
    }

    public void agrandir(double facteur) throws IllegalZoomFactorException{
    	super.agrandir(facteur);
		r = r*facteur;
		h = h*facteur;
    }
    
	public void reduire(double facteur) throws IllegalZoomFactorException{
		super.reduire(facteur);
		r = r/facteur;
		h = h/facteur;
	}
	
	public String toString(){
		return "Cylindre r:"+r+" h:"+h;
	}
}