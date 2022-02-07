/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 24 14:12:32 CET 2022
*
*/
public class MotDansTitreSelectionneur implements Selectionneur{
	private String mot;
	
	public MotDansTitreSelectionneur(String m){
		mot = m;
	}

	/**Renvoi si le titre du document contient le mot du selectionneur
	 * 
	 * return Renvoi si le document satisfait le selectionneur
	 */
	@Override
	public boolean estSatisfaitPar(Document d){
		return d.getTitre().indexOf(mot) != -1;
	}
}