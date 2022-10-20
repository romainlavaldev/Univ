package com.soprasteria.gestion;

import static org.assertj.core.api.Assertions.assertThat;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import com.soprasteria.paiement.IPaiement;
import com.soprasteria.panier.model.Article;
import com.soprasteria.panier.model.Panier;
import com.soprasteria.panier.model.exceptions.MontantTropEleveException;
import com.soprasteria.panier.model.exceptions.QuantiteArticleTropGrandeException;
import com.soprasteria.panier.model.exceptions.TropDeReferencesException;

public class CommandeAvecStubTest {
	private static Client client;
	private static Panier pan;
	private static Article art1;

	@BeforeAll
	public static void init()
			throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException {
		// Panier
		pan = new Panier();
		art1 = new Article(100.00, "REF001", "LIBELLE01", 9.99);
		pan.ajouterArticle(art1, 5);
		client = new Client();
	}

	@Test
	public void testValiderPaiement() {
		// TODO : créer un stub de IPaiement avec une classe anonyme permettant
		// à l'assertion du test de passer.

		IPaiement ip = new IPaiement() {

			@Override
			public boolean transaction(String refCommercant, String pan, String moisExpiration, String anneeExpiration,
					String cvv2, double montant) {
				
				return true;
			}
			
		};

		// preparation
		Commande commande = new Commande(client, pan, ip);

		// execution
		boolean resultat = commande.validerPaiement("4444555551666666", "01/2017", "345");

		// verification
		assertThat(resultat).isTrue();
	}
}
