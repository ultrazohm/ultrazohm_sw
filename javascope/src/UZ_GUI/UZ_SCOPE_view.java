/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;

/**
 *
 * @author Hufnagel
 */
public class UZ_SCOPE_view extends javax.swing.JInternalFrame {
    private static final String ACCENT_VIOLET_HEX = "#7C3AED";
    private static final java.awt.Color SURFACE_DARK = new java.awt.Color(0x2F, 0x31, 0x36);
    private static final java.awt.Color SURFACE_DARK_RAISED = new java.awt.Color(0x3A, 0x3D, 0x41);
    private static final java.awt.Color SURFACE_LIGHT = new java.awt.Color(0xF4, 0xF5, 0xF7);
    private static final java.awt.Color SURFACE_LIGHT_RAISED = new java.awt.Color(0xFF, 0xFF, 0xFF);
    private static final int CHANNEL_LEGEND_ROWS = 20;
    private static final int CHANNEL_LEGEND_START_ROW = 3;
    private static final int CHANNEL_LEGEND_COLUMN = 0;
    private static final int CHANNEL_COMBO_COLUMN = 1;
    private static final int CHANNEL_COMBO_WIDTH = 4;

    private javax.swing.JToggleButton[] channelVisibilityButtons;
    private javax.swing.JLabel channelVisibilityLabel;
    private final ScopeDevPanel scopeDevPanel = new ScopeDevPanel();

    /**
     * @return the lbl_snd_fld_10
     */
    public javax.swing.JLabel getLbl_snd_fld_10() {
        return lbl_snd_fld_10;
    }

    /**
     * @return the lbl_snd_fld_11
     */
    public javax.swing.JLabel getLbl_snd_fld_11() {
        return lbl_snd_fld_11;
    }

    /**
     * @return the lbl_snd_fld_12
     */
    public javax.swing.JLabel getLbl_snd_fld_12() {
        return lbl_snd_fld_12;
    }

    /**
     * @return the lbl_snd_fld_13
     */
    public javax.swing.JLabel getLbl_snd_fld_13() {
        return lbl_snd_fld_13;
    }

    /**
     * @return the lbl_snd_fld_14
     */
    public javax.swing.JLabel getLbl_snd_fld_14() {
        return lbl_snd_fld_14;
    }

    /**
     * @return the lbl_snd_fld_15
     */
    public javax.swing.JLabel getLbl_snd_fld_15() {
        return lbl_snd_fld_15;
    }

    /**
     * @return the lbl_snd_fld_16
     */
    public javax.swing.JLabel getLbl_snd_fld_16() {
        return lbl_snd_fld_16;
    }

    /**
     * @return the lbl_snd_fld_17
     */
    public javax.swing.JLabel getLbl_snd_fld_17() {
        return lbl_snd_fld_17;
    }

    /**
     * @return the lbl_snd_fld_18
     */
    public javax.swing.JLabel getLbl_snd_fld_18() {
        return lbl_snd_fld_18;
    }

    /**
     * @return the lbl_snd_fld_19
     */
    public javax.swing.JLabel getLbl_snd_fld_19() {
        return lbl_snd_fld_19;
    }

    /**
     * @return the lbl_snd_fld_20
     */
    public javax.swing.JLabel getLbl_snd_fld_20() {
        return lbl_snd_fld_20;
    }

    /**
     * @return the lbl_snd_fld_7
     */
    public javax.swing.JLabel getLbl_snd_fld_7() {
        return lbl_snd_fld_7;
    }

    /**
     * @return the lbl_snd_fld_8
     */
    public javax.swing.JLabel getLbl_snd_fld_8() {
        return lbl_snd_fld_8;
    }

    /**
     * @return the lbl_snd_fld_9
     */
    public javax.swing.JLabel getLbl_snd_fld_9() {
        return lbl_snd_fld_9;
    }

    /**
     * @return the field_10
     */
    public javax.swing.JPanel getField_10() {
        return field_10;
    }

    /**
     * @return the field_11
     */
    public javax.swing.JPanel getField_11() {
        return field_11;
    }

    /**
     * @return the field_12
     */
    public javax.swing.JPanel getField_12() {
        return field_12;
    }

    /**
     * @return the field_13
     */
    public javax.swing.JPanel getField_13() {
        return field_13;
    }

    /**
     * @return the field_14
     */
    public javax.swing.JPanel getField_14() {
        return field_14;
    }

    /**
     * @return the field_15
     */
    public javax.swing.JPanel getField_15() {
        return field_15;
    }

    /**
     * @return the field_16
     */
    public javax.swing.JPanel getField_16() {
        return field_16;
    }

    /**
     * @return the field_17
     */
    public javax.swing.JPanel getField_17() {
        return field_17;
    }

    /**
     * @return the field_18
     */
    public javax.swing.JPanel getField_18() {
        return field_18;
    }

    /**
     * @return the field_19
     */
    public javax.swing.JPanel getField_19() {
        return field_19;
    }

    /**
     * @return the field_20
     */
    public javax.swing.JPanel getField_20() {
        return field_20;
    }

    /**
     * @return the field_7
     */
    public javax.swing.JPanel getField_7() {
        return field_7;
    }

    /**
     * @return the field_8
     */
    public javax.swing.JPanel getField_8() {
        return field_8;
    }

    /**
     * @return the field_9
     */
    public javax.swing.JPanel getField_9() {
        return field_9;
    }

    /**
     * @return the lbl_rcv_fld_10
     */
    public javax.swing.JLabel getLbl_rcv_fld_10() {
        return lbl_rcv_fld_10;
    }

    /**
     * @return the lbl_rcv_fld_11
     */
    public javax.swing.JLabel getLbl_rcv_fld_11() {
        return lbl_rcv_fld_11;
    }

    /**
     * @return the lbl_rcv_fld_12
     */
    public javax.swing.JLabel getLbl_rcv_fld_12() {
        return lbl_rcv_fld_12;
    }

    /**
     * @return the lbl_rcv_fld_13
     */
    public javax.swing.JLabel getLbl_rcv_fld_13() {
        return lbl_rcv_fld_13;
    }

    /**
     * @return the lbl_rcv_fld_14
     */
    public javax.swing.JLabel getLbl_rcv_fld_14() {
        return lbl_rcv_fld_14;
    }

    /**
     * @return the lbl_rcv_fld_15
     */
    public javax.swing.JLabel getLbl_rcv_fld_15() {
        return lbl_rcv_fld_15;
    }

    /**
     * @return the lbl_rcv_fld_16
     */
    public javax.swing.JLabel getLbl_rcv_fld_16() {
        return lbl_rcv_fld_16;
    }

    /**
     * @return the lbl_rcv_fld_17
     */
    public javax.swing.JLabel getLbl_rcv_fld_17() {
        return lbl_rcv_fld_17;
    }

    /**
     * @return the lbl_rcv_fld_18
     */
    public javax.swing.JLabel getLbl_rcv_fld_18() {
        return lbl_rcv_fld_18;
    }

    /**
     * @return the lbl_rcv_fld_19
     */
    public javax.swing.JLabel getLbl_rcv_fld_19() {
        return lbl_rcv_fld_19;
    }

    /**
     * @return the lbl_rcv_fld_20
     */
    public javax.swing.JLabel getLbl_rcv_fld_20() {
        return lbl_rcv_fld_20;
    }

    /**
     * @return the lbl_rcv_fld_7
     */
    public javax.swing.JLabel getLbl_rcv_fld_7() {
        return lbl_rcv_fld_7;
    }

    /**
     * @return the lbl_rcv_fld_8
     */
    public javax.swing.JLabel getLbl_rcv_fld_8() {
        return lbl_rcv_fld_8;
    }

    /**
     * @return the lbl_rcv_fld_9
     */
    public javax.swing.JLabel getLbl_rcv_fld_9() {
        return lbl_rcv_fld_9;
    }

    /**
     * @return the receive_field_10
     */
    public javax.swing.JPanel getReceive_field_10() {
        return receive_field_10;
    }

    /**
     * @return the receive_field_11
     */
    public javax.swing.JPanel getReceive_field_11() {
        return receive_field_11;
    }

    /**
     * @return the receive_field_12
     */
    public javax.swing.JPanel getReceive_field_12() {
        return receive_field_12;
    }

    /**
     * @return the receive_field_13
     */
    public javax.swing.JPanel getReceive_field_13() {
        return receive_field_13;
    }

    /**
     * @return the receive_field_14
     */
    public javax.swing.JPanel getReceive_field_14() {
        return receive_field_14;
    }

    /**
     * @return the receive_field_15
     */
    public javax.swing.JPanel getReceive_field_15() {
        return receive_field_15;
    }

    /**
     * @return the receive_field_16
     */
    public javax.swing.JPanel getReceive_field_16() {
        return receive_field_16;
    }

    /**
     * @return the receive_field_17
     */
    public javax.swing.JPanel getReceive_field_17() {
        return receive_field_17;
    }

    /**
     * @return the receive_field_18
     */
    public javax.swing.JPanel getReceive_field_18() {
        return receive_field_18;
    }

    /**
     * @return the receive_field_19
     */
    public javax.swing.JPanel getReceive_field_19() {
        return receive_field_19;
    }

    /**
     * @return the receive_field_20
     */
    public javax.swing.JPanel getReceive_field_20() {
        return receive_field_20;
    }

    /**
     * @return the receive_field_7
     */
    public javax.swing.JPanel getReceive_field_7() {
        return receive_field_7;
    }

    /**
     * @return the receive_field_8
     */
    public javax.swing.JPanel getReceive_field_8() {
        return receive_field_8;
    }

    /**
     * @return the receive_field_9
     */
    public javax.swing.JPanel getReceive_field_9() {
        return receive_field_9;
    }

    /**
     * @return the BtnSetSendField_19
     */
    public javax.swing.JButton getBtnSetSendField_19() {
        return BtnSetSendField_19;
    }

    /**
     * @return the BtnSetSendField_20
     */
    public javax.swing.JButton getBtnSetSendField_20() {
        return BtnSetSendField_20;
    }

    /**
     * @return the txt_rcv_fld_19
     */
    public javax.swing.JTextField getTxt_rcv_fld_19() {
        return txt_rcv_fld_19;
    }

    /**
     * @return the txt_rcv_fld_20
     */
    public javax.swing.JTextField getTxt_rcv_fld_20() {
        return txt_rcv_fld_20;
    }

    /**
     * @return the txt_snd_fld_19
     */
    public javax.swing.JTextField getTxt_snd_fld_19() {
        return txt_snd_fld_19;
    }

    /**
     * @return the txt_snd_fld_20
     */
    public javax.swing.JTextField getTxt_snd_fld_20() {
        return txt_snd_fld_20;
    }

    /**
     * @return the txtError1
     */
    public javax.swing.JTextField getTxtError1() {
        return txtError1;
    }

    /**
     * @return the txtReady1
     */
    public javax.swing.JTextField getTxtReady1() {
        return txtReady1;
    }

    /**
     * @return the txtRunning1
     */
    public javax.swing.JTextField getTxtRunning1() {
        return txtRunning1;
    }

    /**
     * @return the txtUser1
     */
    public javax.swing.JTextField getTxtUser1() {
        return txtUser1;
    }

    /**
     * @return the btnEnControl1
     */
    public javax.swing.JButton getBtnEnControl1() {
        return btnEnControl1;
    }

    /**
     * @return the btnEnSystem1
     */
    public javax.swing.JButton getBtnEnSystem1() {
        return btnEnSystem1;
    }

    /**
     * @return the btnStop1
     */
    public javax.swing.JButton getBtnStop1() {
        return btnStop1;
    }

    public javax.swing.JButton getBtnEnSystemDev() {
        return scopeDevPanel.getBtnEnSystemDev();
    }

    public javax.swing.JButton getBtnEnControlDev() {
        return scopeDevPanel.getBtnEnControlDev();
    }

    public javax.swing.JButton getBtnStopDev() {
        return scopeDevPanel.getBtnStopDev();
    }

    public javax.swing.JTextField getTxtReadyDev() {
        return scopeDevPanel.getTxtReadyDev();
    }

    public javax.swing.JTextField getTxtRunningDev() {
        return scopeDevPanel.getTxtRunningDev();
    }

    public javax.swing.JTextField getTxtErrorDev() {
        return scopeDevPanel.getTxtErrorDev();
    }

    public javax.swing.JTextField getTxtUserDev() {
        return scopeDevPanel.getTxtUserDev();
    }

    public javax.swing.JButton getBtnScopeDevDetectSamplingRate() {
        return scopeDevPanel.getBtnScopeDevDetectSamplingRate();
    }

    public javax.swing.JButton getBtnScopeDevPauseAck() {
        return scopeDevPanel.getBtnScopeDevPauseAck();
    }

    public javax.swing.JButton getBtnScopeDevPrintSentCommands() {
        return scopeDevPanel.getBtnScopeDevPrintSentCommands();
    }

    public javax.swing.JButton getBtnScopeDevSingleInstanceGuard() {
        return scopeDevPanel.getBtnScopeDevSingleInstanceGuard();
    }

    public javax.swing.JTextField getTxtScopeDevThroughput() {
        return scopeDevPanel.getTxtScopeDevThroughput();
    }

    public javax.swing.JButton getBtnScopeDevLifecheckMonitor() {
        return scopeDevPanel.getBtnScopeDevLifecheckMonitor();
    }

    public javax.swing.JTextField getTxtScopeDevLifecheckStatus() {
        return scopeDevPanel.getTxtScopeDevLifecheckStatus();
    }

    public javax.swing.JList<String> getListScopeDevLifecheckErrors() {
        return scopeDevPanel.getListScopeDevLifecheckErrors();
    }

    /**
     * @return the BtnSetSendField_10
     */
    public javax.swing.JButton getBtnSetSendField_10() {
        return BtnSetSendField_10;
    }

    /**
     * @return the BtnSetSendField_11
     */
    public javax.swing.JButton getBtnSetSendField_11() {
        return BtnSetSendField_11;
    }

    /**
     * @return the BtnSetSendField_12
     */
    public javax.swing.JButton getBtnSetSendField_12() {
        return BtnSetSendField_12;
    }

    /**
     * @return the BtnSetSendField_13
     */
    public javax.swing.JButton getBtnSetSendField_13() {
        return BtnSetSendField_13;
    }

    /**
     * @return the BtnSetSendField_14
     */
    public javax.swing.JButton getBtnSetSendField_14() {
        return BtnSetSendField_14;
    }

    /**
     * @return the BtnSetSendField_15
     */
    public javax.swing.JButton getBtnSetSendField_15() {
        return BtnSetSendField_15;
    }

    /**
     * @return the BtnSetSendField_16
     */
    public javax.swing.JButton getBtnSetSendField_16() {
        return BtnSetSendField_16;
    }

    /**
     * @return the BtnSetSendField_17
     */
    public javax.swing.JButton getBtnSetSendField_17() {
        return BtnSetSendField_17;
    }

    /**
     * @return the BtnSetSendField_18
     */
    public javax.swing.JButton getBtnSetSendField_18() {
        return BtnSetSendField_18;
    }

    /**
     * @return the BtnSetSendField_7
     */
    public javax.swing.JButton getBtnSetSendField_7() {
        return BtnSetSendField_7;
    }

    /**
     * @return the BtnSetSendField_8
     */
    public javax.swing.JButton getBtnSetSendField_8() {
        return BtnSetSendField_8;
    }

    /**
     * @return the BtnSetSendField_9
     */
    public javax.swing.JButton getBtnSetSendField_9() {
        return BtnSetSendField_9;
    }

    /**
     * @return the txt_snd_fld_10
     */
    public javax.swing.JTextField getTxt_snd_fld_10() {
        return txt_snd_fld_10;
    }

    /**
     * @return the txt_snd_fld_11
     */
    public javax.swing.JTextField getTxt_snd_fld_11() {
        return txt_snd_fld_11;
    }

    /**
     * @return the txt_snd_fld_12
     */
    public javax.swing.JTextField getTxt_snd_fld_12() {
        return txt_snd_fld_12;
    }

    /**
     * @return the txt_snd_fld_13
     */
    public javax.swing.JTextField getTxt_snd_fld_13() {
        return txt_snd_fld_13;
    }

    /**
     * @return the txt_snd_fld_14
     */
    public javax.swing.JTextField getTxt_snd_fld_14() {
        return txt_snd_fld_14;
    }

    /**
     * @return the txt_snd_fld_15
     */
    public javax.swing.JTextField getTxt_snd_fld_15() {
        return txt_snd_fld_15;
    }

    /**
     * @return the txt_snd_fld_16
     */
    public javax.swing.JTextField getTxt_snd_fld_16() {
        return txt_snd_fld_16;
    }

    /**
     * @return the txt_snd_fld_17
     */
    public javax.swing.JTextField getTxt_snd_fld_17() {
        return txt_snd_fld_17;
    }

    /**
     * @return the txt_snd_fld_18
     */
    public javax.swing.JTextField getTxt_snd_fld_18() {
        return txt_snd_fld_18;
    }

    /**
     * @return the txt_snd_fld_7
     */
    public javax.swing.JTextField getTxt_snd_fld_7() {
        return txt_snd_fld_7;
    }

    /**
     * @return the txt_snd_fld_8
     */
    public javax.swing.JTextField getTxt_snd_fld_8() {
        return txt_snd_fld_8;
    }

    /**
     * @return the txt_snd_fld_9
     */
    public javax.swing.JTextField getTxt_snd_fld_9() {
        return txt_snd_fld_9;
    }

    /**
     * @return the txt_rcv_fld_10
     */
    public javax.swing.JTextField getTxt_rcv_fld_10() {
        return txt_rcv_fld_10;
    }

    /**
     * @return the txt_rcv_fld_11
     */
    public javax.swing.JTextField getTxt_rcv_fld_11() {
        return txt_rcv_fld_11;
    }

    /**
     * @return the txt_rcv_fld_12
     */
    public javax.swing.JTextField getTxt_rcv_fld_12() {
        return txt_rcv_fld_12;
    }

    /**
     * @return the txt_rcv_fld_13
     */
    public javax.swing.JTextField getTxt_rcv_fld_13() {
        return txt_rcv_fld_13;
    }

    /**
     * @return the txt_rcv_fld_14
     */
    public javax.swing.JTextField getTxt_rcv_fld_14() {
        return txt_rcv_fld_14;
    }

    /**
     * @return the txt_rcv_fld_15
     */
    public javax.swing.JTextField getTxt_rcv_fld_15() {
        return txt_rcv_fld_15;
    }

    /**
     * @return the txt_rcv_fld_16
     */
    public javax.swing.JTextField getTxt_rcv_fld_16() {
        return txt_rcv_fld_16;
    }

    /**
     * @return the txt_rcv_fld_17
     */
    public javax.swing.JTextField getTxt_rcv_fld_17() {
        return txt_rcv_fld_17;
    }

    /**
     * @return the txt_rcv_fld_18
     */
    public javax.swing.JTextField getTxt_rcv_fld_18() {
        return txt_rcv_fld_18;
    }

    /**
     * @return the txt_rcv_fld_7
     */
    public javax.swing.JTextField getTxt_rcv_fld_7() {
        return txt_rcv_fld_7;
    }

    /**
     * @return the txt_rcv_fld_8
     */
    public javax.swing.JTextField getTxt_rcv_fld_8() {
        return txt_rcv_fld_8;
    }

    /**
     * @return the txt_rcv_fld_9
     */
    public javax.swing.JTextField getTxt_rcv_fld_9() {
        return txt_rcv_fld_9;
    }

        /**
     */

    /**
     */

    /**
     * @return the myBtn_1
     */
    public javax.swing.JButton getMyBtn_1() {
        return myBtn_1;
    }

    /**
     * @return the myBtn_2
     */
    public javax.swing.JButton getMyBtn_2() {
        return myBtn_2;
    }

    /**
     * @return the myBtn_3
     */
    public javax.swing.JButton getMyBtn_3() {
        return myBtn_3;
    }

    /**
     * @return the myBtn_4
     */
    public javax.swing.JButton getMyBtn_4() {
        return myBtn_4;
    }

    /**
     * @return the myBtn_5
     */
    public javax.swing.JButton getMyBtn_5() {
        return myBtn_5;
    }

    /**
     * @return the myBtn_6
     */
    public javax.swing.JButton getMyBtn_6() {
        return myBtn_6;
    }

    /**
     * @return the myBtn_7
     */
    public javax.swing.JButton getMyBtn_7() {
        return myBtn_7;
    }

