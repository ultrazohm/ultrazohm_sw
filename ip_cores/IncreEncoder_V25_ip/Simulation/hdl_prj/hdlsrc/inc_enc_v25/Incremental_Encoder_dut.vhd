-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\inc_enc_v25\Incremental_Encoder_dut.vhd
-- Created: 2022-04-20 12:43:31
-- 
-- Generated by MATLAB 9.12 and HDL Coder 3.20
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Incremental_Encoder_dut
-- Source Path: Incremental_Encoder/Incremental_Encoder_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Incremental_Encoder_dut IS
  PORT( clk                               :   IN    std_logic;
        reset_x                           :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        A                                 :   IN    std_logic;  -- ufix1
        B                                 :   IN    std_logic;  -- ufix1
        I                                 :   IN    std_logic;  -- ufix1
        PI2_Inc_AXI4                      :   IN    std_logic_vector(23 DOWNTO 0);  -- ufix24_En24
        Timer_FPGA_ms_AXI4                :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32_En32
        IncPerTurn_mech_AXI4              :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        IncPerTurn_elek_AXI4              :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        OmegaPerOverSampl_AXI4            :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        PeriodEnd                         :   IN    std_logic;  -- ufix1
        timeout_value_AXI4                :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        ce_out                            :   OUT   std_logic;  -- ufix1
        omega                             :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        omega_AXI4                        :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        theta_el                          :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        theta_el_AXI4                     :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
        position                          :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
        position_AXI4                     :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
        edge_rsvd                         :   OUT   std_logic;  -- ufix1
        count                             :   OUT   std_logic;  -- ufix1
        direction_AXI4                    :   OUT   std_logic_vector(3 DOWNTO 0);  -- sfix4
        countPerPeriod_AXI4               :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16
        OverSamplFactor                   :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
        omega_MA_N4                       :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        omega_MA_N4_AXI                   :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        timeout_active                    :   OUT   std_logic;  -- ufix1
        omegaA                            :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        omegaNOTA                         :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        omegaB                            :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        omegaNOTB                         :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
        new_measurement                   :   OUT   std_logic  -- ufix1
        );
END Incremental_Encoder_dut;


