-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\uz_mpc_cost_and_optim_state_machine\uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd_pkg.vhd
-- Created: 2022-10-04 11:16:03
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

PACKAGE uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd_pkg IS
  TYPE vector_of_signed18 IS ARRAY (NATURAL RANGE <>) OF signed(17 DOWNTO 0);
  TYPE vector_of_unsigned32 IS ARRAY (NATURAL RANGE <>) OF unsigned(31 DOWNTO 0);
  TYPE vector_of_signed27 IS ARRAY (NATURAL RANGE <>) OF signed(26 DOWNTO 0);
  TYPE matrix_of_signed18 IS ARRAY (NATURAL RANGE <>, NATURAL RANGE <>) OF signed(17 DOWNTO 0);
END uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd_pkg;
