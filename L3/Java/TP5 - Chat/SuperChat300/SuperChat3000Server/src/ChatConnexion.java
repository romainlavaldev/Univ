import java.io.*;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

/**
 * Represent a connexion thread
 */
public class ChatConnexion extends Thread {
    
    private Client client;
    private List<Client> connectedClients;
    private boolean running;
    {
        running = true;
    }

    /**
     * Instantiates a new Chat connexion thread
     *
     * @param client           the client
     * @param connectedClients the connected clients
     */
    public ChatConnexion(Client client, List<Client> connectedClients){
        
        this.client = client;
        this.client.setConnexion(this);
        this.connectedClients = connectedClients;
        connectedClients.add(client);

        System.out.printf("Client added to the list. count : (%d)\n", connectedClients.size());

        //Send a message to all clients to welcome the new client
        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + getTime() + " SYSTEM" + " - " + this.client.getName() + " connected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();

                System.out.println("Connexion message sended to " + clientConnected.getName());
            } catch (IOException e) {
                System.err.println("Error while sending message to " + clientConnected.getName());
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }


        sendClientList();

        start();
    }

    //Send a list of the connected users to all connected users (used to populate client connected JList)
    private void sendClientList() {

        String data = "CLIENTLIST:";

        for (Client clienConnected : connectedClients) {
            data += clienConnected.getColor() + "%55%" + clienConnected.getName() + "%23%";
        }

        for (Client clientConnected : connectedClients) {
            try {
                clientConnected.getOutput().write(data);
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                System.out.println("Client list sended to " + clientConnected.getName());
            } catch (IOException e) {
                System.out.println("Error while sending connected list to " + clientConnected.getName());
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }
    }

    @Override
    public void run(){
        String line = "";
        
        while(running){

            //Reading any message sent from the client
            try {
                line = client.getInput().readLine();
            } catch (IOException e) {
                System.err.println("Erreur while reading message from " + this.client.getName());
                disconnect();
                e.printStackTrace();
                //connectedClients.remove(client);
                return;
            }

            
            
            if(line != null){

                if (line.equals("%99%")){
                    disconnect();
                    return;
                }else if(line.startsWith("%88%")){ //%88% correspond to a currently typing state (start typing or stop typing)
                    if (line.replace("%88%", "").equals("TRUE")){
                        System.out.println(client.getName() + " started typing");
                        client.setTyping(true);

                        sendTypingClients();
                    }
                    else if (line.replace("%88%", "").equals("FALSE")){
                        System.out.println(client.getName() + " stopped typing");
                        client.setTyping(false);

                        sendTypingClients();
                    }
                }else{ //Normal treatment of message
                    for (Client clientConnected : connectedClients) {
                        try {
                            clientConnected.getOutput().write(this.client.getColor() + getTime() + " >> " + this.client.getName() + " - " + line);
                            clientConnected.getOutput().newLine();
                            clientConnected.getOutput().flush();
                            System.out.println("message sended from " + this.client.getName() + " to " + clientConnected.getName());
                        } catch (IOException e) {
                            System.err.println("Erreur while sending message from " + this.client.getName() + " to " + clientConnected.getName());
                            clientConnected.disconnect();
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    //Send a list of the currently typing users to all connected users (used to populate client typing list)
    private void sendTypingClients() {
        String data = "TYPINGLIST:";

        for (Client clienConnected : connectedClients) {
            if (clienConnected.isTyping()){
                data += clienConnected.getColor() + "%55%" + clienConnected.getName() + "%23%";
            }
        }

        System.out.println(data);

        for (Client clientConnected : connectedClients) {
            try {
                clientConnected.getOutput().write(data);
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                System.out.println("Client typing list sended to " + clientConnected.getName());
            } catch (IOException e) {
                System.out.println("Error while sending client typing list " + clientConnected.getName());
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }
    }

    /**
     * Disconnect.
     */
    public void disconnect() {

        connectedClients.remove(client);
        try {
            client.getInput().close();
            client.getOutput().close();
        } catch (IOException e1) {
            e1.printStackTrace();
        }


        //Send a message to all clients to tell them that the client has gone
        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + getTime() + " SYSTEM" + " - " + this.client.getName() + " diconnected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                System.out.println("Connexion message sended from " + this.client.getName() + " to " + clientConnected.getName());
            } catch (IOException e) {
                System.err.println("Error while sending message from " + this.client.getName() + " to " + clientConnected.getName());
                e.printStackTrace();
            }
        }

        //Send the updated connected client list and client typing list to all users
        if(connectedClients.size() != 0){
            sendClientList();
            sendTypingClients();
        }

        //Stopping the thread
        running = false;
        System.out.println(client.getName() + " disconnected");

    }

    private String getTime(){
        Format f = new SimpleDateFormat("HH:mm:ss");
        return f.format(new Date());
    }
}
