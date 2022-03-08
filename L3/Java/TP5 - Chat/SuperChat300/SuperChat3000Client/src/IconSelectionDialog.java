import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.util.HashMap;
import java.util.Map;

/**
 * Dialog used to select emote
 */
public class IconSelectionDialog extends VerticalPanel {

    private final Map<String, ImageIcon> emoteMap;
    private final JList<String> emoteJList;

    /**
     * Gets emote JList.
     *
     * @return the emote JList
     */
    public JList<String> getEmoteJList() {
        return emoteJList;
    }

    /**
     * Instantiates a new Icon selection dialog.
     */
    public IconSelectionDialog() {

        emoteMap = new HashMap<>();

        populateEmoteMap();

        DefaultListModel<String> lm = new DefaultListModel<>();

        for (String emote : emoteMap.keySet()){
            lm.addElement(emote);
        }

        emoteJList = new JList<>(lm);

        emoteJList.setCellRenderer(new DefaultListCellRenderer(){ //Customise a ListCellRenderer to display emote name with corresponding Icon
            @Override
            public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {

                JLabel label = (JLabel) super.getListCellRendererComponent(list, value,index,isSelected,cellHasFocus);

                label.setIcon(emoteMap.get((String) value));
                label.setHorizontalTextPosition(JLabel.RIGHT);
                return label;
            }
        });


        this.add(new JScrollPane(emoteJList));

        //Show a popup with this dialog content
        JOptionPane.showMessageDialog(null, this, "Choose an emote", JOptionPane.DEFAULT_OPTION);
    }

    //Get emotes Icon and name from resources files
    private void populateEmoteMap() {
        File dir = null;

        dir = new File("img" + File.separator + "emotes");

        for (File emoteFile : dir.listFiles()) {
            String emoteName = emoteFile.getName().split("\\.")[0].replace("EMO", "");

            this.emoteMap.put(emoteName, new ImageIcon("img" + File.separator + "emotes" + File.separator + emoteFile.getName()));
        }

    }

}