    /**
     * @return the myBtn_8
     */
    public javax.swing.JButton getMyBtn_8() {
        return myBtn_8;
    }

    /**
     * @return the txtBtn1
     */
    public javax.swing.JTextField getTxtBtn1() {
        return txtBtn1;
    }

    /**
     * @return the txtBtn2
     */
    public javax.swing.JTextField getTxtBtn2() {
        return txtBtn2;
    }

    /**
     * @return the txtBtn3
     */
    public javax.swing.JTextField getTxtBtn3() {
        return txtBtn3;
    }

    /**
     * @return the txtBtn4
     */
    public javax.swing.JTextField getTxtBtn4() {
        return txtBtn4;
    }

    /**
     * @return the txtBtn5
     */
    public javax.swing.JTextField getTxtBtn5() {
        return txtBtn5;
    }

    /**
     * @return the txtBtn6
     */
    public javax.swing.JTextField getTxtBtn6() {
        return txtBtn6;
    }

    /**
     * @return the txtBtn7
     */
    public javax.swing.JTextField getTxtBtn7() {
        return txtBtn7;
    }

    /**
     * @return the txtBtn8
     */
    public javax.swing.JTextField getTxtBtn8() {
        return txtBtn8;
    }
    /**
     * @return the tbSlowData3
     */
    public javax.swing.JTable getTbSlowData3() {
        return tbSlowData3;
    }
    
    /**
     * @return the btnScaleMinusCH1
     */
    public javax.swing.JButton getBtnScaleMinusCH1() {
        return btnScaleMinusCH1;
    }

