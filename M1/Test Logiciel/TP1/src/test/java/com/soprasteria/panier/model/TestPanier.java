package com.soprasteria.panier.model;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertLinesMatch;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.assertj.core.api.JUnitBDDSoftAssertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import com.soprasteria.panier.model.exceptions.ArticleInexistantException;
import com.soprasteria.panier.model.exceptions.MontantTropEleveException;
import com.soprasteria.panier.model.exceptions.QuantiteArticleTropGrandeException;
import com.soprasteria.panier.model.exceptions.TropDeReferencesException;
import com.soprasteria.tools.OutilsChaine;

import java.util.ArrayList;
import java.util.Date;


/**
 * Classe de tests unitaires de la classe Panier
 */
public class TestPanier {
	/**
	 * Les donnees de test
	 */
	static Panier pan;
	static Article art1, art2;
	static ArrayList<Article> listeArticle;

	/**
	 * Initialisation des donnees de test avant l'ensemble des tests
	 */
	@BeforeAll
	public static void initTests() {
		pan = new Panier();
		art1 = new Article(100.00, "REF001", "LIBELLE01", 9.99);
		art2 = new Article(100.00, "REF002", "LIBELLE02", 10.00);
		listeArticle = new ArrayList<Article>();
		for (int i = 0; i < 7; i++)
			listeArticle.add(new Article(100.00, "REF00" + i, "LIB" + i, 10.00));
	}

	/**
	 * Remise a zero du panier avant chaque test
	 */
	@BeforeEach
	public void avantTest() {
		pan.vider();
		pan.ecrireRemiseActive(false);

	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_01
	 * @throws MontantTropEleveException
	 * @throws QuantiteArticleTropGrandeException
	 * @throws TropDeReferencesException
	 */
	@Test
	public void testAjouterArticle() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ajouterArticle(art1, 1);

		assertEquals(1, pan.nbArticles(art1.lireReference()));
	}

	@Test
	public void testRetirerArticle() throws ArticleInexistantException, TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		testAjouterArticle();
		
		pan.retirerArticle(art1.lireReference());

