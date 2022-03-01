import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ChatReader extends Thread{

    private final BufferedReader input;
    private final JTextPane chatTextPane;
    private final JList<String> connectedList;
    public boolean running;
    private final SuperChat3000Frame superChat3000Frame;

    public ChatReader(BufferedReader input, JTextPane chatTextPane, JList<String> connectedList, SuperChat3000Frame superChat3000Frame) {
        this.input = input;
        this.chatTextPane = chatTextPane;
        this.connectedList = connectedList;
        this.superChat3000Frame = superChat3000Frame;
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

                        Map<String, String> clientsMap = new HashMap<String, String>();

                        for (String client : received.replace("CLIENTLIST:", "").split("%23%")) {

                            String color = client.split("%55%")[0];
                            String name = client.split("%55%")[1];

                            clientsMap.put(name, color);

                            clients.add(new Client(name, color));
                        }


                        populateConnectedClients(clientsMap);

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

                        boolean emo = false;
                        for (String messagePart : message.split("//")){
                            if(emo){
                                s = chatTextPane.getStyle("emoteStyle");
                                StyleConstants.setIcon(s, getIconFromEmoteName(messagePart));

                                sDoc.insertString(sDoc.getLength(), "replaced text", s);
                                emo = false;

                            }else {
                                //Affichage du message en couleur
                                s = chatTextPane.getStyle("colorPrint");
                                StyleConstants.setForeground(s, Color.decode(color));

                                sDoc.insertString(sDoc.getLength(), messagePart, s);
                                emo = true;

                            }

                        }

                        s = chatTextPane.getStyle("colorPrint");
                        StyleConstants.setForeground(s, Color.decode(color));

                        sDoc.insertString(sDoc.getLength(), "\n", s);
                    }
                }

            } catch(IOException e){
                e.printStackTrace();
            } catch(BadLocationException e){
                e.printStackTrace();
            }

        }
    }

    private ImageIcon getIconFromEmoteName(String messagePart) {

        if (messagePart.equals("hop3x")){
            return new ImageIcon(this.getClass().getClassLoader().getResource("img/EMOhop3x.jpg"));
        } else if (messagePart.equals("wave")){
            return new ImageIcon(this.getClass().getClassLoader().getResource("img/EMOwave.png"));
        }else if (messagePart.equals("uwu")){
            return new ImageIcon(this.getClass().getClassLoader().getResource("img/EMOuwu.png"));
        }else if (messagePart.equals("thinking")){
            return new ImageIcon(this.getClass().getClassLoader().getResource("img/EMOthinking.png"));
        }

        return new ImageIcon(this.getClass().getClassLoader().getResource("img/EMOunknown.png"));
    }

    public void setRunning(boolean running){
        this.running = running;
    }

    private void populateConnectedClients(Map<String, String> clients) {
        DefaultListModel lm = new DefaultListModel();

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
