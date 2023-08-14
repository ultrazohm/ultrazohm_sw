-- (c) Copyright 1995-2022 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:module_ref:top_npc_state_machine:1.0
-- IP Revision: 1

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY zusys_top_npc_state_machine_0_0 IS
  PORT (
    clock : IN STD_LOGIC;
    enable : IN STD_LOGIC;
    switching_signals : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
    deadtime : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
    A_S1 : OUT STD_LOGIC;
    A_S2 : OUT STD_LOGIC;
    A_S3 : OUT STD_LOGIC;
    A_S4 : OUT STD_LOGIC;
    B_S1 : OUT STD_LOGIC;
    B_S2 : OUT STD_LOGIC;
    B_S3 : OUT STD_LOGIC;
    B_S4 : OUT STD_LOGIC;
    C_S1 : OUT STD_LOGIC;
    C_S2 : OUT STD_LOGIC;
    C_S3 : OUT STD_LOGIC;
    C_S4 : OUT STD_LOGIC;
    A_phase_off : OUT STD_LOGIC;
    B_phase_off : OUT STD_LOGIC;
    C_phase_off : OUT STD_LOGIC
  );
END zusys_top_npc_state_machine_0_0;

ARCHITECTURE zusys_top_npc_state_machine_0_0_arch OF zusys_top_npc_state_machine_0_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF zusys_top_npc_state_machine_0_0_arch: ARCHITECTURE IS "yes";
  COMPONENT top_npc_state_machine IS
    PORT (
      clock : IN STD_LOGIC;
      enable : IN STD_LOGIC;
      switching_signals : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
      deadtime : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
      A_S1 : OUT STD_LOGIC;
      A_S2 : OUT STD_LOGIC;
      A_S3 : OUT STD_LOGIC;
      A_S4 : OUT STD_LOGIC;
      B_S1 : OUT STD_LOGIC;
      B_S2 : OUT STD_LOGIC;
      B_S3 : OUT STD_LOGIC;
      B_S4 : OUT STD_LOGIC;
      C_S1 : OUT STD_LOGIC;
      C_S2 : OUT STD_LOGIC;
      C_S3 : OUT STD_LOGIC;
      C_S4 : OUT STD_LOGIC;
      A_phase_off : OUT STD_LOGIC;
      B_phase_off : OUT STD_LOGIC;
      C_phase_off : OUT STD_LOGIC
    );
  END COMPONENT top_npc_state_machine;
  ATTRIBUTE X_CORE_INFO : STRING;
  ATTRIBUTE X_CORE_INFO OF zusys_top_npc_state_machine_0_0_arch: ARCHITECTURE IS "top_npc_state_machine,Vivado 2020.1.1";
  ATTRIBUTE CHECK_LICENSE_TYPE : STRING;
  ATTRIBUTE CHECK_LICENSE_TYPE OF zusys_top_npc_state_machine_0_0_arch : ARCHITECTURE IS "zusys_top_npc_state_machine_0_0,top_npc_state_machine,{}";
  ATTRIBUTE CORE_GENERATION_INFO : STRING;
  ATTRIBUTE CORE_GENERATION_INFO OF zusys_top_npc_state_machine_0_0_arch: ARCHITECTURE IS "zusys_top_npc_state_machine_0_0,top_npc_state_machine,{x_ipProduct=Vivado 2020.1.1,x_ipVendor=xilinx.com,x_ipLibrary=module_ref,x_ipName=top_npc_state_machine,x_ipVersion=1.0,x_ipCoreRevision=1,x_ipLanguage=VHDL,x_ipSimLanguage=VHDL}";
  ATTRIBUTE IP_DEFINITION_SOURCE : STRING;
  ATTRIBUTE IP_DEFINITION_SOURCE OF zusys_top_npc_state_machine_0_0_arch: ARCHITECTURE IS "module_ref";
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER OF clock: SIGNAL IS "XIL_INTERFACENAME clock, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF clock: SIGNAL IS "xilinx.com:signal:clock:1.0 clock CLK";
BEGIN
  U0 : top_npc_state_machine
    PORT MAP (
      clock => clock,
      enable => enable,
      switching_signals => switching_signals,
      deadtime => deadtime,
      A_S1 => A_S1,
      A_S2 => A_S2,
      A_S3 => A_S3,
      A_S4 => A_S4,
      B_S1 => B_S1,
      B_S2 => B_S2,
      B_S3 => B_S3,
      B_S4 => B_S4,
      C_S1 => C_S1,
      C_S2 => C_S2,
      C_S3 => C_S3,
      C_S4 => C_S4,
      A_phase_off => A_phase_off,
      B_phase_off => B_phase_off,
      C_phase_off => C_phase_off
    );
END zusys_top_npc_state_machine_0_0_arch;
