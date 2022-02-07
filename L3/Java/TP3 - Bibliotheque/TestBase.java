/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 19 14:55:40 CET 2022
*
*/

import java.util.*;
public class TestBase {
	public static void main(String args[]) throws InvalidDateException{
		

		//Création base
		BaseDocuments b = new BaseDocuments();
	
		Auteur pedro = new Auteur("Pedro Lestracicus", new Date(8,10,2001));
		Auteur jeanEude = new Auteur("Jean-Eude du Frêne", new Date(14,2,1945), new Date(1,1,2014));
	
		Document ltb1 = new Document(jeanEude, "Le livre trop bien 1");
		Document ltb2 = new Document(jeanEude, "Le livre trop bien 2");
		Document ltbr1 = new Document(pedro, "Le livre trop bien REMAKE 1");
		Document ltb3 = new Document(jeanEude, "Le livre trop bien 3");
		Document ltbr2 = new Document(pedro, "Le livre trop bien REMASTERED EDITION COMPLETE");
	
		b.ajoute(ltb1);
		b.ajoute(ltb2);
		b.ajoute(ltb3);
		b.ajoute(ltbr1);
		b.ajoute(ltbr2);

		//Test d'affichage
		b.affiche();

		//Test suppression
		System.out.println("\nSuppression de ltb2");
		b.supprime(ltb2);
		b.affiche();

		//Test emprunt
		System.out.println("\nEmprunt de ltbr1");
		b.emprunte(ltbr1);
		System.out.println("Dispo de ltbr1 : " + b.estDisponible(ltbr1));

		System.out.println("\nRendu de ltbr1");
		b.rend(ltbr1);
		System.out.println("Dispo de ltbr1 : " + b.estDisponible(ltbr1));


		//Test erreur emprunt
		System.out.println("\nEmprunt de imp (pas dans la bdd)");
		try{
			Document imp = new Document(jeanEude, "L'imposteur");
			b.emprunte(imp);
		}catch(Exception e){
			System.out.println("Il n'y a pas l'element dans la bdd -> erreur !");
		}

		//Test SELECTIONNEUR Emprunt
		b.emprunte(ltbr1);
		System.out.println("\nDispo de ltbr1 : " + b.estDisponible(ltbr1));
		b.emprunte(ltb3);
		System.out.println("Dispo de ltb3 : " + b.estDisponible(ltbr1));

		Selectionneur s = new NonEmprunteSelectionneur();
		Iterator i = b.selectionne(s);

		System.out.println("\nDocuments non empruntés");
		
		System.out.println("---------------------------------------------");
		while (i.hasNext()){
			System.out.println(i.next());
			System.out.println("---------------------------------------------");
		}

		//Test SELECTIONNEUR AuteurVivant
		s = new AuteurVivantSelectionneur(2016);
		i = b.selectionne(s);

		System.out.println("\nDocuments avec auteur Vivant en 2016");
		System.out.println("---------------------------------------------");
		while (i.hasNext()){
			System.out.println(i.next());
			System.out.println("---------------------------------------------");
		}
		//Test SELECTIONNEUR Mot dans Titre
		s = new MotDansTitreSelectionneur("trop");
		i = b.selectionne(s);

		System.out.println("\nDocuments avec trop dans le titre");
		System.out.println("---------------------------------------------");
		while (i.hasNext()){
			System.out.println(i.next());
			System.out.println("---------------------------------------------");
		}

		
		s = new MotDansTitreSelectionneur("REMAKE");
		i = b.selectionne(s);

		System.out.println("\nDocuments avec REMAKE dans le titre");
		System.out.println("---------------------------------------------");
		while (i.hasNext()){
			System.out.println(i.next());
			System.out.println("---------------------------------------------");
		}

		//Test SELECTIONNEUR Composite

		Document leDocPourLeTest = new Document(jeanEude, "Le polymorphisme dans la cuisine des antilles");
		b.ajoute(leDocPourLeTest);

		SelectionneurComposite sc = new SelectionneurComposite();
		sc.add(new MotDansTitreSelectionneur("polymorphisme"));
		sc.add(new AuteurVivantSelectionneur(2005));

		i = b.selectionne(sc);

		System.out.println("\nDocuments avec polmorphisme et auteur vivant en 2005");
		System.out.println("---------------------------------------------");
		while (i.hasNext()){
			System.out.println(i.next());
			System.out.println("---------------------------------------------");
		}

		//Test TRI
		Document dTest1 = new Document(jeanEude, "Art et polymorphisme");
		b.ajoute(dTest1);
		
		Document dTest2 = new Document(jeanEude, "L'oiseau de feu dans les cendres rouges, interpretation du polymorphisme moderne");
		b.ajoute(dTest2);

		s = new MotDansTitreSelectionneur("polymorphisme");
		i = b.selectionne(s);

		System.out.println("\nListe des documents avec polymorphisme triée");
		List<Document> l = BaseDocuments.listeTriee(i, new TitreComparator());
		System.out.println("---------------------------------------------");
		for (Document doc : l){
			System.out.println(doc);
			System.out.println("---------------------------------------------");
		}

	}
}