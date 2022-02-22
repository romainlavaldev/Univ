import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class ChatManager {
    private JTextArea chatTxtArea;
    private JTextField messageTxtField;
    private JButton sendBtn;
    private BufferedReader input;
    private BufferedWriter output;

    public ChatManager(Socket serverConnexion, JTextArea chatTxtArea, JTextField messageTxtField, JButton sendBtn) {
        this.chatTxtArea = chatTxtArea;
        this.messageTxtField = messageTxtField;
        this.sendBtn = sendBtn;

        try {
            input = new BufferedReader(new InputStreamReader(serverConnexion.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(serverConnexion.getOutputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        ChatReader chatUpdate = new ChatReader(input, chatTxtArea);
        chatUpdate.start();

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