    /**
     * @return the btnScaleMinusCH2
     */
    public javax.swing.JButton getBtnScaleMinusCH2() {
        return btnScaleMinusCH2;
    }

    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH3() {
        return btnScaleMinusCH3;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH4() {
        return btnScaleMinusCH4;
    }
    
    /**
     * @return the btnScaleMinusCH1
     */
    public javax.swing.JButton getBtnScaleMinusCH5() {
        return btnScaleMinusCH5;
    }

    /**
     * @return the btnScaleMinusCH2
     */
    public javax.swing.JButton getBtnScaleMinusCH6() {
        return btnScaleMinusCH6;
    }

    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH7() {
        return btnScaleMinusCH7;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH8() {
        return btnScaleMinusCH8;
    }
    
    /**
     * @return the btnScaleMinusCH1
     */
    public javax.swing.JButton getBtnScaleMinusCH9() {
        return btnScaleMinusCH9;
    }

    /**
     * @return the btnScaleMinusCH2
     */
    public javax.swing.JButton getBtnScaleMinusCH10() {
        return btnScaleMinusCH10;
    }

    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH11() {
        return btnScaleMinusCH11;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH12() {
        return btnScaleMinusCH12;
    }
    
    
    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH13() {
        return btnScaleMinusCH13;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH14() {
        return btnScaleMinusCH14;
    }
    
    /**
     * @return the btnScaleMinusCH1
     */
    public javax.swing.JButton getBtnScaleMinusCH15() {
        return btnScaleMinusCH15;
    }

    /**
     * @return the btnScaleMinusCH2
     */
    public javax.swing.JButton getBtnScaleMinusCH16() {
        return btnScaleMinusCH16;
    }

    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH17() {
        return btnScaleMinusCH17;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH18() {
        return btnScaleMinusCH18;
    }
    
    /**
     * @return the btnScaleMinusCH3
     */
    public javax.swing.JButton getBtnScaleMinusCH19() {
        return btnScaleMinusCH19;
    }

    /**
     * @return the btnScaleMinusCH4
     */
    public javax.swing.JButton getBtnScaleMinusCH20() {
        return btnScaleMinusCH20;
    }

    /**
     * @return the btnScalePlusCH1
     */
    public javax.swing.JButton getBtnScalePlusCH1() {
        return btnScalePlusCH1;
    }

    /**
     * @return the btnScalePlusCH2
     */
    public javax.swing.JButton getBtnScalePlusCH2() {
        return btnScalePlusCH2;
    }

    /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH3() {
        return btnScalePlusCH3;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH4() {
        return btnScalePlusCH4;
    }
    
    
    /**
     * @return the btnScalePlusCH1
     */
    public javax.swing.JButton getBtnScalePlusCH5() {
        return btnScalePlusCH5;
    }

    /**
     * @return the btnScalePlusCH2
     */
    public javax.swing.JButton getBtnScalePlusCH6() {
        return btnScalePlusCH6;
    }

    /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH7() {
        return btnScalePlusCH7;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH8() {
        return btnScalePlusCH8;
    }
    
     /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH9() {
        return btnScalePlusCH9;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH10() {
        return btnScalePlusCH10;
    }
    
    /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH11() {
        return btnScalePlusCH11;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH12() {
        return btnScalePlusCH12;
    }
    
    
    /**
     * @return the btnScalePlusCH1
     */
    public javax.swing.JButton getBtnScalePlusCH13() {
        return btnScalePlusCH13;
    }

    /**
     * @return the btnScalePlusCH2
     */
    public javax.swing.JButton getBtnScalePlusCH14() {
        return btnScalePlusCH14;
    }

    /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH15() {
        return btnScalePlusCH15;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH16() {
        return btnScalePlusCH16;
    }
    
     /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH17() {
        return btnScalePlusCH17;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH18() {
        return btnScalePlusCH18;
    }
    
    /**
     * @return the btnScalePlusCH3
     */
    public javax.swing.JButton getBtnScalePlusCH19() {
        return btnScalePlusCH19;
    }

    /**
     * @return the btnScalePlusCH4
     */
    public javax.swing.JButton getBtnScalePlusCH20() {
        return btnScalePlusCH20;
    }

    /**
     * @return the GraphJFree
     */
    public javax.swing.JPanel getGraphJFree() {
        return GraphJFree;
    }
    
    /**
     */

    /**
     */

    /**
     */

    /**
     */
    
    /**
     */

    /**
     */

    /**
     */

    /**
     */
    
    /**
     */

    /**
     */
    
    /**
     */

    /**
     */

    /**
     */
    
    /**
     */

    /**
     */
    
    /**
     */
    
    /**
     */

    /**
     */
    
    /**
     */

    /**
     */
    

    /**
     */

    /**
     */

    /**
     */

    /**
     */
    
    

    /**
     */

    /**
     */

    /**
     */
    

    /**
     */

    /**
     */

    /**
     */
    

    /**
     */

    /**
     */

    /**
     */
    
     /**
     */

    /**
     */
    
    /**
     */

    /**
     */
    
    /**
     * @return the txtOffsetCH1
     */
    public javax.swing.JTextField getTxtOffsetCH1() {
        return txtOffsetCH1;
    }

    /**
     * @return the txtOffsetCH2
     */
    public javax.swing.JTextField getTxtOffsetCH2() {
        return txtOffsetCH2;
    }

    /**
     * @return the txtOffsetCH3
     */
    public javax.swing.JTextField getTxtOffsetCH3() {
        return txtOffsetCH3;
    }

    /**
     * @return the txtOffsetCH4
     */
    public javax.swing.JTextField getTxtOffsetCH4() {
        return txtOffsetCH4;
    }
      
    /**
     * @return the txtOffsetCH5
     */
    public javax.swing.JTextField getTxtOffsetCH5() {
        return txtOffsetCH5;
    }
    
    /**
     * @return the txtOffsetCH6
     */
    public javax.swing.JTextField getTxtOffsetCH6() {
        return txtOffsetCH6;
    }

    /**
     * @return the txtOffsetCH7
     */
    public javax.swing.JTextField getTxtOffsetCH7() {
        return txtOffsetCH7;
    }

    /**
     * @return the txtOffsetCH8
     */
    public javax.swing.JTextField getTxtOffsetCH8() {
        return txtOffsetCH8;
    }

    /**
     * @return the txtOffsetCH9
     */
    public javax.swing.JTextField getTxtOffsetCH9() {
        return txtOffsetCH9;
    }
      
    /**
     * @return the txtOffsetCH10
     */
    public javax.swing.JTextField getTxtOffsetCH10() {
        return txtOffsetCH10;
    }
    
    /**
     * @return the txtOffsetCH11
     */
    public javax.swing.JTextField getTxtOffsetCH11() {
        return txtOffsetCH11;
    }

    /**
     * @return the txtOffsetCH12
     */
    public javax.swing.JTextField getTxtOffsetCH12() {
        return txtOffsetCH12;
    }

    /**
     * @return the txtOffsetCH13
     */
    public javax.swing.JTextField getTxtOffsetCH13() {
        return txtOffsetCH13;
    }

    /**
     * @return the txtOffsetCH14
     */
    public javax.swing.JTextField getTxtOffsetCH14() {
        return txtOffsetCH14;
    }
      
    /**
     * @return the txtOffsetCH15
     */
    public javax.swing.JTextField getTxtOffsetCH15() {
        return txtOffsetCH15;
    }
    
    /**
     * @return the txtOffsetCH16
     */
    public javax.swing.JTextField getTxtOffsetCH16() {
        return txtOffsetCH16;
    }

    /**
     * @return the txtOffsetCH17
     */
    public javax.swing.JTextField getTxtOffsetCH17() {
        return txtOffsetCH17;
    }
      
    /**
     * @return the txtOffsetCH18
     */
    public javax.swing.JTextField getTxtOffsetCH18() {
        return txtOffsetCH18;
    }
    
    /**
     * @return the txtOffsetCH19
     */
    public javax.swing.JTextField getTxtOffsetCH19() {
        return txtOffsetCH19;
    }
      
    /**
     * @return the txtOffsetCH20
     */
    public javax.swing.JTextField getTxtOffsetCH20() {
        return txtOffsetCH20;
    }
    
    /**
     * @return the txtScaleCH1
     */
    public javax.swing.JTextField getTxtScaleCH1() {
        return txtScaleCH1;
    }

    /**
     * @return the txtScaleCH2
     */
    public javax.swing.JTextField getTxtScaleCH2() {
        return txtScaleCH2;
    }

    /**
     * @return the txtScaleCH3
     */
    public javax.swing.JTextField getTxtScaleCH3() {
        return txtScaleCH3;
    }

    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH4() {
        return txtScaleCH4;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH5() {
        return txtScaleCH5;
    }
    
    /**
     * @return the txtScaleCH1
     */
    public javax.swing.JTextField getTxtScaleCH6() {
        return txtScaleCH6;
    }

    /**
     * @return the txtScaleCH2
     */
    public javax.swing.JTextField getTxtScaleCH7() {
        return txtScaleCH7;
    }

    /**
     * @return the txtScaleCH3
     */
    public javax.swing.JTextField getTxtScaleCH8() {
        return txtScaleCH8;
    }

    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH9() {
        return txtScaleCH9;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH10() {
        return txtScaleCH10;
    }
    
    /**
     * @return the txtScaleCH1
     */
    public javax.swing.JTextField getTxtScaleCH11() {
        return txtScaleCH11;
    }

    /**
     * @return the txtScaleCH2
     */
    public javax.swing.JTextField getTxtScaleCH12() {
        return txtScaleCH12;
    }

    /**
     * @return the txtScaleCH3
     */
    public javax.swing.JTextField getTxtScaleCH13() {
        return txtScaleCH13;
    }

    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH14() {
        return txtScaleCH14;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH15() {
        return txtScaleCH15;
    }
    
    /**
     * @return the txtScaleCH3
     */
    public javax.swing.JTextField getTxtScaleCH16() {
        return txtScaleCH16;
    }

    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH17() {
        return txtScaleCH17;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH18() {
        return txtScaleCH18;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH19() {
        return txtScaleCH19;
    }
    
    /**
     * @return the txtScaleCH4
     */
    public javax.swing.JTextField getTxtScaleCH20() {
        return txtScaleCH20;
    }
    
    /**
     */

    /**
     * @return the comboSelectData1
     */
    public javax.swing.JComboBox<String> getComboSelectData1() {
        return comboSelectData1;
    }

    /**
     * @return the comboSelectData2
     */
    public javax.swing.JComboBox<String> getComboSelectData2() {
        return comboSelectData2;
    }

    /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData3() {
        return comboSelectData3;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData4() {
        return comboSelectData4;
    }
    
    /**
     * @return the comboSelectData1
     */
    public javax.swing.JComboBox<String> getComboSelectData5() {
        return comboSelectData5;
    }

    /**
     * @return the comboSelectData2
     */
    public javax.swing.JComboBox<String> getComboSelectData6() {
        return comboSelectData6;
    }

    /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData7() {
        return comboSelectData7;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData8() {
        return comboSelectData8;
    }
    
    
    /**
     * @return the comboSelectData1
     */
    public javax.swing.JComboBox<String> getComboSelectData9() {
        return comboSelectData9;
    }

    /**
     * @return the comboSelectData2
     */
    public javax.swing.JComboBox<String> getComboSelectData10() {
        return comboSelectData10;
    }

    /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData11() {
        return comboSelectData11;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData12() {
        return comboSelectData12;
    }
    
    /**
     * @return the comboSelectData1
     */
    public javax.swing.JComboBox<String> getComboSelectData13() {
        return comboSelectData13;
    }

    /**
     * @return the comboSelectData2
     */
    public javax.swing.JComboBox<String> getComboSelectData14() {
        return comboSelectData14;
    }

    /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData15() {
        return comboSelectData15;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData16() {
        return comboSelectData16;
    }
    
    /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData17() {
        return comboSelectData17;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData18() {
        return comboSelectData18;
    }
    
     /**
     * @return the comboSelectData3
     */
    public javax.swing.JComboBox<String> getComboSelectData19() {
        return comboSelectData19;
    }

    /**
     * @return the comboSelectData4
     */
    public javax.swing.JComboBox<String> getComboSelectData20() {
        return comboSelectData20;
    } 

    /**
     * @return the BtnSetSendField_1
     */
    public javax.swing.JButton getBtnSetSendField_1() {
        return BtnSetSendField_1;
    }

    /**
     * @return the BtnSetSendField_2
     */
    public javax.swing.JButton getBtnSetSendField_2() {
        return BtnSetSendField_2;
    }

    /**
     * @return the BtnSetSendField_3
     */
    public javax.swing.JButton getBtnSetSendField_3() {
        return BtnSetSendField_3;
    }

    /**
     * @return the BtnSetSendField_4
     */
    public javax.swing.JButton getBtnSetSendField_4() {
        return BtnSetSendField_4;
    }

    /**
     * @return the BtnSetSendField_5
     */
    public javax.swing.JButton getBtnSetSendField_5() {
        return BtnSetSendField_5;
    }

    /**
     * @return the BtnSetSendField_6
     */
    public javax.swing.JButton getBtnSetSendField_6() {
        return BtnSetSendField_6;
    }

    /**
     * @return the btnErrorReset
     */
    public javax.swing.JButton getBtnErrorReset() {
        return btnErrorReset;
    }

    /**
     * @return the lblErrorCode
     */
    public javax.swing.JLabel getLblErrorCode() {
        return lblErrorCode;
    }

    /**
     * @return the lbl_rcv_fld_1
     */
    public javax.swing.JLabel getLbl_rcv_fld_1() {
        return lbl_rcv_fld_1;
    }

    /**
     * @return the lbl_rcv_fld_2
     */
    public javax.swing.JLabel getLbl_rcv_fld_2() {
        return lbl_rcv_fld_2;
    }

    /**
     * @return the lbl_rcv_fld_3
     */
    public javax.swing.JLabel getLbl_rcv_fld_3() {
        return lbl_rcv_fld_3;
    }

    /**
     * @return the lbl_rcv_fld_4
     */
    public javax.swing.JLabel getLbl_rcv_fld_4() {
        return lbl_rcv_fld_4;
    }

    /**
     * @return the lbl_rcv_fld_5
     */
    public javax.swing.JLabel getLbl_rcv_fld_5() {
        return lbl_rcv_fld_5;
    }

    /**
     * @return the lbl_rcv_fld_6
     */
    public javax.swing.JLabel getLbl_rcv_fld_6() {
        return lbl_rcv_fld_6;
    }

    /**
     * @return the txtControlEn
     */
    public javax.swing.JTextField getTxtControlEn() {
        return getTxtRunning();
    }

    /**
     * @return the txtErrorCode
     */
    public javax.swing.JTextField getTxtErrorCode() {
        return txtErrorCode;
    }
    
    /**
     * @return the txt_rcv_fld_1
     */
    public javax.swing.JTextField getTxt_rcv_fld_1() {
        return txt_rcv_fld_1;
    }

    /**
     * @return the txt_rcv_fld_2
     */
    public javax.swing.JTextField getTxt_rcv_fld_2() {
        return txt_rcv_fld_2;
    }

    /**
     * @return the txt_rcv_fld_3
     */
    public javax.swing.JTextField getTxt_rcv_fld_3() {
        return txt_rcv_fld_3;
    }

    /**
     * @return the txt_rcv_fld_4
     */
    public javax.swing.JTextField getTxt_rcv_fld_4() {
        return txt_rcv_fld_4;
    }

    /**
     * @return the txt_rcv_fld_5
     */
    public javax.swing.JTextField getTxt_rcv_fld_5() {
        return txt_rcv_fld_5;
    }

    /**
     * @return the txt_rcv_fld_6
     */
    public javax.swing.JTextField getTxt_rcv_fld_6() {
        return txt_rcv_fld_6;
    }

    /**
     * @return the txt_snd_fld_1
     */
    public javax.swing.JTextField getTxt_snd_fld_1() {
        return txt_snd_fld_1;
    }

    /**
     * @return the txt_snd_fld_2
     */
    public javax.swing.JTextField getTxt_snd_fld_2() {
        return txt_snd_fld_2;
    }

    /**
     * @return the txt_snd_fld_3
     */
    public javax.swing.JTextField getTxt_snd_fld_3() {
        return txt_snd_fld_3;
    }

    /**
     * @return the txt_snd_fld_4
     */
    public javax.swing.JTextField getTxt_snd_fld_4() {
        return txt_snd_fld_4;
    }

    /**
     * @return the txt_snd_fld_5
     */
    public javax.swing.JTextField getTxt_snd_fld_5() {
        return txt_snd_fld_5;
    }

    /**
     * @return the txt_snd_fld_6
     */
    public javax.swing.JTextField getTxt_snd_fld_6() {
        return txt_snd_fld_6;
    }

    /**
     * @return the btnStop
     */
    public javax.swing.JButton getBtnStop() {
        return btnStop;
    }

    /**
     * @return the field_1
     */
    public javax.swing.JPanel getField_1() {
        return field_1;
    }

    /**
     * @return the field_2
     */
    public javax.swing.JPanel getField_2() {
        return field_2;
    }

    /**
     * @return the field_3
     */
    public javax.swing.JPanel getField_3() {
        return field_3;
    }

    /**
     * @return the field_4
     */
    public javax.swing.JPanel getField_4() {
        return field_4;
    }

    /**
     * @return the field_5
     */
    public javax.swing.JPanel getField_5() {
        return field_5;
    }

    /**
     * @return the field_6
     */
    public javax.swing.JPanel getField_6() {
        return field_6;
    }

    /**
     * @return the receive_field_1
     */
    public javax.swing.JPanel getReceive_field_1() {
        return receive_field_1;
    }

    /**
     * @return the receive_field_2
     */
    public javax.swing.JPanel getReceive_field_2() {
        return receive_field_2;
    }

    /**
     * @return the receive_field_3
     */
    public javax.swing.JPanel getReceive_field_3() {
        return receive_field_3;
    }

    /**
     * @return the receive_field_4
     */
    public javax.swing.JPanel getReceive_field_4() {
        return receive_field_4;
    }

    /**
     * @return the receive_field_5
     */
    public javax.swing.JPanel getReceive_field_5() {
        return receive_field_5;
    }

    /**
     * @return the receive_field_6
     */
    public javax.swing.JPanel getReceive_field_6() {
        return receive_field_6;
    }

    /**
     * @return the lbl_snd_fld_1
     */
    public javax.swing.JLabel getLbl_snd_fld_1() {
        return lbl_snd_fld_1;
    }

    /**
     * @return the lbl_snd_fld_2
     */
    public javax.swing.JLabel getLbl_snd_fld_2() {
        return lbl_snd_fld_2;
    }

    /**
     * @return the lbl_snd_fld_3
     */
    public javax.swing.JLabel getLbl_snd_fld_3() {
        return lbl_snd_fld_3;
    }

    /**
     * @return the lbl_snd_fld_4
     */
    public javax.swing.JLabel getLbl_snd_fld_4() {
        return lbl_snd_fld_4;
    }

    /**
     * @return the lbl_snd_fld_5
     */
    public javax.swing.JLabel getLbl_snd_fld_5() {
        return lbl_snd_fld_5;
    }

    /**
     * @return the lbl_snd_fld_6
     */
    public javax.swing.JLabel getLbl_snd_fld_6() {
        return lbl_snd_fld_6;
    }

    /**
     * @return the btnEnControl
     */
    public javax.swing.JButton getBtnEnControl() {
        return btnEnControl;
    }

    /**
     * @return the btnEnSystem
     */
    public javax.swing.JButton getBtnEnSystem() {
        return btnEnSystem;
    }

    /**
     * @return the txtError
     */
    public javax.swing.JTextField getTxtError() {
        return txtError;
    }

    /**
     * @return the txtReady
     */
    public javax.swing.JTextField getTxtReady() {
        return txtReady;
    }

    /**
     * @return the txtRunning
     */
    public javax.swing.JTextField getTxtRunning() {
        return txtRunning;
    }

    /**
     * @return the txtUser
     */
    public javax.swing.JTextField getTxtUser() {
        return txtUser;
    }
    
    /**
     * @return the txtSystemEn
     */
    public javax.swing.JTextField getTxtSystemEn() {
        return getTxtReady();
    }
    
     /**
     * @return the BtnSetT_ref3
     */
    public javax.swing.JButton getBtnSetT_ref3() {
        return getBtnSetSendField_2();
    }

    /**
     * @return the BtnSetidref3
     */
    public javax.swing.JButton getBtnSetidref3() {
        return getBtnSetSendField_3();
    }

    /**
     * @return the BtnSetiqref3
     */
    public javax.swing.JButton getBtnSetiqref3() {
        return getBtnSetSendField_4();
    }

    /**
     * @return the BtnSetnref3
     */
    public javax.swing.JButton getBtnSetnref3() {
        return getBtnSetSendField_1();
    }

    /**
     * @return the btnErrorReset3
     */
    public javax.swing.JButton getBtnErrorReset3() {
        return getBtnErrorReset();
    }

    /**
     * @return the btnStop3
     */
    public javax.swing.JButton getBtnStop3() {
        return getBtnStop();
    }

    /**
     * @return the txtControlEn3
     */
    public javax.swing.JTextField getTxtControlEn3() {
        return getTxtControlEn();
    }

    /**
     * @return the txtErrorCode3
     */
    public javax.swing.JTextField getTxtErrorCode3() {
        return getTxtErrorCode();
    }

    /**
     * @return the txtInverterEn3
     */
    public javax.swing.JTextField getTxtInverterEn3() {
        return getTxtSystemEn();
    }

    /**
     * @return the txt_T_ref3
     */
    public javax.swing.JTextField getTxt_T_ref3() {
        return getTxt_snd_fld_2();
    }

    /**
     * @return the txt_current_d3
     */
    public javax.swing.JTextField getTxt_current_d3() {
        return getTxt_rcv_fld_3();
    }

    /**
     * @return the txt_current_q3
     */
    public javax.swing.JTextField getTxt_current_q3() {
        return getTxt_rcv_fld_4();
    }

    /**
     * @return the txt_idref3
     */
    public javax.swing.JTextField getTxt_idref3() {
        return getTxt_snd_fld_3();
    }

    /**
     * @return the txt_iqref3
     */
    public javax.swing.JTextField getTxt_iqref3() {
        return getTxt_snd_fld_4();
    }
    
    /**
     * @return the txt_n_ref3
     */
    public javax.swing.JTextField getTxt_n_ref3() {
        return getTxt_snd_fld_1();
    }

    /**
     * @return the txt_speed3
     */
    public javax.swing.JTextField getTxt_speed3() {
        return getTxt_rcv_fld_1();
    }

    /**
     * @return the txt_torque3
     */
    public javax.swing.JTextField getTxt_torque3() {
        return getTxt_rcv_fld_2();
    }

    /**
     * @return the txt_voltage_d3
     */
    public javax.swing.JTextField getTxt_voltage_d3() {
        return getTxt_rcv_fld_5();
    }

    /**
     * @return the txt_voltage_q3
     */
    public javax.swing.JTextField getTxt_voltage_q3() {
        return getTxt_rcv_fld_6();
    }
    
    /**
     * Creates new form UZ_SCOPE_view
     */
    public UZ_SCOPE_view() {
        initComponents();
        jTabbedPane1.addTab("ScopeDev", scopeDevPanel);
        jTabbedPane1.setSelectedComponent(Controlpanel);
        applySurfaceTheme();
        applyChannelLegendLayout();
        applyDisableAllChannelsButton();
        applyChannelSetupHeaderStyles();
        applyChannelComboSizing();
        applyChannelColumnSpacing();
        applyChannelValueFieldAlignment();
        applyControlPanelLayout();
    }

    public void setScopeDevTabVisible(boolean visible) {
        int tabIndex = jTabbedPane1.indexOfComponent(scopeDevPanel);
        if (visible && tabIndex < 0) {
            jTabbedPane1.addTab("ScopeDev", scopeDevPanel);
            return;
        }
        if (!visible && tabIndex >= 0) {
            jTabbedPane1.removeTabAt(tabIndex);
        }
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

        MotorControl = new javax.swing.JPanel();
        TabPanel = new javax.swing.JTabbedPane();
        GraphJFree = new javax.swing.JPanel();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        Hautpmenupanel = new javax.swing.JPanel();
        comboSelectData1 = new javax.swing.JComboBox<>();
        comboSelectData2 = new javax.swing.JComboBox<>();
        comboSelectData3 = new javax.swing.JComboBox<>();
        comboSelectData4 = new javax.swing.JComboBox<>();
        comboSelectData5 = new javax.swing.JComboBox<>();
        comboSelectData6 = new javax.swing.JComboBox<>();
        comboSelectData7 = new javax.swing.JComboBox<>();
        comboSelectData8 = new javax.swing.JComboBox<>();
        comboSelectData9 = new javax.swing.JComboBox<>();
        comboSelectData10 = new javax.swing.JComboBox<>();
        comboSelectData11 = new javax.swing.JComboBox<>();
        comboSelectData12 = new javax.swing.JComboBox<>();
        comboSelectData13 = new javax.swing.JComboBox<>();
        comboSelectData14 = new javax.swing.JComboBox<>();
        comboSelectData15 = new javax.swing.JComboBox<>();
        comboSelectData16 = new javax.swing.JComboBox<>();
        comboSelectData17 = new javax.swing.JComboBox<>();
        comboSelectData18 = new javax.swing.JComboBox<>();
        txtOffsetCH5 = new javax.swing.JTextField();
        txtScaleCH5 = new javax.swing.JTextField();
        txtOffsetCH6 = new javax.swing.JTextField();
        txtScaleCH6 = new javax.swing.JTextField();
        txtOffsetCH7 = new javax.swing.JTextField();
        txtScaleCH7 = new javax.swing.JTextField();
        txtOffsetCH8 = new javax.swing.JTextField();
        txtScaleCH8 = new javax.swing.JTextField();
        txtScaleCH9 = new javax.swing.JTextField();
        txtOffsetCH9 = new javax.swing.JTextField();
        txtScaleCH10 = new javax.swing.JTextField();
        txtOffsetCH10 = new javax.swing.JTextField();
        txtScaleCH11 = new javax.swing.JTextField();
        txtScaleCH12 = new javax.swing.JTextField();
        txtScaleCH13 = new javax.swing.JTextField();
        txtScaleCH14 = new javax.swing.JTextField();
        txtScaleCH15 = new javax.swing.JTextField();
        txtScaleCH16 = new javax.swing.JTextField();
        txtScaleCH17 = new javax.swing.JTextField();
        txtScaleCH18 = new javax.swing.JTextField();
        txtOffsetCH11 = new javax.swing.JTextField();
        txtOffsetCH12 = new javax.swing.JTextField();
        txtOffsetCH13 = new javax.swing.JTextField();
        txtOffsetCH14 = new javax.swing.JTextField();
        txtOffsetCH15 = new javax.swing.JTextField();
        txtOffsetCH16 = new javax.swing.JTextField();
        txtOffsetCH17 = new javax.swing.JTextField();
        txtOffsetCH18 = new javax.swing.JTextField();
        btnScalePlusCH4 = new javax.swing.JButton();
        btnScalePlusCH5 = new javax.swing.JButton();
        btnScalePlusCH6 = new javax.swing.JButton();
        btnScalePlusCH7 = new javax.swing.JButton();
        btnScalePlusCH8 = new javax.swing.JButton();
        btnScalePlusCH9 = new javax.swing.JButton();
        btnScalePlusCH10 = new javax.swing.JButton();
        btnScalePlusCH11 = new javax.swing.JButton();
        btnScalePlusCH12 = new javax.swing.JButton();
        btnScalePlusCH13 = new javax.swing.JButton();
        btnScalePlusCH14 = new javax.swing.JButton();
        btnScalePlusCH15 = new javax.swing.JButton();
        btnScalePlusCH16 = new javax.swing.JButton();
        btnScalePlusCH17 = new javax.swing.JButton();
        btnScaleMinusCH4 = new javax.swing.JButton();
        btnScaleMinusCH5 = new javax.swing.JButton();
        btnScaleMinusCH6 = new javax.swing.JButton();
        btnScaleMinusCH7 = new javax.swing.JButton();
        btnScaleMinusCH8 = new javax.swing.JButton();
        btnScaleMinusCH9 = new javax.swing.JButton();
        btnScaleMinusCH10 = new javax.swing.JButton();
        btnScaleMinusCH11 = new javax.swing.JButton();
        btnScaleMinusCH12 = new javax.swing.JButton();
        btnScaleMinusCH13 = new javax.swing.JButton();
        btnScaleMinusCH14 = new javax.swing.JButton();
        btnScaleMinusCH15 = new javax.swing.JButton();
        btnScaleMinusCH16 = new javax.swing.JButton();
        btnScaleMinusCH17 = new javax.swing.JButton();
        txtScaleCH2 = new javax.swing.JTextField();
        txtScaleCH3 = new javax.swing.JTextField();
        txtScaleCH4 = new javax.swing.JTextField();
        txtScaleCH20 = new javax.swing.JTextField();
        btnScalePlusCH20 = new javax.swing.JButton();
        btnScaleMinusCH20 = new javax.swing.JButton();
        txtOffsetCH20 = new javax.swing.JTextField();
        btnScalePlusCH19 = new javax.swing.JButton();
        txtScaleCH19 = new javax.swing.JTextField();
        btnScaleMinusCH19 = new javax.swing.JButton();
        txtOffsetCH19 = new javax.swing.JTextField();
        btnScalePlusCH2 = new javax.swing.JButton();
        btnScalePlusCH3 = new javax.swing.JButton();
        btnScalePlusCH18 = new javax.swing.JButton();
        btnScaleMinusCH2 = new javax.swing.JButton();
        btnScaleMinusCH3 = new javax.swing.JButton();
        btnScaleMinusCH18 = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        btnDisableAllChannels = new javax.swing.JButton();
        btnEnableAllChannels = new javax.swing.JButton();
        lblSlowData2 = new javax.swing.JLabel();
        jLabel13 = new javax.swing.JLabel();
        comboSelectData19 = new javax.swing.JComboBox<>();
        comboSelectData20 = new javax.swing.JComboBox<>();
        btnScaleMinusCH1 = new javax.swing.JButton();
        btnScalePlusCH1 = new javax.swing.JButton();
        txtScaleCH1 = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        jLabel12 = new javax.swing.JLabel();
        txtOffsetCH1 = new javax.swing.JTextField();
        txtOffsetCH2 = new javax.swing.JTextField();
        txtOffsetCH3 = new javax.swing.JTextField();
        txtOffsetCH4 = new javax.swing.JTextField();
        Controlpanel = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        tbSlowData3 = new javax.swing.JTable();
        receive_field_1 = new javax.swing.JPanel();
        txt_rcv_fld_1 = new javax.swing.JTextField();
        lbl_rcv_fld_1 = new javax.swing.JLabel();
        receive_field_2 = new javax.swing.JPanel();
        txt_rcv_fld_2 = new javax.swing.JTextField();
        lbl_rcv_fld_2 = new javax.swing.JLabel();
        receive_field_3 = new javax.swing.JPanel();
        txt_rcv_fld_3 = new javax.swing.JTextField();
        lbl_rcv_fld_3 = new javax.swing.JLabel();
        receive_field_4 = new javax.swing.JPanel();
        txt_rcv_fld_4 = new javax.swing.JTextField();
        lbl_rcv_fld_4 = new javax.swing.JLabel();
        receive_field_5 = new javax.swing.JPanel();
        txt_rcv_fld_5 = new javax.swing.JTextField();
        lbl_rcv_fld_5 = new javax.swing.JLabel();
        receive_field_6 = new javax.swing.JPanel();
        txt_rcv_fld_6 = new javax.swing.JTextField();
        lbl_rcv_fld_6 = new javax.swing.JLabel();
        field_1 = new javax.swing.JPanel();
        txt_snd_fld_1 = new javax.swing.JTextField();
        BtnSetSendField_1 = new javax.swing.JButton();
        lbl_snd_fld_1 = new javax.swing.JLabel();
        field_2 = new javax.swing.JPanel();
        txt_snd_fld_2 = new javax.swing.JTextField();
        BtnSetSendField_2 = new javax.swing.JButton();
        lbl_snd_fld_2 = new javax.swing.JLabel();
        field_3 = new javax.swing.JPanel();
        txt_snd_fld_3 = new javax.swing.JTextField();
        BtnSetSendField_3 = new javax.swing.JButton();
        lbl_snd_fld_3 = new javax.swing.JLabel();
        field_4 = new javax.swing.JPanel();
        txt_snd_fld_4 = new javax.swing.JTextField();
        BtnSetSendField_4 = new javax.swing.JButton();
        lbl_snd_fld_4 = new javax.swing.JLabel();
        jLabel11 = new javax.swing.JLabel();
        btnStop = new javax.swing.JButton();
        txtReady = new javax.swing.JTextField();
        txtRunning = new javax.swing.JTextField();
        btnErrorReset = new javax.swing.JButton();
        txtErrorCode = new javax.swing.JTextField();
        lblErrorCode = new javax.swing.JLabel();
        field_5 = new javax.swing.JPanel();
        txt_snd_fld_5 = new javax.swing.JTextField();
        BtnSetSendField_5 = new javax.swing.JButton();
        lbl_snd_fld_5 = new javax.swing.JLabel();
        field_6 = new javax.swing.JPanel();
        txt_snd_fld_6 = new javax.swing.JTextField();
        BtnSetSendField_6 = new javax.swing.JButton();
        lbl_snd_fld_6 = new javax.swing.JLabel();
        myButtons = new javax.swing.JPanel();
        myBtn_1 = new javax.swing.JButton();
        myBtn_2 = new javax.swing.JButton();
        myBtn_3 = new javax.swing.JButton();
        myBtn_4 = new javax.swing.JButton();
        myBtn_5 = new javax.swing.JButton();
        myBtn_6 = new javax.swing.JButton();
        myBtn_7 = new javax.swing.JButton();
        myBtn_8 = new javax.swing.JButton();
        txtBtn1 = new javax.swing.JTextField();
        txtBtn2 = new javax.swing.JTextField();
        txtBtn3 = new javax.swing.JTextField();
        txtBtn4 = new javax.swing.JTextField();
        txtBtn5 = new javax.swing.JTextField();
        txtBtn6 = new javax.swing.JTextField();
        txtBtn7 = new javax.swing.JTextField();
        txtBtn8 = new javax.swing.JTextField();
        btnEnControl = new javax.swing.JButton();
        btnEnSystem = new javax.swing.JButton();
        txtError = new javax.swing.JTextField();
        txtUser = new javax.swing.JTextField();
        SendReveivePanel = new javax.swing.JPanel();
        receive_field_7 = new javax.swing.JPanel();
        txt_rcv_fld_7 = new javax.swing.JTextField();
        lbl_rcv_fld_7 = new javax.swing.JLabel();
        receive_field_8 = new javax.swing.JPanel();
        txt_rcv_fld_8 = new javax.swing.JTextField();
        lbl_rcv_fld_8 = new javax.swing.JLabel();
        receive_field_9 = new javax.swing.JPanel();
        txt_rcv_fld_9 = new javax.swing.JTextField();
        lbl_rcv_fld_9 = new javax.swing.JLabel();
        receive_field_10 = new javax.swing.JPanel();
        txt_rcv_fld_10 = new javax.swing.JTextField();
        lbl_rcv_fld_10 = new javax.swing.JLabel();
        receive_field_11 = new javax.swing.JPanel();
        txt_rcv_fld_11 = new javax.swing.JTextField();
        lbl_rcv_fld_11 = new javax.swing.JLabel();
        receive_field_12 = new javax.swing.JPanel();
        txt_rcv_fld_12 = new javax.swing.JTextField();
        lbl_rcv_fld_12 = new javax.swing.JLabel();
        field_7 = new javax.swing.JPanel();
        txt_snd_fld_7 = new javax.swing.JTextField();
        BtnSetSendField_7 = new javax.swing.JButton();
        lbl_snd_fld_7 = new javax.swing.JLabel();
        field_8 = new javax.swing.JPanel();
        txt_snd_fld_8 = new javax.swing.JTextField();
        BtnSetSendField_8 = new javax.swing.JButton();
        lbl_snd_fld_8 = new javax.swing.JLabel();
        field_9 = new javax.swing.JPanel();
        txt_snd_fld_9 = new javax.swing.JTextField();
        BtnSetSendField_9 = new javax.swing.JButton();
        lbl_snd_fld_9 = new javax.swing.JLabel();
        field_10 = new javax.swing.JPanel();
        txt_snd_fld_10 = new javax.swing.JTextField();
        BtnSetSendField_10 = new javax.swing.JButton();
        lbl_snd_fld_10 = new javax.swing.JLabel();
        btnStop1 = new javax.swing.JButton();
        txtReady1 = new javax.swing.JTextField();
        txtRunning1 = new javax.swing.JTextField();
        field_11 = new javax.swing.JPanel();
        txt_snd_fld_11 = new javax.swing.JTextField();
        BtnSetSendField_11 = new javax.swing.JButton();
        lbl_snd_fld_11 = new javax.swing.JLabel();
        field_12 = new javax.swing.JPanel();
        txt_snd_fld_12 = new javax.swing.JTextField();
        BtnSetSendField_12 = new javax.swing.JButton();
        lbl_snd_fld_12 = new javax.swing.JLabel();
        btnEnControl1 = new javax.swing.JButton();
        btnEnSystem1 = new javax.swing.JButton();
        txtError1 = new javax.swing.JTextField();
        txtUser1 = new javax.swing.JTextField();
        receive_field_15 = new javax.swing.JPanel();
        txt_rcv_fld_15 = new javax.swing.JTextField();
        lbl_rcv_fld_15 = new javax.swing.JLabel();
        receive_field_13 = new javax.swing.JPanel();
        txt_rcv_fld_13 = new javax.swing.JTextField();
        lbl_rcv_fld_13 = new javax.swing.JLabel();
        receive_field_14 = new javax.swing.JPanel();
        txt_rcv_fld_14 = new javax.swing.JTextField();
        lbl_rcv_fld_14 = new javax.swing.JLabel();
        receive_field_16 = new javax.swing.JPanel();
        txt_rcv_fld_16 = new javax.swing.JTextField();
        lbl_rcv_fld_16 = new javax.swing.JLabel();
        receive_field_17 = new javax.swing.JPanel();
        txt_rcv_fld_17 = new javax.swing.JTextField();
        lbl_rcv_fld_17 = new javax.swing.JLabel();
        receive_field_18 = new javax.swing.JPanel();
        txt_rcv_fld_18 = new javax.swing.JTextField();
        lbl_rcv_fld_18 = new javax.swing.JLabel();
        field_13 = new javax.swing.JPanel();
        txt_snd_fld_13 = new javax.swing.JTextField();
        BtnSetSendField_13 = new javax.swing.JButton();
        lbl_snd_fld_13 = new javax.swing.JLabel();
        field_14 = new javax.swing.JPanel();
        txt_snd_fld_14 = new javax.swing.JTextField();
        BtnSetSendField_14 = new javax.swing.JButton();
        lbl_snd_fld_14 = new javax.swing.JLabel();
        field_15 = new javax.swing.JPanel();
        txt_snd_fld_15 = new javax.swing.JTextField();
        BtnSetSendField_15 = new javax.swing.JButton();
        lbl_snd_fld_15 = new javax.swing.JLabel();
        field_16 = new javax.swing.JPanel();
        txt_snd_fld_16 = new javax.swing.JTextField();
        BtnSetSendField_16 = new javax.swing.JButton();
        lbl_snd_fld_16 = new javax.swing.JLabel();
        field_17 = new javax.swing.JPanel();
        txt_snd_fld_17 = new javax.swing.JTextField();
        BtnSetSendField_17 = new javax.swing.JButton();
        lbl_snd_fld_17 = new javax.swing.JLabel();
        field_18 = new javax.swing.JPanel();
        txt_snd_fld_18 = new javax.swing.JTextField();
        BtnSetSendField_18 = new javax.swing.JButton();
        lbl_snd_fld_18 = new javax.swing.JLabel();
        receive_field_19 = new javax.swing.JPanel();
        txt_rcv_fld_19 = new javax.swing.JTextField();
        lbl_rcv_fld_19 = new javax.swing.JLabel();
        receive_field_20 = new javax.swing.JPanel();
        txt_rcv_fld_20 = new javax.swing.JTextField();
        lbl_rcv_fld_20 = new javax.swing.JLabel();
        field_19 = new javax.swing.JPanel();
        txt_snd_fld_19 = new javax.swing.JTextField();
        BtnSetSendField_19 = new javax.swing.JButton();
        lbl_snd_fld_19 = new javax.swing.JLabel();
        field_20 = new javax.swing.JPanel();
        txt_snd_fld_20 = new javax.swing.JTextField();
        BtnSetSendField_20 = new javax.swing.JButton();
        lbl_snd_fld_20 = new javax.swing.JLabel();

        setPreferredSize(new java.awt.Dimension(1600, 800));

        MotorControl.setLayout(new java.awt.BorderLayout());

        GraphJFree.setLayout(new java.awt.CardLayout());
        TabPanel.addTab("JavaScope", GraphJFree);

        MotorControl.add(TabPanel, java.awt.BorderLayout.CENTER);

        jTabbedPane1.setMaximumSize(new java.awt.Dimension(700, 198));
        jTabbedPane1.setMinimumSize(new java.awt.Dimension(700, 198));
        jTabbedPane1.setPreferredSize(new java.awt.Dimension(590, 198));

        Hautpmenupanel.setLayout(new java.awt.GridBagLayout());

        comboSelectData1.setPreferredSize(new java.awt.Dimension(176, 25));
        comboSelectData1.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData1.setMaximumSize(new java.awt.Dimension(176, 25));
        comboSelectData1.setMinimumSize(new java.awt.Dimension(176, 25));
        comboSelectData1.setName(""); // NOI18N
        comboSelectData1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData1, gridBagConstraints);

        comboSelectData2.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData2.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData2.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData2.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData2, gridBagConstraints);

        comboSelectData3.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData3.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData3.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData3.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData3, gridBagConstraints);

        comboSelectData4.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData4.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData4.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData4.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData4, gridBagConstraints);

        comboSelectData5.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData5.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData5.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData5.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData5, gridBagConstraints);

        comboSelectData6.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData6.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData6.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData6.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData6, gridBagConstraints);

        comboSelectData7.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData7.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData7.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData7.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData7, gridBagConstraints);

        comboSelectData8.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData8.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData8.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData8.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData8, gridBagConstraints);

        comboSelectData9.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData9.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData9.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData9.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData9ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData9, gridBagConstraints);

        comboSelectData10.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData10.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData10.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData10.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData10ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData10, gridBagConstraints);

        comboSelectData11.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData11.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData11.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData11.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData11, gridBagConstraints);

        comboSelectData12.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData12.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData12.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData12.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData12, gridBagConstraints);

        comboSelectData13.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData13.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData13.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData13.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData13, gridBagConstraints);

        comboSelectData14.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData14.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData14.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData14.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData14ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData14, gridBagConstraints);

        comboSelectData15.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData15.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData15.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData15.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData15, gridBagConstraints);

        comboSelectData16.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData16.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData16.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData16.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData16, gridBagConstraints);

        comboSelectData17.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData17.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData17.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData17.setMinimumSize(comboSelectData1.getMinimumSize());
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 19;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData17, gridBagConstraints);

        comboSelectData18.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData18.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData18.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData18.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData18.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData18ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 20;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData18, gridBagConstraints);

        txtOffsetCH5.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH5.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH5, gridBagConstraints);

        txtScaleCH5.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH5.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH5, gridBagConstraints);

        txtOffsetCH6.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH6.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH6, gridBagConstraints);

        txtScaleCH6.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH6.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH6, gridBagConstraints);

