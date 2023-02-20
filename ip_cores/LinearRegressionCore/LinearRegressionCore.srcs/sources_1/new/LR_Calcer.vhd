----------------------------------------------------------------------------------
-- Company:     Univeristät Kassel - Elektrische Maschinen und Antriebe
-- Engineer:    Robert Zipprich
-- 
-- Create Date: 02.02.2023 11:12:33
-- Design Name: LinearRegressionIP
-- Module Name: LR_Calcer
-- Project Name: Diss
-- Target Devices: UZ
-- Tool Versions: 2020.1
-- Description: AWESOME
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments: Computes the Values and alpha_0 with the Linear regression wth those parameters
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library ieee_proposed;
use ieee_proposed.fixed_pkg.all;

entity LR_Calcer is
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
end LR_Calcer;

architecture Behavioral of LR_Calcer is

-- Constants Tabs
constant Tabs_c             : sfixed(DataWidth-Fracbits-1 downto -Fracbits) := to_sfixed(Tabs,DataWidth-Fracbits-1,-Fracbits);
-- wird (Tabs/2+0,5)
constant SamplesMean        : sfixed(DataWidth-Fracbits-1 downto -Fracbits) := to_sfixed((real(Tabs/2)+0.5),DataWidth-Fracbits-1,-Fracbits);
-- wird 1/(SamplesSquaredMean-(SamplesMean^2))
constant FaktorCalcAlpha1   : sfixed(DataWidth-Fracbits-1 downto -Fracbits) := to_sfixed(real(real(1)/(((real(Tabs*(Tabs+1)*(2*Tabs+1))/real(6))/(real(Tabs)))-((real(Tabs/2)+0.5)**2))),DataWidth-Fracbits-1,-Fracbits);

-- Pipeline Stages and Signals
signal Alpha_0_p1           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal Alpha_0_s1_long      : sfixed(DataWidth-Fracbits downto -Fracbits);
signal Alpha_1_p1           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal Alpha_1_s1_long      : sfixed((DataWidth-Fracbits)*2-1 downto -Fracbits*2);
signal Alpha_1_p2           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal Alpha_1_s2           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal Alpha_1_p3           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal Alpha_1_s3           : sfixed(DataWidth-Fracbits-1 downto -Fracbits);

signal RMW_p1               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_s1               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_p2               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_s2               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_p3               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_s3               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_p4               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMW_s4               : sfixed(DataWidth-Fracbits-1 downto -Fracbits);

signal TabesTimesAlpha1_p1  : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal TabesTimesAlpha1_s1_long  : sfixed((DataWidth-Fracbits)*2-1 downto -Fracbits*2);

signal SampleMeantimesCalcedRMWStS_p1       : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal SampleMeantimesCalcedRMWStS_s1_long  : sfixed((DataWidth-Fracbits)*2-1 downto -Fracbits*2);

signal RMWStSminusRMStimesSamples_p1        : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMWStSminusRMStimesSamples_s1_long   : sfixed(DataWidth-Fracbits downto -Fracbits);

signal RMWtimesSamplemean_p1            : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMWtimesSamplemean_s1_long       : sfixed((DataWidth-Fracbits)*2-1 downto -Fracbits*2);

signal RMWStS_p1                        : sfixed(DataWidth-Fracbits-1 downto -Fracbits);
signal RMWStS_s1                        : sfixed(DataWidth-Fracbits-1 downto -Fracbits);

signal Signal_LR_out_s_long             : sfixed(DataWidth-Fracbits downto -Fracbits); 
signal Alpha_0_out_s                    : sfixed(DataWidth-Fracbits-1 downto -Fracbits); 
signal Alpha_1_out_s                    : sfixed(DataWidth-Fracbits-1 downto -Fracbits); 

begin

-- Calculate DataRMW_in times SamplesMean , Pipeline DataRMW_in and DataRMWtimesSample_in
Pipeline1:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            RMW_s1                  <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            RMWStS_s1               <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            RMWtimesSamplemean_s1_long   <= to_sfixed(0,(DataWidth-Fracbits)*2-1,-Fracbits*2);
        else
            RMW_s1                  <= to_sfixed(DataRMW_in,DataWidth-Fracbits-1,-Fracbits);
            RMWStS_s1               <= to_sfixed(DataRMWtimesSample_in,DataWidth-Fracbits-1,-Fracbits);
            RMWtimesSamplemean_s1_long   <= to_sfixed(DataRMW_in,DataWidth-Fracbits-1,-Fracbits) * SamplesMean;
        end if;
    end if;
end process;

