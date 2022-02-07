/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Fri Jan 14 18:46:59 CET 2022
*
*/
import java.util.*;

public abstract class LouableManager {
	public static List<Louable> filtreLouable(List<Louable> list, Personne p){
		List<Louable> resultat = new <Louable>ArrayList();
		
		for (Louable loc : list){
			if (loc.peutEtreLoue(p)){
				resultat.add(loc);
			}
		}

		return resultat;
	}
}