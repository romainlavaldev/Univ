/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:35:48 CET 2022
*
*/

import java.util.List;
import java.util.ArrayList;

public class CaseLibre extends Case{
	private boolean blurf;
	private List<Glarks> listeGlarks;

	/**Constructor
	 * 
	 * @param int row : Ligne de la case dans le damier
	 * @param int column : Colonne de la case dans le damier
	 * @param Damier d : Damier sur lequel la case se trouve
	 * @param boolean blurf : Présence de blurf sur la case
	 */
	public CaseLibre(int x, int y, Damier d, boolean blurf){
		super(x,y,d);
		this.blurf = blurf;
		listeGlarks = new ArrayList<>();
	}

	/**Methode de verification de la nature de la case
	 * 
	 * @return false : Nature bloquante de la case
	 */
	@Override
	public boolean estObstacle(){
		return false;
	}

	/**Methode de suppression d'un Glarks sur la case
	 * 
	 * @param Glarks g : Le Glarks à supprimer
	 */
	public void removeGlarks(Glarks g){
		listeGlarks.remove(g);
	}

	/**Methode d'ajout d'un Glarks sur la case. Présente aussi le menu de la case à l'arrivée d'un nouveau Glarks
	 * 
	 * @param Glarks g : Le Glarks à ajouter
	 */
	public void addGlarks(Glarks g){
		
		listeGlarks.add(g);
		presenterMenu(g);
		
	}

	/**Methode de comptage des Glarks présents sur la case
	 * 
	 * @return int : Nombres de Glarks sur la case
	 */
	public int countGlarks(){
		return listeGlarks.size();
	}

	/**Getter
	 * 
	 * @return boolean : Présence de blurf sur la case
	 */
	public boolean hasBlurf(){
		return blurf;
	}

	/**Setter - Pose du blurf sur la case
	 * 
	 */
	public void poserBlurf(){
		blurf = true;
	}

	/**Setter - Enlève le blurf sur la case
	 * 
	 */
	public void enleverBlurf(){
		blurf = false;
	}

	/**Methode d'accès à la voisine droite de la case
	 * 
	 * @return Case : voisine droite de la case
	 */
	public Case getVoisinEst(){
		return new Direction(Rose.EST).voisineDansDir(this);
	}

	/**Methode d'accès à la voisine gauche de la case
	 * 
	 * @return Case : voisine gauche de la case
	 */
	public Case getVoisinOuest(){
		return new Direction(Rose.OUEST).voisineDansDir(this);
	}

	/**Methode d'accès à la voisine au dessus de la case
	 * 
	 * @return Case : voisine au dessus de la case
	 */
	public Case getVoisinNord(){
		return new Direction(Rose.NORD).voisineDansDir(this);
	}

	/**Methode d'accès à la voisine en dessous de la case
	 * 
	 * @return Case : voisine en dessous de la case
	 */
	public Case getVoisinSud(){
		return new Direction(Rose.SUD).voisineDansDir(this);
	}


	/**Propose à un Glarks de manger tous les Glarks présents sur la case
	 * 
	 * @param Glarks mangeur : Le Glarks qui se verra proposé le menu
	 */
	public void presenterMenu(Glarks mangeur){
		for (Glarks g : listeGlarks){
			mangeur.mangerGlarks(g);
		}
	}

	
	/**Corespondance en String d'une case libre
	 * 
	 * @return String : Soit le caractère du blurf, soit le premier blurf sur la case, soit un blanc
	 */
	@Override
	public String toString(){
		if (listeGlarks.size() == 0){
			return blurf ? "$":" ";
		}else{
			return listeGlarks.iterator().next().toString();
		}
	}
}