-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\parallel_8_min_cost_function\hdlsrc\parallel_8_min_cost_function\parallel_8_sim_min_cost_function_src_Positive_block.vhd
-- Created: 2022-12-09 12:04:39
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: parallel_8_sim_min_cost_function_src_Positive_block
-- Source Path: parallel_8_min_cost_function/Min_cost_function_and_vopt1/Detect Rise Positive1/Positive
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY parallel_8_sim_min_cost_function_src_Positive_block IS
  PORT( u                                 :   IN    std_logic;
        y                                 :   OUT   std_logic
        );
END parallel_8_sim_min_cost_function_src_Positive_block;


ARCHITECTURE rtl OF parallel_8_sim_min_cost_function_src_Positive_block IS

  -- Signals
  SIGNAL Constant_out1                    : std_logic;
  SIGNAL Compare_relop1                   : std_logic;

BEGIN
  Constant_out1 <= '0';

  
  Compare_relop1 <= '1' WHEN u > Constant_out1 ELSE
      '0';

  y <= Compare_relop1;

END rtl;
