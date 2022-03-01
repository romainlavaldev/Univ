import javax.swing.*;
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

    public ChatManager(Socket serverConnexion, JTextPane chatTextPane, JTextField messageTxtField, JButton sendBtn, String nomClient, JList<String> connectedList, SuperChat3000Frame superChat3000Frame) {
        this.messageTxtField = messageTxtField;
        this.sendBtn = sendBtn;

        try {
            input = new BufferedReader(new InputStreamReader(serverConnexion.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(serverConnexion.getOutputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.chatReader = new ChatReader(input, chatTextPane, connectedList, superChat3000Frame);
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
