-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj/hdlsrc/IP_Core_SS_Switch_and_PWM/PWM_and_SS_control_V4_ip_src_Subsystem3.vhd
-- Created: 2023-10-12 16:25:24
-- 
-- Generated by MATLAB 9.14 and HDL Coder 4.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_and_SS_control_V4_ip_src_Subsystem3
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/Triangle shift/Subsystem3
-- Hierarchy Level: 3
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY PWM_and_SS_control_V4_ip_src_Subsystem3 IS
  PORT( triangle_in                       :   IN    std_logic_vector(19 DOWNTO 0);  -- sfix20_En17
        modified_triangle_shift           :   IN    std_logic_vector(19 DOWNTO 0);  -- sfix20_En17
        direction_up                      :   IN    std_logic;
        shifted_triangle_in_signal        :   OUT   std_logic_vector(20 DOWNTO 0)  -- sfix21_En17
        );
END PWM_and_SS_control_V4_ip_src_Subsystem3;


ARCHITECTURE rtl OF PWM_and_SS_control_V4_ip_src_Subsystem3 IS

  -- Signals
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL modified_triangle_shift_signed   : signed(19 DOWNTO 0);  -- sfix20_En17
  SIGNAL triangle_in_signed               : signed(19 DOWNTO 0);  -- sfix20_En17
  SIGNAL Relational_Operator6_relop1      : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Sum3_sub_cast                    : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum3_sub_cast_1                  : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum3_out1                        : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum4_add_cast                    : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum4_add_cast_1                  : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum4_out1                        : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum2_sub_cast                    : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum2_sub_cast_1                  : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Sum2_out1                        : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL Switch3_out1                     : signed(20 DOWNTO 0);  -- sfix21_En17
  SIGNAL sw_out1                          : signed(20 DOWNTO 0);  -- sfix21_En17

BEGIN
  
  switch_compare_1 <= '1' WHEN direction_up > '0' ELSE
      '0';

  modified_triangle_shift_signed <= signed(modified_triangle_shift);

  triangle_in_signed <= signed(triangle_in);

  
  Relational_Operator6_relop1 <= '1' WHEN triangle_in_signed <= modified_triangle_shift_signed ELSE
      '0';

  
  switch_compare_1_1 <= '1' WHEN Relational_Operator6_relop1 > '0' ELSE
      '0';

  Sum3_sub_cast <= resize(triangle_in_signed, 21);
  Sum3_sub_cast_1 <= resize(modified_triangle_shift_signed, 21);
  Sum3_out1 <= Sum3_sub_cast - Sum3_sub_cast_1;

  Sum4_add_cast <= resize(modified_triangle_shift_signed, 21);
  Sum4_add_cast_1 <= resize(triangle_in_signed, 21);
  Sum4_out1 <= Sum4_add_cast + Sum4_add_cast_1;

  Sum2_sub_cast <= resize(modified_triangle_shift_signed, 21);
  Sum2_sub_cast_1 <= resize(triangle_in_signed, 21);
  Sum2_out1 <= Sum2_sub_cast - Sum2_sub_cast_1;

  
  Switch3_out1 <= Sum3_out1 WHEN switch_compare_1_1 = '0' ELSE
      Sum2_out1;

  
  sw_out1 <= Sum4_out1 WHEN switch_compare_1 = '0' ELSE
      Switch3_out1;

  shifted_triangle_in_signal <= std_logic_vector(sw_out1);

END rtl;
