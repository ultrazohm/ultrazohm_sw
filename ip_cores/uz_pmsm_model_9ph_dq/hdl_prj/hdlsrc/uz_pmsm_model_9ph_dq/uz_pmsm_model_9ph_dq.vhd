-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj123\hdlsrc\uz_pmsm_model_9ph_dq\uz_pmsm_model_9ph_dq.vhd
-- Created: 2022-07-04 09:50:42
-- 
-- Generated by MATLAB 9.11 and HDL Coder 3.19
-- 
-- 
-- -------------------------------------------------------------
-- Rate and Clocking Details
-- -------------------------------------------------------------
-- Model base rate: -1
-- Target subsystem base rate: -1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: uz_pmsm_model_9ph_dq
-- Source Path: uz_pmsm_model_9ph_dq
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.uz_pmsm_model_9ph_dq_pkg.ALL;

ENTITY uz_pmsm_model_9ph_dq IS
  PORT( IPCORE_CLK                        :   IN    std_logic;  -- ufix1
        IPCORE_RESETN                     :   IN    std_logic;  -- ufix1
        voltage_input_dq_0                :   IN    std_logic_vector(242 DOWNTO 0);  -- ufix243
        AXI4_ACLK                         :   IN    std_logic;  -- ufix1
        AXI4_ARESETN                      :   IN    std_logic;  -- ufix1
        AXI4_AWID                         :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
        AXI4_AWADDR                       :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        AXI4_AWLEN                        :   IN    std_logic_vector(7 DOWNTO 0);  -- ufix8
        AXI4_AWSIZE                       :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        AXI4_AWBURST                      :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_AWLOCK                       :   IN    std_logic;  -- ufix1
        AXI4_AWCACHE                      :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        AXI4_AWPROT                       :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        AXI4_AWVALID                      :   IN    std_logic;  -- ufix1
        AXI4_WDATA                        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_WSTRB                        :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        AXI4_WLAST                        :   IN    std_logic;  -- ufix1
        AXI4_WVALID                       :   IN    std_logic;  -- ufix1
        AXI4_BREADY                       :   IN    std_logic;  -- ufix1
        AXI4_ARID                         :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
        AXI4_ARADDR                       :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        AXI4_ARLEN                        :   IN    std_logic_vector(7 DOWNTO 0);  -- ufix8
        AXI4_ARSIZE                       :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        AXI4_ARBURST                      :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_ARLOCK                       :   IN    std_logic;  -- ufix1
        AXI4_ARCACHE                      :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        AXI4_ARPROT                       :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        AXI4_ARVALID                      :   IN    std_logic;  -- ufix1
        AXI4_RREADY                       :   IN    std_logic;  -- ufix1
        theta_el_out                      :   OUT   std_logic_vector(17 DOWNTO 0);  -- ufix18
        currents_dq_out_0                 :   OUT   std_logic_vector(242 DOWNTO 0);  -- ufix243
        AXI4_AWREADY                      :   OUT   std_logic;  -- ufix1
        AXI4_WREADY                       :   OUT   std_logic;  -- ufix1
        AXI4_BID                          :   OUT   std_logic_vector(11 DOWNTO 0);  -- ufix12
        AXI4_BRESP                        :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_BVALID                       :   OUT   std_logic;  -- ufix1
        AXI4_ARREADY                      :   OUT   std_logic;  -- ufix1
        AXI4_RID                          :   OUT   std_logic_vector(11 DOWNTO 0);  -- ufix12
        AXI4_RDATA                        :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_RRESP                        :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_RLAST                        :   OUT   std_logic;  -- ufix1
        AXI4_RVALID                       :   OUT   std_logic  -- ufix1
        );
END uz_pmsm_model_9ph_dq;


