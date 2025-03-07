-- -------------------------------------------------------------
-- 
-- File Name: uz_axi_testIP/hdlsrc/uz_axi_testIP/AXI_testI_ip_src_uz_axi_testIP.vhd
-- Created: 2021-04-18 13:18:01
-- 
-- Generated by MATLAB 9.9 and HDL Coder 3.17
-- 
-- 
-- -------------------------------------------------------------
-- Rate and Clocking Details
-- -------------------------------------------------------------
-- Model base rate: 0.2
-- Target subsystem base rate: 0.2
-- 
-- 
-- Clock Enable  Sample Time
-- -------------------------------------------------------------
-- ce_out        0.2
-- -------------------------------------------------------------
-- 
-- 
-- Output Signal                 Clock Enable  Sample Time
-- -------------------------------------------------------------
-- C_float_0                     ce_out        0.2
-- C_float_1                     ce_out        0.2
-- C_float_2                     ce_out        0.2
-- C_float_3                     ce_out        0.2
-- C_uint32                      ce_out        0.2
-- C_int32                       ce_out        0.2
-- C_fx_1_16_5                   ce_out        0.2
-- -------------------------------------------------------------
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: AXI_testI_ip_src_uz_axi_testIP
-- Source Path: uz_axi_testIP/uz_axi_testIP
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.AXI_testI_ip_src_uz_axi_testIP_pkg.ALL;

ENTITY AXI_testI_ip_src_uz_axi_testIP IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        clk_enable                        :   IN    std_logic;
        A_float_0                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        A_float_1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        A_float_2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        A_float_3                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        B_float_0                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        B_float_1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        B_float_2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        B_float_3                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        A_uint32                          :   IN    std_logic_vector(31 DOWNTO 0);  -- uint32
        B_uint32                          :   IN    std_logic_vector(31 DOWNTO 0);  -- uint32
        A_int32                           :   IN    std_logic_vector(31 DOWNTO 0);  -- int32
        B_int32                           :   IN    std_logic_vector(31 DOWNTO 0);  -- int32
        A_fx_1_16_5                       :   IN    std_logic_vector(15 DOWNTO 0);  -- sfix16_En5
        B_fx_1_16_5                       :   IN    std_logic_vector(15 DOWNTO 0);  -- sfix16_En5
        ce_out                            :   OUT   std_logic;
        C_float_0                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- single
        C_float_1                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- single
        C_float_2                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- single
        C_float_3                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- single
        C_uint32                          :   OUT   std_logic_vector(31 DOWNTO 0);  -- uint32
        C_int32                           :   OUT   std_logic_vector(31 DOWNTO 0);  -- int32
        C_fx_1_16_5                       :   OUT   std_logic_vector(15 DOWNTO 0)  -- sfix16_En5
        );
END AXI_testI_ip_src_uz_axi_testIP;


