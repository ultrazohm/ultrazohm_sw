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
-- Additional Comments: Computes the Running mean Window (RMW) from the input signal
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library ieee_proposed;
use ieee_proposed.fixed_pkg.all;

library syn_functions;
use syn_functions.syn_functions_pkg;

entity RWM_Signal is
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
end RWM_Signal;

architecture Behavioral of RWM_Signal is

constant OneByTabs      : sfixed((DataWidth + syn_functions_pkg.ceil_log2(Tabs))-Fracbits-1 downto -Fracbits) := to_sfixed(real(real(1)/real(Tabs)),(DataWidth + syn_functions_pkg.ceil_log2(Tabs))-Fracbits-1,-Fracbits);

-- Array of Tabs
type t_TabsArray is array(Tabs-1 downto 0) of std_logic_vector(DataWidth-1 downto 0);
signal TabsArray_s      : t_TabsArray;

signal Adder_input_s    : std_logic_vector(0 to (DataWidth*Tabs)-1);
signal Adder_output_s   : std_logic_vector(((DataWidth + syn_functions_pkg.ceil_log2(Tabs)) - 1) downto 0);
signal Adder_output_FP_s: sfixed((DataWidth + syn_functions_pkg.ceil_log2(Tabs))-Fracbits-1 downto -Fracbits);

signal Mult_output_s    : sfixed(((DataWidth + syn_functions_pkg.ceil_log2(Tabs)-Fracbits)*2 - 1) downto -Fracbits*2);
signal Mult_output_p    : sfixed(((DataWidth + syn_functions_pkg.ceil_log2(Tabs)-Fracbits) - 1) downto -Fracbits);

signal DataRMW_out_pipe : std_logic_vector(DataWidth-1 downto 0);
signal DataRMW_out_s    : std_logic_vector(((DataWidth + syn_functions_pkg.ceil_log2(Tabs)) - 1) downto 0);

component ExplicitBinaryTreeAdder_Generic is
    generic(
        -- Core capacity
        NB_TERMS                    : positive  := 50;
        -- Signal widths
        TERM_WIDTH                  : positive  := 8
    );
    port(
        -- Clock domain
        clock_i                     : in  std_logic;
        clock_enable_i              : in  std_logic;
        -- Input interface
        input_term_concatenation_i  : in  std_logic_vector(0 to ((NB_TERMS * TERM_WIDTH) - 1));
        -- Output_interface
        output_sum_o                : out std_logic_vector(((TERM_WIDTH + syn_functions_pkg.ceil_log2(NB_TERMS)) - 1) downto 0)
    );
end component ExplicitBinaryTreeAdder_Generic;

begin

-- Process to generate the Triggered Shift-Regsiter
ShiftRegister:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            for i in 0 to Tabs-1 loop
                TabsArray_s(i)  <= std_logic_vector(to_signed(0,DataWidth));
            end loop;
        else
            if (Trigger_Calc = '1') then
                for i in 1 to Tabs-1 loop
                    TabsArray_s(0)  <= DataRMW_in;
                    TabsArray_s(i)  <= TabsArray_s(i-1);
                end loop;
            end if;
        end if;
    end if;
end process;

-- Map Tabs into the Adder
Tab_Mapping:process(clk)
begin
    for i in 0 to Tabs-1 loop
        -- Adder_input_s    : std_logic_vector(0 to (DataWidth*Tabs)-1);
        Adder_input_s(DataWidth*i to ((i+1)*DataWidth-1))   <= TabsArray_s(i);
    end loop;
end process;

-- Binary-Adder-Tree
AdderTree : ExplicitBinaryTreeAdder_Generic
    generic map(
        -- Core capacity
        NB_TERMS                    => Tabs,
        -- Signal widths
        TERM_WIDTH                  => DataWidth
    )
    port map(
        -- Clock domain
        clock_i                     => clk,
        clock_enable_i              => '1',
        -- Input interface
        input_term_concatenation_i  => Adder_input_s,
        -- Output_interface
        output_sum_o                => Adder_output_s
    );

Adder_output_FP_s <= to_sfixed(Adder_output_s,(DataWidth + syn_functions_pkg.ceil_log2(Tabs))-Fracbits-1,-Fracbits);

-- Multiplikation with 1/Tabs
Mult_OnebyTabs:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            Mult_output_s    <= (others=>'0');
        else
            Mult_output_s    <= Adder_output_FP_s * OneByTabs;
        end if;
    end if;
end process;

Mult_output_p   <= Mult_output_s(((DataWidth + syn_functions_pkg.ceil_log2(Tabs)-Fracbits) - 1) downto -Fracbits);
DataRMW_out_s   <= std_logic_vector(Mult_output_p);
-- Output-Pipeline
Output_Pipeline:process(clk)
begin
    if (rising_edge (clk)) then
        if (rst_n = '0') then
            DataRMW_out_pipe    <= (others=>'0');
        else
            DataRMW_out_pipe    <= DataRMW_out_s(DataWidth-1 downto 0);
       end if;
    end if;
end process;

DataRMW_out <= DataRMW_out_pipe;

end Behavioral;
