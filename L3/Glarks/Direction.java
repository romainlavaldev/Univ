/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:45:32 CET 2022
*
*/


public class Direction {
	private Rose direction;

	/**Contructor
	 * 
	 * @param Rose d : Le sens (Nord,Est,Sud,Ouest) de la direction
	 */
	public Direction(Rose d){
		direction = d;
	}

	/**Getter
	 * 
	 * @return Rose : Le sens (Nord,Est,Sud,Ouest) de la direction
	 */
	public Rose getDirectionRose(){
		return direction;
	}

	/**Methode qui permet de trouver la case voisine dans la direction
	 * 
	 * @param : Case c : La case de départ
	 * 
	 * @return Case : La case trouvée
	 */
	public Case voisineDansDir(Case c){
		int caseRow = c.getRow();
		int caseColumn = c.getColumn();
		
		switch(direction){
			case NORD:
				return c.getDamier().getCase(caseRow-1, caseColumn);
			case SUD:
				return c.getDamier().getCase(caseRow+1, caseColumn);
			case EST:
				return c.getDamier().getCase(caseRow, caseColumn+1);
			default:
				return c.getDamier().getCase(caseRow, caseColumn-1);
		}
		
	}

	/**Methode qui permet de trouver la case voisine à gauche de la direction
	 * 
	 * @param : Case c : La case de départ
	 * 
	 * @return Case : La case trouvée
	 */
	public Case voisineGauche(Case c){
		int caseRow = c.getRow();
		int caseColumn = c.getColumn();
		
		switch(direction){
			case NORD:
				return c.getDamier().getCase(caseRow, caseColumn-1);
			case SUD:
				return c.getDamier().getCase(caseRow, caseColumn+1);
			case EST:
				return c.getDamier().getCase(caseRow-1, caseColumn);
			default:
				return c.getDamier().getCase(caseRow+1, caseColumn);
		}
	}

	/**Methode qui permet de trouver la case voisine à droite de la direction
	 * 
	 * @param : Case c : La case de départ
	 * 
	 * @return Case : La case trouvée
	 */
	public Case voisineDroite(Case c){
		int caseRow = c.getRow();
		int caseColumn = c.getColumn();
		
		switch(direction){
			case NORD:
				return c.getDamier().getCase(caseRow, caseColumn+1);
			case SUD:
				return c.getDamier().getCase(caseRow, caseColumn-1);
			case EST:
				return c.getDamier().getCase(caseRow+1, caseColumn);
			default:
				return c.getDamier().getCase(caseRow-1, caseColumn);
		}
	}


	/**Methode qui permet de trouver la case voisine à l'opposé de la direction
	 * 
	 * @param : Case c : La case de départ
	 * 
	 * @return Case : La case trouvée
	 */
	public Case voisineOpposee(Case c){
		int caseRow = c.getRow();
		int caseColumn = c.getColumn();
		
		switch(direction){
			case NORD:
				return c.getDamier().getCase(caseRow+1, caseColumn);
			case SUD:
				return c.getDamier().getCase(caseRow-1, caseColumn);
			case EST:
				return c.getDamier().getCase(caseRow, caseColumn-1);
			default:
				return c.getDamier().getCase(caseRow, caseColumn+1);
		}
	}

	
}