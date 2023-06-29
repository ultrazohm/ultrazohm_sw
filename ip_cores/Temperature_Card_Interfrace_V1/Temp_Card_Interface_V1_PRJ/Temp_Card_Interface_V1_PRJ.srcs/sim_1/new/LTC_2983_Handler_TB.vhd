----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.06.2023 13:44:34
-- Design Name: 
-- Module Name: LTC_2983_Handler_TB - Behavioral
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

entity LTC_2983_Handler_TB is
--  Port ( );
end LTC_2983_Handler_TB;

architecture Behavioral of LTC_2983_Handler_TB is

--Signals to map the compoents--------------------------------------------------------
signal clock_tb   			: STD_LOGIC;                  --system clock
signal reset_n_tb 			: STD_LOGIC;                  --synchronous reset
signal enable_tb            : STD_LOGIC;                    --System enable
signal go_sig_tb            : STD_LOGIC;					--global Trigger

signal busy_tb 		        : STD_LOGIC;
signal ready_tb 		    : STD_LOGIC;
signal error_flag_tb 		: STD_LOGIC;					--Error occured, need reset

signal SPI_MOSI_tb		    : STD_LOGIC;					-- SPI-Port
signal SPI_MISO_tb			: STD_LOGIC;	
signal SPI_SCLK_tb			: STD_LOGIC;	
signal SPI_SS_tb			: STD_LOGIC;
signal LTC_Interrupt_tb		: STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
signal LTC_resetn_tb		: STD_LOGIC;

signal Temp_00_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_01_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_02_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_03_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_04_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_05_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_06_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_07_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_08_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_09_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_10_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_11_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_12_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_13_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_14_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_15_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_16_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_17_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_18_out_LTC_tb   : std_logic_vector(31 downto 0);				
signal Temp_19_out_LTC_tb   : std_logic_vector(31 downto 0);

signal LTC_Global_config_tb	: std_logic_vector(7 DOWNTO 0);
signal LTC_Mux_config_tb	: std_logic_vector(7 DOWNTO 0);

signal LTC_CH_0_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_1_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_2_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_3_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_4_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_5_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_6_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_7_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_8_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_9_config_tb	: std_logic_vector(31 downto 0);
signal LTC_CH_10_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_11_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_12_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_13_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_14_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_15_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_16_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_17_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_18_config_tb  : std_logic_vector(31 downto 0);
signal LTC_CH_19_config_tb  : std_logic_vector(31 downto 0);

-- Constanten und Variablen
constant PERIOD         : time := 10ns;   -- 100 MHz
constant PERIOD_Trigger : time := 200000ns;

--Components---------------------------------------------------------------------
component LTC2983_Interface is
	Generic(	
		SPI_Datalength			: INTEGER	:=  32;					-- Wortlänge SPI
		SPI_Slavenumber			: INTEGER	:=  1;					-- sollte auf 1 bleiben
		SPI_cpha				: STD_LOGIC	:= '0';					-- Clock-Phase SPI
		SPI_cpol				: STD_LOGIC	:= '0';					-- Clock-Polarität SPI
		SPI_cont				: STD_LOGIC	:= '0';					-- continuierlicher Modus SPI
		SPI_clk_div				: INTEGER	:=  2 ;					-- Taktteiler SPIs
		Channelcount			: INTEGER 	:= 20					-- Kanaele des LTC2983
	);
	Port (
		clock   				: IN    STD_LOGIC;                  --system clock
		reset_n 				: IN    STD_LOGIC;                  --synchronous reset
		enable  				: IN    STD_LOGIC;                 	--System enable
		go_sig					: IN	STD_LOGIC;					--global Trigger
		busy    				: OUT   STD_LOGIC;                  --busy / data ready signal
		ready 					: OUT	STD_LOGIC;					--New Data available
		error_flag				: OUT	STD_LOGIC;					--Error occured, need reset
		--
		SPI_MOSI				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO				: IN	 STD_LOGIC;	
		SPI_SCLK				: OUT	 STD_LOGIC;	
		SPI_SS					: OUT	 STD_LOGIC;
		--
		LTC_Interrupt			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn				: OUT	 STD_LOGIC;
		--
		Temp_00_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_01_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_02_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_03_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_04_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_05_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_06_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_07_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_08_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_09_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_10_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_11_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_12_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_13_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_14_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_15_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_16_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_17_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_18_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		Temp_19_out				: OUT 	STD_LOGIC_VECTOR(31 DOWNTO 0);
		--
		LTC_CH_0_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_1_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_2_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_3_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_4_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_5_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_6_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_7_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_8_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_9_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_10_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_11_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_12_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_13_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_14_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_15_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_16_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_17_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_18_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		LTC_CH_19_config_in		: IN  std_logic_vector(31 DOWNTO 0);
		--
		LTC_Global_config_in	: IN  std_logic_vector(7 DOWNTO 0);
		LTC_Mux_config_in	    : IN  std_logic_vector(7 DOWNTO 0)	
	);
end component LTC2983_Interface;

