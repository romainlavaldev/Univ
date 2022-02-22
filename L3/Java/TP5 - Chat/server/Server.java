import java.net.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

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


        //Attente d'un client
        Socket client = null;
        client = listener.accept();
        System.out.printf("Client connected");

        //Recuperatons des streams
        BufferedReader input = null;
        BufferedWriter output = null;
        input = new BufferedReader(new InputStreamReader(client.getInputStream()));
        output = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));


        //Communication
        String line;
        while(true){
            line = input.readLine();

            if (line.equals("STOP")){
                output.write(">>>Connexion stopped");
                output.newLine();
                output.flush();

                client.close();
                break;
            }

            output.write(">>>" + line);
            output.newLine();
            output.flush();
        }

        System.out.println("Server stopped");
        listener.close();


    }
}
