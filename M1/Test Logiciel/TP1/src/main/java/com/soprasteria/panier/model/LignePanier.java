package com.soprasteria.panier.model;

/**
 * La classe LignePanier represente la presence d'un article dans un panier.
 * <P>
 * C'est une classe d'association entre les classes Panier et Article Elle porte
 * le nombre d'exemplaires de l'article present dans le panier.
 * <P>
 * 
 * @see Article
 * @see Panier
 * 
 * @author Olivier
 * @version 2.0
 */
public class LignePanier {
	private Article art;
	private int quantite;

	/**
	 * Initialise une nouvelle ligne de panier.
	 */
	public LignePanier() {
		art = null;
		quantite = 0;
	}

	/**
	 * Renvoie l'article
	 * 
	 * @return l'article
	 */
	public Article lireArt() {
		return art;
	}

	/**
	 * Renvoie le prix HT unitaire de l'article multiplie par la quantite
	 * 
	 * @return le prix total HT
	 */
	public double lirePrixHT() {
		return lireArt( ).lirePrixHT( ) * quantite;
	}

	/**
	 * Renvoie le prix TTC unitaire de l'article multiplie par la quantite
	 * 
	 * @return le prix total TTC
	 */
	public double lirePrixTTC() {
		return lireArt( ).lirePrixTTC( ) * quantite;
	}

	/**
	 * Renvoie le nombre d'exemplaires de l'article considere
	 * 
	 * @return la quantite
	 */
	public int lireQuantite() {
		return quantite;
	}

	/**
	 * fixe l'article
	 * 
	 * @param art
	 *           designe l'article present
	 */
	public void ecrireArt( Article art ) {
		this.art = art;
	}

	/**
	 * Fixe le nombre d'exemplaires de l'article
	 * 
	 * @param quantite
	 *           est le nombre d'exemplaires de l'article
	 */
	public void ecrireQuantite( int quantite ) {
		this.quantite = quantite;
	}

	/**
	 * Renvoie une description textuelle de l'article present dans le panier
	 * 
	 * @return la description de l'article et son nombre d'exemplaires dans le
	 *         panier
	 */
	@Override
	public String toString() {
		return art + "  " + quantite;
	}

	/**
	 * compare la ligne du panier a une autre et retourne vrai en cas d'egalite
	 * 
	 * @param autre
	 *           la ligne de panier a laquelle se comparer
	 * @return vrai quand la ligne du panier a les memes caracteristiques que
	 *         l'autre
	 */
	public boolean equals( LignePanier autre ) {
		if (!art.equals( autre.lireArt( ) ))
			return false;
		if (quantite != autre.lireQuantite( ))
			return false;
		return true;
	}
}
