----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.02.2023 11:28:39
-- Design Name: 
-- Module Name: LinearRegressionIP_TB_Sines - Behavioral
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
use ieee.math_real.all;

entity LinearRegressionIP_TB_Sines is
Generic(
    DataWidth_TB   : integer := 32;
    Tabs_TB        : integer := 50;
    Fracbits_TB    : integer := 16
);
end LinearRegressionIP_TB_Sines;

architecture Behavioral of LinearRegressionIP_TB_Sines is

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

-- Declaration SineSource
component dds_compiler_SineAndCosine_1MHz is
  Port (
    aclk                : in    std_logic;
    m_axis_data_tvalid  : out   std_logic;
    m_axis_data_tdata   : out   std_logic_vector(31 downto 0)
  );
end component dds_compiler_SineAndCosine_1MHz;

-- Constanten und Variablen
constant PERIOD         : time := 10ns;  -- 100 MHz
constant PERIOD_Trigger : time := 100ns; -- 1 MHz

--Declaration TB-Signals
signal clk_tb           : std_logic;
signal rst_n_tb         : std_logic;
signal Trigger_Calc_tb  : std_logic;
signal Calc_enable_tb   : std_logic;

signal DDS_out_s_tb       : std_logic_vector(31 downto 0);
signal Sine_s_tb          : signed(15 downto 0);
signal Cosine_s_tb        : signed(15 downto 0);
signal Sine_s_resized_tb  : signed(31 downto 0);
signal Cosine_resized_s_tb: signed(31 downto 0);

signal Data_in_1_tb       : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_in_1_s_tb     : signed(DataWidth_TB-1 downto 0);
signal Alpha_0_out_1_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_1_out_1_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_out_1_tb      : std_logic_vector(DataWidth_TB-1 downto 0);

signal Data_in_2_tb       : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_in_2_s_tb     : signed(DataWidth_TB-1 downto 0);
signal Alpha_0_out_2_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_1_out_2_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_out_2_tb      : std_logic_vector(DataWidth_TB-1 downto 0);

signal Data_in_3_tb       : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_in_3_s_tb     : signed(DataWidth_TB-1 downto 0);
signal Alpha_0_out_3_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Alpha_1_out_3_tb   : std_logic_vector(DataWidth_TB-1 downto 0);
signal Data_out_3_tb      : std_logic_vector(DataWidth_TB-1 downto 0);

signal rand_sig           : real := 0.0;
signal Noise_s_tb         : signed(31 downto 0);

begin

-- Create DUT with Sine-Input
DUT1_Sine : LinearRegressionIP
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
    Data_in     => Data_in_1_tb      ,
    Alpha_0_out => Alpha_0_out_1_tb  ,
    Alpha_1_out => Alpha_1_out_1_tb  ,
    Data_out    => Data_out_1_tb
);

-- Create DUT with Sine+Cosine-Input
DUT2_SinePlusCosine : LinearRegressionIP
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
    Data_in     => Data_in_2_tb      ,
    Alpha_0_out => Alpha_0_out_2_tb  ,
    Alpha_1_out => Alpha_1_out_2_tb  ,
    Data_out    => Data_out_2_tb
);

-- Create DUT with Sine-Input with Noise
DUT3_SineWithNoise : LinearRegressionIP
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
    Data_in     => Data_in_3_tb      ,
    Alpha_0_out => Alpha_0_out_3_tb  ,
    Alpha_1_out => Alpha_1_out_3_tb  ,
    Data_out    => Data_out_3_tb
);

-- Create SineSource
SineSource: dds_compiler_SineAndCosine_1MHz
  Port map (
    aclk                 => clk_tb          ,
    m_axis_data_tvalid   => open            ,
    m_axis_data_tdata    => DDS_out_s_tb
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

-- Create Noise
Noise:process
    variable seed1, seed2: positive;              
    variable rand: real;  
begin
    uniform(seed1, seed2, rand);   -- generate a random number
    rand_sig <= ((rand- real(0.5)) * real((2**13)));
    wait for 10 ns;
end process;

Noise_s_tb      <= to_signed(integer(rand_sig),Noise_s_tb'length);

-- Create Stimuli
rst_n_tb        <= '0' after 0ns, '1' after 40ns;
Calc_enable_tb  <= '0' after 0ns, '1' after 40ns;

Sine_s_tb       <= signed(DDS_out_s_tb(31 downto 16));
Cosine_s_tb     <= signed(DDS_out_s_tb(15 downto 0));

Sine_s_resized_tb   <= resize(Sine_s_tb   ,Sine_s_resized_tb ' length);
Cosine_resized_s_tb <= resize(Cosine_s_tb ,Cosine_resized_s_tb ' length);

Data_in_1_s_tb  <= Sine_s_resized_tb sll 6;         -- Sines with Amplitude of 0.5, so we need some gain
Data_in_2_s_tb  <= Cosine_resized_s_tb sll 6;
Data_in_3_s_tb  <= (Sine_s_resized_tb sll 6)+(Noise_s_tb sll 7);

Data_in_1_tb    <= std_logic_vector(Data_in_1_s_tb);
Data_in_2_tb    <= std_logic_vector(Data_in_2_s_tb);
Data_in_3_tb    <= std_logic_vector(Data_in_3_s_tb);

end Behavioral;