		assertEquals(0, pan.nbArticles(art1.lireReference()));
	}


	@Test
	public void testAjouterPlusieursArticle() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException {
		pan.ajouterArticle(art1, 8);

		assertEquals(8, pan.nbArticles(art1.lireReference()));
	}

	@Test
	public void testModifierQuantiteChaqueArticle() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException, ArticleInexistantException{
		pan.ajouterArticle(art1, 7);
		pan.ajouterArticle(art2, 1);

		pan.modifierQuantiteArticle(art1.lireReference(), 8);
		pan.modifierQuantiteArticle(art2.lireReference(), 3);

		assertEquals(5, pan.nbArticles(art1.lireReference()));
		assertEquals(3, pan.nbArticles(art2.lireReference()));
	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_02
	 * @throws MontantTropEleveException
	 * @throws QuantiteArticleTropGrandeException
	 * 
	 * @throws TropDeReferencesException
	 */
	@Test
	public void testViderPanier() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ajouterArticle(art1, 3);
		pan.ajouterArticle(art2, 2);

		pan.vider();

		assertEquals(0, pan.nbReferences());
	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_03
	 */
	@Test
	public void testCreerPanier(){
		assertNotNull(pan);
	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_04
	 * 
	 * @throws TropDeReferencesException
	 */

	@Test
	public void testAjouterReferenceEnTrop() throws TropDeReferencesException {
		// code exemple
		assertThrows(TropDeReferencesException.class, () -> {
			for (Article article : listeArticle) {
				pan.ajouterArticle(article, 1);
			}
		});
	}

	@Test
	public void testAjouterReferencePile() throws TropDeReferencesException {
		// code exemple
		assertDoesNotThrow(() -> {
			for (Article article : listeArticle.subList(0, 5)) {
				pan.ajouterArticle(article, 1);
			}
		});
	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_05
	 */
	@Test
	public void testAjouterArticleEnTrop() throws TropDeReferencesException {
		// code exemple
		assertThrows(QuantiteArticleTropGrandeException.class, () -> {
			pan.ajouterArticle(art1, 11);
		});
	}

	@Test
	public void testAjouterArticlePile() throws TropDeReferencesException {
		// code exemple
		assertDoesNotThrow(() -> {
			pan.ajouterArticle(art1, 10);
		});
	}

	/**
	 * Test unitaire couvrant l'exigence EXG_PAN_06
	 */
	@Test
	public void testExcederPrixHT(){
		Article articleTresCher = new Article(580, "REF001", "LIVELLE01", 20);
		
		assertThrows(MontantTropEleveException.class, () -> {
			pan.ajouterArticle(articleTresCher, 3);
		});
	}

	/**
	 * Tests unitaires couvrant l'exigence EXG_REMISE_01
	 */
	@Test
	public void testParametrerRemise(){
		pan.ecrireMontantSeuil(666);
		pan.ecrirePourcentageRemise(17);

		assertEquals(666, pan.lireMontantSeuil());
		assertEquals(17, pan.lirePourcentageRemise());
	}

	@Test
	public void testDeclanchementRemise() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ecrireRemiseActive(true);
		pan.ecrireMontantSeuil(10);
		pan.ecrirePourcentageRemise(17);

		Article articleDeclancheur = new Article(800, "REF001", "LIVELLE01", 20);
		pan.ajouterArticle(articleDeclancheur, 1);
		
		assertTrue(pan.remiseActive());
	}

	@Test
	public void testMontantRemise() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ecrireRemiseActive(true);
		pan.ecrireMontantSeuil(50);
		pan.ecrirePourcentageRemise(10);

		Article articleDeclancheur = new Article(800, "REF001", "LIVELLE01", 0);
		pan.ajouterArticle(articleDeclancheur, 1);
		
		assertEquals(80, pan.montantRemise(), .01);
	}

	@Test
	public void testRemiseTicket() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ecrireRemiseActive(true);
		pan.ecrireMontantSeuil(50);
		pan.ecrirePourcentageRemise(10);

		Article articleTest1 = new Article(100, "REF001", "LIVELLE01", 10);
		Article articleTest2 = new Article(200, "REF001", "LIVELLE01", 10);
		
		pan.ajouterArticle(articleTest1, 2);
		pan.ajouterArticle(articleTest2, 1);

	}

	/**
	 * Tests unitaires couvrant l'exigence EXG_TICKET_01
	 * @throws MontantTropEleveException
	 * @throws QuantiteArticleTropGrandeException
	 * @throws TropDeReferencesException
	 */
	@Test
	public void testTicketSansRemise() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{

		Article articleTest1 = new Article(100, "REF001", "LIBELLE01", 10);
		Article articleTest2 = new Article(200, "REF002", "LIBELLE02", 10);
		
		pan.ajouterArticle(articleTest1, 2);
		pan.ajouterArticle(articleTest2, 1);

		Date laDate = new Date();
		String sDate = OutilsChaine.formatDateFrance.format(laDate);
		String sHeure = OutilsChaine.formatHeure.format(laDate);

		String ticketParfait = "------------------------------------\n| LE BEAU PANIER                   |\n| "+sDate+" - "+sHeure+"               |\n------------------------------------\n| LIBELLE      PU_HT   QTE     TTC |\n|                                  |\n| LIBELLE01   100,00     2  220,00 |\n| LIBELLE02   200,00     1  220,00 |\n|                                  |\n------------------------------------\n| TOTAL                     440,00 |\n------------------------------------\n| REMISE 0,00%                0,00 |\n------------------------------------\n| TVA                        40,00 |\n------------------------------------\n| NET A PAYER               440,00 |\n------------------------------------\n| Les prix s'entendent en Euro     |\n------------------------------------";
		
		assertEquals(ticketParfait, pan.lireTicket());

	}

	@Test
	public void testTicketAvecRemise() throws TropDeReferencesException, QuantiteArticleTropGrandeException, MontantTropEleveException{
		pan.ecrireMontantSeuil(50);
		pan.ecrirePourcentageRemise(10);
		pan.ecrireRemiseActive(true);

		Article articleTest1 = new Article(100, "REF001", "LIBELLE01", 10);
		Article articleTest2 = new Article(200, "REF002", "LIBELLE02", 10);
		
		pan.ajouterArticle(articleTest1, 2);
		pan.ajouterArticle(articleTest2, 1);

		Date laDate = new Date();
		String sDate = OutilsChaine.formatDateFrance.format(laDate);
		String sHeure = OutilsChaine.formatHeure.format(laDate);

		String ticketParfait = "------------------------------------\n| LE BEAU PANIER                   |\n| "+sDate+" - "+sHeure+"               |\n------------------------------------\n| LIBELLE      PU_HT   QTE     TTC |\n|                                  |\n| LIBELLE01   100,00     2  220,00 |\n| LIBELLE02   200,00     1  220,00 |\n|                                  |\n------------------------------------\n| TOTAL                     440,00 |\n------------------------------------\n| REMISE 10,00%              44,00 |\n------------------------------------\n| TVA                        40,00 |\n------------------------------------\n| NET A PAYER               396,00 |\n------------------------------------\n| Les prix s'entendent en Euro     |\n------------------------------------";
		
		assertEquals(ticketParfait, pan.lireTicket());

	}
}
