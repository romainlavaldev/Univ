package com.soprasteria.paiement.impl;

import com.soprasteria.paiement.IPaiement;

public class PaiementAMEX implements IPaiement {

	@Override
	public boolean transaction(String refCommercant, String pan, String moisExpiration, String anneeExpiration,
			String cvv2, double montant) {
		// TODO Auto-generated method stub
		return false;
	}

}
