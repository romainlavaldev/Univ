/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Jan 11 09:30:51 CET 2022
*
*/
public class Test {
	public static void main(String args[]) throws DroiteParalleleException{
		
	
		Point p1 = new Point(0.0 , 0.0);
		System.out.println("A : " + p1.toString());
		Point p2 = new Point(3.0 , 0.0);
		System.out.println("B : " + p2.toString());
		Point p3 = new Point(3.0 , 4.0);
		System.out.println("C : " + p3.toString());
		Point p4 = new Point(0.0 , 4.0);
		System.out.println("C : " + p3.toString());
	
		System.out.println("distance a - b : " + p1.distance(p2));


		Triangle t = new Triangle(p1, p2, p3);

		System.out.println(t.toString());
		System.out.println("Perimetre : " + t.perimetre());
		System.out.println("Surface : " + t.surface());

		Droite d = new Droite(p1,p3);
		System.out.println("d1 : " + d.toString());
		System.out.println(p2.toString() + " sur d ? : " + p2.estSurDroite(d));

		Droite d2 = new Droite(p2,p4);
		System.out.println("d2 : " + d2.toString());

		System.out.println("point d'intersection entre d1 et d2 : " + d.intersection(d2));

		Droite d3 = new Droite(p1,p2);
		System.out.println("Triangle d1,d2,d3 : " + new Triangle(d,d2,d3));
		System.out.println("Triangle d1,d1,d3 : " + new Triangle(d,d,d3));
		
	}

}