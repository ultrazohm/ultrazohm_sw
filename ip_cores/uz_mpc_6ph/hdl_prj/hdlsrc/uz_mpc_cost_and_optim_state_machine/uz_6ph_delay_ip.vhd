-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\uz_mpc_cost_and_optim_state_machine\uz_6ph_delay_ip.vhd
-- Created: 2022-10-04 11:18:49
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
-- Module: uz_6ph_delay_ip
-- Source Path: uz_6ph_delay_ip
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY uz_6ph_delay_ip IS
  PORT( IPCORE_CLK                        :   IN    std_logic;  -- ufix1
        IPCORE_RESETN                     :   IN    std_logic;  -- ufix1
        id_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        iq_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        ix_pu                             :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18
        iy_pu                             :   IN    std_logic_vector(17 DOWNTO 0);  -- ufix18
        vd_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        vq_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        vx_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        vy_pu                             :   IN    std_logic_vector(26 DOWNTO 0);  -- ufix27
        trigger_voltages_done             :   IN    std_logic;  -- ufix1
        trigger_park_done                 :   IN    std_logic;  -- ufix1
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
        id_delay_pu                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        iq_delay_pu                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        ix_delay_pu                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        iy_delay_pu                       :   OUT   std_logic_vector(26 DOWNTO 0);  -- ufix27
        delay_comp_done                   :   OUT   std_logic;  -- ufix1
        AXI4_Lite_AWREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_WREADY                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_BRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_BVALID                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_ARREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_RDATA                   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_Lite_RRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_RVALID                  :   OUT   std_logic  -- ufix1
        );
END uz_6ph_delay_ip;


