-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\uz_mpc_cost_and_optim_state_machine\uz_6_ph_voltages_ip_dut.vhd
-- Created: 2022-10-04 11:16:09
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_6_ph_voltages_ip_dut
-- Source Path: uz_6_ph_voltages_ip/uz_6_ph_voltages_ip_dut
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_6_ph_voltages_ip_dut IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        dut_enable                        :   IN    std_logic;  -- ufix1
        v_DC_pu                           :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
        sin_angle                         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        cos_angle                         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
        index                             :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        index_select                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        index_AXI                         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        trigger_park_done                 :   IN    std_logic;  -- ufix1
        trigger_prediction_done           :   IN    std_logic;  -- ufix1
        trigger_delay_comp_done           :   IN    std_logic;  -- ufix1
        last_opt_index                    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        ce_out                            :   OUT   std_logic;  -- ufix1
        pu_vd                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vq                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vx                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vy                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vd_AXI                         :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vq_AXI                         :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vx_AXI                         :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        pu_vy_AXI                         :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
        voltages_done                     :   OUT   std_logic  -- ufix1
        );
END uz_6_ph_voltages_ip_dut;


ARCHITECTURE rtl OF uz_6_ph_voltages_ip_dut IS

  -- Component Declarations
  COMPONENT uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd
    PORT( clk                             :   IN    std_logic;
          clk_enable                      :   IN    std_logic;
          reset                           :   IN    std_logic;
          v_DC_pu                         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          sin_angle                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
          cos_angle                       :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En16
          index                           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          index_select                    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          index_AXI                       :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          trigger_park_done               :   IN    std_logic;  -- ufix1
          trigger_prediction_done         :   IN    std_logic;  -- ufix1
          trigger_delay_comp_done         :   IN    std_logic;  -- ufix1
          last_opt_index                  :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          ce_out                          :   OUT   std_logic;  -- ufix1
          pu_vd                           :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vq                           :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vx                           :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vy                           :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vd_AXI                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vq_AXI                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vx_AXI                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          pu_vy_AXI                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          voltages_done                   :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd
    USE ENTITY work.uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd(rtl);

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL trigger_park_done_sig            : std_logic;  -- ufix1
  SIGNAL trigger_prediction_done_sig      : std_logic;  -- ufix1
  SIGNAL trigger_delay_comp_done_sig      : std_logic;  -- ufix1
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL pu_vd_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vq_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vx_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vy_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vd_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vq_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vx_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vy_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL voltages_done_sig                : std_logic;  -- ufix1

BEGIN
  u_uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd : uz_6_ph_voltages_ip_src_uz_6ph_mpc_pu_voltages_vsd
    PORT MAP( clk => clk,
              clk_enable => enb,
              reset => reset,
              v_DC_pu => v_DC_pu,  -- sfix18_En15
              sin_angle => sin_angle,  -- sfix18_En16
              cos_angle => cos_angle,  -- sfix18_En16
              index => index,  -- ufix32
              index_select => index_select,  -- ufix32
              index_AXI => index_AXI,  -- ufix32
              trigger_park_done => trigger_park_done_sig,  -- ufix1
              trigger_prediction_done => trigger_prediction_done_sig,  -- ufix1
              trigger_delay_comp_done => trigger_delay_comp_done_sig,  -- ufix1
              last_opt_index => last_opt_index,  -- ufix32
              ce_out => ce_out_sig,  -- ufix1
              pu_vd => pu_vd_sig,  -- sfix27_En24
              pu_vq => pu_vq_sig,  -- sfix27_En24
              pu_vx => pu_vx_sig,  -- sfix27_En24
              pu_vy => pu_vy_sig,  -- sfix27_En24
              pu_vd_AXI => pu_vd_AXI_sig,  -- sfix27_En24
              pu_vq_AXI => pu_vq_AXI_sig,  -- sfix27_En24
              pu_vx_AXI => pu_vx_AXI_sig,  -- sfix27_En24
              pu_vy_AXI => pu_vy_AXI_sig,  -- sfix27_En24
              voltages_done => voltages_done_sig  -- ufix1
              );

  trigger_park_done_sig <= trigger_park_done;

  trigger_prediction_done_sig <= trigger_prediction_done;

  trigger_delay_comp_done_sig <= trigger_delay_comp_done;

  enb <= dut_enable;

  ce_out <= ce_out_sig;

  pu_vd <= pu_vd_sig;

  pu_vq <= pu_vq_sig;

  pu_vx <= pu_vx_sig;

  pu_vy <= pu_vy_sig;

  pu_vd_AXI <= pu_vd_AXI_sig;

  pu_vq_AXI <= pu_vq_AXI_sig;

  pu_vx_AXI <= pu_vx_AXI_sig;

  pu_vy_AXI <= pu_vy_AXI_sig;

  voltages_done <= voltages_done_sig;

END rtl;
