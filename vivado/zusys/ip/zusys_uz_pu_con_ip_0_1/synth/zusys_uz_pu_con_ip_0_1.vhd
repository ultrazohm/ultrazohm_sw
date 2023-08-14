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

-- IP VLNV: xilinx.com:ip:uz_pu_con_ip:1.0
-- IP Revision: 2112396747

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY zusys_uz_pu_con_ip_0_1 IS
  PORT (
    IPCORE_CLK : IN STD_LOGIC;
    IPCORE_RESETN : IN STD_LOGIC;
    in0 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in1 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in2 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in3 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in4 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in5 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in6 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in7 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in8 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in9 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in10 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in11 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in12 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in13 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in14 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in15 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in16 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in17 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in18 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in19 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in20 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in21 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in22 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in23 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in24 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in25 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in26 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in27 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in28 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in29 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in30 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    in31 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    adc_trigger : IN STD_LOGIC;
    AXI4_Lite_ACLK : IN STD_LOGIC;
    AXI4_Lite_ARESETN : IN STD_LOGIC;
    AXI4_Lite_AWADDR : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    AXI4_Lite_AWVALID : IN STD_LOGIC;
    AXI4_Lite_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    AXI4_Lite_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    AXI4_Lite_WVALID : IN STD_LOGIC;
    AXI4_Lite_BREADY : IN STD_LOGIC;
    AXI4_Lite_ARADDR : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    AXI4_Lite_ARVALID : IN STD_LOGIC;
    AXI4_Lite_RREADY : IN STD_LOGIC;
    out0 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out1 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out2 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out3 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out4 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out5 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out6 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out7 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out8 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out9 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out10 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out11 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out12 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out13 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out14 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out15 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out16 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out17 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out18 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out19 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out20 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out21 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out22 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out23 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out24 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out25 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out26 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out27 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out28 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out29 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out30 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out31 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
    out_valid : OUT STD_LOGIC;
    AXI4_Lite_AWREADY : OUT STD_LOGIC;
    AXI4_Lite_WREADY : OUT STD_LOGIC;
    AXI4_Lite_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    AXI4_Lite_BVALID : OUT STD_LOGIC;
    AXI4_Lite_ARREADY : OUT STD_LOGIC;
    AXI4_Lite_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    AXI4_Lite_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    AXI4_Lite_RVALID : OUT STD_LOGIC
  );
END zusys_uz_pu_con_ip_0_1;

ARCHITECTURE zusys_uz_pu_con_ip_0_1_arch OF zusys_uz_pu_con_ip_0_1 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF zusys_uz_pu_con_ip_0_1_arch: ARCHITECTURE IS "yes";
  COMPONENT uz_pu_con_ip IS
    PORT (
      IPCORE_CLK : IN STD_LOGIC;
      IPCORE_RESETN : IN STD_LOGIC;
      in0 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in1 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in2 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in3 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in4 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in5 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in6 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in7 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in8 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in9 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in10 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in11 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in12 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in13 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in14 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in15 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in16 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in17 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in18 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in19 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in20 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in21 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in22 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in23 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in24 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in25 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in26 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in27 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in28 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in29 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in30 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      in31 : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
      adc_trigger : IN STD_LOGIC;
      AXI4_Lite_ACLK : IN STD_LOGIC;
      AXI4_Lite_ARESETN : IN STD_LOGIC;
      AXI4_Lite_AWADDR : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
      AXI4_Lite_AWVALID : IN STD_LOGIC;
      AXI4_Lite_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      AXI4_Lite_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      AXI4_Lite_WVALID : IN STD_LOGIC;
      AXI4_Lite_BREADY : IN STD_LOGIC;
      AXI4_Lite_ARADDR : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
      AXI4_Lite_ARVALID : IN STD_LOGIC;
      AXI4_Lite_RREADY : IN STD_LOGIC;
      out0 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out1 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out2 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out3 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out4 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out5 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out6 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out7 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out8 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out9 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out10 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out11 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out12 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out13 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out14 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out15 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out16 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out17 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out18 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out19 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out20 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out21 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out22 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out23 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out24 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out25 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out26 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out27 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out28 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out29 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out30 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out31 : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
      out_valid : OUT STD_LOGIC;
      AXI4_Lite_AWREADY : OUT STD_LOGIC;
      AXI4_Lite_WREADY : OUT STD_LOGIC;
      AXI4_Lite_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      AXI4_Lite_BVALID : OUT STD_LOGIC;
      AXI4_Lite_ARREADY : OUT STD_LOGIC;
      AXI4_Lite_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      AXI4_Lite_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      AXI4_Lite_RVALID : OUT STD_LOGIC
    );
  END COMPONENT uz_pu_con_ip;
  ATTRIBUTE X_CORE_INFO : STRING;
  ATTRIBUTE X_CORE_INFO OF zusys_uz_pu_con_ip_0_1_arch: ARCHITECTURE IS "uz_pu_con_ip,Vivado 2020.1.1";
  ATTRIBUTE CHECK_LICENSE_TYPE : STRING;
  ATTRIBUTE CHECK_LICENSE_TYPE OF zusys_uz_pu_con_ip_0_1_arch : ARCHITECTURE IS "zusys_uz_pu_con_ip_0_1,uz_pu_con_ip,{}";
  ATTRIBUTE CORE_GENERATION_INFO : STRING;
  ATTRIBUTE CORE_GENERATION_INFO OF zusys_uz_pu_con_ip_0_1_arch: ARCHITECTURE IS "zusys_uz_pu_con_ip_0_1,uz_pu_con_ip,{x_ipProduct=Vivado 2020.1.1,x_ipVendor=xilinx.com,x_ipLibrary=ip,x_ipName=uz_pu_con_ip,x_ipVersion=1.0,x_ipCoreRevision=2112396747,x_ipLanguage=VHDL,x_ipSimLanguage=VHDL}";
  ATTRIBUTE IP_DEFINITION_SOURCE : STRING;
  ATTRIBUTE IP_DEFINITION_SOURCE OF zusys_uz_pu_con_ip_0_1_arch: ARCHITECTURE IS "package_project";
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_RVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_RRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_RDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_ARREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_BVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_BRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_WREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_AWREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_RREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_ARVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite ARVALID";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_ARADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_BREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_WVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_WSTRB: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_WDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_AWVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite AWVALID";
  ATTRIBUTE X_INTERFACE_PARAMETER OF AXI4_Lite_AWADDR: SIGNAL IS "XIL_INTERFACENAME AXI4_Lite, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 16, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1," & 
" NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_AWADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 AXI4_Lite AWADDR";
  ATTRIBUTE X_INTERFACE_PARAMETER OF AXI4_Lite_ARESETN: SIGNAL IS "XIL_INTERFACENAME AXI4_Lite_signal_reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_ARESETN: SIGNAL IS "xilinx.com:signal:reset:1.0 AXI4_Lite_signal_reset RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF AXI4_Lite_ACLK: SIGNAL IS "XIL_INTERFACENAME AXI4_Lite_signal_clock, ASSOCIATED_BUSIF AXI4_Lite, ASSOCIATED_RESET AXI4_Lite_ARESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF AXI4_Lite_ACLK: SIGNAL IS "xilinx.com:signal:clock:1.0 AXI4_Lite_signal_clock CLK";
  ATTRIBUTE X_INTERFACE_PARAMETER OF IPCORE_RESETN: SIGNAL IS "XIL_INTERFACENAME IPCORE_RESETN, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF IPCORE_RESETN: SIGNAL IS "xilinx.com:signal:reset:1.0 IPCORE_RESETN RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF IPCORE_CLK: SIGNAL IS "XIL_INTERFACENAME IPCORE_CLK, ASSOCIATED_RESET IPCORE_RESETN, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF IPCORE_CLK: SIGNAL IS "xilinx.com:signal:clock:1.0 IPCORE_CLK CLK";
BEGIN
  U0 : uz_pu_con_ip
    PORT MAP (
      IPCORE_CLK => IPCORE_CLK,
      IPCORE_RESETN => IPCORE_RESETN,
      in0 => in0,
      in1 => in1,
      in2 => in2,
      in3 => in3,
      in4 => in4,
      in5 => in5,
      in6 => in6,
      in7 => in7,
      in8 => in8,
      in9 => in9,
      in10 => in10,
      in11 => in11,
      in12 => in12,
      in13 => in13,
      in14 => in14,
      in15 => in15,
      in16 => in16,
      in17 => in17,
      in18 => in18,
      in19 => in19,
      in20 => in20,
      in21 => in21,
      in22 => in22,
      in23 => in23,
      in24 => in24,
      in25 => in25,
      in26 => in26,
      in27 => in27,
      in28 => in28,
      in29 => in29,
      in30 => in30,
      in31 => in31,
      adc_trigger => adc_trigger,
      AXI4_Lite_ACLK => AXI4_Lite_ACLK,
      AXI4_Lite_ARESETN => AXI4_Lite_ARESETN,
      AXI4_Lite_AWADDR => AXI4_Lite_AWADDR,
      AXI4_Lite_AWVALID => AXI4_Lite_AWVALID,
      AXI4_Lite_WDATA => AXI4_Lite_WDATA,
      AXI4_Lite_WSTRB => AXI4_Lite_WSTRB,
      AXI4_Lite_WVALID => AXI4_Lite_WVALID,
      AXI4_Lite_BREADY => AXI4_Lite_BREADY,
      AXI4_Lite_ARADDR => AXI4_Lite_ARADDR,
      AXI4_Lite_ARVALID => AXI4_Lite_ARVALID,
      AXI4_Lite_RREADY => AXI4_Lite_RREADY,
      out0 => out0,
      out1 => out1,
      out2 => out2,
      out3 => out3,
      out4 => out4,
      out5 => out5,
      out6 => out6,
      out7 => out7,
      out8 => out8,
      out9 => out9,
      out10 => out10,
      out11 => out11,
      out12 => out12,
      out13 => out13,
      out14 => out14,
      out15 => out15,
      out16 => out16,
      out17 => out17,
      out18 => out18,
      out19 => out19,
      out20 => out20,
      out21 => out21,
      out22 => out22,
      out23 => out23,
      out24 => out24,
      out25 => out25,
      out26 => out26,
      out27 => out27,
      out28 => out28,
      out29 => out29,
      out30 => out30,
      out31 => out31,
      out_valid => out_valid,
      AXI4_Lite_AWREADY => AXI4_Lite_AWREADY,
      AXI4_Lite_WREADY => AXI4_Lite_WREADY,
      AXI4_Lite_BRESP => AXI4_Lite_BRESP,
      AXI4_Lite_BVALID => AXI4_Lite_BVALID,
      AXI4_Lite_ARREADY => AXI4_Lite_ARREADY,
      AXI4_Lite_RDATA => AXI4_Lite_RDATA,
      AXI4_Lite_RRESP => AXI4_Lite_RRESP,
      AXI4_Lite_RVALID => AXI4_Lite_RVALID
    );
END zusys_uz_pu_con_ip_0_1_arch;
