/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:33:00 CET 2022
*
*/
public class Case {
	private int positionRow;
	private int positionColumn;
	protected Damier damier;

	/**Constructor
	 * 
	 * @param int row : Ligne de la case dans le damier
	 * @param int column : Colonne de la case dans le damier
	 * @param Damier d : Damier sur lequel la case se trouve
	 */
	public Case(int row, int column, Damier d){
		positionRow = row;
		positionColumn = column;
		damier = d;
	}

	/**Getter
	 * 
	 * @return Damier : damier sur lequel la case se trouve
	 */
	public Damier getDamier(){
		return damier;
	}

	/**Methode de verification de la nature de la case
	 * 
	 * @return true : Nature bloquante de la case
	 */
	public boolean estObstacle(){
		return true;
	}

	/**Getter
	 * 
	 * @return int : Ligne du damier sur laquelle se trouve la case
	 */
	public int getRow(){
		return positionRow;
	}

	/**Getter
	 * 
	 * @return int : Colonne du damier sur laquelle se trouve la case
	 */
	public int getColumn(){
		return positionColumn;
	}

	/**Corespondance en String d'une case bloquante
	 * 
	 * @return String : Caractère corespondant à une case bloquante 
	 */
	@Override
	public String toString(){
		return "#";
	}
}