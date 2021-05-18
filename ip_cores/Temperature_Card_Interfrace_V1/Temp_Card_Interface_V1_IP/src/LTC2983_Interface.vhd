----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/24/2020 08:27:52 AM
-- Design Name: 
-- Module Name: LTC2983_Interface - Behavioral
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

entity LTC2983_Interface is
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
		LTC_CH_19_config_in		: IN  std_logic_vector(31 DOWNTO 0)
	);
end LTC2983_Interface;

architecture Behavioral of LTC2983_Interface is

-- Konstanten anlegen-------------------------------------------------------------------------------
constant SPI_readCMD				: std_logic_vector	:= x"03";
constant SPI_writeCMD				: std_logic_vector	:= x"02";

constant LTC_Channeladdr_start    	: std_logic_vector := x"0200";
constant LTC_resultsaddr_start		: std_logic_vector := x"0010";

-- Signale anlegen----------------------------------------------------------------------------------
type states_LTC2983_Interface is (LTC_powerup, LTC_Resetcounter, LTC_Wakeup, LTC_SendCFG, LTC_start, LTC_ConvStart, LTC_WaitConversion, LTC_InitialReadData, LTC_ReadData, LTC_Output, LTC_SPI_Waittransmit1, LTC_SPI_Waittransmit2, LTC_SPI_WaitCShigh, LTC_Failstate);
signal state_LTC_Interface : states_LTC2983_Interface;
signal laststate_LTC_Interface : states_LTC2983_Interface;

signal SPI_enable			: std_logic;
signal SPI_busy				: std_logic;
signal SPI_TX_Data			: std_logic_vector(SPI_Datalength-1 downto 0);			-- Buffer
signal SPI_RX_Data			: std_logic_vector(SPI_Datalength-1 downto 0);			-- Buffer
signal byte_tx_counter		: unsigned(7 downto 0);
signal byte_rx_counter		: unsigned(7 downto 0);

signal wakeup_counter		: unsigned(31 downto 0);

type LTC_Channelconfigdata_type is array (Channelcount-1 downto 0) of std_logic_vector(31 downto 0);
signal LTC_Channelconfigs	: LTC_Channelconfigdata_type;

type LTC_Channelresultdata_type is array (Channelcount-1 downto 0) of std_logic_vector(31 downto 0);
signal LTC_Channelresults	: LTC_Channelresultdata_type;

-- Komponenten anlegen------------------------------------------------------------------------------
component spi_master_LTC is
  	generic(
		slaves  : INTEGER := 1;  --number of spi slaves
		d_width : INTEGER := 8   --data bus width
	);
  	port(
		clock   : IN     STD_LOGIC;                             --system clock
		reset_n : IN     STD_LOGIC;                             --synchronous reset
		enable  : IN     STD_LOGIC;                             --initiate transaction
		cpol    : IN     STD_LOGIC;                             --spi clock polarity
		cpha    : IN     STD_LOGIC;                             --spi clock phase
		cont    : IN     STD_LOGIC;                             --continuous mode command
		clk_div : IN     INTEGER;                               --system clock cycles per 1/2 period of sclk
		addr    : IN     INTEGER;                               --address of slave
		tx_data : IN     STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);  --data to transmit
		miso    : IN     STD_LOGIC;                             --master in, slave out
		sclk    : OUT    STD_LOGIC;                             --spi clock
		ss_n    : BUFFER STD_LOGIC_VECTOR(slaves-1 DOWNTO 0);   --slave select
		mosi    : OUT    STD_LOGIC;                             --master out, slave in
		busy    : OUT    STD_LOGIC;                             --busy / data ready signal
		rx_data : OUT    STD_LOGIC_VECTOR(d_width-1 DOWNTO 0)   --data1 received
	); 
end component spi_master_LTC;


begin
-- Komponenten instanziieren------------------------------------------------------------------------
SPI_Core : spi_master_LTC
	generic map(
		slaves 	=> SPI_Slavenumber,
		d_width	=> SPI_Datalength
	)
  	port map(
		clock   => clock,				--system clock
		reset_n => reset_n,				--synchronous reset
		enable  => SPI_enable,			--initiate transaction
		cpol    => SPI_cpol,			--spi clock polarity
		cpha    => SPI_cpha,			--spi clock phase
		cont    => SPI_cont,			--continuous mode command
		clk_div => SPI_clk_div,			--system clock cycles per 1/2 period of sclk
		addr    => (SPI_Slavenumber-1),	--address of slave
		tx_data => SPI_TX_Data,			--data to transmit
		miso    => SPI_MISO,			--master in, slave out
		sclk    => SPI_SCLK,			--spi clock
		ss_n    => open,				--slave select
		mosi    => SPI_MOSI,			--master out, slave in
		busy    => SPI_busy,			--busy / data ready signal
		rx_data => SPI_RX_Data			--data received
	); 
	
