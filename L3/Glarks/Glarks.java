/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:42:19 CET 2022
*
*/
public abstract class Glarks {
	private int coutDeplacement;
	{
		coutDeplacement = 5;
	}
	
	protected int energie;
	{
		energie = 100;
	}
	
	private CaseLibre caseActuelle;

	/**Constructor
	 * 
	 * @param CaseLibre c : La case sur laquelle le Glarks se trouve à la création
	 */
	public Glarks(CaseLibre c){
		setCaseActuelle(c);
	}
	
	/**Getter
	 * 
	 * @return int : L'energie restante au Glarks 
	 */
	public int getEnergie(){
		return energie;
	}

	/**Setter - Modification + action sur une case
	 * 
	 * @param CaseLibre newCase : La nouvelle case sur laquelle va se trouver le Glarks
	 * 
	 */
	protected void setCaseActuelle(CaseLibre newCase){
		if (caseActuelle != null){
			caseActuelle.removeGlarks(this);
		}
		caseActuelle = newCase;
		caseActuelle.addGlarks(this);
		if(caseActuelle.hasBlurf()){
			mangerBlurf();
		}
	}

	/**Getter
	 * 
	 * @return CaseLibre : La case sur laquelle se trouve le Glarks
	 */
	protected CaseLibre getCaseActuelle(){
		return caseActuelle;
	}

	/**Methode de gestion de l'élimination d'un Glarks
	 * 
	 */
	protected void meurs(){
		energie = 0;
		caseActuelle.removeGlarks(this);
	}

	/**Methode principale qui définie le comportement du Glarks à chaque cycle de jeu
	 * 
	 */
	public void doCycle(){
		energie -= coutDeplacement;
		if (energie <= 0){
			meurs();
		}else{
			CaseLibre c = (CaseLibre)trouveDestination();
			if (c != caseActuelle){
				setCaseActuelle(c);
			}
		}
	}

	/**Methode de verification de la nature du Glarks
	 * 
	 * @return false : Nature "borné" du Glarks
	 */
	public boolean estBorne(){
		return false;
	}

	/**Methode permettant de manger le blurf présent sur la case actuelle
	 * 
	 */
	public void mangerBlurf(){
		energie += 100;
		caseActuelle.enleverBlurf();
	}

	/**Methode qui definie le comportement lorsque qu'un repas est présenté au Glarks
	 * 
	 * @param Glarks g : Le Glarks qui va se faire manger
	 */
	public void mangerGlarks(Glarks g){
		//on ne mange pas ses camarades
		return;
	}

	/**Methode qui permet de trouver la case vers laquelle le Glarks va se diriger
	 * 
	 * @return Case : La case trouvée
	 */
	public abstract Case trouveDestination();

	/**Methode de récupération des infos du Glarks
	 * 
	 * @return String : Informations sur le glarks (type, energie restante, cout de déplacement) 
	 */
	public String stats(){
		return this.getClass() + " [Energie : " + energie + " / Cout déplacement : " + coutDeplacement + "]";
	}
}