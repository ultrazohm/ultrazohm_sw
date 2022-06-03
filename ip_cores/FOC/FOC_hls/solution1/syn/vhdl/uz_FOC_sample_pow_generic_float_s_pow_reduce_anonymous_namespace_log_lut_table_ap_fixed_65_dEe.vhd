-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe_rom is 
    generic(
             DWIDTH     : integer := 52; 
             AWIDTH     : integer := 4; 
             MEM_SIZE    : integer := 16
    ); 
    port (
          addr0      : in std_logic_vector(AWIDTH-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DWIDTH-1 downto 0);
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe_rom is 

signal addr0_tmp : std_logic_vector(AWIDTH-1 downto 0); 
type mem_array is array (0 to MEM_SIZE-1) of std_logic_vector (DWIDTH-1 downto 0); 
signal mem : mem_array := (
    0 => "0000000000000000000000000000000000000000000000000000", 
    1 => "0001000000000000000000010101010101010101100010001000", 
    2 => "0010000000010000000100101011111011000011001011111000", 
    3 => "0011000000110000010101001001110100111011001010100001", 
    4 => "0100000001100000111001111011001111111001100000100100", 
    5 => "0101000010100001111011010010101000010011011111001101", 
    6 => "0110000011110011100001101000110000001110111100111001", 
    7 => "0111000101010101110101011100110110000001110101010011", 
    8 => "0111100110001101010011000101101010111101011011111111", 
    9 => "1000101000001000111011001111100110100100111001100101", 
    10 => "1001101010010101100110100010011011010011100001100010", 
    11 => "1010101100110011011101110100101111011001111000111000", 
    12 => "1011101111100010101010000100000100010000100111101111", 
    13 => "1100110010100011010100010100111101101000010111100101", 
    14 => "1101110101110101100101110011001001000011010011000001", 
    15 => "1110111001011001100111110001100101011000010110101001" );

attribute syn_rom_style : string;
attribute syn_rom_style of mem : signal is "select_rom";
attribute ROM_STYLE : string;
attribute ROM_STYLE of mem : signal is "distributed";

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

entity uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe is
    generic (
        DataWidth : INTEGER := 52;
        AddressRange : INTEGER := 16;
        AddressWidth : INTEGER := 4);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe is
    component uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe_rom is
        port (
            clk : IN STD_LOGIC;
            addr0 : IN STD_LOGIC_VECTOR;
            ce0 : IN STD_LOGIC;
            q0 : OUT STD_LOGIC_VECTOR);
    end component;



begin
    uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe_rom_U :  component uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe_rom
    port map (
        clk => clk,
        addr0 => address0,
        ce0 => ce0,
        q0 => q0);

end architecture;


