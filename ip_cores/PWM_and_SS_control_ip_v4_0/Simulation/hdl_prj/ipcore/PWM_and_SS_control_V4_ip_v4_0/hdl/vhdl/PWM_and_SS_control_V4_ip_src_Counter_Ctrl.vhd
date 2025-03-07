-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\IP_Core_SS_Switch_and_PWM\PWM_and_SS_control_V4_ip_src_Counter_Ctrl.vhd
-- Created: 2022-05-09 15:08:08
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_and_SS_control_V4_ip_src_Counter_Ctrl
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/Counter Ctrl
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY PWM_and_SS_control_V4_ip_src_Counter_Ctrl IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        hdl_cnt                           :   IN    std_logic_vector(19 DOWNTO 0);  -- ufix20
        f_carrier_kHz                     :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25_En26
        T_carrier_us                      :   IN    std_logic_vector(24 DOWNTO 0);  -- ufix25
        dir_ctrl                          :   OUT   std_logic;
        triangle_sig                      :   OUT   std_logic_vector(17 DOWNTO 0);  -- ufix18_En17
        Period_CenterMax                  :   OUT   std_logic;
        Period_CenterMin                  :   OUT   std_logic
        );
END PWM_and_SS_control_V4_ip_src_Counter_Ctrl;


ARCHITECTURE rtl OF PWM_and_SS_control_V4_ip_src_Counter_Ctrl IS

  -- Signals
  SIGNAL hdl_cnt_unsigned                 : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL T_carrier_us_unsigned            : unsigned(24 DOWNTO 0);  -- ufix25
  SIGNAL Relational_Operator4_relop1      : std_logic;
  SIGNAL Constant11_out1                  : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL Relational_Operator5_relop1      : std_logic;
  SIGNAL Logical_Operator_out1            : std_logic;
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Constant14_out1                  : std_logic;
  SIGNAL Constant12_out1                  : std_logic;
  SIGNAL Switch7_out1                     : std_logic;
  SIGNAL Switch6_out1                     : std_logic;
  SIGNAL Delay6_out1                      : std_logic;
  SIGNAL f_carrier_kHz_unsigned           : unsigned(24 DOWNTO 0);  -- ufix25_En26
  SIGNAL Delay_out1                       : unsigned(24 DOWNTO 0);  -- ufix25_En26
  SIGNAL Product_mul_temp                 : unsigned(44 DOWNTO 0);  -- ufix45_En26
  SIGNAL Product_out1                     : unsigned(17 DOWNTO 0);  -- ufix18_En17
  SIGNAL Relational_Operator1_relop1      : std_logic;
  SIGNAL Constant1_out1                   : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL Relational_Operator2_relop1      : std_logic;

BEGIN
  -- if (hdl_cnt >= step_cnt)
  -- 	dir_ctrl = true;
  -- else if (hdl_cnt <= 0)
  -- 	dir_ctrl = false;
  -- else
  -- 	dir_ctrl = dir_ctrl;
  -- 
  -- scaling triangle amplitude to 100

  hdl_cnt_unsigned <= unsigned(hdl_cnt);

  T_carrier_us_unsigned <= unsigned(T_carrier_us);

  
  Relational_Operator4_relop1 <= '1' WHEN resize(hdl_cnt_unsigned, 25) >= T_carrier_us_unsigned ELSE
      '0';

  Constant11_out1 <= to_unsigned(16#00000#, 20);

  
  Relational_Operator5_relop1 <= '1' WHEN hdl_cnt_unsigned <= Constant11_out1 ELSE
      '0';

  Logical_Operator_out1 <= Relational_Operator4_relop1 OR Relational_Operator5_relop1;

  
  switch_compare_1 <= '1' WHEN Logical_Operator_out1 > '0' ELSE
      '0';

  
  switch_compare_1_1 <= '1' WHEN Relational_Operator4_relop1 > '0' ELSE
      '0';

  Constant14_out1 <= '1';

  Constant12_out1 <= '0';

  
  Switch7_out1 <= Constant14_out1 WHEN switch_compare_1_1 = '0' ELSE
      Constant12_out1;

  Delay6_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay6_out1 <= '0';
      ELSIF enb = '1' THEN
        Delay6_out1 <= Switch6_out1;
      END IF;
    END IF;
  END PROCESS Delay6_process;


  
  Switch6_out1 <= Delay6_out1 WHEN switch_compare_1 = '0' ELSE
      Switch7_out1;

  f_carrier_kHz_unsigned <= unsigned(f_carrier_kHz);

  Delay_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay_out1 <= to_unsigned(16#0000000#, 25);
      ELSIF enb = '1' THEN
        Delay_out1 <= f_carrier_kHz_unsigned;
      END IF;
    END IF;
  END PROCESS Delay_process;


  Product_mul_temp <= hdl_cnt_unsigned * Delay_out1;
  Product_out1 <= Product_mul_temp(26 DOWNTO 9);

  triangle_sig <= std_logic_vector(Product_out1);

  
  Relational_Operator1_relop1 <= '1' WHEN resize(hdl_cnt_unsigned, 25) = T_carrier_us_unsigned ELSE
      '0';

  Constant1_out1 <= to_unsigned(16#00000#, 20);

  
  Relational_Operator2_relop1 <= '1' WHEN hdl_cnt_unsigned = Constant1_out1 ELSE
      '0';

  dir_ctrl <= Switch6_out1;

  Period_CenterMax <= Relational_Operator1_relop1;

  Period_CenterMin <= Relational_Operator2_relop1;

END rtl;