RMW_p1                  <= RMW_s1;
RMWStS_p1               <= RMWStS_s1;
RMWtimesSamplemean_p1   <= RMWtimesSamplemean_s1_long((DataWidth-Fracbits)-1 downto -Fracbits);

-- Calculate DataRMWtimesSample_in - (DataRMW_in * SamplesMean), Pipeline DataRMW_in
Pipeline2:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            RMW_s2                              <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            RMWStSminusRMStimesSamples_s1_long  <= to_sfixed(0,DataWidth-Fracbits,-Fracbits);
        else
            RMW_s2                              <= RMW_p1;
            RMWStSminusRMStimesSamples_s1_long  <= RMWStS_p1 - RMWtimesSamplemean_p1;
        end if;
    end if;
end process;

RMW_p2                          <= RMW_s2;
RMWStSminusRMStimesSamples_p1   <= RMWStSminusRMStimesSamples_s1_long((DataWidth-Fracbits)-1 downto -Fracbits);

-- Calculates (DataRMWtimesSample_in - (DataRMW_in * SamplesMean)) * FaktorCalcAlpha1 = Alpha_1, Pipeline DataRMW_in
Pipeline3:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            RMW_s3          <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            Alpha_1_s1_long <= to_sfixed(0,(DataWidth-Fracbits)*2-1,-Fracbits*2);
        else
            RMW_s3          <= RMW_p2;
            Alpha_1_s1_long <= FaktorCalcAlpha1 * RMWStSminusRMStimesSamples_p1;
        end if;
    end if;
end process;

RMW_p3          <= RMW_s3;
Alpha_1_p1      <= Alpha_1_s1_long((DataWidth-Fracbits)-1 downto -Fracbits);

-- Calculates Alpha_1 * SamplesMean, Pipeline Alpha_1 and DataRMW_in
Pipeline4:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            RMW_s4                              <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            Alpha_1_s2                          <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            SampleMeantimesCalcedRMWStS_s1_long <= to_sfixed(0,(DataWidth-Fracbits)*2-1,-Fracbits*2);
        else
            RMW_s4                              <= RMW_p3;
            Alpha_1_s2                          <= Alpha_1_p1;
            SampleMeantimesCalcedRMWStS_s1_long <= SamplesMean * Alpha_1_p1;
        end if;
    end if;
end process;

RMW_p4                          <= RMW_s4;
Alpha_1_p2                      <= Alpha_1_s2;
SampleMeantimesCalcedRMWStS_p1  <= SampleMeantimesCalcedRMWStS_s1_long((DataWidth-Fracbits)-1 downto -Fracbits);

-- calculates DataRMW_in - (Alpha_1 * SamplesMean) =  Alpha_0 and Alpha_1 * Tabs_c, Pipeline Alpha_1
Pipeline5:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            Alpha_0_s1_long             <= to_sfixed(0,DataWidth-Fracbits,-Fracbits);
            Alpha_1_s3                  <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            TabesTimesAlpha1_s1_long    <= to_sfixed(0,(DataWidth-Fracbits)*2-1,-Fracbits*2);
        else
            Alpha_0_s1_long             <= RMW_p4 - SampleMeantimescalcedRMWStS_p1;
            Alpha_1_s3                  <= Alpha_1_p2;
            TabesTimesAlpha1_s1_long    <= Tabs_c * Alpha_1_p2;
        end if;
    end if;
end process;

Alpha_0_p1          <= Alpha_0_s1_long(DataWidth-Fracbits-1 downto -Fracbits);
Alpha_1_p3          <= Alpha_1_s3;
TabesTimesAlpha1_p1 <= TabesTimesAlpha1_s1_long((DataWidth-Fracbits)-1 downto -Fracbits);

-- Add Alpha_0 with Alpha_1 times Tabes, Pipeline Alpha 0 and Alpha 1
Pipeline6:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            Signal_LR_out_s_long<= to_sfixed(0,DataWidth-Fracbits,-Fracbits);
            Alpha_0_out_s       <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
            Alpha_1_out_s       <= to_sfixed(0,DataWidth-Fracbits-1,-Fracbits);
        else
            Signal_LR_out_s_long<= Alpha_0_p1 + TabesTimesAlpha1_p1;
            Alpha_0_out_s       <= Alpha_0_p1;
            Alpha_1_out_s       <= Alpha_1_p3;
        end if;
    end if;
end process;

Signal_LR_out   <= std_logic_vector(Signal_LR_out_s_long(DataWidth-Fracbits-1 downto -Fracbits));
Alpha_0_out     <= std_logic_vector(Alpha_0_out_s);
Alpha_1_out     <= std_logic_vector(Alpha_1_out_s);

end Behavioral;
