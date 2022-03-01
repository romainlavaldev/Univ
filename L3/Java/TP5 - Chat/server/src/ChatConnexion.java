import java.io.*;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

public class ChatConnexion extends Thread {
    
    private Client client;
    private List<Client> connectedClients;

    public ChatConnexion(Client client, List<Client> connectedClients){
        
        this.client = client;
        this.client.setConnexion(this);
        this.connectedClients = connectedClients;
        connectedClients.add(client);
        System.out.printf("Client ajouté a la liste (%d)\n", connectedClients.size());

        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + getTime() + " SYSTEM" + " - " + this.client.getName() + " connected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();

                System.out.println("Connexion message sended to 1 client");
            } catch (IOException e) {
                System.err.println("Erreur envoi message");
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }


        sendClientList();

        start();
    }
    
    private void sendClientList() {

        String data = "CLIENTLIST:";

        System.out.printf("nb connectés : (%d)\n", connectedClients.size());

        for (Client clienConnected : connectedClients) {
            data += clienConnected.getColor() + "%55%" + clienConnected.getName() + "%23%";
        }

        for (Client clientConnected : connectedClients) {
            try {
                clientConnected.getOutput().write(data);
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                System.out.println("Client list sended to 1 client");
            } catch (IOException e) {
                System.out.println("Error sending connected list");
                clientConnected.disconnect();
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
                disconnect();
                e.printStackTrace();
                //connectedClients.remove(client);
                break;
            }

            
            
            if(line != null){

                if (line.equals("%99%")){
                    disconnect();
                    return;
                }

                for (Client clientConnected : connectedClients) {
                    try {
                        clientConnected.getOutput().write(this.client.getColor() + getTime() + " >>" + this.client.getName() + " - " + line);
                        clientConnected.getOutput().newLine();
                        clientConnected.getOutput().flush();
                        System.out.println("message sended to 1 client");
                    } catch (IOException e) {
                        System.err.println("Erreur envoi message");
                        clientConnected.disconnect();
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public void disconnect() {

        connectedClients.remove(client);
        try {
            client.getInput().close();
            client.getOutput().close();
        } catch (IOException e1) {
            e1.printStackTrace();
        }


        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + getTime() + " SYSTEM" + " - " + this.client.getName() + " diconnected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                System.out.println("Connexion message sended to 1 client");
            } catch (IOException e) {
                System.err.println("Erreur envoi message");
                e.printStackTrace();
            }
        }

        if(connectedClients.size() != 0){
            sendClientList();
        }

        System.out.println(client.getName() + " disconnected");
    }

    private String getTime(){
        Format f = new SimpleDateFormat("HH:mm:ss");
        return f.format(new Date());
    }
}
