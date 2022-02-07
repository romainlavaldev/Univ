/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 17 13:36:00 CET 2022
*
*/
public class Test {
	public static void main(String args[]) throws IllegalZoomFactorException{

		Cercle c = new Cercle(4);
		Rectangle r = new Rectangle(1.5,2);

		System.out.println("perimetre ("+c+") : "+c.perimetre()+ " surface : "+c.surface());
		System.out.println("perimetre ("+r+") : "+r.perimetre()+ " surface : "+r.surface());

		c.agrandir(2);
		System.out.println("perimetre ("+c+") : "+c.perimetre()+ " surface : "+c.surface());

		
		Sphere s = new Sphere(3);
		Cylindre cy = new Cylindre(4,8);

		System.out.println("volume ("+s+") : "+s.volume()+ " surface : "+s.surface());
		System.out.println("volume ("+cy+") : "+cy.volume()+ " surface : "+cy.surface());

		s.agrandir(2);
		System.out.println("volume ("+s+") : "+s.volume()+ " surface : "+s.surface());
		s.agrandir(-2);
	}
}