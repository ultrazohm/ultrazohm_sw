-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\IP_Core_SS_Switch_and_PWM\PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive.vhd
-- Created: 2023-10-25 14:50:38
-- 
-- Generated by MATLAB 9.14 and HDL Coder 4.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive
-- Source Path: IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Detect Rise Positive
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        U                                 :   IN    std_logic;
        Y                                 :   OUT   std_logic
        );
END PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive;


ARCHITECTURE rtl OF PWM_and_SS_control_V4_ip_src_Detect_Rise_Positive IS

  -- Signals
  SIGNAL U_k                              : std_logic;
  SIGNAL U_k_1                            : std_logic;
  SIGNAL FixPt_Relational_Operator_relop1 : std_logic;

BEGIN
  -- Edge
  -- U(k)

  
  U_k <= '1' WHEN U > '0' ELSE
      '0';

  -- Store in Global RAM
  Delay_Input1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        U_k_1 <= '0';
      ELSIF enb = '1' THEN
        U_k_1 <= U_k;
      END IF;
    END IF;
  END PROCESS Delay_Input1_process;


  
  FixPt_Relational_Operator_relop1 <= '1' WHEN U_k > U_k_1 ELSE
      '0';

  Y <= FixPt_Relational_Operator_relop1;

END rtl;
