import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.net.Socket;

/**
 * Main frame of the client application
 */
public class SuperChat3000Frame extends JFrame {

    JButton connexionBtn;{
        connexionBtn = new JButton("Connect");
        connexionBtn.setPreferredSize(new Dimension(20, 10));
        connexionBtn.setEnabled(false);
    }


    JTextField nameTxtField;{
        nameTxtField = new JTextField();
        nameTxtField.setColumns(10);

        nameTxtField.addActionListener(actionEvent -> connect());
    }


    JTextField ipTxtField;{
        ipTxtField = new JTextField();
        ipTxtField.setColumns(10);

        ipTxtField.addActionListener(actionEvent -> connect());

        ipTxtField.setText("127.0.1.1");
    }


    JTextField portTxtField;{
        portTxtField = new JTextField();
        portTxtField.setColumns(10);

        portTxtField.addActionListener(actionEvent -> connect());

        portTxtField.setText("8888");
    }


    JList<String> connectedList;{
        connectedList = new JList<>();
        connectedList.setPreferredSize(new Dimension(100, 10));
    }


    JTextPane chatTextPane;{
        chatTextPane = new JTextPane();
        chatTextPane.addStyle("colorPrint", null);
        chatTextPane.addStyle("emoteStyle", null);


        Style s = chatTextPane.getStyle("colorPrint");
        StyleConstants.setFontSize(s, 16);
        //chatTextPane.setMinimumSize(new Dimension(100, 250));
        chatTextPane.setEditable(false);

        //Scroll the chat all the way down when a new message is printed
        chatTextPane.getDocument().addDocumentListener(new DocumentAdapter(){

            @Override
            public void insertUpdate(DocumentEvent documentEvent) {
                chatTextPane.setCaretPosition(chatTextPane.getDocument().getLength());


            }
        });
    }


    JTextPane typingTextPane;{
        typingTextPane = new JTextPane();
        typingTextPane.addStyle("colorPrint", null);
        typingTextPane.addStyle("emoteStyle", null);

        typingTextPane.setEditable(false);
    }


    JTextField messageTextField;{
        messageTextField = new JTextField();
        messageTextField.setMaximumSize(new Dimension(10000, 60));

    }


    JButton sendBtn;{
        sendBtn = new JButton("Send");

    }


    JButton emoteBtn;{
        emoteBtn = new JButton("Emote");

    }

    private ChatManager chatManager;
    private boolean connected = false;

    /**
     * Instantiates a new Super chat 3000 frame.
     *
     * @param name the name displayed on the frame
     */
    public SuperChat3000Frame(){
        super("SuperChat3000");

        //Listener on connexion fields
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

        //Using lambda -> correspond to a new action listener
        connexionBtn.addActionListener(actionEvent -> connect());


        //Using lambda -> correspond to a new action listener
        emoteBtn.addActionListener(actionEvent -> {
            IconSelectionDialog isd = new IconSelectionDialog();
            if (!isd.getEmoteJList().isSelectionEmpty()){
                messageTextField.setText(messageTextField.getText() + " //" + isd.getEmoteJList().getSelectedValue());
            }

        });

        buildInterface();

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                if (connected){
                    connect();
                }
                super.windowClosing(e);
            }
        });
    }


    //Enable or disable the connexion button
    private void checkEmptyTextField() {
        connexionBtn.setEnabled(!nameTxtField.getText().isBlank() && !ipTxtField.getText().isBlank() && !portTxtField.getText().isBlank());
    }


    private void buildInterface(){

        //Name Label + TxtBox
        JPanel namePanel = new JPanel();
        namePanel.setLayout(new FlowLayout());
        namePanel.add(new JLabel("Name"));
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

        JPanel headerPanel = new JPanel(new FlowLayout());
        JLabel logo = new JLabel(new ImageIcon("img/LOGO.png"));
        logo.setPreferredSize(new Dimension(100, 100));
        headerPanel.add(logo);
        headerPanel.add(connexionPanel);

        this.getContentPane().add(headerPanel, BorderLayout.NORTH);


        //WEST
        JPanel connectedPanel = new VerticalPanel();
        connectedPanel.add(new JLabel("Connected Users"));
        connectedPanel.add(connectedList);

        this.getContentPane().add(connectedPanel, BorderLayout.WEST);

        //Center
        JPanel chatPanel = new VerticalPanel();
        chatPanel.add(new JLabel("Chat"));
        JScrollPane jsp = new JScrollPane(chatTextPane);
        jsp.setPreferredSize(new Dimension(100, 250));
        chatPanel.add(jsp);
        chatPanel.add(typingTextPane);
        chatPanel.add(new JLabel("Message"));
        chatPanel.add(messageTextField);
        JPanel tmp = new JPanel(new FlowLayout());
        tmp.add(sendBtn);
        tmp.add(emoteBtn);

        chatPanel.add(tmp);
        this.getContentPane().add(chatPanel, BorderLayout.CENTER);
    }

    /**
     * Connect to the server (also used to disconnect if connected variable is true)
     */
    public void connect(){

        if (!connected){ //Connect to server
            if(nameTxtField.getText().isBlank()){
                JOptionPane.showMessageDialog(this, "Name field is empty !");
                return;
            }

            if (!ipTxtField.getText().matches("([0-9]+(\\.[0-9]+)+)")){
                JOptionPane.showMessageDialog(this,"IP format is incorrect !");
                return;
            }

            if(!portTxtField.getText().matches("[0-9]+")){
                JOptionPane.showMessageDialog(this, "Port format is incorrect");
                return;
            }



            System.out.printf("Trying to reach server : %s@%s -p %s%n", nameTxtField.getText(), ipTxtField.getText(), portTxtField.getText());

            Socket serverConnexion;
            try {
                serverConnexion = new Socket(ipTxtField.getText(), Integer.parseInt(portTxtField.getText()));
            } catch (IOException e) {
                e.printStackTrace();
                JOptionPane.showMessageDialog(this, "Can't reach server !\n\n" + e.getMessage());
                return;
            }

            System.out.println("Connected to server");
            this.chatManager = new ChatManager(serverConnexion, chatTextPane, messageTextField, sendBtn, nameTxtField.getText(), connectedList, this, typingTextPane);
            connexionBtn.setText("Disconnect");

            nameTxtField.setEnabled(false);
            ipTxtField.setEnabled(false);
            portTxtField.setEnabled(false);

            messageTextField.grabFocus();
            connected = true;

        }else{ //Disconnect from server
            messageTextField.setText("%99%");
            sendBtn.doClick();

            connexionBtn.setText("Connect");

            nameTxtField.setEnabled(true);
            ipTxtField.setEnabled(true);
            portTxtField.setEnabled(true);

            chatTextPane.setText("");
            typingTextPane.setText("");

            connectedList.setModel(new DefaultListModel());

            this.chatManager.disconnect();

            connected = false;
        }



    }



}
