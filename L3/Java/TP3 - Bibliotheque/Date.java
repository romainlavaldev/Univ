/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 19 13:33:10 CET 2022
*
*/
public class Date implements Comparable{
	private int jour;
	private int mois;
	private int annee;

	public Date(int j, int m, int a) throws InvalidDateException{
		jour = j;
		mois = m;
		annee = a;

		if (!dateBonne()){
			throw new InvalidDateException("Can't create date : " + jour + " " + mois + " " + annee);
		}
	}

	/**Verifie si la date est correcte
	 * 
	 * @return boolean
	 */
	private boolean dateBonne(){
		return !((jour <= 0 || jour > 31) || (mois <= 0 || mois > 12));
	}

	public int getAnnee(){
		return annee;
	}

	@Override
	public int compareTo(Object o){
		Date oDate;
		if (o instanceof Date){ 
			oDate = (Date)o;
		}
		else{
			throw new ClassCastException("Can't compare Date with a non-Date obj");
		}

		if(this.annee > oDate.annee){
			return 1;
		}else if (this.annee < oDate.annee){
			return -1;
		}else{
			if (this.mois > oDate.mois){
				return 1;
			}else if (this.mois < oDate.mois){
				return -1;
			}else{
				if (this.jour > oDate.jour){
					return 1;
				}else if (this.jour < oDate.jour){
					return -1;
				}else{
					return 0;
				}
			}
		}
	}

	@Override
	public String toString(){
		return jour+" "+mois+" "+annee;
	}
}