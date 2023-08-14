-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:43:25 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub -rename_top zusys_PWM_and_SS_control_V_0_2 -prefix
--               zusys_PWM_and_SS_control_V_0_2_ zusys_PWM_and_SS_control_V_0_0_stub.vhdl
-- Design      : zusys_PWM_and_SS_control_V_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_PWM_and_SS_control_V_0_2 is
  Port ( 
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    m_u1_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u2_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    m_u3_norm : in STD_LOGIC_VECTOR ( 13 downto 0 );
    SS0_IN_External : in STD_LOGIC;
    SS1_IN_External : in STD_LOGIC;
    SS2_IN_External : in STD_LOGIC;
    SS3_IN_External : in STD_LOGIC;
    SS4_IN_External : in STD_LOGIC;
    SS5_IN_External : in STD_LOGIC;
    AXI4_Lite_ACLK : in STD_LOGIC;
    AXI4_Lite_ARESETN : in STD_LOGIC;
    AXI4_Lite_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_AWVALID : in STD_LOGIC;
    AXI4_Lite_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_Lite_WVALID : in STD_LOGIC;
    AXI4_Lite_BREADY : in STD_LOGIC;
    AXI4_Lite_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_Lite_ARVALID : in STD_LOGIC;
    AXI4_Lite_RREADY : in STD_LOGIC;
    SS0_OUT : out STD_LOGIC;
    SS1_OUT : out STD_LOGIC;
    SS2_OUT : out STD_LOGIC;
    SS3_OUT : out STD_LOGIC;
    SS4_OUT : out STD_LOGIC;
    SS5_OUT : out STD_LOGIC;
    PWM_enb_out : out STD_LOGIC;
    Triangular_Max : out STD_LOGIC;
    Triangular_Min : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );

end zusys_PWM_and_SS_control_V_0_2;

architecture stub of zusys_PWM_and_SS_control_V_0_2 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "IPCORE_CLK,IPCORE_RESETN,m_u1_norm[13:0],m_u2_norm[13:0],m_u3_norm[13:0],SS0_IN_External,SS1_IN_External,SS2_IN_External,SS3_IN_External,SS4_IN_External,SS5_IN_External,AXI4_Lite_ACLK,AXI4_Lite_ARESETN,AXI4_Lite_AWADDR[15:0],AXI4_Lite_AWVALID,AXI4_Lite_WDATA[31:0],AXI4_Lite_WSTRB[3:0],AXI4_Lite_WVALID,AXI4_Lite_BREADY,AXI4_Lite_ARADDR[15:0],AXI4_Lite_ARVALID,AXI4_Lite_RREADY,SS0_OUT,SS1_OUT,SS2_OUT,SS3_OUT,SS4_OUT,SS5_OUT,PWM_enb_out,Triangular_Max,Triangular_Min,AXI4_Lite_AWREADY,AXI4_Lite_WREADY,AXI4_Lite_BRESP[1:0],AXI4_Lite_BVALID,AXI4_Lite_ARREADY,AXI4_Lite_RDATA[31:0],AXI4_Lite_RRESP[1:0],AXI4_Lite_RVALID";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "PWM_and_SS_control_V3_ip,Vivado 2020.1.1";
begin
end;
