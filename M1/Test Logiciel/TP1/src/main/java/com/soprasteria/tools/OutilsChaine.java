package com.soprasteria.tools;

import java.text.NumberFormat;
import java.text.SimpleDateFormat;

public class OutilsChaine {
	public static NumberFormat formatMonnaie = NumberFormat.getInstance();
	public static SimpleDateFormat formatDateFrance = new SimpleDateFormat("dd/MM/yyyy");
	public static SimpleDateFormat formatHeure = new SimpleDateFormat("hh:mm");
	public static SimpleDateFormat formatDateHeure = new SimpleDateFormat("dd/MM/yyyy hh:mm:ss");
	// Code statique d'initialisation
	static {
		formatMonnaie.setMaximumFractionDigits(2);
		formatMonnaie.setMinimumFractionDigits(2);
	}

	/**
	 * Une methode qui permet de formater un chaine ( chaine ) de la maniere
	 * suivante : <BR>
	 * On rajoute n caracteres ( caractere ) a gauche ou a droite de la chaine
	 * <BR>
	 * en fonction d'une orientation ( orientation ) de telle maniere que la
	 * longueur <BR>
	 * de la chaine resultante soit egale a une longueur ( longueur ) fixee en
	 * parametre <BR>
	 * Cette methode permet donc de justifier a gauche ou a droite sur une
	 * longueur precise <BR>
	 * <BR>
	 * ex formater ( "12,34" , 10 , 0 , ' ') donne " 12,34" <BR>
	 * ex formater ( "ARTICLE 0001" , 15 , 1 , ' ') donne "ARTICLE 0001 "
	 * 
	 * @param chaine
	 *            : la chaine d'origine
	 * @param longueur
	 *            : la longueur voulue de la chaine resultante
	 * @param orientation
	 *            : 0 on ajoute des caracteres par la gauche, 1 par la droite
	 * @param caractere
	 *            : le caractere a ajouter
	 */
	public static String formater(String chaine, int longueur, int orientation, char caractere) {
		StringBuilder sb = new StringBuilder(chaine);
		int longueurChaine = chaine.length();
		if (longueurChaine > longueur)
			return chaine.substring(0, longueur - 1);
		if (orientation == 0) // On rempli par la gauche
		{
			for (int i = longueurChaine; i < longueur; i++)
				sb.insert(0, caractere);
		}
		if (orientation == 1) // On rempli par la droite
		{
			for (int i = longueurChaine; i < longueur; i++)
				sb.append(caractere);
		}
		return sb.toString();
	}
}