ARCHITECTURE rtl OF Incremental_Encoder_dut IS

  -- Component Declarations
  COMPONENT Incremental_Encoder_src_IncEnc_V25
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset_x                         :   IN    std_logic;
          A                               :   IN    std_logic;  -- ufix1
          B                               :   IN    std_logic;  -- ufix1
          I                               :   IN    std_logic;  -- ufix1
          PI2_Inc_AXI4                    :   IN    std_logic_vector(23 DOWNTO 0);  -- ufix24_En24
          Timer_FPGA_ms_AXI4              :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32_En32
          IncPerTurn_mech_AXI4            :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          IncPerTurn_elek_AXI4            :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          OmegaPerOverSampl_AXI4          :   IN    std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          PeriodEnd                       :   IN    std_logic;  -- ufix1
          timeout_value_AXI4              :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          ce_out                          :   OUT   std_logic;  -- ufix1
          omega                           :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          omega_AXI4                      :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          theta_el                        :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
          theta_el_AXI4                   :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En20
          position                        :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
          position_AXI4                   :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
          edge_rsvd                       :   OUT   std_logic;  -- ufix1
          count                           :   OUT   std_logic;  -- ufix1
          direction_AXI4                  :   OUT   std_logic_vector(3 DOWNTO 0);  -- sfix4
          countPerPeriod_AXI4             :   OUT   std_logic_vector(15 DOWNTO 0);  -- sfix16
          OverSamplFactor                 :   OUT   std_logic_vector(15 DOWNTO 0);  -- ufix16
          omega_MA_N4                     :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          omega_MA_N4_AXI                 :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          timeout_active                  :   OUT   std_logic;  -- ufix1
          omegaA                          :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          omegaNOTA                       :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          omegaB                          :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          omegaNOTB                       :   OUT   std_logic_vector(23 DOWNTO 0);  -- sfix24_En11
          new_measurement                 :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : Incremental_Encoder_src_IncEnc_V25
    USE ENTITY work.Incremental_Encoder_src_IncEnc_V25(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL A_sig                            : std_logic;  -- ufix1
  SIGNAL B_sig                            : std_logic;  -- ufix1
  SIGNAL I_sig                            : std_logic;  -- ufix1
  SIGNAL PeriodEnd_sig                    : std_logic;  -- ufix1
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL omega_sig                        : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL omega_AXI4_sig                   : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL theta_el_sig                     : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL theta_el_AXI4_sig                : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL position_sig                     : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL position_AXI4_sig                : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL edge_rsvd_sig                    : std_logic;  -- ufix1
  SIGNAL count_sig                        : std_logic;  -- ufix1
  SIGNAL direction_AXI4_sig               : std_logic_vector(3 DOWNTO 0);  -- ufix4
  SIGNAL countPerPeriod_AXI4_sig          : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL OverSamplFactor_sig              : std_logic_vector(15 DOWNTO 0);  -- ufix16
  SIGNAL omega_MA_N4_sig                  : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL omega_MA_N4_AXI_sig              : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL timeout_active_sig               : std_logic;  -- ufix1
  SIGNAL omegaA_sig                       : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL omegaNOTA_sig                    : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL omegaB_sig                       : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL omegaNOTB_sig                    : std_logic_vector(23 DOWNTO 0);  -- ufix24
  SIGNAL new_measurement_sig              : std_logic;  -- ufix1

BEGIN
  u_Incremental_Encoder_src_IncEnc_V25 : Incremental_Encoder_src_IncEnc_V25
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset_x => reset_x,
              A => A_sig,  -- ufix1
              B => B_sig,  -- ufix1
              I => I_sig,  -- ufix1
              PI2_Inc_AXI4 => PI2_Inc_AXI4,  -- ufix24_En24
              Timer_FPGA_ms_AXI4 => Timer_FPGA_ms_AXI4,  -- ufix32_En32
              IncPerTurn_mech_AXI4 => IncPerTurn_mech_AXI4,  -- ufix16
              IncPerTurn_elek_AXI4 => IncPerTurn_elek_AXI4,  -- ufix16
              OmegaPerOverSampl_AXI4 => OmegaPerOverSampl_AXI4,  -- sfix24_En11
              PeriodEnd => PeriodEnd_sig,  -- ufix1
              timeout_value_AXI4 => timeout_value_AXI4,  -- ufix32
              ce_out => ce_out_sig,  -- ufix1
              omega => omega_sig,  -- sfix24_En11
              omega_AXI4 => omega_AXI4_sig,  -- sfix24_En11
              theta_el => theta_el_sig,  -- sfix24_En20
              theta_el_AXI4 => theta_el_AXI4_sig,  -- sfix24_En20
              position => position_sig,  -- ufix16
              position_AXI4 => position_AXI4_sig,  -- ufix16
              edge_rsvd => edge_rsvd_sig,  -- ufix1
              count => count_sig,  -- ufix1
              direction_AXI4 => direction_AXI4_sig,  -- sfix4
              countPerPeriod_AXI4 => countPerPeriod_AXI4_sig,  -- sfix16
              OverSamplFactor => OverSamplFactor_sig,  -- ufix16
              omega_MA_N4 => omega_MA_N4_sig,  -- sfix24_En11
              omega_MA_N4_AXI => omega_MA_N4_AXI_sig,  -- sfix24_En11
              timeout_active => timeout_active_sig,  -- ufix1
              omegaA => omegaA_sig,  -- sfix24_En11
              omegaNOTA => omegaNOTA_sig,  -- sfix24_En11
              omegaB => omegaB_sig,  -- sfix24_En11
              omegaNOTB => omegaNOTB_sig,  -- sfix24_En11
              new_measurement => new_measurement_sig  -- ufix1
              );

  A_sig <= A;

  B_sig <= B;

  I_sig <= I;

  PeriodEnd_sig <= PeriodEnd;

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  omega <= omega_sig;

  omega_AXI4 <= omega_AXI4_sig;

  theta_el <= theta_el_sig;

  theta_el_AXI4 <= theta_el_AXI4_sig;

  position <= position_sig;

  position_AXI4 <= position_AXI4_sig;

  edge_rsvd <= edge_rsvd_sig;

  count <= count_sig;

  direction_AXI4 <= direction_AXI4_sig;

  countPerPeriod_AXI4 <= countPerPeriod_AXI4_sig;

  OverSamplFactor <= OverSamplFactor_sig;

  omega_MA_N4 <= omega_MA_N4_sig;

  omega_MA_N4_AXI <= omega_MA_N4_AXI_sig;

  timeout_active <= timeout_active_sig;

  omegaA <= omegaA_sig;

  omegaNOTA <= omegaNOTA_sig;

  omegaB <= omegaB_sig;

  omegaNOTB <= omegaNOTB_sig;

  new_measurement <= new_measurement_sig;

END rtl;
