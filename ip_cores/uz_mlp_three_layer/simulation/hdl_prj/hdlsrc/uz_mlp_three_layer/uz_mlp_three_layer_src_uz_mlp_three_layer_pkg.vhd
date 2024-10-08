-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj/hdlsrc/uz_mlp_three_layer/uz_mlp_three_layer_src_uz_mlp_three_layer_pkg.vhd
-- Created: 2021-03-17 16:47:05
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

PACKAGE uz_mlp_three_layer_src_uz_mlp_three_layer_pkg IS
  TYPE T_state_type_is_layer_control IS (IN_calc_perceptron, IN_calc_running, IN_entry_to_entry_state, IN_finished, IN_finished2, IN_idle, IN_perceptron_rdy);
  TYPE T_state_type_is_mac_control IS (IN_accumulate, IN_idle_entry, IN_mac_finished, IN_mac_stop, IN_start_counter, IN_start_mac, IN_write_ram_entry);
END uz_mlp_three_layer_src_uz_mlp_three_layer_pkg;