ARCHITECTURE rtl OF uz_6ph_delay_ip IS

  -- Component Declarations
  COMPONENT uz_6ph_delay_ip_reset_sync
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset_in                        :   IN    std_logic;  -- ufix1
          reset_out                       :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT uz_6ph_delay_ip_axi_lite
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
          read_id_delay_pu_AXI            :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_iq_delay_pu_AXI            :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_ix_delay_pu_AXI            :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          read_iy_delay_pu_AXI            :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          AXI4_Lite_AWREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_WREADY                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_BRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_BVALID                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_ARREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_RDATA                 :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_Lite_RRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_RVALID                :   OUT   std_logic;  -- ufix1
          write_axi_enable                :   OUT   std_logic;  -- ufix1
          write_omega_m_pu                :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Rs_over_ZB_AXI            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Ts_times_ZB_over_Ld_AXI   :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Ts_times_ZB_over_Lq_AXI   :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Ts_times_ZB_over_Lx_AXI   :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Ts_times_ZB_over_Ly_AXI   :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Ld_over_LB_AXI            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_Lq_over_LB_AXI            :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_psi_pm_over_psiB_AXI      :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          write_polepairs_AXI             :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          reset_internal                  :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  COMPONENT uz_6ph_delay_ip_dut
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset                           :   IN    std_logic;
          dut_enable                      :   IN    std_logic;  -- ufix1
          id_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          iq_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En16
          ix_pu                           :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          iy_pu                           :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
          vd_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          vq_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          vx_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          vy_pu                           :   IN    std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          omega_m_pu                      :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Rs_over_ZB_AXI                  :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Ts_times_ZB_over_Ld_AXI         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Ts_times_ZB_over_Lq_AXI         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Ts_times_ZB_over_Lx_AXI         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Ts_times_ZB_over_Ly_AXI         :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Ld_over_LB_AXI                  :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          Lq_over_LB_AXI                  :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          psi_pm_over_psiB_AXI            :   IN    std_logic_vector(17 DOWNTO 0);  -- sfix18_En15
          polepairs_AXI                   :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          trigger_voltages_done           :   IN    std_logic;  -- ufix1
          trigger_park_done               :   IN    std_logic;  -- ufix1
          ce_out                          :   OUT   std_logic;  -- ufix1
          id_delay_pu                     :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          iq_delay_pu                     :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          ix_delay_pu                     :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          iy_delay_pu                     :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          id_delay_pu_AXI                 :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          iq_delay_pu_AXI                 :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          ix_delay_pu_AXI                 :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          iy_delay_pu_AXI                 :   OUT   std_logic_vector(26 DOWNTO 0);  -- sfix27_En24
          delay_comp_done                 :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : uz_6ph_delay_ip_reset_sync
    USE ENTITY work.uz_6ph_delay_ip_reset_sync(rtl);

  FOR ALL : uz_6ph_delay_ip_axi_lite
    USE ENTITY work.uz_6ph_delay_ip_axi_lite(rtl);

  FOR ALL : uz_6ph_delay_ip_dut
    USE ENTITY work.uz_6ph_delay_ip_dut(rtl);

  -- Signals
  SIGNAL reset                            : std_logic;
  SIGNAL ip_timestamp                     : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL reset_cm                         : std_logic;  -- ufix1
  SIGNAL id_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL id_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL iq_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL iq_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En16
  SIGNAL ix_pu_unsigned                   : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL ix_pu_sig                        : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL iy_pu_unsigned                   : unsigned(17 DOWNTO 0);  -- ufix18
  SIGNAL iy_pu_sig                        : signed(17 DOWNTO 0);  -- sfix18_En11
  SIGNAL vd_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL vd_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL vq_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL vq_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL vx_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL vx_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL vy_pu_unsigned                   : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL vy_pu_sig                        : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL reset_internal                   : std_logic;  -- ufix1
  SIGNAL reset_before_sync                : std_logic;  -- ufix1
  SIGNAL id_delay_pu_AXI_sig              : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL iq_delay_pu_AXI_sig              : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL ix_delay_pu_AXI_sig              : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL iy_delay_pu_AXI_sig              : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL AXI4_Lite_BRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL AXI4_Lite_RDATA_tmp              : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI4_Lite_RRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL write_axi_enable                 : std_logic;  -- ufix1
  SIGNAL write_omega_m_pu                 : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Rs_over_ZB_AXI             : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Ts_times_ZB_over_Ld_AXI    : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Ts_times_ZB_over_Lq_AXI    : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Ts_times_ZB_over_Lx_AXI    : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Ts_times_ZB_over_Ly_AXI    : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Ld_over_LB_AXI             : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_Lq_over_LB_AXI             : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_psi_pm_over_psiB_AXI       : std_logic_vector(17 DOWNTO 0);  -- ufix18
  SIGNAL write_polepairs_AXI              : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL id_delay_pu_sig                  : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL iq_delay_pu_sig                  : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL ix_delay_pu_sig                  : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL iy_delay_pu_sig                  : std_logic_vector(26 DOWNTO 0);  -- ufix27
  SIGNAL delay_comp_done_sig              : std_logic;  -- ufix1
  SIGNAL id_delay_pu_sig_signed           : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL id_delay_pu_tmp                  : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL iq_delay_pu_sig_signed           : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL iq_delay_pu_tmp                  : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL ix_delay_pu_sig_signed           : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL ix_delay_pu_tmp                  : unsigned(26 DOWNTO 0);  -- ufix27
  SIGNAL iy_delay_pu_sig_signed           : signed(26 DOWNTO 0);  -- sfix27_En24
  SIGNAL iy_delay_pu_tmp                  : unsigned(26 DOWNTO 0);  -- ufix27

