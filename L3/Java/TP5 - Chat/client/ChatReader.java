import javax.swing.*;
import java.io.BufferedReader;
import java.io.IOException;

public class ChatReader extends Thread{

    BufferedReader input;
    JTextArea chatTextArea;

    public ChatReader(BufferedReader input, JTextArea chatTextArea) {
        this.input = input;
        this.chatTextArea = chatTextArea;
    }

    @Override
    public void run() {
        while(true){
            try {
                chatTextArea.append(input.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
