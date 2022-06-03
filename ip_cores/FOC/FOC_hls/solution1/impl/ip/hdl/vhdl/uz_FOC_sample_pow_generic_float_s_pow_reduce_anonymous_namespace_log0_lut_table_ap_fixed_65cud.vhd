-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud_rom is 
    generic(
             DWIDTH     : integer := 56; 
             AWIDTH     : integer := 6; 
             MEM_SIZE    : integer := 64
    ); 
    port (
          addr0      : in std_logic_vector(AWIDTH-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DWIDTH-1 downto 0);
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud_rom is 

signal addr0_tmp : std_logic_vector(AWIDTH-1 downto 0); 
type mem_array is array (0 to MEM_SIZE-1) of std_logic_vector (DWIDTH-1 downto 0); 
signal mem : mem_array := (
    0 to 2=> "11111111011111000001111011111101010110010011111011101000", 
    3 to 4=> "00000111100111001100110111000010010011001110000100001001", 
    5 to 6=> "00010000000000011011011110110010111101110111100011101101", 
    7 to 9=> "00011000101011110111110101011010101100101000100001101111", 
    10 to 11=> "00100001101010110011110000000001101010010000011111011111", 
    12 to 14=> "00101010111110101001111111010100000000011011101001001011", 
    15 to 17=> "00110100101000111111100101110110011011101111001010101110", 
    18 to 21=> "00111110101011100101011111010110110000001010010111011010", 
    22 to 25=> "01001001001000011010011101000010001011001010110100110001", 
    26 to 29=> "01010100000001101101011100011010001110111100111001000110", 
    30 to 31=> "01011111011010000000011111101100101110011001001101010111", 
    32 to 33=> "10110011110110001001010000010001110101001100101000100101", 
    34 to 35=> "10111001110111101010110001001110101010101010011010110000", 
    36 to 38=> "11000000000010011110111000100010100111001100001010010011", 
    39 to 41=> "11000110010111000010111101101110001001000000101010100100", 
    42 to 43=> "11001100110101110110100111000011011100001001000101111111", 
    44 to 46=> "11010011011111011011111000011100000010100001011101000000", 
    47 to 49=> "11011010010100010111100100001101000110010101010010100001", 
    50 to 53=> "11100001010101010001011110001111001011100100110000000010", 
    54 to 56=> "11101000100010110100110001110010011100111101001110011100", 
    57 to 60=> "11101111111101110000011010011101010100001000110110010101", 
    61 to 63=> "11110111100110110111100000111001101110110011001000101000" );


begin 


memory_access_guard_0: process (addr0) 
begin
      addr0_tmp <= addr0;
--synthesis translate_off
      if (CONV_INTEGER(addr0) > mem_size-1) then
           addr0_tmp <= (others => '0');
      else 
           addr0_tmp <= addr0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
        if (ce0 = '1') then 
            q0 <= mem(CONV_INTEGER(addr0_tmp)); 
        end if;
    end if;
end process;

end rtl;

Library IEEE;
use IEEE.std_logic_1164.all;

entity uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud is
    generic (
        DataWidth : INTEGER := 56;
        AddressRange : INTEGER := 64;
        AddressWidth : INTEGER := 6);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud is
    component uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud_rom is
        port (
            clk : IN STD_LOGIC;
            addr0 : IN STD_LOGIC_VECTOR;
            ce0 : IN STD_LOGIC;
            q0 : OUT STD_LOGIC_VECTOR);
    end component;



begin
    uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud_rom_U :  component uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud_rom
    port map (
        clk => clk,
        addr0 => address0,
        ce0 => ce0,
        q0 => q0);

end architecture;


