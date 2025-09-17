//
// Client Java pour communiquer avec le Serveur C++ 
// eric lecolinet - telecom paristech - 2015
//

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

// repond a la question 3 de la partie Java et implément le client Java

// Répond à la question de la partie Java

public class Window extends JFrame {  // on crée une classe MainFrame qui hérite de JFrame
 
  private static final long serialVersionUID = 1L;
    
  static private JTextArea textArea = new JTextArea(20, 80);
  private EndButton endButton = new EndButton("End");
  private CustomMenuBar customMenuBar = new CustomMenuBar();
  private JToolBar toolBar = new JToolBar();
  static final String DEFAULT_HOST = "localhost";
  static final int DEFAULT_PORT = 3331;
  private Client client;
  private BufferedReader input;
  private BufferedWriter output;
  private Socket sock; 
  private JTextField textField = new JTextField(20);

    class TexteButton extends JButton {  // on crée une classe TexteButton qui hérite de JButton (3eme version)

        public TexteButton(String text)  {
            super(text);
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    textArea.append("Command = " + text + textField.getText() +"\n");
                    String response = send(text + textField.getText());
                    textArea.append(response + "\n");
                    
                    
                    

                }
            });
        }
    }

    class EndButton extends JButton {  // de même pour la classe endButton

        public EndButton(String text) {
            super(text);
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    textArea.append("Exit \n");
                    System.exit(2);
                }
            });
        }
    }

    public Window(String host, int port) throws UnknownHostException, IOException {
        super("Media Handler");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize( 800, 1200);

        this.client = client;
        setLayout(new BorderLayout());

        setJMenuBar(customMenuBar);
        textField.setText("Type the name of desired doc");
        toolBar.add(textField);
        toolBar.add(new TexteButton("print "));
        toolBar.add(new TexteButton("play "));
        toolBar.add(new TexteButton("group "));
        toolBar.add(new EndButton("Exit"));
        add(toolBar, BorderLayout.NORTH);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(new TexteButton("remove "));
        panel.add(new TexteButton("add "));
        
        add(panel, BorderLayout.EAST);
        setPreferredSize(new Dimension(800, 600));
        pack();
        

        add(new JScrollPane(textArea), BorderLayout.CENTER); // on ajoute le textArea au centre de la fenêtre
        
        try {
          sock = new java.net.Socket(host, port);
        }
        catch (java.net.UnknownHostException e) {
          System.err.println("Client: Couldn't find host "+host+":"+port);
          throw e;
        }
        catch (java.io.IOException e) {
          System.err.println("Client: Couldn't reach host "+host+":"+port);
          throw e;
        }

        try {
          input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
          output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        }
        catch (java.io.IOException e) {
            textArea.setText("Client: Couldn't open input or output streams");
            throw e;
        }
      
        String response = send("Opening");
        textArea.append("Files managed are : " + response + "\n");
        setVisible(true);
    }
    
    public String send(String request) {
        // Envoyer la requete au serveur
        

      try {
        request += "\n";  // ajouter le separateur de lignes
        output.write(request, 0, request.length());
        output.flush();
        
      }
      catch (java.io.IOException e) {
        System.err.println("Client: Couldn't send message: " + e);
        return null;
      }
      
      // Recuperer le resultat envoye par le serveur
      try {
        return input.readLine();
      }
      catch (java.io.IOException e) {
        System.err.println("Client: Couldn't receive message: " + e);
        return null;
      }
    }

    

  public class CustomMenuBar extends JMenuBar {
    
    JMenu fileMenu = new JMenu("File");

    class ItemMenu extends AbstractAction {
        
        public ItemMenu(String text ) {
            super(text);
        
        }

        public void actionPerformed(ActionEvent e) {
            if (getValue(Action.NAME).equals("Print")) {
                textArea.append("Command = print \n");
                String response = send("print " + textField.getText());
                textArea.append(response + "\n");

            }
            else if (getValue(Action.NAME).equals("Play")) {
                textArea.append("Command = play \n");
                String response = send("play " + textField.getText());
                textArea.append(response + "\n");
                
            }
            else if (getValue(Action.NAME).equals("Exit")) {
                textArea.append("Exit");
                System.exit(0);
            }
        }
    }

    public CustomMenuBar() {
        
        fileMenu.add(new JMenuItem(new ItemMenu("Print")));
        fileMenu.add(new JMenuItem(new ItemMenu("Play")));
        fileMenu.add(new JMenuItem(new ItemMenu("Exit")));

        add(fileMenu);
    }




}
public static void main(String argv[]) {
  String host = DEFAULT_HOST;
  int port = DEFAULT_PORT;
  if (argv.length >=1) host = argv[0];
  if (argv.length >=2) port = Integer.parseInt(argv[1]);
  Window window = null;
  try {
    window = new Window(host, port);
  }
  catch (Exception e) {
    System.err.println("Client: Couldn't connect to "+host+":"+port);
    System.exit(1);
  }
  
  System.out.println("Client connected to "+host+":"+port);

}

}







