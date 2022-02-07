/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Jan 11 09:08:21 CET 2022
*
*/
import java.lang.Math;

public class Point {
	/**
	 * Class point
	 * 
	 * @param x
	 * @param y
	 */
	private double x;
	private double y;


	//Constructors
	/**
	 * Constructeur
	 * 
	 */
	public Point(double x, double y){
		this.x = x;
		this.y = y;
	}

	//Class Methods

	
	//Methods
	public double getX(){
		return x;
	}
	
	public double getY(){
		return y;
	}
	
	public void setX(double x){
		this.x = x;
	}
	
	public void setY(){
		this.y = y;
	}

	/**
	 * 
	 * Renvoi la distance avec un autre point
	 * 
	 * @param p
	 * @return double distance
	 */
	public double distance(Point p){
		return Math.sqrt( (p.x-this.x)*(p.x-this.x) + (p.y-this.y)*(p.y-this.y) );
	}

	/**
	 * Verifie si le point est sur la droite
	 * 
	 * @param d
	 * @return boolean
	 * 
	 */
	public boolean estSurDroite(Droite d){
		return y == d.getPente() * x + d.getOrigine();
	}

	
	@Override
	public boolean equals(Object obj){
		if (obj instanceof Point){
			Point p = (Point)obj;

			return this.x == p.x && this.y == p.y;
		}
		return false;
	}

	@Override
	public String toString(){
		return String.format("(%.2f,%.2f)", x, y); 
	}

	
}