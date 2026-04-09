/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package UZ_GUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyVetoException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import org.jfree.chart.ChartPanel;

/**
 *
 * @author z002311d
 */
public class SendController implements ActionListener
{
    final static int LOG_INTERVALS[] = {10, 20, 100, 500, 1000, 10000, 60000, 600000, 3600000};
    final static long NUMBER_OF_MEASURES[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    private long loggingRate = 0;  //100 entspricht 10ms, also 0.01 s
    private long samplesPerEvent = 0;
    public boolean DarkLightModeChanged;
	
    //JAVASCOPE
    private Logger lg = Logger.getLogger("Chat");
    private UZ_GUI_view view;
    private UZ_SCOPE_view viewSCOPE;
    private Transmitter transmitter;
    private ChartPanel chPanel;
    
    private int chnum;

    private long SELECT_DATA_CH1_bits   = 201;
    private long SELECT_DATA_CH2_bits   = 202;
    private long SELECT_DATA_CH3_bits   = 203;
    private long SELECT_DATA_CH4_bits   = 204;
    
    private long SELECT_DATA_CH5_bits   = 205;
    private long SELECT_DATA_CH6_bits   = 206;
    private long SELECT_DATA_CH7_bits   = 207;
    private long SELECT_DATA_CH8_bits   = 208;
    
    private long SELECT_DATA_CH9_bits   = 209;
    private long SELECT_DATA_CH10_bits  = 210;
    private long SELECT_DATA_CH11_bits  = 211;
    private long SELECT_DATA_CH12_bits  = 212;
    
    private long SELECT_DATA_CH13_bits   = 213;
    private long SELECT_DATA_CH14_bits   = 214;
    private long SELECT_DATA_CH15_bits   = 215;
    private long SELECT_DATA_CH16_bits   = 216;
    
    private long SELECT_DATA_CH17_bits   = 217;
    private long SELECT_DATA_CH18_bits   = 218;
    private long SELECT_DATA_CH19_bits   = 219;
    private long SELECT_DATA_CH20_bits   = 220;
        
    //Get Button Mapping from javascope.h
    ArrayList<String> ButtonNames = ButtonNames = readSndButtonMappingFromFileLineByLine();

    // Constructor.
    public SendController(UZ_GUI_view view, UZ_SCOPE_view viewSCOPE, Transmitter transmitter, ChartPanel chPanel, int chnum, Properties prop)
    {
        this.view = view;
        this.viewSCOPE = viewSCOPE;
        this.transmitter = transmitter;
        this.chPanel = chPanel;

        //JAVASCOPE
        this.chnum = chnum;
        DarkLightModeChanged = false;
        view.getBtn_select_JavaScope().addActionListener(this);
        // Light mode deprecated; keep toggle hidden/disabled.
                
        //Control panel buttons
        viewSCOPE.getBtnEnSystem().addActionListener(this);
        viewSCOPE.getBtnEnSystem1().addActionListener(this);
        viewSCOPE.getBtnEnSystemDev().addActionListener(this);
        viewSCOPE.getBtnEnControl().addActionListener(this);
        viewSCOPE.getBtnEnControl1().addActionListener(this);
        viewSCOPE.getBtnEnControlDev().addActionListener(this);
        viewSCOPE.getBtnStop().addActionListener(this);
        viewSCOPE.getBtnStop1().addActionListener(this);
        viewSCOPE.getBtnStopDev().addActionListener(this);
        viewSCOPE.getBtnSetSendField_1().addActionListener(this);
        viewSCOPE.getBtnSetSendField_2().addActionListener(this);
        viewSCOPE.getBtnSetSendField_3().addActionListener(this);
        viewSCOPE.getBtnSetSendField_4().addActionListener(this);
        viewSCOPE.getBtnSetSendField_5().addActionListener(this);
        viewSCOPE.getBtnSetSendField_6().addActionListener(this);
        viewSCOPE.getBtnSetSendField_7().addActionListener(this);
        viewSCOPE.getBtnSetSendField_8().addActionListener(this);
        viewSCOPE.getBtnSetSendField_9().addActionListener(this);
        viewSCOPE.getBtnSetSendField_10().addActionListener(this);
        viewSCOPE.getBtnSetSendField_11().addActionListener(this);
        viewSCOPE.getBtnSetSendField_12().addActionListener(this);
        viewSCOPE.getBtnSetSendField_13().addActionListener(this);
        viewSCOPE.getBtnSetSendField_14().addActionListener(this);
        viewSCOPE.getBtnSetSendField_15().addActionListener(this);
        viewSCOPE.getBtnSetSendField_16().addActionListener(this);
        viewSCOPE.getBtnSetSendField_17().addActionListener(this);
        viewSCOPE.getBtnSetSendField_18().addActionListener(this);
        viewSCOPE.getBtnSetSendField_19().addActionListener(this);
        viewSCOPE.getBtnSetSendField_20().addActionListener(this);
        viewSCOPE.getBtnErrorReset().addActionListener(this);
        viewSCOPE.getMyBtn_1().addActionListener(this);
        viewSCOPE.getMyBtn_2().addActionListener(this);
        viewSCOPE.getMyBtn_3().addActionListener(this);
        viewSCOPE.getMyBtn_4().addActionListener(this);
        viewSCOPE.getMyBtn_5().addActionListener(this);
        viewSCOPE.getMyBtn_6().addActionListener(this);
        viewSCOPE.getMyBtn_7().addActionListener(this);
        viewSCOPE.getMyBtn_8().addActionListener(this);
        wireSendFieldEnterToSetButtons();
             
    }
    
    private void wireSendFieldEnterToSetButtons()
    {
        JTextField[] sendFields = getSendTextFields();
        JButton[] setButtons = getSendSetButtons();
        int count = Math.min(sendFields.length, setButtons.length);
        for (int index = 0; index < count; index++) {
            JTextField sendField = sendFields[index];
            JButton setButton = setButtons[index];
            if (sendField == null || setButton == null) {
                continue;
            }
            sendField.addActionListener(event -> setButton.doClick());
        }
    }

    private JTextField[] getSendTextFields()
    {
        return new JTextField[] {
            viewSCOPE.getTxt_snd_fld_1(), viewSCOPE.getTxt_snd_fld_2(), viewSCOPE.getTxt_snd_fld_3(), viewSCOPE.getTxt_snd_fld_4(),
            viewSCOPE.getTxt_snd_fld_5(), viewSCOPE.getTxt_snd_fld_6(), viewSCOPE.getTxt_snd_fld_7(), viewSCOPE.getTxt_snd_fld_8(),
            viewSCOPE.getTxt_snd_fld_9(), viewSCOPE.getTxt_snd_fld_10(), viewSCOPE.getTxt_snd_fld_11(), viewSCOPE.getTxt_snd_fld_12(),
            viewSCOPE.getTxt_snd_fld_13(), viewSCOPE.getTxt_snd_fld_14(), viewSCOPE.getTxt_snd_fld_15(), viewSCOPE.getTxt_snd_fld_16(),
            viewSCOPE.getTxt_snd_fld_17(), viewSCOPE.getTxt_snd_fld_18(), viewSCOPE.getTxt_snd_fld_19(), viewSCOPE.getTxt_snd_fld_20()
        };
    }

    private JButton[] getSendSetButtons()
    {
        return new JButton[] {
            viewSCOPE.getBtnSetSendField_1(), viewSCOPE.getBtnSetSendField_2(), viewSCOPE.getBtnSetSendField_3(), viewSCOPE.getBtnSetSendField_4(),
            viewSCOPE.getBtnSetSendField_5(), viewSCOPE.getBtnSetSendField_6(), viewSCOPE.getBtnSetSendField_7(), viewSCOPE.getBtnSetSendField_8(),
            viewSCOPE.getBtnSetSendField_9(), viewSCOPE.getBtnSetSendField_10(), viewSCOPE.getBtnSetSendField_11(), viewSCOPE.getBtnSetSendField_12(),
            viewSCOPE.getBtnSetSendField_13(), viewSCOPE.getBtnSetSendField_14(), viewSCOPE.getBtnSetSendField_15(), viewSCOPE.getBtnSetSendField_16(),
            viewSCOPE.getBtnSetSendField_17(), viewSCOPE.getBtnSetSendField_18(), viewSCOPE.getBtnSetSendField_19(), viewSCOPE.getBtnSetSendField_20()
        };
    }

    private String normalizeDecimalInput(String raw)
    {
        if (raw == null) {
            return "";
        }
        return raw.trim().replace(',', '.');
    }

    long getParamCmd(long bits, String s)
    {
        double value = 0;
        long retval = 0;
        boolean err = false;
        try
        {
            value = Double.parseDouble(normalizeDecimalInput(s));
        }
        catch(Exception ex) {
            JOptionPane.showMessageDialog(null, "Entered value is not a valid number", "Exception" , JOptionPane.INFORMATION_MESSAGE);
            retval = 0;
            err = true;
        }
        
        float val;
        val = (float) (value);
        long cmd = (long)Float.floatToIntBits(val); // get bit representation of value
        cmd = cmd << 32; 
        cmd |= (bits & 0xFFFFFFFF);    // append bits to value to form a 64bit long       
        retval = cmd;

        if (err == false)
            return retval;
        else 
            return 0;
    }

    private void printSelectDataCommands(ArrayList<Long> commands)
    {
        if (commands.size() > 1) {
            StringBuilder ids = new StringBuilder("ids=[");
            StringBuilder selected = new StringBuilder("selected=[");
            for (int commandIndex = 0; commandIndex < commands.size(); commandIndex++) {
                long command = commands.get(commandIndex);
                int idInt = (int) command;
                int valueBitsInt = (int) (command >>> 32);
                int selectedChannelNumber = Math.round(Float.intBitsToFloat(valueBitsInt));
                if (commandIndex > 0) {
                    ids.append(",");
                    selected.append(",");
                }
                ids.append(idInt);
                selected.append(selectedChannelNumber);
            }
            ids.append("]");
            selected.append("]");
            System.out.println("SendSelectData(all):\n  " + ids + "\n  " + selected);
            return;
        }

        StringBuilder message = new StringBuilder("SendSelectData: [");
        for (int commandIndex = 0; commandIndex < commands.size(); commandIndex++) {
            long command = commands.get(commandIndex);
            int idInt = (int) command;
            int valueBitsInt = (int) (command >>> 32);
            int selectedChannelNumber = Math.round(Float.intBitsToFloat(valueBitsInt));
            if (commandIndex > 0) {
                message.append(", ");
            }
            message.append("(idInt=").append(idInt)
                   .append(", selectedChannelNumber=").append(selectedChannelNumber)
                   .append(")");
        }
        message.append("]");
        System.out.println(message.toString());
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object quelle = e.getSource();
        
        //JAVASCOPE                
        if (quelle == view.getBtn_select_JavaScope()) {
            try {
                viewSCOPE.setMaximum(true);
            } catch (PropertyVetoException ex) {
            // Vetoed by internalFrame
            }
            viewSCOPE.toFront();
        }
        
        
        //Control panel
        else if( quelle == viewSCOPE.getBtnSetSendField_1())
        {  
            ArrayList<Long> commands = new ArrayList<Long>();    
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_1"), viewSCOPE.getTxt_snd_fld_1().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_2())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_2"), viewSCOPE.getTxt_snd_fld_2().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_3())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_3"), viewSCOPE.getTxt_snd_fld_3().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_4())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_4"), viewSCOPE.getTxt_snd_fld_4().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_5())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_5"), viewSCOPE.getTxt_snd_fld_5().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_6())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_6"), viewSCOPE.getTxt_snd_fld_6().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_7())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_7"), viewSCOPE.getTxt_snd_fld_7().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_8())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_8"), viewSCOPE.getTxt_snd_fld_8().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_9())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_9"), viewSCOPE.getTxt_snd_fld_9().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_10())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_10"), viewSCOPE.getTxt_snd_fld_10().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_11())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_11"), viewSCOPE.getTxt_snd_fld_11().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_12())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_12"), viewSCOPE.getTxt_snd_fld_12().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_13())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_13"), viewSCOPE.getTxt_snd_fld_13().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_14())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_14"), viewSCOPE.getTxt_snd_fld_14().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_15())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_15"), viewSCOPE.getTxt_snd_fld_15().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_16())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_16"), viewSCOPE.getTxt_snd_fld_16().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_17())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_17"), viewSCOPE.getTxt_snd_fld_17().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_18())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_18"), viewSCOPE.getTxt_snd_fld_18().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_19())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_19"), viewSCOPE.getTxt_snd_fld_19().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewSCOPE.getBtnSetSendField_20())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(getParamCmd(ButtonNames.indexOf("Set_Send_Field_20"), viewSCOPE.getTxt_snd_fld_20().getText()  ));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
       
        
        
        
        //My Button 1
        else if(quelle == viewSCOPE.getMyBtn_1())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_1");     
            transmitter.setCommand(cmd);      
            
        }        
        
        //My Button 2
        else if(quelle == viewSCOPE.getMyBtn_2())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_2");              
            transmitter.setCommand(cmd);           
        }
        
        //My Button 3
        else if(quelle == viewSCOPE.getMyBtn_3())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_3");              
            transmitter.setCommand(cmd);           
        }

        //My Button 4
        else if(quelle == viewSCOPE.getMyBtn_4())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_4");              
            transmitter.setCommand(cmd);           
        }

        //My Button 5
        else if(quelle == viewSCOPE.getMyBtn_5())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_5");              
            transmitter.setCommand(cmd);           
        }

        //My Button 6
        else if(quelle == viewSCOPE.getMyBtn_6())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_6");              
            transmitter.setCommand(cmd);           
        }

        //My Button 7
        else if(quelle == viewSCOPE.getMyBtn_7())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_7");              
            transmitter.setCommand(cmd);           
        }

        //My Button 8
        else if(quelle == viewSCOPE.getMyBtn_8())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("My_Button_8");              
            transmitter.setCommand(cmd);           
        }        
        
        //ERROR RESET
        else if(quelle == viewSCOPE.getBtnErrorReset())
        {    
            long cmd;                     
            cmd = ButtonNames.indexOf("Error_Reset");              
            transmitter.setCommand(cmd);                     
        }
        else if(quelle == viewSCOPE.getBtnEnSystem() || quelle == viewSCOPE.getBtnEnSystem1() || quelle == viewSCOPE.getBtnEnSystemDev())
        {
            long cmd;
            cmd = ButtonNames.indexOf("Enable_System");
            transmitter.setCommand(cmd);
        }
        else if( quelle == viewSCOPE.getBtnEnControl() || quelle == viewSCOPE.getBtnEnControl1() || quelle == viewSCOPE.getBtnEnControlDev())
        {    
            long cmd;
            cmd = ButtonNames.indexOf("Enable_Control");  
            transmitter.setCommand(cmd);                
        } 
        else if( quelle == viewSCOPE.getBtnStop() || quelle == viewSCOPE.getBtnStop1() || quelle == viewSCOPE.getBtnStopDev())
        {   
            long cmd;
            cmd = ButtonNames.indexOf("Stop");
            transmitter.setCommand(cmd);
        }

    }  
    
    
        /**
     * returns true, if the look and feel changed since the call of the update-function
     * 
     * @return bool
     */
    public boolean did_LookAndFeel_change(){
        return DarkLightModeChanged;
    }
    
    /**
     * resets the variable, which indicates,that the LookAndFeels has changed
     * 
     */
    public void reset_LookAndFeel_change() {
        DarkLightModeChanged = false;
    }
    
    
        public ArrayList<String> readSndButtonMappingFromFileLineByLine() {
        ArrayList<String> ButtonNames = new ArrayList<String>();
        try {
            final String startMarker = "GUI_BTN_ZEROVALUE=0";
            final String endMarker = "GUI_BTN_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.IDENTIFIER
            );
            if (section.getStartMarkerCount() != 1 || section.getEndMarkerCount() != 1) {
                String fileLabel = section.getSourceFile() == null ? "javascope.h" : section.getSourceFile().getAbsolutePath();
                JOptionPane.showMessageDialog(
                    null,
                    "Invalid File: " + fileLabel + "\n"
                        + "Section 'gui_button_mapping' must contain exactly one start marker and one end marker.\n"
                        + "Start marker '" + startMarker + "' found " + section.getStartMarkerCount() + " time(s).\n"
                        + "End marker '" + endMarker + "' found " + section.getEndMarkerCount() + " time(s).",
                    "Error",
                    JOptionPane.INFORMATION_MESSAGE
                );
            }
            ButtonNames = section.getEntries();
            if (ButtonNames.isEmpty()) {
                ButtonNames.add("GUI_BTN_ZEROVALUE");
            }

        } catch (IOException ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, ex.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
        
    return ButtonNames;

    }

    /**
     * Sends select data commands for all 20 channels.
     * Called automatically on connection and when clicking "sendSelectData (all)" button.
     */
    public void sendSelectDataAll()
    {
        ArrayList<Long> commands = new ArrayList<Long>();

        int idx1 = viewSCOPE.getComboSelectData1().getSelectedIndex();
        int idx2 = viewSCOPE.getComboSelectData2().getSelectedIndex();
        int idx3 = viewSCOPE.getComboSelectData3().getSelectedIndex();
        int idx4 = viewSCOPE.getComboSelectData4().getSelectedIndex();

        int idx5 = viewSCOPE.getComboSelectData5().getSelectedIndex();
        int idx6 = viewSCOPE.getComboSelectData6().getSelectedIndex();
        int idx7 = viewSCOPE.getComboSelectData7().getSelectedIndex();
        int idx8 = viewSCOPE.getComboSelectData8().getSelectedIndex();

        int idx9 = viewSCOPE.getComboSelectData9().getSelectedIndex();
        int idx10 = viewSCOPE.getComboSelectData10().getSelectedIndex();
        int idx11 = viewSCOPE.getComboSelectData11().getSelectedIndex();
        int idx12 = viewSCOPE.getComboSelectData12().getSelectedIndex();

        int idx13 = viewSCOPE.getComboSelectData13().getSelectedIndex();
        int idx14 = viewSCOPE.getComboSelectData14().getSelectedIndex();
        int idx15 = viewSCOPE.getComboSelectData15().getSelectedIndex();
        int idx16 = viewSCOPE.getComboSelectData16().getSelectedIndex();

        int idx17 = viewSCOPE.getComboSelectData17().getSelectedIndex();
        int idx18 = viewSCOPE.getComboSelectData18().getSelectedIndex();
        int idx19 = viewSCOPE.getComboSelectData19().getSelectedIndex();
        int idx20 = viewSCOPE.getComboSelectData20().getSelectedIndex();

        commands.add(getParamCmd(SELECT_DATA_CH1_bits,  Integer.toString(idx1)));
        commands.add(getParamCmd(SELECT_DATA_CH2_bits,  Integer.toString(idx2)));
        commands.add(getParamCmd(SELECT_DATA_CH3_bits,  Integer.toString(idx3)));
        commands.add(getParamCmd(SELECT_DATA_CH4_bits,  Integer.toString(idx4)));
        commands.add(getParamCmd(SELECT_DATA_CH5_bits,  Integer.toString(idx5)));
        commands.add(getParamCmd(SELECT_DATA_CH6_bits,  Integer.toString(idx6)));
        commands.add(getParamCmd(SELECT_DATA_CH7_bits,  Integer.toString(idx7)));
        commands.add(getParamCmd(SELECT_DATA_CH8_bits,  Integer.toString(idx8)));
        commands.add(getParamCmd(SELECT_DATA_CH9_bits,  Integer.toString(idx9)));
        commands.add(getParamCmd(SELECT_DATA_CH10_bits, Integer.toString(idx10)));
        commands.add(getParamCmd(SELECT_DATA_CH11_bits, Integer.toString(idx11)));
        commands.add(getParamCmd(SELECT_DATA_CH12_bits, Integer.toString(idx12)));
        commands.add(getParamCmd(SELECT_DATA_CH13_bits, Integer.toString(idx13)));
        commands.add(getParamCmd(SELECT_DATA_CH14_bits, Integer.toString(idx14)));
        commands.add(getParamCmd(SELECT_DATA_CH15_bits, Integer.toString(idx15)));
        commands.add(getParamCmd(SELECT_DATA_CH16_bits, Integer.toString(idx16)));
        commands.add(getParamCmd(SELECT_DATA_CH17_bits, Integer.toString(idx17)));
        commands.add(getParamCmd(SELECT_DATA_CH18_bits, Integer.toString(idx18)));
        commands.add(getParamCmd(SELECT_DATA_CH19_bits, Integer.toString(idx19)));
        commands.add(getParamCmd(SELECT_DATA_CH20_bits, Integer.toString(idx20)));

        transmitter.setCommandList(commands);
        printSelectDataCommands(commands);
    }

    private long getSelectDataChannelBits(int channelIndexZeroBased)
    {
        switch (channelIndexZeroBased) {
            case 0: return SELECT_DATA_CH1_bits;
            case 1: return SELECT_DATA_CH2_bits;
            case 2: return SELECT_DATA_CH3_bits;
            case 3: return SELECT_DATA_CH4_bits;
            case 4: return SELECT_DATA_CH5_bits;
            case 5: return SELECT_DATA_CH6_bits;
            case 6: return SELECT_DATA_CH7_bits;
            case 7: return SELECT_DATA_CH8_bits;
            case 8: return SELECT_DATA_CH9_bits;
            case 9: return SELECT_DATA_CH10_bits;
            case 10: return SELECT_DATA_CH11_bits;
            case 11: return SELECT_DATA_CH12_bits;
            case 12: return SELECT_DATA_CH13_bits;
            case 13: return SELECT_DATA_CH14_bits;
            case 14: return SELECT_DATA_CH15_bits;
            case 15: return SELECT_DATA_CH16_bits;
            case 16: return SELECT_DATA_CH17_bits;
            case 17: return SELECT_DATA_CH18_bits;
            case 18: return SELECT_DATA_CH19_bits;
            case 19: return SELECT_DATA_CH20_bits;
            default: return -1;
        }
    }

    public void sendSelectDataSingle(int channelIndexZeroBased, int selectedIndex)
    {
        long selectDataBits = getSelectDataChannelBits(channelIndexZeroBased);
        if (selectDataBits < 0) {
            return;
        }
        ArrayList<Long> commands = new ArrayList<Long>();
        commands.add(getParamCmd(selectDataBits, Integer.toString(selectedIndex)));
        transmitter.setCommandList(commands);
        printSelectDataCommands(commands);
    }

}
