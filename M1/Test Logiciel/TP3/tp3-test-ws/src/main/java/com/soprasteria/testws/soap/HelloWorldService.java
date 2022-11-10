package com.soprasteria.testws.soap;

import java.util.Set;

import javax.jws.WebMethod;
import javax.jws.WebService;

@WebService
public interface HelloWorldService {

	/**
	 * Enregistre le nom et retourne un message personnalisé.
	 * 
	 * @param name
	 *            Nom
	 * @return Message personnalisé
	 */
	@WebMethod
	String sayHello(String name);

	/**
	 * Retourne la liste des noms utilisés par les invocations de sayHello
	 * 
	 * @return Liste des noms
	 */
	@WebMethod
	Set<String> listNames();
}