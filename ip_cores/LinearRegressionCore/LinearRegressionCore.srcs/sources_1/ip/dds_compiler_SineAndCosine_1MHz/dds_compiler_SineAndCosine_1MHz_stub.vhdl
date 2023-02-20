-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1.1_AR75502 (win64) Build 2960000 Wed Aug  5 22:57:20 MDT 2020
-- Date        : Wed Feb  8 12:07:11 2023
-- Host        : HPC running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               e:/01_Repos/06_Ultrazohm_HADEK/ip_cores/LinearRegressionCore/LinearRegressionCore.srcs/sources_1/ip/dds_compiler_SineAndCosine_1MHz/dds_compiler_SineAndCosine_1MHz_stub.vhdl
-- Design      : dds_compiler_SineAndCosine_1MHz
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu9eg-ffvc900-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dds_compiler_SineAndCosine_1MHz is
  Port ( 
    aclk : in STD_LOGIC;
    m_axis_data_tvalid : out STD_LOGIC;
    m_axis_data_tdata : out STD_LOGIC_VECTOR ( 31 downto 0 )
  );

end dds_compiler_SineAndCosine_1MHz;

architecture stub of dds_compiler_SineAndCosine_1MHz is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "aclk,m_axis_data_tvalid,m_axis_data_tdata[31:0]";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "dds_compiler_v6_0_20,Vivado 2020.1.1_AR75502";
begin
end;
