-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\parallel_8_delay_compensation\hdlsrc\parallel_8_delay_compensation\parallel_8_sim_delay_compensation_src_Positive_block.vhd
-- Created: 2022-12-07 16:30:36
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: parallel_8_sim_delay_compensation_src_Positive_block
-- Source Path: parallel_8_delay_compensation/Delay_compensation/Detect Rise Positive1/Positive
-- Hierarchy Level: 2
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY parallel_8_sim_delay_compensation_src_Positive_block IS
  PORT( u                                 :   IN    std_logic;
        y                                 :   OUT   std_logic
        );
END parallel_8_sim_delay_compensation_src_Positive_block;


ARCHITECTURE rtl OF parallel_8_sim_delay_compensation_src_Positive_block IS

  -- Signals
  SIGNAL Constant_out1                    : std_logic;
  SIGNAL Compare_relop1                   : std_logic;

BEGIN
  Constant_out1 <= '0';

  
  Compare_relop1 <= '1' WHEN u > Constant_out1 ELSE
      '0';

  y <= Compare_relop1;

END rtl;
