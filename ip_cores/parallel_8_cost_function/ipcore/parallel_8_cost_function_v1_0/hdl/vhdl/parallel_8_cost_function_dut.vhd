-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\parallel_8_cost_function\hdlsrc\parallel_8_cost_function\parallel_8_cost_function_dut.vhd
-- Created: 2022-10-18 09:53:50
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: parallel_8_cost_function_dut
-- Source Path: parallel_8_cost_function/parallel_8_cost_function_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY parallel_8_cost_function_dut IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        valid_in                          :   IN    std_logic;  -- ufix1
        Prediction_0                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_1                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_2                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_3                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_4                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_5                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_6                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_7                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_8                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_9                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_10                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_11                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_12                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_13                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_14                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_15                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_16                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_17                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_18                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_19                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_20                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_21                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_22                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_23                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_24                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_25                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_26                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_27                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_28                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_29                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_30                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Prediction_31                     :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        id_ref_AXI                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        iq_ref_AXI                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        ix_ref_AXI                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        iy_ref_AXI                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        ce_out                            :   OUT   std_logic;  -- ufix1
        done                              :   OUT   std_logic;  -- ufix1
        J_0                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_1                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_2                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_3                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_4                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_5                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_6                               :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
        J_7                               :   OUT   std_logic_vector(19 DOWNTO 0)  -- sfix20_En11
        );
END parallel_8_cost_function_dut;


ARCHITECTURE rtl OF parallel_8_cost_function_dut IS

  -- Component Declarations
  COMPONENT parallel_8_cost_function_src_HDL_DUT1
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset                           :   IN    std_logic;
          valid_in                        :   IN    std_logic;  -- ufix1
          Prediction_0                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_1                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_2                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_3                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_4                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_5                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_6                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_7                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_8                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_9                    :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_10                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_11                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_12                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_13                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_14                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_15                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_16                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_17                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_18                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_19                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_20                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_21                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_22                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_23                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_24                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_25                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_26                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_27                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_28                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_29                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_30                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Prediction_31                   :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          id_ref_AXI                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          iq_ref_AXI                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          ix_ref_AXI                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          iy_ref_AXI                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          ce_out                          :   OUT   std_logic;  -- ufix1
          done                            :   OUT   std_logic;  -- ufix1
          J_0                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_1                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_2                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_3                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_4                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_5                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_6                             :   OUT   std_logic_vector(19 DOWNTO 0);  -- sfix20_En11
          J_7                             :   OUT   std_logic_vector(19 DOWNTO 0)  -- sfix20_En11
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : parallel_8_cost_function_src_HDL_DUT1
    USE ENTITY work.parallel_8_cost_function_src_HDL_DUT1(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL done_sig                         : std_logic;  -- ufix1
  SIGNAL J_0_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_1_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_2_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_3_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_4_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_5_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_6_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20
  SIGNAL J_7_sig                          : std_logic_vector(19 DOWNTO 0);  -- ufix20

BEGIN
  u_parallel_8_cost_function_src_HDL_DUT1 : parallel_8_cost_function_src_HDL_DUT1
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset => reset,
              valid_in => valid_in,  -- ufix1
              Prediction_0 => Prediction_0,  -- sfix18_En11
              Prediction_1 => Prediction_1,  -- sfix18_En11
              Prediction_2 => Prediction_2,  -- sfix18_En11
              Prediction_3 => Prediction_3,  -- sfix18_En11
              Prediction_4 => Prediction_4,  -- sfix18_En11
              Prediction_5 => Prediction_5,  -- sfix18_En11
              Prediction_6 => Prediction_6,  -- sfix18_En11
              Prediction_7 => Prediction_7,  -- sfix18_En11
              Prediction_8 => Prediction_8,  -- sfix18_En11
              Prediction_9 => Prediction_9,  -- sfix18_En11
              Prediction_10 => Prediction_10,  -- sfix18_En11
              Prediction_11 => Prediction_11,  -- sfix18_En11
              Prediction_12 => Prediction_12,  -- sfix18_En11
              Prediction_13 => Prediction_13,  -- sfix18_En11
              Prediction_14 => Prediction_14,  -- sfix18_En11
              Prediction_15 => Prediction_15,  -- sfix18_En11
              Prediction_16 => Prediction_16,  -- sfix18_En11
              Prediction_17 => Prediction_17,  -- sfix18_En11
              Prediction_18 => Prediction_18,  -- sfix18_En11
              Prediction_19 => Prediction_19,  -- sfix18_En11
              Prediction_20 => Prediction_20,  -- sfix18_En11
              Prediction_21 => Prediction_21,  -- sfix18_En11
              Prediction_22 => Prediction_22,  -- sfix18_En11
              Prediction_23 => Prediction_23,  -- sfix18_En11
              Prediction_24 => Prediction_24,  -- sfix18_En11
              Prediction_25 => Prediction_25,  -- sfix18_En11
              Prediction_26 => Prediction_26,  -- sfix18_En11
              Prediction_27 => Prediction_27,  -- sfix18_En11
              Prediction_28 => Prediction_28,  -- sfix18_En11
              Prediction_29 => Prediction_29,  -- sfix18_En11
              Prediction_30 => Prediction_30,  -- sfix18_En11
              Prediction_31 => Prediction_31,  -- sfix18_En11
              id_ref_AXI => id_ref_AXI,  -- ufix32
              iq_ref_AXI => iq_ref_AXI,  -- ufix32
              ix_ref_AXI => ix_ref_AXI,  -- ufix32
              iy_ref_AXI => iy_ref_AXI,  -- ufix32
              ce_out => ce_out_sig,  -- ufix1
              done => done_sig,  -- ufix1
              J_0 => J_0_sig,  -- sfix20_En11
              J_1 => J_1_sig,  -- sfix20_En11
              J_2 => J_2_sig,  -- sfix20_En11
              J_3 => J_3_sig,  -- sfix20_En11
              J_4 => J_4_sig,  -- sfix20_En11
              J_5 => J_5_sig,  -- sfix20_En11
              J_6 => J_6_sig,  -- sfix20_En11
              J_7 => J_7_sig  -- sfix20_En11
              );

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  done <= done_sig;

  J_0 <= J_0_sig;

  J_1 <= J_1_sig;

  J_2 <= J_2_sig;

  J_3 <= J_3_sig;

  J_4 <= J_4_sig;

  J_5 <= J_5_sig;

  J_6 <= J_6_sig;

  J_7 <= J_7_sig;

END rtl;
