

public class Droite {
	//a et b represente y = ax + b
	/**
	 * Class Droite
	 * 
	 * @param a Pente de la droite
	 * @param b Ordonnée à l'origine
	 */
	private double a;
	private double b;


	//Constructor
	/**
	 * Constructor
	 * 
	 * @params deux points de la droite
	 */
	public Droite(Point p1, Point p2){
		//Calcul de la pente a
		a = (p2.getY()-p1.getY()) / (p2.getX()-p1.getX());

		//Calcul de l'ordonné à l'orgine b
		b = p1.getY() - a * p1.getX();
	}

	//Class Methods


	//Methods
	public double getPente(){
		return a;
	}

	public void setPente(double p){
		a = p;
	}

	public double getOrigine(){
		return b;
	}

	public void setOrigine(double o){
		b = o;
	}

	/**
	 * Verifie si la droite est parrallele à une autre droite
	 * 
	 * @param d Droite
	 * @return boolean
	 * 
	 */
	public boolean estParallele(Droite d){
		return this.getPente() == d.getPente();
	}

	/**
	 * Renvoi le point qui appartient au deux droites
	 * 
	 * @param d Droite
	 * @return le Point qui coupe les deux droites
	 */
	public Point intersection(Droite d) throws DroiteParalleleException{
		Point inter;
		//Pas de solution si parallele
		if (!this.estParallele(d)){
			double x = (d.getOrigine() - this.getOrigine()) / (this.getPente() - d.getPente());
			double y = this.getPente() * x + this.getOrigine();

			inter = new Point(x,y);
		}else{
			throw new DroiteParalleleException("Impossible de calculer l'intersection de deux droites paralleles");
		}
		return inter;
	}
	
	@Override
	public String toString(){
		return String.format("Droite : y = %.2fx + %.2f", a, b);
	}

	
	
}