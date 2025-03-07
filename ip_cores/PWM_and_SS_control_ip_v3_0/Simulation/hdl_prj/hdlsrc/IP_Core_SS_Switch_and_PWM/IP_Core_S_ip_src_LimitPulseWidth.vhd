-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\IP_Core_SS_Switch_and_PWM\IP_Core_S_ip_src_LimitPulseWidth.vhd
-- Created: 2018-10-01 12:50:34
-- 
-- Generated by MATLAB 9.4 and HDL Coder 3.12
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: IP_Core_S_ip_src_LimitPulseWidth
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/LimitPulseWidth
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY IP_Core_S_ip_src_LimitPulseWidth IS
  PORT( ref_sig                           :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En10
        min_pulse_width                   :   IN    std_logic_vector(7 DOWNTO 0);  -- uint8
        ref_sig_limit                     :   OUT   std_logic_vector(17 DOWNTO 0)  -- ufix18_En10
        );
END IP_Core_S_ip_src_LimitPulseWidth;


ARCHITECTURE rtl OF IP_Core_S_ip_src_LimitPulseWidth IS

  -- Signals
  SIGNAL ref_sig_signed                   : signed(17 DOWNTO 0);  -- sfix18_En10
  SIGNAL Constant_out1                    : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL min_pulse_width_unsigned         : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL Add_sub_cast                     : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Add_sub_cast_1                   : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Add_sub_temp                     : signed(8 DOWNTO 0);  -- sfix9
  SIGNAL Add_out1                         : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Relational_Operator_1_cast       : signed(18 DOWNTO 0);  -- sfix19_En10
  SIGNAL Relational_Operator_1_cast_1     : signed(18 DOWNTO 0);  -- sfix19_En10
  SIGNAL Relational_Operator_relop1       : std_logic;
  SIGNAL dtc_out                          : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Saturation_out1                  : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Relational_Operator1_1_cast      : signed(18 DOWNTO 0);  -- sfix19_En10
  SIGNAL Relational_Operator1_1_cast_1    : signed(18 DOWNTO 0);  -- sfix19_En10
  SIGNAL Relational_Operator1_relop1      : std_logic;
  SIGNAL Logical_Operator_out1            : std_logic;
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Constant1_out1                   : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL ref_sig_dtc                      : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Constant2_out1                   : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Switch1_out1                     : unsigned(17 DOWNTO 0);  -- ufix18_En10
  SIGNAL Switch6_out1                     : unsigned(17 DOWNTO 0);  -- ufix18_En10

BEGIN
  -- Set pulse width in percent

  ref_sig_signed <= signed(ref_sig);

  Constant_out1 <= to_unsigned(16#64#, 8);

  min_pulse_width_unsigned <= unsigned(min_pulse_width);

  Add_sub_cast <= signed(resize(Constant_out1, 9));
  Add_sub_cast_1 <= signed(resize(min_pulse_width_unsigned, 9));
  Add_sub_temp <= Add_sub_cast - Add_sub_cast_1;
  Add_out1 <= unsigned(Add_sub_temp(7 DOWNTO 0) & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0');

  Relational_Operator_1_cast <= resize(ref_sig_signed, 19);
  Relational_Operator_1_cast_1 <= signed(resize(Add_out1, 19));
  
  Relational_Operator_relop1 <= '1' WHEN Relational_Operator_1_cast > Relational_Operator_1_cast_1 ELSE
      '0';

  dtc_out <= min_pulse_width_unsigned & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0';

  
  Saturation_out1 <= to_unsigned(16#0C400#, 18) WHEN dtc_out > to_unsigned(16#0C400#, 18) ELSE
      to_unsigned(16#00400#, 18) WHEN dtc_out < to_unsigned(16#00400#, 18) ELSE
      dtc_out;

  Relational_Operator1_1_cast <= resize(ref_sig_signed, 19);
  Relational_Operator1_1_cast_1 <= signed(resize(Saturation_out1, 19));
  
  Relational_Operator1_relop1 <= '1' WHEN Relational_Operator1_1_cast < Relational_Operator1_1_cast_1 ELSE
      '0';

  Logical_Operator_out1 <= Relational_Operator_relop1 OR Relational_Operator1_relop1;

  
  switch_compare_1 <= '1' WHEN Logical_Operator_out1 > '0' ELSE
      '0';

  
  switch_compare_1_1 <= '1' WHEN Relational_Operator1_relop1 > '0' ELSE
      '0';

  Constant1_out1 <= to_unsigned(16#19400#, 18);

  ref_sig_dtc <= unsigned(ref_sig_signed);

  Constant2_out1 <= to_unsigned(16#00000#, 18);

  
  Switch1_out1 <= Constant1_out1 WHEN switch_compare_1_1 = '0' ELSE
      Constant2_out1;

  
  Switch6_out1 <= ref_sig_dtc WHEN switch_compare_1 = '0' ELSE
      Switch1_out1;

  ref_sig_limit <= std_logic_vector(Switch6_out1);

END rtl;

