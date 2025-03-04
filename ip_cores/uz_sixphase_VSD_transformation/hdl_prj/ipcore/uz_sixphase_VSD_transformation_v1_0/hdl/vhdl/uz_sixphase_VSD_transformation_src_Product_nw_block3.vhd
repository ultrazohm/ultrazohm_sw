-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_sixphase_VSD_transformation\hdl_prj\hdlsrc\uz_sixphase_VSD_transformation\uz_sixphase_VSD_transformation_src_Product_nw_block3.vhd
-- Created: 2022-10-17 10:15:35
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_sixphase_VSD_transformation_src_Product_nw_block3
-- Source Path: 
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_sixphase_VSD_transformation_src_Product_nw_block3 IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        in0                               :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
        in1                               :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        globalSchedule                    :   IN    std_logic;
        out0                              :   OUT   std_logic_vector(26 DOWNTO 0)  -- sfix27_En16
        );
END uz_sixphase_VSD_transformation_src_Product_nw_block3;


ARCHITECTURE rtl OF uz_sixphase_VSD_transformation_src_Product_nw_block3 IS

  -- Signals
  SIGNAL enb_gated                        : std_logic;
  SIGNAL in0_signed                       : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL Product_C2ReIm_1_C2ReIm_A        : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL in1_signed                       : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product_C2ReIm_2_C2ReIm_A        : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL Product_mul_temp                 : signed(44 DOWNTO 0);  -- sfix45_En32
  SIGNAL Product_Re_AC                    : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL Product_Re_AC_1                  : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL Product_Re_AC_bypass             : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL Product_Re_AC_last_value         : signed(26 DOWNTO 0);  -- sfix27_En16

BEGIN
  enb_gated <= globalSchedule AND enb;

  in0_signed <= signed(in0);

  HwModeRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_1_C2ReIm_A <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        Product_C2ReIm_1_C2ReIm_A <= in0_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister_process;


  in1_signed <= signed(in1);

  HwModeRegister1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_C2ReIm_2_C2ReIm_A <= to_signed(16#00000#, 18);
      ELSIF enb_gated = '1' THEN
        Product_C2ReIm_2_C2ReIm_A <= in1_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister1_process;


  Product_mul_temp <= Product_C2ReIm_1_C2ReIm_A * Product_C2ReIm_2_C2ReIm_A;
  Product_Re_AC <= Product_mul_temp(42 DOWNTO 16);

  PipelineRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Re_AC_1 <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        Product_Re_AC_1 <= Product_Re_AC;
      END IF;
    END IF;
  END PROCESS PipelineRegister_process;


  out0_bypass_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Product_Re_AC_last_value <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        Product_Re_AC_last_value <= Product_Re_AC_bypass;
      END IF;
    END IF;
  END PROCESS out0_bypass_process;


  
  Product_Re_AC_bypass <= Product_Re_AC_last_value WHEN globalSchedule = '0' ELSE
      Product_Re_AC_1;

  out0 <= std_logic_vector(Product_Re_AC_bypass);

END rtl;

