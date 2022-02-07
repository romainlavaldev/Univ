/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 31 22:07:08 CET 2022
*
*/
public class ArbreBinaireRecherche <E extends Comparable>{
	private E element;
	private ArbreBinaireRecherche<E> gauche;
	private ArbreBinaireRecherche<E> droit;

	public ArbreBinaireRecherche(E racine){
		element = racine;
		gauche = null;
		droit = null;
	}

	public ArbreBinaireRecherche(E racine, ArbreBinaireRecherche<E> g, ArbreBinaireRecherche<E> d){
		element = racine;
		gauche = g;
		droit = d;
	}

	public E valeur(){
		return element;
	}

	public ArbreBinaireRecherche<E> filsGauche(){
		return gauche;
	}

	public ArbreBinaireRecherche<E> filsDroit(){
		return droit;
	}

	public void affecterFilsGauche(ArbreBinaireRecherche<E> a){
		gauche = a;
	}

	public void affecterFilsDroit(ArbreBinaireRecherche<E> a){
		droit = a;
	}

	public boolean existeFilsGauche(){
		return gauche != null;
	}

	public boolean existeFilsDroit(){
		return droit != null;
	}

	public boolean estFeuille(){
		return !existeFilsGauche() && !existeFilsDroit();
	}
	
	public boolean contient(E x){
		if (element == x){
			return true;
		}
		
		if (estFeuille()){
			return false;
		}

		return x.compareTo(element) > 0 ? droit.contient(x):gauche.contient(x);
	}

	public void inserer(E e){
		if (contient(e)){
			throw new IllegalArgumentException("Can't add %{e} in tree because the element is already in it");
		}

		if (e.compareTo(element) > 0){
			if (!existeFilsDroit()){
				affecterFilsDroit(new ArbreBinaireRecherche<E>(e));
			}else{
				droit.inserer(e);
			}
		}

		if (e.compareTo(element) < 0){
			if (!existeFilsGauche()){
				affecterFilsGauche(new ArbreBinaireRecherche<E>(e));
			}else{
				gauche.inserer(e);
			}
		}
	}
	
}