----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.02.2023 14:14:20
-- Design Name: 
-- Module Name: LinearRegressionIP_TB - Behavioral
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

entity LinearRegressionIP_TB_Simple is
Generic(
    DataWidth_TB   : integer := 32;
    Tabs_TB        : integer := 50;
    Fracbits_TB    : integer := 16
);
end LinearRegressionIP_TB_Simple;

architecture Behavioral of LinearRegressionIP_TB_Simple is
--Declaration DUT
component LinearRegressionIP is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 10;
    Fracbits    : integer := 16
);
Port(
    clk         : in    std_logic;
    rst_n       : in    std_logic;
    Trigger_Calc: in    std_logic;
    Calc_enable : in    std_logic;
    Data_in     : in    std_logic_vector(DataWidth-1 downto 0);
    Alpha_0_out : out   std_logic_vector(DataWidth-1 downto 0);
    Alpha_1_out : out   std_logic_vector(DataWidth-1 downto 0);
    Data_out    : out   std_logic_vector(DataWidth-1 downto 0)
);
end component;

-- Constanten und Variablen
constant PERIOD         : time := 10ns;   -- 100 MHz
constant PERIOD_Trigger : time := 1000ns; -- 1 MHz

--Declaration TB-Signals
signal clk_tb           : std_logic;
signal rst_n_tb         : std_logic;
signal Trigger_Calc_tb  : std_logic;
signal Calc_enable_tb   : std_logic;
signal Data_in_tb       : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_0_out_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_1_out_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_out_tb      : std_logic_vector(DataWidth_TB-1 downto 0);

begin

-- Create DUT
DUT : LinearRegressionIP
Generic map(
    DataWidth   => DataWidth_TB ,
    Tabs        => Tabs_TB      ,
    Fracbits    => Fracbits_TB
)
Port map(
    clk         => clk_tb          ,
    rst_n       => rst_n_tb        ,
    Trigger_Calc=> Trigger_Calc_tb ,
    Calc_enable =>Calc_enable_tb,
    Data_in     => Data_in_tb      ,
    Alpha_0_out => Alpha_0_out_tb  ,
    Alpha_1_out => Alpha_1_out_tb  ,
    Data_out    => Data_out_tb
);

-- Create Clock 100MHz
clock:process         
    begin
        clk_tb <= '1';
        wait for PERIOD/2;
        clk_tb <= '0';
        wait for PERIOD/2;   
end process;

-- Create Trigger
Trigger:process         
    begin
        Trigger_Calc_tb <= '1';
        wait for 10ns;
        Trigger_Calc_tb <= '0';
        wait for PERIOD_Trigger-10ns;   
end process;

-- Create Stimuli
rst_n_tb             <= '0' after 0ns, '1' after 40ns;
Calc_enable_tb  <= '0' after 0ns, '1' after 40ns;
Data_in_tb           <= std_logic_vector(to_signed((1 * (2**Fracbits_TB)),DataWidth_TB)) after 0ns;

end Behavioral;