        txtOffsetCH7.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH7.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH7, gridBagConstraints);

        txtScaleCH7.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH7.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH7, gridBagConstraints);

        txtOffsetCH8.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH8.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH8, gridBagConstraints);

        txtScaleCH8.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH8.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH8, gridBagConstraints);

        txtScaleCH9.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH9.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH9, gridBagConstraints);

        txtOffsetCH9.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH9.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH9, gridBagConstraints);

        txtScaleCH10.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH10.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH10, gridBagConstraints);

        txtOffsetCH10.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH10.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH10, gridBagConstraints);

        txtScaleCH11.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH11.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH11, gridBagConstraints);

        txtScaleCH12.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH12.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH12, gridBagConstraints);

        txtScaleCH13.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH13.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH13ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH13, gridBagConstraints);

        txtScaleCH14.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH14.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH14, gridBagConstraints);

        txtScaleCH15.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH15.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH15, gridBagConstraints);

        txtScaleCH16.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH16.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH16, gridBagConstraints);

        txtScaleCH17.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH17.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 19;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH17, gridBagConstraints);

        txtScaleCH18.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH18.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 20;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH18, gridBagConstraints);

        txtOffsetCH11.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH11.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH11, gridBagConstraints);

        txtOffsetCH12.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH12.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH12, gridBagConstraints);

        txtOffsetCH13.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH13.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH13, gridBagConstraints);

        txtOffsetCH14.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH14.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH14ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH14, gridBagConstraints);

        txtOffsetCH15.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH15.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH15, gridBagConstraints);

        txtOffsetCH16.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH16.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH16, gridBagConstraints);

        txtOffsetCH17.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH17.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 19;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH17, gridBagConstraints);

        txtOffsetCH18.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH18.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 20;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH18, gridBagConstraints);

        btnScalePlusCH4.setText("+");
        btnScalePlusCH4.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH4, gridBagConstraints);

        btnScalePlusCH5.setText("+");
        btnScalePlusCH5.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH5, gridBagConstraints);

        btnScalePlusCH6.setText("+");
        btnScalePlusCH6.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH6, gridBagConstraints);

        btnScalePlusCH7.setText("+");
        btnScalePlusCH7.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH7, gridBagConstraints);

        btnScalePlusCH8.setText("+");
        btnScalePlusCH8.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH8, gridBagConstraints);

        btnScalePlusCH9.setText("+");
        btnScalePlusCH9.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH9, gridBagConstraints);

        btnScalePlusCH10.setText("+");
        btnScalePlusCH10.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH10, gridBagConstraints);

        btnScalePlusCH11.setText("+");
        btnScalePlusCH11.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH11, gridBagConstraints);

        btnScalePlusCH12.setText("+");
        btnScalePlusCH12.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH12, gridBagConstraints);

        btnScalePlusCH13.setText("+");
        btnScalePlusCH13.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH13, gridBagConstraints);

        btnScalePlusCH14.setText("+");
        btnScalePlusCH14.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH14, gridBagConstraints);

        btnScalePlusCH15.setText("+");
        btnScalePlusCH15.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH15, gridBagConstraints);

        btnScalePlusCH16.setText("+");
        btnScalePlusCH16.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH16, gridBagConstraints);

        btnScalePlusCH17.setText("+");
        btnScalePlusCH17.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 19;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH17, gridBagConstraints);

        btnScaleMinusCH4.setText("-");
        btnScaleMinusCH4.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH4, gridBagConstraints);

        btnScaleMinusCH5.setText("-");
        btnScaleMinusCH5.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH5, gridBagConstraints);

        btnScaleMinusCH6.setText("-");
        btnScaleMinusCH6.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH6, gridBagConstraints);

        btnScaleMinusCH7.setText("-");
        btnScaleMinusCH7.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH7, gridBagConstraints);

        btnScaleMinusCH8.setText("-");
        btnScaleMinusCH8.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH8, gridBagConstraints);

        btnScaleMinusCH9.setText("-");
        btnScaleMinusCH9.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH9, gridBagConstraints);

        btnScaleMinusCH10.setText("-");
        btnScaleMinusCH10.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH10, gridBagConstraints);

        btnScaleMinusCH11.setText("-");
        btnScaleMinusCH11.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH11, gridBagConstraints);

        btnScaleMinusCH12.setText("-");
        btnScaleMinusCH12.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH12, gridBagConstraints);

        btnScaleMinusCH13.setText("-");
        btnScaleMinusCH13.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH13, gridBagConstraints);

        btnScaleMinusCH14.setText("-");
        btnScaleMinusCH14.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH14, gridBagConstraints);

        btnScaleMinusCH15.setText("-");
        btnScaleMinusCH15.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH15, gridBagConstraints);

        btnScaleMinusCH16.setText("-");
        btnScaleMinusCH16.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH16, gridBagConstraints);

        btnScaleMinusCH17.setText("-");
        btnScaleMinusCH17.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 19;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH17, gridBagConstraints);































        txtScaleCH2.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH2.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH2, gridBagConstraints);

        txtScaleCH3.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH3.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH3, gridBagConstraints);

        txtScaleCH4.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH4.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH4, gridBagConstraints);





        txtScaleCH20.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH20.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 22;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH20, gridBagConstraints);

        btnScalePlusCH20.setText("+");
        btnScalePlusCH20.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 22;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH20, gridBagConstraints);

        btnScaleMinusCH20.setText("-");
        btnScaleMinusCH20.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 22;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH20, gridBagConstraints);


        txtOffsetCH20.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH20.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 22;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH20, gridBagConstraints);


        btnScalePlusCH19.setText("+");
        btnScalePlusCH19.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 21;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH19, gridBagConstraints);

        txtScaleCH19.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH19.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 21;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH19, gridBagConstraints);

        btnScaleMinusCH19.setText("-");
        btnScaleMinusCH19.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 21;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH19, gridBagConstraints);


        txtOffsetCH19.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH19.setPreferredSize(new java.awt.Dimension(57, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 21;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH19, gridBagConstraints);




        btnScalePlusCH2.setText("+");
        btnScalePlusCH2.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH2, gridBagConstraints);

        btnScalePlusCH3.setText("+");
        btnScalePlusCH3.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH3, gridBagConstraints);

        btnScalePlusCH18.setText("+");
        btnScalePlusCH18.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 20;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH18, gridBagConstraints);

        btnScaleMinusCH2.setText("-");
        btnScaleMinusCH2.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH2, gridBagConstraints);

        btnScaleMinusCH3.setText("-");
        btnScaleMinusCH3.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH3, gridBagConstraints);

        btnScaleMinusCH18.setText("-");
        btnScaleMinusCH18.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 20;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH18, gridBagConstraints);

        jPanel1.setOpaque(false);
        jPanel1.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 8, 0));

        btnDisableAllChannels.setText("Disable All");
        btnDisableAllChannels.setMargin(new java.awt.Insets(2, 10, 2, 10));
        jPanel1.add(btnDisableAllChannels);

        btnEnableAllChannels.setText("Enable All");
        btnEnableAllChannels.setMargin(new java.awt.Insets(2, 10, 2, 10));
        jPanel1.add(btnEnableAllChannels);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 23;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(6, 0, 0, 8);
        Hautpmenupanel.add(jPanel1, gridBagConstraints);


        lblSlowData2.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        lblSlowData2.setText("Scope Channel Setup");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 14;
        Hautpmenupanel.add(lblSlowData2, gridBagConstraints);

        jLabel13.setFont(new java.awt.Font("Tahoma", 1, 12)); // NOI18N
        jLabel13.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel13.setText("Signal");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        Hautpmenupanel.add(jLabel13, gridBagConstraints);

        comboSelectData19.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData19.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData19.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData19.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData19.setName(""); // NOI18N
        comboSelectData19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData19ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 21;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData19, gridBagConstraints);

        comboSelectData20.setPreferredSize(comboSelectData1.getPreferredSize());
        comboSelectData20.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "ZEROVALUE", "SineWave1", "Sawtooth1", "SineWave2", "Sawtooth2" }));
        comboSelectData20.setMaximumSize(comboSelectData1.getMaximumSize());
        comboSelectData20.setMinimumSize(comboSelectData1.getMinimumSize());
        comboSelectData20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                comboSelectData20ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 22;
        gridBagConstraints.gridwidth = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(comboSelectData20, gridBagConstraints);


        btnScaleMinusCH1.setText("-");
        btnScaleMinusCH1.setMargin(new java.awt.Insets(2, 2, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScaleMinusCH1, gridBagConstraints);

        btnScalePlusCH1.setText("+");
        btnScalePlusCH1.setMargin(new java.awt.Insets(2, 0, 2, 0));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 0);
        Hautpmenupanel.add(btnScalePlusCH1, gridBagConstraints);

        txtScaleCH1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtScaleCH1.setPreferredSize(new java.awt.Dimension(57, 20));
        txtScaleCH1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtScaleCH1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 0);
        Hautpmenupanel.add(txtScaleCH1, gridBagConstraints);


        jLabel9.setFont(new java.awt.Font("Tahoma", 1, 12)); // NOI18N
        jLabel9.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel9.setText("Scaling");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        Hautpmenupanel.add(jLabel9, gridBagConstraints);

        jLabel12.setFont(new java.awt.Font("Tahoma", 1, 12)); // NOI18N
        jLabel12.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel12.setText("Offset");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
        Hautpmenupanel.add(jLabel12, gridBagConstraints);

        txtOffsetCH1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH1.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH1, gridBagConstraints);

        txtOffsetCH2.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH2.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH2, gridBagConstraints);

        txtOffsetCH3.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH3.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH3, gridBagConstraints);

        txtOffsetCH4.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtOffsetCH4.setPreferredSize(new java.awt.Dimension(57, 20));
        txtOffsetCH4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtOffsetCH4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 9;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.insets = new java.awt.Insets(0, 10, 5, 12);
        Hautpmenupanel.add(txtOffsetCH4, gridBagConstraints);

        jTabbedPane1.addTab("Setup Scope", Hautpmenupanel);

        Controlpanel.setLayout(new java.awt.GridBagLayout());

        jScrollPane2.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        jScrollPane2.setPreferredSize(new java.awt.Dimension(500, 180));

        tbSlowData3.setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_LAST_COLUMN);
        tbSlowData3.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null},
                {null, null, null}
            },
            new String [] {
                "id", "variable", "value"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        tbSlowData3.setPreferredSize(new java.awt.Dimension(500, 1400));
        tbSlowData3.setRowHeight(18);
        jScrollPane2.setViewportView(tbSlowData3);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 6;
        gridBagConstraints.gridheight = 12;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.insets = new java.awt.Insets(5, 2, 5, 5);
        Controlpanel.add(jScrollPane2, gridBagConstraints);

        receive_field_1.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_1"));
        receive_field_1.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_1.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_1.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_1.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_1.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_1.setText("0.00");
        txt_rcv_fld_1.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_1.setEnabled(false);
        txt_rcv_fld_1.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_1.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_1.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_1.add(txt_rcv_fld_1, gridBagConstraints);

        lbl_rcv_fld_1.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_1.setText("RPM");
        receive_field_1.add(lbl_rcv_fld_1, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_1, gridBagConstraints);

        receive_field_2.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_2"));
        receive_field_2.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_2.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_2.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_2.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_2.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_2.setText("0.00");
        txt_rcv_fld_2.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_2.setEnabled(false);
        txt_rcv_fld_2.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_2.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_2.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_2.add(txt_rcv_fld_2, gridBagConstraints);

        lbl_rcv_fld_2.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_2.setText("Nm");
        receive_field_2.add(lbl_rcv_fld_2, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_2, gridBagConstraints);

        receive_field_3.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_3"));
        receive_field_3.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_3.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_3.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_3.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_3.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_3.setText("0.00");
        txt_rcv_fld_3.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_3.setEnabled(false);
        txt_rcv_fld_3.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_3.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_3.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_3.add(txt_rcv_fld_3, gridBagConstraints);

        lbl_rcv_fld_3.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_3.setText("A");
        receive_field_3.add(lbl_rcv_fld_3, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_3, gridBagConstraints);

        receive_field_4.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_4"));
        receive_field_4.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_4.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_4.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_4.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_4.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_4.setText("0.00");
        txt_rcv_fld_4.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_4.setEnabled(false);
        txt_rcv_fld_4.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_4.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_4.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_4.add(txt_rcv_fld_4, gridBagConstraints);

        lbl_rcv_fld_4.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_4.setText("A");
        receive_field_4.add(lbl_rcv_fld_4, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_4, gridBagConstraints);

        receive_field_5.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_5"));
        receive_field_5.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_5.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_5.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_5.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_5.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_5.setText("0.00");
        txt_rcv_fld_5.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_5.setEnabled(false);
        txt_rcv_fld_5.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_5.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_5.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_5.add(txt_rcv_fld_5, gridBagConstraints);

        lbl_rcv_fld_5.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_5.setText("V");
        receive_field_5.add(lbl_rcv_fld_5, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_5, gridBagConstraints);

        receive_field_6.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_6"));
        receive_field_6.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_6.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_6.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_6.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_6.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_6.setText("0.00");
        txt_rcv_fld_6.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_6.setEnabled(false);
        txt_rcv_fld_6.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_6.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_6.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_6.add(txt_rcv_fld_6, gridBagConstraints);

        lbl_rcv_fld_6.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_6.setText("V");
        receive_field_6.add(lbl_rcv_fld_6, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(3, 8, 3, 8);
        Controlpanel.add(receive_field_6, gridBagConstraints);

        field_1.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_1"));
        field_1.setMinimumSize(new java.awt.Dimension(200, 40));
        field_1.setPreferredSize(new java.awt.Dimension(200, 40));
        field_1.setRequestFocusEnabled(false);
        field_1.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_1.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_1.setText("0");
        txt_snd_fld_1.setEnabled(false);
        txt_snd_fld_1.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_1.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_1.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_1.add(txt_snd_fld_1, gridBagConstraints);

        BtnSetSendField_1.setText("set");
        BtnSetSendField_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_1.add(BtnSetSendField_1, gridBagConstraints);

        lbl_snd_fld_1.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_1.setText("RPM");
        field_1.add(lbl_snd_fld_1, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_1, gridBagConstraints);

        field_2.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_2"));
        field_2.setMinimumSize(new java.awt.Dimension(200, 40));
        field_2.setPreferredSize(new java.awt.Dimension(200, 40));
        field_2.setRequestFocusEnabled(false);
        field_2.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_2.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_2.setText("0");
        txt_snd_fld_2.setEnabled(false);
        txt_snd_fld_2.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_2.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_2.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_2.add(txt_snd_fld_2, gridBagConstraints);

        BtnSetSendField_2.setText("set");
        BtnSetSendField_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_2.add(BtnSetSendField_2, gridBagConstraints);

        lbl_snd_fld_2.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_2.setText("Nm");
        field_2.add(lbl_snd_fld_2, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_2, gridBagConstraints);

        field_3.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_3"));
        field_3.setMinimumSize(new java.awt.Dimension(200, 40));
        field_3.setPreferredSize(new java.awt.Dimension(200, 40));
        field_3.setRequestFocusEnabled(false);
        field_3.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_3.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_3.setText("0");
        txt_snd_fld_3.setEnabled(false);
        txt_snd_fld_3.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_3.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_3.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_3.add(txt_snd_fld_3, gridBagConstraints);

        BtnSetSendField_3.setText("set");
        BtnSetSendField_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_3.add(BtnSetSendField_3, gridBagConstraints);

        lbl_snd_fld_3.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_3.setText("A");
        field_3.add(lbl_snd_fld_3, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_3, gridBagConstraints);

        field_4.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_4"));
        field_4.setMinimumSize(new java.awt.Dimension(200, 40));
        field_4.setPreferredSize(new java.awt.Dimension(200, 40));
        field_4.setRequestFocusEnabled(false);
        field_4.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_4.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_4.setText("0");
        txt_snd_fld_4.setEnabled(false);
        txt_snd_fld_4.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_4.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_4.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_4.add(txt_snd_fld_4, gridBagConstraints);

        BtnSetSendField_4.setText("set");
        BtnSetSendField_4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_4.add(BtnSetSendField_4, gridBagConstraints);

        lbl_snd_fld_4.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_4.setText("A");
        field_4.add(lbl_snd_fld_4, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_4, gridBagConstraints);

        jLabel11.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel11.setText("SlowData");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.gridwidth = 6;
        Controlpanel.add(jLabel11, gridBagConstraints);

        btnStop.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
        btnStop.setForeground(new java.awt.Color(255, 0, 0));
        btnStop.setText("STOP");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridheight = 3;
        gridBagConstraints.ipadx = 5;
        gridBagConstraints.ipady = 5;
        Controlpanel.add(btnStop, gridBagConstraints);

        txtReady.setForeground(new java.awt.Color(51, 51, 51));
        txtReady.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtReady.setText("Ready");
        txtReady.setToolTipText("");
        txtReady.setEnabled(false);
        txtReady.setMaximumSize(new java.awt.Dimension(75, 22));
        txtReady.setMinimumSize(new java.awt.Dimension(75, 22));
        txtReady.setPreferredSize(new java.awt.Dimension(75, 22));
        txtReady.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtReadyActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        Controlpanel.add(txtReady, gridBagConstraints);

        txtRunning.setForeground(new java.awt.Color(51, 51, 51));
        txtRunning.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtRunning.setText("Running");
        txtRunning.setToolTipText("");
        txtRunning.setEnabled(false);
        txtRunning.setMaximumSize(new java.awt.Dimension(75, 22));
        txtRunning.setMinimumSize(new java.awt.Dimension(75, 22));
        txtRunning.setPreferredSize(new java.awt.Dimension(75, 22));
        txtRunning.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtRunningActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        Controlpanel.add(txtRunning, gridBagConstraints);

        btnErrorReset.setText("Error Reset");
        btnErrorReset.setEnabled(false);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        Controlpanel.add(btnErrorReset, gridBagConstraints);

        txtErrorCode.setEditable(false);
        txtErrorCode.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        txtErrorCode.setForeground(new java.awt.Color(180, 180, 180));
        txtErrorCode.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtErrorCode.setText("ERR N/A");
        txtErrorCode.setMaximumSize(new java.awt.Dimension(160, 20));
        txtErrorCode.setMinimumSize(new java.awt.Dimension(160, 20));
        txtErrorCode.setPreferredSize(new java.awt.Dimension(160, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 4, 0);
        Controlpanel.add(txtErrorCode, gridBagConstraints);

        lblErrorCode.setText("error code");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        Controlpanel.add(lblErrorCode, gridBagConstraints);

        field_5.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_5"));
        field_5.setMinimumSize(new java.awt.Dimension(200, 40));
        field_5.setPreferredSize(new java.awt.Dimension(200, 40));
        field_5.setRequestFocusEnabled(false);
        field_5.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_5.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_5.setText("0");
        txt_snd_fld_5.setEnabled(false);
        txt_snd_fld_5.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_5.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_5.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_5.add(txt_snd_fld_5, gridBagConstraints);

        BtnSetSendField_5.setText("set");
        BtnSetSendField_5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_5.add(BtnSetSendField_5, gridBagConstraints);

        lbl_snd_fld_5.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_5.setText("A");
        field_5.add(lbl_snd_fld_5, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_5, gridBagConstraints);

        field_6.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_6"));
        field_6.setMinimumSize(new java.awt.Dimension(200, 40));
        field_6.setPreferredSize(new java.awt.Dimension(200, 40));
        field_6.setRequestFocusEnabled(false);
        field_6.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_6.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_6.setText("0");
        txt_snd_fld_6.setEnabled(false);
        txt_snd_fld_6.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_6.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_6.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_6.add(txt_snd_fld_6, gridBagConstraints);

        BtnSetSendField_6.setText("set");
        BtnSetSendField_6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_6.add(BtnSetSendField_6, gridBagConstraints);

        lbl_snd_fld_6.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_6.setText("A");
        field_6.add(lbl_snd_fld_6, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 5, 2, 5);
        Controlpanel.add(field_6, gridBagConstraints);

        myButtons.setBorder(javax.swing.BorderFactory.createTitledBorder("my buttons"));
        myButtons.setMinimumSize(new java.awt.Dimension(220, 250));
        myButtons.setName(""); // NOI18N
        myButtons.setPreferredSize(new java.awt.Dimension(220, 70));
        myButtons.setRequestFocusEnabled(false);
        myButtons.setLayout(new java.awt.GridBagLayout());

        myBtn_1.setText("MyButton1");
        myBtn_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        myButtons.add(myBtn_1, gridBagConstraints);

        myBtn_2.setText("MyButton2");
        myBtn_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        myButtons.add(myBtn_2, gridBagConstraints);

        myBtn_3.setText("MyButton3");
        myBtn_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        myButtons.add(myBtn_3, gridBagConstraints);

        myBtn_4.setText("MyButton4");
        myBtn_4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        myButtons.add(myBtn_4, gridBagConstraints);

        myBtn_5.setText("MyButton5");
        myBtn_5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        myButtons.add(myBtn_5, gridBagConstraints);

        myBtn_6.setText("MyButton6");
        myBtn_6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        myButtons.add(myBtn_6, gridBagConstraints);

        myBtn_7.setText("MyButton7");
        myBtn_7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        myButtons.add(myBtn_7, gridBagConstraints);

        myBtn_8.setText("MyButton8");
        myBtn_8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                myBtn_8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 7;
        myButtons.add(myBtn_8, gridBagConstraints);

        txtBtn1.setForeground(txtBtn1.getBackground());
        txtBtn1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn1.setText("ACT");
        txtBtn1.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn1.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        myButtons.add(txtBtn1, gridBagConstraints);

        txtBtn2.setForeground(txtBtn2.getBackground());
        txtBtn2.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn2.setText("ACT");
        txtBtn2.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn2.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn2ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        myButtons.add(txtBtn2, gridBagConstraints);

        txtBtn3.setForeground(txtBtn3.getBackground());
        txtBtn3.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn3.setText("ACT");
        txtBtn3.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn3.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn3ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 2;
        myButtons.add(txtBtn3, gridBagConstraints);

        txtBtn4.setForeground(txtBtn4.getBackground());
        txtBtn4.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn4.setText("ACT");
        txtBtn4.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn4.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn4ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 3;
        myButtons.add(txtBtn4, gridBagConstraints);

        txtBtn5.setForeground(txtBtn5.getBackground());
        txtBtn5.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn5.setText("ACT");
        txtBtn5.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn5.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn5ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 4;
        myButtons.add(txtBtn5, gridBagConstraints);

        txtBtn6.setForeground(txtBtn6.getBackground());
        txtBtn6.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn6.setText("ACT");
        txtBtn6.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn6.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn6ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 5;
        myButtons.add(txtBtn6, gridBagConstraints);

        txtBtn7.setForeground(txtBtn7.getBackground());
        txtBtn7.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn7.setText("ACT");
        txtBtn7.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn7.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 6;
        myButtons.add(txtBtn7, gridBagConstraints);

        txtBtn8.setForeground(txtBtn8.getBackground());
        txtBtn8.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtBtn8.setText("ACT");
        txtBtn8.setMinimumSize(new java.awt.Dimension(35, 25));
        txtBtn8.setPreferredSize(new java.awt.Dimension(45, 25));
        txtBtn8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtBtn8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 7;
        myButtons.add(txtBtn8, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        Controlpanel.add(myButtons, gridBagConstraints);

        btnEnControl.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnControl.setForeground(new java.awt.Color(255, 0, 0));
        btnEnControl.setText("Enable Control");
        btnEnControl.setMaximumSize(new java.awt.Dimension(160, 35));
        btnEnControl.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnControl.setPreferredSize(new java.awt.Dimension(160, 35));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 3;
        Controlpanel.add(btnEnControl, gridBagConstraints);

        btnEnSystem.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnSystem.setForeground(new java.awt.Color(255, 0, 0));
        btnEnSystem.setText("Enable System");
        btnEnSystem.setMaximumSize(new java.awt.Dimension(160, 35));
        btnEnSystem.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnSystem.setPreferredSize(new java.awt.Dimension(160, 35));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 3;
        Controlpanel.add(btnEnSystem, gridBagConstraints);

        txtError.setForeground(new java.awt.Color(51, 51, 51));
        txtError.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtError.setText("Error");
        txtError.setToolTipText("");
        txtError.setEnabled(false);
        txtError.setMinimumSize(new java.awt.Dimension(75, 22));
        txtError.setPreferredSize(new java.awt.Dimension(70, 22));
        txtError.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtErrorActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        Controlpanel.add(txtError, gridBagConstraints);

        txtUser.setForeground(new java.awt.Color(51, 51, 51));
        txtUser.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtUser.setText("User");
        txtUser.setToolTipText("");
        txtUser.setEnabled(false);
        txtUser.setMaximumSize(new java.awt.Dimension(75, 22));
        txtUser.setMinimumSize(new java.awt.Dimension(75, 22));
        txtUser.setPreferredSize(new java.awt.Dimension(75, 22));
        txtUser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtUserActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        Controlpanel.add(txtUser, gridBagConstraints);

        jTabbedPane1.addTab("Control", Controlpanel);

        SendReveivePanel.setLayout(new java.awt.GridBagLayout());

        receive_field_7.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_7"));
        receive_field_7.setToolTipText("");
        receive_field_7.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_7.setName(""); // NOI18N
        receive_field_7.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_7.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_7.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_7.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_7.setText("0.00");
        txt_rcv_fld_7.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_7.setEnabled(false);
        txt_rcv_fld_7.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_7.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_7.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_7.add(txt_rcv_fld_7, gridBagConstraints);

        lbl_rcv_fld_7.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_7.setText("-");
        receive_field_7.add(lbl_rcv_fld_7, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_7, gridBagConstraints);

        receive_field_8.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_8"));
        receive_field_8.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_8.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_8.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_8.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_8.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_8.setText("0.00");
        txt_rcv_fld_8.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_8.setEnabled(false);
        txt_rcv_fld_8.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_8.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_8.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_8.add(txt_rcv_fld_8, gridBagConstraints);

        lbl_rcv_fld_8.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_8.setText("-");
        receive_field_8.add(lbl_rcv_fld_8, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_8, gridBagConstraints);

        receive_field_9.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_9"));
        receive_field_9.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_9.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_9.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_9.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_9.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_9.setText("0.00");
        txt_rcv_fld_9.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_9.setEnabled(false);
        txt_rcv_fld_9.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_9.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_9.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_9ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_9.add(txt_rcv_fld_9, gridBagConstraints);

        lbl_rcv_fld_9.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_9.setText("-");
        receive_field_9.add(lbl_rcv_fld_9, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_9, gridBagConstraints);

        receive_field_10.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_10"));
        receive_field_10.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_10.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_10.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_10.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_10.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_10.setText("0.00");
        txt_rcv_fld_10.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_10.setEnabled(false);
        txt_rcv_fld_10.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_10.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_10.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_10ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_10.add(txt_rcv_fld_10, gridBagConstraints);

        lbl_rcv_fld_10.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_10.setText("-");
        receive_field_10.add(lbl_rcv_fld_10, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_10, gridBagConstraints);
        receive_field_10.getAccessibleContext().setAccessibleDescription("");

        receive_field_11.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_11"));
        receive_field_11.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_11.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_11.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_11.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_11.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_11.setText("0.00");
        txt_rcv_fld_11.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_11.setEnabled(false);
        txt_rcv_fld_11.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_11.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_11.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_11ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_11.add(txt_rcv_fld_11, gridBagConstraints);

        lbl_rcv_fld_11.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_11.setText("-");
        receive_field_11.add(lbl_rcv_fld_11, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_11, gridBagConstraints);

        receive_field_12.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_12"));
        receive_field_12.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_12.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_12.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_12.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_12.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_12.setText("0.00");
        txt_rcv_fld_12.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_12.setEnabled(false);
        txt_rcv_fld_12.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_12.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_12.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_12ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_12.add(txt_rcv_fld_12, gridBagConstraints);

        lbl_rcv_fld_12.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_12.setText("-");
        receive_field_12.add(lbl_rcv_fld_12, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_12, gridBagConstraints);

        field_7.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_7"));
        field_7.setMinimumSize(new java.awt.Dimension(200, 40));
        field_7.setPreferredSize(new java.awt.Dimension(200, 40));
        field_7.setRequestFocusEnabled(false);
        field_7.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_7.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_7.setText("0");
        txt_snd_fld_7.setEnabled(false);
        txt_snd_fld_7.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_7.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_7.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_7.add(txt_snd_fld_7, gridBagConstraints);

        BtnSetSendField_7.setText("set");
        BtnSetSendField_7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_7ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_7.add(BtnSetSendField_7, gridBagConstraints);

        lbl_snd_fld_7.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_7.setText("-");
        field_7.add(lbl_snd_fld_7, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_7, gridBagConstraints);

        field_8.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_8"));
        field_8.setMinimumSize(new java.awt.Dimension(200, 40));
        field_8.setPreferredSize(new java.awt.Dimension(200, 40));
        field_8.setRequestFocusEnabled(false);
        field_8.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_8.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_8.setText("0");
        txt_snd_fld_8.setEnabled(false);
        txt_snd_fld_8.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_8.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_8.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_8.add(txt_snd_fld_8, gridBagConstraints);

        BtnSetSendField_8.setText("set");
        BtnSetSendField_8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_8ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_8.add(BtnSetSendField_8, gridBagConstraints);

        lbl_snd_fld_8.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_8.setText("-");
        field_8.add(lbl_snd_fld_8, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_8, gridBagConstraints);

        field_9.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_9"));
        field_9.setMinimumSize(new java.awt.Dimension(200, 40));
        field_9.setPreferredSize(new java.awt.Dimension(200, 40));
        field_9.setRequestFocusEnabled(false);
        field_9.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_9.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_9.setText("0");
        txt_snd_fld_9.setEnabled(false);
        txt_snd_fld_9.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_9.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_9.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_9ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_9.add(txt_snd_fld_9, gridBagConstraints);

        BtnSetSendField_9.setText("set");
        BtnSetSendField_9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_9ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_9.add(BtnSetSendField_9, gridBagConstraints);

        lbl_snd_fld_9.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_9.setText("-");
        field_9.add(lbl_snd_fld_9, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 7;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_9, gridBagConstraints);

        field_10.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_10"));
        field_10.setMinimumSize(new java.awt.Dimension(200, 40));
        field_10.setPreferredSize(new java.awt.Dimension(200, 40));
        field_10.setRequestFocusEnabled(false);
        field_10.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_10.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_10.setText("0");
        txt_snd_fld_10.setEnabled(false);
        txt_snd_fld_10.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_10.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_10.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_10ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_10.add(txt_snd_fld_10, gridBagConstraints);

        BtnSetSendField_10.setText("set");
        BtnSetSendField_10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_10ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_10.add(BtnSetSendField_10, gridBagConstraints);

        lbl_snd_fld_10.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_10.setText("-");
        field_10.add(lbl_snd_fld_10, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 8;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_10, gridBagConstraints);

        btnStop1.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
        btnStop1.setForeground(new java.awt.Color(255, 0, 0));
        btnStop1.setText("STOP");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridheight = 3;
        gridBagConstraints.ipadx = 5;
        gridBagConstraints.ipady = 5;
        SendReveivePanel.add(btnStop1, gridBagConstraints);

        txtReady1.setForeground(new java.awt.Color(51, 51, 51));
        txtReady1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtReady1.setText("Ready");
        txtReady1.setToolTipText("");
        txtReady1.setEnabled(false);
        txtReady1.setMaximumSize(new java.awt.Dimension(75, 22));
        txtReady1.setMinimumSize(new java.awt.Dimension(75, 22));
        txtReady1.setPreferredSize(new java.awt.Dimension(75, 22));
        txtReady1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtReady1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        SendReveivePanel.add(txtReady1, gridBagConstraints);

        txtRunning1.setForeground(new java.awt.Color(51, 51, 51));
        txtRunning1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtRunning1.setText("Running");
        txtRunning1.setToolTipText("");
        txtRunning1.setEnabled(false);
        txtRunning1.setMaximumSize(new java.awt.Dimension(75, 22));
        txtRunning1.setMinimumSize(new java.awt.Dimension(75, 22));
        txtRunning1.setPreferredSize(new java.awt.Dimension(75, 22));
        txtRunning1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtRunning1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        SendReveivePanel.add(txtRunning1, gridBagConstraints);

        field_11.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_11"));
        field_11.setMinimumSize(new java.awt.Dimension(200, 40));
        field_11.setPreferredSize(new java.awt.Dimension(200, 40));
        field_11.setRequestFocusEnabled(false);
        field_11.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_11.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_11.setText("0");
        txt_snd_fld_11.setEnabled(false);
        txt_snd_fld_11.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_11.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_11.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_11ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_11.add(txt_snd_fld_11, gridBagConstraints);

        BtnSetSendField_11.setText("set");
        BtnSetSendField_11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_11ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_11.add(BtnSetSendField_11, gridBagConstraints);

        lbl_snd_fld_11.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_11.setText("-");
        field_11.add(lbl_snd_fld_11, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 9;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_11, gridBagConstraints);

        field_12.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_12"));
        field_12.setMinimumSize(new java.awt.Dimension(200, 40));
        field_12.setPreferredSize(new java.awt.Dimension(200, 40));
        field_12.setRequestFocusEnabled(false);
        field_12.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_12.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_12.setText("0");
        txt_snd_fld_12.setEnabled(false);
        txt_snd_fld_12.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_12.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_12.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_12ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_12.add(txt_snd_fld_12, gridBagConstraints);

        BtnSetSendField_12.setText("set");
        BtnSetSendField_12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_12ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_12.add(BtnSetSendField_12, gridBagConstraints);

        lbl_snd_fld_12.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_12.setText("-");
        field_12.add(lbl_snd_fld_12, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 10;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_12, gridBagConstraints);

        btnEnControl1.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnControl1.setForeground(new java.awt.Color(255, 0, 0));
        btnEnControl1.setText("Enable Control");
        btnEnControl1.setMaximumSize(new java.awt.Dimension(160, 35));
        btnEnControl1.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnControl1.setPreferredSize(new java.awt.Dimension(160, 35));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 3;
        SendReveivePanel.add(btnEnControl1, gridBagConstraints);

        btnEnSystem1.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        btnEnSystem1.setForeground(new java.awt.Color(255, 0, 0));
        btnEnSystem1.setText("Enable System");
        btnEnSystem1.setMaximumSize(new java.awt.Dimension(160, 35));
        btnEnSystem1.setMinimumSize(new java.awt.Dimension(160, 35));
        btnEnSystem1.setPreferredSize(new java.awt.Dimension(160, 35));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 3;
        SendReveivePanel.add(btnEnSystem1, gridBagConstraints);

        txtError1.setForeground(new java.awt.Color(51, 51, 51));
        txtError1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtError1.setText("Error");
        txtError1.setToolTipText("");
        txtError1.setEnabled(false);
        txtError1.setMinimumSize(new java.awt.Dimension(75, 22));
        txtError1.setPreferredSize(new java.awt.Dimension(70, 22));
        txtError1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtError1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        SendReveivePanel.add(txtError1, gridBagConstraints);

        txtUser1.setForeground(new java.awt.Color(51, 51, 51));
        txtUser1.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtUser1.setText("User");
        txtUser1.setToolTipText("");
        txtUser1.setEnabled(false);
        txtUser1.setMaximumSize(new java.awt.Dimension(75, 22));
        txtUser1.setMinimumSize(new java.awt.Dimension(75, 22));
        txtUser1.setPreferredSize(new java.awt.Dimension(75, 22));
        txtUser1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtUser1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 6;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 10, 10);
        SendReveivePanel.add(txtUser1, gridBagConstraints);

        receive_field_15.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_15"));
        receive_field_15.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_15.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_15.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_15.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_15.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_15.setText("0.00");
        txt_rcv_fld_15.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_15.setEnabled(false);
        txt_rcv_fld_15.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_15.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_15.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_15.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_15ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_15.add(txt_rcv_fld_15, gridBagConstraints);

        lbl_rcv_fld_15.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_15.setText("-");
        receive_field_15.add(lbl_rcv_fld_15, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 13;
        SendReveivePanel.add(receive_field_15, gridBagConstraints);

        receive_field_13.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_13"));
        receive_field_13.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_13.setName(""); // NOI18N
        receive_field_13.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_13.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_13.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_13.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_13.setText("0.00");
        txt_rcv_fld_13.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_13.setEnabled(false);
        txt_rcv_fld_13.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_13.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_13.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_13ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_13.add(txt_rcv_fld_13, gridBagConstraints);

        lbl_rcv_fld_13.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_13.setText("-");
        receive_field_13.add(lbl_rcv_fld_13, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_13, gridBagConstraints);

        receive_field_14.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_14"));
        receive_field_14.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_14.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_14.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_14.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_14.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_14.setText("0.00");
        txt_rcv_fld_14.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_14.setEnabled(false);
        txt_rcv_fld_14.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_14.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_14.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_14ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_14.add(txt_rcv_fld_14, gridBagConstraints);

        lbl_rcv_fld_14.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_14.setText("-");
        receive_field_14.add(lbl_rcv_fld_14, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_14, gridBagConstraints);

        receive_field_16.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_16"));
        receive_field_16.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_16.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_16.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_16.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_16.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_16.setText("0.00");
        txt_rcv_fld_16.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_16.setEnabled(false);
        txt_rcv_fld_16.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_16.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_16.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_16ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_16.add(txt_rcv_fld_16, gridBagConstraints);

        lbl_rcv_fld_16.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_16.setText("-");
        receive_field_16.add(lbl_rcv_fld_16, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_16, gridBagConstraints);

        receive_field_17.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_17"));
        receive_field_17.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_17.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_17.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_17.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_17.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_17.setText("0.00");
        txt_rcv_fld_17.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_17.setEnabled(false);
        txt_rcv_fld_17.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_17.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_17.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_17.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_17ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_17.add(txt_rcv_fld_17, gridBagConstraints);

        lbl_rcv_fld_17.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_17.setText("-");
        receive_field_17.add(lbl_rcv_fld_17, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_17, gridBagConstraints);

        receive_field_18.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_18"));
        receive_field_18.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_18.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_18.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_18.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_18.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_18.setText("0.00");
        txt_rcv_fld_18.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_18.setEnabled(false);
        txt_rcv_fld_18.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_18.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_18.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_18.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_18ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_18.add(txt_rcv_fld_18, gridBagConstraints);

        lbl_rcv_fld_18.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_18.setText("-");
        receive_field_18.add(lbl_rcv_fld_18, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_18, gridBagConstraints);

        field_13.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_13"));
        field_13.setMinimumSize(new java.awt.Dimension(200, 40));
        field_13.setPreferredSize(new java.awt.Dimension(200, 40));
        field_13.setRequestFocusEnabled(false);
        field_13.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_13.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_13.setText("0");
        txt_snd_fld_13.setEnabled(false);
        txt_snd_fld_13.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_13.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_13.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_13ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_13.add(txt_snd_fld_13, gridBagConstraints);

        BtnSetSendField_13.setText("set");
        BtnSetSendField_13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_13ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_13.add(BtnSetSendField_13, gridBagConstraints);

        lbl_snd_fld_13.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_13.setText("-");
        field_13.add(lbl_snd_fld_13, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 11;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_13, gridBagConstraints);

        field_14.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_14"));
        field_14.setMinimumSize(new java.awt.Dimension(200, 40));
        field_14.setPreferredSize(new java.awt.Dimension(200, 40));
        field_14.setRequestFocusEnabled(false);
        field_14.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_14.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_14.setText("0");
        txt_snd_fld_14.setEnabled(false);
        txt_snd_fld_14.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_14.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_14.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_14ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_14.add(txt_snd_fld_14, gridBagConstraints);

        BtnSetSendField_14.setText("set");
        BtnSetSendField_14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_14ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_14.add(BtnSetSendField_14, gridBagConstraints);

        lbl_snd_fld_14.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_14.setText("-");
        field_14.add(lbl_snd_fld_14, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 12;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_14, gridBagConstraints);
        field_14.getAccessibleContext().setAccessibleDescription("");

        field_15.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_15"));
        field_15.setMinimumSize(new java.awt.Dimension(200, 40));
        field_15.setPreferredSize(new java.awt.Dimension(200, 40));
        field_15.setRequestFocusEnabled(false);
        field_15.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_15.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_15.setText("0");
        txt_snd_fld_15.setEnabled(false);
        txt_snd_fld_15.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_15.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_15.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_15.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_15ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_15.add(txt_snd_fld_15, gridBagConstraints);

        BtnSetSendField_15.setText("set");
        BtnSetSendField_15.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_15ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_15.add(BtnSetSendField_15, gridBagConstraints);

        lbl_snd_fld_15.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_15.setText("-");
        field_15.add(lbl_snd_fld_15, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 13;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_15, gridBagConstraints);

        field_16.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_16"));
        field_16.setMinimumSize(new java.awt.Dimension(200, 40));
        field_16.setPreferredSize(new java.awt.Dimension(200, 40));
        field_16.setRequestFocusEnabled(false);
        field_16.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_16.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_16.setText("0");
        txt_snd_fld_16.setEnabled(false);
        txt_snd_fld_16.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_16.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_16.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_16ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_16.add(txt_snd_fld_16, gridBagConstraints);

        BtnSetSendField_16.setText("set");
        BtnSetSendField_16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_16ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_16.add(BtnSetSendField_16, gridBagConstraints);

        lbl_snd_fld_16.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_16.setText("-");
        field_16.add(lbl_snd_fld_16, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 14;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_16, gridBagConstraints);

        field_17.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_17"));
        field_17.setMinimumSize(new java.awt.Dimension(200, 40));
        field_17.setPreferredSize(new java.awt.Dimension(200, 40));
        field_17.setRequestFocusEnabled(false);
        field_17.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_17.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_17.setText("0");
        txt_snd_fld_17.setEnabled(false);
        txt_snd_fld_17.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_17.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_17.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_17.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_17ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_17.add(txt_snd_fld_17, gridBagConstraints);

        BtnSetSendField_17.setText("set");
        BtnSetSendField_17.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_17ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_17.add(BtnSetSendField_17, gridBagConstraints);

        lbl_snd_fld_17.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_17.setText("-");
        field_17.add(lbl_snd_fld_17, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 15;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_17, gridBagConstraints);

        field_18.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_18"));
        field_18.setMinimumSize(new java.awt.Dimension(200, 40));
        field_18.setPreferredSize(new java.awt.Dimension(200, 40));
        field_18.setRequestFocusEnabled(false);
        field_18.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_18.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_18.setText("0");
        txt_snd_fld_18.setEnabled(false);
        txt_snd_fld_18.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_18.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_18.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_18.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_18ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_18.add(txt_snd_fld_18, gridBagConstraints);

        BtnSetSendField_18.setText("set");
        BtnSetSendField_18.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_18ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_18.add(BtnSetSendField_18, gridBagConstraints);

        lbl_snd_fld_18.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_18.setText("-");
        field_18.add(lbl_snd_fld_18, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 16;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_18, gridBagConstraints);

        receive_field_19.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_19"));
        receive_field_19.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_19.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_19.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_19.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_19.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_19.setText("0.00");
        txt_rcv_fld_19.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_19.setEnabled(false);
        txt_rcv_fld_19.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_19.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_19.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_19ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_19.add(txt_rcv_fld_19, gridBagConstraints);

        lbl_rcv_fld_19.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_19.setText("-");
        receive_field_19.add(lbl_rcv_fld_19, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_19, gridBagConstraints);

        receive_field_20.setBorder(javax.swing.BorderFactory.createTitledBorder("receive_field_20"));
        receive_field_20.setMinimumSize(new java.awt.Dimension(200, 40));
        receive_field_20.setPreferredSize(new java.awt.Dimension(200, 40));
        receive_field_20.setLayout(new java.awt.GridBagLayout());

        txt_rcv_fld_20.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        txt_rcv_fld_20.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        txt_rcv_fld_20.setText("0.00");
        txt_rcv_fld_20.setDisabledTextColor(new java.awt.Color(255, 102, 102));
        txt_rcv_fld_20.setEnabled(false);
        txt_rcv_fld_20.setMaximumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_20.setMinimumSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_20.setPreferredSize(new java.awt.Dimension(120, 20));
        txt_rcv_fld_20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_rcv_fld_20ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        receive_field_20.add(txt_rcv_fld_20, gridBagConstraints);

        lbl_rcv_fld_20.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_rcv_fld_20.setText("-");
        receive_field_20.add(lbl_rcv_fld_20, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 2, 0);
        SendReveivePanel.add(receive_field_20, gridBagConstraints);

        field_19.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_19"));
        field_19.setMinimumSize(new java.awt.Dimension(200, 40));
        field_19.setPreferredSize(new java.awt.Dimension(200, 40));
        field_19.setRequestFocusEnabled(false);
        field_19.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_19.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_19.setText("0");
        txt_snd_fld_19.setEnabled(false);
        txt_snd_fld_19.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_19.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_19.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_19ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_19.add(txt_snd_fld_19, gridBagConstraints);

        BtnSetSendField_19.setText("set");
        BtnSetSendField_19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_19ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_19.add(BtnSetSendField_19, gridBagConstraints);

        lbl_snd_fld_19.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_19.setText("-");
        field_19.add(lbl_snd_fld_19, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 17;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_19, gridBagConstraints);

        field_20.setBorder(javax.swing.BorderFactory.createTitledBorder("send_field_20"));
        field_20.setMinimumSize(new java.awt.Dimension(200, 40));
        field_20.setPreferredSize(new java.awt.Dimension(200, 40));
        field_20.setRequestFocusEnabled(false);
        field_20.setLayout(new java.awt.GridBagLayout());

        txt_snd_fld_20.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        txt_snd_fld_20.setText("0");
        txt_snd_fld_20.setEnabled(false);
        txt_snd_fld_20.setMaximumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_20.setMinimumSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_20.setPreferredSize(new java.awt.Dimension(80, 21));
        txt_snd_fld_20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_snd_fld_20ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(3, 5, 3, 5);
        field_20.add(txt_snd_fld_20, gridBagConstraints);

        BtnSetSendField_20.setText("set");
        BtnSetSendField_20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BtnSetSendField_20ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        field_20.add(BtnSetSendField_20, gridBagConstraints);

        lbl_snd_fld_20.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        lbl_snd_fld_20.setText("-");
        field_20.add(lbl_snd_fld_20, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 7;
        gridBagConstraints.gridy = 18;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 2, 2);
        SendReveivePanel.add(field_20, gridBagConstraints);

        jTabbedPane1.addTab("MoreSendAndReceive", SendReveivePanel);

        MotorControl.add(jTabbedPane1, java.awt.BorderLayout.LINE_END);

        getContentPane().add(MotorControl, java.awt.BorderLayout.CENTER);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void txt_rcv_fld_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_1ActionPerformed

    private void txt_rcv_fld_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_2ActionPerformed

    private void txt_rcv_fld_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_3ActionPerformed

    private void txt_rcv_fld_4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_4ActionPerformed

    private void txt_rcv_fld_5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_5ActionPerformed

    private void txt_rcv_fld_6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_6ActionPerformed

    private void txt_snd_fld_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_1ActionPerformed

    private void BtnSetSendField_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_1ActionPerformed

    private void txt_snd_fld_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_2ActionPerformed

    private void BtnSetSendField_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_2ActionPerformed

    private void txt_snd_fld_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_3ActionPerformed

    private void BtnSetSendField_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_3ActionPerformed

    private void txt_snd_fld_4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_4ActionPerformed

    private void BtnSetSendField_4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_4ActionPerformed

    private void txtReadyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtReadyActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtReadyActionPerformed

    private void txtRunningActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtRunningActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtRunningActionPerformed

    private void txt_snd_fld_5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_5ActionPerformed

    private void BtnSetSendField_5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_5ActionPerformed

    private void txt_snd_fld_6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_6ActionPerformed

    private void BtnSetSendField_6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_6ActionPerformed

    private void myBtn_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_1ActionPerformed

    private void myBtn_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_2ActionPerformed

    private void myBtn_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_3ActionPerformed

    private void myBtn_4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_4ActionPerformed

    private void myBtn_5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_5ActionPerformed

    private void myBtn_6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_6ActionPerformed

    private void myBtn_7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_7ActionPerformed

    private void myBtn_8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_myBtn_8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_myBtn_8ActionPerformed

    private void txtBtn1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn1ActionPerformed

    private void txtBtn2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn2ActionPerformed

    private void txtBtn3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn3ActionPerformed

    private void txtBtn4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn4ActionPerformed

    private void txtBtn5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn5ActionPerformed

    private void txtBtn6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn6ActionPerformed

    private void txtBtn7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn7ActionPerformed

    private void txtBtn8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtBtn8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtBtn8ActionPerformed

    private void txtErrorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtErrorActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtErrorActionPerformed

    private void txtUserActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtUserActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtUserActionPerformed


    private void comboSelectData1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData1ActionPerformed

    private void comboSelectData2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData2ActionPerformed


    private void comboSelectData5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData5ActionPerformed

    private void comboSelectData7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData7ActionPerformed

    private void comboSelectData8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData8ActionPerformed

    private void comboSelectData9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData9ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData9ActionPerformed

    private void comboSelectData10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData10ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData10ActionPerformed

    private void comboSelectData14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData14ActionPerformed

    private void comboSelectData18ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData18ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData18ActionPerformed

    private void txtOffsetCH5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH5ActionPerformed

    private void txtScaleCH5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH5ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH5ActionPerformed

    private void txtScaleCH6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH6ActionPerformed

    private void txtOffsetCH7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH7ActionPerformed

    private void txtOffsetCH8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH8ActionPerformed

    private void txtScaleCH13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH13ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH13ActionPerformed

    private void txtOffsetCH14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH14ActionPerformed



    private void comboSelectData19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData19ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData19ActionPerformed

    private void comboSelectData20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_comboSelectData20ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_comboSelectData20ActionPerformed





    private void txtScaleCH1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH1ActionPerformed

    private void txtScaleCH2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH2ActionPerformed

    private void txtScaleCH3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH3ActionPerformed

    private void txtScaleCH4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtScaleCH4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtScaleCH4ActionPerformed

    private void txtOffsetCH2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH2ActionPerformed

    private void txtOffsetCH3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH3ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH3ActionPerformed

    private void txtOffsetCH4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH4ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH4ActionPerformed

    private void txt_rcv_fld_7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_7ActionPerformed

    private void txt_rcv_fld_8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_8ActionPerformed

    private void txt_rcv_fld_9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_9ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_9ActionPerformed

    private void txt_rcv_fld_10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_10ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_10ActionPerformed

    private void txt_rcv_fld_11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_11ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_11ActionPerformed

    private void txt_rcv_fld_12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_12ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_12ActionPerformed

    private void txt_snd_fld_7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_7ActionPerformed

    private void BtnSetSendField_7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_7ActionPerformed

    private void txt_snd_fld_8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_8ActionPerformed

    private void BtnSetSendField_8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_8ActionPerformed

    private void txt_snd_fld_9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_9ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_9ActionPerformed

    private void BtnSetSendField_9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_9ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_9ActionPerformed

    private void txt_snd_fld_10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_10ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_10ActionPerformed

    private void BtnSetSendField_10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_10ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_10ActionPerformed

    private void txtReady1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtReady1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtReady1ActionPerformed

    private void txtRunning1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtRunning1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtRunning1ActionPerformed

    private void txt_snd_fld_11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_11ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_11ActionPerformed

    private void BtnSetSendField_11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_11ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_11ActionPerformed

    private void txt_snd_fld_12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_12ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_12ActionPerformed

    private void BtnSetSendField_12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_12ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_12ActionPerformed

    private void txtError1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtError1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtError1ActionPerformed

    private void txtUser1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtUser1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtUser1ActionPerformed

    private void txt_rcv_fld_13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_13ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_13ActionPerformed

    private void txt_rcv_fld_14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_14ActionPerformed

    private void txt_rcv_fld_15ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_15ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_15ActionPerformed

    private void txt_rcv_fld_16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_16ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_16ActionPerformed

    private void txt_rcv_fld_17ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_17ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_17ActionPerformed

    private void txt_rcv_fld_18ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_18ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_18ActionPerformed

    private void txt_snd_fld_13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_13ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_13ActionPerformed

    private void BtnSetSendField_13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_13ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_13ActionPerformed

    private void txt_snd_fld_14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_14ActionPerformed

    private void BtnSetSendField_14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_14ActionPerformed

    private void txt_snd_fld_15ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_15ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_15ActionPerformed

    private void BtnSetSendField_15ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_15ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_15ActionPerformed

    private void txt_snd_fld_16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_16ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_16ActionPerformed

    private void BtnSetSendField_16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_16ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_16ActionPerformed

    private void txt_snd_fld_17ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_17ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_17ActionPerformed

    private void BtnSetSendField_17ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_17ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_17ActionPerformed

    private void txt_snd_fld_18ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_18ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_18ActionPerformed

    private void BtnSetSendField_18ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_18ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_18ActionPerformed

    private void txt_rcv_fld_19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_19ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_19ActionPerformed

    private void txt_rcv_fld_20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_rcv_fld_20ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_rcv_fld_20ActionPerformed

    private void txt_snd_fld_19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_19ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_19ActionPerformed

    private void BtnSetSendField_19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_19ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_19ActionPerformed

    private void txt_snd_fld_20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_snd_fld_20ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_snd_fld_20ActionPerformed

    private void BtnSetSendField_20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BtnSetSendField_20ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_BtnSetSendField_20ActionPerformed

    private void txtOffsetCH1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txtOffsetCH1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txtOffsetCH1ActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton BtnSetSendField_1;
    private javax.swing.JButton BtnSetSendField_10;
    private javax.swing.JButton BtnSetSendField_11;
    private javax.swing.JButton BtnSetSendField_12;
    private javax.swing.JButton BtnSetSendField_13;
    private javax.swing.JButton BtnSetSendField_14;
    private javax.swing.JButton BtnSetSendField_15;
    private javax.swing.JButton BtnSetSendField_16;
    private javax.swing.JButton BtnSetSendField_17;
    private javax.swing.JButton BtnSetSendField_18;
    private javax.swing.JButton BtnSetSendField_19;
    private javax.swing.JButton BtnSetSendField_2;
    private javax.swing.JButton BtnSetSendField_20;
    private javax.swing.JButton BtnSetSendField_3;
    private javax.swing.JButton BtnSetSendField_4;
    private javax.swing.JButton BtnSetSendField_5;
    private javax.swing.JButton BtnSetSendField_6;
    private javax.swing.JButton BtnSetSendField_7;
    private javax.swing.JButton BtnSetSendField_8;
    private javax.swing.JButton BtnSetSendField_9;
    private javax.swing.JPanel Controlpanel;
    private javax.swing.JPanel GraphJFree;
    private javax.swing.JPanel Hautpmenupanel;
    private javax.swing.JPanel MotorControl;
    private javax.swing.JPanel SendReveivePanel;
    private javax.swing.JTabbedPane TabPanel;
    private javax.swing.JButton btnDisableAllChannels;
    private javax.swing.JButton btnEnControl;
    private javax.swing.JButton btnEnControl1;
    private javax.swing.JButton btnEnSystem;
    private javax.swing.JButton btnEnSystem1;
    private javax.swing.JButton btnEnableAllChannels;
    private javax.swing.JButton btnErrorReset;
    private javax.swing.JButton btnScaleMinusCH1;
    private javax.swing.JButton btnScaleMinusCH10;
    private javax.swing.JButton btnScaleMinusCH11;
    private javax.swing.JButton btnScaleMinusCH12;
    private javax.swing.JButton btnScaleMinusCH13;
    private javax.swing.JButton btnScaleMinusCH14;
    private javax.swing.JButton btnScaleMinusCH15;
    private javax.swing.JButton btnScaleMinusCH16;
    private javax.swing.JButton btnScaleMinusCH17;
    private javax.swing.JButton btnScaleMinusCH18;
    private javax.swing.JButton btnScaleMinusCH19;
    private javax.swing.JButton btnScaleMinusCH2;
    private javax.swing.JButton btnScaleMinusCH20;
    private javax.swing.JButton btnScaleMinusCH3;
    private javax.swing.JButton btnScaleMinusCH4;
    private javax.swing.JButton btnScaleMinusCH5;
    private javax.swing.JButton btnScaleMinusCH6;
    private javax.swing.JButton btnScaleMinusCH7;
    private javax.swing.JButton btnScaleMinusCH8;
    private javax.swing.JButton btnScaleMinusCH9;
    private javax.swing.JButton btnScalePlusCH1;
    private javax.swing.JButton btnScalePlusCH10;
    private javax.swing.JButton btnScalePlusCH11;
    private javax.swing.JButton btnScalePlusCH12;
    private javax.swing.JButton btnScalePlusCH13;
    private javax.swing.JButton btnScalePlusCH14;
    private javax.swing.JButton btnScalePlusCH15;
    private javax.swing.JButton btnScalePlusCH16;
    private javax.swing.JButton btnScalePlusCH17;
    private javax.swing.JButton btnScalePlusCH18;
    private javax.swing.JButton btnScalePlusCH19;
    private javax.swing.JButton btnScalePlusCH2;
    private javax.swing.JButton btnScalePlusCH20;
    private javax.swing.JButton btnScalePlusCH3;
    private javax.swing.JButton btnScalePlusCH4;
    private javax.swing.JButton btnScalePlusCH5;
    private javax.swing.JButton btnScalePlusCH6;
    private javax.swing.JButton btnScalePlusCH7;
    private javax.swing.JButton btnScalePlusCH8;
    private javax.swing.JButton btnScalePlusCH9;
    private javax.swing.JButton btnStop;
    private javax.swing.JButton btnStop1;
    private javax.swing.JComboBox<String> comboSelectData1;
    private javax.swing.JComboBox<String> comboSelectData10;
    private javax.swing.JComboBox<String> comboSelectData11;
    private javax.swing.JComboBox<String> comboSelectData12;
    private javax.swing.JComboBox<String> comboSelectData13;
    private javax.swing.JComboBox<String> comboSelectData14;
    private javax.swing.JComboBox<String> comboSelectData15;
    private javax.swing.JComboBox<String> comboSelectData16;
    private javax.swing.JComboBox<String> comboSelectData17;
    private javax.swing.JComboBox<String> comboSelectData18;
    private javax.swing.JComboBox<String> comboSelectData19;
    private javax.swing.JComboBox<String> comboSelectData2;
    private javax.swing.JComboBox<String> comboSelectData20;
    private javax.swing.JComboBox<String> comboSelectData3;
    private javax.swing.JComboBox<String> comboSelectData4;
    private javax.swing.JComboBox<String> comboSelectData5;
    private javax.swing.JComboBox<String> comboSelectData6;
    private javax.swing.JComboBox<String> comboSelectData7;
    private javax.swing.JComboBox<String> comboSelectData8;
    private javax.swing.JComboBox<String> comboSelectData9;
    private javax.swing.JPanel field_1;
    private javax.swing.JPanel field_10;
    private javax.swing.JPanel field_11;
    private javax.swing.JPanel field_12;
    private javax.swing.JPanel field_13;
    private javax.swing.JPanel field_14;
    private javax.swing.JPanel field_15;
    private javax.swing.JPanel field_16;
    private javax.swing.JPanel field_17;
    private javax.swing.JPanel field_18;
    private javax.swing.JPanel field_19;
    private javax.swing.JPanel field_2;
    private javax.swing.JPanel field_20;
    private javax.swing.JPanel field_3;
    private javax.swing.JPanel field_4;
    private javax.swing.JPanel field_5;
    private javax.swing.JPanel field_6;
    private javax.swing.JPanel field_7;
    private javax.swing.JPanel field_8;
    private javax.swing.JPanel field_9;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JTabbedPane jTabbedPane1;
    private javax.swing.JLabel lblErrorCode;
    private javax.swing.JLabel lblSlowData2;
    private javax.swing.JLabel lbl_rcv_fld_1;
    private javax.swing.JLabel lbl_rcv_fld_10;
    private javax.swing.JLabel lbl_rcv_fld_11;
    private javax.swing.JLabel lbl_rcv_fld_12;
    private javax.swing.JLabel lbl_rcv_fld_13;
    private javax.swing.JLabel lbl_rcv_fld_14;
    private javax.swing.JLabel lbl_rcv_fld_15;
    private javax.swing.JLabel lbl_rcv_fld_16;
    private javax.swing.JLabel lbl_rcv_fld_17;
    private javax.swing.JLabel lbl_rcv_fld_18;
    private javax.swing.JLabel lbl_rcv_fld_19;
    private javax.swing.JLabel lbl_rcv_fld_2;
    private javax.swing.JLabel lbl_rcv_fld_20;
    private javax.swing.JLabel lbl_rcv_fld_3;
    private javax.swing.JLabel lbl_rcv_fld_4;
    private javax.swing.JLabel lbl_rcv_fld_5;
    private javax.swing.JLabel lbl_rcv_fld_6;
    private javax.swing.JLabel lbl_rcv_fld_7;
    private javax.swing.JLabel lbl_rcv_fld_8;
    private javax.swing.JLabel lbl_rcv_fld_9;
    private javax.swing.JLabel lbl_snd_fld_1;
    private javax.swing.JLabel lbl_snd_fld_10;
    private javax.swing.JLabel lbl_snd_fld_11;
    private javax.swing.JLabel lbl_snd_fld_12;
    private javax.swing.JLabel lbl_snd_fld_13;
    private javax.swing.JLabel lbl_snd_fld_14;
    private javax.swing.JLabel lbl_snd_fld_15;
    private javax.swing.JLabel lbl_snd_fld_16;
    private javax.swing.JLabel lbl_snd_fld_17;
    private javax.swing.JLabel lbl_snd_fld_18;
    private javax.swing.JLabel lbl_snd_fld_19;
    private javax.swing.JLabel lbl_snd_fld_2;
    private javax.swing.JLabel lbl_snd_fld_20;
    private javax.swing.JLabel lbl_snd_fld_3;
    private javax.swing.JLabel lbl_snd_fld_4;
    private javax.swing.JLabel lbl_snd_fld_5;
    private javax.swing.JLabel lbl_snd_fld_6;
    private javax.swing.JLabel lbl_snd_fld_7;
    private javax.swing.JLabel lbl_snd_fld_8;
    private javax.swing.JLabel lbl_snd_fld_9;
    private javax.swing.JButton myBtn_1;
    private javax.swing.JButton myBtn_2;
    private javax.swing.JButton myBtn_3;
    private javax.swing.JButton myBtn_4;
    private javax.swing.JButton myBtn_5;
    private javax.swing.JButton myBtn_6;
    private javax.swing.JButton myBtn_7;
    private javax.swing.JButton myBtn_8;
    private javax.swing.JPanel myButtons;
    private javax.swing.JPanel receive_field_1;
    private javax.swing.JPanel receive_field_10;
    private javax.swing.JPanel receive_field_11;
    private javax.swing.JPanel receive_field_12;
    private javax.swing.JPanel receive_field_13;
    private javax.swing.JPanel receive_field_14;
    private javax.swing.JPanel receive_field_15;
    private javax.swing.JPanel receive_field_16;
    private javax.swing.JPanel receive_field_17;
    private javax.swing.JPanel receive_field_18;
    private javax.swing.JPanel receive_field_19;
    private javax.swing.JPanel receive_field_2;
    private javax.swing.JPanel receive_field_20;
    private javax.swing.JPanel receive_field_3;
    private javax.swing.JPanel receive_field_4;
    private javax.swing.JPanel receive_field_5;
    private javax.swing.JPanel receive_field_6;
    private javax.swing.JPanel receive_field_7;
    private javax.swing.JPanel receive_field_8;
    private javax.swing.JPanel receive_field_9;
    private javax.swing.JTable tbSlowData3;
    private javax.swing.JTextField txtBtn1;
    private javax.swing.JTextField txtBtn2;
    private javax.swing.JTextField txtBtn3;
    private javax.swing.JTextField txtBtn4;
    private javax.swing.JTextField txtBtn5;
    private javax.swing.JTextField txtBtn6;
    private javax.swing.JTextField txtBtn7;
    private javax.swing.JTextField txtBtn8;
    private javax.swing.JTextField txtError;
    private javax.swing.JTextField txtError1;
    private javax.swing.JTextField txtErrorCode;
    private javax.swing.JTextField txtOffsetCH1;
    private javax.swing.JTextField txtOffsetCH10;
    private javax.swing.JTextField txtOffsetCH11;
    private javax.swing.JTextField txtOffsetCH12;
    private javax.swing.JTextField txtOffsetCH13;
    private javax.swing.JTextField txtOffsetCH14;
    private javax.swing.JTextField txtOffsetCH15;
    private javax.swing.JTextField txtOffsetCH16;
    private javax.swing.JTextField txtOffsetCH17;
    private javax.swing.JTextField txtOffsetCH18;
    private javax.swing.JTextField txtOffsetCH19;
    private javax.swing.JTextField txtOffsetCH2;
    private javax.swing.JTextField txtOffsetCH20;
    private javax.swing.JTextField txtOffsetCH3;
    private javax.swing.JTextField txtOffsetCH4;
    private javax.swing.JTextField txtOffsetCH5;
    private javax.swing.JTextField txtOffsetCH6;
    private javax.swing.JTextField txtOffsetCH7;
    private javax.swing.JTextField txtOffsetCH8;
    private javax.swing.JTextField txtOffsetCH9;
    private javax.swing.JTextField txtReady;
    private javax.swing.JTextField txtReady1;
    private javax.swing.JTextField txtRunning;
    private javax.swing.JTextField txtRunning1;
    private javax.swing.JTextField txtScaleCH1;
    private javax.swing.JTextField txtScaleCH10;
    private javax.swing.JTextField txtScaleCH11;
    private javax.swing.JTextField txtScaleCH12;
    private javax.swing.JTextField txtScaleCH13;
    private javax.swing.JTextField txtScaleCH14;
    private javax.swing.JTextField txtScaleCH15;
    private javax.swing.JTextField txtScaleCH16;
    private javax.swing.JTextField txtScaleCH17;
    private javax.swing.JTextField txtScaleCH18;
    private javax.swing.JTextField txtScaleCH19;
    private javax.swing.JTextField txtScaleCH2;
    private javax.swing.JTextField txtScaleCH20;
    private javax.swing.JTextField txtScaleCH3;
    private javax.swing.JTextField txtScaleCH4;
    private javax.swing.JTextField txtScaleCH5;
    private javax.swing.JTextField txtScaleCH6;
    private javax.swing.JTextField txtScaleCH7;
    private javax.swing.JTextField txtScaleCH8;
    private javax.swing.JTextField txtScaleCH9;
    private javax.swing.JTextField txtUser;
    private javax.swing.JTextField txtUser1;
    private javax.swing.JTextField txt_rcv_fld_1;
    private javax.swing.JTextField txt_rcv_fld_10;
    private javax.swing.JTextField txt_rcv_fld_11;
    private javax.swing.JTextField txt_rcv_fld_12;
    private javax.swing.JTextField txt_rcv_fld_13;
    private javax.swing.JTextField txt_rcv_fld_14;
    private javax.swing.JTextField txt_rcv_fld_15;
    private javax.swing.JTextField txt_rcv_fld_16;
    private javax.swing.JTextField txt_rcv_fld_17;
    private javax.swing.JTextField txt_rcv_fld_18;
    private javax.swing.JTextField txt_rcv_fld_19;
    private javax.swing.JTextField txt_rcv_fld_2;
    private javax.swing.JTextField txt_rcv_fld_20;
    private javax.swing.JTextField txt_rcv_fld_3;
    private javax.swing.JTextField txt_rcv_fld_4;
    private javax.swing.JTextField txt_rcv_fld_5;
    private javax.swing.JTextField txt_rcv_fld_6;
    private javax.swing.JTextField txt_rcv_fld_7;
    private javax.swing.JTextField txt_rcv_fld_8;
    private javax.swing.JTextField txt_rcv_fld_9;
    private javax.swing.JTextField txt_snd_fld_1;
    private javax.swing.JTextField txt_snd_fld_10;
    private javax.swing.JTextField txt_snd_fld_11;
    private javax.swing.JTextField txt_snd_fld_12;
    private javax.swing.JTextField txt_snd_fld_13;
    private javax.swing.JTextField txt_snd_fld_14;
    private javax.swing.JTextField txt_snd_fld_15;
    private javax.swing.JTextField txt_snd_fld_16;
    private javax.swing.JTextField txt_snd_fld_17;
    private javax.swing.JTextField txt_snd_fld_18;
    private javax.swing.JTextField txt_snd_fld_19;
    private javax.swing.JTextField txt_snd_fld_2;
    private javax.swing.JTextField txt_snd_fld_20;
    private javax.swing.JTextField txt_snd_fld_3;
    private javax.swing.JTextField txt_snd_fld_4;
    private javax.swing.JTextField txt_snd_fld_5;
    private javax.swing.JTextField txt_snd_fld_6;
    private javax.swing.JTextField txt_snd_fld_7;
    private javax.swing.JTextField txt_snd_fld_8;
    private javax.swing.JTextField txt_snd_fld_9;
    // End of variables declaration//GEN-END:variables

    private void applyTabbedPaneStyle(javax.swing.JTabbedPane tabbedPane, java.awt.Color tabAreaColor) {
        if (tabbedPane == null) {
            return;
        }
        tabbedPane.putClientProperty("JTabbedPane.tabType", "underline");
        tabbedPane.setBackground(tabAreaColor);
        tabbedPane.setOpaque(true);
        String tabAreaHex = toHex(tabAreaColor);
        tabbedPane.putClientProperty(
            "FlatLaf.style",
            "underlineColor: " + ACCENT_VIOLET_HEX + "; " +
            "inactiveUnderlineColor: " + ACCENT_VIOLET_HEX + "; " +
            "disabledUnderlineColor: " + ACCENT_VIOLET_HEX + "; " +
            "focusColor: " + ACCENT_VIOLET_HEX + "; " +
            "contentAreaColor: " + tabAreaHex + "; " +
            "selectedBackground: " + tabAreaHex + ";"
        );
    }

    private void applySurfaceTheme() {
        boolean darkMode = com.formdev.flatlaf.FlatLaf.isLafDark();
        java.awt.Color base = darkMode ? SURFACE_DARK : SURFACE_LIGHT;
        java.awt.Color raised = darkMode ? SURFACE_DARK_RAISED : SURFACE_LIGHT_RAISED;

        MotorControl.setBackground(base);
        GraphJFree.setBackground(base);
        TabPanel.setBackground(base);
        jTabbedPane1.setBackground(raised);
        Hautpmenupanel.setBackground(raised);
        Controlpanel.setBackground(raised);
        SendReveivePanel.setBackground(raised);
        scopeDevPanel.applyTheme(raised);

        applyTabbedPaneStyle(jTabbedPane1, raised);
        applyTabbedPaneStyle(TabPanel, base);
    }

    private void applyChannelLegendLayout() {
        if (channelVisibilityButtons != null) {
            return;
        }
        java.awt.LayoutManager layout = Hautpmenupanel.getLayout();
        if (!(layout instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) layout;

        javax.swing.JComboBox<String>[] combos = getChannelComboBoxes();
        for (javax.swing.JComboBox<String> combo : combos) {
            shiftGridBagColumn(gbl, combo, CHANNEL_COMBO_COLUMN, CHANNEL_COMBO_WIDTH);
        }

        shiftGridBagColumn(gbl, jLabel13, CHANNEL_COMBO_COLUMN, CHANNEL_COMBO_WIDTH);

        channelVisibilityLabel = new javax.swing.JLabel("Enable");
        channelVisibilityLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        java.awt.GridBagConstraints labelGbc = new java.awt.GridBagConstraints();
        labelGbc.gridx = CHANNEL_LEGEND_COLUMN;
        labelGbc.gridy = 2;
        labelGbc.insets = new java.awt.Insets(0, 0, 4, 8);
        labelGbc.fill = java.awt.GridBagConstraints.HORIZONTAL;
        labelGbc.anchor = java.awt.GridBagConstraints.CENTER;
        Hautpmenupanel.add(channelVisibilityLabel, labelGbc);

        channelVisibilityButtons = new javax.swing.JToggleButton[CHANNEL_LEGEND_ROWS];
        for (int i = 0; i < CHANNEL_LEGEND_ROWS; i++) {
            javax.swing.JToggleButton toggle = new javax.swing.JToggleButton("CH" + (i + 1));
            toggle.setSelected(true);
            toggle.setFocusPainted(false);
            toggle.setOpaque(false);
            toggle.setContentAreaFilled(false);
            toggle.setBorderPainted(false);
            toggle.setFont(toggle.getFont().deriveFont(java.awt.Font.BOLD, 14f));
            toggle.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
            toggle.setMargin(new java.awt.Insets(0, 0, 0, 0));
            channelVisibilityButtons[i] = toggle;

            java.awt.GridBagConstraints gbc = new java.awt.GridBagConstraints();
            gbc.gridx = CHANNEL_LEGEND_COLUMN;
            gbc.gridy = CHANNEL_LEGEND_START_ROW + i;
            gbc.insets = new java.awt.Insets(0, 0, 5, 8);
            gbc.anchor = java.awt.GridBagConstraints.WEST;
            Hautpmenupanel.add(toggle, gbc);
        }

        Hautpmenupanel.revalidate();
        Hautpmenupanel.repaint();
    }

    private void applyDisableAllChannelsButton() {
        if (btnDisableAllChannels == null || btnEnableAllChannels == null) {
            return;
        }

        java.awt.Insets margin = new java.awt.Insets(2, 10, 2, 10);
        btnDisableAllChannels.setMargin(margin);
        btnEnableAllChannels.setMargin(margin);

        java.awt.Dimension disableSize = btnDisableAllChannels.getPreferredSize();
        java.awt.Dimension enableSize = btnEnableAllChannels.getPreferredSize();
        int unifiedWidth = Math.max(disableSize.width, enableSize.width);
        int unifiedHeight = Math.max(disableSize.height, enableSize.height);
        java.awt.Dimension unifiedSize = new java.awt.Dimension(unifiedWidth, unifiedHeight);
        btnDisableAllChannels.setPreferredSize(unifiedSize);
        btnDisableAllChannels.setMinimumSize(unifiedSize);
        btnDisableAllChannels.setMaximumSize(unifiedSize);
        btnEnableAllChannels.setPreferredSize(unifiedSize);
        btnEnableAllChannels.setMinimumSize(unifiedSize);
        btnEnableAllChannels.setMaximumSize(unifiedSize);
    }


    private void shiftGridBagColumn(java.awt.GridBagLayout gbl, java.awt.Component component, int gridx, int gridwidth) {
        java.awt.GridBagConstraints gbc = gbl.getConstraints(component);
        gbc.gridx = gridx;
        gbc.gridwidth = gridwidth;
        gbl.setConstraints(component, gbc);
    }

    private void applyChannelSetupHeaderStyles() {
        java.awt.Font headerFont = jLabel9.getFont().deriveFont(java.awt.Font.BOLD, 12f);

        if (channelVisibilityLabel != null) {
            channelVisibilityLabel.setText("Enable");
            channelVisibilityLabel.setFont(headerFont);
            channelVisibilityLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        }

        jLabel13.setText("Signal");
        jLabel13.setFont(headerFont);
        jLabel13.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);

        jLabel9.setText("Scaling");
        jLabel9.setFont(headerFont);
        jLabel9.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);

        jLabel12.setText("Offset");
        jLabel12.setFont(headerFont);
        jLabel12.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
    }

    private void applyChannelComboSizing() {
        javax.swing.JComboBox<String>[] combos = getChannelComboBoxes();
        java.awt.Dimension preferred = comboSelectData1.getPreferredSize();
        int baseWidth = Math.max(preferred.width, 200);
        java.awt.Dimension wide = new java.awt.Dimension(baseWidth, preferred.height);

        for (javax.swing.JComboBox<String> combo : combos) {
            combo.setPreferredSize(wide);
            combo.setMinimumSize(wide);
        }

        if (Hautpmenupanel.getLayout() instanceof java.awt.GridBagLayout) {
            java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Hautpmenupanel.getLayout();
            for (javax.swing.JComboBox<String> combo : combos) {
                java.awt.GridBagConstraints gbc = gbl.getConstraints(combo);
                gbc.fill = java.awt.GridBagConstraints.HORIZONTAL;
                gbc.weightx = 0.0;
                gbl.setConstraints(combo, gbc);
            }
            java.awt.GridBagConstraints labelGbc = gbl.getConstraints(jLabel13);
            labelGbc.fill = java.awt.GridBagConstraints.HORIZONTAL;
            labelGbc.weightx = 0.0;
            gbl.setConstraints(jLabel13, labelGbc);
        }
    }

    private void applyChannelColumnSpacing() {
        if (!(Hautpmenupanel.getLayout() instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Hautpmenupanel.getLayout();
        int leftInset = 12;
        int rightInset = 12;

        if (channelVisibilityLabel != null) {
            setGridBagInsets(gbl, channelVisibilityLabel, leftInset, null);
        }
        if (channelVisibilityButtons != null) {
            for (javax.swing.JToggleButton toggle : channelVisibilityButtons) {
                if (toggle != null) {
                    setGridBagInsets(gbl, toggle, leftInset, null);
                }
            }
        }

        setGridBagInsets(gbl, jLabel12, null, rightInset);
        for (javax.swing.JTextField field : getOffsetTextFields()) {
            setGridBagInsets(gbl, field, null, rightInset);
        }
    }

    private void setGridBagInsets(java.awt.GridBagLayout gbl, java.awt.Component component, Integer left, Integer right) {
        java.awt.GridBagConstraints gbc = gbl.getConstraints(component);
        java.awt.Insets old = gbc.insets != null ? gbc.insets : new java.awt.Insets(0, 0, 0, 0);
        int newLeft = left != null ? left : old.left;
        int newRight = right != null ? right : old.right;
        gbc.insets = new java.awt.Insets(old.top, newLeft, old.bottom, newRight);
        gbl.setConstraints(component, gbc);
    }

    private void applyChannelValueFieldAlignment() {
        javax.swing.JTextField[] scaleFields = getScaleTextFields();
        javax.swing.JTextField[] offsetFields = getOffsetTextFields();
        for (javax.swing.JTextField field : scaleFields) {
            field.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        }
        for (javax.swing.JTextField field : offsetFields) {
            field.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        }
    }

    private void applyControlPanelLayout() {
        shiftControlPanelRows(-2, 2);
        syncControlUnitFonts();
        applyUnitLabelSizing();
        alignControlReceiveFields();
        applySendFieldSizing();
        alignControlSendFields();
        alignControlErrorCode();
        resizeMyButtonsPanel();
        configureSlowDataTable();
    }

    private void shiftControlPanelRows(int rowDelta, int minRow) {
        if (!(Controlpanel.getLayout() instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();
        for (java.awt.Component component : Controlpanel.getComponents()) {
            java.awt.GridBagConstraints gbc = gbl.getConstraints(component);
            if (gbc.gridy >= minRow) {
                gbc.gridy = Math.max(0, gbc.gridy + rowDelta);
                gbl.setConstraints(component, gbc);
            }
        }
    }

    private void syncControlUnitFonts() {
        java.awt.Font receiveFont = txt_rcv_fld_1.getFont();
        java.awt.Font unitFont = receiveFont.deriveFont(12f);

        lbl_rcv_fld_1.setFont(unitFont);
        lbl_rcv_fld_2.setFont(unitFont);
        lbl_rcv_fld_3.setFont(unitFont);
        lbl_rcv_fld_4.setFont(unitFont);
        lbl_rcv_fld_5.setFont(unitFont);
        lbl_rcv_fld_6.setFont(unitFont);

        lbl_snd_fld_1.setFont(unitFont);
        lbl_snd_fld_2.setFont(unitFont);
        lbl_snd_fld_3.setFont(unitFont);
        lbl_snd_fld_4.setFont(unitFont);
        lbl_snd_fld_5.setFont(unitFont);
        lbl_snd_fld_6.setFont(unitFont);
    }

    private void applyUnitLabelSizing() {
        javax.swing.JLabel[] receiveLabels = getReceiveUnitLabels();
        javax.swing.JLabel[] sendLabels = getSendUnitLabels();
        int maxWidth = 0;

        for (javax.swing.JLabel label : receiveLabels) {
            if (label == null) {
                continue;
            }
            java.awt.FontMetrics metrics = label.getFontMetrics(label.getFont());
            int width = metrics.stringWidth("WWWW") + 2;
            maxWidth = Math.max(maxWidth, width);
        }
        for (javax.swing.JLabel label : sendLabels) {
            if (label == null) {
                continue;
            }
            java.awt.FontMetrics metrics = label.getFontMetrics(label.getFont());
            int width = metrics.stringWidth("WWWW") + 2;
            maxWidth = Math.max(maxWidth, width);
        }

        for (javax.swing.JLabel label : receiveLabels) {
            setUnitLabelSize(label, maxWidth);
        }
        for (javax.swing.JLabel label : sendLabels) {
            setUnitLabelSize(label, maxWidth);
        }
    }

    private void setUnitLabelSize(javax.swing.JLabel label, int width) {
        if (label == null) {
            return;
        }
        java.awt.Dimension pref = label.getPreferredSize();
        java.awt.Dimension size = new java.awt.Dimension(width, pref.height);
        label.setPreferredSize(size);
        label.setMinimumSize(size);
        label.setMaximumSize(size);
        label.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
    }

    private javax.swing.JLabel[] getReceiveUnitLabels() {
        return new javax.swing.JLabel[] {
            lbl_rcv_fld_1, lbl_rcv_fld_2, lbl_rcv_fld_3, lbl_rcv_fld_4, lbl_rcv_fld_5,
            lbl_rcv_fld_6, lbl_rcv_fld_7, lbl_rcv_fld_8, lbl_rcv_fld_9, lbl_rcv_fld_10,
            lbl_rcv_fld_11, lbl_rcv_fld_12, lbl_rcv_fld_13, lbl_rcv_fld_14, lbl_rcv_fld_15,
            lbl_rcv_fld_16, lbl_rcv_fld_17, lbl_rcv_fld_18, lbl_rcv_fld_19, lbl_rcv_fld_20
        };
    }

    private javax.swing.JLabel[] getSendUnitLabels() {
        return new javax.swing.JLabel[] {
            lbl_snd_fld_1, lbl_snd_fld_2, lbl_snd_fld_3, lbl_snd_fld_4, lbl_snd_fld_5,
            lbl_snd_fld_6, lbl_snd_fld_7, lbl_snd_fld_8, lbl_snd_fld_9, lbl_snd_fld_10,
            lbl_snd_fld_11, lbl_snd_fld_12, lbl_snd_fld_13, lbl_snd_fld_14, lbl_snd_fld_15,
            lbl_snd_fld_16, lbl_snd_fld_17, lbl_snd_fld_18, lbl_snd_fld_19, lbl_snd_fld_20
        };
    }

    private void alignControlSendFields() {
        if (!(Controlpanel.getLayout() instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();
        javax.swing.JPanel[] sendFields = new javax.swing.JPanel[] {
            field_1, field_2, field_3, field_4, field_5, field_6
        };
        for (javax.swing.JPanel field : sendFields) {
            java.awt.GridBagConstraints gbc = gbl.getConstraints(field);
            gbc.anchor = java.awt.GridBagConstraints.WEST;
            gbc.insets = new java.awt.Insets(2, 5, 2, 5);
            gbl.setConstraints(field, gbc);
        }
    }

    private void applySendFieldSizing() {
        javax.swing.JTextField[] sendFields = getSendTextFields();
        javax.swing.JButton[] setButtons = getSendSetButtons();
        java.awt.FontMetrics fieldMetrics = txt_snd_fld_1.getFontMetrics(txt_snd_fld_1.getFont());
        int fieldWidth = fieldMetrics.stringWidth("000000000") + 14;
        int fieldHeight = txt_snd_fld_1.getPreferredSize().height;
        java.awt.Dimension fieldSize = new java.awt.Dimension(fieldWidth, fieldHeight);

        for (javax.swing.JTextField field : sendFields) {
            if (field != null) {
                field.setPreferredSize(fieldSize);
                field.setMinimumSize(fieldSize);
                field.setMaximumSize(new java.awt.Dimension(fieldWidth, fieldHeight));
            }
        }

        java.awt.FontMetrics buttonMetrics = BtnSetSendField_1.getFontMetrics(BtnSetSendField_1.getFont());
        int buttonWidth = Math.max(50, buttonMetrics.stringWidth("set") + 30);
        int buttonHeight = BtnSetSendField_1.getPreferredSize().height;
        java.awt.Dimension buttonSize = new java.awt.Dimension(buttonWidth, buttonHeight);

        for (javax.swing.JButton button : setButtons) {
            if (button != null) {
                button.setPreferredSize(buttonSize);
                button.setMinimumSize(buttonSize);
                button.setMaximumSize(new java.awt.Dimension(buttonWidth, buttonHeight));
            }
        }
    }

    private javax.swing.JTextField[] getSendTextFields() {
        return new javax.swing.JTextField[] {
            txt_snd_fld_1, txt_snd_fld_2, txt_snd_fld_3, txt_snd_fld_4, txt_snd_fld_5,
            txt_snd_fld_6, txt_snd_fld_7, txt_snd_fld_8, txt_snd_fld_9, txt_snd_fld_10,
            txt_snd_fld_11, txt_snd_fld_12, txt_snd_fld_13, txt_snd_fld_14, txt_snd_fld_15,
            txt_snd_fld_16, txt_snd_fld_17, txt_snd_fld_18, txt_snd_fld_19, txt_snd_fld_20
        };
    }

    private javax.swing.JButton[] getSendSetButtons() {
        return new javax.swing.JButton[] {
            BtnSetSendField_1, BtnSetSendField_2, BtnSetSendField_3, BtnSetSendField_4, BtnSetSendField_5,
            BtnSetSendField_6, BtnSetSendField_7, BtnSetSendField_8, BtnSetSendField_9, BtnSetSendField_10,
            BtnSetSendField_11, BtnSetSendField_12, BtnSetSendField_13, BtnSetSendField_14, BtnSetSendField_15,
            BtnSetSendField_16, BtnSetSendField_17, BtnSetSendField_18, BtnSetSendField_19, BtnSetSendField_20
        };
    }

    private void alignControlReceiveFields() {
        if (!(Controlpanel.getLayout() instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();
        javax.swing.JPanel[] receiveFields = new javax.swing.JPanel[] {
            receive_field_1, receive_field_2, receive_field_3, receive_field_4, receive_field_5, receive_field_6
        };
        for (javax.swing.JPanel field : receiveFields) {
            java.awt.GridBagConstraints gbc = gbl.getConstraints(field);
            gbc.anchor = java.awt.GridBagConstraints.CENTER;
            gbc.insets = new java.awt.Insets(3, 8, 3, 8);
            gbl.setConstraints(field, gbc);
        }
    }

    private void alignControlErrorCode() {
        if (!(Controlpanel.getLayout() instanceof java.awt.GridBagLayout)) {
            return;
        }
        java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();

        java.awt.GridBagConstraints labelGbc = gbl.getConstraints(lblErrorCode);
        labelGbc.gridx = 0;
        labelGbc.gridwidth = 3;
        labelGbc.anchor = java.awt.GridBagConstraints.CENTER;
        labelGbc.insets = new java.awt.Insets(2, 0, 2, 0);
        gbl.setConstraints(lblErrorCode, labelGbc);

        java.awt.GridBagConstraints valueGbc = gbl.getConstraints(txtErrorCode);
        valueGbc.gridx = 0;
        valueGbc.gridwidth = 3;
        valueGbc.anchor = java.awt.GridBagConstraints.CENTER;
        valueGbc.insets = new java.awt.Insets(2, 0, 4, 0);
        gbl.setConstraints(txtErrorCode, valueGbc);
    }

    private void resizeMyButtonsPanel() {
        java.awt.Dimension min = myButtons.getMinimumSize();
        java.awt.Dimension pref = myButtons.getPreferredSize();
        int width = 220;
        myButtons.setMinimumSize(new java.awt.Dimension(width, min.height));
        myButtons.setPreferredSize(new java.awt.Dimension(width, pref.height));

        if (Controlpanel.getLayout() instanceof java.awt.GridBagLayout) {
            java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();
            java.awt.GridBagConstraints gbc = gbl.getConstraints(myButtons);
            gbc.gridwidth = 3;
            gbc.anchor = java.awt.GridBagConstraints.WEST;
            gbl.setConstraints(myButtons, gbc);
        }
    }

    private void configureSlowDataTable() {
        int rowCount = tbSlowData3.getRowCount();
        if (rowCount <= 0) {
            rowCount = 100;
        }
        javax.swing.table.DefaultTableModel model = new javax.swing.table.DefaultTableModel(
            new Object[rowCount][3],
            new String[] { "id", "variable", "value" }
        ) {
            Class[] types = new Class[] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean[] {
                false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types[columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit[columnIndex];
            }
        };
        tbSlowData3.setModel(model);
        tbSlowData3.setRowHeight(18);
        tbSlowData3.setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_LAST_COLUMN);
        jScrollPane2.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        jScrollPane2.setPreferredSize(new java.awt.Dimension(500, 180));
        tbSlowData3.setPreferredSize(new java.awt.Dimension(500, 1400));

        javax.swing.table.TableColumnModel columns = tbSlowData3.getColumnModel();
        int valueMinWidth = tbSlowData3.getFontMetrics(tbSlowData3.getFont()).stringWidth("000000000000") + 16;
        int idWidth = tbSlowData3.getFontMetrics(tbSlowData3.getFont()).stringWidth("000") + 8;
        columns.getColumn(0).setPreferredWidth(idWidth);
        columns.getColumn(0).setMinWidth(idWidth);
        columns.getColumn(0).setMaxWidth(idWidth);
        columns.getColumn(1).setPreferredWidth(220);
        columns.getColumn(1).setMinWidth(160);
        columns.getColumn(1).setMaxWidth(260);
        columns.getColumn(2).setPreferredWidth(Math.max(110, valueMinWidth));
        columns.getColumn(2).setMinWidth(Math.max(95, valueMinWidth));

        javax.swing.table.TableRowSorter<javax.swing.table.TableModel> sorter =
            new javax.swing.table.TableRowSorter<>(tbSlowData3.getModel());
        for (int col = 0; col < tbSlowData3.getColumnCount(); col++) {
            sorter.setSortable(col, false);
        }
        sorter.setRowFilter(new javax.swing.RowFilter<javax.swing.table.TableModel, Integer>() {
            public boolean include(javax.swing.RowFilter.Entry<? extends javax.swing.table.TableModel, ? extends Integer> entry) {
                return entry.getIdentifier() != 0;
            }
        });
        tbSlowData3.setRowSorter(sorter);

        if (Controlpanel.getLayout() instanceof java.awt.GridBagLayout) {
            java.awt.GridBagLayout gbl = (java.awt.GridBagLayout) Controlpanel.getLayout();
            java.awt.GridBagConstraints tableGbc = gbl.getConstraints(jScrollPane2);
            tableGbc.gridx = 3;
            tableGbc.gridwidth = 6;
            tableGbc.fill = java.awt.GridBagConstraints.BOTH;
            tableGbc.weightx = 1.0;
            tableGbc.insets = new java.awt.Insets(5, 2, 5, 5);
            gbl.setConstraints(jScrollPane2, tableGbc);

            java.awt.GridBagConstraints labelGbc = gbl.getConstraints(jLabel11);
            labelGbc.gridx = 3;
            labelGbc.gridwidth = 6;
            gbl.setConstraints(jLabel11, labelGbc);
        }

        installSlowDataCopySupport();
    }

    private void installSlowDataCopySupport() {
        if (tbSlowData3 == null) {
            return;
        }
        if (Boolean.TRUE.equals(tbSlowData3.getClientProperty("slowDataCopyInstalled"))) {
            return;
        }
        tbSlowData3.putClientProperty("slowDataCopyInstalled", Boolean.TRUE);

        javax.swing.Action copyAction = new javax.swing.AbstractAction("Copy") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent event) {
                copySelectedSlowDataToClipboard();
            }
        };
        tbSlowData3.getActionMap().put("copySlowDataSelection", copyAction);
        tbSlowData3.getInputMap(javax.swing.JComponent.WHEN_FOCUSED).put(
            javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_C, java.awt.event.InputEvent.CTRL_DOWN_MASK),
            "copySlowDataSelection"
        );

        javax.swing.JPopupMenu popupMenu = new javax.swing.JPopupMenu();
        javax.swing.JMenuItem copyItem = new javax.swing.JMenuItem(copyAction);
        copyItem.setText("Copy");
        popupMenu.add(copyItem);

        tbSlowData3.addMouseListener(new java.awt.event.MouseAdapter() {
            private void showPopup(java.awt.event.MouseEvent event) {
                if (!event.isPopupTrigger()) {
                    return;
                }
                int row = tbSlowData3.rowAtPoint(event.getPoint());
                if (row >= 0 && !tbSlowData3.isRowSelected(row)) {
                    tbSlowData3.setRowSelectionInterval(row, row);
                }
                copyItem.setEnabled(tbSlowData3.getSelectedRowCount() > 0);
                popupMenu.show(event.getComponent(), event.getX(), event.getY());
            }

            @Override
            public void mousePressed(java.awt.event.MouseEvent event) {
                showPopup(event);
            }

            @Override
            public void mouseReleased(java.awt.event.MouseEvent event) {
                showPopup(event);
            }
        });
    }

    private void copySelectedSlowDataToClipboard() {
        int selectedViewRow = tbSlowData3.getSelectedRow();
        if (selectedViewRow < 0) {
            return;
        }
        if (tbSlowData3.getColumnCount() < 3) {
            return;
        }

        int modelRow = tbSlowData3.convertRowIndexToModel(selectedViewRow);
        int variableModelCol = tbSlowData3.convertColumnIndexToModel(1); // variable
        int valueModelCol = tbSlowData3.convertColumnIndexToModel(2);    // value
        Object variable = tbSlowData3.getModel().getValueAt(modelRow, variableModelCol);
        Object value = tbSlowData3.getModel().getValueAt(modelRow, valueModelCol);

        StringBuilder builder = new StringBuilder();
        if (variable != null) {
            builder.append(variable.toString());
        }
        builder.append('\t');
        if (value != null) {
            builder.append(value.toString());
        }

        java.awt.datatransfer.StringSelection selection = new java.awt.datatransfer.StringSelection(builder.toString());
        java.awt.Toolkit.getDefaultToolkit().getSystemClipboard().setContents(selection, null);
    }

    @SuppressWarnings("unchecked")
    private javax.swing.JComboBox<String>[] getChannelComboBoxes() {
        return new javax.swing.JComboBox[] {
            comboSelectData1, comboSelectData2, comboSelectData3, comboSelectData4, comboSelectData5,
            comboSelectData6, comboSelectData7, comboSelectData8, comboSelectData9, comboSelectData10,
            comboSelectData11, comboSelectData12, comboSelectData13, comboSelectData14, comboSelectData15,
            comboSelectData16, comboSelectData17, comboSelectData18, comboSelectData19, comboSelectData20
        };
    }

    private javax.swing.JTextField[] getScaleTextFields() {
        return new javax.swing.JTextField[] {
            txtScaleCH1, txtScaleCH2, txtScaleCH3, txtScaleCH4, txtScaleCH5,
            txtScaleCH6, txtScaleCH7, txtScaleCH8, txtScaleCH9, txtScaleCH10,
            txtScaleCH11, txtScaleCH12, txtScaleCH13, txtScaleCH14, txtScaleCH15,
            txtScaleCH16, txtScaleCH17, txtScaleCH18, txtScaleCH19, txtScaleCH20
        };
    }

    private javax.swing.JTextField[] getOffsetTextFields() {
        return new javax.swing.JTextField[] {
            txtOffsetCH1, txtOffsetCH2, txtOffsetCH3, txtOffsetCH4, txtOffsetCH5,
            txtOffsetCH6, txtOffsetCH7, txtOffsetCH8, txtOffsetCH9, txtOffsetCH10,
            txtOffsetCH11, txtOffsetCH12, txtOffsetCH13, txtOffsetCH14, txtOffsetCH15,
            txtOffsetCH16, txtOffsetCH17, txtOffsetCH18, txtOffsetCH19, txtOffsetCH20
        };
    }

    public javax.swing.JToggleButton[] getChannelVisibilityButtons() {
        return channelVisibilityButtons;
    }

    public javax.swing.JButton getBtnDisableAllChannels() {
        return btnDisableAllChannels;
    }

    public javax.swing.JButton getBtnEnableAllChannels() {
        return btnEnableAllChannels;
    }

    private static String toHex(java.awt.Color color) {
        return String.format("#%02X%02X%02X", color.getRed(), color.getGreen(), color.getBlue());
    }
}
