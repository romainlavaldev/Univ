public class Filtre {
	private int valeur;
	private Filtre suivant;

	public Filtre(int v){
		valeur = v;
		suivant = null;
	}

	public void aToiDeTraiter(int nombre){
		if (nombre == valeur){
			System.out.println(nombre + " est premier");
		}else{
			if (nombre % valeur == 0){
				System.out.println(nombre + " n'est pas premier");
			}else{
				if (suivant != null){
					suivant.aToiDeTraiter(nombre);
				}else{
					System.out.println(nombre + " est premier");
					suivant = new Filtre(nombre);
				}
			}
		}
	}

	public String toString(){
		String res = Integer.toString(valeur) + ":";

		if (suivant != null){
			res += suivant.toString();
		}
		return res;
	}
}