begin
DUT : LTC2983_Interface	
Port map(
		clock   				=> clock_tb   		,
		reset_n 				=> reset_n_tb 		,
		enable  				=> enable_tb  		,
		go_sig					=> go_sig_tb		,		
		busy    				=> busy_tb    		,
		ready 					=> ready_tb 		,		
		error_flag				=> error_flag_tb   ,

		SPI_MOSI				=> SPI_MOSI_tb,
		SPI_MISO				=> SPI_MISO_tb,
		SPI_SCLK				=> SPI_SCLK_tb,
		SPI_SS					=> SPI_SS_tb,         

		LTC_Interrupt			=> LTC_Interrupt_tb,
		LTC_resetn				=> LTC_resetn_tb	,	

		Temp_00_out				=> Temp_00_out_LTC_tb,
		Temp_01_out				=> Temp_01_out_LTC_tb,
		Temp_02_out				=> Temp_02_out_LTC_tb,
		Temp_03_out				=> Temp_03_out_LTC_tb,
		Temp_04_out				=> Temp_04_out_LTC_tb,
		Temp_05_out				=> Temp_05_out_LTC_tb,
		Temp_06_out				=> Temp_06_out_LTC_tb,
		Temp_07_out				=> Temp_07_out_LTC_tb,
		Temp_08_out				=> Temp_08_out_LTC_tb,
		Temp_09_out				=> Temp_09_out_LTC_tb,
		Temp_10_out				=> Temp_10_out_LTC_tb,
		Temp_11_out				=> Temp_11_out_LTC_tb,
		Temp_12_out				=> Temp_12_out_LTC_tb,
		Temp_13_out				=> Temp_13_out_LTC_tb,
		Temp_14_out				=> Temp_14_out_LTC_tb,
		Temp_15_out				=> Temp_15_out_LTC_tb,
		Temp_16_out				=> Temp_16_out_LTC_tb,
		Temp_17_out				=> Temp_17_out_LTC_tb,
		Temp_18_out				=> Temp_18_out_LTC_tb,
		Temp_19_out				=> Temp_19_out_LTC_tb,

		LTC_CH_0_config_in		=> LTC_CH_0_config_tb	,
		LTC_CH_1_config_in		=> LTC_CH_1_config_tb	,
		LTC_CH_2_config_in		=> LTC_CH_2_config_tb	,
		LTC_CH_3_config_in		=> LTC_CH_3_config_tb	,
		LTC_CH_4_config_in		=> LTC_CH_4_config_tb	,
		LTC_CH_5_config_in		=> LTC_CH_5_config_tb	,
		LTC_CH_6_config_in		=> LTC_CH_6_config_tb	,
		LTC_CH_7_config_in		=> LTC_CH_7_config_tb	,
		LTC_CH_8_config_in		=> LTC_CH_8_config_tb	,
		LTC_CH_9_config_in		=> LTC_CH_9_config_tb	,
		LTC_CH_10_config_in		=> LTC_CH_10_config_tb  ,
		LTC_CH_11_config_in		=> LTC_CH_11_config_tb  ,
		LTC_CH_12_config_in		=> LTC_CH_12_config_tb  ,
		LTC_CH_13_config_in		=> LTC_CH_13_config_tb  ,
		LTC_CH_14_config_in		=> LTC_CH_14_config_tb  ,
		LTC_CH_15_config_in		=> LTC_CH_15_config_tb  ,
		LTC_CH_16_config_in		=> LTC_CH_16_config_tb  ,
		LTC_CH_17_config_in		=> LTC_CH_17_config_tb  ,
		LTC_CH_18_config_in		=> LTC_CH_18_config_tb  ,
		LTC_CH_19_config_in		=> LTC_CH_19_config_tb  ,

		LTC_Global_config_in	=> LTC_Global_config_tb,
		LTC_Mux_config_in	    => LTC_Mux_config_tb	
	);

-- Create Clock 100MHz
clock:process         
    begin
        clock_tb <= '1';
        wait for PERIOD/2;
        clock_tb <= '0';
        wait for PERIOD/2;   
end process;

-- Create Trigger
Trigger:process         
    begin
        go_sig_tb <= '1';
        wait for 10ns;
        go_sig_tb <= '0';
        wait for PERIOD_Trigger-10ns;   
end process;

-- Create LTC_Interrpt
Interrupt:process         
    begin
        LTC_Interrupt_tb <= '0';
        wait for PERIOD_Trigger-10ns;
        LTC_Interrupt_tb <= '1';
        wait for 10ns;   
        LTC_Interrupt_tb <= '0';
        wait for 10ns;
end process;

-- Create Stimuli
reset_n_tb           <= '0' after 0ns, '1' after 40ns;
enable_tb            <= '0' after 0ns, '1' after 40ns;

LTC_CH_0_config_tb	    <= x"12341234";
LTC_CH_1_config_tb	    <= x"12341234";
LTC_CH_2_config_tb	    <= x"12341234";
LTC_CH_3_config_tb	    <= x"12341234";
LTC_CH_4_config_tb	    <= x"12341234";
LTC_CH_5_config_tb	    <= x"12341234";
LTC_CH_6_config_tb	    <= x"12341234";
LTC_CH_7_config_tb	    <= x"12341234";
LTC_CH_8_config_tb	    <= x"12341234";
LTC_CH_9_config_tb	    <= x"12341234";
LTC_CH_10_config_tb     <= x"12341234";
LTC_CH_11_config_tb     <= x"12341234";
LTC_CH_12_config_tb     <= x"12341234";
LTC_CH_13_config_tb     <= x"12341234";
LTC_CH_14_config_tb     <= x"12341234";
LTC_CH_15_config_tb     <= x"12341234";
LTC_CH_16_config_tb     <= x"12341234";
LTC_CH_17_config_tb     <= x"12341234";
LTC_CH_18_config_tb     <= x"12341234";
LTC_CH_19_config_tb     <= x"12341234";       

LTC_Global_config_tb	<= x"12";
LTC_Mux_config_tb	    <= x"34";

SPI_MISO_tb             <= '1';

end Behavioral;
