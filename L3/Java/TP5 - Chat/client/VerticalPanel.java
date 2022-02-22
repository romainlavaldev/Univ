import javax.swing.*;

public class VerticalPanel extends JPanel{

    public VerticalPanel(){
        super();
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    }
}
