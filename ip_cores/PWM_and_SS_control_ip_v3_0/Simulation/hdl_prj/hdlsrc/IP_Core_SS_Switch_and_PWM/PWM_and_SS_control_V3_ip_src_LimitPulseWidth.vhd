-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\IP_Core_SS_Switch_and_PWM\PWM_and_SS_control_V3_ip_src_LimitPulseWidth.vhd
-- Created: 2020-02-07 14:11:52
-- 
-- Generated by MATLAB 9.4 and HDL Coder 3.12
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_and_SS_control_V3_ip_src_LimitPulseWidth
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/LimitPulseWidth
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY PWM_and_SS_control_V3_ip_src_LimitPulseWidth IS
  PORT( ref_sig                           :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        min_pulse_width                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        ref_sig_limit                     :   OUT   std_logic_vector(17 DOWNTO 0)  -- sfix18_En16
        );
END PWM_and_SS_control_V3_ip_src_LimitPulseWidth;


ARCHITECTURE rtl OF PWM_and_SS_control_V3_ip_src_LimitPulseWidth IS

  -- Signals
  SIGNAL ref_sig_signed                   : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL Constant_out1                    : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL min_pulse_width_signed           : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Add_out1                         : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Relational_Operator_1_cast       : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Relational_Operator_relop1       : std_logic;
  SIGNAL Saturation_out1                  : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Relational_Operator1_1_cast      : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Relational_Operator1_relop1      : std_logic;
  SIGNAL Logical_Operator_out1            : std_logic;
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Constant1_out1                   : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL ref_sig_dtc                      : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Constant2_out1                   : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Switch1_out1                     : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Switch6_out1                     : signed(17 DOWNTO 0);  -- sfix18_En16

BEGIN
  -- Set pulse width between 0-1

  ref_sig_signed <= signed(ref_sig);

  Constant_out1 <= to_signed(16#10000#, 18);

  min_pulse_width_signed <= signed(min_pulse_width);

  Add_out1 <= Constant_out1 - min_pulse_width_signed;

  Relational_Operator_1_cast <= ref_sig_signed & '0' & '0' & '0' & '0';
  
  Relational_Operator_relop1 <= '1' WHEN Relational_Operator_1_cast > Add_out1 ELSE
      '0';

  
  Saturation_out1 <= to_signed(16#10000#, 18) WHEN min_pulse_width_signed > to_signed(16#10000#, 18) ELSE
      to_signed(16#00000#, 18) WHEN min_pulse_width_signed < to_signed(16#00000#, 18) ELSE
      min_pulse_width_signed;

  Relational_Operator1_1_cast <= ref_sig_signed & '0' & '0' & '0' & '0';
  
  Relational_Operator1_relop1 <= '1' WHEN Relational_Operator1_1_cast < Saturation_out1 ELSE
      '0';

  Logical_Operator_out1 <= Relational_Operator_relop1 OR Relational_Operator1_relop1;

  
  switch_compare_1 <= '1' WHEN Logical_Operator_out1 > '0' ELSE
      '0';

  
  switch_compare_1_1 <= '1' WHEN Relational_Operator1_relop1 > '0' ELSE
      '0';

  Constant1_out1 <= to_signed(16#1028F#, 18);

  ref_sig_dtc <= ref_sig_signed & '0' & '0' & '0' & '0';

  Constant2_out1 <= to_signed(16#00000#, 18);

  
  Switch1_out1 <= Constant1_out1 WHEN switch_compare_1_1 = '0' ELSE
      Constant2_out1;

  
  Switch6_out1 <= ref_sig_dtc WHEN switch_compare_1 = '0' ELSE
      Switch1_out1;

  ref_sig_limit <= std_logic_vector(Switch6_out1);

END rtl;

