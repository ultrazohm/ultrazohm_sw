----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.02.2023 09:17:55
-- Design Name: 
-- Module Name: RMW_TB - Behavioral
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

entity RMW_TB is
Generic(
    DataWidth_TB   : integer := 32;
    Tabs_TB        : integer := 50;
    Fracbits_TB    : integer := 16
);
end RMW_TB;

architecture Behavioral of RMW_TB is

-- DUT1 
component RWM_SignalTimesSamples is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 10;
    Fracbits    : integer := 16
);
Port(
    clk                     : in    std_logic;
    rst_n                   : in    std_logic;
    Trigger_Calc            : in    std_logic;
    DataRMW_in              : in    std_logic_vector(DataWidth-1 downto 0);
    DataRMW_out             : out   std_logic_vector(DataWidth-1 downto 0)
);
end component RWM_SignalTimesSamples;

-- DUT2
component RWM_Signal is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 10;
    Fracbits    : integer := 16
);
Port(
    clk                     : in    std_logic;
    rst_n                   : in    std_logic;
    Trigger_Calc            : in    std_logic;
    DataRMW_in              : in    std_logic_vector(DataWidth-1 downto 0);
    DataRMW_out             : out   std_logic_vector(DataWidth-1 downto 0)
);
end component RWM_Signal;

-- Constanten und Variablen
constant PERIOD         : time := 10ns;   -- 100 MHz
constant PERIOD_Trigger : time := 100ns; -- 1 MHz

--Declaration TB-Signals
signal clk_tb                   : std_logic;
signal rst_n_tb                 : std_logic;
signal Trigger_Calc_tb          : std_logic;
signal DataRMW_in_RMW_tb        : std_logic_vector(DataWidth_TB-1 downto 0);
signal DataRMW_in_RMW_StS_tb    : std_logic_vector(DataWidth_TB-1 downto 0);
signal DataRMW_out_RMW_tb       : std_logic_vector(DataWidth_TB-1 downto 0);
signal DataRMW_out_RMW_StS_tb   : std_logic_vector(DataWidth_TB-1 downto 0);

begin

-- Create DUT1
RWM_Signal_DUT : RWM_Signal
Generic map(
    DataWidth   => DataWidth_TB ,
    Tabs        => Tabs_TB      ,
    Fracbits    => Fracbits_TB
)
Port map(
    clk                     => clk_tb                   ,
    rst_n                   => rst_n_tb                 ,
    Trigger_Calc            => Trigger_Calc_tb          ,
    DataRMW_in              => DataRMW_in_RMW_tb        ,
    DataRMW_out             => DataRMW_out_RMW_tb           
);

-- Create DUT 2
RWM_SignalTimesSamples_DUT : RWM_SignalTimesSamples
Generic map(
    DataWidth   => DataWidth_TB ,
    Tabs        => Tabs_TB      ,
    Fracbits    => Fracbits_TB
)
Port map(
    clk                     => clk_tb                   ,
    rst_n                   => rst_n_tb                 ,
    Trigger_Calc            => Trigger_Calc_tb          ,
    DataRMW_in              => DataRMW_in_RMW_StS_tb    ,
    DataRMW_out             => DataRMW_out_RMW_StS_tb           
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

rst_n_tb                    <= '0' after 0ns, '1' after 40ns;

DataRMW_in_RMW_tb           <= std_logic_vector(to_signed((1 * (2**Fracbits_TB)),DataWidth_TB)) after 0ns;
DataRMW_in_RMW_StS_tb       <= DataRMW_in_RMW_tb;

end Behavioral;
