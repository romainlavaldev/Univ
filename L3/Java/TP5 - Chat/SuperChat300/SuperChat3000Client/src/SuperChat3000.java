import javax.swing.*;

import com.formdev.flatlaf.intellijthemes.materialthemeuilite.*;

public class SuperChat3000 {
    public static void main(String[] args) {

        FlatMoonlightContrastIJTheme.setup();

        JFrame mainFrame = new SuperChat3000Frame("Super Chat 3000");
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.pack();

        mainFrame.setLocationRelativeTo(null);
        mainFrame.setVisible(true);

    }
}
