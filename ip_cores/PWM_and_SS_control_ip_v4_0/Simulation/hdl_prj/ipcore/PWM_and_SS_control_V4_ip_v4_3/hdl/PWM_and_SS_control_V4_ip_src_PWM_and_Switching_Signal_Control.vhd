-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\IP_Core_SS_Switch_and_PWM\PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control.vhd
-- Created: 2023-10-25 14:50:38
-- 
-- Generated by MATLAB 9.14 and HDL Coder 4.1
-- 
-- 
-- -------------------------------------------------------------
-- Rate and Clocking Details
-- -------------------------------------------------------------
-- Model base rate: 1e-08
-- Target subsystem base rate: 1e-08
-- 
-- 
-- Clock Enable  Sample Time
-- -------------------------------------------------------------
-- ce_out        1e-08
-- -------------------------------------------------------------
-- 
-- 
-- Output Signal                 Clock Enable  Sample Time
-- -------------------------------------------------------------
-- SS0_OUT                       ce_out        1e-08
-- SS1_OUT                       ce_out        1e-08
-- SS2_OUT                       ce_out        1e-08
-- SS3_OUT                       ce_out        1e-08
-- SS4_OUT                       ce_out        1e-08
-- SS5_OUT                       ce_out        1e-08
-- PWM_en_rd_AXI                 ce_out        1e-08
-- PWM_f_carrier_kHz_rd_AXI      ce_out        1e-08
-- PWM_T_carrier_us_rd_AXI       ce_out        1e-08
-- PWM_min_pulse_width_rd_AXI    ce_out        1e-08
-- PWM_enb_out                   ce_out        1e-08
-- Mode_rd_AXI                   ce_out        1e-08
-- Triangular_Max                ce_out        1e-08
-- Triangular_Min                ce_out        1e-08
-- triangle_out                  ce_out        1e-08
-- dir_out                       ce_out        1e-08
-- applied_new_reference_value   ce_out        1e-08
-- -------------------------------------------------------------
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control_pkg.ALL;

ENTITY PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        clk_enable                        :   IN    std_logic;
        PWM_en_AXI                        :   IN    std_logic;
        Mode_AXI                          :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        Scal_f_carrier_AXI                :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25_En26
        Scal_T_carrier_AXI                :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25
        PWM_min_pulse_width_AXI           :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        m_u1_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        m_u2_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        m_u3_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        m_u1_norm_AXI                     :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        m_u2_norm_AXI                     :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        m_u3_norm_AXI                     :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        SS0_IN_External                   :   IN    std_logic;
        SS1_IN_External                   :   IN    std_logic;
        SS2_IN_External                   :   IN    std_logic;
        SS3_IN_External                   :   IN    std_logic;
        SS4_IN_External                   :   IN    std_logic;
        SS5_IN_External                   :   IN    std_logic;
        TriState_HB1_AXI                  :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        TriState_HB2_AXI                  :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        TriState_HB3_AXI                  :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        triangle_in                       :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        count_src_ext_AXI                 :   IN    std_logic;
        triangle_shift_HB1_AXI            :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        triangle_shift_HB2_AXI            :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        triangle_shift_HB3_AXI            :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        PWM_trigger_source_AXI            :   IN    std_logic_vector(31 DOWNTO 0);  -- uint32
        pwm_counter_rst                   :   IN    std_logic;
        ce_out                            :   OUT   std_logic;
        SS0_OUT                           :   OUT   std_logic;
        SS1_OUT                           :   OUT   std_logic;
        SS2_OUT                           :   OUT   std_logic;
        SS3_OUT                           :   OUT   std_logic;
        SS4_OUT                           :   OUT   std_logic;
        SS5_OUT                           :   OUT   std_logic;
        PWM_en_rd_AXI                     :   OUT   std_logic;
        PWM_f_carrier_kHz_rd_AXI          :   OUT   std_logic_vector(24 DOWNTO 0);  -- ufix25_En26
        PWM_T_carrier_us_rd_AXI           :   OUT   std_logic_vector(24 DOWNTO 0);  -- ufix25
        PWM_min_pulse_width_rd_AXI        :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        PWM_enb_out                       :   OUT   std_logic;
        Mode_rd_AXI                       :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        Triangular_Max                    :   OUT   std_logic;
        Triangular_Min                    :   OUT   std_logic;
        triangle_out                      :   OUT   std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        dir_out                           :   OUT   std_logic;
        applied_new_reference_value       :   OUT   std_logic
        );
END PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control;


ARCHITECTURE rtl OF PWM_and_SS_control_V4_ip_src_PWM_and_Switching_Signal_Control IS

  -- Component Declarations
  COMPONENT PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          U                               :   IN    std_logic;
          Y                               :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT PWM_and_SS_control_V4_ip_src_GenPWM
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          PWM_en_AXI                      :   IN    std_logic;
          f_carrier_kHz_AXI               :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25_En26
          T_carrier_us_AXI                :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25
          min_pulse_width_AXI             :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
          U1_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
          U2_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
          U3_norm                         :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
          triangle_in                     :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
          count_src_ext_AXI               :   IN    std_logic;
          triangle_shift_HB1_AXI          :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
          triangle_shift_HB2_AXI          :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
          triangle_shift_HB3_AXI          :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
          PWM_trigger_source_AXI          :   IN    std_logic_vector(31 DOWNTO 0);  -- uint32
          counter_reset                   :   IN    std_logic;
          S1                              :   OUT   std_logic;  -- ufix1
          S2                              :   OUT   std_logic;  -- ufix1
          S3                              :   OUT   std_logic;  -- ufix1
          S4                              :   OUT   std_logic;  -- ufix1
          S5                              :   OUT   std_logic;  -- ufix1
          S6                              :   OUT   std_logic;  -- ufix1
          PWM_en_rd_AXI                   :   OUT   std_logic;
          f_carrier_kHz_rd_AXI            :   OUT   std_logic_vector(24 DOWNTO 0);  -- ufix25_En26
          T_carrier_us_rd_AXI             :   OUT   std_logic_vector(24 DOWNTO 0);  -- ufix25
          min_pulse_width_rd_AXI          :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
          enb_out                         :   OUT   std_logic;
          Triangle_Max                    :   OUT   std_logic;
          Triangle_Min                    :   OUT   std_logic;
          triangle_out                    :   OUT   std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
          dir_out                         :   OUT   std_logic;
          applied_new_reference_value     :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT PWM_and_SS_control_V4_ip_src_VSI_Control_Signal_Switch
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          Switch_AXI                      :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          SS0_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS1_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS2_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS3_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS4_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS5_IN_PWM                      :   IN    std_logic;  -- ufix1
          SS0_IN_External                 :   IN    std_logic;
          SS1_IN_External                 :   IN    std_logic;
          SS2_IN_External                 :   IN    std_logic;
          SS3_IN_External                 :   IN    std_logic;
          SS4_IN_External                 :   IN    std_logic;
          SS5_IN_External                 :   IN    std_logic;
          TriState_HB1_AXI                :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          TriState_HB2_AXI                :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          TriState_HB3_AXI                :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          SS0_OUT                         :   OUT   std_logic;
          SS1_OUT                         :   OUT   std_logic;
          SS2_OUT                         :   OUT   std_logic;
          SS3_OUT                         :   OUT   std_logic;
          SS4_OUT                         :   OUT   std_logic;
          SS5_OUT                         :   OUT   std_logic
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive
    USE ENTITY work.PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive(rtl);

  FOR ALL : PWM_and_SS_control_V4_ip_src_GenPWM
    USE ENTITY work.PWM_and_SS_control_V4_ip_src_GenPWM(rtl);

  FOR ALL : PWM_and_SS_control_V4_ip_src_VSI_Control_Signal_Switch
    USE ENTITY work.PWM_and_SS_control_V4_ip_src_VSI_Control_Signal_Switch(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL Mode_AXI_unsigned                : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL m_u1_norm_AXI_signed             : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL m_u1_norm_signed                 : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL Switch7_out1                     : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL m_u2_norm_AXI_signed             : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL m_u2_norm_signed                 : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL Switch8_out1                     : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL m_u3_norm_AXI_signed             : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL m_u3_norm_signed                 : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL Switch9_out1                     : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL Detect_Rise_Positive_out1        : std_logic;
  SIGNAL GenPWM_out1                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out2                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out3                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out4                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out5                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out6                      : std_logic;  -- ufix1
  SIGNAL GenPWM_out7                      : std_logic;
  SIGNAL GenPWM_out8                      : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL GenPWM_out9                      : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL GenPWM_out10                     : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL GenPWM_out11                     : std_logic;
  SIGNAL GenPWM_out12                     : std_logic;
  SIGNAL GenPWM_out13                     : std_logic;
  SIGNAL GenPWM_out14                     : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL GenPWM_out15                     : std_logic;
  SIGNAL GenPWM_out16                     : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out1   : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out2   : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out3   : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out4   : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out5   : std_logic;
  SIGNAL VSI_Control_Signal_Switch_out6   : std_logic;
  SIGNAL delayMatch_reg                   : vector_of_unsigned2(0 TO 1);  -- ufix2 [2]
  SIGNAL Mode_AXI_1                       : unsigned(1 DOWNTO 0);  -- ufix2

BEGIN
  -- This PWM block can be replaced by an SVM,
  -- if required.
  -- - The PWM frequency must be between 100 Hz and 100 kHz, otherwise the counter end values must be extended/checked.
  -- - Asymetrical Regular Sampled is used regarding to Grahame Holmes. 
  -- - An up-down-counter is used.
  -- - A flag for 1 cycle is outputet at the counter maximum and minimum value for triggering subsequent blocks or interrupts.
  -- - TriState flags can be used to set both switches of one phase-leg to an off-state.
  -- Set pulse width in percent

  u_Detect_Rise_Positive : PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              U => pwm_counter_rst,
              Y => Detect_Rise_Positive_out1
              );

  u_GenPWM : PWM_and_SS_control_V4_ip_src_GenPWM
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              PWM_en_AXI => PWM_en_AXI,
              f_carrier_kHz_AXI => Scal_f_carrier_AXI,  -- ufix25_En26
              T_carrier_us_AXI => Scal_T_carrier_AXI,  -- ufix25
              min_pulse_width_AXI => PWM_min_pulse_width_AXI,  -- sfix18_En16
              U1_norm => std_logic_vector(Switch7_out1),  -- sfix14_En12
              U2_norm => std_logic_vector(Switch8_out1),  -- sfix14_En12
              U3_norm => std_logic_vector(Switch9_out1),  -- sfix14_En12
              triangle_in => triangle_in,  -- ufix18_En17
              count_src_ext_AXI => count_src_ext_AXI,
              triangle_shift_HB1_AXI => triangle_shift_HB1_AXI,  -- ufix18_En17
              triangle_shift_HB2_AXI => triangle_shift_HB2_AXI,  -- ufix18_En17
              triangle_shift_HB3_AXI => triangle_shift_HB3_AXI,  -- ufix18_En17
              PWM_trigger_source_AXI => PWM_trigger_source_AXI,  -- uint32
              counter_reset => Detect_Rise_Positive_out1,
              S1 => GenPWM_out1,  -- ufix1
              S2 => GenPWM_out2,  -- ufix1
              S3 => GenPWM_out3,  -- ufix1
              S4 => GenPWM_out4,  -- ufix1
              S5 => GenPWM_out5,  -- ufix1
              S6 => GenPWM_out6,  -- ufix1
              PWM_en_rd_AXI => GenPWM_out7,
              f_carrier_kHz_rd_AXI => GenPWM_out8,  -- ufix25_En26
              T_carrier_us_rd_AXI => GenPWM_out9,  -- ufix25
              min_pulse_width_rd_AXI => GenPWM_out10,  -- sfix18_En16
              enb_out => GenPWM_out11,
              Triangle_Max => GenPWM_out12,
              Triangle_Min => GenPWM_out13,
              triangle_out => GenPWM_out14,  -- ufix18_En17
              dir_out => GenPWM_out15,
              applied_new_reference_value => GenPWM_out16
              );

  u_VSI_Control_Signal_Switch : PWM_and_SS_control_V4_ip_src_VSI_Control_Signal_Switch
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              Switch_AXI => Mode_AXI,  -- ufix2
              SS0_IN_PWM => GenPWM_out1,  -- ufix1
              SS1_IN_PWM => GenPWM_out2,  -- ufix1
              SS2_IN_PWM => GenPWM_out3,  -- ufix1
              SS3_IN_PWM => GenPWM_out4,  -- ufix1
              SS4_IN_PWM => GenPWM_out5,  -- ufix1
              SS5_IN_PWM => GenPWM_out6,  -- ufix1
              SS0_IN_External => SS0_IN_External,
              SS1_IN_External => SS1_IN_External,
              SS2_IN_External => SS2_IN_External,
              SS3_IN_External => SS3_IN_External,
              SS4_IN_External => SS4_IN_External,
              SS5_IN_External => SS5_IN_External,
              TriState_HB1_AXI => TriState_HB1_AXI,  -- ufix2
              TriState_HB2_AXI => TriState_HB2_AXI,  -- ufix2
              TriState_HB3_AXI => TriState_HB3_AXI,  -- ufix2
              SS0_OUT => VSI_Control_Signal_Switch_out1,
              SS1_OUT => VSI_Control_Signal_Switch_out2,
              SS2_OUT => VSI_Control_Signal_Switch_out3,
              SS3_OUT => VSI_Control_Signal_Switch_out4,
              SS4_OUT => VSI_Control_Signal_Switch_out5,
              SS5_OUT => VSI_Control_Signal_Switch_out6
              );

  Mode_AXI_unsigned <= unsigned(Mode_AXI);

  m_u1_norm_AXI_signed <= signed(m_u1_norm_AXI);

  m_u1_norm_signed <= signed(m_u1_norm);

  
  Switch7_out1 <= m_u1_norm_AXI_signed WHEN Mode_AXI_unsigned = to_unsigned(16#0#, 2) ELSE
      m_u1_norm_signed;

  m_u2_norm_AXI_signed <= signed(m_u2_norm_AXI);

  m_u2_norm_signed <= signed(m_u2_norm);

  
  Switch8_out1 <= m_u2_norm_AXI_signed WHEN Mode_AXI_unsigned = to_unsigned(16#0#, 2) ELSE
      m_u2_norm_signed;

  m_u3_norm_AXI_signed <= signed(m_u3_norm_AXI);

  m_u3_norm_signed <= signed(m_u3_norm);

  
  Switch9_out1 <= m_u3_norm_AXI_signed WHEN Mode_AXI_unsigned = to_unsigned(16#0#, 2) ELSE
      m_u3_norm_signed;

  enb <= clk_enable;

  delayMatch_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch_reg <= (OTHERS => to_unsigned(16#0#, 2));
      ELSIF enb = '1' THEN
        delayMatch_reg(0) <= Mode_AXI_unsigned;
        delayMatch_reg(1) <= delayMatch_reg(0);
      END IF;
    END IF;
  END PROCESS delayMatch_process;

  Mode_AXI_1 <= delayMatch_reg(1);

  Mode_rd_AXI <= std_logic_vector(Mode_AXI_1);

  ce_out <= clk_enable;

  SS0_OUT <= VSI_Control_Signal_Switch_out1;

  SS1_OUT <= VSI_Control_Signal_Switch_out2;

  SS2_OUT <= VSI_Control_Signal_Switch_out3;

  SS3_OUT <= VSI_Control_Signal_Switch_out4;

  SS4_OUT <= VSI_Control_Signal_Switch_out5;

  SS5_OUT <= VSI_Control_Signal_Switch_out6;

  PWM_en_rd_AXI <= GenPWM_out7;

  PWM_f_carrier_kHz_rd_AXI <= GenPWM_out8;

  PWM_T_carrier_us_rd_AXI <= GenPWM_out9;

  PWM_min_pulse_width_rd_AXI <= GenPWM_out10;

  PWM_enb_out <= GenPWM_out11;

  Triangular_Max <= GenPWM_out12;

  Triangular_Min <= GenPWM_out13;

  triangle_out <= GenPWM_out14;

  dir_out <= GenPWM_out15;

  applied_new_reference_value <= GenPWM_out16;

END rtl;
