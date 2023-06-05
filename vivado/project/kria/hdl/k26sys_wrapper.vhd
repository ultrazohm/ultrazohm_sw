--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
--Date        : Fri Apr 21 13:37:23 2023
--Host        : LAPTOP-41KTL5VJ running 64-bit major release  (build 9200)
--Command     : generate_target k26sys_wrapper.bd
--Design      : k26sys_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity k26sys_wrapper is
end k26sys_wrapper;

architecture STRUCTURE of k26sys_wrapper is
  component k26sys is
  end component k26sys;
begin
k26sys_i: component k26sys
 ;
end STRUCTURE;
