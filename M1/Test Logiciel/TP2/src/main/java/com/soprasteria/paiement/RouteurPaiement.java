package com.soprasteria.paiement;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import org.apache.commons.lang.StringUtils;

import com.soprasteria.paiement.exception.PaiementException;
import com.soprasteria.paiement.impl.PaiementAMEX;
import com.soprasteria.paiement.impl.PaiementMasterCard;
import com.soprasteria.paiement.impl.PaiementVISA;

public class RouteurPaiement implements IPaiement {
	private Map<String, IPaiement> mapRouteurReseaux = new HashMap<>();

	public RouteurPaiement() {
		initRouteurReseaux();
	}

	/**
	 * Enregistre les réseaux supportés pour effectuer des transactions.
	 */
	private void initRouteurReseaux() {
		mapRouteurReseaux.put("4", new PaiementVISA());
		mapRouteurReseaux.put("51", new PaiementMasterCard());
		mapRouteurReseaux.put("34", new PaiementAMEX());
	}

	/**
	 * Renvoie l'implémentation du réseaux correspondant au PAN
	 * 
	 * @param pan
	 *            Numéro de carte
	 * @return Implémentation du réseau
	 * @throws PaiementException
	 *             si le réseau n'est pas supporté.
	 */
	private IPaiement getPaiementPourPAN(String pan) {
		for (Entry<String, IPaiement> entry : mapRouteurReseaux.entrySet()) {
			if (StringUtils.startsWith(pan, entry.getKey())) {
				return entry.getValue();
			}
		}
		throw new PaiementException("Le réseau associé à la carte n'est pas supporté.");
	}

	public void ping() {
		// fake method
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.soprasteria.paiement.IPaiement#transaction(java.lang.String,
	 * java.lang.String, java.lang.String, java.lang.String, java.lang.String,
	 * double)
	 */
	@Override
	public boolean transaction(String refCommercant, String pan, String moisExpiration, String anneeExpiration,
			String cvv2, double montant) {
		IPaiement paiement = getPaiementPourPAN(pan);
		return paiement.transaction(refCommercant, pan, moisExpiration, anneeExpiration, cvv2, montant);
	}

}
