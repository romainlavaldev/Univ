/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:31:59 CET 2022
*
*/

import java.util.List;
import java.util.ArrayList;


public class Jeu {
	private Damier damier;
	private List<Glarks> listeGlarks;
	private int vitesse;

	/**Constructor
	 * @param int vitesse : Permet de définir la vitesse d'affichage des cycles du jeu (1 -> affichage normale (1s), 4 -> affichage rapide (0.25s))
	 */
	public Jeu(int vitesse){
		this.vitesse = vitesse;
		listeGlarks = new ArrayList<>();
		initialiser();
		
	}

	/**Methode de lancement du jeu. Permet l'affichage et le déroulement des cycles du jeu jusqu'a la fin
	 * 
	 * 
	 * @throws InterruptedException : Si interruption pendant l'attente entre chaques cycles
	 */
	public void lancer() throws InterruptedException{
		boolean unGlarksEnVie;

		do{
			afficherJeu();
			unGlarksEnVie = false;
			
			for (Glarks g : listeGlarks){
				if (g.getEnergie() > 0){
					unGlarksEnVie = true;
					g.doCycle();
					afficherJeu();
					Thread.sleep(1000/vitesse);
				}
			}
			
		}while(unGlarksEnVie);
	}

	/**Methode d'initialisation du jeu. La création du plateau de jeu et le positionnement des Glarks sont fixés
	 * 
	 * 
	 */
	public void initialiser(){
		damier = new Damier(10,10);
		bloquerContours();

		//Remplissage de cases vides
		remplirCentre();


		//Murs
		damier.setCase(3, 1, new Case(3, 1, damier));
		damier.setCase(3, 2, new Case(3, 2, damier));

		
		damier.setCase(7, 1, new Case(7, 1, damier));
		damier.setCase(7, 2, new Case(7, 2, damier));
		damier.setCase(7, 3, new Case(7, 3, damier));
		damier.setCase(7, 4, new Case(7, 4, damier));

		
		damier.setCase(1, 6, new Case(1, 6, damier));
		damier.setCase(2, 6, new Case(2, 6, damier));
		damier.setCase(3, 6, new Case(3, 6, damier));
		damier.setCase(4, 6, new Case(4, 6, damier));

		//Blurfage de la zone
		CaseLibre c = (CaseLibre)damier.getCase(1, 2);
		c.poserBlurf();
		c = (CaseLibre)damier.getCase(4, 3);
		c.poserBlurf();
		c = (CaseLibre)damier.getCase(4, 7);
		c.poserBlurf();
		c = (CaseLibre)damier.getCase(7, 8);
		c.poserBlurf();
		c = (CaseLibre)damier.getCase(8, 5);
		c.poserBlurf();

		//Posage des Glarks
		c = (CaseLibre)damier.getCase(5,4);
		listeGlarks.add(new Borne(c, new Direction(Rose.NORD)));
		c = (CaseLibre)damier.getCase(7,7);
		listeGlarks.add(new Glouton(c));
		c = (CaseLibre)damier.getCase(8,2);
		listeGlarks.add(new Pirate(c));
		c = (CaseLibre)damier.getCase(5,2);
		listeGlarks.add(new Borne(c, new Direction(Rose.EST)));
	}

	/**Methode permetant de positionner des murs tout autour du damier
	 * 
	 */
	private void bloquerContours(){
		//Colonne 1 + derniere colonne
		for(int i = 0; i < damier.rowsCount(); i++){
			damier.setCase(i, 0, new Case(i, 0, damier));
			damier.setCase(i, damier.columnsCount()-1, new Case(i, damier.columnsCount()-1, damier));
		}
		//Ligne 1 + derniere ligne
		for(int i = 1; i < damier.columnsCount()-1; i++){
			damier.setCase(0, i, new Case(0, i, damier));
			damier.setCase(damier.columnsCount()-1, i, new Case(damier.columnsCount()-1, i, damier));
		}
	}

	/**Methode permetant de remplire le damier (contours exclus) de cases libres 
	 * 
	 * 
	 */
	private void remplirCentre(){
		for(int i = 1; i < damier.rowsCount()-1; i++){
			for (int j = 1; j < damier.columnsCount()-1; j++){
				damier.setCase(i, j, new CaseLibre(i, j, damier, false));
			}
		}
	}

	
	/**Methode d'affichage du jeu. Un "clear" est simulé par 100 retours à la ligne
	 * 
	 */
	public void afficherJeu(){
		System.out.println("\n".repeat(100));
		System.out.println(this);
	}

	/**Methode de récuperation de la liste des Glarks et de leurs statistiques (type ,energie, cout de déplacement)
	 * 
	 * @return String 
	 */
	private String statsGlarks(){
		String s = "Statistiques des Glarks en jeu :\n";
		for (Glarks g : listeGlarks){
			s += g.stats() + "\n";
		}
		return s;
	}

	/**Affichage des stats + du damier
	 * 
	 * @return String
	 */
	@Override
	public String toString(){
		return "Jeu de Glarks !\n\n" +
				statsGlarks() +
				damier;
	}
	
}