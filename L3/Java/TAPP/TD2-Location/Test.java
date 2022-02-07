/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Fri Jan 14 18:24:02 CET 2022
*
*/
import java.util.*;

public class Test {
	public static void main(String[] args){
		Personne moi = new Personne("Romain", 20, 18224556, true);
		Personne pasMoi = new Personne("Michel", 68, 1400, false);

		Louable laBMW = new Voiture("BMW e320", 2400);
		Louable laClio = new Voiture("Renault Clio 1", 150);
		Louable la121 = new Chambre(121, 78);
		Louable la345 = new Chambre(345, 700);

		List <Louable>locations = new <Louable>ArrayList();
		locations.add(laBMW);
		locations.add(laClio);
		locations.add(la121);
		locations.add(la345);

		System.out.println("Liste des locations :");
		for (Louable l : locations){
			System.out.println(l.toString());
		}

		System.out.println("\nListe des locations possibles pour Romain :");
		List <Louable>locationsPossibles = LouableManager.filtreLouable(locations, moi);
		for (Louable l : locationsPossibles){
			System.out.println(l.toString());
		}

		System.out.println("\nListe des locations possibles pour Michel :");
		locationsPossibles = LouableManager.filtreLouable(locations, pasMoi);
		for (Louable l : locationsPossibles){
			System.out.println(l.toString());
		}
		
	}
}