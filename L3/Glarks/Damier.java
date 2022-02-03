/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:59:44 CET 2022
*
*/
public class Damier {
	private Case[][] cases;

	/**Constructor
	 * 
	 * @param int rows : Nombre de lignes du damier
	 * @param int columns : Nombre de colonnes du damier
	 */
	public Damier(int rows, int columns){
		cases = new Case[rows][columns];
	}

	/**Methode de recherche de case dans le damier
	 * 
	 * @param int i : La ligne de la case
	 * @param int j : La colonne de la case
	 * 
	 * @return Case : La case corréspondante aux coordonées
	 */
	public Case getCase(int i, int j){
		return cases[i][j];
	}

	/**Methode de modification de case dans le damier
	 * 
	 * @param int i : La ligne de la case
	 * @param int j : La colonne de la case
	 * @param Case c : La nouvelle case
	 * 
	 */
	public void setCase(int i, int j, Case c){
		cases[i][j] = c;
	}

	/**Getter
	 * 
	 * @return int : Le nombre de lignes dans le damier
	 */
	public int rowsCount(){
		return cases[0].length;
	}

	
	/**Getter
	 * 
	 * @return int : Le nombre de colonnes dans le damier
	 */
	public int columnsCount(){
		return cases.length;
	}

	/**Methode de transforamtion du damier en String. Concatenne l'affichage des cases du damier.
	 * 
	 */
	@Override
	public String toString(){
		String s = "";

		for (int i = 0; i < rowsCount(); i++){
			s += "\n";
			for (int j = 0; j < columnsCount(); j++){
				s+= cases[i][j] + " ";
			}
		}
		return s;
	}
}