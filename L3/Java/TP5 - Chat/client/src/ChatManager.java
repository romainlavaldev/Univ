import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class ChatManager {
    private final JTextPane chatTextPane;
    private final JTextField messageTxtField;
    private final JButton sendBtn;
    private BufferedReader input;
    private BufferedWriter output;

    public ChatManager(Socket serverConnexion, JTextPane chatTextPane, JTextField messageTxtField, JButton sendBtn, String nomClient) {
        this.chatTextPane = chatTextPane;
        this.messageTxtField = messageTxtField;
        this.sendBtn = sendBtn;

        try {
            input = new BufferedReader(new InputStreamReader(serverConnexion.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(serverConnexion.getOutputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        ChatReader chatUpdate = new ChatReader(input, chatTextPane);
        chatUpdate.start();

        try {
            output.write(nomClient);
            output.newLine();
            output.flush();
        }catch (IOException e){
            System.err.println("Problème d'envoi du nom du client");
            e.printStackTrace();
        }

        sendBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                sendMessage();
            }
        });
    }

    private void sendMessage(){
        if(messageTxtField.getText().isBlank()){
          return;
        }

        System.out.println("Envoi du message");
        try {
            output.write(messageTxtField.getText());
            output.newLine();
            output.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
