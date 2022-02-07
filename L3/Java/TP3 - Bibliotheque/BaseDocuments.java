import java.util.*;

public class BaseDocuments {
	// attribut(s) et constructeur(s)
	private List<Document> bdd;

	public BaseDocuments(){
		bdd = new ArrayList<Document>();
	}
	
	/** ajoute un document dans la base de documents
	* @param d le document `a ajouter
	*/
	public void ajoute(Document d){
		bdd.add(d);
	}
	
	/** supprime un document de la base de documents (si il est plusieurs
	* fois présents, une seule des occurrences est supprimée). Il
	* importe peu que le document soit emprunté ou non ,au moment de sa
	* suppression.
	* @param d le document à supprimer
	* @return le document supprimé, null s’il n’existe pas
	*/
	public Document supprime(Document d){
		return bdd.remove(d) ? d:null;
	}
	
	/** affiche tous les documents de la mediathèque (pour impression
	* du catalogue par exemple)
	*/
	public void affiche(){
		System.out.println("Affichage du catalogue");
		System.out.println("---------------------------------------------");
		for (Document d : bdd){
			System.out.println(d);
			System.out.println("---------------------------------------------");
		}
	}
	
	/** indique si le document donné est disponible (non emprunté)
	* @param d le document concerné
	* @return true si le document donné est disponible (non emprunté)
	* @exception NoSuchElementException si le document n’existe
	* pas dans la mediathèque
	*/
	public boolean estDisponible(Document d){
		if (bdd.contains(d)){
			return !bdd.get(bdd.indexOf(d)).getEmprunte();
		}else{
			throw new NoSuchElementException();
		}
	}
	
	/** permet d’emprunter un document
	* @param d le document concerne
	* @exception NoSuchElementException si le document n’existe
	* pas dans la mediathèque
	*/
	public void emprunte(Document d){
		if (estDisponible(d)){
			 bdd.get(bdd.indexOf(d)).setEmprunte(true);
		}
	}
	
	/** permet de rendre un document
	* @param d le document concerné
	*/
	public void rend(Document d){
		if (bdd.contains(d)){
			bdd.get(bdd.indexOf(d)).setEmprunte(false);
		}
	}

	/** fait une selection dans la base de document par rapport a un selectionneur
	 * @params s le selectionneur
	 * @return un iterateur sur la selection
	 */
	public Iterator selectionne(Selectionneur s){
		List<Document> selection = new ArrayList<Document>();

		for (Document d : bdd){
			if(s.estSatisfaitPar(d)){
				selection.add(d);
			}
		}

		return selection.iterator();
	}


	/**Créer une liste triée a partir d'un interateur
	 * 
	 * @param i iterateur pour la construction
	 * @param c comparateur pour le tri
	 * 
	 * @return La liste trié
	 */
	public static List<Document> listeTriee(Iterator i, Comparator c){
		List<Document> res = new ArrayList<Document>();

		while(i.hasNext()){
			res.add((Document)i.next());
		}

		Collections.sort(res, c);

		return res;
	}
}
