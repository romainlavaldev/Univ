package com.soprasteria.testws.soap;

import javax.xml.ws.Endpoint;

public class HelloWorldServiceRunner {

	public static void main(String[] args) {
		String url = "http://127.0.0.1:8888/HelloWorldService";
		System.out.println("Publishing HelloWorldService to " + url);
		Endpoint.publish(url, new HelloWorldServiceImpl());
	}

}
