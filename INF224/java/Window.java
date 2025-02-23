/**
 * @file Window.java
 * @brief Client Java pour communiquer avec le Serveur C++.
 * @author Eric Lecolinet
 * @date 2015
 *
 * Ce fichier contient le code pour une fenêtre GUI qui permet à un client Java de se connecter à un serveur C++.
 * Il implémente l'interface utilisateur avec une barre de menu, une barre d'outils et un champ de texte pour interagir avec le serveur.
 * Le client envoie des commandes au serveur et affiche les réponses dans une zone de texte.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

/**
 * @class Window
 * @brief Fenêtre principale du client Java qui hérite de JFrame.
 *
 * Cette classe crée une fenêtre GUI permettant à l'utilisateur d'interagir avec le serveur via un client Java. 
 * Elle permet d'envoyer des commandes au serveur et d'afficher les réponses dans une zone de texte.
 */
public class Window extends JFrame {

  private static final long serialVersionUID = 1L;

  // Déclaration des composants graphiques
  static private JTextArea textArea = new JTextArea(20, 80); /**< Zone de texte pour afficher les réponses du serveur */
  private EndButton endButton = new EndButton("End"); /**< Bouton pour fermer l'application */
  private CustomMenuBar customMenuBar = new CustomMenuBar(); /**< Menu personnalisé pour la fenêtre */
  private JToolBar toolBar = new JToolBar(); /**< Barre d'outils contenant les boutons d'interaction */
  static final String DEFAULT_HOST = "localhost"; /**< Hôte par défaut du serveur */
  static final int DEFAULT_PORT = 3331; /**< Port par défaut du serveur */
  private Client client; /**< Instance du client */
  private BufferedReader input; /**< Flux de lecture pour recevoir les réponses du serveur */
  private BufferedWriter output; /**< Flux d'écriture pour envoyer des commandes au serveur */
  private Socket sock; /**< Socket pour la communication avec le serveur */
  private JTextField textField = new JTextField(20); /**< Champ de texte pour saisir des commandes */

  /**
   * @class TexteButton
   * @brief Bouton personnalisé pour envoyer des commandes au serveur.
   * 
   * Cette classe crée des boutons qui, lorsqu'ils sont pressés, envoient des commandes au serveur 
   * et affichent les réponses dans la zone de texte.
   */
  class TexteButton extends JButton {

    /**
     * @brief Constructeur de TexteButton.
     * @param text Le texte à afficher sur le bouton.
     */
    public TexteButton(String text) {
      super(text);
      addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          textArea.append("Command = " + text + textField.getText() + "\n");
          String response = send(text + textField.getText());
          textArea.append(response + "\n");
        }
      });
    }
  }

  /**
   * @class EndButton
   * @brief Bouton pour fermer l'application.
   * 
   * Cette classe crée un bouton "Exit" qui ferme l'application lorsque cliqué.
   */
  class EndButton extends JButton {

    /**
     * @brief Constructeur de EndButton.
     * @param text Le texte à afficher sur le bouton.
     */
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

  /**
   * @brief Constructeur de la fenêtre principale.
   * @param host L'hôte du serveur.
   * @param port Le port du serveur.
   * @throws UnknownHostException Si l'hôte est inconnu.
   * @throws IOException Si une erreur d'entrée/sortie se produit lors de la connexion au serveur.
   */
  public Window(String host, int port) throws UnknownHostException, IOException {
    super("Media Handler");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setSize(800, 1200);

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

    add(new JScrollPane(textArea), BorderLayout.CENTER); // Ajout de la zone de texte au centre

    try {
      sock = new java.net.Socket(host, port); // Connexion au serveur
    } catch (java.net.UnknownHostException e) {
      System.err.println("Client: Couldn't find host " + host + ":" + port);
      throw e;
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't reach host " + host + ":" + port);
      throw e;
    }

    try {
      input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
      output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
    } catch (java.io.IOException e) {
      textArea.setText("Client: Couldn't open input or output streams");
      throw e;
    }

    String response = send("Opening");
    textArea.append("Files managed are : " + response + "\n");
    setVisible(true);
  }

  /**
   * @brief Envoie une requête au serveur et retourne la réponse.
   * @param request La commande à envoyer au serveur.
   * @return La réponse du serveur.
   */
  public String send(String request) {
    try {
      request += "\n"; // Ajouter le séparateur de lignes
      output.write(request, 0, request.length());
      output.flush();
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't send message: " + e);
      return null;
    }

    try {
      return input.readLine();
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't receive message: " + e);
      return null;
    }
  }

  /**
   * @class CustomMenuBar
   * @brief Barre de menu personnalisée pour la fenêtre.
   * 
   * Cette classe crée un menu avec des options "Print", "Play" et "Exit".
   */
  public class CustomMenuBar extends JMenuBar {

    JMenu fileMenu = new JMenu("File");

    /**
     * @class ItemMenu
     * @brief Item de menu qui déclenche l'envoi d'une commande au serveur.
     * 
     * Cette classe définit les actions associées aux éléments du menu (Print, Play, Exit).
     */
    class ItemMenu extends AbstractAction {

      /**
       * @brief Constructeur de l'élément de menu.
       * @param text Le texte de l'élément de menu.
       */
      public ItemMenu(String text) {
        super(text);
      }

      /**
       * @brief Action à effectuer lorsqu'un élément du menu est sélectionné.
       * @param e L'événement déclencheur.
       */
      public void actionPerformed(ActionEvent e) {
        if (getValue(Action.NAME).equals("Print")) {
          textArea.append("Command = print \n");
          String response = send("print " + textField.getText());
          textArea.append(response + "\n");
        } else if (getValue(Action.NAME).equals("Play")) {
          textArea.append("Command = play \n");
          String response = send("play " + textField.getText());
          textArea.append(response + "\n");
        } else if (getValue(Action.NAME).equals("Exit")) {
          textArea.append("Exit");
          System.exit(0);
        }
      }
    }

    /**
     * @brief Constructeur de la barre de menu personnalisée.
     */
    public CustomMenuBar() {
      fileMenu.add(new JMenuItem(new ItemMenu("Print")));
      fileMenu.add(new JMenuItem(new ItemMenu("Play")));
      fileMenu.add(new JMenuItem(new ItemMenu("Exit")));
      add(fileMenu);
    }
  }

  /**
   * @brief Point d'entrée principal de l'application.
   * @param argv Arguments de ligne de commande (hôte et port).
   */
  public static void main(String argv[]) {
    String host = DEFAULT_HOST;
    int port = DEFAULT_PORT;
    if (argv.length >= 1) host = argv[0];
    if (argv.length >= 2) port = Integer.parseInt(argv[1]);
    Window window = null;
    try {
      window = new Window(host, port);
    } catch (Exception e) {
      System.err.println("Client: Couldn't connect to " + host + ":" + port);
      System.exit(1);
    }

    System.out.println("Client connected to " + host + ":" + port);
  }
}
