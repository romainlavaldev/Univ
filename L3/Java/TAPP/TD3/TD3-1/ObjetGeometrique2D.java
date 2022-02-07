/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:36:22 CET 2022
*
*/
public abstract class ObjetGeometrique2D implements Zoomable{
	public abstract double perimetre();
	public abstract double surface();

	public void agrandir(double facteur)  throws IllegalZoomFactorException {
		if (facteur <= 0){
			throw new IllegalZoomFactorException("Impossible d'agrandir par "+facteur);
		}
	}
	
	public void reduire(double facteur) throws IllegalZoomFactorException {
		if (facteur <= 0){
			throw new IllegalZoomFactorException("Impossible de reduire par "+facteur);
		}
	}
}