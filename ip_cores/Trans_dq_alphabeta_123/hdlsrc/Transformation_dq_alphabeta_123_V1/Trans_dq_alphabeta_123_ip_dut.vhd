-- -------------------------------------------------------------
-- 
-- File Name: C:\ultrazohm_sw\ip_cores\Trans_dq_alphabeta_123\Simulation\hdlsrc\Transformation_dq_alphabeta_123_V1\Trans_dq_alphabeta_123_ip_dut.vhd
-- Created: 2022-05-27 15:32:32
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Trans_dq_alphabeta_123_ip_dut
-- Source Path: Trans_dq_alphabeta_123_ip/Trans_dq_alphabeta_123_ip_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Trans_dq_alphabeta_123_ip_dut IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        theta                             :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        theta_offset_AXI                  :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        CurrentValid_in                   :   IN    std_logic;  -- ufix1
        Id_ref_AXI                        :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        Iq_ref_AXI                        :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ce_out                            :   OUT   std_logic;  -- ufix1
        dq_Done                           :   OUT   std_logic;  -- ufix1
        sin                               :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16_En14
        cos                               :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16_En14
        ialpha                            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ialpha_AXI                        :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ibeta                             :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        ibeta_AXI                         :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i1                                :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i1_AXI                            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i2                                :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i2_AXI                            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i3                                :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
        i3_AXI                            :   OUT   std_logic_vector(17 DOWNTO 0)  -- sfix18_En11
        );
END Trans_dq_alphabeta_123_ip_dut;


ARCHITECTURE rtl OF Trans_dq_alphabeta_123_ip_dut IS

  -- Component Declarations
  COMPONENT Trans_dq_alphabeta_123_ip_src_Trans_dq_alphabeta_123_fix_V1
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset                           :   IN    std_logic;
          theta                           :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
          theta_offset_AXI                :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
          CurrentValid_in                 :   IN    std_logic;  -- ufix1
          Id_ref_AXI                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          Iq_ref_AXI                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          ce_out                          :   OUT   std_logic;  -- ufix1
          dq_Done                         :   OUT   std_logic;  -- ufix1
          sin                             :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16_En14
          cos                             :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16_En14
          ialpha                          :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          ialpha_AXI                      :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          ibeta                           :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          ibeta_AXI                       :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i1                              :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i1_AXI                          :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i2                              :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i2_AXI                          :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i3                              :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          i3_AXI                          :   OUT   std_logic_vector(17 DOWNTO 0)  -- sfix18_En11
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : Trans_dq_alphabeta_123_ip_src_Trans_dq_alphabeta_123_fix_V1
    USE ENTITY work.Trans_dq_alphabeta_123_ip_src_Trans_dq_alphabeta_123_fix_V1(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL CurrentValid_in_sig              : std_logic;  -- ufix1
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL dq_Done_sig                      : std_logic;  -- ufix1
  SIGNAL sin_sig                          : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL cos_sig                          : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL ialpha_sig                       : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL ialpha_AXI_sig                   : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL ibeta_sig                        : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL ibeta_AXI_sig                    : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i1_sig                           : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i1_AXI_sig                       : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i2_sig                           : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i2_AXI_sig                       : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i3_sig                           : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL i3_AXI_sig                       : std_logic_vector(17 DOWNTO 0);  -- ufix18

BEGIN
  u_Trans_dq_alphabeta_123_ip_src_Trans_dq_alphabeta_123_fix_V1 : Trans_dq_alphabeta_123_ip_src_Trans_dq_alphabeta_123_fix_V1
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset => reset,
              theta => theta,  -- sfix24_En20
              theta_offset_AXI => theta_offset_AXI,  -- sfix24_En20
              CurrentValid_in => CurrentValid_in_sig,  -- ufix1
              Id_ref_AXI => Id_ref_AXI,  -- sfix18_En11
              Iq_ref_AXI => Iq_ref_AXI,  -- sfix18_En11
              ce_out => ce_out_sig,  -- ufix1
              dq_Done => dq_Done_sig,  -- ufix1
              sin => sin_sig,  -- sfix16_En14
              cos => cos_sig,  -- sfix16_En14
              ialpha => ialpha_sig,  -- sfix18_En11
              ialpha_AXI => ialpha_AXI_sig,  -- sfix18_En11
              ibeta => ibeta_sig,  -- sfix18_En11
              ibeta_AXI => ibeta_AXI_sig,  -- sfix18_En11
              i1 => i1_sig,  -- sfix18_En11
              i1_AXI => i1_AXI_sig,  -- sfix18_En11
              i2 => i2_sig,  -- sfix18_En11
              i2_AXI => i2_AXI_sig,  -- sfix18_En11
              i3 => i3_sig,  -- sfix18_En11
              i3_AXI => i3_AXI_sig  -- sfix18_En11
              );

  CurrentValid_in_sig <= CurrentValid_in;

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  dq_Done <= dq_Done_sig;

  sin <= sin_sig;

  cos <= cos_sig;

  ialpha <= ialpha_sig;

  ialpha_AXI <= ialpha_AXI_sig;

  ibeta <= ibeta_sig;

  ibeta_AXI <= ibeta_AXI_sig;

  i1 <= i1_sig;

  i1_AXI <= i1_AXI_sig;

  i2 <= i2_sig;

  i2_AXI <= i2_AXI_sig;

  i3 <= i3_sig;

  i3_AXI <= i3_AXI_sig;

END rtl;
