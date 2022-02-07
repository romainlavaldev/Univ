/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:42:48 CET 2022
*
*/
public class Glouton extends Glarks{

	/**Constructor
	 * 
	 * @param CaseLibre c : La case sur laquelle le Glouton se trouve à la création
	 */
	public Glouton(CaseLibre c){
		super(c);
	}


	/**Comportement du Glouton lors de la présentation d'un repas : Reprend le comportement de base -> ne mange pas
	 * 
	 * @param Glarks g : Le Glarks qui va se faire manger
	 */
	public void mangerGlarks(Glarks g){
		super.mangerGlarks(g);
	}


	/**Methode qui permet de trouver la case vers laquelle le Glouton va se diriger
	 * 
	 * @return Case : La première case qui contient du blurf ou la première case libre si aucun blurf aux alentours
	 */
	public Case trouveDestination(){
		//Recherche du blurf
		Case c = getCaseActuelle().getVoisinNord();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.hasBlurf()){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinEst();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.hasBlurf()){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinSud();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.hasBlurf()){
				return c;
			}
		}
		
		c = getCaseActuelle().getVoisinOuest();
		if (!c.estObstacle()){
			CaseLibre cl = (CaseLibre)c;
			if (cl.hasBlurf()){
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


	/**Corespondance en String d'un Glouton
	 * 
	 * @return String : Caractère corespondant à un Glouton
	 */
	@Override
	public String toString(){
		return "G";
	}
}