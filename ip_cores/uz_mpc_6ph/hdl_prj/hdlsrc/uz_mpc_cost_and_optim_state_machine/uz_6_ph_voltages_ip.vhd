-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\uz_mpc_cost_and_optim_state_machine\uz_6_ph_voltages_ip.vhd
-- Created: 2022-10-04 11:16:09
-- 
-- Generated by MATLAB 9.10 and HDL Coder 3.18
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
-- Module: uz_6_ph_voltages_ip
-- Source Path: uz_6_ph_voltages_ip
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_6_ph_voltages_ip IS
  PORT( IPCORE_CLK                        :   IN    std_logic;  -- ufix1
        IPCORE_RESETN                     :   IN    std_logic;  -- ufix1
        v_DC_pu                           :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18
        sin_angle                         :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18
        cos_angle                         :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18
        index                             :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        trigger_park_done                 :   IN    std_logic;  -- ufix1
        trigger_prediction_done           :   IN    std_logic;  -- ufix1
        trigger_delay_comp_done           :   IN    std_logic;  -- ufix1
        last_opt_index                    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_Lite_ACLK                    :   IN    std_logic;  -- ufix1
        AXI4_Lite_ARESETN                 :   IN    std_logic;  -- ufix1
        AXI4_Lite_AWADDR                  :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        AXI4_Lite_AWVALID                 :   IN    std_logic;  -- ufix1
        AXI4_Lite_WDATA                   :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_Lite_WSTRB                   :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        AXI4_Lite_WVALID                  :   IN    std_logic;  -- ufix1
        AXI4_Lite_BREADY                  :   IN    std_logic;  -- ufix1
        AXI4_Lite_ARADDR                  :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
        AXI4_Lite_ARVALID                 :   IN    std_logic;  -- ufix1
        AXI4_Lite_RREADY                  :   IN    std_logic;  -- ufix1
        pu_vd                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        pu_vq                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        pu_vx                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        pu_vy                             :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        voltages_done                     :   OUT   std_logic;  -- ufix1
        AXI4_Lite_AWREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_WREADY                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_BRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_BVALID                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_ARREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_RDATA                   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_Lite_RRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_RVALID                  :   OUT   std_logic  -- ufix1
        );
END uz_6_ph_voltages_ip;


