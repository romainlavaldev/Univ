public class Generateur {
	private Filtre premierFiltre;

	public Generateur(){
		premierFiltre = new Filtre(2);
	}

	public String toString(){
		return "\nLa liste des Filtres Générés est :\n" + premierFiltre.toString();
	}

	public void lanceToi(int nombre){
		for (int i=3; i<=nombre; i++){
			premierFiltre.aToiDeTraiter(i);
		}
	}
}