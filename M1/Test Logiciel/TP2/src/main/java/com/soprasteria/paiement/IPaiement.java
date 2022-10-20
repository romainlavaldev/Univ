package com.soprasteria.paiement;

public interface IPaiement {
	public boolean transaction(String refCommercant, String pan, String moisExpiration, String anneeExpiration,
			String cvv2, double montant);
}
