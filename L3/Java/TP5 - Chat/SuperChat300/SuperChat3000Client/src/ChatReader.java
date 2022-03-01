import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.HashMap;
import java.util.Map;

public class ChatReader extends Thread{

    private final BufferedReader input;
    private final JTextPane chatTextPane;
    private final JTextPane typingTextPane;
    private final JList<String> connectedList;
    public boolean running;
    private final SuperChat3000Frame superChat3000Frame;
    private final Map<String, ImageIcon> emoteMap;{
        emoteMap = new HashMap<>();

        File dir = null;

        dir = new File("img" + File.separator + "emotes");

        for (File emoteFile : dir.listFiles()){
            String emoteName = emoteFile.getName().split("\\.")[0].replace("EMO", "");

            this.emoteMap.put(emoteName, new ImageIcon("img" + File.separator + "emotes" + File.separator + emoteFile.getName()));
        }
    }

    public ChatReader(BufferedReader input, JTextPane chatTextPane, JList<String> connectedList, SuperChat3000Frame superChat3000Frame, JTextPane typingTextPane) {
        this.input = input;
        this.chatTextPane = chatTextPane;
        this.connectedList = connectedList;
        this.superChat3000Frame = superChat3000Frame;
        this.typingTextPane = typingTextPane;
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

                        Map<String, String> clientsMap = new HashMap<>();

                        for (String client : received.replace("CLIENTLIST:", "").split("%23%")) {

                            String color = client.split("%55%")[0];
                            String name = client.split("%55%")[1];

                            clientsMap.put(name, color);

                        }


                        populateConnectedClients(clientsMap);

                    }else if (received.startsWith("TYPINGLIST:")) {
                        Map<String, String> clientsMap = new HashMap<>();

                        typingTextPane.setText("");


                        StyledDocument sDoc = typingTextPane.getStyledDocument();


                        Style s = typingTextPane.getStyle("colorPrint");
                        StyleConstants.setForeground(s, Color.white);
                        sDoc.insertString(sDoc.getLength(), "Typing : ", s);

                        for (String client : received.replace("TYPINGLIST:", "").split("%23%")) {

                            if (client.split("%55").length != 1) {
                                String color = client.split("%55%")[0];
                                String name = client.split("%55%")[1];

                                clientsMap.put(name, color);

                            }
                        }

                        for (String clientName : clientsMap.keySet()) {
                            for (String messagePart : clientName.split(" ")) {

                                if (messagePart.startsWith("//")) {
                                    s = typingTextPane.getStyle("emoteStyle");

                                    ImageIcon ico;

                                    if (emoteMap.get(messagePart.replace("//", "")) == null) {
                                        ico = emoteMap.get("unknown");
                                    } else {
                                        ico = emoteMap.get(messagePart.replace("//", ""));
                                    }

                                    StyleConstants.setIcon(s, ico);

                                    sDoc.insertString(sDoc.getLength(), "replaced text", s);

                                    sDoc.insertString(sDoc.getLength(), " ", null);

                                } else {
                                    //Affichage du message en couleur
                                    s = typingTextPane.getStyle("colorPrint");
                                    StyleConstants.setForeground(s, Color.decode(clientsMap.get(clientName)));

                                    sDoc.insertString(sDoc.getLength(), messagePart + ", ", s);
                                }
                            }
                        }

                    } else if (received.equals("%99%")){
                        superChat3000Frame.connect();
                        JOptionPane.showMessageDialog(superChat3000Frame,"server closed by operator ");
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

                        for (String messagePart : message.split(" ")){

                            if (messagePart.startsWith("//")){
                                s = chatTextPane.getStyle("emoteStyle");

                                ImageIcon ico;

                                if (emoteMap.get(messagePart.replace("//", "")) == null){
                                    ico = emoteMap.get("unknown");
                                }else{
                                    ico = emoteMap.get(messagePart.replace("//", ""));
                                }

                                StyleConstants.setIcon(s, ico);

                                sDoc.insertString(sDoc.getLength(), "replaced text", s);

                                sDoc.insertString(sDoc.getLength(), " ", null);

                            }else{
                                //Affichage du message en couleur
                                s = chatTextPane.getStyle("colorPrint");
                                StyleConstants.setForeground(s, Color.decode(color));

                                sDoc.insertString(sDoc.getLength(), messagePart + " ", s);
                            }
                        }

                        s = chatTextPane.getStyle("colorPrint");
                        StyleConstants.setForeground(s, Color.decode(color));

                        sDoc.insertString(sDoc.getLength(), "\n", s);
                    }
                }

            } catch(BadLocationException | IOException e){
                e.printStackTrace();
            }

        }
    }


    public void setRunning(boolean running){
        this.running = running;
    }

    private void populateConnectedClients(Map<String, String> clients) {
        DefaultListModel<String> lm = new DefaultListModel<> ();

        for (String clientName : clients.keySet()){
            lm.addElement(clientName);
        }

        connectedList.setModel(lm);

        connectedList.setCellRenderer(new DefaultListCellRenderer() {

            @Override
            public Component getListCellRendererComponent(JList list, Object value, int index,
                                                          boolean isSelected, boolean cellHasFocus) {
                Component c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
                if (value instanceof String) {
                    String nextUser = (String) value;
                    setText(nextUser);
                    String color = clients.get(nextUser);
                    setForeground(Color.decode(color));

                    if (isSelected) {
                        setBackground(getBackground().darker());
                    }
                } else {
                    setText("error?");
                }
                return c;
            }

        });
    }

}
