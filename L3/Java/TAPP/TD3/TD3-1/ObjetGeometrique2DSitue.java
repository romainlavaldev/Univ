/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:55:35 CET 2022
*
*/
public abstract class ObjetGeometrique2DSitue extends ObjetGeometrique2D implements Mobile{
	private double x;
	private double y;
	
	public void deplacerHorizontalement(double dep){
		this.x = x+dep;
	}
	
	public void deplacerVerticalement(double dep){
		this.y = y+dep;
	}
}