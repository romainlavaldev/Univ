/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 24 14:32:56 CET 2022
*
*/
import java.util.*;
public class SelectionneurComposite implements Selectionneur{

	private List<Selectionneur> s;

	public SelectionneurComposite(){
		s = new ArrayList<Selectionneur>();
	}

	public void add(Selectionneur sel){
		s.add(sel);
	}


	/**Verifie si tous les selectionneurs de la liste sont satisfaits
	 * 
	 * return Renvoi si tous les selectionneurs sont satisfaits 
	 */
	@Override
	public boolean estSatisfaitPar(Document d){
		for (Selectionneur sel : s){
			if (!sel.estSatisfaitPar(d)){
				return false;
			}
		}
		return true;
	}
	
}