-- Statemachine-Prozess-----------------------------------------------------------------------------
StateMachine_LTC : process (clock)
begin
	if (reset_n = '0') then																		-- Reset
		SPI_TX_Data				<= x"FFFFFFFF";

		error_flag				<= '0';
		byte_tx_counter			<= (others=> '0');
		byte_rx_counter			<= (others=> '0');
		wakeup_counter			<= (others=> '0');

		SPI_SS					<= '1';
		SPI_enable				<= '0';
		busy					<= '1';
		ready					<= '0';
		LTC_resetn				<= '0';
		
		Temp_00_out				<=(others=>'0');
		Temp_01_out				<=(others=>'0');
		Temp_02_out				<=(others=>'0');
		Temp_03_out				<=(others=>'0');
		Temp_04_out				<=(others=>'0');
		Temp_05_out				<=(others=>'0');
		Temp_06_out				<=(others=>'0');
		Temp_07_out				<=(others=>'0');
		Temp_08_out				<=(others=>'0');
		Temp_09_out				<=(others=>'0');
		Temp_10_out				<=(others=>'0');
		Temp_11_out				<=(others=>'0');
		Temp_12_out				<=(others=>'0');
		Temp_13_out				<=(others=>'0');
		Temp_14_out				<=(others=>'0');
		Temp_15_out				<=(others=>'0');
		Temp_16_out				<=(others=>'0');
		Temp_17_out				<=(others=>'0');
		Temp_18_out				<=(others=>'0');
		Temp_19_out				<=(others=>'0');
		
		for K in 0 to 19 loop
			LTC_Channelresults(K)	<=(others=>'0');
		end loop;

		state_LTC_Interface		<= LTC_powerup;
		laststate_LTC_Interface	<= LTC_powerup;
	elsif (reset_n = '1' ) then
		if (rising_edge (clock) AND enable = '1') then
			case (state_LTC_Interface) is
			----------------------------------------------------------------------------------------
				when LTC_powerup =>																-- Status nach POR
					busy								<= '1';
					ready								<= '0';
					LTC_resetn							<= '0';

					state_LTC_Interface					<= LTC_Resetcounter;
					laststate_LTC_Interface				<= LTC_powerup;
			----------------------------------------------------------------------------------------
				when LTC_Resetcounter =>
					if(wakeup_counter >= 1500) then												-- 15 us warten nach POR
							state_LTC_Interface			<= LTC_Wakeup;
							laststate_LTC_Interface		<= LTC_Resetcounter;
							LTC_resetn					<= '1';
							wakeup_counter				<= (others=> '0');
						else
							wakeup_counter				<= wakeup_counter + 1;
						end if;
			----------------------------------------------------------------------------------------
				when LTC_Wakeup =>
					if(wakeup_counter >= 20000000) then											-- 200ms warten nach POR  (20000000)
						
						LTC_Channelconfigs(0)	<= LTC_CH_0_config_in;							-- Latchen der Configdaten,. nur nach Reset kann die Config verändert werden
						LTC_Channelconfigs(1)	<= LTC_CH_1_config_in;							-- keine neukonfigurierung des LTC im laufenden Betrieb, da nicht gebraucht
						LTC_Channelconfigs(2)	<= LTC_CH_2_config_in;
						LTC_Channelconfigs(3)	<= LTC_CH_3_config_in;
						LTC_Channelconfigs(4)	<= LTC_CH_4_config_in;
						LTC_Channelconfigs(5)	<= LTC_CH_5_config_in;
						LTC_Channelconfigs(6)	<= LTC_CH_6_config_in;
						LTC_Channelconfigs(7)	<= LTC_CH_7_config_in;
						LTC_Channelconfigs(8)	<= LTC_CH_8_config_in;
						LTC_Channelconfigs(9)	<= LTC_CH_9_config_in;
						LTC_Channelconfigs(10)	<= LTC_CH_10_config_in;
						LTC_Channelconfigs(11)	<= LTC_CH_11_config_in;
						LTC_Channelconfigs(12)	<= LTC_CH_12_config_in;
						LTC_Channelconfigs(13)	<= LTC_CH_13_config_in;
						LTC_Channelconfigs(14)	<= LTC_CH_14_config_in;
						LTC_Channelconfigs(15)	<= LTC_CH_15_config_in;
						LTC_Channelconfigs(16)	<= LTC_CH_16_config_in;
						LTC_Channelconfigs(17)	<= LTC_CH_17_config_in;
						LTC_Channelconfigs(18)	<= LTC_CH_18_config_in;
						LTC_Channelconfigs(19)	<= LTC_CH_19_config_in;
						
						state_LTC_Interface				<= LTC_SendCFG;							-- Prozedur laut Datenblat LTC2983
						laststate_LTC_Interface			<= LTC_Wakeup;
						wakeup_counter					<= (others=> '0');
					else
						wakeup_counter					<= wakeup_counter + 1;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_SendCFG =>																--Initiale Kanalconfig senden
					if(byte_tx_counter <= 79) then												-- Channelkonfig senden
						SPI_TX_Data						<= SPI_writeCMD & std_logic_vector((unsigned(LTC_Channeladdr_start) + byte_tx_counter)) & LTC_Channelconfigs(to_integer(byte_tx_counter(7 downto 2))) (31-(8*to_integer(byte_tx_counter(1 downto 0))) downto 24-(8*to_integer(byte_tx_counter(1 downto 0))));					
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						byte_tx_counter					<= byte_tx_counter +1;
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_SendCFG;	
					elsif(byte_tx_counter = 80) then					-- Multichannelconversionmask CH20-CH17 setzen senden
						SPI_TX_Data						<= SPI_writeCMD & x"00F5" & x"0F";
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						byte_tx_counter					<= byte_tx_counter +1;
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_SendCFG;	
					elsif(byte_tx_counter = 81) then					-- Multichannelconversionmask CH16-CH9 setzen senden
						SPI_TX_Data						<= SPI_writeCMD & x"00F6" & x"FF";
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						byte_tx_counter					<= byte_tx_counter +1;
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_SendCFG;	
					elsif(byte_tx_counter = 82) then					-- Multichannelconversionmask CH8-CH0 setzen senden
						SPI_TX_Data						<= SPI_writeCMD & x"00F7" & x"FF";
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						byte_tx_counter					<= byte_tx_counter +1;
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_SendCFG;	
					else
						byte_tx_counter					<= (others=>'0');
						state_LTC_Interface				<= LTC_start;
						laststate_LTC_Interface			<= LTC_SendCFG;	
					end if;			
			----------------------------------------------------------------------------------------
				when LTC_start =>																-- Design wartet auf globalen Trigger 
					busy								<= '0';
					ready								<= '0';
					if (go_sig = '1')then
						busy							<= '1';
						state_LTC_Interface				<= LTC_ConvStart;
						laststate_LTC_Interface			<= LTC_start;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_ConvStart =>															-- Conversion-Start Puls generieren
					if(laststate_LTC_Interface = LTC_SPI_WaitCShigh) then
						state_LTC_Interface				<= LTC_WaitConversion;
						laststate_LTC_Interface			<= LTC_ConvStart;	
					else
						SPI_TX_Data						<= SPI_writeCMD & x"0000" & x"80";		-- Channelkonfig Byte 0 senden
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_ConvStart;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_WaitConversion =>														-- warten auf Interrupt
					if(wakeup_counter >= 1500) then												-- 15uS warten, bis Interruptpin vom LTC gesetzt wurde (1500)
						if(LTC_Interrupt = '1') then											-- Abfrage, ob Interruptpin auf 1 für abgeschlossene conversion
							state_LTC_Interface			<= LTC_InitialReadData;
							laststate_LTC_Interface		<= LTC_WaitConversion;
							wakeup_counter				<= (others=> '0');
						end if;
					else
						wakeup_counter					<= wakeup_counter + 1;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_InitialReadData =>														-- Initiales lesen
					if(laststate_LTC_Interface = LTC_SPI_WaitCShigh) then
						state_LTC_Interface				<= LTC_ReadData;
						laststate_LTC_Interface			<= LTC_InitialReadData;
					else
						SPI_TX_Data						<= SPI_readCMD & std_logic_vector((unsigned(LTC_resultsaddr_start))) & x"00";					
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_InitialReadData;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_ReadData =>															-- Daten lesen
					if(byte_tx_counter <= 78) then																																					-- Channeldaten lesen
						SPI_TX_Data						<= SPI_readCMD & std_logic_vector((unsigned(LTC_resultsaddr_start) + byte_tx_counter+1)) & x"00";					
						SPI_enable						<= '1';
						SPI_SS							<= '0';
						LTC_Channelresults(to_integer(byte_tx_counter(7 downto 2))) (31-(8*to_integer(byte_tx_counter(1 downto 0))) downto 24-(8*to_integer(byte_tx_counter(1 downto 0))))		<= SPI_RX_Data(7 downto 0);			-- Empfang MSB first!!!
						byte_tx_counter					<= byte_tx_counter +1;
						state_LTC_Interface				<= LTC_SPI_Waittransmit1;
						laststate_LTC_Interface			<= LTC_ReadData;		
					else
						LTC_Channelresults(to_integer(byte_tx_counter(7 downto 2))) (31-(8*to_integer(byte_tx_counter(1 downto 0))) downto 24-(8*to_integer(byte_tx_counter(1 downto 0))))		<= SPI_RX_Data(7 downto 0);			-- letztes Byte abspeichern
						byte_tx_counter					<= (others=>'0');
						state_LTC_Interface				<= LTC_Output;
						laststate_LTC_Interface			<= LTC_ReadData;	
					end if;	
			----------------------------------------------------------------------------------------
				when LTC_Output =>																-- Aktualisierte Daten am Ausgang durch ready-Flag anzeigen
					busy								<= '0';
					ready								<= '1';
					
					-- Daten aus dem Empfangsspeicher drehen, um mit in die MSB-Darstellung zu kommen
					Temp_00_out							<= LTC_Channelresults(0) ;
					Temp_01_out							<= LTC_Channelresults(1) ;
					Temp_02_out							<= LTC_Channelresults(2) ;
					Temp_03_out							<= LTC_Channelresults(3) ;
					Temp_04_out							<= LTC_Channelresults(4) ;
					Temp_05_out							<= LTC_Channelresults(5) ;
					Temp_06_out							<= LTC_Channelresults(6) ;
					Temp_07_out							<= LTC_Channelresults(7) ;
					Temp_08_out							<= LTC_Channelresults(8) ;
					Temp_09_out							<= LTC_Channelresults(9) ;
					Temp_10_out							<= LTC_Channelresults(10);
					Temp_11_out							<= LTC_Channelresults(11);
					Temp_12_out							<= LTC_Channelresults(12);
					Temp_13_out							<= LTC_Channelresults(13);
					Temp_14_out							<= LTC_Channelresults(14);
					Temp_15_out							<= LTC_Channelresults(15);
					Temp_16_out							<= LTC_Channelresults(16);
					Temp_17_out							<= LTC_Channelresults(17);
					Temp_18_out							<= LTC_Channelresults(18);
					Temp_19_out							<= LTC_Channelresults(19);
		
					state_LTC_Interface					<= LTC_start;
					laststate_LTC_Interface				<= LTC_Output;
			---------------------------------------------------------------------------------------- 
				when LTC_Failstate =>															-- Zusätzliches Fehlerhandlig hier möglich
				
			---------------------------------------------------------------------------------------- 
				when LTC_SPI_Waittransmit1 =>													-- Wartezustand 1 für den SPI-Core
					SPI_enable							<= '0';									-- SPI-Enable wird genommen
					state_LTC_Interface					<= LTC_SPI_Waittransmit2;
			----------------------------------------------------------------------------------------
				when LTC_SPI_Waittransmit2 =>													-- Wartezustand 2 für den SPI-Core
					SPI_enable							<= '0';									-- Warten auf fertige Übertragung
					if(SPI_busy = '0') then
						SPI_SS							<= '1';
						state_LTC_Interface				<= LTC_SPI_WaitCShigh;
					end if;
			----------------------------------------------------------------------------------------
				when LTC_SPI_WaitCShigh =>
					if(wakeup_counter >= 500) then												-- 15 us warten nach POR
							state_LTC_Interface			<= laststate_LTC_Interface;
							laststate_LTC_Interface		<= LTC_SPI_WaitCShigh;
							wakeup_counter				<= (others=> '0');
						else
							wakeup_counter				<= wakeup_counter + 1;
						end if;
			----------------------------------------------------------------------------------------
				when others =>
					state_LTC_Interface                 <= LTC_Failstate;
			----------------------------------------------------------------------------------------	
			end case;	
		end if;
	end if;	
end process;

end Behavioral;
