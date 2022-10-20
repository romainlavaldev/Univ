package com.soprasteria.panier.model;

import java.util.Date;
import java.util.HashMap;

import com.soprasteria.panier.model.exceptions.ArticleInexistantException;
import com.soprasteria.panier.model.exceptions.MontantTropEleveException;
import com.soprasteria.panier.model.exceptions.QuantiteArticleTropGrandeException;
import com.soprasteria.panier.model.exceptions.TropDeReferencesException;
import com.soprasteria.tools.OutilsChaine;

/**
 * La classe Panier repr�sente un panier d'achats.
 * <P>
 * Il est possible d'ajouter et retirer des articles, changer les quantit�s
 * des articles d�j� pr�sents, vider le panier de tous les articles,
 * imprimer un ticket tenant compte ou non d'une remise param�trable �
 * partir d'un seuil param�trable
 * 
 * Voir Document des Exigences
 * <P>
 * 
 * @see Article
 * 
 * @author Olivier
 * @version 2.0
 */
public class Panier {
	/**
	 * Les articles present dans le panier
	 */
	private final HashMap<String, LignePanier> contenuPanier = new HashMap<String, LignePanier>( );
	private boolean remiseActive = false;
	private double pourcentageRemise = 0.00;
	private double montantSeuil = 0.00;

	/**
	 * Permet d'ajouter un nombre d'exemplaire donn� d'un article pr�sent ou
	 * non dans le panier
	 * 
	 * @param art
	 *           repr�sente l'article � ajouter au panier
	 * @param qte
	 *           est le nombre d'exemplaires � ajouter de cet article
	 */
	public void ajouterArticle( Article art , int qte )
	      throws TropDeReferencesException, QuantiteArticleTropGrandeException,
	      MontantTropEleveException {
		// si art appartient a la liste d'articles
		final double prixActuel = prixHTPanier( );
		final double supplement = qte * art.lirePrixHT( );
		if (!articleEstDansPanier( art.lireReference( ) )) {
			if (nbReferences( ) < 5) {
				if (qte < 10) {
					if (prixActuel + supplement <= 1000) {
						final LignePanier lp = new LignePanier( );
						lp.ecrireArt( art );
						lp.ecrireQuantite( qte );
						contenuPanier.put( art.lireReference( ) , lp );
					} else
						throw new MontantTropEleveException( "L'ajout de " + qte
						      + " " + art.lireReference( )
						      + " au prix unitaire HT de " + art.lirePrixHT( )
						      + " � un panier de " + prixActuel
						      + " HT d�passe 1000." );
				} else {
					throw new QuantiteArticleTropGrandeException(
					      "Le nombre d'exemplaires (" + qte
					            + ") de l'article de r�f�rence "
					            + art.lireReference( ) + " d�passe 10." );
				}
			} else {
				throw new TropDeReferencesException(
				      "Article de r�f�rence "
				            + art.lireReference( )
				            + " impossible � ajouter dans un panier contenant d�j� 5 r�f�rences" );
			}
		} else {
			final String ref = art.lireReference( );
			final int deja = lireLignePanier( ref ).lireQuantite( );
			if (qte + deja < 10) {
				if (prixActuel + supplement <= 1000) {
					final LignePanier lp = lireLignePanier( ref );
					lp.ecrireQuantite( lp.lireQuantite( ) + qte );
				} else
					throw new MontantTropEleveException( "L'ajout de " + qte + " "
					      + art.lireReference( ) + " au prix unitaire HT de "
					      + art.lirePrixHT( ) + " � un panier de " + prixActuel
					      + " HT d�passe 1000." );
			} else {
				throw new QuantiteArticleTropGrandeException(
				      "L'article de r�f�rence " + ref + " est pr�sent en "
				            + deja + " exemplaires. Il ne peut �tre ajout� en "
				            + qte + " exemplaires dans le panier." );
			}
		}
	}

