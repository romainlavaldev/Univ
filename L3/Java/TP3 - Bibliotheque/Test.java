/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 19 13:45:06 CET 2022
*
*/
public class Test {
	public static void main(String args[]) throws InvalidDateException{

		Date d1 = new Date(19,1,2022);

		Date d2 = new Date(25,4,2020);


		//Test comparaison
		System.out.println(d1+" comparé à "+d2+" : "+d1.compareTo(d2) + "\n");

		//Test erreur date
		try{
			Date d3 = new Date(25,14,2012);
		}catch(InvalidDateException e){
			System.out.println("\nException dans la création de la date ! -> InvalidDateException");
		}

		//Test auteur
		Auteur a = new Auteur("Pedro Lestracicus", new Date(8,10,2001));
		System.out.println("\nAuteur1 : "+a);
		
		Auteur a2 = new Auteur("Pedro Lestracicus", new Date(8,10,2001));
		System.out.println("\nAuteur2 : "+a2);

		System.out.println("Auteur1 equals Auteur2 ? : "+a.equals(a2));


		//Test document
		Document doc = new Document(a, "Les fleurs rouge du crépuscule quand le soleil se couche");
		Document doc2 = new Document(a2, "La petite et le grand qui court en marchant seul");

		System.out.println("\n");
		System.out.println(doc);
		System.out.println(doc2);
	
		System.out.println("equals sur les deux docs : " + doc.equals(doc2));
	}
}