-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj7/hdlsrc/uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph3_src_Line_Line_to_Phase_voltage.vhd
-- Created: 2022-06-04 17:38:56
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_9ph3_src_Line_Line_to_Phase_voltage
-- Source Path: uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/Line-Line to Phase voltage
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.uz_pmsm_model_9ph3_src_uz_pmsm_model_9ph_pkg.ALL;

ENTITY uz_pmsm_model_9ph3_src_Line_Line_to_Phase_voltage IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb_1_20_0                        :   IN    std_logic;
        In1                               :   IN    vector_of_std_logic_vector25(0 TO 2);  -- sfix25_En12 [3]
        Out1                              :   OUT   vector_of_std_logic_vector25(0 TO 2)  -- sfix25_En12 [3]
        );
END uz_pmsm_model_9ph3_src_Line_Line_to_Phase_voltage;


ARCHITECTURE rtl OF uz_pmsm_model_9ph3_src_Line_Line_to_Phase_voltage IS

  -- Component Declarations
  COMPONENT uz_pmsm_model_9ph3_src_abc_to_alpha_beta_0
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb_1_20_0                      :   IN    std_logic;
          a_b_c                           :   IN    vector_of_std_logic_vector25(0 TO 2);  -- sfix25_En12 [3]
          alpha_beta_0                    :   OUT   vector_of_std_logic_vector25(0 TO 2)  -- sfix25_En12 [3]
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph3_src_alpha_beta_0_to_abc
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb_1_20_0                      :   IN    std_logic;
          alpha_beta_0                    :   IN    vector_of_std_logic_vector25(0 TO 2);  -- sfix25_En12 [3]
          a_b_c                           :   OUT   vector_of_std_logic_vector25(0 TO 2)  -- sfix25_En12 [3]
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_pmsm_model_9ph3_src_abc_to_alpha_beta_0
    USE ENTITY work.uz_pmsm_model_9ph3_src_abc_to_alpha_beta_0(rtl);

  FOR ALL : uz_pmsm_model_9ph3_src_alpha_beta_0_to_abc
    USE ENTITY work.uz_pmsm_model_9ph3_src_alpha_beta_0_to_abc(rtl);

  -- Signals
  SIGNAL abc_to_alpha_beta_0_out1_signed  : vector_of_std_logic_vector25(0 TO 2);  -- ufix25 [3]
  SIGNAL abc_to_alpha_beta_0_out1_0       : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_C2ReIm_1_C2ReIm_A        : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Constant1_out1_re                : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Constant1_out1_im                : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL HwModeRegister1_reg              : vector_of_signed18(0 TO 1);  -- sfix18 [2]
  SIGNAL HwModeRegister1_reg_next         : vector_of_signed18(0 TO 1);  -- sfix18_En16 [2]
  SIGNAL Product_C2ReIm_2_C2ReIm_A        : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product_mul_temp                 : signed(42 DOWNTO 0);  -- sfix43_En28
  SIGNAL Product_Re_AC                    : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_Re_AC_1                  : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL abc_to_alpha_beta_0_out1_1       : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_C2ReIm_1_C2ReIm_B        : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL HwModeRegister5_reg              : vector_of_signed18(0 TO 1);  -- sfix18 [2]
  SIGNAL HwModeRegister5_reg_next         : vector_of_signed18(0 TO 1);  -- sfix18_En16 [2]
  SIGNAL Product_C2ReIm_2_C2ReIm_B        : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product2_mul_temp                : signed(42 DOWNTO 0);  -- sfix43_En28
  SIGNAL Product_Re_BD                    : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_C2ReIm_1_C2ReIm_A_1      : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL HwModeRegister3_reg              : vector_of_signed18(0 TO 1);  -- sfix18 [2]
  SIGNAL HwModeRegister3_reg_next         : vector_of_signed18(0 TO 1);  -- sfix18_En16 [2]
  SIGNAL Product_C2ReIm_2_C2ReIm_B_1      : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product1_mul_temp                : signed(42 DOWNTO 0);  -- sfix43_En28
  SIGNAL Product_Im_AD                    : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_Im_AD_1                  : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_C2ReIm_1_C2ReIm_B_1      : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL HwModeRegister7_reg              : vector_of_signed18(0 TO 1);  -- sfix18 [2]
  SIGNAL HwModeRegister7_reg_next         : vector_of_signed18(0 TO 1);  -- sfix18_En16 [2]
  SIGNAL Product_C2ReIm_2_C2ReIm_A_1      : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product3_mul_temp                : signed(42 DOWNTO 0);  -- sfix43_En28
  SIGNAL Product_Im_BC                    : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_Re_BD_1                  : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL mulOutput                        : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Product_Im_BC_1                  : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL mulOutput_1                      : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Constant_out1                    : signed(24 DOWNTO 0);  -- sfix25_En12
  SIGNAL Mux4_out1                        : vector_of_signed25(0 TO 2);  -- sfix25_En12 [3]
  SIGNAL Mux4_out1_1                      : vector_of_std_logic_vector25(0 TO 2);  -- ufix25 [3]
  SIGNAL alpha_beta_0_to_abc_out1         : vector_of_std_logic_vector25(0 TO 2);  -- ufix25 [3]

