-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_pmsm_model_9ph\hdl_opti\hdlsrc\uz_pmsm_model_9ph\uz_pmsm_model_9ph_opti_dut.vhd
-- Created: 2022-05-03 13:56:31
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_9ph_opti_dut
-- Source Path: uz_pmsm_model_9ph_opti/uz_pmsm_model_9ph_opti_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_pmsm_model_9ph_opti_dut IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        Model_Parameter_reset_integrators :   IN    std_logic;  -- ufix1
        Model_Parameter_simulate_mechanical :   IN    std_logic;  -- ufix1
        Model_Parameter_switch_pspl       :   IN    std_logic;  -- ufix1
        Model_Parameter_control_dq_abc    :   IN    std_logic;  -- ufix1
        physical_parameters_1_J           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_mu            :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_M_R0          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_1_L_d         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_1_L_q         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_R_1           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_polepair      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_psi_pm        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_z1          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_z2          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_x1          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_y1          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_x2          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_y2          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        physical_parameters_L_z3          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        input_0                           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        input_1                           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        input_2                           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        input_3                           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        u_abc1_pl_0                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc1_pl_1                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc1_pl_2                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc2_pl_0                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc2_pl_1                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc2_pl_2                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc3_pl_0                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc3_pl_1                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        u_abc3_pl_2                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        in_theta_el                       :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        ce_out                            :   OUT   std_logic;  -- ufix1
        outputs_0                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        outputs_1                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        outputs_2                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_0                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_1                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_2                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_3                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_4                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_5                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_6                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_7                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_dq_ps_8                         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        i_abc1_pl_0                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc1_pl_1                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc1_pl_2                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc2_pl_0                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc2_pl_1                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc2_pl_2                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc3_pl_0                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc3_pl_1                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        i_abc3_pl_2                       :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
        out_theta_el                      :   OUT   std_logic_vector(24 DOWNTO 0)  -- sfix25_En12
        );
END uz_pmsm_model_9ph_opti_dut;


ARCHITECTURE rtl OF uz_pmsm_model_9ph_opti_dut IS

  -- Component Declarations
  COMPONENT uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset                           :   IN    std_logic;
          Model_Parameter_reset_integrators :   IN    std_logic;  -- ufix1
          Model_Parameter_simulate_mechanical :   IN    std_logic;  -- ufix1
          Model_Parameter_switch_pspl     :   IN    std_logic;  -- ufix1
          Model_Parameter_control_dq_abc  :   IN    std_logic;  -- ufix1
          physical_parameters_1_J         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_mu          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_M_R0        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_1_L_d       :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_1_L_q       :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_R_1         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_polepair    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_psi_pm      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_z1        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_z2        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_x1        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_y1        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_x2        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_y2        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_z3        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          input_0                         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          input_1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          input_2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          input_3                         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          u_abc1_pl_0                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc1_pl_1                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc1_pl_2                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc2_pl_0                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc2_pl_1                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc2_pl_2                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc3_pl_0                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc3_pl_1                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          u_abc3_pl_2                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          in_theta_el                     :   IN    std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          ce_out                          :   OUT   std_logic;  -- ufix1
          outputs_0                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          outputs_1                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          outputs_2                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_0                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_1                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_2                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_3                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_4                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_5                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_6                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_7                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_dq_ps_8                       :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          i_abc1_pl_0                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc1_pl_1                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc1_pl_2                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc2_pl_0                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc2_pl_1                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc2_pl_2                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc3_pl_0                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc3_pl_1                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          i_abc3_pl_2                     :   OUT   std_logic_vector(24 DOWNTO 0);  -- sfix25_En12
          out_theta_el                    :   OUT   std_logic_vector(24 DOWNTO 0)  -- sfix25_En12
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph
    USE ENTITY work.uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL outputs_0_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL outputs_1_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL outputs_2_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_0_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_1_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_2_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_3_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_4_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_5_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_6_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_7_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_dq_ps_8_sig                    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL i_abc1_pl_0_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc1_pl_1_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc1_pl_2_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc2_pl_0_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc2_pl_1_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc2_pl_2_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc3_pl_0_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc3_pl_1_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL i_abc3_pl_2_sig                  : std_logic_vector(24 DOWNTO 0);  -- ufix25
  SIGNAL out_theta_el_sig                 : std_logic_vector(24 DOWNTO 0);  -- ufix25

