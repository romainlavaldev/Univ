import java.io.BufferedReader;
import java.io.BufferedWriter;

public class Client {
    private final BufferedWriter output;
    private final BufferedReader input;
    private final String name;
    private final String color;

    public Client(BufferedWriter out, BufferedReader in,String name, String color){
        this.output = out;
        this.input =  in;
        this.name = name;
        this.color = color;
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

}
