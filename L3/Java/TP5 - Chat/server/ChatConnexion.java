import java.io.*;
import java.net.Socket;
import java.util.List;

public class ChatConnexion extends Thread {
    
    private String clientName;
    private String clientColor;
    private BufferedReader input;
    private List<BufferedWriter> connectedClientsOutput;

    public ChatConnexion(String clientName, String clientColor, Socket clientConnexion, List<BufferedWriter> connectedClientsOutput){
        this.clientColor = clientColor;
        this.clientName = clientName;
        this.connectedClientsOutput = connectedClientsOutput;
        try {
            input = new BufferedReader(new InputStreamReader(clientConnexion.getInputStream()));
        } catch (IOException e) {
            System.err.println("Erreur dans l'ouverture du tube avec le client");
            e.printStackTrace();
            return;
        }

        start();
    }
    
    @Override
    public void run(){
        String line = "";
        
        while(true){
            try {
                line = input.readLine();
            } catch (IOException e) {
                System.err.println("Erreur lecture message");
                e.printStackTrace();
            }
            
            for (BufferedWriter output : connectedClientsOutput) {
                try {
                    output.write(clientColor + ">>" + clientName + " - " + line);
                    output.newLine();
                    output.flush();
                } catch (IOException e) {
                    System.err.println("Erreur envoi message");
                    e.printStackTrace();
                }
            }
            
        }
    }
}
