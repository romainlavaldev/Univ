package com.soprasteria.testws.soap;

import java.util.HashSet;
import java.util.Set;

import javax.jws.WebService;

@WebService
public class HelloWorldServiceImpl implements HelloWorldService {

	private Set<String> listNames = new HashSet<>();

	@Override
	public synchronized String sayHello(String name) {
		// mémorisation des noms
		listNames.add(name);

		// réponse
		return "Hello " + name + " ! How are you?!";
	}

	@Override
	public Set<String> listNames() {
		return listNames;
	}

}