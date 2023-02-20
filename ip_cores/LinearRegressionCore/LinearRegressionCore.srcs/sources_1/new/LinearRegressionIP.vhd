----------------------------------------------------------------------------------
-- Company:     Univeristät Kassel - Elektrische Maschinen und Antriebe
-- Engineer:    Robert Zipprich
-- 
-- Create Date: 02.02.2023 11:12:33
-- Design Name: LinearRegressionIP
-- Module Name: LinearRegressionIP - Behavioral
-- Project Name: Diss
-- Target Devices: UZ
-- Tool Versions: 2020.1
-- Description: AWESOME
-- 
-- Dependencies: Nope
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments: 
--      Core computes the linear Regression of the given Signal with a fixed Number of Tabs
--      it will solve the equation  y = alpha_1 * x + alpha_0, where y is the calculated linear Regression, x ist the number of the last Tab and alpha_1/alpha_0 are factors, which 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity LinearRegressionIP is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 50;
    Fracbits    : integer := 16
);
Port(
    clk             : in    std_logic;
    rst_n           : in    std_logic;
    Trigger_Calc    : in    std_logic;
    Calc_enable     : in    std_logic;
    Data_in         : in    std_logic_vector(DataWidth-1 downto 0);
    Alpha_0_out     : out   std_logic_vector(DataWidth-1 downto 0);
    Alpha_1_out     : out   std_logic_vector(DataWidth-1 downto 0);
    Data_out        : out   std_logic_vector(DataWidth-1 downto 0)
);
end LinearRegressionIP;

architecture Behavioral of LinearRegressionIP is

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

signal Out_RMW_Signal_s             : std_logic_vector(DataWidth-1 downto 0);
signal Out_RMW_SignaltimesSamples_s : std_logic_vector(DataWidth-1 downto 0);
signal OutPutMuxValue_1             : std_logic_vector(DataWidth-1 downto 0);
signal OutPutMuxValue_2             : std_logic_vector(DataWidth-1 downto 0);

begin

-- Create RMW_Signal
RWM_Signal_C : RWM_Signal
Generic map(
    DataWidth   => DataWidth ,
    Tabs        => Tabs      ,
    Fracbits    => Fracbits
)
Port map(
    clk                     => clk                   ,
    rst_n                   => rst_n                 ,
    Trigger_Calc            => Trigger_Calc          ,
    DataRMW_in              => Data_in               ,
    DataRMW_out             => Out_RMW_Signal_s           
);

-- Create RMW_SignalTimesSamples
RWM_SignalTimesSamples_C : RWM_SignalTimesSamples
Generic map(
    DataWidth   => DataWidth ,
    Tabs        => Tabs      ,
    Fracbits    => Fracbits
)
Port map(
    clk                     => clk                   ,
    rst_n                   => rst_n                 ,
    Trigger_Calc            => Trigger_Calc          ,
    DataRMW_in              => Data_in               ,
    DataRMW_out             => Out_RMW_SignaltimesSamples_s           
);

-- Create LR-Calcer
LR_Calcer_C : LR_Calcer
Generic map(
    DataWidth   => DataWidth ,
    Tabs        => Tabs      ,
    Fracbits    => Fracbits
)
Port map(
    clk                     => clk                   ,
    rst_n                   => rst_n                 ,
    DataRMW_in              => Out_RMW_Signal_s            ,
    DataRMWtimesSample_in   => Out_RMW_SignaltimesSamples_s ,
    Alpha_0_out             => Alpha_0_out           ,
    Alpha_1_out             => Alpha_1_out           ,
    Signal_LR_out           => OutPutMuxValue_1
);

OutPutMuxValue_2    <= Data_in;

OutMux:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            Data_out <= (others=>'0');
        else
            if (Calc_enable = '0') then
                -- Output the Data_in, no LR is calculated
                 Data_out <= OutPutMuxValue_2;
            else
                -- Output the calculated LR
                 Data_out <= OutPutMuxValue_1;
            end if;
        end if;
    end if;
end process;

end Behavioral;
