-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Fri Jan 28 14:47:56 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_axi_testIP_0_0/zusys_uz_axi_testIP_0_0_stub.vhdl
-- Design      : zusys_uz_axi_testIP_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_uz_axi_testIP_0_0 is
  Port ( 
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    AXI4_ACLK : in STD_LOGIC;
    AXI4_ARESETN : in STD_LOGIC;
    AXI4_AWID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_AWADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_AWLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_AWSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_AWLOCK : in STD_LOGIC;
    AXI4_AWCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_AWPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_AWVALID : in STD_LOGIC;
    AXI4_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_WLAST : in STD_LOGIC;
    AXI4_WVALID : in STD_LOGIC;
    AXI4_BREADY : in STD_LOGIC;
    AXI4_ARID : in STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_ARADDR : in STD_LOGIC_VECTOR ( 15 downto 0 );
    AXI4_ARLEN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    AXI4_ARSIZE : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARBURST : in STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_ARLOCK : in STD_LOGIC;
    AXI4_ARCACHE : in STD_LOGIC_VECTOR ( 3 downto 0 );
    AXI4_ARPROT : in STD_LOGIC_VECTOR ( 2 downto 0 );
    AXI4_ARVALID : in STD_LOGIC;
    AXI4_RREADY : in STD_LOGIC;
    AXI4_AWREADY : out STD_LOGIC;
    AXI4_WREADY : out STD_LOGIC;
    AXI4_BID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_BVALID : out STD_LOGIC;
    AXI4_ARREADY : out STD_LOGIC;
    AXI4_RID : out STD_LOGIC_VECTOR ( 11 downto 0 );
    AXI4_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_RLAST : out STD_LOGIC;
    AXI4_RVALID : out STD_LOGIC
  );

end zusys_uz_axi_testIP_0_0;

architecture stub of zusys_uz_axi_testIP_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "IPCORE_CLK,IPCORE_RESETN,AXI4_ACLK,AXI4_ARESETN,AXI4_AWID[11:0],AXI4_AWADDR[15:0],AXI4_AWLEN[7:0],AXI4_AWSIZE[2:0],AXI4_AWBURST[1:0],AXI4_AWLOCK,AXI4_AWCACHE[3:0],AXI4_AWPROT[2:0],AXI4_AWVALID,AXI4_WDATA[31:0],AXI4_WSTRB[3:0],AXI4_WLAST,AXI4_WVALID,AXI4_BREADY,AXI4_ARID[11:0],AXI4_ARADDR[15:0],AXI4_ARLEN[7:0],AXI4_ARSIZE[2:0],AXI4_ARBURST[1:0],AXI4_ARLOCK,AXI4_ARCACHE[3:0],AXI4_ARPROT[2:0],AXI4_ARVALID,AXI4_RREADY,AXI4_AWREADY,AXI4_WREADY,AXI4_BID[11:0],AXI4_BRESP[1:0],AXI4_BVALID,AXI4_ARREADY,AXI4_RID[11:0],AXI4_RDATA[31:0],AXI4_RRESP[1:0],AXI4_RLAST,AXI4_RVALID";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "uz_axi_testIP,Vivado 2020.1.1";
begin
end;
