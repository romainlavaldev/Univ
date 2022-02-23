import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.io.*;

public class Server {

    public static void main(String[] args) throws IOException {

        

        if (args.length != 1){
            System.err.println("Mauvais nombres d'arguments (1 attendus)");
            return;
        }

        //Ouverture du server
        ServerSocket listener = null;
        listener = new ServerSocket(Integer.parseInt(args[0]));
        System.out.println("Ouerture du server sur le port " + args[0]);

        List<BufferedWriter> connectedClientsOutput = new ArrayList<BufferedWriter>();


        Socket client = null;
        while(true){
            //Attente d'un client
            System.out.println("Attente d'un nouveau client");
            client = listener.accept();
            System.out.printf("Client connected");

            //Recuperatons des streams
            BufferedReader input = null;
            input = new BufferedReader(new InputStreamReader(client.getInputStream()));

            connectedClientsOutput.add(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())));

            new ChatConnexion(input.readLine(), getRandomColor(), client, connectedClientsOutput);
        }

        //listener.close();

    }

    private static String getRandomColor() {

        Random obj = new Random();
        int rand_num = obj.nextInt(0xffffff + 1);

        return String.format("#%06x", rand_num);
    }
}
