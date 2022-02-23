import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;

public class ChatReader extends Thread{

    BufferedReader input;
    JTextPane chatTextPane;

    public ChatReader(BufferedReader input, JTextPane chatTextPane) {
        this.input = input;
        this.chatTextPane = chatTextPane;
    }

    @Override
    public void run() {
        while(true){
            try {
                String received = input.readLine();
                System.out.println(received);

                String color = received.substring(0, 7);
                String message = received.replace(color, "");

                System.out.printf("Color : %s\nMessage : %s", color, message);

                StyledDocument sDoc = chatTextPane.getStyledDocument();

                Style s = chatTextPane.getStyle("colorPrint");
                StyleConstants.setForeground(s, Color.decode(color));

                sDoc.insertString(sDoc.getLength(), message +"\n", s);

            } catch (IOException e) {
                e.printStackTrace();
            } catch (BadLocationException e) {
                e.printStackTrace();
            }
        }
    }
}
