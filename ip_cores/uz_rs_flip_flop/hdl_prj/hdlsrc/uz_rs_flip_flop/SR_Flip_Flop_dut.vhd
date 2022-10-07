-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_rs_flip_flop\hdl_prj\hdlsrc\uz_rs_flip_flop\SR_Flip_Flop_dut.vhd
-- Created: 2022-09-27 19:38:24
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: SR_Flip_Flop_dut
-- Source Path: SR_Flip_Flop/SR_Flip_Flop_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY SR_Flip_Flop_dut IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        ff_reset                          :   IN    std_logic;  -- ufix1
        ff_set                            :   IN    std_logic;  -- ufix1
        ce_out                            :   OUT   std_logic;  -- ufix1
        ff_out                            :   OUT   std_logic  -- ufix1
        );
END SR_Flip_Flop_dut;


ARCHITECTURE rtl OF SR_Flip_Flop_dut IS

  -- Component Declarations
  COMPONENT SR_Flip_Flop_src_uz_rs_flip_flop
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset                           :   IN    std_logic;
          ff_reset                        :   IN    std_logic;  -- ufix1
          ff_set                          :   IN    std_logic;  -- ufix1
          ce_out                          :   OUT   std_logic;  -- ufix1
          ff_out                          :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : SR_Flip_Flop_src_uz_rs_flip_flop
    USE ENTITY work.SR_Flip_Flop_src_uz_rs_flip_flop(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL ff_reset_sig                     : std_logic;  -- ufix1
  SIGNAL ff_set_sig                       : std_logic;  -- ufix1
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL ff_out_sig                       : std_logic;  -- ufix1

BEGIN
  u_SR_Flip_Flop_src_uz_rs_flip_flop : SR_Flip_Flop_src_uz_rs_flip_flop
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset => reset,
              ff_reset => ff_reset_sig,  -- ufix1
              ff_set => ff_set_sig,  -- ufix1
              ce_out => ce_out_sig,  -- ufix1
              ff_out => ff_out_sig  -- ufix1
              );

  ff_reset_sig <= ff_reset;

  ff_set_sig <= ff_set;

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  ff_out <= ff_out_sig;

END rtl;
