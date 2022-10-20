package com.soprasteria.gestion;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.ArgumentMatchers.anyDouble;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;
import static org.mockito.Mockito.verify;

import static org.mockito.ArgumentMatchers.eq;

import static org.mockito.AdditionalMatchers.eq;


import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import com.soprasteria.paiement.IPaiement;
import com.soprasteria.paiement.exception.PaiementException;
import com.soprasteria.panier.model.Article;
import com.soprasteria.panier.model.Panier;
import com.soprasteria.panier.model.exceptions.MontantTropEleveException;
import com.soprasteria.panier.model.exceptions.QuantiteArticleTropGrandeException;
import com.soprasteria.panier.model.exceptions.TropDeReferencesException;

@ExtendWith(MockitoExtension.class)
public class CommandeAvecMockTest {

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
	public void testValiderPaiementMockInstance() {
		// TODO : instancier un mock de IPaiement et le configurer
		// afin que le test passe l'assertion

		IPaiement ipMock = mock(IPaiement.class);
		when(ipMock.transaction(anyString(), anyString(), anyString(), anyString(), anyString(), anyDouble())).thenReturn(true);

		// preparation
		Commande commande = new Commande(client, pan, ipMock);

		// execution
		boolean resultat = commande.validerPaiement("4444555551666666", "01/2017", "345");

		// verification mock
		// TODO : vérifier l'invocation de la méthode transaction sur le mock
		// avec les paramètres pan=4444555551666666, moisExpiration=01,
		// anneeExpiration=2017, cvv2=345 et le montant attendu selon le panier
		// passé à la commande

		// vérification système testé
		assertThat(resultat).isTrue();

		verify(ipMock).transaction(anyString(), eq("4444555551666666"), eq("01"), eq("2017"), eq("345"),  eq(549.95, 0.01));

	}

	@Mock
	private IPaiement ipMockAnno;

	@Test
	public void testValiderPaiementMockAnnotation() {
		// TODO : instancier un mock de IPaiement et le configurer
		// afin que le test passe l'assertion

		when(ipMockAnno.transaction(anyString(), anyString(), anyString(), anyString(), anyString(), anyDouble())).thenReturn(true);

		// preparation
		Commande commande = new Commande(client, pan, ipMockAnno);

		// execution
		boolean resultat = commande.validerPaiement("4444555551666666", "01/2017", "345");

		// verification mock
		// TODO : vérifier l'invocation de la méthode transaction sur le mock
		// avec les paramètres pan=4444555551666666, moisExpiration=01,
		// anneeExpiration=2017, cvv2=345 et le montant attendu selon le panier
		// passé à la commande

		// vérification système testé
		assertThat(resultat).isTrue();

		verify(ipMockAnno).transaction(anyString(), eq("4444555551666666"), eq("01"), eq("2017"), eq("345"),  eq(549.95, 0.01));

	}

	@Test
	public void testValiderPaiementMockException() {
		// TODO : configurer le mock par annotation (à définir) de IPaiement
		// afin que le test passe l'assertion quel que soit les paramètres
		// d'appel de la dépendance
		when(ipMockAnno.transaction(anyString(), anyString(), anyString(), anyString(), anyString(), anyDouble())).thenThrow(PaiementException.class);

		// preparation
		Commande commande = new Commande(/* params à renseigner */client, pan, ipMockAnno);
		
		// verification
		assertThrows(PaiementException.class, () -> {			
			// execution
			commande.validerPaiement("4444555551666666", "01/2017", "345");
		});

	}

}
