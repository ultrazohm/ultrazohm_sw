----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/07/2020 01:42:38 PM
-- Design Name: 
-- Module Name: SHIFT_REGISTER - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SHIFT_REGISTER is
    generic ( DEPTH : INTEGER := 16);
    port ( POUT : out STD_LOGIC_VECTOR (DEPTH-1 downto 0);
           SER_IN : in STD_LOGIC;
           SER_OUT: out std_logic;
           CLK : in STD_LOGIC;
           RESET_N : in STD_LOGIC;
           CLKEN : in STD_LOGIC);
end SHIFT_REGISTER;

architecture RTL of SHIFT_REGISTER is
    signal s_shreg: std_logic_vector(DEPTH - 1 downto 0);
begin

    shifter: process (clk) is
        constant zero : std_logic_vector(DEPTH - 1 downto 0) := (others => '0');
    begin
    if rising_edge(CLK) then
        if RESET_N = '0' then s_shreg <= zero;
        elsif CLKEN = '1' THEN
            s_shreg <= s_shreg(DEPTH - 2 downto 0) & SER_IN;
        end if;
    end if;
    end process shifter;
    
    POUT <= s_shreg;
end RTL;
