-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\UZ_D_GaN_Inverter\UZ_D_GaN_Inverter.vhd
-- Created: 2021-05-07 11:44:56
-- 
-- Generated by MATLAB 9.9 and HDL Coder 3.17
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
-- Module: UZ_D_GaN_Inverter
-- Source Path: UZ_D_GaN_Inverter
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY UZ_D_GaN_Inverter IS
  PORT( IPCORE_CLK                        :   IN    std_logic;  -- ufix1
        IPCORE_RESETN                     :   IN    std_logic;  -- ufix1
        GaN_Temp                          :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
        GaN_FAULT                         :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
        GaN_OC                            :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
        I_DIAG                            :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
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
        PWM_EN                            :   OUT   std_logic;  -- ufix1
        AXI4_Lite_AWREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_WREADY                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_BRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_BVALID                  :   OUT   std_logic;  -- ufix1
        AXI4_Lite_ARREADY                 :   OUT   std_logic;  -- ufix1
        AXI4_Lite_RDATA                   :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
        AXI4_Lite_RRESP                   :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        AXI4_Lite_RVALID                  :   OUT   std_logic  -- ufix1
        );
END UZ_D_GaN_Inverter;


ARCHITECTURE rtl OF UZ_D_GaN_Inverter IS

  -- Component Declarations
  COMPONENT UZ_D_GaN_Inverter_reset_sync
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset_in                        :   IN    std_logic;  -- ufix1
          reset_out                       :   OUT   std_logic
          );
  END COMPONENT;

  COMPONENT UZ_D_GaN_Inverter_axi_lite
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
          read_AXI_Gan_Temp_1_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_1_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_1_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_1_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_Gan_Temp_2_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_2_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_2_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_2_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_Gan_Temp_3_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_3_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_3_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_3_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_Gan_Temp_4_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_4_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_4_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_4_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_Gan_Temp_5_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_5_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_5_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_5_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_Gan_Temp_6_period      :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_6_hightime    :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_6_lowtime     :   IN    std_logic_vector(31 DOWNTO 0);  -- ufix32
          read_AXI_Gan_Temp_6_dutycyc     :   IN    std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          read_AXI_GaN_FAULT              :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
          read_AXI_GaN_OC                 :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
          read_AXI_I_DIAG                 :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI4_Lite_AWREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_WREADY                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_BRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_BVALID                :   OUT   std_logic;  -- ufix1
          AXI4_Lite_ARREADY               :   OUT   std_logic;  -- ufix1
          AXI4_Lite_RDATA                 :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI4_Lite_RRESP                 :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
          AXI4_Lite_RVALID                :   OUT   std_logic;  -- ufix1
          write_axi_enable                :   OUT   std_logic;  -- ufix1
          write_AXI_PWM_Enable            :   OUT   std_logic;  -- ufix1
          reset_internal                  :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  COMPONENT UZ_D_GaN_Inverter_dut
    PORT( clk                             :   IN    std_logic;  -- ufix1
          reset                           :   IN    std_logic;
          dut_enable                      :   IN    std_logic;  -- ufix1
          GaN_Temp                        :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
          GaN_FAULT                       :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
          GaN_OC                          :   IN    std_logic_vector(5 DOWNTO 0);  -- ufix6
          I_DIAG                          :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
          AXI_PWM_Enable                  :   IN    std_logic;  -- ufix1
          ce_out                          :   OUT   std_logic;  -- ufix1
          AXI_Gan_Temp_1_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_1_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_1_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_1_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_Gan_Temp_2_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_2_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_2_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_2_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_Gan_Temp_3_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_3_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_3_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_3_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_Gan_Temp_4_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_4_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_4_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_4_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_Gan_Temp_5_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_5_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_5_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_5_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_Gan_Temp_6_period           :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_6_hightime         :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_6_lowtime          :   OUT   std_logic_vector(31 DOWNTO 0);  -- ufix32
          AXI_Gan_Temp_6_dutycyc          :   OUT   std_logic_vector(31 DOWNTO 0);  -- sfix32_En24
          AXI_GaN_FAULT                   :   OUT   std_logic_vector(5 DOWNTO 0);  -- ufix6
          AXI_GaN_OC                      :   OUT   std_logic_vector(5 DOWNTO 0);  -- ufix6
          AXI_I_DIAG                      :   OUT   std_logic_vector(3 DOWNTO 0);  -- ufix4
          PWM_EN                          :   OUT   std_logic  -- ufix1
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : UZ_D_GaN_Inverter_reset_sync
    USE ENTITY work.UZ_D_GaN_Inverter_reset_sync(rtl);

  FOR ALL : UZ_D_GaN_Inverter_axi_lite
    USE ENTITY work.UZ_D_GaN_Inverter_axi_lite(rtl);

  FOR ALL : UZ_D_GaN_Inverter_dut
    USE ENTITY work.UZ_D_GaN_Inverter_dut(rtl);

  -- Signals
  SIGNAL reset                            : std_logic;
  SIGNAL ip_timestamp                     : unsigned(31 DOWNTO 0);  -- ufix32
  SIGNAL reset_cm                         : std_logic;  -- ufix1
  SIGNAL reset_internal                   : std_logic;  -- ufix1
  SIGNAL reset_before_sync                : std_logic;  -- ufix1
  SIGNAL AXI_Gan_Temp_1_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_1_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_1_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_1_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_2_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_2_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_2_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_2_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_3_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_3_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_3_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_3_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_4_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_4_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_4_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_4_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_5_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_5_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_5_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_5_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_6_period_sig        : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_6_hightime_sig      : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_6_lowtime_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_Gan_Temp_6_dutycyc_sig       : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI_GaN_FAULT_sig                : std_logic_vector(5 DOWNTO 0);  -- ufix6
  SIGNAL AXI_GaN_OC_sig                   : std_logic_vector(5 DOWNTO 0);  -- ufix6
  SIGNAL AXI_I_DIAG_sig                   : std_logic_vector(3 DOWNTO 0);  -- ufix4
  SIGNAL AXI4_Lite_BRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL AXI4_Lite_RDATA_tmp              : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL AXI4_Lite_RRESP_tmp              : std_logic_vector(1 DOWNTO 0);  -- ufix2
  SIGNAL write_axi_enable                 : std_logic;  -- ufix1
  SIGNAL write_AXI_PWM_Enable             : std_logic;  -- ufix1
  SIGNAL ce_out_sig                       : std_logic;  -- ufix1
  SIGNAL PWM_EN_sig                       : std_logic;  -- ufix1

BEGIN
  u_UZ_D_GaN_Inverter_reset_sync_inst : UZ_D_GaN_Inverter_reset_sync
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset_in => reset_before_sync,  -- ufix1
              reset_out => reset
              );

  u_UZ_D_GaN_Inverter_axi_lite_inst : UZ_D_GaN_Inverter_axi_lite
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
              read_AXI_Gan_Temp_1_period => AXI_Gan_Temp_1_period_sig,  -- ufix32
              read_AXI_Gan_Temp_1_hightime => AXI_Gan_Temp_1_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_1_lowtime => AXI_Gan_Temp_1_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_1_dutycyc => AXI_Gan_Temp_1_dutycyc_sig,  -- sfix32_En24
              read_AXI_Gan_Temp_2_period => AXI_Gan_Temp_2_period_sig,  -- ufix32
              read_AXI_Gan_Temp_2_hightime => AXI_Gan_Temp_2_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_2_lowtime => AXI_Gan_Temp_2_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_2_dutycyc => AXI_Gan_Temp_2_dutycyc_sig,  -- sfix32_En24
              read_AXI_Gan_Temp_3_period => AXI_Gan_Temp_3_period_sig,  -- ufix32
              read_AXI_Gan_Temp_3_hightime => AXI_Gan_Temp_3_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_3_lowtime => AXI_Gan_Temp_3_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_3_dutycyc => AXI_Gan_Temp_3_dutycyc_sig,  -- sfix32_En24
              read_AXI_Gan_Temp_4_period => AXI_Gan_Temp_4_period_sig,  -- ufix32
              read_AXI_Gan_Temp_4_hightime => AXI_Gan_Temp_4_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_4_lowtime => AXI_Gan_Temp_4_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_4_dutycyc => AXI_Gan_Temp_4_dutycyc_sig,  -- sfix32_En24
              read_AXI_Gan_Temp_5_period => AXI_Gan_Temp_5_period_sig,  -- ufix32
              read_AXI_Gan_Temp_5_hightime => AXI_Gan_Temp_5_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_5_lowtime => AXI_Gan_Temp_5_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_5_dutycyc => AXI_Gan_Temp_5_dutycyc_sig,  -- sfix32_En24
              read_AXI_Gan_Temp_6_period => AXI_Gan_Temp_6_period_sig,  -- ufix32
              read_AXI_Gan_Temp_6_hightime => AXI_Gan_Temp_6_hightime_sig,  -- ufix32
              read_AXI_Gan_Temp_6_lowtime => AXI_Gan_Temp_6_lowtime_sig,  -- ufix32
              read_AXI_Gan_Temp_6_dutycyc => AXI_Gan_Temp_6_dutycyc_sig,  -- sfix32_En24
              read_AXI_GaN_FAULT => AXI_GaN_FAULT_sig,  -- ufix6
              read_AXI_GaN_OC => AXI_GaN_OC_sig,  -- ufix6
              read_AXI_I_DIAG => AXI_I_DIAG_sig,  -- ufix4
              AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,  -- ufix1
              AXI4_Lite_WREADY => AXI4_Lite_WREADY,  -- ufix1
              AXI4_Lite_BRESP => AXI4_Lite_BRESP_tmp,  -- ufix2
              AXI4_Lite_BVALID => AXI4_Lite_BVALID,  -- ufix1
              AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,  -- ufix1
              AXI4_Lite_RDATA => AXI4_Lite_RDATA_tmp,  -- ufix32
              AXI4_Lite_RRESP => AXI4_Lite_RRESP_tmp,  -- ufix2
              AXI4_Lite_RVALID => AXI4_Lite_RVALID,  -- ufix1
              write_axi_enable => write_axi_enable,  -- ufix1
              write_AXI_PWM_Enable => write_AXI_PWM_Enable,  -- ufix1
              reset_internal => reset_internal  -- ufix1
              );

  u_UZ_D_GaN_Inverter_dut_inst : UZ_D_GaN_Inverter_dut
    PORT MAP( clk => IPCORE_CLK,  -- ufix1
              reset => reset,
              dut_enable => write_axi_enable,  -- ufix1
              GaN_Temp => GaN_Temp,  -- ufix6
              GaN_FAULT => GaN_FAULT,  -- ufix6
              GaN_OC => GaN_OC,  -- ufix6
              I_DIAG => I_DIAG,  -- ufix4
              AXI_PWM_Enable => write_AXI_PWM_Enable,  -- ufix1
              ce_out => ce_out_sig,  -- ufix1
              AXI_Gan_Temp_1_period => AXI_Gan_Temp_1_period_sig,  -- ufix32
              AXI_Gan_Temp_1_hightime => AXI_Gan_Temp_1_hightime_sig,  -- ufix32
              AXI_Gan_Temp_1_lowtime => AXI_Gan_Temp_1_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_1_dutycyc => AXI_Gan_Temp_1_dutycyc_sig,  -- sfix32_En24
              AXI_Gan_Temp_2_period => AXI_Gan_Temp_2_period_sig,  -- ufix32
              AXI_Gan_Temp_2_hightime => AXI_Gan_Temp_2_hightime_sig,  -- ufix32
              AXI_Gan_Temp_2_lowtime => AXI_Gan_Temp_2_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_2_dutycyc => AXI_Gan_Temp_2_dutycyc_sig,  -- sfix32_En24
              AXI_Gan_Temp_3_period => AXI_Gan_Temp_3_period_sig,  -- ufix32
              AXI_Gan_Temp_3_hightime => AXI_Gan_Temp_3_hightime_sig,  -- ufix32
              AXI_Gan_Temp_3_lowtime => AXI_Gan_Temp_3_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_3_dutycyc => AXI_Gan_Temp_3_dutycyc_sig,  -- sfix32_En24
              AXI_Gan_Temp_4_period => AXI_Gan_Temp_4_period_sig,  -- ufix32
              AXI_Gan_Temp_4_hightime => AXI_Gan_Temp_4_hightime_sig,  -- ufix32
              AXI_Gan_Temp_4_lowtime => AXI_Gan_Temp_4_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_4_dutycyc => AXI_Gan_Temp_4_dutycyc_sig,  -- sfix32_En24
              AXI_Gan_Temp_5_period => AXI_Gan_Temp_5_period_sig,  -- ufix32
              AXI_Gan_Temp_5_hightime => AXI_Gan_Temp_5_hightime_sig,  -- ufix32
              AXI_Gan_Temp_5_lowtime => AXI_Gan_Temp_5_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_5_dutycyc => AXI_Gan_Temp_5_dutycyc_sig,  -- sfix32_En24
              AXI_Gan_Temp_6_period => AXI_Gan_Temp_6_period_sig,  -- ufix32
              AXI_Gan_Temp_6_hightime => AXI_Gan_Temp_6_hightime_sig,  -- ufix32
              AXI_Gan_Temp_6_lowtime => AXI_Gan_Temp_6_lowtime_sig,  -- ufix32
              AXI_Gan_Temp_6_dutycyc => AXI_Gan_Temp_6_dutycyc_sig,  -- sfix32_En24
              AXI_GaN_FAULT => AXI_GaN_FAULT_sig,  -- ufix6
              AXI_GaN_OC => AXI_GaN_OC_sig,  -- ufix6
              AXI_I_DIAG => AXI_I_DIAG_sig,  -- ufix4
              PWM_EN => PWM_EN_sig  -- ufix1
              );

  ip_timestamp <= to_unsigned(2105071144, 32);

  reset_cm <=  NOT IPCORE_RESETN;

  reset_before_sync <= reset_cm OR reset_internal;

  PWM_EN <= PWM_EN_sig;

  AXI4_Lite_BRESP <= AXI4_Lite_BRESP_tmp;

  AXI4_Lite_RDATA <= AXI4_Lite_RDATA_tmp;

  AXI4_Lite_RRESP <= AXI4_Lite_RRESP_tmp;

END rtl;
