/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 24 13:53:49 CET 2022
*
*/
public class AuteurVivantSelectionneur implements Selectionneur{

	private Date debutAnnee;

	public AuteurVivantSelectionneur(int annee) throws InvalidDateException{
		debutAnnee = new Date(1,1,annee);
	}

	/**Verifie si l'auteur était vivant durant l'année du selectionneur
	 * 
	 * return Renvoi si le document satisfait le selectionneur
	 */
	@Override
	public boolean estSatisfaitPar(Document d){
		Date naissance = d.getAuteur().getNaissance();
		Date deces;

		try{
			deces = d.getAuteur().getDeces();
		}catch(NullPointerException e){
			deces = null;
		}

		//Si l'auteur était née l'année donnée
		if (naissance.compareTo(debutAnnee) < 0){
			//Pas mort
			if (deces == null){
				return true;
			}else{
				//renvoi si l'auteur est mort apres l'année donnée
				return (deces.compareTo(debutAnnee) > 0);
			}
		}
		//L'auteur n'était pas née l'année donnée
		return false;
		
	}
}