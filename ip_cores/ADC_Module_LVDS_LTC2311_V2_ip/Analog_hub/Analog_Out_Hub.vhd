----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Eyke Liegmann
-- 
-- Create Date: 19.08.2020 10:31:04
-- Design Name: 
-- Module Name: Analog_Out_Hub - Behavioral
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

entity Analog_Out_Hub is
    Port ( CLK_A_P : in STD_LOGIC;
           CLK_A_N : in STD_LOGIC;
           CLK_B_P : in STD_LOGIC;
           CLK_B_N : in STD_LOGIC;
           A_OUT : out STD_LOGIC_VECTOR (3 downto 0)
		   );
end Analog_Out_Hub;

architecture Behavioral of Analog_Out_Hub is

begin
	A_OUT(0) <= CLK_A_P;
	A_OUT(1) <= CLK_A_N;
	A_OUT(2) <= CLK_B_P;
	A_OUT(3) <= CLK_B_N;
	
end Behavioral;
