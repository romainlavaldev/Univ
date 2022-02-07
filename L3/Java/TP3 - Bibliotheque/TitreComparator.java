/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 24 14:59:08 CET 2022
*
*/
import java.util.*;
public class TitreComparator implements Comparator{


	/**Compare le titre de deux documents dans l'ordre alphabetique
	 * 
	 * Renvoi -1, 0 ou 1
	 */
	@Override
	public int compare(Object o1, Object o2){
		//Cast
		Document d1;
		Document d2;
		if (o1 instanceof Document && o2 instanceof Document){
			d1 = (Document)o1;
			d2 = (Document)o2;
		}else{
			throw new ClassCastException("Can't compare non-Documents obj");
		}

		//Compare
		return d1.getTitre().compareTo(d2.getTitre());
	}
}