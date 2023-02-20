----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06.02.2023 12:13:35
-- Design Name: 
-- Module Name: LR_Calcer_TB - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

entity LR_Calcer_TB is
Generic(
    DataWidth_TB   : integer := 32;
    Tabs_TB        : integer := 50;
    Fracbits_TB    : integer := 16
);
end LR_Calcer_TB;

architecture Behavioral of LR_Calcer_TB is
--Declaration DUT
component LR_Calcer is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 10;
    Fracbits    : integer := 16
);
Port(
    clk                     : in    std_logic;
    rst_n                   : in    std_logic;
    DataRMW_in              : in    std_logic_vector(DataWidth-1 downto 0);
    DataRMWtimesSample_in   : in    std_logic_vector(DataWidth-1 downto 0);
    Alpha_0_out             : out   std_logic_vector(DataWidth-1 downto 0);
    Alpha_1_out             : out   std_logic_vector(DataWidth-1 downto 0);
    Signal_LR_out           : out   std_logic_vector(DataWidth-1 downto 0)
);
end component LR_Calcer;

-- Constanten und Variablen
constant PERIOD         : time := 10ns;   -- 100 MHz

--Declaration TB-Signals
signal clk_tb                   : std_logic;
signal rst_n_tb                 : std_logic;
signal DataRMW_in_tb            : std_logic_vector(DataWidth_TB-1 downto 0);
signal DataRMWtimesSample_in_tb : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_0_out_tb           : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_1_out_tb           : std_logic_vector(DataWidth_TB-1 downto 0);
signal Signal_LR_out_tb         : std_logic_vector(DataWidth_TB-1 downto 0);

begin

-- Create DUT
DUT : LR_Calcer
Generic map(
    DataWidth   => DataWidth_TB ,
    Tabs        => Tabs_TB      ,
    Fracbits    => Fracbits_TB
)
Port map(
    clk                     => clk_tb                   ,
    rst_n                   => rst_n_tb                 ,
    DataRMW_in              => DataRMW_in_tb            ,
    DataRMWtimesSample_in   => DataRMWtimesSample_in_tb ,
    Alpha_0_out             => Alpha_0_out_tb           ,
    Alpha_1_out             => Alpha_1_out_tb           ,
    Signal_LR_out           => Signal_LR_out_tb
);

-- Create Clock 100MHz
clock:process         
    begin
        clk_tb <= '1';
        wait for PERIOD/2;
        clk_tb <= '0';
        wait for PERIOD/2;   
end process;

-- Create Stimuli

rst_n_tb                    <= '0' after 0ns, '1' after 40ns;

DataRMW_in_tb               <= std_logic_vector(to_signed((1 * (2**Fracbits_TB)),DataWidth_TB)) after 0ns;
DataRMWtimesSample_in_tb    <= std_logic_vector(to_signed((1 * (2**Fracbits_TB)),DataWidth_TB)) after 0ns;

end Behavioral;
