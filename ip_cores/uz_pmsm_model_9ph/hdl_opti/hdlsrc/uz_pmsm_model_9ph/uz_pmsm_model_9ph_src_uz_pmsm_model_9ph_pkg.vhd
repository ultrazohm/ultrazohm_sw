-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdl_opti\hdlsrc\uz_pmsm_model_9ph\uz_pmsm_model_9ph_src_uz_pmsm_model_9ph_pkg.vhd
-- Created: 2022-06-01 20:58:47
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- -------------------------------------------------------------


LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

PACKAGE uz_pmsm_model_9ph_src_uz_pmsm_model_9ph_pkg IS
  TYPE vector_of_unsigned8 IS ARRAY (NATURAL RANGE <>) OF unsigned(7 DOWNTO 0);
  TYPE vector_of_unsigned23 IS ARRAY (NATURAL RANGE <>) OF unsigned(22 DOWNTO 0);
  TYPE vector_of_unsigned26 IS ARRAY (NATURAL RANGE <>) OF unsigned(25 DOWNTO 0);
  TYPE vector_of_std_logic_vector32 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(31 DOWNTO 0);
  TYPE matrix_of_std_logic_vector32 IS ARRAY (NATURAL RANGE <>, NATURAL RANGE <>) OF std_logic_vector(31 DOWNTO 0);
  TYPE vector_of_unsigned128 IS ARRAY (NATURAL RANGE <>) OF unsigned(127 DOWNTO 0);
  TYPE vector_of_std_logic_vector25 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(24 DOWNTO 0);
  TYPE vector_of_signed43 IS ARRAY (NATURAL RANGE <>) OF signed(42 DOWNTO 0);
  TYPE vector_of_signed18 IS ARRAY (NATURAL RANGE <>) OF signed(17 DOWNTO 0);
  TYPE matrix_of_signed18 IS ARRAY (NATURAL RANGE <>, NATURAL RANGE <>) OF signed(17 DOWNTO 0);
  TYPE vector_of_signed25 IS ARRAY (NATURAL RANGE <>) OF signed(24 DOWNTO 0);
  TYPE vector_of_std_logic_vector18 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(17 DOWNTO 0);
  TYPE vector_of_signed9 IS ARRAY (NATURAL RANGE <>) OF signed(8 DOWNTO 0);
  TYPE vector_of_unsigned24 IS ARRAY (NATURAL RANGE <>) OF unsigned(23 DOWNTO 0);
  TYPE vector_of_std_logic_vector43 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(42 DOWNTO 0);
  TYPE vector_of_unsigned79 IS ARRAY (NATURAL RANGE <>) OF unsigned(78 DOWNTO 0);
  TYPE vector_of_unsigned27 IS ARRAY (NATURAL RANGE <>) OF unsigned(26 DOWNTO 0);
  TYPE vector_of_unsigned51 IS ARRAY (NATURAL RANGE <>) OF unsigned(50 DOWNTO 0);
  TYPE vector_of_signed27 IS ARRAY (NATURAL RANGE <>) OF signed(26 DOWNTO 0);
  TYPE vector_of_unsigned20 IS ARRAY (NATURAL RANGE <>) OF unsigned(19 DOWNTO 0);
  TYPE vector_of_unsigned29 IS ARRAY (NATURAL RANGE <>) OF unsigned(28 DOWNTO 0);
  TYPE vector_of_unsigned54 IS ARRAY (NATURAL RANGE <>) OF unsigned(53 DOWNTO 0);
  TYPE vector_of_unsigned21 IS ARRAY (NATURAL RANGE <>) OF unsigned(20 DOWNTO 0);
  TYPE vector_of_unsigned30 IS ARRAY (NATURAL RANGE <>) OF unsigned(29 DOWNTO 0);
  TYPE vector_of_unsigned106 IS ARRAY (NATURAL RANGE <>) OF unsigned(105 DOWNTO 0);
  TYPE vector_of_unsigned52 IS ARRAY (NATURAL RANGE <>) OF unsigned(51 DOWNTO 0);
  TYPE vector_of_unsigned11 IS ARRAY (NATURAL RANGE <>) OF unsigned(10 DOWNTO 0);
  TYPE vector_of_std_logic_vector64 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(63 DOWNTO 0);
END uz_pmsm_model_9ph_src_uz_pmsm_model_9ph_pkg;
