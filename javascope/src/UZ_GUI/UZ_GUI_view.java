
        /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;

/**
 *
 * @author LoehdefinkPh
 */
public class UZ_GUI_view extends javax.swing.JFrame {  
    private static final java.awt.Color UZ_HEADER_BG = new java.awt.Color(74, 78, 105);
    private static final java.awt.Color UZ_HEADER_PANEL_BG = new java.awt.Color(74, 78, 105);
    private static final java.awt.Color UZ_BOTTOM_BG = new java.awt.Color(74, 78, 105);
    private static final java.awt.Color UZ_TEXT_PRIMARY = new java.awt.Color(255, 255, 255);
    private static final java.awt.Color UZ_TEXT_MUTED = new java.awt.Color(153, 153, 153);
    private static final java.awt.Color UZ_GROUP_BORDER = new java.awt.Color(114, 118, 149);
    private static final java.awt.Color UZ_ACCENT_PURPLE = new java.awt.Color(124, 58, 237);
    private static final int HEADER_ROW_SPACING_PX = 1;
    private static final int HEADER_COLUMN_SPACING_PX = 8;
    private static final int LOGO_ICON_MAX_HEIGHT_PX = 56;
    private static final int LOGO_WORDMARK_MAX_HEIGHT_PX = 44;
    private static final int LOGO_WORDMARK_LEFT_INSET_PX = 44;
    private static final int LOGO_LEFT_INSET_PX = 5;
    private static final int LOGO_RIGHT_PADDING_PX = 8;
    private static final int LOGO_WORDMARK_HIDE_BELOW_WIDTH_PX = 120;
    private static final int LOGO_PANEL_MIN_WIDTH_PX = 170;
    private static final int HEADER_MIN_WIDTH_PADDING_PX = 16;
    private static final int HEADER_BUTTON_TEXT_EXTRA_PADDING_PX = 14;
    private static final int HEADER_GROUP_CONTENT_TOP_INSET_PX = 2;
    private static final int HEADER_GROUP_CONTENT_SIDE_INSET_PX = 8;
    private static final int HEADER_GROUP_CONTENT_BOTTOM_INSET_PX = 4;
    private static final int FOOTER_DEFAULT_HORIZONTAL_GAP_PX = 80;
    private static final int FOOTER_MIN_HORIZONTAL_GAP_PX = 20;
    private static final int FOOTER_VERTICAL_GAP_PX = 8;
    private static final String HEADER_BUTTON_STYLE =
        "background: #2F3136; " +
        "foreground: #F3F4F6; " +
        "hoverBackground: #3A3D41; " +
        "pressedBackground: #1F2124; " +
        "borderColor: #4A4D52;";
    private static final String HEADER_ACTIVE_BUTTON_STYLE =
        "background: #7C3AED; " +
        "foreground: #FFFFFF; " +
        "hoverBackground: #6D28D9; " +
        "pressedBackground: #5B21B6; " +
        "borderColor: #8B5CF6;";
    private static final String HEADER_NEUTRAL_TOGGLE_STYLE =
        HEADER_BUTTON_STYLE +
        "selectedBackground: #2F3136; " +
        "selectedForeground: #F3F4F6;";
    private static final String HEADER_INPUT_STYLE =
        "background: #26282C; " +
        "foreground: #F3F4F6; " +
        "borderColor: #4A4D52;";
    private static final String PRETRIG_SLIDER_STYLE =
        "trackColor: #EDE9FE; " +
        "trackValueColor: #FFFFFF; " +
        "thumbColor: #2B1E3E; " +
        "thumbBorderColor: #FFFFFF; " +
        "focusedColor: #FFFFFF;";

    private static final String LOGO_LEFT_CUSTOM = "/UZ_GUI/UltraZohm_nur_Logo.png";
    private static final String LOGO_WORDMARK_CUSTOM = "/UZ_GUI/UltraZohm_nur_Schrift.png";
    private static final String LOGO_LEFT_FORM = "/UZ_GUI/UltraZohm_nur_Logo_form.png";
    private static final String LOGO_WORDMARK_FORM = "/UZ_GUI/UltraZohm_nur_Schrift_form.png";

    private javax.swing.ImageIcon logoLeftSourceIcon;
    private javax.swing.ImageIcon logoLeftScaledIcon;
    private javax.swing.ImageIcon logoWordmarkSourceIcon;
    private final javax.swing.JButton btnNewLogFile = new javax.swing.JButton("New Log File");

    /**
     * @return the btnLogOnOff
     */
    public javax.swing.JButton getBtnLogOnOff() {
        return btnLogOnOff;
    }

    /**
     * @return the BtnChange_fastDataLog
     */
    public javax.swing.JButton getBtnChange_fastDataLog() {
        return BtnChange_fastDataLog;
    }
    
    /**
     * @return the BtnChange_slowDataLog
     */
    public javax.swing.JButton getBtnChange_slowDataLog() {
        return BtnChange_slowDataLog;
    }
    
