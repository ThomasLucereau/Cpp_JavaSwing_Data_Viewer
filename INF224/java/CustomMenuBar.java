
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CustomMenuBar extends JMenuBar {
    
    JMenu fileMenu = new JMenu("File");

    JToolBar toolBar = new JToolBar();

    class ItemMenu extends AbstractAction {
        
        public ItemMenu(String text) {
            super(text);
        }

        public void actionPerformed(ActionEvent e) {
            System.out.println("Action: " + getValue(Action.NAME));
        }
    }

    public CustomMenuBar() {
        add(fileMenu);
        fileMenu.add(new JMenuItem(new ItemMenu("New")));
        fileMenu.add(new JMenuItem(new ItemMenu("Open")));
        fileMenu.add(new JMenuItem(new ItemMenu("Save")));
        fileMenu.add(new JMenuItem(new ItemMenu("Exit")));

        add(toolBar);
        toolBar.add(new JButton(new ItemMenu("New")));
        toolBar.add(new JButton(new ItemMenu("Open")));
        toolBar.add(new JButton(new ItemMenu("Save")));
        toolBar.add(new JButton(new ItemMenu("Exit")));
    
    }




}