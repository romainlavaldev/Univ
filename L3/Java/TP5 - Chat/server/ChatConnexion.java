import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ChatConnexion extends Thread {
    
    private Client client;
    private List<Client> connectedClients;

    public ChatConnexion(Client client, List<Client> connectedClients){
        
        this.client = client;
        this.connectedClients = connectedClients;
        connectedClients.add(client);
        System.out.printf("Client ajouté a la liste (%d)\n", connectedClients.size());

        sendClientList();

        start();
    }
    
    private void sendClientList() {

        String data = "CLIENTLIST:";

        System.out.printf("nb connectés : (%d)\n", connectedClients.size());

        for (Client client : connectedClients) {
            data += client.getColor() + "%55%" + client.getName() + "%23%";
        }

        for (Client client : connectedClients) {
            try {
                client.getOutput().write(data);
                client.getOutput().newLine();
                client.getOutput().flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void run(){
        String line = "";
        
        while(true){
            try {
                line = client.getInput().readLine();
            } catch (IOException e) {
                System.err.println("Erreur lecture message");
                e.printStackTrace();
            }
            
            for (Client client : connectedClients) {
                try {
                    client.getOutput().write(client.getColor() + ">>" + client.getName() + " - " + line);
                    client.getOutput().newLine();
                    client.getOutput().flush();
                } catch (IOException e) {
                    System.err.println("Erreur envoi message");
                    e.printStackTrace();
                }
            }
            
        }
    }
}
