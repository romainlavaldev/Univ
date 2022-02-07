/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:48:21 CET 2022
*
*/
public class Sphere extends ObjetGeometrique3D {
	private double r;


	public Sphere(double r){
		this.r = r;
	}

	public double surface(){
		return 4*3.14*r*r;
	}
	
    public double volume(){
    	return (4*3.14*r*r*r)/3;
    }

    public void agrandir(double facteur) throws IllegalZoomFactorException{
    	super.agrandir(facteur);
		r = r*facteur;
    }
    
	public void reduire(double facteur) throws IllegalZoomFactorException{
		super.reduire(facteur);
		r = r/facteur;
	}

	public String toString(){
		return "Sphere rayon:"+r;
	}
}