    /**
     * @return the Btn_select_ParaID
     */
    public javax.swing.JButton getBtn_select_ParaID() {
        return Btn_select_ParaID;
    }
    
    
    /**
     * Creates new form KnaufView
     */
    public UZ_GUI_view() {
        initComponents();
        btnNewLogFile.setEnabled(false);
        btnNewLogFile.setVisible(false);
        applyUltraZohmTheme();
        applyHeaderBranding();
        applyHeaderLayoutTweaks();
        setTriggerEnabled(false);
        setTriggerEdgeRising(true);
        installResponsiveHeaderBranding();
        installResponsiveFooterLayout();
        java.awt.EventQueue.invokeLater(this::updateResponsiveHeaderBranding);
        java.awt.EventQueue.invokeLater(this::updateResponsiveFooterLayout);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        PanelOben = new javax.swing.JPanel();
        titleInfoPanel = new javax.swing.JPanel();
        lblLogo3 = new javax.swing.JLabel();
        lblLogo2 = new javax.swing.JLabel();
        titleControlPanel = new javax.swing.JPanel();
        btnRunStop = new javax.swing.JButton();
        BtnFixAxis = new javax.swing.JButton();
        comboTrigger = new javax.swing.JComboBox<>();
        btnTriggerEdge = new javax.swing.JToggleButton();
        lblTriggerMode = new javax.swing.JLabel();
        btnSingleShot = new javax.swing.JToggleButton();
        btnTriggerEnabled = new javax.swing.JToggleButton();
        lblTimeBase = new javax.swing.JLabel();
        comboTimeBase = new javax.swing.JComboBox<>();
        sliPreTrigger = new javax.swing.JSlider();
        txtTriggerValue = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        btnSaveSettings = new javax.swing.JButton();
        btnLogOnOff = new javax.swing.JButton();
        BtnChange_fastDataLog = new javax.swing.JButton();
        BtnChange_slowDataLog = new javax.swing.JButton();
        Combo_LogNthValue = new javax.swing.JComboBox<>();
        txtLogEveryN = new javax.swing.JTextField();
        BtnSet_extLogging = new javax.swing.JButton();
        txt_LogStatus = new javax.swing.JLabel();
        txt_RunStop = new javax.swing.JLabel();
        titlePanelSelection = new javax.swing.JPanel();
        Btn_select_JavaScope = new javax.swing.JButton();
        Btn_select_ParaID = new javax.swing.JButton();
        PanelUnten = new javax.swing.JPanel();
        lblStatusUnten = new javax.swing.JLabel();
        lblAnzeigeConnected = new javax.swing.JLabel();
        txtIPAdresse = new javax.swing.JTextField();
        btnConnect = new javax.swing.JButton();
        btnDisconnect = new javax.swing.JButton();
        btnDetectSamplingRate = new javax.swing.JButton();
        txtSamplingRateKHz = new javax.swing.JTextField();
        txtSamplingRateStatus = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMinimumSize(new java.awt.Dimension(1200, 800));
        setPreferredSize(new java.awt.Dimension(1600, 800));

        PanelOben.setBackground(new java.awt.Color(33, 64, 154));
        PanelOben.setMinimumSize(new java.awt.Dimension(890, 120));
        PanelOben.setPreferredSize(new java.awt.Dimension(1000, 140));
        PanelOben.setLayout(new java.awt.BorderLayout());

        titleInfoPanel.setBackground(new java.awt.Color(33, 64, 154));
        titleInfoPanel.setMinimumSize(new java.awt.Dimension(170, 115));
        titleInfoPanel.setPreferredSize(new java.awt.Dimension(1091, 115));
        titleInfoPanel.setLayout(new java.awt.GridBagLayout());

        lblLogo3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/UZ_GUI/UltraZohm_nur_Logo_form.png"))); // NOI18N
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.CENTER;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 0);
        gridBagConstraints.weighty = 1.0;
        titleInfoPanel.add(lblLogo3, gridBagConstraints);

        lblLogo2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/UZ_GUI/UltraZohm_nur_Schrift_form.png"))); // NOI18N
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.CENTER;
        gridBagConstraints.insets = new java.awt.Insets(0, 44, 0, 0);
        gridBagConstraints.weighty = 1.0;
        titleInfoPanel.add(lblLogo2, gridBagConstraints);

        PanelOben.add(titleInfoPanel, java.awt.BorderLayout.CENTER);

        titleControlPanel.setMaximumSize(new java.awt.Dimension(1600, 130));
        titleControlPanel.setMinimumSize(new java.awt.Dimension(760, 105));
        titleControlPanel.setPreferredSize(new java.awt.Dimension(930, 115));
        titleControlPanel.setLayout(new java.awt.GridBagLayout());

