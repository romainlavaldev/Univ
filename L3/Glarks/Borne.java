/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 02 13:42:32 CET 2022
*
*/
public class Borne extends Glarks{
	private Direction direction;

	/**Constructor
	 * 
	 * @param CaseLibre c : La case sur laquelle le Borné se trouve à la création
	 * @param Direction d : La direction de départ du Borné
	 */
	public Borne(CaseLibre c, Direction d){
		super(c);
		direction = d;
	}

	/**Methode de verification de la nature du Borné
	 * 
	 * @return true : Nature "borné" du Borné
	 */
	@Override
	public boolean estBorne(){
		return true;
	}

	/**Comportement du Borné lors de la présentation d'un repas : Le manger et prendre son energie
	 * 
	 * @param Glarks g : Le Glarks qui va se faire manger
	 */
	@Override
	public void mangerGlarks(Glarks g){
		if (this != g){
			energie += g.energie;
			g.meurs();
		}
	}

	/**Methode qui permet de trouver la case vers laquelle le Borné va se diriger
	 * 
	 * @return Case : La case dans la direction du Borné ou une case libre en cas de mur devant le Borné
	 */
	public Case trouveDestination(){
		//Essai dans la direction du Borné
		Case c = direction.voisineDansDir(getCaseActuelle());

		if (!c.estObstacle()){
			return c;
		}else{
			//Essai à gauche
			c = direction.voisineGauche(getCaseActuelle());
			Rose sensActuelle = direction.getDirectionRose();
			
			if (!c.estObstacle()){
				//Mise à jout de la direction
				switch(sensActuelle){
					case NORD:
						direction = new Direction(Rose.OUEST);
						break;
					case SUD:
						direction = new Direction(Rose.EST);
						break;
					case EST:
						direction = new Direction(Rose.NORD);
						break;
					default:
						direction = new Direction(Rose.SUD);
				}
				
				return c;
			}else{
				//Essai derrière
				c = direction.voisineOpposee(getCaseActuelle());

				if (!c.estObstacle()){
					//Mise à jour de la direction
					switch(sensActuelle){
						case NORD:
							direction = new Direction(Rose.SUD);
							break;
						case SUD:
							direction = new Direction(Rose.NORD);
							break;
						case EST:
							direction = new Direction(Rose.OUEST);
							break;
						default:
							direction = new Direction(Rose.EST);
					}
				
					return c;
				}else{
					//Essai à droite
					c = direction.voisineDroite(getCaseActuelle());

					if (!c.estObstacle()){
						//Mise à jour de la direction
						switch(sensActuelle){
							case NORD:
								direction = new Direction(Rose.EST);
								break;
							case SUD:
								direction = new Direction(Rose.OUEST);
								break;
							case EST:
								direction = new Direction(Rose.SUD);
								break;
							default:
								direction = new Direction(Rose.NORD);
						}
				
						return c;
					}else{
						//Pas de possibilitées
						return getCaseActuelle();
					}
				}
			}
		}
	}

	/**Corespondance en String d'un Borné
	 * 
	 * @return String : Caractère corespondant à un Borné en fonction de sa direction
	 */
	@Override
	public String toString(){

		switch(direction.getDirectionRose()){
			case NORD:
				return "^";
			case SUD:
				return "v";
			case EST:
				return ">";
			default:
				return "<";
		}
	}
}