ARCHITECTURE rtl OF uz_6_ph_voltages_ip IS

  -- Component Declarations
  COMPONENT uz_6_ph_voltages_ip_reset_sync
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset_in                        :   IN    std_logic;  -- ufix1
          reset_out                       :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT uz_6_ph_voltages_ip_axi_lite
    PORT( reset                           :   IN    std_logic;
          AXI4_Lite_ACLK                  :   IN    std_logic;  -- ufix1
          AXI4_Lite_ARESETN               :   IN    std_logic;  -- ufix1
          AXI4_Lite_AWADDR                :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          AXI4_Lite_AWVALID               :   IN    std_logic;  -- ufix1
          AXI4_Lite_WDATA                 :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_Lite_WSTRB                 :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI4_Lite_WVALID                :   IN    std_logic;  -- ufix1
          AXI4_Lite_BREADY                :   IN    std_logic;  -- ufix1
          AXI4_Lite_ARADDR                :   IN    std_logic_vector(15 DOWNTO 0);  -- ufix16
          AXI4_Lite_ARVALID               :   IN    std_logic;  -- ufix1
          AXI4_Lite_RREADY                :   IN    std_logic;  -- ufix1
          read_ip_timestamp               :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_pu_vd_AXI                  :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_pu_vq_AXI                  :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_pu_vx_AXI                  :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_pu_vy_AXI                  :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          AXI4_Lite_AWREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_WREADY                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_BRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_BVALID                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_ARREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_RDATA                 :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_Lite_RRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_RVALID                :   OUT   std_logic;  -- ufix1
          write_axi_enable                :   OUT   std_logic;  -- ufix1
          write_index_select              :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          write_index_AXI                 :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          reset_internal                  :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  COMPONENT uz_6_ph_voltages_ip_dut
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset                           :   IN    std_logic;
          dut_enable                      :   IN    std_logic;  -- ufix1
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
  FOR ALL : uz_6_ph_voltages_ip_reset_sync
    USE ENTITY work.uz_6_ph_voltages_ip_reset_sync(rtl);

  FOR ALL : uz_6_ph_voltages_ip_axi_lite
    USE ENTITY work.uz_6_ph_voltages_ip_axi_lite(rtl);

  FOR ALL : uz_6_ph_voltages_ip_dut
    USE ENTITY work.uz_6_ph_voltages_ip_dut(rtl);

  -- Signals
  SIGNAL reset                            : std_logic;
  SIGNAL ip_timestamp                     : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL reset_cm                         : std_logic;  -- ufix1
  SIGNAL v_DC_pu_unsigned                 : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL v_DC_pu_sig                      : signed(17 DOWNTO 0);  -- sfix18_En15
  SIGNAL sin_angle_unsigned               : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL sin_angle_sig                    : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL cos_angle_unsigned               : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL cos_angle_sig                    : signed(17 DOWNTO 0);  -- sfix18_En16
  SIGNAL reset_internal                   : std_logic;  -- ufix1
  SIGNAL reset_before_sync                : std_logic;  -- ufix1
  SIGNAL pu_vd_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vq_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vx_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vy_AXI_sig                    : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL AXI4_Lite_BRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL AXI4_Lite_RDATA_tmp              : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI4_Lite_RRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL write_axi_enable                 : std_logic;  -- ufix1
  SIGNAL write_index_select               : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL write_index_AXI                  : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL pu_vd_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vq_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vx_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vy_sig                        : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL voltages_done_sig                : std_logic;  -- ufix1
  SIGNAL pu_vd_sig_signed                 : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL pu_vd_tmp                        : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vq_sig_signed                 : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL pu_vq_tmp                        : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vx_sig_signed                 : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL pu_vx_tmp                        : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL pu_vy_sig_signed                 : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL pu_vy_tmp                        : unsigned(26 DOWNTO 0);  -- ufix27

BEGIN
  u_uz_6_ph_voltages_ip_reset_sync_inst : uz_6_ph_voltages_ip_reset_sync
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset_in => reset_before_sync,  -- ufix1
              reset_out => reset
              );

  u_uz_6_ph_voltages_ip_axi_lite_inst : uz_6_ph_voltages_ip_axi_lite
    PORT MAP( reset => reset,
              AXI4_Lite_ACLK => AXI4_Lite_ACLK,  -- ufix1
              AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,  -- ufix1
              AXI4_Lite_AWADDR => AXI4_Lite_AWADDR,  -- ufix16
              AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,  -- ufix1
              AXI4_Lite_WDATA => AXI4_Lite_WDATA,  -- ufix32
              AXI4_Lite_WSTRB => AXI4_Lite_WSTRB,  -- ufix4
              AXI4_Lite_WVALID => AXI4_Lite_WVALID,  -- ufix1
              AXI4_Lite_BREADY => AXI4_Lite_BREADY,  -- ufix1
              AXI4_Lite_ARADDR => AXI4_Lite_ARADDR,  -- ufix16
              AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,  -- ufix1
              AXI4_Lite_RREADY => AXI4_Lite_RREADY,  -- ufix1
              read_ip_timestamp => std_logic_vector(ip_timestamp),  -- ufix32
              read_pu_vd_AXI => pu_vd_AXI_sig,  -- sfix27_En24
              read_pu_vq_AXI => pu_vq_AXI_sig,  -- sfix27_En24
              read_pu_vx_AXI => pu_vx_AXI_sig,  -- sfix27_En24
              read_pu_vy_AXI => pu_vy_AXI_sig,  -- sfix27_En24
              AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,  -- ufix1
              AXI4_Lite_WREADY => AXI4_Lite_WREADY,  -- ufix1
              AXI4_Lite_BRESP => AXI4_Lite_BRESP_tmp,  -- ufix2
              AXI4_Lite_BVALID => AXI4_Lite_BVALID,  -- ufix1
              AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,  -- ufix1
              AXI4_Lite_RDATA => AXI4_Lite_RDATA_tmp,  -- ufix32
              AXI4_Lite_RRESP => AXI4_Lite_RRESP_tmp,  -- ufix2
              AXI4_Lite_RVALID => AXI4_Lite_RVALID,  -- ufix1
              write_axi_enable => write_axi_enable,  -- ufix1
              write_index_select => write_index_select,  -- ufix32
              write_index_AXI => write_index_AXI,  -- ufix32
              reset_internal => reset_internal  -- ufix1
              );

  u_uz_6_ph_voltages_ip_dut_inst : uz_6_ph_voltages_ip_dut
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset => reset,
              dut_enable => write_axi_enable,  -- ufix1
              v_DC_pu => std_logic_vector(v_DC_pu_sig),  -- sfix18_En15
              sin_angle => std_logic_vector(sin_angle_sig),  -- sfix18_En16
              cos_angle => std_logic_vector(cos_angle_sig),  -- sfix18_En16
              index => index,  -- ufix32
              index_select => write_index_select,  -- ufix32
              index_AXI => write_index_AXI,  -- ufix32
              trigger_park_done => trigger_park_done,  -- ufix1
              trigger_prediction_done => trigger_prediction_done,  -- ufix1
              trigger_delay_comp_done => trigger_delay_comp_done,  -- ufix1
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

  ip_timestamp <= unsigned'(X"83BA8D1C");

  reset_cm <=  NOT IPCORE_RESETN;

  v_DC_pu_unsigned <= unsigned(v_DC_pu);

  v_DC_pu_sig <= signed(v_DC_pu_unsigned);

  sin_angle_unsigned <= unsigned(sin_angle);

  sin_angle_sig <= signed(sin_angle_unsigned);

  cos_angle_unsigned <= unsigned(cos_angle);

  cos_angle_sig <= signed(cos_angle_unsigned);

  reset_before_sync <= reset_cm OR reset_internal;

  pu_vd_sig_signed <= signed(pu_vd_sig);

  pu_vd_tmp <= unsigned(pu_vd_sig_signed);

  pu_vd <= std_logic_vector(pu_vd_tmp);

  pu_vq_sig_signed <= signed(pu_vq_sig);

  pu_vq_tmp <= unsigned(pu_vq_sig_signed);

  pu_vq <= std_logic_vector(pu_vq_tmp);

  pu_vx_sig_signed <= signed(pu_vx_sig);

  pu_vx_tmp <= unsigned(pu_vx_sig_signed);

  pu_vx <= std_logic_vector(pu_vx_tmp);

  pu_vy_sig_signed <= signed(pu_vy_sig);

  pu_vy_tmp <= unsigned(pu_vy_sig_signed);

  pu_vy <= std_logic_vector(pu_vy_tmp);

  voltages_done <= voltages_done_sig;

  AXI4_Lite_BRESP <= AXI4_Lite_BRESP_tmp;

  AXI4_Lite_RDATA <= AXI4_Lite_RDATA_tmp;

  AXI4_Lite_RRESP <= AXI4_Lite_RRESP_tmp;

END rtl;
