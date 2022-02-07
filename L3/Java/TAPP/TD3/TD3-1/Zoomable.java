/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:45:20 CET 2022
*
*/
public interface Zoomable{
	public void agrandir(double facteur) throws IllegalZoomFactorException;
	public void reduire(double facteur) throws IllegalZoomFactorException;
}