	/**
	 * Renseigne sur la pr�sence dans le panier de l'article identifi� par sa
	 * r�f�rence
	 * 
	 * @param ref
	 *           est la r�f�rence de l'article recherch�
	 * @return vrai si l'article consid�r� est pr�sent dans le panier, faux
	 *         dans le cas contraire
	 */
	private boolean articleEstDansPanier( String ref ) {
		return contenuPanier.containsKey( ref );
	}

	/**
	 * Fixe le nombre d'exemplaires de l'article identifi� par sa r�f�rence
	 * 
	 * @param ref
	 *           est la r�f�rence de l'article consid�r�
	 * @param qte
	 *           est le nouveau nombre d'exemplaires pr�sents dans le panier de
	 *           l'article consid�r�
	 */
	public void modifierQuantiteArticle( String ref , int qte )
	      throws ArticleInexistantException, QuantiteArticleTropGrandeException,
	      MontantTropEleveException {
		final LignePanier lp = lireLignePanier( ref );
		if (lp != null) {
			if (qte < 10) {
				final double prixActuel = prixHTPanier( );
				final Article art = lp.lireArt( );
				final double supplement = qte * art.lirePrixHT( );
				if (prixActuel + supplement <= 1000) {
					lp.ecrireQuantite( qte );
				} else
					throw new MontantTropEleveException(
					      "Faire passer le nombre d'exemplaires de "
					            + art.lireReference( )
					            + " � "
					            + qte
					            + " conduit � un panier de prix HT sup�rieur � 1000." );
			} else
				throw new QuantiteArticleTropGrandeException(
				      "Le nombre d'exemplaires � modifier (" + qte
				            + ") de l'article de r�f�rence " + ref
				            + " d�passe 10." );
		} else
			throw new ArticleInexistantException( "Reference " + ref
			      + " inexistante dans le panier" );
	}

	/**
	 * Renvoie le nombre d'exemplaires dans le panier d'un article identifi�
	 * par sa r�f�rence
	 * 
	 * @param ref
	 *           est la r�f�rence de l'article recherch�
	 * @return le nombre d'exemplaires pr�sents de l'article consid�r�
	 */
	public int nbArticles( String ref ) {
		if (!articleEstDansPanier( ref )) {
			return 0;
		} else {
			return lireLignePanier( ref ).lireQuantite( );
		}
	}

	/**
	 * Renvoie le nombre d'articles diff�rents pr�sents dans le panier
	 * 
	 * @return le nombre d'articles dans le panier
	 */
	public int nbReferences() {
		return contenuPanier.size( );
	}

	/**
	 * Renvoie la ligne du panier qui �voque une article identifi� par sa
	 * r�f�rence
	 * 
	 * @param ref
	 *           est la r�f�rence de l'article consid�r�
	 * @return une ligne de panier
	 */
	private LignePanier lireLignePanier( String ref ) {
		return contenuPanier.get( ref );
	}

	/**
	 * Calcule et renvoie le prix hors taxe du panier
	 * 
	 * @return le prix total HT du panier
	 */
	public double prixHTPanier() {
		double prixHT = 0.0d;
		for (final LignePanier lp : contenuPanier.values( )) {
			prixHT += lp.lirePrixHT( );
		}
		return prixHT;
	}

	/**
	 * Calcule et renvoie le prix toutes taxes comprises du panier
	 * 
	 * @return le prix total TTC du panier
	 */
	public double prixTTCPanier() {
		double prixTTC = 0.0d;
		for (final LignePanier lp : contenuPanier.values( )) {
			prixTTC += lp.lirePrixTTC( );
		}
		return prixTTC;
	}

	/**
	 * Retire du panier un article identifi� par sa r�f�rence. Si l'article
	 * consid�r� n'est pas pr�sent, une exception
	 * ArticleInexistantException est lev�e
	 * 
	 * @param ref
	 *           est la r�f�rence de l'article consid�r�
	 */
	public void retirerArticle( String ref ) throws ArticleInexistantException {
		if (articleEstDansPanier( ref )) {
			contenuPanier.remove( ref );
		} else
			throw new ArticleInexistantException( "Reference " + ref
			      + " inexistante dans le panier" );
	}

