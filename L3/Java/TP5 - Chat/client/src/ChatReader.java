import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ChatReader extends Thread{

    private BufferedReader input;
    private JTextPane chatTextPane;
    private JList<String> connectedList;
    public boolean running;

    public ChatReader(BufferedReader input, JTextPane chatTextPane, JList<String> connectedList) {
        this.input = input;
        this.chatTextPane = chatTextPane;
        this.connectedList = connectedList;
    }

    @Override
    public void run() {
        running = true;
        while(running){
            try {
                String received = input.readLine();
                System.out.println("msg received : " + received);

                if (received != null) {


                    if (received.startsWith("CLIENTLIST:")) {
                        List<Client> clients = new ArrayList<>();
                        for (String client : received.replace("CLIENTLIST:", "").split("%23%")) {

                            String color = client.split("%55%")[0];
                            String name = client.split("%55%")[1];

                            clients.add(new Client(name, color));
                        }


                        populateConnectedClients(clients);

                    } else {
                        String color = received.substring(0, 7);
                        String message = received.replace(color, "");
                        String time = message.substring(0, 8);
                        message = message.replace(time, "");

                        System.out.printf("Color : %s\nMessage : %s\nTime : %s\n", color, message, time);

                        StyledDocument sDoc = chatTextPane.getStyledDocument();

                        //Affichage de l'heure d'envoi du message
                        Style s = chatTextPane.getStyle("colorPrint");
                        StyleConstants.setForeground(s, Color.white);
                        sDoc.insertString(sDoc.getLength(), time, s);


                        //Affichage du message en couleur
                        s = chatTextPane.getStyle("colorPrint");
                        StyleConstants.setForeground(s, Color.decode(color));

                        sDoc.insertString(sDoc.getLength(), message + "\n", s);
                    }
                }

            } catch(IOException e){
                e.printStackTrace();
            } catch(BadLocationException e){
                e.printStackTrace();
            }

        }
    }

    public void setRunning(boolean running){
        this.running = running;
    }

    private void populateConnectedClients(List<Client> clients) {
        DefaultListModel lm = new DefaultListModel();

        for (Client client : clients){
            lm.addElement(client.getName());
        }

        connectedList.setModel(lm);
    }
}
