import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.net.*;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Random;
import java.io.*;

/**
 * A stream used to redirect a stream into a JTextPane with color
 */
class TextPaneOutputStream extends OutputStream {

    private JTextPane tp;
    private Color c;

    /**
     * Instantiates a new Text pane output stream.
     *
     * @param tp the text pane component
     */
    public TextPaneOutputStream(JTextPane tp, Color c) {
        this.tp = tp;
        this.c = c;
    }

    public synchronized void write(int b) throws IOException {
        
        Style s = tp.getStyle("colorPrint");
        StyleConstants.setForeground(s, c);

        try {
            tp.getDocument().insertString(tp.getDocument().getLength(), String.valueOf((char) b), s);
        } catch (BadLocationException e) {
            e.printStackTrace();
        }
    }
}


/**
 * Main class of the server which create and load a server window
 */
public class Server {

    private static List<Client> connectedClients;

    /**
     * The entry point of application.
     *
     * @param args the input arguments
     * @throws IOException the io exception
     */
    public static void main(String[] args) throws IOException {
        String port;

        if (args.length == 0){

            //Version GUI
            port = JOptionPane.showInputDialog("Port ?");


            //Forcing the port to be 4 or 5 digits
            while (!port.matches("[0-9]{4,5}")){
                JOptionPane.showMessageDialog(null,"Port provided is incorrect (5-6 digits above 1023 required)");
                port = JOptionPane.showInputDialog("Port ?");
            }

            //Building the app

            
            JFrame mainFrame = new JFrame("SuperChat3000 Server");

            JTextPane consoleTextPane = new JTextPane();
            consoleTextPane.addStyle("colorPrint", null);

            //Redirecting System.out and System.err to the JTextPane with colored error printing
            PrintStream psOut = new PrintStream(new TextPaneOutputStream(consoleTextPane, Color.BLACK));
            PrintStream psErr = new PrintStream(new TextPaneOutputStream(consoleTextPane, Color.RED));
            System.setOut(psOut);
            System.setErr(psErr);

            JScrollPane js = new JScrollPane(consoleTextPane);
            js.setPreferredSize(new Dimension(600, 400));

            mainFrame.add (js);
            mainFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

            mainFrame.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    closeServer();
                }
            });

            mainFrame.pack();
            mainFrame.setVisible(true);


        }else{
            //Run in terminal version. Don't load any Java Swing component

            port = args[0];
        }


        ServerSocket listener = null;

        //Opening the server on the provided port
        try {
            listener = new ServerSocket(Integer.parseInt(port));
        }catch (BindException e){
            JOptionPane.showMessageDialog( null,"This port is already use by another server or application. Please consider using another port");
            closeServer();
        }


        printlnTimedMessae("Starting server on port " + port + ", local address is " + InetAddress.getLocalHost().getHostAddress() + "\n");

        connectedClients = new ArrayList<Client>();


        Socket clientConnexion = null;

        //Main loop of the server
        while(true){
            //Waiting for a client to connect
            printlnTimedMessae("Waiting for a client to connect");
            clientConnexion = listener.accept();
            printlnTimedMessae("Client connected" + "\n");

            BufferedReader input = new BufferedReader(new InputStreamReader(clientConnexion.getInputStream()));
            BufferedWriter output = new BufferedWriter(new OutputStreamWriter(clientConnexion.getOutputStream()));

            //Saving the new client
            Client client = new Client(output, input, input.readLine(), getRandomColor(), null);

            //Starting a communication thread with this client
            new ChatConnexion(client, connectedClients);
            
        }

    }

    private static void closeServer() {

        //Disconnect all connected users
        if (connectedClients != null && connectedClients.size() != 0 ){
            for (Client client : connectedClients) {
                try {
                    printlnTimedMessae("Forcing " + client.getName() + " to disconnect" + "\n");
                    client.getOutput().write("%99%");
                    client.getOutput().newLine();
                    client.getOutput().flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        System.exit(0);
    }

    //Get a random hex formated color
    private static String getRandomColor() {

        //Random in a list (only visible colors on the client background)
        String colors[] = {"#3d9624", "#3de258", "#f9eb3b", "#c84de6", "#fe95a4", "#e39f0e", "#ec5617", "#d0ed00", "#8c782f", "#fc15b2", "#7dddd2", "#7f85d0", "#738765", "#cf7974", "#75335c", "#c65eda"};
        return colors[new Random().nextInt(colors.length)];

        //Random color (can be a non-visible color on the client background)
        /*
        Random obj = new Random();
        int rand_num = obj.nextInt(0xffffff + 1);
        return String.format("#%06x", rand_num);
        */
    }

    static void printlnTimedMessae(String msg){
        System.out.println(getTime() + " " + msg);
    }

    static void printlnTimedError(String errorMessage){
        System.err.println("\nERROR\n" + getTime() + " " + errorMessage);
    }

    static String getTime(){
        Format f = new SimpleDateFormat("HH:mm:ss");
        return f.format(new Date());
    }
}
