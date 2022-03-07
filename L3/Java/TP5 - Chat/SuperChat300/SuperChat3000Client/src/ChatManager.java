import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.text.Document;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class ChatManager {
    private final JTextField messageTxtField;
    private final JButton sendBtn;
    private BufferedReader input;
    private BufferedWriter output;
    private final ChatReader chatReader;
    private boolean writing;{
        writing = false;
    }

    /**
     * Instantiates a new Chat manager.
     *
     * @param serverConnexion    the server connexion socket
     * @param chatTextPane       the chat text pane
     * @param messageTxtField    the message txt field
     * @param sendBtn            the send btn
     * @param nomClient          the nom client
     * @param connectedList      the connected users list
     * @param superChat3000Frame the super chat 3000 frame
     * @param typingTextPane     the typing text pane
     */
    public ChatManager(Socket serverConnexion, JTextPane chatTextPane, JTextField messageTxtField, JButton sendBtn, String nomClient, JList<String> connectedList, SuperChat3000Frame superChat3000Frame, JTextPane typingTextPane) {
        this.messageTxtField = messageTxtField;
        this.sendBtn = sendBtn;

        try {
            input = new BufferedReader(new InputStreamReader(serverConnexion.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(serverConnexion.getOutputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.chatReader = new ChatReader(input, chatTextPane, connectedList, superChat3000Frame, typingTextPane);
        this.chatReader.start();

        try {
            output.write(nomClient);
            output.newLine();
            output.flush();
        }catch (IOException e){
            System.err.println("Problem while sending client name");
            e.printStackTrace();
        }

        sendBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                sendMessage();
            }
        });

        messageTxtField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                sendMessage();
            }
        });

        messageTxtField.getDocument().addDocumentListener(new DocumentAdapter(){
            @Override
            public void insertUpdate(DocumentEvent documentEvent) {
                if (!writing && !messageTxtField.getText().isBlank()){


                    sendWrite(true);
                    writing = true;
                }


            }

            @Override
            public void removeUpdate(DocumentEvent documentEvent) {
                if (writing && messageTxtField.getText().isBlank()){

                    sendWrite(false);
                    writing = false;
                }
            }
        });
    }

    //Seding to the server the typing state
    private void sendWrite(boolean b) {
        String code = b ? "%88%TRUE" : "%88%FALSE";
        System.out.println("Sending writing state (" + code + ") ...");
        try {
            output.write(code);
            output.newLine();
            output.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendMessage(){
        if(messageTxtField.getText().isBlank()){
            JOptionPane.showMessageDialog(null, "Message field is empty !");
          return;
        }

        System.out.println("Sending message ...");
        try {
            output.write(messageTxtField.getText());
            output.newLine();
            output.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

        messageTxtField.setText("");
        messageTxtField.grabFocus();

    }

    /**
     * Disconnect.
     */
    public void disconnect(){


        this.chatReader.setRunning(false);

        for( ActionListener al : sendBtn.getActionListeners() ) {
            sendBtn.removeActionListener( al );
        }

        for (ActionListener al : messageTxtField.getActionListeners()) {
            messageTxtField.removeActionListener(al);
        }


        try {
            input.close();
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
