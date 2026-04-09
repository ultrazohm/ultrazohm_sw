/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;


import com.formdev.flatlaf.FlatDarkLaf;
import java.awt.CardLayout;
import java.awt.BorderLayout;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStream;
import java.io.Reader;
import java.time.Instant;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.UIManager;
import javax.swing.plaf.basic.BasicInternalFrameUI;
import javax.swing.plaf.InternalFrameUI;
import javax.swing.JDesktopPane;
import javax.swing.SwingUtilities;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.LegendItemCollection;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import java.beans.PropertyVetoException;
import java.awt.Color;
import java.awt.Font;
import java.awt.BasicStroke;
/*Some changes have been made here*/

/**
 *
 * @author LoehdefinkPh
 */
public class Start {

    private static final DateTimeFormatter BUILD_TIMESTAMP_FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss z").withZone(ZoneId.of("Europe/Berlin"));
    
    private Reader propreader;

    public Start()
    {
        System.setProperty("flatlaf.useNativeLibrary", "false");
        Color accentViolet = new Color(0x7C, 0x3A, 0xED);
        // ------------ Properties ---------------
        File propertiesFile = new File("properties.ini");
        System.out.println("Using properties.ini: " + propertiesFile.getAbsolutePath());
        try {
            propreader = new FileReader(propertiesFile);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ReceiveController.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, ex.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
        Properties prop = new Properties();
        try {
            prop.load(propreader);
        } catch (Exception ex) {
            Logger.getLogger(ReceiveController.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, ex.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
        PropertyFileDiagnostics propertyDiagnostics = PropertyFileDiagnostics.loadDefault();
        boolean autoDetectSamplingRate = parseBooleanProperty(prop, "autoDetectSamplingRate", false);
        boolean sendZeroAckCommand = parseBooleanProperty(prop, "sendZeroAckCommand", true);
        boolean scopeDevTabEnabled = parseBooleanProperty(prop, "ScopeDevTab", false);
        boolean parameterIDEnabled = parseBooleanProperty(prop, "ParameterID", false);
        System.out.println("buildTimestamp = " + readBuildTimestamp());
        System.out.println("autoDetectSamplingRate = " + (autoDetectSamplingRate ? "1" : "0"));
        System.out.println("sendZeroAckCommand = " + (sendZeroAckCommand ? "1" : "0"));
        System.out.println("ScopeDevTab = " + (scopeDevTabEnabled ? "1" : "0"));
        System.out.println("ParameterID = " + (parameterIDEnabled ? "1" : "0"));
        File javascopeHeader = resolveJavascopeHeaderFile();
        System.out.println("Using " + javascopeHeader.getAbsolutePath());
        boolean isDarkMode = true;
        try
        {
            UIManager.setLookAndFeel( new FlatDarkLaf() );
            UIManager.getLookAndFeelDefaults().put("defaultFont", new Font("SansSerif", Font.PLAIN, 13));
            applyUITheme(true, accentViolet);
        }
        catch (Exception ex)
        {
            JOptionPane.showMessageDialog(null, ex);
        }
        
        int chnum = parseIntProperty(prop, propertyDiagnostics, "scopeChannelNumber", 20);
        if (chnum < 1 || chnum > 20) {
            int clamped = Math.max(1, Math.min(20, chnum));
            propertyDiagnostics.printValidationIssue(
                    "scopeChannelNumber",
                    "Value " + chnum + " is outside supported range [1..20]. Using " + clamped + "."
            );
            chnum = clamped;
        }
            
        // how to read into an Array
        //String[] values = prop.get("initScaleCHx").toString().split(";");
        //for (int i=0; i<values.length; i++)     System.out.println("prop = " + Double.parseDouble(values[i]));
        // -----------------------------------------------
        
        int demo_mode = 0; // demo_mode for offline testing
        UZ_GUI_view sview = new UZ_GUI_view();
        Transmitter transmitter = new Transmitter(demo_mode, prop, sview); 
        JDesktopPane desktopMain = new JDesktopPane();
        UZ_SCOPE_view viewSCOPE = new UZ_SCOPE_view(){
           @Override
           public void setUI(InternalFrameUI ui) {
               super.setUI(ui); // this gets called internally when updating the ui and makes the northPane reappear
               BasicInternalFrameUI frameUI = (BasicInternalFrameUI) getUI(); 
               if (frameUI != null) frameUI.setNorthPane(null); 
           }
        };
        UZ_ParaID_view viewParaID = new UZ_ParaID_view(){
           @Override
            public void setUI(InternalFrameUI ui) {
               super.setUI(ui); // this gets called internally when updating the ui and makes the northPane reappear
               BasicInternalFrameUI frameUI = (BasicInternalFrameUI) getUI();
               if (frameUI != null) frameUI.setNorthPane(null);
            }
        };
        viewSCOPE.setScopeDevTabVisible(scopeDevTabEnabled);
        sview.add(desktopMain,BorderLayout.CENTER);
        desktopMain.add(viewSCOPE);
        desktopMain.add(viewParaID);
        viewParaID.setVisible(false);
        //Sets internalJFrames to the max size avaivable
        try {
            viewSCOPE.setMaximum(true);
        } catch (PropertyVetoException e) {
            // Vetoed by internalFrame
        }
        
        //Set only Javascope visible after startup
        viewSCOPE.setVisible(true);
        viewSCOPE.toFront();
        DecimalSeparatorSupport.installOnContainer(sview);
        DecimalSeparatorSupport.installOnContainer(viewSCOPE);
        DecimalSeparatorSupport.installOnContainer(viewParaID);
               
        
        JFreeChart chart = ChartFactory.createXYLineChart(null, "Time (s)", "Values", null);
        chart.setBackgroundPaint(null);
        chart.getXYPlot().setBackgroundPaint(Color.white);
        chart.getXYPlot().setDomainGridlinePaint(Color.black);
        chart.getXYPlot().setRangeGridlinePaint(Color.black);
        chart.getLegend().setBackgroundPaint(null);
        chart.getLegend().setItemPaint(Color.black);
        ChartPanel chPanel = new ScopeChartPanel(chart);
        CardLayout cl = (CardLayout)(viewSCOPE.getGraphJFree().getLayout());
        viewSCOPE.getGraphJFree().add(chPanel, "graphJFree"); 
        cl.show(viewSCOPE.getGraphJFree(), "graphJFree");
        
 
        //--------------------JavaScope------------------------------------------  
        
        // for setting fixed Legend items --------------------------
        XYSeriesCollection dataset = new XYSeriesCollection();
        XYSeries[] ser = new XYSeries[chnum];
        String Colorcodes[] = new String[] {
            "#FF4444", "#44FF44", "#4488FF", "#FFD644", "#44DDDD",
            "#FF44FF", "#FF8833", "#33FF99", "#AA66FF", "#FF6699",
            "#66CCFF", "#AAFF33", "#FF9977", "#33FFCC", "#CC88FF",
            "#FFAA22", "#88FFAA", "#FF77AA", "#7799FF", "#FFCC66"
        };
        for (int s=0; s < chnum; s++) {
            ser[s] = new XYSeries("CH"+(s+1));
            dataset.addSeries(ser[s]);
            chPanel.getChart().getXYPlot().getRenderer().setSeriesStroke(s, new BasicStroke(2.0f));
            chPanel.getChart().getXYPlot().getRenderer().setSeriesPaint(s, Color.decode(Colorcodes[s]));
        }
        chPanel.getChart().getXYPlot().setDataset(dataset);
        chPanel.repaint();
        LegendItemCollection legendItems = chPanel.getChart().getXYPlot().getLegendItems();
        chPanel.getChart().getXYPlot().setFixedLegendItems(legendItems); 
        chPanel.getChart().getLegend().setItemFont(new Font("SansSerif", Font.BOLD, 13));
        if(isDarkMode){
            //Sets up the Scope Background to the DarkMode
            Color chartText = new Color(0xD1, 0xD5, 0xDB);
            Color chartGrid = new Color(0x4A, 0x4D, 0x52);
            Color chartBg = new Color(0x26, 0x29, 0x2E);
            chPanel.getChart().getXYPlot().getDomainAxis().setLabelPaint(chartText);
            chPanel.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(chartText);
            chPanel.getChart().getXYPlot().getRangeAxis().setLabelPaint(chartText);
            chPanel.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(chartText);
            if (chPanel.getChart().getTitle() != null) {
                chPanel.getChart().getTitle().setPaint(chartText);
            }
            chPanel.getChart().getLegend().setItemPaint(chartText);
            chPanel.getChart().getXYPlot().setBackgroundPaint(chartBg);
            chPanel.getChart().getXYPlot().setDomainGridlinePaint(chartGrid);
            chPanel.getChart().getXYPlot().setRangeGridlinePaint(chartGrid);
        }
        ConnectController conCont = new ConnectController(sview, viewSCOPE, transmitter);
        SendController sendCont = new SendController(sview, viewSCOPE, transmitter, chPanel, chnum, prop);
        ReceiveController recvCont = new ReceiveController(sview, viewSCOPE, transmitter, sendCont, chPanel, chnum, prop); 


        
        sview.getTxtIPAdresse().setText(prop.getProperty("ipAdress", "").replaceAll("\\s",""));
        sview.getBtn_select_JavaScope().addActionListener(event -> activateInternalFrame(viewSCOPE, true));
        sview.getBtn_select_ParaID().addActionListener(event -> {
            if (parameterIDEnabled) {
                activateInternalFrame(viewParaID, true);
            }
        });

        //if PID extension should be activated, initialize ParameterID
        if(parameterIDEnabled){
            sview.getBtn_select_ParaID().setVisible(true);
            viewParaID.setVisible(true);
            viewParaID.toBack();
            new ParameterID(sview, viewSCOPE, viewParaID, transmitter, chPanel, chnum, prop, sendCont, recvCont);
        } else {
            sview.getBtn_select_ParaID().setVisible(false);
            viewParaID.setVisible(false);
        }
        sview.revalidate();
        sview.repaint();
      
        // Preferred Full HD size; if that does not fit, fall back to plain full-screen bounds.
        applyInitialWindowBounds(sview, 1920, 1080);
        sview.setVisible(true);

        // Attempt auto-connect on startup after all controllers/extensions are initialized.
        SwingUtilities.invokeLater(() -> sview.getBtnConnect().doClick());
    }
    
    
    public static void main(String[] args) {
        // Avoid loading FlatLaf native window decorations (prevents JDK native-access warnings).
        System.setProperty("flatlaf.useWindowDecorations", "false");
        new Start();
    }

    private int parseIntProperty(Properties prop, PropertyFileDiagnostics diagnostics, String key, int defaultValue)
    {
        String value = prop.getProperty(key);
        if (value == null) {
            return defaultValue;
        }
        try {
            return Integer.parseInt(value.trim());
        } catch (NumberFormatException exception) {
            diagnostics.printInvalidScalar(key, value, "an integer", Integer.toString(defaultValue));
            return defaultValue;
        }
    }

    private static String readBuildTimestamp()
    {
        Properties buildInfo = new Properties();
        try (InputStream stream = Start.class.getResourceAsStream("/UZ_GUI/build-info.properties")) {
            if (stream == null) {
                return "unavailable";
            }
            buildInfo.load(stream);
            return formatBuildTimestamp(buildInfo.getProperty("build.timestamp", "unavailable"));
        } catch (Exception exception) {
            return "unavailable";
        }
    }

    private static String formatBuildTimestamp(String rawTimestamp)
    {
        try {
            return BUILD_TIMESTAMP_FORMATTER.format(Instant.parse(rawTimestamp));
        } catch (Exception exception) {
            return rawTimestamp;
        }
    }

    private boolean parseBooleanProperty(Properties prop, String key, boolean defaultValue)
    {
        String value = prop.getProperty(key);
        if (value == null) {
            return defaultValue;
        }
        String normalized = value.trim().toLowerCase(java.util.Locale.US);
        if (normalized.equals("1") || normalized.equals("true") || normalized.equals("yes") || normalized.equals("on")) {
            return true;
        }
        if (normalized.equals("0") || normalized.equals("false") || normalized.equals("no") || normalized.equals("off")) {
            return false;
        }
        return defaultValue;
    }

    private File resolveJavascopeHeaderFile()
    {
        File file_javascopeh = new File("../vitis/software/Baremetal/src/include/javascope.h");
        if (!file_javascopeh.exists()) {
            file_javascopeh = new File("javascope.h");
        }
        return file_javascopeh;
    }

    private void applyInitialWindowBounds(JFrame frame, int preferredWidth, int preferredHeight)
    {
        GraphicsConfiguration gc = GraphicsEnvironment
                .getLocalGraphicsEnvironment()
                .getDefaultScreenDevice()
                .getDefaultConfiguration();
        Rectangle screenBounds = gc.getBounds();

        if (preferredWidth > screenBounds.width || preferredHeight > screenBounds.height) {
            frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
        } else {
            frame.setSize(preferredWidth, preferredHeight);
            frame.setLocation(screenBounds.x, screenBounds.y);
        }
    }

    private void activateInternalFrame(javax.swing.JInternalFrame frame, boolean maximize)
    {
        if (frame == null) {
            return;
        }
        if (!frame.isVisible()) {
            frame.setVisible(true);
        }
        try {
            if (maximize) {
                frame.setMaximum(true);
            }
        } catch (PropertyVetoException exception) {
            // Vetoed by internalFrame.
        }
        try {
            if (frame.isIcon()) {
                frame.setIcon(false);
            }
            frame.setSelected(true);
        } catch (PropertyVetoException exception) {
            // Vetoed by internalFrame.
        }
        frame.toFront();
    }

    private void applyUITheme(boolean isDarkMode, Color accentViolet) {
        UIManager.put("TabbedPane.underlineColor", accentViolet);
        UIManager.put("TabbedPane.inactiveUnderlineColor", accentViolet);
        UIManager.put("TabbedPane.disabledUnderlineColor", accentViolet);
        UIManager.put("TabbedPane.focusColor", accentViolet);
        UIManager.put("TabbedPane.tabSeparatorColor", accentViolet);
        UIManager.put("TabbedPane.tabSelectionHeight", 3);
        UIManager.put("TabbedPane.tabHeight", 28);
        UIManager.put("TabbedPane.tabArc", 8);
        UIManager.put("TabbedPane.tabSelectionArc", 8);

        UIManager.put("Component.arc", 8);
        UIManager.put("Button.arc", 8);
        UIManager.put("TextComponent.arc", 6);
        UIManager.put("Component.focusWidth", 1);
        UIManager.put("ScrollBar.thumbArc", 999);

        if (isDarkMode) {
            Color surfaceBase = new Color(0x2F, 0x31, 0x36);
            Color surfaceRaised = new Color(0x3A, 0x3D, 0x41);
            Color surfaceSoft = new Color(0x26, 0x28, 0x2C);
            Color surfaceHover = new Color(0x45, 0x48, 0x4D);
            Color surfacePressed = new Color(0x1F, 0x21, 0x24);
            Color textPrimary = new Color(0xED, 0xED, 0xED);
            Color textMuted = new Color(0xA3, 0xA7, 0xB0);
            Color border = new Color(0x4A, 0x4D, 0x52);
            Color selection = new Color(0x5B, 0x21, 0xB6);

            UIManager.put("Panel.background", surfaceBase);
            UIManager.put("Label.foreground", textPrimary);
            UIManager.put("Label.disabledForeground", textMuted);

            UIManager.put("Button.background", surfaceRaised);
            UIManager.put("Button.foreground", textPrimary);
            UIManager.put("Button.hoverBackground", surfaceHover);
            UIManager.put("Button.pressedBackground", surfacePressed);
            UIManager.put("Button.disabledText", textMuted);

            UIManager.put("ToggleButton.background", surfaceRaised);
            UIManager.put("ToggleButton.foreground", textPrimary);
            UIManager.put("ToggleButton.selectedBackground", accentViolet);
            UIManager.put("ToggleButton.selectedForeground", Color.white);

            UIManager.put("TextComponent.background", surfaceSoft);
            UIManager.put("TextComponent.foreground", textPrimary);
            UIManager.put("TextComponent.inactiveBackground", surfaceSoft);
            UIManager.put("TextComponent.selectionBackground", selection);
            UIManager.put("TextComponent.selectionForeground", Color.white);

            UIManager.put("TextField.background", surfaceSoft);
            UIManager.put("TextField.foreground", textPrimary);

            UIManager.put("ComboBox.background", surfaceSoft);
            UIManager.put("ComboBox.foreground", textPrimary);
            UIManager.put("ComboBox.buttonBackground", surfaceRaised);

            UIManager.put("Table.background", surfaceSoft);
            UIManager.put("Table.foreground", textPrimary);
            UIManager.put("Table.selectionBackground", selection);
            UIManager.put("Table.selectionForeground", Color.white);
            UIManager.put("Table.gridColor", border);
            UIManager.put("TableHeader.background", surfaceRaised);
            UIManager.put("TableHeader.foreground", textPrimary);

            UIManager.put("ScrollBar.thumb", border);
            UIManager.put("ScrollBar.track", surfaceBase);

            UIManager.put("Separator.foreground", border);
            UIManager.put("Separator.background", border);
            UIManager.put("TabbedPane.contentAreaColor", surfaceBase);
            UIManager.put("TabbedPane.tabAreaBackground", surfaceBase);
            UIManager.put("TabbedPane.foreground", textMuted);
            UIManager.put("TabbedPane.selectedForeground", textPrimary);
            UIManager.put("TabbedPane.disabledForeground", textMuted);
        } else {
            Color surfaceBase = new Color(0xF4, 0xF5, 0xF7);
            Color surfaceRaised = new Color(0xFF, 0xFF, 0xFF);
            Color surfaceSoft = new Color(0xED, 0xEE, 0xF1);
            Color surfaceHover = new Color(0xE5, 0xE7, 0xEB);
            Color surfacePressed = new Color(0xD1, 0xD5, 0xDB);
            Color textPrimary = new Color(0x1F, 0x29, 0x37);
            Color textMuted = new Color(0x6B, 0x72, 0x80);
            Color border = new Color(0xD1, 0xD5, 0xDB);

            UIManager.put("Panel.background", surfaceBase);
            UIManager.put("Label.foreground", textPrimary);
            UIManager.put("Label.disabledForeground", textMuted);

            UIManager.put("Button.background", surfaceRaised);
            UIManager.put("Button.foreground", textPrimary);
            UIManager.put("Button.hoverBackground", surfaceHover);
            UIManager.put("Button.pressedBackground", surfacePressed);
            UIManager.put("Button.disabledText", textMuted);

            UIManager.put("ToggleButton.background", surfaceRaised);
            UIManager.put("ToggleButton.foreground", textPrimary);
            UIManager.put("ToggleButton.selectedBackground", accentViolet);
            UIManager.put("ToggleButton.selectedForeground", Color.white);

            UIManager.put("TextComponent.background", surfaceRaised);
            UIManager.put("TextComponent.foreground", textPrimary);
            UIManager.put("TextComponent.inactiveBackground", surfaceSoft);
            UIManager.put("TextComponent.selectionBackground", accentViolet);
            UIManager.put("TextComponent.selectionForeground", Color.white);

            UIManager.put("TextField.background", surfaceRaised);
            UIManager.put("TextField.foreground", textPrimary);

            UIManager.put("ComboBox.background", surfaceRaised);
            UIManager.put("ComboBox.foreground", textPrimary);
            UIManager.put("ComboBox.buttonBackground", surfaceSoft);

            UIManager.put("Table.background", surfaceRaised);
            UIManager.put("Table.foreground", textPrimary);
            UIManager.put("Table.selectionBackground", accentViolet);
            UIManager.put("Table.selectionForeground", Color.white);
            UIManager.put("Table.gridColor", border);
            UIManager.put("TableHeader.background", surfaceSoft);
            UIManager.put("TableHeader.foreground", textPrimary);

            UIManager.put("ScrollBar.thumb", border);
            UIManager.put("ScrollBar.track", surfaceBase);

            UIManager.put("Separator.foreground", border);
            UIManager.put("Separator.background", border);
            UIManager.put("TabbedPane.contentAreaColor", surfaceBase);
            UIManager.put("TabbedPane.tabAreaBackground", surfaceBase);
            UIManager.put("TabbedPane.foreground", textMuted);
            UIManager.put("TabbedPane.selectedForeground", textPrimary);
            UIManager.put("TabbedPane.disabledForeground", textMuted);
        }
    }
    
}
