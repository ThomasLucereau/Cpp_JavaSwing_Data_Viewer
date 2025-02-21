
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

// répond à la question 2 de la partie

public class CustomMenuBar extends JMenuBar {
    
    JMenu fileMenu = new JMenu("File");

    static class ItemMenu extends AbstractAction {
        
        public ItemMenu(String text) {
            super(text);
        }

        public void actionPerformed(ActionEvent e) {
            if (getValue(Action.NAME).equals("Print")) {
                System.out.println("Print");
            }
            else if (getValue(Action.NAME).equals("Play")) {
                System.out.println("Play");
            }
            else if (getValue(Action.NAME).equals("Exit")) {
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