	/**
	 * Renvoie une description textuelle du panier
	 * 
	 * @return la descrition du panier
	 */
	@Override
	public String toString() {
		String strPanier = "";
		for (final LignePanier lp : contenuPanier.values( )) {
			strPanier += lp.toString( ) + "\n";
		}
		strPanier += "Prix TTC " + prixTTCPanier( ) + "\n";
		strPanier += "Prix HT " + prixHTPanier( ) + "\n";
		strPanier += "Remise " + montantRemise( ) + "\n";
		return strPanier;
	}

	/**
	 * Vide le panier
	 */
	public void vider() {
		HashMap<String, LignePanier> cloneContenu = (HashMap<String, LignePanier>) contenuPanier.clone();
		int i = 0;
		for (String ligne: cloneContenu.keySet()) {
			if (i > 0) {
				contenuPanier.remove(ligne);
			}
			i++;
		}
	}

	/**
	 * Renseigne sur l'applicabilit� de la remise
	 * 
	 * @return vrai si la remise est pratiqu�e
	 */
	public boolean remiseActive() {
		return remiseActive;
	}

	/**
	 * Renvoie le pourcentage de remise applicable au panier
	 * 
	 * @return le pourcentage de remise (dd.dd)
	 */
	public double lirePourcentageRemise() {
		return pourcentageRemise;
	}

	/**
	 * Renvoie le montant � partir duquel s'applique la remise
	 * 
	 * @return le montant seuil de d�clenchement du calcul de la remise
	 */
	public double lireMontantSeuil() {
		return montantSeuil;
	}

	/**
	 * Active ou d�sactive l'application de la remise
	 * 
	 * @param remiseActive
	 *           indique si le calcul de la remise s'applique (vrai) ou non
	 *           (faux)
	 */
	public void ecrireRemiseActive( boolean remiseActive ) {
		this.remiseActive = remiseActive;
	}

	/**
	 * Fixe le pourcentage utilis� pour le calcul de la remise
	 * 
	 * @param pourcentageRemise
	 *           est le pourcentage � utiliser pour le calcul de la remise
	 */
	public void ecrirePourcentageRemise( double pourcentageRemise ) {
		this.pourcentageRemise = pourcentageRemise;
	}

	/**
	 * Fixe le montant � partir duquel s'applique le calcul de la remise
	 * 
	 * @param montantSeuil
	 *           est le montant � partir duquel une remise est d�duite du
	 *           prix du panier
	 */
	public void ecrireMontantSeuil( double montantSeuil ) {
		this.montantSeuil = montantSeuil;
	}

	/**
	 * Calcule et renvoie le montant de la remise
	 * 
	 * @return le montant de la remise applicable au panier
	 */
	public double montantRemise() {
		if (remiseActive) {
			double ttc = prixTTCPanier( );
			if (ttc > montantSeuil)
				return ttc * pourcentageRemise / 100;
		}
		return 0.00;
	}

