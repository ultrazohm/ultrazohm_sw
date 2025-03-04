-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\uz_pmsm_model\uz_pmsm_model_src_nfp_abs_single.vhd
-- Created: 2024-05-23 13:50:30
-- 
-- Generated by MATLAB 23.2, HDL Coder 23.2, and Simulink 23.2
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_src_nfp_abs_single
-- Source Path: uz_pmsm_model/uz_pmsm_model/nfp_abs_single
-- Hierarchy Level: 1
-- Model version: 7.0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_pmsm_model_src_nfp_abs_single IS
  PORT( nfp_in                            :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        nfp_out                           :   OUT   std_logic_vector(31 DOWNTO 0)  -- ufix32
        );
END uz_pmsm_model_src_nfp_abs_single;


ARCHITECTURE rtl OF uz_pmsm_model_src_nfp_abs_single IS

  -- Signals
  SIGNAL Constant_out1                    : std_logic;  -- ufix1
  SIGNAL nfp_in_unsigned                  : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL XS                               : std_logic;  -- ufix1
  SIGNAL XE                               : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL XM                               : unsigned(22 DOWNTO 0);  -- ufix23
  SIGNAL nfp_out_pack                     : unsigned(31 DOWNTO 0);  -- ufix32

BEGIN
  Constant_out1 <= '0';

  nfp_in_unsigned <= unsigned(nfp_in);

  -- Split 32 bit word into FP sign, exponent, mantissa
  XS <= nfp_in_unsigned(31);
  XE <= nfp_in_unsigned(30 DOWNTO 23);
  XM <= nfp_in_unsigned(22 DOWNTO 0);

  -- Combine FP sign, exponent, mantissa into 32 bit word
  nfp_out_pack <= Constant_out1 & XE & XM;

  nfp_out <= std_logic_vector(nfp_out_pack);

END rtl;