ARCHITECTURE rtl OF uz_pmsm_model_9ph_dq IS

  -- Component Declarations
  COMPONENT uz_pmsm_model_9ph_dq_reset_sync
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset_in                        :   IN    std_logic;  -- ufix1
          reset_out                       :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_dq_axi4
    PORT( reset                           :   IN    std_logic;
          AXI4_ACLK                       :   IN    std_logic;  -- ufix1
          AXI4_ARESETN                    :   IN    std_logic;  -- ufix1
          AXI4_AWID                       :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
          AXI4_AWADDR                     :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          AXI4_AWLEN                      :   IN    std_logic_vector(7 DOWNTO 0);  -- ufix8
          AXI4_AWSIZE                     :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
          AXI4_AWBURST                    :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_AWLOCK                     :   IN    std_logic;  -- ufix1
          AXI4_AWCACHE                    :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI4_AWPROT                     :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
          AXI4_AWVALID                    :   IN    std_logic;  -- ufix1
          AXI4_WDATA                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_WSTRB                      :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI4_WLAST                      :   IN    std_logic;  -- ufix1
          AXI4_WVALID                     :   IN    std_logic;  -- ufix1
          AXI4_BREADY                     :   IN    std_logic;  -- ufix1
          AXI4_ARID                       :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
          AXI4_ARADDR                     :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          AXI4_ARLEN                      :   IN    std_logic_vector(7 DOWNTO 0);  -- ufix8
          AXI4_ARSIZE                     :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
          AXI4_ARBURST                    :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_ARLOCK                     :   IN    std_logic;  -- ufix1
          AXI4_ARCACHE                    :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI4_ARPROT                     :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
          AXI4_ARVALID                    :   IN    std_logic;  -- ufix1
          AXI4_RREADY                     :   IN    std_logic;  -- ufix1
          read_ip_timestamp               :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_theta_el_out_axi           :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_M_Mi_out_axi               :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_omega_mech_out_axi         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_currents_dq_out_axi        :   IN    vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
          read_voltage_input_dq_out_axi_fb :   IN    vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
          AXI4_AWREADY                    :   OUT   std_logic;  -- ufix1
          AXI4_WREADY                     :   OUT   std_logic;  -- ufix1
          AXI4_BID                        :   OUT   std_logic_vector(11 DOWNTO 0);  -- ufix12
          AXI4_BRESP                      :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_BVALID                     :   OUT   std_logic;  -- ufix1
          AXI4_ARREADY                    :   OUT   std_logic;  -- ufix1
          AXI4_RID                        :   OUT   std_logic_vector(11 DOWNTO 0);  -- ufix12
          AXI4_RDATA                      :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_RRESP                      :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_RLAST                      :   OUT   std_logic;  -- ufix1
          AXI4_RVALID                     :   OUT   std_logic;  -- ufix1
          write_axi_enable                :   OUT   std_logic;  -- ufix1
          write_reset_integrators         :   OUT   std_logic;  -- ufix1
          write_use_axi_input             :   OUT   std_logic;  -- ufix1
          write_simulate_mechanical       :   OUT   std_logic;  -- ufix1
          write_load_torque               :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_omega_mech                :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_voltage_input_dq_axi      :   OUT   vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
          write_physical_parameters_mu    :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_M_R0  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_1_L_d :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_1_L_q :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_R_1   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_polepair :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_psi_pm :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_x1  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_y1  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_x2  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_y2  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_x3  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_y3  :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_L_zero :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_physical_parameters_1_J   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          reset_internal                  :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  COMPONENT uz_pmsm_model_9ph_dq_dut
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset                           :   IN    std_logic;
          dut_enable                      :   IN    std_logic;  -- ufix1
          reset_integrators               :   IN    std_logic;  -- ufix1
          use_axi_input                   :   IN    std_logic;  -- ufix1
          simulate_mechanical             :   IN    std_logic;  -- ufix1
          load_torque                     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          omega_mech                      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_1_J         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_mu          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_M_R0        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_1_L_d       :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_1_L_q       :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_R_1         :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_polepair    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_psi_pm      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_x1        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_y1        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_x2        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_y2        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_x3        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_y3        :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          physical_parameters_L_zero      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_0          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_1          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_2          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_3          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_4          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_5          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_6          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_7          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_axi_8          :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_0              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_1              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_2              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_3              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_4              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_5              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_6              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_7              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          voltage_input_dq_8              :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          ce_out                          :   OUT   std_logic;  -- ufix1
          theta_el_out_axi                :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          theta_el_out                    :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En14
          M_Mi_out_axi                    :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          omega_mech_out_axi              :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_0           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_1           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_2           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_3           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_4           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_5           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_6           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_7           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_axi_8           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          currents_dq_out_0               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_1               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_2               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_3               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_4               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_5               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_6               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_7               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          currents_dq_out_8               :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En18
          voltage_input_dq_out_axi_fb_0   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_1   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_2   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_3   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_4   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_5   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_6   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_7   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          voltage_input_dq_out_axi_fb_8   :   OUT   std_logic_vector(31 DOWNTO 0)  -- ufix32
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_pmsm_model_9ph_dq_reset_sync
    USE ENTITY work.uz_pmsm_model_9ph_dq_reset_sync(rtl);

  FOR ALL : uz_pmsm_model_9ph_dq_axi4
    USE ENTITY work.uz_pmsm_model_9ph_dq_axi4(rtl);

  FOR ALL : uz_pmsm_model_9ph_dq_dut
    USE ENTITY work.uz_pmsm_model_9ph_dq_dut(rtl);

  -- Signals
  SIGNAL reset                            : std_logic;
  SIGNAL ip_timestamp                     : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL reset_cm                         : std_logic;  -- ufix1
  SIGNAL voltage_input_dq_0_unsigned      : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice         : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_0_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_1    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_1       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_1_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_2    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_2       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_2_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_3    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_3       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_3_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_4    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_4       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_4_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_5    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_5       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_5_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_6    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_6       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_6_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_7    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_7       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_7_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL voltage_input_dq_0_unsigned_8    : unsigned(242 DOWNTO 0);  -- ufix243
  SIGNAL voltage_input_dq_0_slice_8       : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL voltage_input_dq_8_sig           : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL write_voltage_input_dq_axi_unsigned : vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
  SIGNAL reset_internal                   : std_logic;  -- ufix1
  SIGNAL reset_before_sync                : std_logic;  -- ufix1
  SIGNAL read_voltage_input_dq_out_axi_fb_vec : vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
  SIGNAL read_currents_dq_out_axi_vec     : vector_of_std_logic_vector32(0 TO 8);  -- ufix32 [9]
  SIGNAL theta_el_out_axi_sig             : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL M_Mi_out_axi_sig                 : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL omega_mech_out_axi_sig           : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI4_BID_tmp                     : std_logic_vector(11 DOWNTO 0);  -- ufix12
  SIGNAL AXI4_BRESP_tmp                   : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL AXI4_RID_tmp                     : std_logic_vector(11 DOWNTO 0);  -- ufix12
  SIGNAL AXI4_RDATA_tmp                   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI4_RRESP_tmp                   : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL write_axi_enable                 : std_logic;  -- ufix1
  SIGNAL write_reset_integrators          : std_logic;  -- ufix1
  SIGNAL write_use_axi_input              : std_logic;  -- ufix1
  SIGNAL write_simulate_mechanical        : std_logic;  -- ufix1
  SIGNAL write_load_torque                : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_omega_mech                 : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_mu     : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_M_R0   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_1_L_d  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_1_L_q  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_R_1    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_polepair : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_psi_pm : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_x1   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_y1   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_x2   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_y2   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_x3   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_y3   : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_L_zero : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_physical_parameters_1_J    : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL theta_el_out_sig                 : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL currents_dq_out_0_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_1_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_2_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_3_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_4_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_5_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_6_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_7_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL currents_dq_out_8_sig            : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL theta_el_out_sig_signed          : signed(17 DOWNTO 0);  -- sfix18_En14
  SIGNAL theta_el_out_tmp                 : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL currents_dq_out_8_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_7_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_6_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_5_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_4_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_3_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_2_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_1_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_0_sig_signed     : signed(26 DOWNTO 0);  -- sfix27_En18
  SIGNAL currents_dq_out_0_tmp            : unsigned(242 DOWNTO 0);  -- ufix243

BEGIN
  u_uz_pmsm_model_9ph_dq_reset_sync_inst : uz_pmsm_model_9ph_dq_reset_sync
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset_in => reset_before_sync,  -- ufix1
              reset_out => reset
              );

  u_uz_pmsm_model_9ph_dq_axi4_inst : uz_pmsm_model_9ph_dq_axi4
    PORT MAP( reset => reset,
              AXI4_ACLK => AXI4_ACLK,  -- ufix1
              AXI4_ARESETN => AXI4_ARESETN,  -- ufix1
              AXI4_AWID => AXI4_AWID,  -- ufix12
              AXI4_AWADDR => AXI4_AWADDR,  -- ufix16
              AXI4_AWLEN => AXI4_AWLEN,  -- ufix8
              AXI4_AWSIZE => AXI4_AWSIZE,  -- ufix3
              AXI4_AWBURST => AXI4_AWBURST,  -- ufix2
              AXI4_AWLOCK => AXI4_AWLOCK,  -- ufix1
              AXI4_AWCACHE => AXI4_AWCACHE,  -- ufix4
              AXI4_AWPROT => AXI4_AWPROT,  -- ufix3
              AXI4_AWVALID => AXI4_AWVALID,  -- ufix1
              AXI4_WDATA => AXI4_WDATA,  -- ufix32
              AXI4_WSTRB => AXI4_WSTRB,  -- ufix4
              AXI4_WLAST => AXI4_WLAST,  -- ufix1
              AXI4_WVALID => AXI4_WVALID,  -- ufix1
              AXI4_BREADY => AXI4_BREADY,  -- ufix1
              AXI4_ARID => AXI4_ARID,  -- ufix12
              AXI4_ARADDR => AXI4_ARADDR,  -- ufix16
              AXI4_ARLEN => AXI4_ARLEN,  -- ufix8
              AXI4_ARSIZE => AXI4_ARSIZE,  -- ufix3
              AXI4_ARBURST => AXI4_ARBURST,  -- ufix2
              AXI4_ARLOCK => AXI4_ARLOCK,  -- ufix1
              AXI4_ARCACHE => AXI4_ARCACHE,  -- ufix4
              AXI4_ARPROT => AXI4_ARPROT,  -- ufix3
              AXI4_ARVALID => AXI4_ARVALID,  -- ufix1
              AXI4_RREADY => AXI4_RREADY,  -- ufix1
              read_ip_timestamp => std_logic_vector(ip_timestamp),  -- ufix32
              read_theta_el_out_axi => theta_el_out_axi_sig,  -- ufix32
              read_M_Mi_out_axi => M_Mi_out_axi_sig,  -- ufix32
              read_omega_mech_out_axi => omega_mech_out_axi_sig,  -- ufix32
              read_currents_dq_out_axi => read_currents_dq_out_axi_vec,  -- ufix32 [9]
              read_voltage_input_dq_out_axi_fb => read_voltage_input_dq_out_axi_fb_vec,  -- ufix32 [9]
              AXI4_AWREADY => AXI4_AWREADY,  -- ufix1
              AXI4_WREADY => AXI4_WREADY,  -- ufix1
              AXI4_BID => AXI4_BID_tmp,  -- ufix12
              AXI4_BRESP => AXI4_BRESP_tmp,  -- ufix2
              AXI4_BVALID => AXI4_BVALID,  -- ufix1
              AXI4_ARREADY => AXI4_ARREADY,  -- ufix1
              AXI4_RID => AXI4_RID_tmp,  -- ufix12
              AXI4_RDATA => AXI4_RDATA_tmp,  -- ufix32
              AXI4_RRESP => AXI4_RRESP_tmp,  -- ufix2
              AXI4_RLAST => AXI4_RLAST,  -- ufix1
              AXI4_RVALID => AXI4_RVALID,  -- ufix1
              write_axi_enable => write_axi_enable,  -- ufix1
              write_reset_integrators => write_reset_integrators,  -- ufix1
              write_use_axi_input => write_use_axi_input,  -- ufix1
              write_simulate_mechanical => write_simulate_mechanical,  -- ufix1
              write_load_torque => write_load_torque,  -- ufix32
              write_omega_mech => write_omega_mech,  -- ufix32
              write_voltage_input_dq_axi => write_voltage_input_dq_axi_unsigned,  -- ufix32 [9]
              write_physical_parameters_mu => write_physical_parameters_mu,  -- ufix32
              write_physical_parameters_M_R0 => write_physical_parameters_M_R0,  -- ufix32
              write_physical_parameters_1_L_d => write_physical_parameters_1_L_d,  -- ufix32
              write_physical_parameters_1_L_q => write_physical_parameters_1_L_q,  -- ufix32
              write_physical_parameters_R_1 => write_physical_parameters_R_1,  -- ufix32
              write_physical_parameters_polepair => write_physical_parameters_polepair,  -- ufix32
              write_physical_parameters_psi_pm => write_physical_parameters_psi_pm,  -- ufix32
              write_physical_parameters_L_x1 => write_physical_parameters_L_x1,  -- ufix32
              write_physical_parameters_L_y1 => write_physical_parameters_L_y1,  -- ufix32
              write_physical_parameters_L_x2 => write_physical_parameters_L_x2,  -- ufix32
              write_physical_parameters_L_y2 => write_physical_parameters_L_y2,  -- ufix32
              write_physical_parameters_L_x3 => write_physical_parameters_L_x3,  -- ufix32
              write_physical_parameters_L_y3 => write_physical_parameters_L_y3,  -- ufix32
              write_physical_parameters_L_zero => write_physical_parameters_L_zero,  -- ufix32
              write_physical_parameters_1_J => write_physical_parameters_1_J,  -- ufix32
              reset_internal => reset_internal  -- ufix1
              );

  u_uz_pmsm_model_9ph_dq_dut_inst : uz_pmsm_model_9ph_dq_dut
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset => reset,
              dut_enable => write_axi_enable,  -- ufix1
              reset_integrators => write_reset_integrators,  -- ufix1
              use_axi_input => write_use_axi_input,  -- ufix1
              simulate_mechanical => write_simulate_mechanical,  -- ufix1
              load_torque => write_load_torque,  -- ufix32
              omega_mech => write_omega_mech,  -- ufix32
              physical_parameters_1_J => write_physical_parameters_1_J,  -- ufix32
              physical_parameters_mu => write_physical_parameters_mu,  -- ufix32
              physical_parameters_M_R0 => write_physical_parameters_M_R0,  -- ufix32
              physical_parameters_1_L_d => write_physical_parameters_1_L_d,  -- ufix32
              physical_parameters_1_L_q => write_physical_parameters_1_L_q,  -- ufix32
              physical_parameters_R_1 => write_physical_parameters_R_1,  -- ufix32
              physical_parameters_polepair => write_physical_parameters_polepair,  -- ufix32
              physical_parameters_psi_pm => write_physical_parameters_psi_pm,  -- ufix32
              physical_parameters_L_x1 => write_physical_parameters_L_x1,  -- ufix32
              physical_parameters_L_y1 => write_physical_parameters_L_y1,  -- ufix32
              physical_parameters_L_x2 => write_physical_parameters_L_x2,  -- ufix32
              physical_parameters_L_y2 => write_physical_parameters_L_y2,  -- ufix32
              physical_parameters_L_x3 => write_physical_parameters_L_x3,  -- ufix32
              physical_parameters_L_y3 => write_physical_parameters_L_y3,  -- ufix32
              physical_parameters_L_zero => write_physical_parameters_L_zero,  -- ufix32
              voltage_input_dq_axi_0 => write_voltage_input_dq_axi_unsigned(0),  -- ufix32
              voltage_input_dq_axi_1 => write_voltage_input_dq_axi_unsigned(1),  -- ufix32
              voltage_input_dq_axi_2 => write_voltage_input_dq_axi_unsigned(2),  -- ufix32
              voltage_input_dq_axi_3 => write_voltage_input_dq_axi_unsigned(3),  -- ufix32
              voltage_input_dq_axi_4 => write_voltage_input_dq_axi_unsigned(4),  -- ufix32
              voltage_input_dq_axi_5 => write_voltage_input_dq_axi_unsigned(5),  -- ufix32
              voltage_input_dq_axi_6 => write_voltage_input_dq_axi_unsigned(6),  -- ufix32
              voltage_input_dq_axi_7 => write_voltage_input_dq_axi_unsigned(7),  -- ufix32
              voltage_input_dq_axi_8 => write_voltage_input_dq_axi_unsigned(8),  -- ufix32
              voltage_input_dq_0 => std_logic_vector(voltage_input_dq_0_sig),  -- sfix27_En16
              voltage_input_dq_1 => std_logic_vector(voltage_input_dq_1_sig),  -- sfix27_En16
              voltage_input_dq_2 => std_logic_vector(voltage_input_dq_2_sig),  -- sfix27_En16
              voltage_input_dq_3 => std_logic_vector(voltage_input_dq_3_sig),  -- sfix27_En16
              voltage_input_dq_4 => std_logic_vector(voltage_input_dq_4_sig),  -- sfix27_En16
              voltage_input_dq_5 => std_logic_vector(voltage_input_dq_5_sig),  -- sfix27_En16
              voltage_input_dq_6 => std_logic_vector(voltage_input_dq_6_sig),  -- sfix27_En16
              voltage_input_dq_7 => std_logic_vector(voltage_input_dq_7_sig),  -- sfix27_En16
              voltage_input_dq_8 => std_logic_vector(voltage_input_dq_8_sig),  -- sfix27_En16
              ce_out => ce_out_sig,  -- ufix1
              theta_el_out_axi => theta_el_out_axi_sig,  -- ufix32
              theta_el_out => theta_el_out_sig,  -- sfix18_En14
              M_Mi_out_axi => M_Mi_out_axi_sig,  -- ufix32
              omega_mech_out_axi => omega_mech_out_axi_sig,  -- ufix32
              currents_dq_out_axi_0 => read_currents_dq_out_axi_vec(0),  -- ufix32
              currents_dq_out_axi_1 => read_currents_dq_out_axi_vec(1),  -- ufix32
              currents_dq_out_axi_2 => read_currents_dq_out_axi_vec(2),  -- ufix32
              currents_dq_out_axi_3 => read_currents_dq_out_axi_vec(3),  -- ufix32
              currents_dq_out_axi_4 => read_currents_dq_out_axi_vec(4),  -- ufix32
              currents_dq_out_axi_5 => read_currents_dq_out_axi_vec(5),  -- ufix32
              currents_dq_out_axi_6 => read_currents_dq_out_axi_vec(6),  -- ufix32
              currents_dq_out_axi_7 => read_currents_dq_out_axi_vec(7),  -- ufix32
              currents_dq_out_axi_8 => read_currents_dq_out_axi_vec(8),  -- ufix32
              currents_dq_out_0 => currents_dq_out_0_sig,  -- sfix27_En18
              currents_dq_out_1 => currents_dq_out_1_sig,  -- sfix27_En18
              currents_dq_out_2 => currents_dq_out_2_sig,  -- sfix27_En18
              currents_dq_out_3 => currents_dq_out_3_sig,  -- sfix27_En18
              currents_dq_out_4 => currents_dq_out_4_sig,  -- sfix27_En18
              currents_dq_out_5 => currents_dq_out_5_sig,  -- sfix27_En18
              currents_dq_out_6 => currents_dq_out_6_sig,  -- sfix27_En18
              currents_dq_out_7 => currents_dq_out_7_sig,  -- sfix27_En18
              currents_dq_out_8 => currents_dq_out_8_sig,  -- sfix27_En18
              voltage_input_dq_out_axi_fb_0 => read_voltage_input_dq_out_axi_fb_vec(0),  -- ufix32
              voltage_input_dq_out_axi_fb_1 => read_voltage_input_dq_out_axi_fb_vec(1),  -- ufix32
              voltage_input_dq_out_axi_fb_2 => read_voltage_input_dq_out_axi_fb_vec(2),  -- ufix32
              voltage_input_dq_out_axi_fb_3 => read_voltage_input_dq_out_axi_fb_vec(3),  -- ufix32
              voltage_input_dq_out_axi_fb_4 => read_voltage_input_dq_out_axi_fb_vec(4),  -- ufix32
              voltage_input_dq_out_axi_fb_5 => read_voltage_input_dq_out_axi_fb_vec(5),  -- ufix32
              voltage_input_dq_out_axi_fb_6 => read_voltage_input_dq_out_axi_fb_vec(6),  -- ufix32
              voltage_input_dq_out_axi_fb_7 => read_voltage_input_dq_out_axi_fb_vec(7),  -- ufix32
              voltage_input_dq_out_axi_fb_8 => read_voltage_input_dq_out_axi_fb_vec(8)  -- ufix32
              );

  ip_timestamp <= unsigned'(X"838CC5B6");

  reset_cm <=  NOT IPCORE_RESETN;

  voltage_input_dq_0_unsigned <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice <= voltage_input_dq_0_unsigned(26 DOWNTO 0);

  voltage_input_dq_0_sig <= signed(voltage_input_dq_0_slice);

  voltage_input_dq_0_unsigned_1 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_1 <= voltage_input_dq_0_unsigned_1(53 DOWNTO 27);

  voltage_input_dq_1_sig <= signed(voltage_input_dq_0_slice_1);

  voltage_input_dq_0_unsigned_2 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_2 <= voltage_input_dq_0_unsigned_2(80 DOWNTO 54);

  voltage_input_dq_2_sig <= signed(voltage_input_dq_0_slice_2);

  voltage_input_dq_0_unsigned_3 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_3 <= voltage_input_dq_0_unsigned_3(107 DOWNTO 81);

  voltage_input_dq_3_sig <= signed(voltage_input_dq_0_slice_3);

  voltage_input_dq_0_unsigned_4 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_4 <= voltage_input_dq_0_unsigned_4(134 DOWNTO 108);

  voltage_input_dq_4_sig <= signed(voltage_input_dq_0_slice_4);

  voltage_input_dq_0_unsigned_5 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_5 <= voltage_input_dq_0_unsigned_5(161 DOWNTO 135);

  voltage_input_dq_5_sig <= signed(voltage_input_dq_0_slice_5);

  voltage_input_dq_0_unsigned_6 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_6 <= voltage_input_dq_0_unsigned_6(188 DOWNTO 162);

  voltage_input_dq_6_sig <= signed(voltage_input_dq_0_slice_6);

  voltage_input_dq_0_unsigned_7 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_7 <= voltage_input_dq_0_unsigned_7(215 DOWNTO 189);

  voltage_input_dq_7_sig <= signed(voltage_input_dq_0_slice_7);

  voltage_input_dq_0_unsigned_8 <= unsigned(voltage_input_dq_0);

  voltage_input_dq_0_slice_8 <= voltage_input_dq_0_unsigned_8(242 DOWNTO 216);

  voltage_input_dq_8_sig <= signed(voltage_input_dq_0_slice_8);

  reset_before_sync <= reset_cm OR reset_internal;



  theta_el_out_sig_signed <= signed(theta_el_out_sig);

  theta_el_out_tmp <= unsigned(theta_el_out_sig_signed);

  theta_el_out <= std_logic_vector(theta_el_out_tmp);

  currents_dq_out_8_sig_signed <= signed(currents_dq_out_8_sig);

  currents_dq_out_7_sig_signed <= signed(currents_dq_out_7_sig);

  currents_dq_out_6_sig_signed <= signed(currents_dq_out_6_sig);

  currents_dq_out_5_sig_signed <= signed(currents_dq_out_5_sig);

  currents_dq_out_4_sig_signed <= signed(currents_dq_out_4_sig);

  currents_dq_out_3_sig_signed <= signed(currents_dq_out_3_sig);

  currents_dq_out_2_sig_signed <= signed(currents_dq_out_2_sig);

  currents_dq_out_1_sig_signed <= signed(currents_dq_out_1_sig);

  currents_dq_out_0_sig_signed <= signed(currents_dq_out_0_sig);

  currents_dq_out_0_tmp <= unsigned(currents_dq_out_8_sig_signed) & unsigned(currents_dq_out_7_sig_signed) & unsigned(currents_dq_out_6_sig_signed) & unsigned(currents_dq_out_5_sig_signed) & unsigned(currents_dq_out_4_sig_signed) & unsigned(currents_dq_out_3_sig_signed) & unsigned(currents_dq_out_2_sig_signed) & unsigned(currents_dq_out_1_sig_signed) & unsigned(currents_dq_out_0_sig_signed);

  currents_dq_out_0 <= std_logic_vector(currents_dq_out_0_tmp);

  AXI4_BID <= AXI4_BID_tmp;

  AXI4_BRESP <= AXI4_BRESP_tmp;

  AXI4_RID <= AXI4_RID_tmp;

  AXI4_RDATA <= AXI4_RDATA_tmp;

  AXI4_RRESP <= AXI4_RRESP_tmp;

END rtl;

