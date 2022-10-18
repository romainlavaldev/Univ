package com.soprasteria.panier.model;

/**
 * La classe Article represente un article.
 * <P>
 * Un article est decrit par sa reference, son libelle, son prix hors taxe, le
 * taux de TVA applicable. Un article peut etre ajoute a un panier.
 * <P>
 * 
 * @see Panier
 * @author : Olivier
 * @version : 2.5
 */
public class Article {
	private String libelle;
	private double prixHT;
	private String reference;
	private double tva;
	private boolean perissable;

	/**
	 * Initialise un nouvel article.
	 */
	public Article() {
		this.prixHT = 0;
		this.reference = null;
		this.libelle = null;
		this.tva = 0;
		this.perissable = false;
	}

	/**
	 * Initialise un article nouvellement cree.
	 * 
	 * @param prixHT
	 *           ext le prix unitaire hors taxe de l'article
	 * @param reference
	 *           est la reference de l'article
	 * @param libelle
	 *           est la designation de l'article
	 * @param tva
	 *           est le taux de TVA qui s'applique au prix de l'article
	 */
	public Article( double prixHT , String reference , String libelle ,
	      double tva ) {
		this.prixHT = prixHT;
		this.reference = reference;
		this.libelle = libelle;
		this.tva = tva;
		this.perissable = false;
	}

	/**
	 * Initialise un article nouvellement cree.
	 * 
	 * @param prixHT
	 *           ext le prix unitaire hors taxe de l'article
	 * @param reference
	 *           est la reference de l'article
	 * @param libelle
	 *           est la designation de l'article
	 * @param tva
	 *           est le taux de TVA qui s'applique au prix de l'article
	 * @param perissable
	 *           indique si l'article est perissable
	 */
	public Article( double prixHT , String reference , String libelle ,
	      double tva , boolean perissable ) {
		this.prixHT = prixHT;
		this.reference = reference;
		this.libelle = libelle;
		this.tva = tva;
		this.perissable = perissable;
	}

	/**
	 * Renvoie le libelle de l'article
	 * 
	 * @return le libelle de l'article
	 */
	public String lireLibelle() {
		return libelle;
	}

	/**
	 * Renvoie le prix hors taxe de l'article
	 * 
	 * @return le prix HT de l'article
	 */
	public double lirePrixHT() {
		return prixHT;
	}

	/**
	 * Calcule le prix toutes taxes comprises et le renvoie.
	 * 
	 * @return le prix TTC de l'article
	 */
	public double lirePrixTTC() {
		return prixHT + prixHT * (tva / 100);
	}

	/**
	 * Renvoie la reference de l'article
	 * 
	 * @return la reference de l'article
	 */
	public String lireReference() {
		return reference;
	}

	/**
	 * Renvoie le taux de taxe sur la valeur ajout�e applicable au prix hors taxe
	 * de l'article
	 * 
	 * @return le taux de TVA pour cet article
	 */
	public double lireTva() {
		return tva;
	}

	/**
	 * Renvoie le caractere perissable de l'article
	 * 
	 * @return vrai si l'article est perissable, faux dans le cas contraire
	 */
	public boolean lirePerissable() {
		return perissable;
	}

	/**
	 * Fixe le nouveau libelle de l'article
	 * 
	 * @param libelle
	 *           est le nouveau libelle de l'article
	 */
	public void ecrireLibelle( String libelle ) {
		this.libelle = libelle;
	}

	/**
	 * Fixe le nouveau prix hors taxe de l'article
	 * 
	 * @param prixHT
	 *           est le nouveau prix hors taxe de l'article
	 */
	public void ecrirePrixHT( double prixHT ) {
		this.prixHT = prixHT;
	}

	/**
	 * Fixe la nouvelle reference de l'article
	 * 
	 * @param reference
	 *           est la nouvelle reference de l'article
	 */
	public void ecrireReference( String reference ) {
		this.reference = reference;
	}

	/**
	 * Fixe le nouveau taux de taxe sur la valeur ajoutee applicable au prix hors
	 * taxe de l'article
	 * 
	 * @param tva
	 *           est le nouveau taux de TVA pour l'article
	 */
	public void ecrireTva( double tva ) {
		this.tva = tva;
	}

	/**
	 * Fixe le caractere perissable de l'article
	 * 
	 * @param perissable
	 *           est la nouvelle valeur du caractere perissable de l'article (
	 *           vrai si l'article est perissable)
	 */
	public void ecrirePerissable( boolean perissable ) {
		this.perissable = perissable;
	}

	/**
	 * Renvoie une description textuelle de l'article
	 * 
	 * @return la description de l'article
	 */
	@Override
	public String toString() {
		return lireReference( ) + "  " + lireLibelle( ) + "  " + lirePrixHT( )
		      + "  " + lireTva( ) + " perissable:"
		      + (lirePerissable( ) ? "oui" : "non");
	}

	/**
	 * compare l'article a un autre et retourne vrai en cas d'egalite
	 * 
	 * @param autre
	 *           l'article auquel se comparer
	 * @return vrai quand l'article a les memes caracteristiques que l'autre
	 */
	public boolean equals( Article autre ) {
		if (!reference.equals( autre.lireReference( ) ))
			return false;
		if (!libelle.equals( autre.lireLibelle( ) ))
			return false;
		if (prixHT != autre.lirePrixHT( ))
			return false;
		if (tva != autre.lireTva( ))
			return false;
		if (perissable != autre.lirePerissable( ))
			return false;
		return true;
	}
}
