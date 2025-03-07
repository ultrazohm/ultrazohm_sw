-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\ThreeL_PWM_direct\PWM_SS_3L_ip_src_Modulator_c.vhd
-- Created: 2020-04-06 17:35:11
-- 
-- Generated by MATLAB 9.7 and HDL Coder 3.15
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: PWM_SS_3L_ip_src_Modulator_c
-- Source Path: ThreeL_PWM_direct/PWM_SS_Ctrl/GenPWM/Modulator_c
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.PWM_SS_3L_ip_src_PWM_SS_Ctrl_pkg.ALL;

ENTITY PWM_SS_3L_ip_src_Modulator_c IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        carrier_peak_count                :   IN    std_logic_vector(19 DOWNTO 0);  -- ufix20
        carrier_signal_pos                :   IN    std_logic_vector(19 DOWNTO 0);  -- ufix20
        carrier_signal_neg                :   IN    std_logic_vector(20 DOWNTO 0);  -- sfix21
        modulation_signal                 :   IN    std_logic_vector(13 DOWNTO 0);  -- sfix14_En12
        S                                 :   OUT   std_logic_vector(0 TO 1)  -- ufix1 [2]
        );
END PWM_SS_3L_ip_src_Modulator_c;


ARCHITECTURE rtl OF PWM_SS_3L_ip_src_Modulator_c IS

  -- Signals
  SIGNAL modulation_signal_signed         : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL modulation_signal_1              : signed(13 DOWNTO 0);  -- sfix14_En12
  SIGNAL carrier_peak_count_unsigned      : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL carrier_peak_count_1             : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL Multiply_cast                    : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL Multiply_mul_temp                : signed(34 DOWNTO 0);  -- sfix35_En12
  SIGNAL Multiply_cast_1                  : signed(33 DOWNTO 0);  -- sfix34_En12
  SIGNAL modulating_signal_in_clock_cycles : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL modulating_signal_in_clock_cycles_1 : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL carrier_signal_pos_unsigned      : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL reduced_reg                      : vector_of_unsigned20(0 TO 1);  -- ufix20 [2]
  SIGNAL carrier_positve                  : unsigned(19 DOWNTO 0);  -- ufix20
  SIGNAL Relational_Operator_1_cast       : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL Relational_Operator_relop1       : std_logic;
  SIGNAL carrier_signal_neg_signed        : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL reduced_reg_1                    : vector_of_signed21(0 TO 1);  -- sfix21 [2]
  SIGNAL carrier_negative                 : signed(20 DOWNTO 0);  -- sfix21
  SIGNAL Relational_Operator1_relop1      : std_logic;
  SIGNAL switch_compare_1                 : std_logic;
  SIGNAL Constant4_out1                   : std_logic_vector(0 TO 1);  -- ufix1 [2]
  SIGNAL AND_out1                         : std_logic;
  SIGNAL switch_compare_1_1               : std_logic;
  SIGNAL Constant1_out1                   : std_logic_vector(0 TO 1);  -- ufix1 [2]
  SIGNAL Switch1_out1                     : std_logic_vector(0 TO 1);  -- ufix1 [2]
  SIGNAL Constant2_out1                   : std_logic_vector(0 TO 1);  -- ufix1 [2]
  SIGNAL Switch7_out1                     : std_logic_vector(0 TO 1);  -- ufix1 [2]

BEGIN
  modulation_signal_signed <= signed(modulation_signal);

  HwModeRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        modulation_signal_1 <= to_signed(16#0000#, 14);
      ELSIF enb = '1' THEN
        modulation_signal_1 <= modulation_signal_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister_process;


  carrier_peak_count_unsigned <= unsigned(carrier_peak_count);

  HwModeRegister1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        carrier_peak_count_1 <= to_unsigned(16#00000#, 20);
      ELSIF enb = '1' THEN
        carrier_peak_count_1 <= carrier_peak_count_unsigned;
      END IF;
    END IF;
  END PROCESS HwModeRegister1_process;


  Multiply_cast <= signed(resize(carrier_peak_count_1, 21));
  Multiply_mul_temp <= modulation_signal_1 * Multiply_cast;
  Multiply_cast_1 <= Multiply_mul_temp(33 DOWNTO 0);
  modulating_signal_in_clock_cycles <= Multiply_cast_1(32 DOWNTO 12);

  PipelineRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        modulating_signal_in_clock_cycles_1 <= to_signed(16#000000#, 21);
      ELSIF enb = '1' THEN
        modulating_signal_in_clock_cycles_1 <= modulating_signal_in_clock_cycles;
      END IF;
    END IF;
  END PROCESS PipelineRegister_process;


  carrier_signal_pos_unsigned <= unsigned(carrier_signal_pos);

  reduced_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        reduced_reg <= (OTHERS => to_unsigned(16#00000#, 20));
      ELSIF enb = '1' THEN
        reduced_reg(0) <= carrier_signal_pos_unsigned;
        reduced_reg(1) <= reduced_reg(0);
      END IF;
    END IF;
  END PROCESS reduced_process;

  carrier_positve <= reduced_reg(1);

  Relational_Operator_1_cast <= signed(resize(carrier_positve, 21));
  
  Relational_Operator_relop1 <= '1' WHEN modulating_signal_in_clock_cycles_1 <= Relational_Operator_1_cast ELSE
      '0';

  carrier_signal_neg_signed <= signed(carrier_signal_neg);

  reduced_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        reduced_reg_1 <= (OTHERS => to_signed(16#000000#, 21));
      ELSIF enb = '1' THEN
        reduced_reg_1(0) <= carrier_signal_neg_signed;
        reduced_reg_1(1) <= reduced_reg_1(0);
      END IF;
    END IF;
  END PROCESS reduced_1_process;

  carrier_negative <= reduced_reg_1(1);

  
  Relational_Operator1_relop1 <= '1' WHEN modulating_signal_in_clock_cycles_1 >= carrier_negative ELSE
      '0';

  
  switch_compare_1 <= '1' WHEN Relational_Operator1_relop1 > '0' ELSE
      '0';

  Constant4_out1(0) <= '0';
  Constant4_out1(1) <= '0';

  AND_out1 <= Relational_Operator_relop1 AND Relational_Operator1_relop1;

  
  switch_compare_1_1 <= '1' WHEN AND_out1 > '0' ELSE
      '0';

  Constant1_out1(0) <= '1';
  Constant1_out1(1) <= '1';

  
  Switch1_out1 <= Constant4_out1 WHEN switch_compare_1 = '0' ELSE
      Constant1_out1;

  Constant2_out1(0) <= '0';
  Constant2_out1(1) <= '1';

  
  Switch7_out1 <= Switch1_out1 WHEN switch_compare_1_1 = '0' ELSE
      Constant2_out1;



  S <= Switch7_out1;

END rtl;