BEGIN
  u_uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph : uz_pmsm_model_9ph_opti_src_uz_pmsm_model_9ph
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset => reset,
              Model_Parameter_reset_integrators => Model_Parameter_reset_integrators,  -- ufix1
              Model_Parameter_simulate_mechanical => Model_Parameter_simulate_mechanical,  -- ufix1
              Model_Parameter_switch_pspl => Model_Parameter_switch_pspl,  -- ufix1
              Model_Parameter_control_dq_abc => Model_Parameter_control_dq_abc,  -- ufix1
              physical_parameters_1_J => physical_parameters_1_J,  -- ufix32
              physical_parameters_mu => physical_parameters_mu,  -- ufix32
              physical_parameters_M_R0 => physical_parameters_M_R0,  -- ufix32
              physical_parameters_1_L_d => physical_parameters_1_L_d,  -- ufix32
              physical_parameters_1_L_q => physical_parameters_1_L_q,  -- ufix32
              physical_parameters_R_1 => physical_parameters_R_1,  -- ufix32
              physical_parameters_polepair => physical_parameters_polepair,  -- ufix32
              physical_parameters_psi_pm => physical_parameters_psi_pm,  -- ufix32
              physical_parameters_L_z1 => physical_parameters_L_z1,  -- ufix32
              physical_parameters_L_z2 => physical_parameters_L_z2,  -- ufix32
              physical_parameters_L_x1 => physical_parameters_L_x1,  -- ufix32
              physical_parameters_L_y1 => physical_parameters_L_y1,  -- ufix32
              physical_parameters_L_x2 => physical_parameters_L_x2,  -- ufix32
              physical_parameters_L_y2 => physical_parameters_L_y2,  -- ufix32
              physical_parameters_L_z3 => physical_parameters_L_z3,  -- ufix32
              input_0 => input_0,  -- ufix32
              input_1 => input_1,  -- ufix32
              input_2 => input_2,  -- ufix32
              input_3 => input_3,  -- ufix32
              u_abc1_pl_0 => u_abc1_pl_0,  -- sfix25_En12
              u_abc1_pl_1 => u_abc1_pl_1,  -- sfix25_En12
              u_abc1_pl_2 => u_abc1_pl_2,  -- sfix25_En12
              u_abc2_pl_0 => u_abc2_pl_0,  -- sfix25_En12
              u_abc2_pl_1 => u_abc2_pl_1,  -- sfix25_En12
              u_abc2_pl_2 => u_abc2_pl_2,  -- sfix25_En12
              u_abc3_pl_0 => u_abc3_pl_0,  -- sfix25_En12
              u_abc3_pl_1 => u_abc3_pl_1,  -- sfix25_En12
              u_abc3_pl_2 => u_abc3_pl_2,  -- sfix25_En12
              in_theta_el => in_theta_el,  -- sfix25_En12
              ce_out => ce_out_sig,  -- ufix1
              outputs_0 => outputs_0_sig,  -- ufix32
              outputs_1 => outputs_1_sig,  -- ufix32
              outputs_2 => outputs_2_sig,  -- ufix32
              i_dq_ps_0 => i_dq_ps_0_sig,  -- ufix32
              i_dq_ps_1 => i_dq_ps_1_sig,  -- ufix32
              i_dq_ps_2 => i_dq_ps_2_sig,  -- ufix32
              i_dq_ps_3 => i_dq_ps_3_sig,  -- ufix32
              i_dq_ps_4 => i_dq_ps_4_sig,  -- ufix32
              i_dq_ps_5 => i_dq_ps_5_sig,  -- ufix32
              i_dq_ps_6 => i_dq_ps_6_sig,  -- ufix32
              i_dq_ps_7 => i_dq_ps_7_sig,  -- ufix32
              i_dq_ps_8 => i_dq_ps_8_sig,  -- ufix32
              i_abc1_pl_0 => i_abc1_pl_0_sig,  -- sfix25_En12
              i_abc1_pl_1 => i_abc1_pl_1_sig,  -- sfix25_En12
              i_abc1_pl_2 => i_abc1_pl_2_sig,  -- sfix25_En12
              i_abc2_pl_0 => i_abc2_pl_0_sig,  -- sfix25_En12
              i_abc2_pl_1 => i_abc2_pl_1_sig,  -- sfix25_En12
              i_abc2_pl_2 => i_abc2_pl_2_sig,  -- sfix25_En12
              i_abc3_pl_0 => i_abc3_pl_0_sig,  -- sfix25_En12
              i_abc3_pl_1 => i_abc3_pl_1_sig,  -- sfix25_En12
              i_abc3_pl_2 => i_abc3_pl_2_sig,  -- sfix25_En12
              out_theta_el => out_theta_el_sig  -- sfix25_En12
              );

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  outputs_0 <= outputs_0_sig;

  outputs_1 <= outputs_1_sig;

  outputs_2 <= outputs_2_sig;

  i_dq_ps_0 <= i_dq_ps_0_sig;

  i_dq_ps_1 <= i_dq_ps_1_sig;

  i_dq_ps_2 <= i_dq_ps_2_sig;

  i_dq_ps_3 <= i_dq_ps_3_sig;

  i_dq_ps_4 <= i_dq_ps_4_sig;

  i_dq_ps_5 <= i_dq_ps_5_sig;

  i_dq_ps_6 <= i_dq_ps_6_sig;

  i_dq_ps_7 <= i_dq_ps_7_sig;

  i_dq_ps_8 <= i_dq_ps_8_sig;

  i_abc1_pl_0 <= i_abc1_pl_0_sig;

  i_abc1_pl_1 <= i_abc1_pl_1_sig;

  i_abc1_pl_2 <= i_abc1_pl_2_sig;

  i_abc2_pl_0 <= i_abc2_pl_0_sig;

  i_abc2_pl_1 <= i_abc2_pl_1_sig;

  i_abc2_pl_2 <= i_abc2_pl_2_sig;

  i_abc3_pl_0 <= i_abc3_pl_0_sig;

  i_abc3_pl_1 <= i_abc3_pl_1_sig;

  i_abc3_pl_2 <= i_abc3_pl_2_sig;

  out_theta_el <= out_theta_el_sig;

END rtl;
