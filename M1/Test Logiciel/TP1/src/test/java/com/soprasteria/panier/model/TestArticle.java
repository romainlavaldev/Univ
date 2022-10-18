package com.soprasteria.panier.model;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import com.soprasteria.panier.model.Article;

/**
 * Classe de tests unitaires de la classe Article
 */
public class TestArticle {
	private static Article art;

	@BeforeAll
	public static void initTests() {
		art = new Article( 100.00 , "ref1" , "lib1" , 19.6 );
	}

	/**
	 * Test unitaire couvrant les exigences EXG_ART_01 , EXG_ART_02
	 */
	@Test
	public void testPrixTTCArticle() {
		assertNotNull(art);

		assertNotNull(art.lirePrixHT());
		assertNotNull(art.lireLibelle());
		assertNotNull(art.lirePrixTTC());
	}

}
