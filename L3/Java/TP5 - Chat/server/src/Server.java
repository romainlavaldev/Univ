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


        System.out.println("Ouerture du server sur le port " + args[0] + " addr : " + InetAddress.getLocalHost().getHostAddress());

        List<Client> connectedClients = new ArrayList<Client>();


        Socket clientConnexion = null;
        while(true){
            //Attente d'un client
            System.out.println("Attente d'un nouveau client");
            clientConnexion = listener.accept();
            System.out.println("Client connected");

            //Recuperatons du nom
            BufferedReader input = new BufferedReader(new InputStreamReader(clientConnexion.getInputStream()));
            BufferedWriter output = new BufferedWriter(new OutputStreamWriter(clientConnexion.getOutputStream()));

            Client client = new Client(output, input, input.readLine(), getRandomColor(), null);

            new ChatConnexion(client, connectedClients);
            
        }

        //listener.close();

    }

    private static String getRandomColor() {

        String colors[] = {"#3d9624", "#3de258", "#f9eb3b", "#c84de6", "#fe95a4", "#e39f0e", "#ec5617", "#d0ed00", "#8c782f", "#fc15b2", "#7dddd2", "#7f85d0", "#738765", "#cf7974", "#75335c", "#c65eda"};

        return colors[new Random().nextInt(colors.length)];

        //Random obj = new Random();
        //int rand_num = obj.nextInt(0xffffff + 1);

        //return String.format("#%06x", rand_num);
    }
}