BEGIN
  u_abc_to_alpha_beta_0 : uz_pmsm_model_9ph3_src_abc_to_alpha_beta_0
    PORT MAP( clk => clk,
              reset => reset,
              enb_1_20_0 => enb_1_20_0,
              a_b_c => In1,  -- sfix25_En12 [3]
              alpha_beta_0 => abc_to_alpha_beta_0_out1_signed  -- sfix25_En12 [3]
              );

  u_alpha_beta_0_to_abc : uz_pmsm_model_9ph3_src_alpha_beta_0_to_abc
    PORT MAP( clk => clk,
              reset => reset,
              enb_1_20_0 => enb_1_20_0,
              alpha_beta_0 => Mux4_out1_1,  -- sfix25_En12 [3]
              a_b_c => alpha_beta_0_to_abc_out1  -- sfix25_En12 [3]
              );

  abc_to_alpha_beta_0_out1_0 <= signed(abc_to_alpha_beta_0_out1_signed(0));

  HwModeRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_1_C2ReIm_A <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_C2ReIm_1_C2ReIm_A <= abc_to_alpha_beta_0_out1_0;
      END IF;
    END IF;
  END PROCESS HwModeRegister_process;


  Constant1_out1_re <= to_signed(16#08000#, 18);
  Constant1_out1_im <= to_signed(-16#049E7#, 18);

  HwModeRegister1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        HwModeRegister1_reg(0) <= to_signed(16#00000#, 18);
        HwModeRegister1_reg(1) <= to_signed(16#00000#, 18);
      ELSIF enb_1_20_0 = '1' THEN
        HwModeRegister1_reg(0) <= HwModeRegister1_reg_next(0);
        HwModeRegister1_reg(1) <= HwModeRegister1_reg_next(1);
      END IF;
    END IF;
  END PROCESS HwModeRegister1_process;

  Product_C2ReIm_2_C2ReIm_A <= HwModeRegister1_reg(1);
  HwModeRegister1_reg_next(0) <= Constant1_out1_re;
  HwModeRegister1_reg_next(1) <= HwModeRegister1_reg(0);

  Product_mul_temp <= Product_C2ReIm_1_C2ReIm_A * Product_C2ReIm_2_C2ReIm_A;
  Product_Re_AC <= Product_mul_temp(40 DOWNTO 16);

  PipelineRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Re_AC_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_Re_AC_1 <= Product_Re_AC;
      END IF;
    END IF;
  END PROCESS PipelineRegister_process;


  abc_to_alpha_beta_0_out1_1 <= signed(abc_to_alpha_beta_0_out1_signed(1));

  HwModeRegister4_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_1_C2ReIm_B <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_C2ReIm_1_C2ReIm_B <= abc_to_alpha_beta_0_out1_1;
      END IF;
    END IF;
  END PROCESS HwModeRegister4_process;


  HwModeRegister5_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        HwModeRegister5_reg(0) <= to_signed(16#00000#, 18);
        HwModeRegister5_reg(1) <= to_signed(16#00000#, 18);
      ELSIF enb_1_20_0 = '1' THEN
        HwModeRegister5_reg(0) <= HwModeRegister5_reg_next(0);
        HwModeRegister5_reg(1) <= HwModeRegister5_reg_next(1);
      END IF;
    END IF;
  END PROCESS HwModeRegister5_process;

  Product_C2ReIm_2_C2ReIm_B <= HwModeRegister5_reg(1);
  HwModeRegister5_reg_next(0) <= Constant1_out1_im;
  HwModeRegister5_reg_next(1) <= HwModeRegister5_reg(0);

  Product2_mul_temp <= Product_C2ReIm_1_C2ReIm_B * Product_C2ReIm_2_C2ReIm_B;
  Product_Re_BD <= Product2_mul_temp(40 DOWNTO 16);

  HwModeRegister2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_1_C2ReIm_A_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_C2ReIm_1_C2ReIm_A_1 <= abc_to_alpha_beta_0_out1_0;
      END IF;
    END IF;
  END PROCESS HwModeRegister2_process;


  HwModeRegister3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        HwModeRegister3_reg(0) <= to_signed(16#00000#, 18);
        HwModeRegister3_reg(1) <= to_signed(16#00000#, 18);
      ELSIF enb_1_20_0 = '1' THEN
        HwModeRegister3_reg(0) <= HwModeRegister3_reg_next(0);
        HwModeRegister3_reg(1) <= HwModeRegister3_reg_next(1);
      END IF;
    END IF;
  END PROCESS HwModeRegister3_process;

  Product_C2ReIm_2_C2ReIm_B_1 <= HwModeRegister3_reg(1);
  HwModeRegister3_reg_next(0) <= Constant1_out1_im;
  HwModeRegister3_reg_next(1) <= HwModeRegister3_reg(0);

  Product1_mul_temp <= Product_C2ReIm_1_C2ReIm_A_1 * Product_C2ReIm_2_C2ReIm_B_1;
  Product_Im_AD <= Product1_mul_temp(40 DOWNTO 16);

  PipelineRegister1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Im_AD_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_Im_AD_1 <= Product_Im_AD;
      END IF;
    END IF;
  END PROCESS PipelineRegister1_process;


  HwModeRegister6_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_1_C2ReIm_B_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_C2ReIm_1_C2ReIm_B_1 <= abc_to_alpha_beta_0_out1_1;
      END IF;
    END IF;
  END PROCESS HwModeRegister6_process;


  HwModeRegister7_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        HwModeRegister7_reg(0) <= to_signed(16#00000#, 18);
        HwModeRegister7_reg(1) <= to_signed(16#00000#, 18);
      ELSIF enb_1_20_0 = '1' THEN
        HwModeRegister7_reg(0) <= HwModeRegister7_reg_next(0);
        HwModeRegister7_reg(1) <= HwModeRegister7_reg_next(1);
      END IF;
    END IF;
  END PROCESS HwModeRegister7_process;

  Product_C2ReIm_2_C2ReIm_A_1 <= HwModeRegister7_reg(1);
  HwModeRegister7_reg_next(0) <= Constant1_out1_re;
  HwModeRegister7_reg_next(1) <= HwModeRegister7_reg(0);

  Product3_mul_temp <= Product_C2ReIm_1_C2ReIm_B_1 * Product_C2ReIm_2_C2ReIm_A_1;
  Product_Im_BC <= Product3_mul_temp(40 DOWNTO 16);

  PipelineRegister2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Re_BD_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_Re_BD_1 <= Product_Re_BD;
      END IF;
    END IF;
  END PROCESS PipelineRegister2_process;


  mulOutput <= Product_Re_AC_1 - Product_Re_BD_1;

  PipelineRegister3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Im_BC_1 <= to_signed(16#0000000#, 25);
      ELSIF enb_1_20_0 = '1' THEN
        Product_Im_BC_1 <= Product_Im_BC;
      END IF;
    END IF;
  END PROCESS PipelineRegister3_process;


  mulOutput_1 <= Product_Im_AD_1 + Product_Im_BC_1;

  Constant_out1 <= to_signed(16#0000000#, 25);

  Mux4_out1(0) <= mulOutput;
  Mux4_out1(1) <= mulOutput_1;
  Mux4_out1(2) <= Constant_out1;

  outputgen: FOR k IN 0 TO 2 GENERATE
    Mux4_out1_1(k) <= std_logic_vector(Mux4_out1(k));
  END GENERATE;

  Out1 <= alpha_beta_0_to_abc_out1;

END rtl;
