import javax.swing.*;

import com.formdev.flatlaf.intellijthemes.materialthemeuilite.*;

public class SuperChat3000 {
    /**
     * The entry point of application.
     *
     * @param args the input arguments
     */
    public static void main(String[] args) {

        //Setting up the theme
        FlatMoonlightContrastIJTheme.setup();


        //initiate a new client window
        JFrame mainFrame = new SuperChat3000Frame();
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.pack();

        //Display the window centered on the screen
        mainFrame.setLocationRelativeTo(null);
        mainFrame.setVisible(true);

    }
}
