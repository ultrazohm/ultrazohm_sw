-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Mon Feb 28 14:42:09 2022
-- Host        : enc177112 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/GIT/UltraZohm/software/ultrazohm_sw_develop/vivado/zusys/ip/zusys_uz_pu_con_ip_0_1/zusys_uz_pu_con_ip_0_1_stub.vhdl
-- Design      : zusys_uz_pu_con_ip_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_uz_pu_con_ip_0_1 is
  Port ( 
    IPCORE_CLK : in STD_LOGIC;
    IPCORE_RESETN : in STD_LOGIC;
    in0 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in1 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in2 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in3 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in4 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in5 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in6 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in7 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in8 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in9 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in10 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in11 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in12 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in13 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in14 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in15 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in16 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in17 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in18 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in19 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in20 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in21 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in22 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in23 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in24 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in25 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in26 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in27 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in28 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in29 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in30 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    in31 : in STD_LOGIC_VECTOR ( 26 downto 0 );
    adc_trigger : in STD_LOGIC;
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
    out0 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out1 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out2 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out3 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out4 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out5 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out6 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out7 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out8 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out9 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out10 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out11 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out12 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out13 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out14 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out15 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out16 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out17 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out18 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out19 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out20 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out21 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out22 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out23 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out24 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out25 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out26 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out27 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out28 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out29 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out30 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out31 : out STD_LOGIC_VECTOR ( 17 downto 0 );
    out_valid : out STD_LOGIC;
    AXI4_Lite_AWREADY : out STD_LOGIC;
    AXI4_Lite_WREADY : out STD_LOGIC;
    AXI4_Lite_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_BVALID : out STD_LOGIC;
    AXI4_Lite_ARREADY : out STD_LOGIC;
    AXI4_Lite_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    AXI4_Lite_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    AXI4_Lite_RVALID : out STD_LOGIC
  );

end zusys_uz_pu_con_ip_0_1;

architecture stub of zusys_uz_pu_con_ip_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "IPCORE_CLK,IPCORE_RESETN,in0[26:0],in1[26:0],in2[26:0],in3[26:0],in4[26:0],in5[26:0],in6[26:0],in7[26:0],in8[26:0],in9[26:0],in10[26:0],in11[26:0],in12[26:0],in13[26:0],in14[26:0],in15[26:0],in16[26:0],in17[26:0],in18[26:0],in19[26:0],in20[26:0],in21[26:0],in22[26:0],in23[26:0],in24[26:0],in25[26:0],in26[26:0],in27[26:0],in28[26:0],in29[26:0],in30[26:0],in31[26:0],adc_trigger,AXI4_Lite_ACLK,AXI4_Lite_ARESETN,AXI4_Lite_AWADDR[15:0],AXI4_Lite_AWVALID,AXI4_Lite_WDATA[31:0],AXI4_Lite_WSTRB[3:0],AXI4_Lite_WVALID,AXI4_Lite_BREADY,AXI4_Lite_ARADDR[15:0],AXI4_Lite_ARVALID,AXI4_Lite_RREADY,out0[17:0],out1[17:0],out2[17:0],out3[17:0],out4[17:0],out5[17:0],out6[17:0],out7[17:0],out8[17:0],out9[17:0],out10[17:0],out11[17:0],out12[17:0],out13[17:0],out14[17:0],out15[17:0],out16[17:0],out17[17:0],out18[17:0],out19[17:0],out20[17:0],out21[17:0],out22[17:0],out23[17:0],out24[17:0],out25[17:0],out26[17:0],out27[17:0],out28[17:0],out29[17:0],out30[17:0],out31[17:0],out_valid,AXI4_Lite_AWREADY,AXI4_Lite_WREADY,AXI4_Lite_BRESP[1:0],AXI4_Lite_BVALID,AXI4_Lite_ARREADY,AXI4_Lite_RDATA[31:0],AXI4_Lite_RRESP[1:0],AXI4_Lite_RVALID";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "uz_pu_con_ip,Vivado 2020.1.1";
begin
end;
