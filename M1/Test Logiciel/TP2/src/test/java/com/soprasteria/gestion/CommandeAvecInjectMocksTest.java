package com.soprasteria.gestion;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.ArgumentMatchers.anyDouble;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.when;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import com.soprasteria.paiement.RouteurPaiement;
import com.soprasteria.panier.model.Panier;

@ExtendWith(MockitoExtension.class)
public class CommandeAvecInjectMocksTest {

	// TODO : Créer un mock par annotation pour Client, Panier et
	// RouteurPaiement.

	// TODO : Injecter les mocks créés dans commande avec une annotation
	private Commande commande;

	@Mock
	private Client clientMock;

	@Mock
	private RouteurPaiement rpMock;

	@Mock
	private Panier panierMock;

	@InjectMocks
	private Commande commandeMock;

	@Test
	public void testValiderPaiement() {
		// TODO : configurer le mock de RouteurPaiement afin que le test passe
		// l'assertion
		when(rpMock.transaction(anyString(), anyString(), anyString(), anyString(), anyString(), anyDouble())).thenReturn(true);


		// execution
		boolean resultat = commandeMock.validerPaiement("4444555551666666", "01/2017", "345");

		// vérification système testé
		assertThat(resultat).isTrue();
	}

}
