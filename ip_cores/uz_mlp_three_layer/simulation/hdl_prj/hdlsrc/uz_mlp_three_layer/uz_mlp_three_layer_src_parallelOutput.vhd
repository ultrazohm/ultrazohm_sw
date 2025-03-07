-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj/hdlsrc/uz_mlp_three_layer/uz_mlp_three_layer_src_parallelOutput.vhd
-- Created: 2021-03-17 16:47:03
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_mlp_three_layer_src_parallelOutput
-- Source Path: uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/parallelOutput
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_mlp_three_layer_src_parallelOutput IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        data_Upper                        :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        n_perceptron                      :   IN    std_logic_vector(9 DOWNTO 0);  -- ufix10
        write_enable                      :   IN    std_logic;
        data_lower                        :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out_rsvd                          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out1                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out2                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out3                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out4                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out5                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out6                              :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
        out7                              :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
        );
END uz_mlp_three_layer_src_parallelOutput;


ARCHITECTURE rtl OF uz_mlp_three_layer_src_parallelOutput IS

  -- Component Declarations
  COMPONENT uz_mlp_three_layer_src_holdValue
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue1
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue2
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue3
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue4
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue5
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue6
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  COMPONENT uz_mlp_three_layer_src_holdValue7
    PORT( clk                             :   IN    std_logic;
          reset                           :   IN    std_logic;
          enb                             :   IN    std_logic;
          takeNewValue                    :   IN    std_logic;
          data                            :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En14
          out_rsvd                        :   OUT   std_logic_vector(31 DOWNTO 0)  -- sfix32_En14
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_mlp_three_layer_src_holdValue
    USE ENTITY work.uz_mlp_three_layer_src_holdValue(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue1
    USE ENTITY work.uz_mlp_three_layer_src_holdValue1(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue2
    USE ENTITY work.uz_mlp_three_layer_src_holdValue2(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue3
    USE ENTITY work.uz_mlp_three_layer_src_holdValue3(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue4
    USE ENTITY work.uz_mlp_three_layer_src_holdValue4(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue5
    USE ENTITY work.uz_mlp_three_layer_src_holdValue5(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue6
    USE ENTITY work.uz_mlp_three_layer_src_holdValue6(rtl);

  FOR ALL : uz_mlp_three_layer_src_holdValue7
    USE ENTITY work.uz_mlp_three_layer_src_holdValue7(rtl);

  -- Signals
  SIGNAL n_perceptron_unsigned            : unsigned(9 DOWNTO 0);  -- ufix10
  SIGNAL Compare_To_Constant_out1         : std_logic;
  SIGNAL Logical_Operator_out1            : std_logic;
  SIGNAL holdValue_out1                   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant2_out1        : std_logic;
  SIGNAL Logical_Operator1_out1           : std_logic;
  SIGNAL holdValue1_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant3_out1        : std_logic;
  SIGNAL Logical_Operator2_out1           : std_logic;
  SIGNAL holdValue2_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant4_out1        : std_logic;
  SIGNAL Logical_Operator3_out1           : std_logic;
  SIGNAL holdValue3_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant5_out1        : std_logic;
  SIGNAL Logical_Operator4_out1           : std_logic;
  SIGNAL holdValue4_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant6_out1        : std_logic;
  SIGNAL Logical_Operator5_out1           : std_logic;
  SIGNAL holdValue5_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant7_out1        : std_logic;
  SIGNAL Logical_Operator6_out1           : std_logic;
  SIGNAL holdValue6_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Compare_To_Constant8_out1        : std_logic;
  SIGNAL Logical_Operator7_out1           : std_logic;
  SIGNAL holdValue7_out1                  : std_logic_vector(31 DOWNTO 0);  -- ufix32

BEGIN
  u_holdValue : uz_mlp_three_layer_src_holdValue
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator_out1,
              data => data_Upper,  -- sfix32_En14
              out_rsvd => holdValue_out1  -- sfix32_En14
              );

  u_holdValue1 : uz_mlp_three_layer_src_holdValue1
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator1_out1,
              data => data_Upper,  -- sfix32_En14
              out_rsvd => holdValue1_out1  -- sfix32_En14
              );

  u_holdValue2 : uz_mlp_three_layer_src_holdValue2
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator2_out1,
              data => data_Upper,  -- sfix32_En14
              out_rsvd => holdValue2_out1  -- sfix32_En14
              );

  u_holdValue3 : uz_mlp_three_layer_src_holdValue3
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator3_out1,
              data => data_Upper,  -- sfix32_En14
              out_rsvd => holdValue3_out1  -- sfix32_En14
              );

  u_holdValue4 : uz_mlp_three_layer_src_holdValue4
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator4_out1,
              data => data_lower,  -- sfix32_En14
              out_rsvd => holdValue4_out1  -- sfix32_En14
              );

  u_holdValue5 : uz_mlp_three_layer_src_holdValue5
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator5_out1,
              data => data_lower,  -- sfix32_En14
              out_rsvd => holdValue5_out1  -- sfix32_En14
              );

  u_holdValue6 : uz_mlp_three_layer_src_holdValue6
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator6_out1,
              data => data_lower,  -- sfix32_En14
              out_rsvd => holdValue6_out1  -- sfix32_En14
              );

  u_holdValue7 : uz_mlp_three_layer_src_holdValue7
    PORT MAP( clk => clk,
              reset => reset,
              enb => enb,
              takeNewValue => Logical_Operator7_out1,
              data => data_lower,  -- sfix32_En14
              out_rsvd => holdValue7_out1  -- sfix32_En14
              );

  n_perceptron_unsigned <= unsigned(n_perceptron);

  
  Compare_To_Constant_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#000#, 10) ELSE
      '0';

  Logical_Operator_out1 <= Compare_To_Constant_out1 AND write_enable;

  
  Compare_To_Constant2_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#001#, 10) ELSE
      '0';

  Logical_Operator1_out1 <= Compare_To_Constant2_out1 AND write_enable;

  
  Compare_To_Constant3_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#002#, 10) ELSE
      '0';

  Logical_Operator2_out1 <= Compare_To_Constant3_out1 AND write_enable;

  
  Compare_To_Constant4_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#003#, 10) ELSE
      '0';

  Logical_Operator3_out1 <= Compare_To_Constant4_out1 AND write_enable;

  
  Compare_To_Constant5_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#000#, 10) ELSE
      '0';

  Logical_Operator4_out1 <= Compare_To_Constant5_out1 AND write_enable;

  
  Compare_To_Constant6_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#001#, 10) ELSE
      '0';

  Logical_Operator5_out1 <= Compare_To_Constant6_out1 AND write_enable;

  
  Compare_To_Constant7_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#002#, 10) ELSE
      '0';

  Logical_Operator6_out1 <= Compare_To_Constant7_out1 AND write_enable;

  
  Compare_To_Constant8_out1 <= '1' WHEN n_perceptron_unsigned = to_unsigned(16#003#, 10) ELSE
      '0';

  Logical_Operator7_out1 <= Compare_To_Constant8_out1 AND write_enable;

  out_rsvd <= holdValue_out1;

  out1 <= holdValue1_out1;

  out2 <= holdValue2_out1;

  out3 <= holdValue3_out1;

  out4 <= holdValue4_out1;

  out5 <= holdValue5_out1;

  out6 <= holdValue6_out1;

  out7 <= holdValue7_out1;

END rtl;

