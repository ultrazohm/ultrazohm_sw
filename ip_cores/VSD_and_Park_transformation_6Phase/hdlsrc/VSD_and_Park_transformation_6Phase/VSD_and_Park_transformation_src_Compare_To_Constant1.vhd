-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\VSD_and_Park_transformation_6Phase\hdlsrc\VSD_and_Park_transformation_6Phase\VSD_and_Park_transformation_src_Compare_To_Constant1.vhd
-- Created: 2022-08-17 10:05:39
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: VSD_and_Park_transformation_src_Compare_To_Constant1
-- Source Path: VSD_and_Park_transformation_6Phase/vsd_and_park_tra/Compare To Constant1
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY VSD_and_Park_transformation_src_Compare_To_Constant1 IS
  PORT( u                                 :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        y                                 :   OUT   std_logic
        );
END VSD_and_Park_transformation_src_Compare_To_Constant1;


ARCHITECTURE rtl OF VSD_and_Park_transformation_src_Compare_To_Constant1 IS

  -- Signals
  SIGNAL u_signed                         : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Constant_out1                    : signed(23 DOWNTO 0);  -- sfix24_En20
  SIGNAL Compare_relop1                   : std_logic;

BEGIN
  u_signed <= signed(u);

  Constant_out1 <= to_signed(16#000000#, 24);

  
  Compare_relop1 <= '1' WHEN u_signed < Constant_out1 ELSE
      '0';

  y <= Compare_relop1;

END rtl;
