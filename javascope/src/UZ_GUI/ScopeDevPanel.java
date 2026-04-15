package UZ_GUI;

public class ScopeDevPanel extends javax.swing.JPanel {
    private final javax.swing.JPanel controlsGrid;
    private final javax.swing.JButton btnEnSystemDev;
    private final javax.swing.JButton btnEnControlDev;
    private final javax.swing.JButton btnStopDev;
    private final javax.swing.JTextField txtReadyDev;
    private final javax.swing.JTextField txtRunningDev;
    private final javax.swing.JTextField txtErrorDev;
    private final javax.swing.JTextField txtUserDev;
    private final javax.swing.JButton btnScopeDevDetectSamplingRate;
    private final javax.swing.JButton btnScopeDevPauseAck;
    private final javax.swing.JButton btnScopeDevPrintSentCommands;
    private final javax.swing.JButton btnScopeDevSingleInstanceGuard;
    private final javax.swing.JButton btnScopeDevLifecheckMonitor;
    private final javax.swing.JTextField txtScopeDevThroughput;
    private final javax.swing.JTextField txtScopeDevLifecheckStatus;
    private final javax.swing.JList<String> listScopeDevLifecheckErrors;
    private final javax.swing.JPanel lifecheckErrorPanel;

    public ScopeDevPanel() {
        super(new java.awt.GridBagLayout());
        setBorder(javax.swing.BorderFactory.createEmptyBorder(8, 8, 8, 8));

        javax.swing.JPanel headerPanel = new javax.swing.JPanel(new java.awt.GridBagLayout());
        headerPanel.setOpaque(false);

        btnEnSystemDev = new javax.swing.JButton("Enable System");
        btnEnSystemDev.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnSystemDev.setForeground(new java.awt.Color(255, 0, 0));
        btnEnSystemDev.setPreferredSize(new java.awt.Dimension(160, 35));
        btnEnSystemDev.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnSystemDev.setMaximumSize(new java.awt.Dimension(160, 35));

        btnEnControlDev = new javax.swing.JButton("Enable Control");
        btnEnControlDev.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnControlDev.setForeground(new java.awt.Color(255, 0, 0));
        btnEnControlDev.setPreferredSize(new java.awt.Dimension(160, 35));
        btnEnControlDev.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnControlDev.setMaximumSize(new java.awt.Dimension(160, 35));

        btnStopDev = new javax.swing.JButton("STOP");
        btnStopDev.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
        btnStopDev.setForeground(new java.awt.Color(255, 0, 0));

        txtReadyDev = createStatusField("Ready");
        txtRunningDev = createStatusField("Running");
        txtErrorDev = createStatusField("Error");
        txtUserDev = createStatusField("User");

        java.awt.GridBagConstraints gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 8, 10);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        headerPanel.add(btnEnSystemDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 10);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        headerPanel.add(btnEnControlDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 8, 10);
        headerPanel.add(txtReadyDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 10);
        headerPanel.add(txtRunningDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 10);
        headerPanel.add(txtUserDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 8, 10);
        headerPanel.add(txtErrorDev, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.ipadx = 5;
        gridBagConstraints.ipady = 5;
        headerPanel.add(btnStopDev, gridBagConstraints);

        controlsGrid = new javax.swing.JPanel(new java.awt.GridBagLayout());
        controlsGrid.setOpaque(false);

        btnScopeDevDetectSamplingRate = new javax.swing.JButton("detect sampling rate");
        btnScopeDevPauseAck = new javax.swing.JButton("pause 0x00 ack commands: OFF");
        btnScopeDevPrintSentCommands = new javax.swing.JButton("printSentCommands: OFF");
        btnScopeDevSingleInstanceGuard = new javax.swing.JButton("single-instance guard: OFF");
        btnScopeDevLifecheckMonitor = new javax.swing.JButton("lifecheck monitor: OFF");
        configureControlButton(btnScopeDevDetectSamplingRate);
        configureControlButton(btnScopeDevPauseAck);
        configureControlButton(btnScopeDevPrintSentCommands);
        configureControlButton(btnScopeDevSingleInstanceGuard);
        configureControlButton(btnScopeDevLifecheckMonitor);

        javax.swing.JPanel throughputPanel = new javax.swing.JPanel(new java.awt.GridBagLayout());
        throughputPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("UZ -> JavaScope throughput"));
        throughputPanel.setOpaque(false);
        throughputPanel.setPreferredSize(new java.awt.Dimension(260, 70));
        txtScopeDevThroughput = new javax.swing.JTextField("0.00 MBit/s");
        txtScopeDevThroughput.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txtScopeDevThroughput.setEditable(false);
        txtScopeDevThroughput.setFocusable(false);
        txtScopeDevThroughput.setPreferredSize(new java.awt.Dimension(160, 25));
        txtScopeDevThroughput.setMinimumSize(new java.awt.Dimension(160, 25));
        txtScopeDevThroughput.setMaximumSize(new java.awt.Dimension(160, 25));
        throughputPanel.add(txtScopeDevThroughput);

        javax.swing.JPanel lifecheckStatusPanel = new javax.swing.JPanel(new java.awt.GridBagLayout());
        lifecheckStatusPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Lifecheck status"));
        lifecheckStatusPanel.setOpaque(false);
        lifecheckStatusPanel.setPreferredSize(new java.awt.Dimension(260, 70));
        txtScopeDevLifecheckStatus = new javax.swing.JTextField("n/a");
        txtScopeDevLifecheckStatus.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScopeDevLifecheckStatus.setEditable(false);
        txtScopeDevLifecheckStatus.setFocusable(false);
        txtScopeDevLifecheckStatus.setPreferredSize(new java.awt.Dimension(160, 25));
        txtScopeDevLifecheckStatus.setMinimumSize(new java.awt.Dimension(160, 25));
        txtScopeDevLifecheckStatus.setMaximumSize(new java.awt.Dimension(160, 25));
        lifecheckStatusPanel.add(txtScopeDevLifecheckStatus);