	/**
	 * Renvoie une chaine de caract�re repr�sentant le Ticket
	 * 
	 * @return le ticket sous forme de String
	 */
	public String lireTicket() {
		Date laDate = new Date( );
		String sDate = OutilsChaine.formatDateFrance.format( laDate );
		String sHeure = OutilsChaine.formatHeure.format( laDate );
		String ticket = "------------------------------------" + "\n"
		      + "| LE BEAU PANIER                   |" + "\n" + "| " + sDate
		      + " - " + sHeure + "               |" + "\n"
		      + "------------------------------------" + "\n"
		      + "| LIBELLE      PU_HT   QTE     TTC |" + "\n"
		      + "|                                  |" + "\n";
		// On boucle sur toutes les LignePanier
		String ligne;
		for (LignePanier lp : contenuPanier.values( )) {
			ligne = "| ";
			String libelle = lp.lireArt( ).lireLibelle( );
			ligne += OutilsChaine.formater( libelle , 10 , 1 , ' ' );
			String prix = OutilsChaine.formatMonnaie.format( lp.lireArt( )
			      .lirePrixHT( ) );
			ligne += OutilsChaine.formater( prix , 8 , 0 , ' ' );
			String qte = "" + lp.lireQuantite( );
			ligne += OutilsChaine.formater( qte , 6 , 0 , ' ' );
			prix = OutilsChaine.formatMonnaie.format( lp.lirePrixTTC( ) );
			ligne += OutilsChaine.formater( prix , 8 , 0 , ' ' );
			ligne += " |" + "\n";
			ticket += ligne;
		}
		// On termine les lignes
		ticket += "|                                  |" + "\n";
		ticket += "------------------------------------" + "\n";
		String total = OutilsChaine.formatMonnaie.format( this.prixTTCPanier( ) );
		total = OutilsChaine.formater( total , 27 , 0 , ' ' );
		ticket += "| TOTAL" + total + " |\n";
		ticket += "------------------------------------" + "\n";
		String remise = OutilsChaine.formatMonnaie.format( this.montantRemise( ) );
		String pct = OutilsChaine.formatMonnaie.format( this
		      .lirePourcentageRemise( ) );
		remise = OutilsChaine.formater( remise , 24 - pct.length( ) , 0 , ' ' );
		ticket += "| REMISE " + pct + "%" + remise + " |\n";
		ticket += "------------------------------------" + "\n";
		String TVA = OutilsChaine.formatMonnaie.format( this.prixTTCPanier( )
		      - this.prixHTPanier( ) );
		TVA = OutilsChaine.formater( TVA , 29 , 0 , ' ' );
		ticket += "| TVA" + TVA + " |\n";
		ticket += "------------------------------------" + "\n";
		String NET = OutilsChaine.formatMonnaie.format( this.prixTTCPanier( )
		      - this.montantRemise( ) );
		NET = OutilsChaine.formater( NET , 21 , 0 , ' ' );
		ticket += "| NET A PAYER" + NET + " |\n";
		ticket += "------------------------------------" + "\n";
		ticket += "| Les prix s'entendent en Euro     |" + "\n";
		ticket += "------------------------------------";
		return ticket;
	}

	/**
	 * compare le panier � un autre et retourne vrai en cas d'�galit� des
	 * contenus
	 * 
	 * @param autre
	 *           le panier auquel se comparer
	 * @return vrai quand le panier a le m�me contenu que l'autre
	 */
	public boolean equals( Panier autre ) {
		LignePanier lpAutre;
		for (final LignePanier lp : contenuPanier.values( )) {
			lpAutre = autre.lireLignePanier( lp.lireArt( ).lireReference( ) );
			if (lpAutre == null)
				return false;
			if (!lp.equals( lpAutre ))
				return false;
		}
		return true;
	}

	public static void main( String[] args ) {
		
		Panier pan = new Panier( );
		Article art1 = new Article( 100.00 , "REF001" , "LIBELLE01" , 9.99 );
		Article art2 = new Article( 100.00 , "REF002" , "LIBELLE02" , 10.00 );
		String ref1 = art1.lireReference( );
		String ref2 = art2.lireReference( );
		try {
			System.out.println( "DEMO PANIER " );
			// On ajoute 3 art1
			pan.ajouterArticle( art1 , 3 );
			// On ajoute 2 art1
			pan.ajouterArticle( art1 , 2 );
			// On ajoute 5 art2
			System.out.println( pan.lireTicket( ) );
			pan.ajouterArticle( art2 , 5 );
			System.out.println( pan.lireTicket( ) );
			// on retire tous les art1
			pan.retirerArticle( ref1 );
			// On change la quantit� des ref2 � 1
			pan.modifierQuantiteArticle( ref2 , 1 );
			System.out.println( pan.lireTicket( ) );
			// On fixe une remise de 10% � partir de 120
			pan.ecrireRemiseActive( true );
			pan.ecrirePourcentageRemise( 10 );
			pan.ecrireMontantSeuil( 120 );
			System.out.println( pan.lireTicket( ) );
			// On fixe le seuil de la remise � 100
			pan.ecrireMontantSeuil( 100 );
			System.out.println( pan.lireTicket( ) );
			// On vide le panier
			pan.vider( );
		} catch (Exception e) {
		}
		
	}
}
