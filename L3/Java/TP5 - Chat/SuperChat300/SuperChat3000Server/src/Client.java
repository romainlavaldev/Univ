import java.io.BufferedReader;
import java.io.BufferedWriter;

/**
 * Representation of a client
 */
public class Client {
    private final BufferedWriter output;
    private final BufferedReader input;
    private final String name;
    private final String color;
    private ChatConnexion connexion;
    private boolean typing;{
        typing = false;
    }

    /**
     * Instantiates a new Client.
     *
     * @param out       the output stream of the socket
     * @param in        the input stream of the socket
     * @param name      the name
     * @param color     the color
     * @param connexion the connexion thread
     */
    public Client(BufferedWriter out, BufferedReader in,String name, String color, ChatConnexion connexion){
        this.output = out;
        this.input =  in;
        this.name = name;
        this.color = color;
        this.connexion = connexion;
    }

    /**
     * Get name string.
     *
     * @return the name
     */
    public String getName(){
        return name;
    }

    /**
     * Get color string.
     *
     * @return the color
     */
    public String getColor(){
        return color;
    }

    /**
     * Get output buffered writer.
     *
     * @return the buffered writer
     */
    public BufferedWriter getOutput(){
        return output;
    }

    /**
     * Get input buffered reader.
     *
     * @return the buffered reader
     */
    public BufferedReader getInput(){
        return input;
    }

    /**
     * Set connexion thread
     *
     * @param connexion the connexion thread
     */
    public void setConnexion(ChatConnexion connexion){
        this.connexion = connexion;
    }

    /**
     * Disconnect the client
     */
    public void disconnect(){
        System.out.println(this.name + " got deconected");
        this.connexion.disconnect();
    }

    /**
     * Is typing boolean.
     *
     * @return the typing state
     */
    public boolean isTyping() {
        return typing;
    }

    /**
     * Sets typing.
     *
     * @param typing the typing state
     */
    public void setTyping(boolean typing) {
        this.typing = typing;
    }
}