        lifecheckErrorPanel = new javax.swing.JPanel(new java.awt.BorderLayout());
        lifecheckErrorPanel.setBorder(javax.swing.BorderFactory.createTitledBorder("Lifecheck gaps"));
        lifecheckErrorPanel.setOpaque(false);
        listScopeDevLifecheckErrors = new javax.swing.JList<>(new String[] {"-"});
        listScopeDevLifecheckErrors.setVisibleRowCount(10);
        listScopeDevLifecheckErrors.setFocusable(false);
        javax.swing.JScrollPane lifecheckErrorScrollPane = new javax.swing.JScrollPane(listScopeDevLifecheckErrors);
        lifecheckErrorScrollPane.setPreferredSize(new java.awt.Dimension(520, 130));
        lifecheckErrorPanel.add(lifecheckErrorScrollPane, java.awt.BorderLayout.CENTER);

        addControlsGridRow(0, btnScopeDevDetectSamplingRate, btnScopeDevPauseAck);
        addControlsGridRow(1, btnScopeDevPrintSentCommands, btnScopeDevLifecheckMonitor);
        addControlsGridRow(2, btnScopeDevSingleInstanceGuard, createPlaceholderPanel());
        addControlsGridRow(3, throughputPanel, lifecheckStatusPanel);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        add(headerPanel, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(14, 0, 0, 0);
        add(controlsGrid, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(8, 0, 0, 0);
        add(lifecheckErrorPanel, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        add(createPlaceholderPanel(), gridBagConstraints);
    }

    public javax.swing.JButton getBtnEnSystemDev() {
        return btnEnSystemDev;
    }

    public javax.swing.JButton getBtnEnControlDev() {
        return btnEnControlDev;
    }

    public javax.swing.JButton getBtnStopDev() {
        return btnStopDev;
    }

    public javax.swing.JTextField getTxtReadyDev() {
        return txtReadyDev;
    }

    public javax.swing.JTextField getTxtRunningDev() {
        return txtRunningDev;
    }

    public javax.swing.JTextField getTxtErrorDev() {
        return txtErrorDev;
    }

    public javax.swing.JTextField getTxtUserDev() {
        return txtUserDev;
    }

    public javax.swing.JButton getBtnScopeDevDetectSamplingRate() {
        return btnScopeDevDetectSamplingRate;
    }

    public javax.swing.JButton getBtnScopeDevPauseAck() {
        return btnScopeDevPauseAck;
    }

    public javax.swing.JButton getBtnScopeDevPrintSentCommands() {
        return btnScopeDevPrintSentCommands;
    }

    public javax.swing.JButton getBtnScopeDevSingleInstanceGuard() {
        return btnScopeDevSingleInstanceGuard;
    }

    public javax.swing.JTextField getTxtScopeDevThroughput() {
        return txtScopeDevThroughput;
    }

    public javax.swing.JButton getBtnScopeDevLifecheckMonitor() {
        return btnScopeDevLifecheckMonitor;
    }

    public javax.swing.JTextField getTxtScopeDevLifecheckStatus() {
        return txtScopeDevLifecheckStatus;
    }

    public javax.swing.JList<String> getListScopeDevLifecheckErrors() {
        return listScopeDevLifecheckErrors;
    }

    public void applyTheme(java.awt.Color background) {
        setBackground(background);
        controlsGrid.setBackground(background);
        lifecheckErrorPanel.setBackground(background);
    }

    private void addControlsGridRow(int row, java.awt.Component leftComponent, java.awt.Component rightComponent) {
        java.awt.GridBagConstraints leftConstraints = new java.awt.GridBagConstraints();
        leftConstraints.gridx = 0;
        leftConstraints.gridy = row;
        leftConstraints.weightx = 0.5;
        leftConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        leftConstraints.insets = new java.awt.Insets(0, 0, 8, 8);
        controlsGrid.add(leftComponent, leftConstraints);

        java.awt.GridBagConstraints rightConstraints = new java.awt.GridBagConstraints();
        rightConstraints.gridx = 1;
        rightConstraints.gridy = row;
        rightConstraints.weightx = 0.5;
        rightConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        rightConstraints.insets = new java.awt.Insets(0, 0, 8, 0);
        controlsGrid.add(rightComponent, rightConstraints);
    }

    private static void configureControlButton(javax.swing.JButton button) {
        button.setPreferredSize(new java.awt.Dimension(250, 40));
        button.setMinimumSize(new java.awt.Dimension(180, 36));
        button.setMargin(new java.awt.Insets(6, 10, 6, 10));
        button.setFocusPainted(false);
    }

    private static javax.swing.JTextField createStatusField(String text) {
        javax.swing.JTextField field = new javax.swing.JTextField(text);
        field.setForeground(new java.awt.Color(51, 51, 51));
        field.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        field.setEnabled(false);
        field.setMaximumSize(new java.awt.Dimension(75, 22));
        field.setMinimumSize(new java.awt.Dimension(75, 22));
        field.setPreferredSize(new java.awt.Dimension(75, 22));
        return field;
    }

    private static javax.swing.JPanel createPlaceholderPanel() {
        javax.swing.JPanel panel = new javax.swing.JPanel();
        panel.setOpaque(false);
        return panel;
    }
}