        btnRunStop.setText("Run/Stop");
        btnRunStop.setEnabled(false);
        btnRunStop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRunStopActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_END;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 5);
        titleControlPanel.add(btnRunStop, gridBagConstraints);

        BtnFixAxis.setText("fixAxis");
        BtnFixAxis.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 5);
        titleControlPanel.add(BtnFixAxis, gridBagConstraints);

        comboTrigger.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7", "CH8", "CH9", "CH10", "CH11", "CH12", "CH13", "CH14", "CH15", "CH16", "CH17", "CH18", "CH19", "CH20" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_START;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 5);
        titleControlPanel.add(comboTrigger, gridBagConstraints);

        btnTriggerEdge.setSelected(true);
        btnTriggerEdge.setText("\u2197 Rising");
        btnTriggerEdge.setFocusable(false);
        btnTriggerEdge.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btnTriggerEdge.setMaximumSize(new java.awt.Dimension(110, 23));
        btnTriggerEdge.setMinimumSize(new java.awt.Dimension(110, 23));
        btnTriggerEdge.setPreferredSize(new java.awt.Dimension(110, 23));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_START;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 5);
        titleControlPanel.add(btnTriggerEdge, gridBagConstraints);

        lblTriggerMode.setText("Trigger");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 4;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_START;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 5);
        titleControlPanel.add(lblTriggerMode, gridBagConstraints);

        btnSingleShot.setText("SingleShot");
        btnSingleShot.setFocusable(false);
        btnSingleShot.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btnSingleShot.setMaximumSize(new java.awt.Dimension(95, 23));
        btnSingleShot.setMinimumSize(new java.awt.Dimension(95, 23));
        btnSingleShot.setPreferredSize(new java.awt.Dimension(95, 23));
        btnSingleShot.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 5);
        titleControlPanel.add(btnSingleShot, gridBagConstraints);

        btnTriggerEnabled.setText("disabled");
        btnTriggerEnabled.setFocusable(false);
        btnTriggerEnabled.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btnTriggerEnabled.setMaximumSize(new java.awt.Dimension(110, 23));
        btnTriggerEnabled.setMinimumSize(new java.awt.Dimension(110, 23));
        btnTriggerEnabled.setPreferredSize(new java.awt.Dimension(110, 23));
        btnTriggerEnabled.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 5);
        titleControlPanel.add(btnTriggerEnabled, gridBagConstraints);

        lblTimeBase.setText("Time base");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_END;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 5);
        titleControlPanel.add(lblTimeBase, gridBagConstraints);

        comboTimeBase.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "x1", "x5", "x10", "x50", "x100" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_START;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 5);
        titleControlPanel.add(comboTimeBase, gridBagConstraints);

        sliPreTrigger.setMaximum(10);
        sliPreTrigger.setValue(5);
        sliPreTrigger.setMaximumSize(new java.awt.Dimension(83, 23));
        sliPreTrigger.setMinimumSize(new java.awt.Dimension(83, 23));
        sliPreTrigger.setPreferredSize(new java.awt.Dimension(83, 23));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.LINE_START;
        titleControlPanel.add(sliPreTrigger, gridBagConstraints);

        txtTriggerValue.setText("0.0");
        txtTriggerValue.setMaximumSize(new java.awt.Dimension(60, 20));
        txtTriggerValue.setMinimumSize(new java.awt.Dimension(60, 20));
        txtTriggerValue.setPreferredSize(new java.awt.Dimension(60, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 1;
        titleControlPanel.add(txtTriggerValue, gridBagConstraints);

        jLabel3.setText("Level (div):");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 4;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 0);
        titleControlPanel.add(jLabel3, gridBagConstraints);

        jLabel4.setText("PreTrig.:");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 4;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 0);
        titleControlPanel.add(jLabel4, gridBagConstraints);

        btnSaveSettings.setText("Save Settings");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 0, 5);
        titleControlPanel.add(btnSaveSettings, gridBagConstraints);

        btnLogOnOff.setText("Logging OFF");
        btnLogOnOff.setEnabled(false);
        btnLogOnOff.setMinimumSize(new java.awt.Dimension(122, 23));
        btnLogOnOff.setPreferredSize(new java.awt.Dimension(122, 23));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 0);
        titleControlPanel.add(btnLogOnOff, gridBagConstraints);

        BtnChange_fastDataLog.setText("Log FastData");
        BtnChange_fastDataLog.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 0);
        titleControlPanel.add(BtnChange_fastDataLog, gridBagConstraints);

        BtnChange_slowDataLog.setText("Log SlowData");
        BtnChange_slowDataLog.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 0, 0);
        titleControlPanel.add(BtnChange_slowDataLog, gridBagConstraints);

        Combo_LogNthValue.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "1", "5", "10", "50", "100", "500", "1000", "5000", "10000" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 10;
        gridBagConstraints.gridy = 1;
        titleControlPanel.add(Combo_LogNthValue, gridBagConstraints);

        txtLogEveryN.setEditable(false);
        txtLogEveryN.setColumns(8);
        txtLogEveryN.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtLogEveryN.setText("Log every N");
        txtLogEveryN.setFocusable(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 1;
        titleControlPanel.add(txtLogEveryN, gridBagConstraints);

        BtnSet_extLogging.setText("ext. log trigger");
        BtnSet_extLogging.setEnabled(false);
        BtnSet_extLogging.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 0;
        titleControlPanel.add(BtnSet_extLogging, gridBagConstraints);

        txt_LogStatus.setText("Log OFF");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 10;
        gridBagConstraints.gridy = 0;
        titleControlPanel.add(txt_LogStatus, gridBagConstraints);

        txt_RunStop.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        txt_RunStop.setForeground(new java.awt.Color(255, 0, 51));
        txt_RunStop.setText("||");
        txt_RunStop.setMinimumSize(new java.awt.Dimension(25, 22));
        txt_RunStop.setPreferredSize(new java.awt.Dimension(25, 22));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.ipadx = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 15);
        titleControlPanel.add(txt_RunStop, gridBagConstraints);

        PanelOben.add(titleControlPanel, java.awt.BorderLayout.EAST);

        titlePanelSelection.setOpaque(false);
        titlePanelSelection.setPreferredSize(new java.awt.Dimension(460, 30));
        titlePanelSelection.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT));


        Btn_select_JavaScope.setText("JavaScope");
        Btn_select_JavaScope.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Btn_select_JavaScopeActionPerformed(evt);
            }
        });
        titlePanelSelection.add(Btn_select_JavaScope);

        Btn_select_ParaID.setText("ParameterID");
        Btn_select_ParaID.setVisible(false);
        Btn_select_ParaID.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Btn_select_ParaIDActionPerformed(evt);
            }
        });
        titlePanelSelection.add(Btn_select_ParaID);

        PanelOben.add(titlePanelSelection, java.awt.BorderLayout.PAGE_END);

        getContentPane().add(PanelOben, java.awt.BorderLayout.PAGE_START);

        PanelUnten.setBackground(new java.awt.Color(33, 64, 154));
        PanelUnten.setMinimumSize(new java.awt.Dimension(985, 33));
        PanelUnten.setPreferredSize(new java.awt.Dimension(1000, 40));
        PanelUnten.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.CENTER, FOOTER_DEFAULT_HORIZONTAL_GAP_PX, FOOTER_VERTICAL_GAP_PX));

        lblStatusUnten.setForeground(new java.awt.Color(255, 255, 255));
        lblStatusUnten.setText("Status: ################################");
        lblStatusUnten.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        PanelUnten.add(lblStatusUnten);

        lblAnzeigeConnected.setForeground(new java.awt.Color(255, 255, 255));
        lblAnzeigeConnected.setText("#~#~#~");
        PanelUnten.add(lblAnzeigeConnected);

        txtIPAdresse.setText("192.168.1.233");
        txtIPAdresse.setMinimumSize(new java.awt.Dimension(80, 20));
        txtIPAdresse.setName(""); // NOI18N
        PanelUnten.add(txtIPAdresse);

        btnConnect.setText("connect");
        PanelUnten.add(btnConnect);

        btnDisconnect.setText("disconnect");
        btnDisconnect.setEnabled(false);
        PanelUnten.add(btnDisconnect);

        btnDetectSamplingRate.setText("detect sampling rate");
        btnDetectSamplingRate.setEnabled(false);
        btnDetectSamplingRate.setVisible(false);
        PanelUnten.add(btnDetectSamplingRate);

        txtSamplingRateKHz.setEditable(false);
        txtSamplingRateKHz.setText("sampling rate 0.0 kHz");
        txtSamplingRateKHz.setColumns(18);
        PanelUnten.add(txtSamplingRateKHz);

        txtSamplingRateStatus.setEditable(false);
        txtSamplingRateStatus.setText("throughput n/a");
        txtSamplingRateStatus.setColumns(15);
        PanelUnten.add(txtSamplingRateStatus);

        getContentPane().add(PanelUnten, java.awt.BorderLayout.PAGE_END);

        setBounds(0, 0, 2589, 1551);
    }// </editor-fold>//GEN-END:initComponents

    private void Btn_select_JavaScopeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Btn_select_JavaScopeActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_Btn_select_JavaScopeActionPerformed

    private void Btn_select_ParaIDActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Btn_select_ParaIDActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_Btn_select_ParaIDActionPerformed

    private void btnRunStopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRunStopActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_btnRunStopActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(UZ_GUI_view.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(UZ_GUI_view.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(UZ_GUI_view.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(UZ_GUI_view.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new UZ_GUI_view().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnChange_fastDataLog;
    private javax.swing.JButton BtnChange_slowDataLog;
    private javax.swing.JButton BtnFixAxis;
    private javax.swing.JButton BtnSet_extLogging;
    private javax.swing.JButton Btn_select_JavaScope;
    private javax.swing.JButton Btn_select_ParaID;
    private javax.swing.JComboBox<String> Combo_LogNthValue;
    private javax.swing.JPanel PanelOben;
    private javax.swing.JPanel PanelUnten;
    private javax.swing.JButton btnConnect;
    private javax.swing.JButton btnDetectSamplingRate;
    private javax.swing.JButton btnDisconnect;
    private javax.swing.JButton btnLogOnOff;
    private javax.swing.JButton btnRunStop;
    private javax.swing.JButton btnSaveSettings;
    private javax.swing.JToggleButton btnSingleShot;
    private javax.swing.JToggleButton btnTriggerEnabled;
    private javax.swing.JToggleButton btnTriggerEdge;
    private javax.swing.JComboBox<String> comboTimeBase;
    private javax.swing.JComboBox<String> comboTrigger;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel lblTriggerMode;
    private javax.swing.JLabel lblTimeBase;
    private javax.swing.JLabel lblAnzeigeConnected;
    private javax.swing.JLabel lblLogo2;
    private javax.swing.JLabel lblLogo3;
    private javax.swing.JLabel lblStatusUnten;
    private javax.swing.JSlider sliPreTrigger;
    private javax.swing.JPanel titleControlPanel;
    private javax.swing.JPanel titleInfoPanel;
    private javax.swing.JPanel titlePanelSelection;
    private javax.swing.JTextField txtIPAdresse;
    private javax.swing.JTextField txtLogEveryN;
    private javax.swing.JTextField txtSamplingRateKHz;
    private javax.swing.JTextField txtSamplingRateStatus;
    private javax.swing.JTextField txtTriggerValue;
    private javax.swing.JLabel txt_LogStatus;
    private javax.swing.JLabel txt_RunStop;
    // End of variables declaration//GEN-END:variables


    /**
     * @return the btnConnect
     */
    public javax.swing.JButton getBtnConnect() {
        return btnConnect;
    }

    public javax.swing.JButton getBtnDisconnect() {
        return btnDisconnect;
    }

    /**
     * @return the lblAnzeigeConnected
     */
    public javax.swing.JLabel getLblAnzeigeConnected() {
        return lblAnzeigeConnected;
    }

    private void applyUltraZohmTheme() {
        PanelOben.setBackground(UZ_HEADER_BG);
        titleInfoPanel.setBackground(UZ_HEADER_BG);
        titleControlPanel.setBackground(UZ_HEADER_PANEL_BG);
        PanelUnten.setBackground(UZ_BOTTOM_BG);

        lblStatusUnten.setForeground(UZ_TEXT_PRIMARY);
        lblAnzeigeConnected.setForeground(UZ_TEXT_PRIMARY);
        txt_LogStatus.setForeground(UZ_TEXT_MUTED);


        sliPreTrigger.putClientProperty("FlatLaf.style", PRETRIG_SLIDER_STYLE);

        applyHeaderControlStyle(btnRunStop);
        applyHeaderControlStyle(btnSingleShot);
        applyHeaderControlStyle(btnTriggerEnabled);
        applyHeaderControlStyle(btnTriggerEdge);
        applyNeutralToggleStyle(btnTriggerEdge);
        applyHeaderControlStyle(BtnFixAxis);
        applyHeaderControlStyle(btnSaveSettings);
        applyHeaderControlStyle(btnLogOnOff);
        applyHeaderControlStyle(BtnChange_fastDataLog);
        applyHeaderControlStyle(BtnChange_slowDataLog);
        applyHeaderControlStyle(BtnSet_extLogging);
        applyHeaderControlStyle(Btn_select_JavaScope);
        applyHeaderControlStyle(Btn_select_ParaID);

        applyHeaderInputStyle(comboTrigger);
        applyHeaderInputStyle(comboTimeBase);
        applyHeaderInputStyle(Combo_LogNthValue);
        applyHeaderTextFieldLabelStyle(txtLogEveryN);
        applyHeaderInputStyle(txtTriggerValue);
        applyHeaderInputStyle(txtIPAdresse);
        applyHeaderInputStyle(txtSamplingRateKHz);
        applyHeaderInputStyle(txtSamplingRateStatus);
        txtSamplingRateKHz.setColumns(18);
        txtSamplingRateStatus.setColumns(15);
        txtSamplingRateKHz.setText("sampling rate 0.0 kHz");
        txtSamplingRateStatus.setText("throughput n/a");

        lblTriggerMode.setForeground(UZ_TEXT_PRIMARY);
        lblTimeBase.setForeground(UZ_TEXT_PRIMARY);
        jLabel3.setForeground(UZ_TEXT_PRIMARY);
        jLabel4.setForeground(UZ_TEXT_PRIMARY);

        applyHeaderControlStyle(btnConnect);
        applyHeaderControlStyle(btnDisconnect);
        btnDetectSamplingRate.setVisible(false);
        setLogOnOffHighlighted(false);
        setFastDataLogHighlighted(false);
        setSlowDataLogHighlighted(false);
        setExtLoggingHighlighted(false);
        setLogStatusHighlighted(false);
        setSingleShotPending(false);
    }

    private void applyHeaderBranding() {
        logoLeftSourceIcon = loadIconResource(LOGO_LEFT_CUSTOM, LOGO_LEFT_FORM);
        logoWordmarkSourceIcon = loadIconResource(LOGO_WORDMARK_CUSTOM, LOGO_WORDMARK_FORM);
        logoLeftScaledIcon = scaleIconToFit(logoLeftSourceIcon, Integer.MAX_VALUE, LOGO_ICON_MAX_HEIGHT_PX);

        lblLogo3.setIcon(logoLeftScaledIcon);
        lblLogo3.setText("");
        lblLogo2.setText("");
        enforceHeaderMinimumWidthForLogo();
        updateResponsiveHeaderBranding();
    }

    private void applyHeaderLayoutTweaks() {
        java.awt.LayoutManager layout = titleInfoPanel.getLayout();
        if (!(layout instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) layout;
        java.awt.GridBagConstraints logoWordmarkConstraints = gbl.getConstraints(lblLogo2);
        logoWordmarkConstraints.insets = new java.awt.Insets(
            logoWordmarkConstraints.insets.top,
            LOGO_WORDMARK_LEFT_INSET_PX,
            logoWordmarkConstraints.insets.bottom,
            logoWordmarkConstraints.insets.right
        );
        gbl.setConstraints(lblLogo2, logoWordmarkConstraints);
        configureHeaderControlPanelGroups();
        enforceHeaderMinimumWidthForLogo();
        updateResponsiveHeaderBranding();
    }

    private void installResponsiveHeaderBranding() {
        titleInfoPanel.addComponentListener(new java.awt.event.ComponentAdapter() {
            @Override
            public void componentResized(java.awt.event.ComponentEvent e) {
                updateResponsiveHeaderBranding();
            }
        });
    }

    private void installResponsiveFooterLayout() {
        PanelUnten.addComponentListener(new java.awt.event.ComponentAdapter() {
            @Override
            public void componentResized(java.awt.event.ComponentEvent e) {
                updateResponsiveFooterLayout();
            }
        });
    }

    private void updateResponsiveHeaderBranding() {
        if (logoLeftScaledIcon != null) {
            lblLogo3.setIcon(logoLeftScaledIcon);
            lblLogo3.setVisible(true);
        }

        if (logoWordmarkSourceIcon == null) {
            lblLogo2.setIcon(null);
            lblLogo2.setVisible(false);
            return;
        }

        int infoPanelWidth = titleInfoPanel.getWidth();
        if (infoPanelWidth <= 0) {
            java.awt.Dimension preferred = titleInfoPanel.getPreferredSize();
            infoPanelWidth = preferred != null ? preferred.width : 0;
        }

        int leftLogoWidth = logoLeftScaledIcon != null ? logoLeftScaledIcon.getIconWidth() : 0;
        int availableWordmarkWidth =
            infoPanelWidth
            - LOGO_LEFT_INSET_PX
            - leftLogoWidth
            - LOGO_WORDMARK_LEFT_INSET_PX
            - LOGO_RIGHT_PADDING_PX;

        if (availableWordmarkWidth < LOGO_WORDMARK_HIDE_BELOW_WIDTH_PX) {
            lblLogo2.setIcon(null);
            lblLogo2.setVisible(false);
            return;
        }

        javax.swing.ImageIcon wordmarkScaled = scaleIconToFit(
            logoWordmarkSourceIcon,
            availableWordmarkWidth,
            LOGO_WORDMARK_MAX_HEIGHT_PX
        );
        lblLogo2.setIcon(wordmarkScaled);
        lblLogo2.setVisible(wordmarkScaled != null);
    }

    private void updateResponsiveFooterLayout() {
        java.awt.LayoutManager layout = PanelUnten.getLayout();
        if (!(layout instanceof java.awt.FlowLayout)) {
            return;
        }

        int visibleComponentCount = 0;
        int componentWidths = 0;
        for (java.awt.Component component : PanelUnten.getComponents()) {
            if (!component.isVisible()) {
                continue;
            }
            java.awt.Dimension preferred = component.getPreferredSize();
            if (preferred != null) {
                componentWidths += preferred.width;
            }
            visibleComponentCount++;
        }
        if (visibleComponentCount == 0) {
            return;
        }

        int footerWidth = PanelUnten.getWidth();
        if (footerWidth <= 0) {
            java.awt.Dimension preferred = PanelUnten.getPreferredSize();
            footerWidth = preferred != null ? preferred.width : 0;
        }
        java.awt.Insets insets = PanelUnten.getInsets();
        int availableWidth = Math.max(0, footerWidth - insets.left - insets.right);
        int gapSlots = visibleComponentCount + 1;
        int responsiveGap = FOOTER_DEFAULT_HORIZONTAL_GAP_PX;
        int maxGapThatFits = (availableWidth - componentWidths) / Math.max(1, gapSlots);
        responsiveGap = Math.min(FOOTER_DEFAULT_HORIZONTAL_GAP_PX, maxGapThatFits);
        responsiveGap = Math.max(FOOTER_MIN_HORIZONTAL_GAP_PX, responsiveGap);

        java.awt.FlowLayout flowLayout = (java.awt.FlowLayout) layout;
        if (flowLayout.getHgap() != responsiveGap) {
            flowLayout.setHgap(responsiveGap);
            PanelUnten.revalidate();
            PanelUnten.repaint();
        }
    }

    private void enforceHeaderMinimumWidthForLogo() {
        int leftLogoWidth = logoLeftScaledIcon != null ? logoLeftScaledIcon.getIconWidth() : 0;
        int requiredLogoPanelWidth = LOGO_LEFT_INSET_PX + leftLogoWidth + LOGO_RIGHT_PADDING_PX;
        requiredLogoPanelWidth = Math.max(requiredLogoPanelWidth, LOGO_PANEL_MIN_WIDTH_PX);

        java.awt.Dimension infoPanelMin = titleInfoPanel.getMinimumSize();
        int logoPanelHeight = infoPanelMin != null ? infoPanelMin.height : 115;
        if (infoPanelMin == null || infoPanelMin.width < requiredLogoPanelWidth) {
            titleInfoPanel.setMinimumSize(new java.awt.Dimension(requiredLogoPanelWidth, logoPanelHeight));
        }

        java.awt.Dimension controlPreferred = titleControlPanel.getPreferredSize();
        java.awt.Dimension controlMinimum = titleControlPanel.getMinimumSize();
        int controlWidth = 0;
        if (controlPreferred != null) {
            controlWidth = Math.max(controlWidth, controlPreferred.width);
        }
        if (controlMinimum != null) {
            controlWidth = Math.max(controlWidth, controlMinimum.width);
        }

        int requiredFrameWidth = requiredLogoPanelWidth + controlWidth + HEADER_MIN_WIDTH_PADDING_PX;
        java.awt.Dimension frameMin = getMinimumSize();
        int frameMinHeight = frameMin != null ? frameMin.height : 800;
        if (frameMin == null || frameMin.width < requiredFrameWidth) {
            setMinimumSize(new java.awt.Dimension(requiredFrameWidth, frameMinHeight));
        }
    }

    private void configureHeaderControlPanelGroups() {
        titleControlPanel.removeAll();
        titleControlPanel.setLayout(new java.awt.GridBagLayout());

        ensureButtonTextFits(btnLogOnOff, "Logging OFF", "Logging ON ");
        ensureButtonTextFits(BtnChange_fastDataLog, "Log FastData");
        ensureButtonTextFits(BtnChange_slowDataLog, "Log SlowData");
        unifyButtonWidths(btnLogOnOff, BtnChange_fastDataLog, BtnChange_slowDataLog);
        int loggingButtonHeight = btnLogOnOff.getPreferredSize() != null
            ? btnLogOnOff.getPreferredSize().height
            : 23;
        setFixedWidth(comboTimeBase, 70);
        setFixedWidth(Combo_LogNthValue, 78);
        setFixedWidth(txtTriggerValue, 56);
        setFixedWidth(comboTrigger, 80);
        ensureTextFieldTextFits(txtLogEveryN, "Log every N");
        setFixedSize(btnTriggerEdge, 110, loggingButtonHeight);
        setFixedSize(btnTriggerEnabled, 110, loggingButtonHeight);
        setFixedSize(btnSingleShot, 95, loggingButtonHeight);

        java.awt.Dimension preTrigSliderSize = new java.awt.Dimension(100, sliPreTrigger.getPreferredSize().height);
        sliPreTrigger.setPreferredSize(preTrigSliderSize);
        sliPreTrigger.setMinimumSize(preTrigSliderSize);
        sliPreTrigger.setMaximumSize(preTrigSliderSize);

        javax.swing.JPanel scopePanel = createHeaderGroupPanel("Scope");
        javax.swing.JPanel scopeRow = createHeaderColumnsPanel();
        javax.swing.JPanel scopeMainColumn = createHeaderColumnPanel();
        addColumnRow(scopeMainColumn, txt_RunStop, btnRunStop);
        addColumnRow(scopeMainColumn, lblTimeBase, comboTimeBase);

        javax.swing.JPanel scopeAuxColumn = createHeaderColumnPanel();
        addColumnRow(scopeAuxColumn, BtnFixAxis);
        addColumnRow(scopeAuxColumn, btnSaveSettings);
        int scopeSpacerRowHeight = Math.max(loggingButtonHeight, comboTimeBase.getPreferredSize().height);
        addEmptyColumnRow(scopeMainColumn, scopeSpacerRowHeight);
        addEmptyColumnRow(scopeAuxColumn, scopeSpacerRowHeight);
        lockPreferredWidth(scopeMainColumn);
        lockPreferredWidth(scopeAuxColumn);

        scopeRow.add(scopeMainColumn);
        scopeRow.add(javax.swing.Box.createHorizontalStrut(HEADER_COLUMN_SPACING_PX));
        scopeRow.add(scopeAuxColumn);
        scopePanel.add(scopeRow);

        javax.swing.JPanel triggerPanel = createHeaderGroupPanel("Trigger");
        javax.swing.JPanel triggerRow = createHeaderColumnsPanel();
        javax.swing.JPanel triggerColumn = createHeaderColumnPanel();
        addColumnRowTrailing(triggerColumn, btnTriggerEdge, lblTriggerMode, comboTrigger);
        addColumnRowTrailing(triggerColumn, btnTriggerEnabled, jLabel3, txtTriggerValue);
        addColumnRowTrailing(triggerColumn, btnSingleShot, jLabel4, sliPreTrigger);
        lockPreferredWidth(triggerColumn);
        triggerRow.add(triggerColumn);
        triggerPanel.add(triggerRow);

        javax.swing.JPanel loggingPanel = createHeaderGroupPanel("Logging");
        javax.swing.JPanel loggingRow = createHeaderColumnsPanel();
        javax.swing.JPanel loggingMainColumn = createHeaderColumnPanel();
        addColumnRow(loggingMainColumn, btnLogOnOff);
        addColumnRow(loggingMainColumn, BtnChange_fastDataLog);
        addColumnRow(loggingMainColumn, BtnChange_slowDataLog);

        javax.swing.JPanel loggingConfigColumn = createHeaderColumnPanel();
        addColumnRowTrailing(loggingConfigColumn, txt_LogStatus, BtnSet_extLogging);
        addColumnRowTrailing(loggingConfigColumn, Combo_LogNthValue, txtLogEveryN);
        addEmptyColumnRow(loggingConfigColumn, loggingButtonHeight);
        lockPreferredWidth(loggingMainColumn);
        lockPreferredWidth(loggingConfigColumn);

        loggingRow.add(loggingMainColumn);
        loggingRow.add(javax.swing.Box.createHorizontalStrut(HEADER_COLUMN_SPACING_PX));
        loggingRow.add(loggingConfigColumn);
        loggingPanel.add(loggingRow);

        matchHeaderGroupHeights(loggingPanel, scopePanel, triggerPanel);

        java.awt.GridBagConstraints fillerGbc = new java.awt.GridBagConstraints();
        fillerGbc.gridx = 0;
        fillerGbc.gridy = 0;
        fillerGbc.weightx = 1.0;
        fillerGbc.weighty = 1.0;
        fillerGbc.fill = java.awt.GridBagConstraints.HORIZONTAL;
        javax.swing.JPanel filler = new javax.swing.JPanel();
        filler.setOpaque(false);
        titleControlPanel.add(filler, fillerGbc);

        addHeaderGroup(scopePanel, 1, 6);
        addHeaderGroup(triggerPanel, 2, 6);
        addHeaderGroup(loggingPanel, 3, 8);

        titleControlPanel.revalidate();
        titleControlPanel.repaint();
    }

    private javax.swing.JPanel createHeaderGroupPanel(String title) {
        javax.swing.JPanel panel = new javax.swing.JPanel();
        panel.setLayout(new javax.swing.BoxLayout(panel, javax.swing.BoxLayout.Y_AXIS));
        panel.setOpaque(false);
        javax.swing.border.TitledBorder border = javax.swing.BorderFactory.createTitledBorder(
            javax.swing.BorderFactory.createLineBorder(UZ_GROUP_BORDER),
            title
        );
        java.awt.Font titleFont = border.getTitleFont();
        if (titleFont == null) {
            titleFont = panel.getFont();
        }
        border.setTitleFont(titleFont.deriveFont(java.awt.Font.BOLD, 11f));
        border.setTitleColor(UZ_TEXT_PRIMARY);
        panel.setBorder(
            javax.swing.BorderFactory.createCompoundBorder(
                border,
                javax.swing.BorderFactory.createEmptyBorder(
                    HEADER_GROUP_CONTENT_TOP_INSET_PX,
                    HEADER_GROUP_CONTENT_SIDE_INSET_PX,
                    HEADER_GROUP_CONTENT_BOTTOM_INSET_PX,
                    HEADER_GROUP_CONTENT_SIDE_INSET_PX
                )
            )
        );
        return panel;
    }

    private javax.swing.JPanel createHeaderRowPanel() {
        javax.swing.JPanel panel = new javax.swing.JPanel(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 4, 1));
        panel.setOpaque(false);
        return panel;
    }

    private javax.swing.JPanel createHeaderColumnsPanel() {
        javax.swing.JPanel panel = new javax.swing.JPanel();
        panel.setLayout(new javax.swing.BoxLayout(panel, javax.swing.BoxLayout.X_AXIS));
        panel.setOpaque(false);
        panel.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        panel.setAlignmentY(java.awt.Component.TOP_ALIGNMENT);
        return panel;
    }

    private javax.swing.JPanel createHeaderRow(java.awt.Component... components) {
        javax.swing.JPanel row = createHeaderRowPanel();
        row.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        for (java.awt.Component component : components) {
            row.add(component);
        }
        return row;
    }

    private javax.swing.JPanel createHeaderColumnPanel() {
        javax.swing.JPanel panel = new javax.swing.JPanel();
        panel.setLayout(new javax.swing.BoxLayout(panel, javax.swing.BoxLayout.Y_AXIS));
        panel.setOpaque(false);
        panel.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        panel.setAlignmentY(java.awt.Component.TOP_ALIGNMENT);
        return panel;
    }

    private void addColumnRow(javax.swing.JPanel column, java.awt.Component... components) {
        if (column.getComponentCount() > 0) {
            column.add(javax.swing.Box.createVerticalStrut(HEADER_ROW_SPACING_PX));
        }
        column.add(createHeaderRow(components));
    }

    private void addEmptyColumnRow(javax.swing.JPanel column, int height) {
        if (column.getComponentCount() > 0) {
            column.add(javax.swing.Box.createVerticalStrut(HEADER_ROW_SPACING_PX));
        }
        javax.swing.JPanel row = createHeaderRowPanel();
        row.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        row.setMinimumSize(new java.awt.Dimension(1, height));
        row.setPreferredSize(new java.awt.Dimension(1, height));
        row.setMaximumSize(new java.awt.Dimension(Integer.MAX_VALUE, height));
        column.add(row);
    }

    private void addColumnRowTrailing(javax.swing.JPanel column, java.awt.Component trailingComponent, java.awt.Component... leadingComponents) {
        if (column.getComponentCount() > 0) {
            column.add(javax.swing.Box.createVerticalStrut(HEADER_ROW_SPACING_PX));
        }
        column.add(createHeaderRowTrailing(trailingComponent, leadingComponents));
    }

    private javax.swing.JPanel createHeaderRowTrailing(java.awt.Component trailingComponent, java.awt.Component... leadingComponents) {
        javax.swing.JPanel row = new javax.swing.JPanel();
        row.setLayout(new javax.swing.BoxLayout(row, javax.swing.BoxLayout.X_AXIS));
        row.setOpaque(false);
        row.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);

        boolean first = true;
        for (java.awt.Component component : leadingComponents) {
            if (!first) {
                row.add(javax.swing.Box.createHorizontalStrut(4));
            }
            row.add(component);
            first = false;
        }

        row.add(javax.swing.Box.createHorizontalGlue());
        if (trailingComponent != null) {
            if (!first) {
                row.add(javax.swing.Box.createHorizontalStrut(4));
            }
            row.add(trailingComponent);
        }
        return row;
    }

    private void matchHeaderGroupHeights(javax.swing.JPanel referenceGroup, javax.swing.JPanel... groups) {
        int targetHeight = referenceGroup.getPreferredSize().height;
        for (javax.swing.JPanel group : groups) {
            java.awt.Dimension preferred = group.getPreferredSize();
            int width = preferred != null ? preferred.width : group.getMinimumSize().width;
            java.awt.Dimension size = new java.awt.Dimension(width, targetHeight);
            group.setPreferredSize(size);
            group.setMinimumSize(size);
        }
    }

    private void addHeaderGroup(javax.swing.JPanel group, int gridx, int rightInsetPx) {
        java.awt.GridBagConstraints gbc = new java.awt.GridBagConstraints();
        gbc.gridx = gridx;
        gbc.gridy = 0;
        gbc.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gbc.insets = new java.awt.Insets(0, 0, 0, rightInsetPx);
        titleControlPanel.add(group, gbc);
    }

    private void setFixedWidth(javax.swing.JComponent component, int width) {
        java.awt.Dimension preferred = component.getPreferredSize();
        int height = preferred != null ? preferred.height : component.getMinimumSize().height;
        setFixedSize(component, width, height);
    }

    private void setFixedSize(javax.swing.JComponent component, int width, int height) {
        java.awt.Dimension size = new java.awt.Dimension(width, height);
        component.setPreferredSize(size);
        component.setMinimumSize(size);
        component.setMaximumSize(size);
    }

    private void unifyButtonWidths(javax.swing.JButton... buttons) {
        int maxWidth = 0;
        int maxHeight = 0;
        for (javax.swing.JButton button : buttons) {
            java.awt.Dimension preferred = button.getPreferredSize();
            if (preferred != null) {
                maxWidth = Math.max(maxWidth, preferred.width);
                maxHeight = Math.max(maxHeight, preferred.height);
            }
        }
        if (maxWidth <= 0 || maxHeight <= 0) {
            return;
        }
        java.awt.Dimension size = new java.awt.Dimension(maxWidth, maxHeight);
        for (javax.swing.JButton button : buttons) {
            button.setPreferredSize(size);
            button.setMinimumSize(size);
            button.setMaximumSize(size);
        }
    }

    private void ensureButtonTextFits(javax.swing.JButton button, String... labels) {
        if (button == null || labels == null || labels.length == 0) {
            return;
        }

        int textWidth = 0;
        java.awt.FontMetrics metrics = button.getFontMetrics(button.getFont());
        for (String label : labels) {
            if (label != null) {
                textWidth = Math.max(textWidth, metrics.stringWidth(label));
            }
        }
        java.awt.Insets insets = button.getInsets();
        int insetWidth = insets != null ? insets.left + insets.right : 0;
        int requiredWidth = textWidth + insetWidth + HEADER_BUTTON_TEXT_EXTRA_PADDING_PX;

        java.awt.Dimension preferred = button.getPreferredSize();
        int currentWidth = preferred != null ? preferred.width : 0;
        int currentHeight = preferred != null ? preferred.height : button.getMinimumSize().height;
        int targetWidth = Math.max(currentWidth, requiredWidth);
        if (targetWidth <= 0 || currentHeight <= 0) {
            return;
        }

        java.awt.Dimension size = new java.awt.Dimension(targetWidth, currentHeight);
        button.setPreferredSize(size);
        button.setMinimumSize(size);
        button.setMaximumSize(size);
    }

    private javax.swing.ImageIcon loadIconResource(String preferredResource, String fallbackResource) {
        java.net.URL resource = getClass().getResource(preferredResource);
        if (resource == null && fallbackResource != null) {
            resource = getClass().getResource(fallbackResource);
        }
        if (resource == null) {
            return null;
        }
        return new javax.swing.ImageIcon(resource);
    }

    private javax.swing.ImageIcon scaleIconToFit(javax.swing.ImageIcon sourceIcon, int maxWidthPx, int maxHeightPx) {
        if (sourceIcon == null) {
            return null;
        }

        int width = sourceIcon.getIconWidth();
        int height = sourceIcon.getIconHeight();
        if (width <= 0 || height <= 0) {
            return sourceIcon;
        }

        double widthScale = maxWidthPx > 0 ? (double) maxWidthPx / (double) width : 1.0;
        double heightScale = maxHeightPx > 0 ? (double) maxHeightPx / (double) height : 1.0;
        double scale = Math.min(1.0, Math.min(widthScale, heightScale));
        if (scale >= 1.0) {
            return sourceIcon;
        }

        int scaledWidth = Math.max(1, (int) Math.round(width * scale));
        int scaledHeight = Math.max(1, (int) Math.round(height * scale));
        java.awt.Image scaledImage = sourceIcon.getImage().getScaledInstance(scaledWidth, scaledHeight, java.awt.Image.SCALE_SMOOTH);
        return new javax.swing.ImageIcon(scaledImage);
    }

    private void applyHeaderControlStyle(javax.swing.JComponent component) {
        component.putClientProperty("FlatLaf.style", HEADER_BUTTON_STYLE);
    }

    private void applyHeaderControlActiveStyle(javax.swing.JComponent component, boolean active) {
        component.putClientProperty("FlatLaf.style", active ? HEADER_ACTIVE_BUTTON_STYLE : HEADER_BUTTON_STYLE);
        component.repaint();
    }

    private void applyNeutralToggleStyle(javax.swing.AbstractButton button) {
        button.putClientProperty("FlatLaf.style", HEADER_NEUTRAL_TOGGLE_STYLE);
    }

    private void applyHeaderInputStyle(javax.swing.JComponent component) {
        component.putClientProperty("FlatLaf.style", HEADER_INPUT_STYLE);
    }

    private void applyHeaderTextFieldLabelStyle(javax.swing.JTextField field) {
        field.putClientProperty("FlatLaf.style", null);
        field.setOpaque(false);
        field.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        field.setForeground(UZ_TEXT_PRIMARY);
        field.setDisabledTextColor(UZ_TEXT_PRIMARY);
        field.setCaretColor(UZ_TEXT_PRIMARY);
        field.setFont(lblTimeBase.getFont());
    }

    private void ensureTextFieldTextFits(javax.swing.JTextField field, String text) {
        if (field == null || text == null) {
            return;
        }
        java.awt.FontMetrics metrics = field.getFontMetrics(field.getFont());
        int textWidth = metrics.stringWidth(text);
        int requiredWidth = textWidth + 6;
        java.awt.Dimension preferred = field.getPreferredSize();
        int currentHeight = preferred != null ? preferred.height : field.getMinimumSize().height;
        if (currentHeight <= 0) {
            currentHeight = 23;
        }
        setFixedSize(field, requiredWidth, currentHeight);
    }

    private void lockPreferredWidth(javax.swing.JComponent component) {
        if (component == null) {
            return;
        }
        java.awt.Dimension preferred = component.getPreferredSize();
        if (preferred == null) {
            return;
        }
        int width = preferred.width;
        int height = preferred.height;
        component.setMinimumSize(new java.awt.Dimension(width, height));
        component.setPreferredSize(new java.awt.Dimension(width, height));
        component.setMaximumSize(new java.awt.Dimension(width, Integer.MAX_VALUE));
    }

    /**
     * @return the lblStatusUnten
     */
    public javax.swing.JLabel getLblStatusUnten() {
        return lblStatusUnten;
    }

    /**
     * @return the txtIPAdresse
     */
    public javax.swing.JTextField getTxtIPAdresse() {
        return txtIPAdresse;
    }

    /**
     * @return the btnTest
     */
    public javax.swing.JButton getBtnRunStop() {
        return btnRunStop;
    }

    /**
     * @return the BtnFixAxis
     */
    public javax.swing.JButton getBtnFixAxis() {
        return BtnFixAxis;
    }    

    /**
     * @return the comboTrigger
     */
    public javax.swing.JComboBox<String> getComboTrigger() {
        return comboTrigger;
    }

    public javax.swing.JToggleButton getBtnTriggerEdge() {
        return btnTriggerEdge;
    }

    public javax.swing.JToggleButton getBtnTriggerEnabled() {
        return btnTriggerEnabled;
    }

    public void setTriggerEnabled(boolean enabled) {
        if (btnTriggerEnabled.isSelected() != enabled) {
            btnTriggerEnabled.setSelected(enabled);
        }
        btnTriggerEnabled.setText(enabled ? "enabled" : "disabled");
    }

    public void setTriggerEdgeRising(boolean rising) {
        if (btnTriggerEdge.isSelected() != rising) {
            btnTriggerEdge.setSelected(rising);
        }
        btnTriggerEdge.setText(rising ? "\u2197 Rising" : "\u2198 Falling");
        btnTriggerEdge.setToolTipText(rising ? "Trigger on rising edge" : "Trigger on falling edge");
    }

    public void setSingleShotPending(boolean pending) {
        if (btnSingleShot.isSelected() != pending) {
            btnSingleShot.setSelected(pending);
        }
        btnSingleShot.putClientProperty("FlatLaf.style", HEADER_BUTTON_STYLE);
        btnSingleShot.repaint();
    }

    public void setLogOnOffHighlighted(boolean highlighted) {
        applyHeaderControlActiveStyle(btnLogOnOff, highlighted);
    }

    public void setFastDataLogHighlighted(boolean highlighted) {
        applyHeaderControlActiveStyle(BtnChange_fastDataLog, highlighted);
    }

    public void setSlowDataLogHighlighted(boolean highlighted) {
        applyHeaderControlActiveStyle(BtnChange_slowDataLog, highlighted);
    }

    public void setExtLoggingHighlighted(boolean highlighted) {
        applyHeaderControlActiveStyle(BtnSet_extLogging, highlighted);
    }

    public void setLogStatusHighlighted(boolean highlighted) {
        txt_LogStatus.setForeground(highlighted ? java.awt.Color.GREEN : UZ_TEXT_MUTED);
    }

    /**
     * @return the btnSingleShot
     */
    public javax.swing.JToggleButton getBtnSingleShot() {
        return btnSingleShot;
    }

    public javax.swing.JButton getBtnDetectSamplingRate() {
        return btnDetectSamplingRate;
    }

    public javax.swing.JTextField getTxtSamplingRateKHz() {
        return txtSamplingRateKHz;
    }

    public javax.swing.JTextField getTxtSamplingRateStatus() {
        return txtSamplingRateStatus;
    }

    /**
     * @return the comboTimeBase
     */
    public javax.swing.JComboBox<String> getComboTimeBase() {
        return comboTimeBase;
    }
    
    /**
     * @return the Combo_LogNthValue
     */
    public javax.swing.JComboBox<String> getCombo_LogNthValue() {
        return Combo_LogNthValue;
    }
    
    /**
     * @return the BtnSet_extLogging
     */
    public javax.swing.JButton getBtnSet_extLogging() {
        return BtnSet_extLogging;
    }

    public javax.swing.JTextField getTxtLogEveryN() {
        return txtLogEveryN;
    }

    public javax.swing.JButton getBtnNewLogFile() {
        return btnNewLogFile;
    }

    /**
     * @return the sliPreTrigger
     */
    public javax.swing.JSlider getSliPreTrigger() {
        return sliPreTrigger;
    }

    /**
     * @return the txtTriggerValue
     */
    public javax.swing.JTextField getTxtTriggerValue() {
        return txtTriggerValue;
    }

    /**
     * @return the btnSaveSettings
     */
    public javax.swing.JButton getBtnSaveSettings() {
        return btnSaveSettings;
    }

    /**
     * @return the Btn_select_JavaScope
     */
    public javax.swing.JButton getBtn_select_JavaScope() {
        return Btn_select_JavaScope;
    }
    
    /**
     * @return the txt_LogStatus
     */
    public javax.swing.JLabel getTxt_LogStatus() {
        return txt_LogStatus;
    }
    
    /**
     * @return the txt_RunStop
     */
    public javax.swing.JLabel getTxt_RunStop() {
        return txt_RunStop;
    }
    
}
