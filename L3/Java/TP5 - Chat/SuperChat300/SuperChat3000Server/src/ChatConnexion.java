import java.io.*;
import java.net.Socket;
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
        System.out.println("\n");
        Server.printlnTimedMessae("Sending " + client.getName() + " connexion message");
        Server.printlnTimedMessae("START");
        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + Server.getTime() + " SYSTEM" + " - " + this.client.getName() + " connected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();

                Server.printlnTimedMessae("Connexion message sended to " + clientConnected.getName());
            } catch (IOException e) {
                Server.printlnTimedError("Error while sending message to " + clientConnected.getName());
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }

        Server.printlnTimedMessae("DONE\n");

        sendClientList();

        Server.printlnTimedMessae("Client " + client.getName() + " fully connected to server" + "\n");

        start();
    }

    //Send a list of the connected users to all connected users (used to populate client connected JList)
    private void sendClientList() {

        String data = "CLIENTLIST:";

        for (Client clienConnected : connectedClients) {
            data += clienConnected.getColor() + "%55%" + clienConnected.getName() + "%23%";
        }

        Server.printlnTimedMessae("Sending client list");
        Server.printlnTimedMessae("START");

        for (Client clientConnected : connectedClients) {
            try {
                clientConnected.getOutput().write(data);
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                Server.printlnTimedMessae("Client list sended to " + clientConnected.getName());
            } catch (IOException e) {
                Server.printlnTimedMessae("Error while sending connected list to " + clientConnected.getName());
                clientConnected.disconnect();
                e.printStackTrace();
            }
        }
        Server.printlnTimedMessae("DONE" + "\n");
    }

    @Override
    public void run(){
        String line = "";
        
        while(running){

            //Reading any message sent from the client
            try {
                line = client.getInput().readLine();
            } catch (IOException e) {
                Server.printlnTimedError("Erreur while reading message from " + this.client.getName());
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
                        Server.printlnTimedMessae(client.getName() + " started typing");
                        client.setTyping(true);

                        sendTypingClients();
                    }
                    else if (line.replace("%88%", "").equals("FALSE")){
                        Server.printlnTimedMessae(client.getName() + " stopped typing");
                        client.setTyping(false);

                        sendTypingClients();
                    }
                }else{ //Normal treatment of message

                    System.out.println("\n");
                    Server.printlnTimedMessae("Sending message from : " + client.getName() + " with content : " + line);
                    Server.printlnTimedMessae("START");
                    for (Client clientConnected : connectedClients) {
                        try {
                            clientConnected.getOutput().write(this.client.getColor() + Server.getTime() + " >> " + this.client.getName() + " - " + line);
                            clientConnected.getOutput().newLine();
                            clientConnected.getOutput().flush();
                            Server.printlnTimedMessae("message sended from " + this.client.getName() + " to " + clientConnected.getName());
                        } catch (IOException e) {
                            Server.printlnTimedError("Erreur while sending message from " + this.client.getName() + " to " + clientConnected.getName());
                            clientConnected.disconnect();
                            e.printStackTrace();
                        }
                    }

                    Server.printlnTimedMessae("DONE\n");
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

        //Server.printlnTimedMessae(data);

        for (Client clientConnected : connectedClients) {
            try {
                clientConnected.getOutput().write(data);
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                //Server.printlnTimedMessae("Client typing list sended to " + clientConnected.getName());
            } catch (IOException e) {
                Server.printlnTimedMessae("Error while sending client typing list " + clientConnected.getName());
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

        System.out.println("\n");
        Server.printlnTimedMessae("Sending " + client.getName() + " disconexion message");
        Server.printlnTimedMessae("START");
        for (Client clientConnected : connectedClients){
            try {
                clientConnected.getOutput().write("#FF0000" + Server.getTime() + " SYSTEM" + " - " + this.client.getName() + " diconnected");
                clientConnected.getOutput().newLine();
                clientConnected.getOutput().flush();
                Server.printlnTimedMessae("Disconnexion message sended from " + this.client.getName() + " to " + clientConnected.getName());
            } catch (IOException e) {
                Server.printlnTimedError("Error while sending message from " + this.client.getName() + " to " + clientConnected.getName());
                e.printStackTrace();
            }
        }
        Server.printlnTimedMessae("DONE");


        //Send the updated connected client list and client typing list to all users
        if(connectedClients.size() != 0){
            sendClientList();
            sendTypingClients();
        }

        //Stopping the thread
        running = false;
        Server.printlnTimedMessae(client.getName() + " disconnected");

    }

    
}