BEGIN
  u_uz_6ph_delay_ip_reset_sync_inst : uz_6ph_delay_ip_reset_sync
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset_in => reset_before_sync,  -- ufix1
              reset_out => reset
              );

  u_uz_6ph_delay_ip_axi_lite_inst : uz_6ph_delay_ip_axi_lite
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
              read_id_delay_pu_AXI => id_delay_pu_AXI_sig,  -- sfix27_En24
              read_iq_delay_pu_AXI => iq_delay_pu_AXI_sig,  -- sfix27_En24
              read_ix_delay_pu_AXI => ix_delay_pu_AXI_sig,  -- sfix27_En24
              read_iy_delay_pu_AXI => iy_delay_pu_AXI_sig,  -- sfix27_En24
              AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,  -- ufix1
              AXI4_Lite_WREADY => AXI4_Lite_WREADY,  -- ufix1
              AXI4_Lite_BRESP => AXI4_Lite_BRESP_tmp,  -- ufix2
              AXI4_Lite_BVALID => AXI4_Lite_BVALID,  -- ufix1
              AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,  -- ufix1
              AXI4_Lite_RDATA => AXI4_Lite_RDATA_tmp,  -- ufix32
              AXI4_Lite_RRESP => AXI4_Lite_RRESP_tmp,  -- ufix2
              AXI4_Lite_RVALID => AXI4_Lite_RVALID,  -- ufix1
              write_axi_enable => write_axi_enable,  -- ufix1
              write_omega_m_pu => write_omega_m_pu,  -- sfix18_En15
              write_Rs_over_ZB_AXI => write_Rs_over_ZB_AXI,  -- sfix18_En15
              write_Ts_times_ZB_over_Ld_AXI => write_Ts_times_ZB_over_Ld_AXI,  -- sfix18_En15
              write_Ts_times_ZB_over_Lq_AXI => write_Ts_times_ZB_over_Lq_AXI,  -- sfix18_En15
              write_Ts_times_ZB_over_Lx_AXI => write_Ts_times_ZB_over_Lx_AXI,  -- sfix18_En15
              write_Ts_times_ZB_over_Ly_AXI => write_Ts_times_ZB_over_Ly_AXI,  -- sfix18_En15
              write_Ld_over_LB_AXI => write_Ld_over_LB_AXI,  -- sfix18_En15
              write_Lq_over_LB_AXI => write_Lq_over_LB_AXI,  -- sfix18_En15
              write_psi_pm_over_psiB_AXI => write_psi_pm_over_psiB_AXI,  -- sfix18_En15
              write_polepairs_AXI => write_polepairs_AXI,  -- ufix32
              reset_internal => reset_internal  -- ufix1
              );

  u_uz_6ph_delay_ip_dut_inst : uz_6ph_delay_ip_dut
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset => reset,
              dut_enable => write_axi_enable,  -- ufix1
              id_pu => std_logic_vector(id_pu_sig),  -- sfix27_En16
              iq_pu => std_logic_vector(iq_pu_sig),  -- sfix27_En16
              ix_pu => std_logic_vector(ix_pu_sig),  -- sfix18_En11
              iy_pu => std_logic_vector(iy_pu_sig),  -- sfix18_En11
              vd_pu => std_logic_vector(vd_pu_sig),  -- sfix27_En24
              vq_pu => std_logic_vector(vq_pu_sig),  -- sfix27_En24
              vx_pu => std_logic_vector(vx_pu_sig),  -- sfix27_En24
              vy_pu => std_logic_vector(vy_pu_sig),  -- sfix27_En24
              omega_m_pu => write_omega_m_pu,  -- sfix18_En15
              Rs_over_ZB_AXI => write_Rs_over_ZB_AXI,  -- sfix18_En15
              Ts_times_ZB_over_Ld_AXI => write_Ts_times_ZB_over_Ld_AXI,  -- sfix18_En15
              Ts_times_ZB_over_Lq_AXI => write_Ts_times_ZB_over_Lq_AXI,  -- sfix18_En15
              Ts_times_ZB_over_Lx_AXI => write_Ts_times_ZB_over_Lx_AXI,  -- sfix18_En15
              Ts_times_ZB_over_Ly_AXI => write_Ts_times_ZB_over_Ly_AXI,  -- sfix18_En15
              Ld_over_LB_AXI => write_Ld_over_LB_AXI,  -- sfix18_En15
              Lq_over_LB_AXI => write_Lq_over_LB_AXI,  -- sfix18_En15
              psi_pm_over_psiB_AXI => write_psi_pm_over_psiB_AXI,  -- sfix18_En15
              polepairs_AXI => write_polepairs_AXI,  -- ufix32
              trigger_voltages_done => trigger_voltages_done,  -- ufix1
              trigger_park_done => trigger_park_done,  -- ufix1
              ce_out => ce_out_sig,  -- ufix1
              id_delay_pu => id_delay_pu_sig,  -- sfix27_En24
              iq_delay_pu => iq_delay_pu_sig,  -- sfix27_En24
              ix_delay_pu => ix_delay_pu_sig,  -- sfix27_En24
              iy_delay_pu => iy_delay_pu_sig,  -- sfix27_En24
              id_delay_pu_AXI => id_delay_pu_AXI_sig,  -- sfix27_En24
              iq_delay_pu_AXI => iq_delay_pu_AXI_sig,  -- sfix27_En24
              ix_delay_pu_AXI => ix_delay_pu_AXI_sig,  -- sfix27_En24
              iy_delay_pu_AXI => iy_delay_pu_AXI_sig,  -- sfix27_En24
              delay_comp_done => delay_comp_done_sig  -- ufix1
              );

  ip_timestamp <= unsigned'(X"83BA8D1E");

  reset_cm <=  NOT IPCORE_RESETN;

  id_pu_unsigned <= unsigned(id_pu);

  id_pu_sig <= signed(id_pu_unsigned);

  iq_pu_unsigned <= unsigned(iq_pu);

  iq_pu_sig <= signed(iq_pu_unsigned);

  ix_pu_unsigned <= unsigned(ix_pu);

  ix_pu_sig <= signed(ix_pu_unsigned);

  iy_pu_unsigned <= unsigned(iy_pu);

  iy_pu_sig <= signed(iy_pu_unsigned);

  vd_pu_unsigned <= unsigned(vd_pu);

  vd_pu_sig <= signed(vd_pu_unsigned);

  vq_pu_unsigned <= unsigned(vq_pu);

  vq_pu_sig <= signed(vq_pu_unsigned);

  vx_pu_unsigned <= unsigned(vx_pu);

  vx_pu_sig <= signed(vx_pu_unsigned);

  vy_pu_unsigned <= unsigned(vy_pu);

  vy_pu_sig <= signed(vy_pu_unsigned);

  reset_before_sync <= reset_cm OR reset_internal;

  id_delay_pu_sig_signed <= signed(id_delay_pu_sig);

  id_delay_pu_tmp <= unsigned(id_delay_pu_sig_signed);

  id_delay_pu <= std_logic_vector(id_delay_pu_tmp);

  iq_delay_pu_sig_signed <= signed(iq_delay_pu_sig);

  iq_delay_pu_tmp <= unsigned(iq_delay_pu_sig_signed);

  iq_delay_pu <= std_logic_vector(iq_delay_pu_tmp);

  ix_delay_pu_sig_signed <= signed(ix_delay_pu_sig);

  ix_delay_pu_tmp <= unsigned(ix_delay_pu_sig_signed);

  ix_delay_pu <= std_logic_vector(ix_delay_pu_tmp);

  iy_delay_pu_sig_signed <= signed(iy_delay_pu_sig);

  iy_delay_pu_tmp <= unsigned(iy_delay_pu_sig_signed);

  iy_delay_pu <= std_logic_vector(iy_delay_pu_tmp);

  delay_comp_done <= delay_comp_done_sig;

  AXI4_Lite_BRESP <= AXI4_Lite_BRESP_tmp;

  AXI4_Lite_RDATA <= AXI4_Lite_RDATA_tmp;

  AXI4_Lite_RRESP <= AXI4_Lite_RRESP_tmp;

END rtl;
