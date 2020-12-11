----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/30/2020 11:26:33 AM
-- Design Name: 
-- Module Name: ADC_TOP - STRUCTURE
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
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADC_TOP is
--  Port ( );
    generic (
        HAS_MOSI : boolean := true;
        BITS : integer := 16
    );
    
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        A           : in std_logic_vector(7 downto 0);
        B           : in std_logic_vector(7 downto 0);
        S           : out std_logic_vector(7 downto 0)
    );
    
end ADC_TOP;

architecture STRUCTURE of ADC_TOP is

begin

    p1: process (CLK)
    begin
        if (CLK = '1' and CLK'event) then 
            S <= (A + B);
        end if;
    end process p1;

end STRUCTURE;
