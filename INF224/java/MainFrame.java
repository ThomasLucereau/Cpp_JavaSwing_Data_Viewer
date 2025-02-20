
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;



public class MainFrame extends JFrame {  // on crée une classe MainFrame qui hérite de JFrame
 
    private static final long serialVersionUID = 1L;
    
    private JTextArea textArea = new JTextArea(10, 40);
    private TexteButton texteButton = new TexteButton("Texte1");
    private TexteButton texteButton2 = new TexteButton("Texte2");
    private EndButton endButton = new EndButton("End");
    private CustomMenuBar customMenuBar = new CustomMenuBar();

    class TexteButton extends JButton {  // on crée une classe TexteButton qui hérite de JButton (3eme version)

        public TexteButton(String text) {
            super(text);
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    textArea.setText(text);
                }
            });
        }
    }

    class EndButton extends JButton {  // de même pour la classe endButton

        public EndButton(String text) {
            super(text);
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    System.exit(0);
                }
            });
        }
    }

    public MainFrame() {
        super("Main Frame");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 500);
        pack();

        BorderLayout layout = new BorderLayout();
        setLayout(layout);

        add(textArea, BorderLayout.CENTER); // on ajoute le textArea au centre de la fenêtre
        add(customMenuBar, BorderLayout.NORTH);

        JPanel panel = new JPanel();        
        panel.add(texteButton);
        panel.add(texteButton2);
        panel.add(endButton);
        add(panel, BorderLayout.SOUTH); // on ajoute les boutons en bas de la fenêtre
        setVisible(true);
    }

}


