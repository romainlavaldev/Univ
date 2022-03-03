/**
 * Representation of a client
 */
public class Client {
    private String name;
    private String color;

    /**
     * Instantiates a new Client.
     *
     * @param name  the name
     * @param color the color
     */
    public Client(String name, String color){
        this.name = name;
        this.color = color;
    }

    /**
     * Gets name.
     *
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * Gets color.
     *
     * @return the color
     */
    public String getColor() {
        return color;
    }

    @Override
    public String toString() {
        return name;
    }
}
