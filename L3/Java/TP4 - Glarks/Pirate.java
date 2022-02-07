/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:42:40 CET 2022
*
*/
public class Pirate extends Glarks{

	/**Constructor
	 * 
	 * @param CaseLibre c : La case sur laquelle le Pirate se trouve à la création
	 */
	public Pirate(CaseLibre c){
		super(c);
	}

	/**Comportement lors de la présentation de blurf sur une case : Ne pas le manger
	 * 
	 */
	public void mangerBlurf(){
		return;
	}

	/**Comportement du Pirate lors de la présentation d'un repas : Le manger et prendre son energie
	 * 
	 * @param Glarks g : Le Glarks qui va se faire manger
	 */
	public void mangerGlarks(Glarks g){
		if (g != this){
			energie += g.energie;
			g.meurs();
		}
	}

	/**Methode qui permet de trouver la case vers laquelle le Pirate va se diriger
	 * 
	 * @return Case : La première case qui contient un Glarks ou la première case libre si aucun Glarks aux alentours
	 */
	public Case trouveDestination(){
		//Recherche d'un Glarks
		Case c = getCaseActuelle().getVoisinNord();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.countGlarks() > 0){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinEst();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.countGlarks() > 0){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinSud();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.countGlarks() > 0){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinOuest();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.countGlarks() > 0){
				return c;
			}
		}

		//Recherche case libre
		c = getCaseActuelle().getVoisinNord();
		if (!c.estObstacle()){
			return c;
		}

		c = getCaseActuelle().getVoisinEst();
		if (!c.estObstacle()){
			return c;
		}
		
		c = getCaseActuelle().getVoisinSud();
		if (!c.estObstacle()){
			return c;
		}
		
		c = getCaseActuelle().getVoisinOuest();
		if (!c.estObstacle()){
			return c;
		}

		return getCaseActuelle();

	}

	/**Corespondance en String d'un Pirate
	 * 
	 * @return String : Caractère corespondant à un Pirate
	 */
	@Override
	public String toString(){
		return "P";
	}
}