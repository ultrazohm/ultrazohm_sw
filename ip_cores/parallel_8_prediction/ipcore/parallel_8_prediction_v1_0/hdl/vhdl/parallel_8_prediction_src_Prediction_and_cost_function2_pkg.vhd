-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\parallel_8_prediction\hdlsrc\parallel_8_prediction\parallel_8_prediction_src_Prediction_and_cost_function2_pkg.vhd
-- Created: 2022-10-18 09:34:49
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

PACKAGE parallel_8_prediction_src_Prediction_and_cost_function2_pkg IS
  TYPE vector_of_unsigned8 IS ARRAY (NATURAL RANGE <>) OF unsigned(7 DOWNTO 0);
  TYPE vector_of_unsigned23 IS ARRAY (NATURAL RANGE <>) OF unsigned(22 DOWNTO 0);
  TYPE vector_of_unsigned26 IS ARRAY (NATURAL RANGE <>) OF unsigned(25 DOWNTO 0);
  TYPE vector_of_signed10 IS ARRAY (NATURAL RANGE <>) OF signed(9 DOWNTO 0);
  TYPE vector_of_std_logic_vector32 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(31 DOWNTO 0);
  TYPE vector_of_unsigned128 IS ARRAY (NATURAL RANGE <>) OF unsigned(127 DOWNTO 0);
  TYPE vector_of_signed9 IS ARRAY (NATURAL RANGE <>) OF signed(8 DOWNTO 0);
  TYPE vector_of_unsigned24 IS ARRAY (NATURAL RANGE <>) OF unsigned(23 DOWNTO 0);
  TYPE vector_of_signed32 IS ARRAY (NATURAL RANGE <>) OF signed(31 DOWNTO 0);
  TYPE vector_of_signed24 IS ARRAY (NATURAL RANGE <>) OF signed(23 DOWNTO 0);
  TYPE vector_of_std_logic_vector24 IS ARRAY (NATURAL RANGE <>) OF std_logic_vector(23 DOWNTO 0);
END parallel_8_prediction_src_Prediction_and_cost_function2_pkg;