ARCHITECTURE rtl OF AXI_testI_ip_src_uz_axi_testIP IS

  -- Component Declarations
  COMPONENT AXI_testI_ip_src_nfp_mul_single
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_in2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT AXI_testI_ip_src_nfp_add_single
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          nfp_in1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_in2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : AXI_testI_ip_src_nfp_mul_single
    USE ENTITY work.AXI_testI_ip_src_nfp_mul_single(rtl);

  FOR ALL : AXI_testI_ip_src_nfp_add_single
    USE ENTITY work.AXI_testI_ip_src_nfp_add_single(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL A_float                          : vector_of_std_logic_vector32(0 TO 3);  -- ufix32 [4]
  SIGNAL Reshape_out1                     : matrix_of_std_logic_vector32(0 TO 1, 0 TO 1);  -- ufix32 [2x2]
  SIGNAL Reshape_out1t                    : matrix_of_std_logic_vector32(0 TO 1, 0 TO 1);  -- ufix32 [2x2]
  SIGNAL B_float                          : vector_of_std_logic_vector32(0 TO 3);  -- ufix32 [4]
  SIGNAL Reshape1_out1                    : matrix_of_std_logic_vector32(0 TO 1, 0 TO 1);  -- ufix32 [2x2]
  SIGNAL tmp_Matrix_Multiply_dotp_1       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_0       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_1_1     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_0_1     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_1_2     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_0_2     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_1_3     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL tmp_Matrix_Multiply_dotp_0_3     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Matrix_Multiply_out1             : matrix_of_std_logic_vector32(0 TO 1, 0 TO 1);  -- ufix32 [2x2]
  SIGNAL Reshape2_out1                    : vector_of_std_logic_vector32(0 TO 3);  -- ufix32 [4]
  SIGNAL A_uint32_unsigned                : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL Delay2_out1                      : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL B_uint32_unsigned                : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL Delay3_out1                      : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL Product_out1                     : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL delayMatch_reg                   : vector_of_unsigned32(0 TO 18);  -- ufix32 [19]
  SIGNAL delayMatch_reg_next              : vector_of_unsigned32(0 TO 18);  -- ufix32 [19]
  SIGNAL Product_out1_1                   : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL A_int32_signed                   : signed(31 DOWNTO 0);  -- int32
  SIGNAL Delay1_out1                      : signed(31 DOWNTO 0);  -- int32
  SIGNAL B_int32_signed                   : signed(31 DOWNTO 0);  -- int32
  SIGNAL Delay4_out1                      : signed(31 DOWNTO 0);  -- int32
  SIGNAL Product1_mul_temp                : signed(63 DOWNTO 0);  -- sfix64
  SIGNAL Product1_out1                    : signed(31 DOWNTO 0);  -- int32
  SIGNAL delayMatch1_reg                  : vector_of_signed32(0 TO 18);  -- sfix32 [19]
  SIGNAL delayMatch1_reg_next             : vector_of_signed32(0 TO 18);  -- sfix32 [19]
  SIGNAL Product1_out1_1                  : signed(31 DOWNTO 0);  -- int32
  SIGNAL A_fx_1_16_5_signed               : signed(15 DOWNTO 0);  -- sfix16_En5
  SIGNAL Delay5_out1                      : signed(15 DOWNTO 0);  -- sfix16_En5
  SIGNAL B_fx_1_16_5_signed               : signed(15 DOWNTO 0);  -- sfix16_En5
  SIGNAL Delay6_out1                      : signed(15 DOWNTO 0);  -- sfix16_En5
  SIGNAL Product2_mul_temp                : signed(31 DOWNTO 0);  -- sfix32_En10
  SIGNAL Product2_out1                    : signed(15 DOWNTO 0);  -- sfix16_En5
  SIGNAL delayMatch2_reg                  : vector_of_signed16(0 TO 18);  -- sfix16 [19]
  SIGNAL delayMatch2_reg_next             : vector_of_signed16(0 TO 18);  -- sfix16_En5 [19]
  SIGNAL Product2_out1_1                  : signed(15 DOWNTO 0);  -- sfix16_En5

BEGIN
  u_nfp_mul_comp : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(1, 0),  -- single
              nfp_in2 => Reshape1_out1(1, 0),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_1  -- single
              );

  u_nfp_mul_comp_1 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(0, 0),  -- single
              nfp_in2 => Reshape1_out1(0, 0),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_0  -- single
              );

  u_nfp_add_comp : AXI_testI_ip_src_nfp_add_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => tmp_Matrix_Multiply_dotp_1,  -- single
              nfp_in2 => tmp_Matrix_Multiply_dotp_0,  -- single
              nfp_out => Matrix_Multiply_out1(0, 0)  -- single
              );

  u_nfp_mul_comp_2 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(1, 1),  -- single
              nfp_in2 => Reshape1_out1(1, 0),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_1_1  -- single
              );

  u_nfp_mul_comp_3 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(0, 1),  -- single
              nfp_in2 => Reshape1_out1(0, 0),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_0_1  -- single
              );

  u_nfp_add_comp_1 : AXI_testI_ip_src_nfp_add_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => tmp_Matrix_Multiply_dotp_1_1,  -- single
              nfp_in2 => tmp_Matrix_Multiply_dotp_0_1,  -- single
              nfp_out => Matrix_Multiply_out1(1, 0)  -- single
              );

  u_nfp_mul_comp_4 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(1, 0),  -- single
              nfp_in2 => Reshape1_out1(1, 1),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_1_2  -- single
              );

  u_nfp_mul_comp_5 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(0, 0),  -- single
              nfp_in2 => Reshape1_out1(0, 1),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_0_2  -- single
              );

  u_nfp_add_comp_2 : AXI_testI_ip_src_nfp_add_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => tmp_Matrix_Multiply_dotp_1_2,  -- single
              nfp_in2 => tmp_Matrix_Multiply_dotp_0_2,  -- single
              nfp_out => Matrix_Multiply_out1(0, 1)  -- single
              );

  u_nfp_mul_comp_6 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(1, 1),  -- single
              nfp_in2 => Reshape1_out1(1, 1),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_1_3  -- single
              );

  u_nfp_mul_comp_7 : AXI_testI_ip_src_nfp_mul_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => Reshape_out1t(0, 1),  -- single
              nfp_in2 => Reshape1_out1(0, 1),  -- single
              nfp_out => tmp_Matrix_Multiply_dotp_0_3  -- single
              );

  u_nfp_add_comp_3 : AXI_testI_ip_src_nfp_add_single
    PORT MAP( clk => clk,
              reset => reset,
              enb => clk_enable,
              nfp_in1 => tmp_Matrix_Multiply_dotp_1_3,  -- single
              nfp_in2 => tmp_Matrix_Multiply_dotp_0_3,  -- single
              nfp_out => Matrix_Multiply_out1(1, 1)  -- single
              );

  A_float(0) <= A_float_0;
  A_float(1) <= A_float_1;
  A_float(2) <= A_float_2;
  A_float(3) <= A_float_3;

  Reshape_output : PROCESS (A_float)
  BEGIN
    Reshape_out1(0, 0) <= A_float(0);
    Reshape_out1(1, 0) <= A_float(1);
    Reshape_out1(0, 1) <= A_float(2);
    Reshape_out1(1, 1) <= A_float(3);
  END PROCESS Reshape_output;


  transpose_output : PROCESS (Reshape_out1)
  BEGIN
    Reshape_out1t(0, 0) <= Reshape_out1(0, 0);
    Reshape_out1t(1, 0) <= Reshape_out1(0, 1);
    Reshape_out1t(0, 1) <= Reshape_out1(1, 0);
    Reshape_out1t(1, 1) <= Reshape_out1(1, 1);
  END PROCESS transpose_output;


  B_float(0) <= B_float_0;
  B_float(1) <= B_float_1;
  B_float(2) <= B_float_2;
  B_float(3) <= B_float_3;

  Reshape1_output : PROCESS (B_float)
  BEGIN
    Reshape1_out1(0, 0) <= B_float(0);
    Reshape1_out1(1, 0) <= B_float(1);
    Reshape1_out1(0, 1) <= B_float(2);
    Reshape1_out1(1, 1) <= B_float(3);
  END PROCESS Reshape1_output;



  Reshape2_output : PROCESS (Matrix_Multiply_out1)
  BEGIN
    Reshape2_out1(0) <= Matrix_Multiply_out1(0, 0);
    Reshape2_out1(1) <= Matrix_Multiply_out1(1, 0);
    Reshape2_out1(2) <= Matrix_Multiply_out1(0, 1);
    Reshape2_out1(3) <= Matrix_Multiply_out1(1, 1);
  END PROCESS Reshape2_output;


  A_uint32_unsigned <= unsigned(A_uint32);

  enb <= clk_enable;

  Delay2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay2_out1 <= to_unsigned(0, 32);
      ELSIF enb = '1' THEN
        Delay2_out1 <= A_uint32_unsigned;
      END IF;
    END IF;
  END PROCESS Delay2_process;


  B_uint32_unsigned <= unsigned(B_uint32);

  Delay3_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay3_out1 <= to_unsigned(0, 32);
      ELSIF enb = '1' THEN
        Delay3_out1 <= B_uint32_unsigned;
      END IF;
    END IF;
  END PROCESS Delay3_process;


  Product_out1 <= resize(Delay2_out1 * Delay3_out1, 32);

  delayMatch_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch_reg(0) <= to_unsigned(0, 32);
        delayMatch_reg(1) <= to_unsigned(0, 32);
        delayMatch_reg(2) <= to_unsigned(0, 32);
        delayMatch_reg(3) <= to_unsigned(0, 32);
        delayMatch_reg(4) <= to_unsigned(0, 32);
        delayMatch_reg(5) <= to_unsigned(0, 32);
        delayMatch_reg(6) <= to_unsigned(0, 32);
        delayMatch_reg(7) <= to_unsigned(0, 32);
        delayMatch_reg(8) <= to_unsigned(0, 32);
        delayMatch_reg(9) <= to_unsigned(0, 32);
        delayMatch_reg(10) <= to_unsigned(0, 32);
        delayMatch_reg(11) <= to_unsigned(0, 32);
        delayMatch_reg(12) <= to_unsigned(0, 32);
        delayMatch_reg(13) <= to_unsigned(0, 32);
        delayMatch_reg(14) <= to_unsigned(0, 32);
        delayMatch_reg(15) <= to_unsigned(0, 32);
        delayMatch_reg(16) <= to_unsigned(0, 32);
        delayMatch_reg(17) <= to_unsigned(0, 32);
        delayMatch_reg(18) <= to_unsigned(0, 32);
      ELSIF enb = '1' THEN
        delayMatch_reg(0) <= delayMatch_reg_next(0);
        delayMatch_reg(1) <= delayMatch_reg_next(1);
        delayMatch_reg(2) <= delayMatch_reg_next(2);
        delayMatch_reg(3) <= delayMatch_reg_next(3);
        delayMatch_reg(4) <= delayMatch_reg_next(4);
        delayMatch_reg(5) <= delayMatch_reg_next(5);
        delayMatch_reg(6) <= delayMatch_reg_next(6);
        delayMatch_reg(7) <= delayMatch_reg_next(7);
        delayMatch_reg(8) <= delayMatch_reg_next(8);
        delayMatch_reg(9) <= delayMatch_reg_next(9);
        delayMatch_reg(10) <= delayMatch_reg_next(10);
        delayMatch_reg(11) <= delayMatch_reg_next(11);
        delayMatch_reg(12) <= delayMatch_reg_next(12);
        delayMatch_reg(13) <= delayMatch_reg_next(13);
        delayMatch_reg(14) <= delayMatch_reg_next(14);
        delayMatch_reg(15) <= delayMatch_reg_next(15);
        delayMatch_reg(16) <= delayMatch_reg_next(16);
        delayMatch_reg(17) <= delayMatch_reg_next(17);
        delayMatch_reg(18) <= delayMatch_reg_next(18);
      END IF;
    END IF;
  END PROCESS delayMatch_process;

  Product_out1_1 <= delayMatch_reg(18);
  delayMatch_reg_next(0) <= Product_out1;
  delayMatch_reg_next(1) <= delayMatch_reg(0);
  delayMatch_reg_next(2) <= delayMatch_reg(1);
  delayMatch_reg_next(3) <= delayMatch_reg(2);
  delayMatch_reg_next(4) <= delayMatch_reg(3);
  delayMatch_reg_next(5) <= delayMatch_reg(4);
  delayMatch_reg_next(6) <= delayMatch_reg(5);
  delayMatch_reg_next(7) <= delayMatch_reg(6);
  delayMatch_reg_next(8) <= delayMatch_reg(7);
  delayMatch_reg_next(9) <= delayMatch_reg(8);
  delayMatch_reg_next(10) <= delayMatch_reg(9);
  delayMatch_reg_next(11) <= delayMatch_reg(10);
  delayMatch_reg_next(12) <= delayMatch_reg(11);
  delayMatch_reg_next(13) <= delayMatch_reg(12);
  delayMatch_reg_next(14) <= delayMatch_reg(13);
  delayMatch_reg_next(15) <= delayMatch_reg(14);
  delayMatch_reg_next(16) <= delayMatch_reg(15);
  delayMatch_reg_next(17) <= delayMatch_reg(16);
  delayMatch_reg_next(18) <= delayMatch_reg(17);

  C_uint32 <= std_logic_vector(Product_out1_1);

  A_int32_signed <= signed(A_int32);

  Delay1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay1_out1 <= to_signed(0, 32);
      ELSIF enb = '1' THEN
        Delay1_out1 <= A_int32_signed;
      END IF;
    END IF;
  END PROCESS Delay1_process;


  B_int32_signed <= signed(B_int32);

  Delay4_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay4_out1 <= to_signed(0, 32);
      ELSIF enb = '1' THEN
        Delay4_out1 <= B_int32_signed;
      END IF;
    END IF;
  END PROCESS Delay4_process;


  Product1_mul_temp <= Delay1_out1 * Delay4_out1;
  Product1_out1 <= Product1_mul_temp(31 DOWNTO 0);

  delayMatch1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch1_reg(0) <= to_signed(0, 32);
        delayMatch1_reg(1) <= to_signed(0, 32);
        delayMatch1_reg(2) <= to_signed(0, 32);
        delayMatch1_reg(3) <= to_signed(0, 32);
        delayMatch1_reg(4) <= to_signed(0, 32);
        delayMatch1_reg(5) <= to_signed(0, 32);
        delayMatch1_reg(6) <= to_signed(0, 32);
        delayMatch1_reg(7) <= to_signed(0, 32);
        delayMatch1_reg(8) <= to_signed(0, 32);
        delayMatch1_reg(9) <= to_signed(0, 32);
        delayMatch1_reg(10) <= to_signed(0, 32);
        delayMatch1_reg(11) <= to_signed(0, 32);
        delayMatch1_reg(12) <= to_signed(0, 32);
        delayMatch1_reg(13) <= to_signed(0, 32);
        delayMatch1_reg(14) <= to_signed(0, 32);
        delayMatch1_reg(15) <= to_signed(0, 32);
        delayMatch1_reg(16) <= to_signed(0, 32);
        delayMatch1_reg(17) <= to_signed(0, 32);
        delayMatch1_reg(18) <= to_signed(0, 32);
      ELSIF enb = '1' THEN
        delayMatch1_reg(0) <= delayMatch1_reg_next(0);
        delayMatch1_reg(1) <= delayMatch1_reg_next(1);
        delayMatch1_reg(2) <= delayMatch1_reg_next(2);
        delayMatch1_reg(3) <= delayMatch1_reg_next(3);
        delayMatch1_reg(4) <= delayMatch1_reg_next(4);
        delayMatch1_reg(5) <= delayMatch1_reg_next(5);
        delayMatch1_reg(6) <= delayMatch1_reg_next(6);
        delayMatch1_reg(7) <= delayMatch1_reg_next(7);
        delayMatch1_reg(8) <= delayMatch1_reg_next(8);
        delayMatch1_reg(9) <= delayMatch1_reg_next(9);
        delayMatch1_reg(10) <= delayMatch1_reg_next(10);
        delayMatch1_reg(11) <= delayMatch1_reg_next(11);
        delayMatch1_reg(12) <= delayMatch1_reg_next(12);
        delayMatch1_reg(13) <= delayMatch1_reg_next(13);
        delayMatch1_reg(14) <= delayMatch1_reg_next(14);
        delayMatch1_reg(15) <= delayMatch1_reg_next(15);
        delayMatch1_reg(16) <= delayMatch1_reg_next(16);
        delayMatch1_reg(17) <= delayMatch1_reg_next(17);
        delayMatch1_reg(18) <= delayMatch1_reg_next(18);
      END IF;
    END IF;
  END PROCESS delayMatch1_process;

  Product1_out1_1 <= delayMatch1_reg(18);
  delayMatch1_reg_next(0) <= Product1_out1;
  delayMatch1_reg_next(1) <= delayMatch1_reg(0);
  delayMatch1_reg_next(2) <= delayMatch1_reg(1);
  delayMatch1_reg_next(3) <= delayMatch1_reg(2);
  delayMatch1_reg_next(4) <= delayMatch1_reg(3);
  delayMatch1_reg_next(5) <= delayMatch1_reg(4);
  delayMatch1_reg_next(6) <= delayMatch1_reg(5);
  delayMatch1_reg_next(7) <= delayMatch1_reg(6);
  delayMatch1_reg_next(8) <= delayMatch1_reg(7);
  delayMatch1_reg_next(9) <= delayMatch1_reg(8);
  delayMatch1_reg_next(10) <= delayMatch1_reg(9);
  delayMatch1_reg_next(11) <= delayMatch1_reg(10);
  delayMatch1_reg_next(12) <= delayMatch1_reg(11);
  delayMatch1_reg_next(13) <= delayMatch1_reg(12);
  delayMatch1_reg_next(14) <= delayMatch1_reg(13);
  delayMatch1_reg_next(15) <= delayMatch1_reg(14);
  delayMatch1_reg_next(16) <= delayMatch1_reg(15);
  delayMatch1_reg_next(17) <= delayMatch1_reg(16);
  delayMatch1_reg_next(18) <= delayMatch1_reg(17);

  C_int32 <= std_logic_vector(Product1_out1_1);

  A_fx_1_16_5_signed <= signed(A_fx_1_16_5);

  Delay5_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay5_out1 <= to_signed(16#0000#, 16);
      ELSIF enb = '1' THEN
        Delay5_out1 <= A_fx_1_16_5_signed;
      END IF;
    END IF;
  END PROCESS Delay5_process;


  B_fx_1_16_5_signed <= signed(B_fx_1_16_5);

  Delay6_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        Delay6_out1 <= to_signed(16#0000#, 16);
      ELSIF enb = '1' THEN
        Delay6_out1 <= B_fx_1_16_5_signed;
      END IF;
    END IF;
  END PROCESS Delay6_process;


  Product2_mul_temp <= Delay5_out1 * Delay6_out1;
  Product2_out1 <= Product2_mul_temp(20 DOWNTO 5);

  delayMatch2_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        delayMatch2_reg(0) <= to_signed(16#0000#, 16);
        delayMatch2_reg(1) <= to_signed(16#0000#, 16);
        delayMatch2_reg(2) <= to_signed(16#0000#, 16);
        delayMatch2_reg(3) <= to_signed(16#0000#, 16);
        delayMatch2_reg(4) <= to_signed(16#0000#, 16);
        delayMatch2_reg(5) <= to_signed(16#0000#, 16);
        delayMatch2_reg(6) <= to_signed(16#0000#, 16);
        delayMatch2_reg(7) <= to_signed(16#0000#, 16);
        delayMatch2_reg(8) <= to_signed(16#0000#, 16);
        delayMatch2_reg(9) <= to_signed(16#0000#, 16);
        delayMatch2_reg(10) <= to_signed(16#0000#, 16);
        delayMatch2_reg(11) <= to_signed(16#0000#, 16);
        delayMatch2_reg(12) <= to_signed(16#0000#, 16);
        delayMatch2_reg(13) <= to_signed(16#0000#, 16);
        delayMatch2_reg(14) <= to_signed(16#0000#, 16);
        delayMatch2_reg(15) <= to_signed(16#0000#, 16);
        delayMatch2_reg(16) <= to_signed(16#0000#, 16);
        delayMatch2_reg(17) <= to_signed(16#0000#, 16);
        delayMatch2_reg(18) <= to_signed(16#0000#, 16);
      ELSIF enb = '1' THEN
        delayMatch2_reg(0) <= delayMatch2_reg_next(0);
        delayMatch2_reg(1) <= delayMatch2_reg_next(1);
        delayMatch2_reg(2) <= delayMatch2_reg_next(2);
        delayMatch2_reg(3) <= delayMatch2_reg_next(3);
        delayMatch2_reg(4) <= delayMatch2_reg_next(4);
        delayMatch2_reg(5) <= delayMatch2_reg_next(5);
        delayMatch2_reg(6) <= delayMatch2_reg_next(6);
        delayMatch2_reg(7) <= delayMatch2_reg_next(7);
        delayMatch2_reg(8) <= delayMatch2_reg_next(8);
        delayMatch2_reg(9) <= delayMatch2_reg_next(9);
        delayMatch2_reg(10) <= delayMatch2_reg_next(10);
        delayMatch2_reg(11) <= delayMatch2_reg_next(11);
        delayMatch2_reg(12) <= delayMatch2_reg_next(12);
        delayMatch2_reg(13) <= delayMatch2_reg_next(13);
        delayMatch2_reg(14) <= delayMatch2_reg_next(14);
        delayMatch2_reg(15) <= delayMatch2_reg_next(15);
        delayMatch2_reg(16) <= delayMatch2_reg_next(16);
        delayMatch2_reg(17) <= delayMatch2_reg_next(17);
        delayMatch2_reg(18) <= delayMatch2_reg_next(18);
      END IF;
    END IF;
  END PROCESS delayMatch2_process;

  Product2_out1_1 <= delayMatch2_reg(18);
  delayMatch2_reg_next(0) <= Product2_out1;
  delayMatch2_reg_next(1) <= delayMatch2_reg(0);
  delayMatch2_reg_next(2) <= delayMatch2_reg(1);
  delayMatch2_reg_next(3) <= delayMatch2_reg(2);
  delayMatch2_reg_next(4) <= delayMatch2_reg(3);
  delayMatch2_reg_next(5) <= delayMatch2_reg(4);
  delayMatch2_reg_next(6) <= delayMatch2_reg(5);
  delayMatch2_reg_next(7) <= delayMatch2_reg(6);
  delayMatch2_reg_next(8) <= delayMatch2_reg(7);
  delayMatch2_reg_next(9) <= delayMatch2_reg(8);
  delayMatch2_reg_next(10) <= delayMatch2_reg(9);
  delayMatch2_reg_next(11) <= delayMatch2_reg(10);
  delayMatch2_reg_next(12) <= delayMatch2_reg(11);
  delayMatch2_reg_next(13) <= delayMatch2_reg(12);
  delayMatch2_reg_next(14) <= delayMatch2_reg(13);
  delayMatch2_reg_next(15) <= delayMatch2_reg(14);
  delayMatch2_reg_next(16) <= delayMatch2_reg(15);
  delayMatch2_reg_next(17) <= delayMatch2_reg(16);
  delayMatch2_reg_next(18) <= delayMatch2_reg(17);

  C_fx_1_16_5 <= std_logic_vector(Product2_out1_1);

  ce_out <= clk_enable;

  C_float_0 <= Reshape2_out1(0);

  C_float_1 <= Reshape2_out1(1);

  C_float_2 <= Reshape2_out1(2);

  C_float_3 <= Reshape2_out1(3);

END rtl;

