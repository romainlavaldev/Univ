import java.io.BufferedReader;
import java.io.BufferedWriter;

public class Client {
    private final BufferedWriter output;
    private final BufferedReader input;
    private final String name;
    private final String color;
    private ChatConnexion connexion;

    public Client(BufferedWriter out, BufferedReader in,String name, String color, ChatConnexion connexion){
        this.output = out;
        this.input =  in;
        this.name = name;
        this.color = color;
        this.connexion = connexion;
    }

    public String getName(){
        return name;
    }

    public String getColor(){
        return color;
    }

    public BufferedWriter getOutput(){
        return output;
    }

    public BufferedReader getInput(){
        return input;
    }

    public void setConnexion(ChatConnexion connexion){
        this.connexion = connexion;
    }

    public void disconnect(){
        System.out.println(this.name + " got deconected");
        this.connexion.disconnect();
    }

}
