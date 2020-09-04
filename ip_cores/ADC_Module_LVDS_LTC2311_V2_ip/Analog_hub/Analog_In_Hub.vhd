----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Eyke Liegmann
-- 
-- Create Date: 19.08.2020 10:06:10
-- Design Name: 
-- Module Name: Analog_In_Hub - Behavioral
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

entity Analog_In_Hub is
    Port ( A_IN : in STD_LOGIC_VECTOR (15 downto 0);
           ADC_A_P : out STD_LOGIC_VECTOR (3 downto 0);
           ADC_A_N : out STD_LOGIC_VECTOR (3 downto 0);
           ADC_B_P : out STD_LOGIC_VECTOR (3 downto 0);
           ADC_B_N : out STD_LOGIC_VECTOR (3 downto 0));
end Analog_In_Hub;

architecture Behavioral of Analog_In_Hub is

begin

-- ADC Block A
	ADC_A_P(0) <= A_IN(12);
	ADC_A_P(1) <= A_IN(8);
	ADC_A_P(2) <= A_IN(4);
	ADC_A_P(3) <= A_IN(0);

	ADC_A_N(0) <= A_IN(13);
	ADC_A_N(1) <= A_IN(9);
	ADC_A_N(2) <= A_IN(5);
	ADC_A_N(3) <= A_IN(1);

-- ADC Block B <= A_IN();
	ADC_B_P(0) <= A_IN(14);
	ADC_B_P(1) <= A_IN(10);
	ADC_B_P(2) <= A_IN(6);
	ADC_B_P(3) <= A_IN(2);

	ADC_B_N(0) <= A_IN(15);
	ADC_B_N(1) <= A_IN(11);
	ADC_B_N(2) <= A_IN(7);
	ADC_B_N(3) <= A_IN(3);

end Behavioral;
