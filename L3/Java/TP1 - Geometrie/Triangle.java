/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Jan 11 09:17:09 CET 2022
*
*/
public class Triangle {
	/**
	 * Class Triangle
	 * 
	 * @param points Tableau qui contient les points du triangle
	 */
	private Point[] points;

	//Constructors
	/**
	*Constructor du triangle a partir de 3 points
	*	
	*/
	public Triangle(Point p1, Point p2, Point p3){
		points = new Point[3];
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
	}
	
	/**
	*Constructor du triangle a partir de 3 droites
	*	
	*/
	public Triangle(Droite d1, Droite d2, Droite d3) throws DroiteParalleleException{
		points = new Point[3];
		points[0] = d1.intersection(d2);
		points[1] = d2.intersection(d3);
		points[2] = d3.intersection(d1);
	}

	//Class Methods

	//Methods
	/**
	 * Renvoi le perimetre du triangle
	 * 
	 * @return double Perimètre du triangle
	 */
	public double perimetre(){
		//Premiere droite
		double p = points[0].distance(points[1]);
		
		//seconde droite
		p += points[1].distance(points[2]);
		
		//troisième droite
		p += points[2].distance(points[0]);

		return p;
	}
	/**
	 * Renvoi l'air du triangle
	 * 
	 * @return double Air du triangle
	 */
	public double surface(){
		double demiP = perimetre() / 2;
		double a = points[0].distance(points[1]);
		double b = points[1].distance(points[2]);
		double c = points[2].distance(points[0]);

		double solution = Math.sqrt( demiP * (demiP - a) * (demiP - b) * (demiP - c) );

		return solution;
	}

	@Override
	public String toString(){
		return String.format("Triangle : (%.2f,%.2f)(%.2f,%.2f)(%.2f,%.2f)", points[0].getX(), points[0].getY(), points[1].getX(), points[1].getY(), points[2].getX(), points[2].getY());
	}
}