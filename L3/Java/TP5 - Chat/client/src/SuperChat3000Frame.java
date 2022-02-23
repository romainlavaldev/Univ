import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.Document;
import javax.swing.text.DocumentFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.Socket;

public class SuperChat3000Frame extends JFrame {

    JButton connexionBtn;{
        connexionBtn = new JButton("Connection");
        connexionBtn.setPreferredSize(new Dimension(20, 10));
        connexionBtn.setEnabled(false);
    }

    JTextField nameTxtField;{
        nameTxtField = new JTextField();
        nameTxtField.setColumns(20);
    }


    JTextField ipTxtField;{
        ipTxtField = new JTextField();
        ipTxtField.setColumns(20);
    }


    JTextField portTxtField;{
        portTxtField = new JTextField();
        portTxtField.setColumns(20);
    }

    JList<Client> connectedList;{
        connectedList = new JList<>();
    }

    JTextPane chatTextPane;{
        chatTextPane = new JTextPane();
        chatTextPane.addStyle("colorPrint", null);
    }

    JTextField messageTextField;{
        messageTextField = new JTextField();
    }

    JButton sendBtn;{
        sendBtn = new JButton("Envoyer");

        connexionBtn.setPreferredSize(new Dimension(20, 10));
    }

    public SuperChat3000Frame(String name){
        super(name);

        DocumentListener dl = new DocumentAdapter(){
            @Override
            public void insertUpdate(DocumentEvent documentEvent) {
                checkEmptyTextField();
            }

            @Override
            public void removeUpdate(DocumentEvent documentEvent) {
                checkEmptyTextField();
            }
        };

        nameTxtField.getDocument().addDocumentListener(dl);
        ipTxtField.getDocument().addDocumentListener(dl);
        portTxtField.getDocument().addDocumentListener(dl);

        connexionBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                connect();
            }
        });


        buildInterface();
    }

    private void checkEmptyTextField() {
        if (!nameTxtField.getText().isBlank() && !ipTxtField.getText().isBlank() && !portTxtField.getText().isBlank()){
            connexionBtn.setEnabled(true);
        }else{
            connexionBtn.setEnabled(false);
        }
    }

    private void buildInterface(){

        //Name Label + TxtBox
        JPanel namePanel = new JPanel();
        namePanel.setLayout(new FlowLayout());
        namePanel.add(new JLabel("Nom"));
        namePanel.add(nameTxtField);

        //IP Label + TxtBox
        JPanel ipPanel = new JPanel();
        ipPanel.setLayout(new FlowLayout());
        ipPanel.add(new JLabel("IP"));
        ipPanel.add(ipTxtField);

        //Port Label + TxtBox
        JPanel portPanel = new JPanel();
        portPanel.setLayout(new FlowLayout());
        portPanel.add(new JLabel("Port"));
        portPanel.add(portTxtField);


        JPanel connexionPanel = new JPanel();
        connexionPanel.setLayout(new GridLayout(2,2));
        connexionPanel.add(namePanel);

        connexionPanel.add(connexionBtn);

        connexionPanel.add(ipPanel);

        connexionPanel.add(portPanel);

        this.getContentPane().setLayout(new BorderLayout(0,0));
        this.getContentPane().add(connexionPanel, BorderLayout.NORTH);



        //WEST
        JPanel connectedPanel = new VerticalPanel();
        connectedPanel.add(new JLabel("Connectés"));
        connectedPanel.add(connectedList);

        this.getContentPane().add(connectedPanel, BorderLayout.WEST);

        //Center
        JPanel chatPanel = new VerticalPanel();
        chatPanel.add(new JLabel("Discussion"));
        chatPanel.add(chatTextPane);
        chatPanel.add(new JLabel("Message"));
        chatPanel.add(messageTextField);
        chatPanel.add(sendBtn);
        this.getContentPane().add(chatPanel, BorderLayout.CENTER);
    }

    private void connect(){

        if(nameTxtField.getText().isBlank()){
            JOptionPane.showMessageDialog(this, "Vous n'avez pas mis de nom !");
            return;
        }

        if (!ipTxtField.getText().matches("([0-9]+(\\.[0-9]+)+)")){
            JOptionPane.showMessageDialog(this,"Le format de l'IP est invalide !");
            return;
        }

        if(!portTxtField.getText().matches("[0-9]+")){
            JOptionPane.showMessageDialog(this, "Le format du port est invalide");
            return;
        }



        System.out.printf("Tentative de connection : %s@%s -p %s%n", nameTxtField.getText(), ipTxtField.getText(), portTxtField.getText());

        Socket serverConnexion;
        try {
            serverConnexion = new Socket(ipTxtField.getText(), Integer.parseInt(portTxtField.getText()));
        } catch (IOException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Problème de connection au server !\n\n" + e.getMessage());
            return;
        }

        System.out.println("Connection réussie");
        new ChatManager(serverConnexion, chatTextPane, messageTextField, sendBtn, nameTxtField.getText());
    }



}
