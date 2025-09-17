
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;


// Répond à la question de la partie Java

public class MainFrame extends JFrame {  // on crée une classe MainFrame qui hérite de JFrame
 
    private static final long serialVersionUID = 1L;
    
    private JTextArea textArea = new JTextArea(10, 40);
    private EndButton endButton = new EndButton("End");
    private CustomMenuBar customMenuBar = new CustomMenuBar(this);
    private JToolBar toolBar = new JToolBar();

    class TexteButton extends JButton {  // on crée une classe TexteButton qui hérite de JButton (3eme version)

        public TexteButton(String text)  {
            super(text);
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    textArea.append(text + "\n");
                    try {
                        String response = client.send(text);
                        textArea.append(response);
                        System.out.println("Response: "+ response + "\n");
                    }
                    catch (Exception i) {
                        System.err.println("Client: IO error");
                        return;
                    }
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
                    System.exit(0);
                }
            });
        }
    }

    public MainFrame() {
        super("Main Frame");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 500);


    
        setLayout(new BorderLayout());

        setJMenuBar(customMenuBar);

        toolBar.add(new TexteButton("print"));
        toolBar.add(new TexteButton("play"));
        toolBar.add(new EndButton("Exit"));
        add(toolBar, BorderLayout.NORTH);

        add(new JScrollPane(textArea), BorderLayout.CENTER); // on ajoute le textArea au centre de la fenêtre
        
        /*

        JPanel panel = new JPanel();        
        panel.add(texteButton);
        panel.add(texteButton2);
        panel.add(endButton);
        add(panel, BorderLayout.SOUTH); // on ajoute les boutons en bas de la fenêtre
        pack();
        */
        setVisible(true);
    }

    public void appendText(String text) {
        textArea.append(text + "\n");
    }

    public String getTextArea() { // on crée une méthode getTextArea qui renvoie la dernière ligne du textArea
        String[] lines = textArea.getText().split("\n");
        if (lines.length == 0) return null;
        String lastLine = lines[lines.length - 1];
        return lastLine;
    }

}


