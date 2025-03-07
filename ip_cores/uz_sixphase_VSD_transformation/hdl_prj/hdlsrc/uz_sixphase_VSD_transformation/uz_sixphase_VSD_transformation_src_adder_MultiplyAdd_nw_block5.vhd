-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_sixphase_VSD_transformation\hdl_prj\hdlsrc\uz_sixphase_VSD_transformation\uz_sixphase_VSD_transformation_src_adder_MultiplyAdd_nw_block5.vhd
-- Created: 2022-10-17 10:15:35
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_sixphase_VSD_transformation_src_adder_MultiplyAdd_nw_block5
-- Source Path: 
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_sixphase_VSD_transformation_src_adder_MultiplyAdd_nw_block5 IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        in0                               :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En17
        in1                               :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
        in2                               :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
        globalSchedule                    :   IN    std_logic;
        out0                              :   OUT   std_logic_vector(45 DOWNTO 0)  -- sfix46_En33
        );
END uz_sixphase_VSD_transformation_src_adder_MultiplyAdd_nw_block5;


ARCHITECTURE rtl OF uz_sixphase_VSD_transformation_src_adder_MultiplyAdd_nw_block5 IS

  -- Signals
  SIGNAL enb_gated                        : std_logic;
  SIGNAL in2_signed                       : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL MatrixMultiply_1_0               : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL MatrixMultiply_1_0_1             : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL in0_signed                       : signed(17 DOWNTO 0);  -- sfix18_En17
  SIGNAL Constant1_out1t_1                : signed(17 DOWNTO 0);  -- sfix18_En17
  SIGNAL in1_signed                       : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL Mux4_out1                        : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL mulOutput                        : signed(44 DOWNTO 0);  -- sfix45_En33
  SIGNAL mulOutput_1                      : signed(44 DOWNTO 0);  -- sfix45_En33
  SIGNAL alpha_adder_MultiplyAdd_add_add_cast : signed(45 DOWNTO 0);  -- sfix46_En33
  SIGNAL alpha_adder_MultiplyAdd_add_add_cast_1 : signed(45 DOWNTO 0);  -- sfix46_En33
  SIGNAL MatrixMultiply_1_0_2             : signed(45 DOWNTO 0);  -- sfix46_En33
  SIGNAL MatrixMultiply_1_0_3             : signed(45 DOWNTO 0);  -- sfix46_En33
  SIGNAL MatrixMultiply_1_0_bypass        : signed(45 DOWNTO 0);  -- sfix46_En33
  SIGNAL MatrixMultiply_1_0_last_value    : signed(45 DOWNTO 0);  -- sfix46_En33

  ATTRIBUTE use_dsp : string;

  ATTRIBUTE use_dsp OF mulOutput : SIGNAL IS "yes";

BEGIN
  enb_gated <= globalSchedule AND enb;

  in2_signed <= signed(in2);

  HwModeRegister2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        MatrixMultiply_1_0 <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        MatrixMultiply_1_0 <= in2_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister2_process;


  HwModeRegister_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        MatrixMultiply_1_0_1 <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        MatrixMultiply_1_0_1 <= MatrixMultiply_1_0;
      END IF;
    END IF;
  END PROCESS HwModeRegister_process;


  in0_signed <= signed(in0);

  HwModeRegister_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Constant1_out1t_1 <= to_signed(16#00000#, 18);
      ELSIF enb_gated = '1' THEN
        Constant1_out1t_1 <= in0_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister_1_process;


  in1_signed <= signed(in1);

  HwModeRegister1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Mux4_out1 <= to_signed(16#0000000#, 27);
      ELSIF enb_gated = '1' THEN
        Mux4_out1 <= in1_signed;
      END IF;
    END IF;
  END PROCESS HwModeRegister1_process;


  mulOutput <= Constant1_out1t_1 * Mux4_out1;

  HwModeRegister_2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        mulOutput_1 <= to_signed(0, 45);
      ELSIF enb_gated = '1' THEN
        mulOutput_1 <= mulOutput;
      END IF;
    END IF;
  END PROCESS HwModeRegister_2_process;


  alpha_adder_MultiplyAdd_add_add_cast <= resize(MatrixMultiply_1_0_1 & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0', 46);
  alpha_adder_MultiplyAdd_add_add_cast_1 <= resize(mulOutput_1, 46);
  MatrixMultiply_1_0_2 <= alpha_adder_MultiplyAdd_add_add_cast + alpha_adder_MultiplyAdd_add_add_cast_1;

  HwModeRegister_3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        MatrixMultiply_1_0_3 <= to_signed(0, 46);
      ELSIF enb_gated = '1' THEN
        MatrixMultiply_1_0_3 <= MatrixMultiply_1_0_2;
      END IF;
    END IF;
  END PROCESS HwModeRegister_3_process;


  out0_bypass_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        MatrixMultiply_1_0_last_value <= to_signed(0, 46);
      ELSIF enb_gated = '1' THEN
        MatrixMultiply_1_0_last_value <= MatrixMultiply_1_0_bypass;
      END IF;
    END IF;
  END PROCESS out0_bypass_process;


  
  MatrixMultiply_1_0_bypass <= MatrixMultiply_1_0_last_value WHEN globalSchedule = '0' ELSE
      MatrixMultiply_1_0_3;

  out0 <= std_logic_vector(MatrixMultiply_1_0_bypass);

END rtl;

