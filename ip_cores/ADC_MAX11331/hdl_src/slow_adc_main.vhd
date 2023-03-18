----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.11.2018 09:16:14
-- Design Name: 
-- Module Name: slow_adc_main - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

use work.ADC_MAX11331_PKG.all;


entity Slow_ADC_Memory_main is
	GENERIC
	(
		OUTPUT_WORD_WIDTH 		: INTEGER := 12;        -- Use 12 for normal operation. Use 16 for debug.
		DIFFERENTIAL_SAMPLING 	: BOOLEAN := false;		-- true: 8 differential inputs, false: 16 single-ended inputs
		DEBUG_MESSAGE_INCLUDED 	: BOOLEAN := false;		-- true: adds 4bit ADC register + 12 bit sample result
		NUMBER_OF_ADCS			: INTEGER := 1			-- How many MAX11331 ADCs are connected to this IP Core
	);
	Port
	(
		clk 					: in STD_LOGIC;
		reset_n 				: in STD_LOGIC;
		enable_measure 			: in STD_LOGIC;
		clk_division 			: IN STD_LOGIC_VECTOR(3 DOWNTO 0); --f_internal = 1/clk_division * f_external 
		sclk 					: out STD_LOGIC;
		mosi 					: out STD_LOGIC;
		miso 					: IN STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1);
		ss_n 					: out STD_LOGIC;
		init_done 				: out STD_LOGIC;
		meas_done 				: out STD_LOGIC;
		new_data 				: out STD_LOGIC;
		error 					: out STD_LOGIC;
		error_counter			: out STD_LOGIC_VECTOR (31 downto 0);
		adc_selector			: in STD_LOGIC_VECTOR (NUMBER_OF_ADCS downto 1);
		force_init 				: in STD_LOGIC;
		data_echo_bipolar       : out t_array_message(NUMBER_OF_ADCS downto 1);
		data_echo_unipolar      : out t_array_message(NUMBER_OF_ADCS downto 1);
		
		all_differential_channels : out t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0);
		all_single_ended_channels : out t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0);
		
		data_ch0 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch1 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch2 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch3 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch4 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch5 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch6 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch7 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch8 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch9 	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch10	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch11	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch12	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch13	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch14	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0);
		data_ch15	: out STD_LOGIC_VECTOR (OUTPUT_WORD_WIDTH-1 downto 0)
	);
end Slow_ADC_Memory_main;

architecture Behavioral of Slow_ADC_Memory_main is
	signal  counter      : integer := 0;
	signal  enable_spi_S :   std_logic := '0';
	signal  busy_spi_S   :   std_logic := '0';
	signal  error_counter_S :std_logic_vector(31 downto 0) := (others=>'0'); 
	signal  error_S      :   std_logic := '0';
	signal  meas_done_S  :   std_logic := '0';
	signal  init_done_S  :   std_logic := '0';
	signal  new_data_S   :   std_logic := '0';
	signal  tx_data_S    :   t_message 	:= (others=>'0'); 
	signal  rx_data_S    :   t_array_message(NUMBER_OF_ADCS downto 1) := (others => (others => '0'));
	
	signal  data_ouput_register :              t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));
    signal  data_ouput_register_single_ended : t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));
	
	signal  data_ch00_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch01_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch02_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch03_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch04_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch05_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch06_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch07_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch08_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch09_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch10_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch11_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch12_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch13_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch14_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	signal  data_ch15_S  :  STD_LOGIC_VECTOR (15 downto 0) := (others=>'0'); 
	
	
	type state_t is (INIT_START, INIT_ADC_REG, INIT_DELAY_0, INIT_BIPOLAR_REG, INIT_DELAY_1, INIT_UNIPOLAR_REG, INIT_DELAY_2, INIT_RANGE_REG, INIT_DELAY_3, IDLE, MEAS_DELAY_IDLE, 	-- initialize register
	MEAS_ASK_0, MEAS_DELAY_ASK_0, MEAS_ASK_2, MEAS_DELAY_ASK_2, MEAS_ASK_4, MEAS_DELAY_ASK_4, MEAS_ASK_6, MEAS_DELAY_ASK_6, MEAS_ASK_8, MEAS_DELAY_ASK_8, MEAS_ASK_10, MEAS_DELAY_ASK_10, MEAS_ASK_12, MEAS_DELAY_ASK_12, MEAS_ASK_14, MEAS_DELAY_ASK_14, MEAS_ASK_EXTRA_DIFF, 	-- differential/single-ended channels
	MEAS_ASK_1, MEAS_DELAY_ASK_1, MEAS_ASK_3, MEAS_DELAY_ASK_3, MEAS_ASK_5, MEAS_DELAY_ASK_5, MEAS_ASK_7, MEAS_DELAY_ASK_7, MEAS_ASK_9, MEAS_DELAY_ASK_9, MEAS_ASK_11, MEAS_DELAY_ASK_11, MEAS_ASK_13, MEAS_DELAY_ASK_13, MEAS_ASK_15, MEAS_DELAY_ASK_15, MEAS_ASK_EXTRA_SING,  -- single-ended channels	
	MEAS_DELAY_ASK_EXTRA, -- last channel
	ERROR_STATE, INIT_RESET, INIT_DELAY_RESET); -- error states
	signal state                    : state_t := IDLE;  

	SIGNAL data_echo_bipolar_S  : t_array_message(NUMBER_OF_ADCS downto 1) := (others => (others => '0'));
	SIGNAL data_echo_unipolar_S : t_array_message(NUMBER_OF_ADCS downto 1) := (others => (others => '0'));
	SIGNAL verify_echo_bipolar_detail	: STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1) := (others => '0');
	SIGNAL verify_echo_unipolar_detail	: STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1) := (others => '0');
	SIGNAL verify_echo_bipolar		: STD_LOGIC;
	SIGNAL verify_echo_unipolar	: STD_LOGIC;
	
	SIGNAL adc_echoed_bipolar_S  : STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1) := (others => '0');
	SIGNAL adc_echoed_unipolar_S : STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1) := (others => '0');
	type memory_t16 is array (0 to 15) of STD_LOGIC_VECTOR(15 downto 0);
	type memory_t8  is array (0 to  7) of STD_LOGIC_VECTOR(15 downto 0);
	SIGNAL adc1_array_S : memory_t16 := (others => (others => '0'));
	signal adc_channels          : t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));
	signal adc_channels_single   : t_matrix_message(NUMBER_OF_ADCS downto 1, C_NUM_CHANNELS-1 downto 0) := (others=> (others => (others => '0')));
	
 
	SIGNAL   DELAY				: INTEGER RANGE 0 TO 31; --Delay count from main clock (100MHz) between SPI transfers. 
	CONSTANT DELAY_ERROR       : INTEGER := 49;	-- delay count from main clock (100MHz) between error state and restart initialization. Consider delay - 1.
	CONSTANT MSG_RESET	       : STD_LOGIC_VECTOR(15 downto 0) := "0000000001000000";	-- ADC Mode Control: 	Reset entire chip (Table 2) 
	CONSTANT MSG_INIT_1	       : STD_LOGIC_VECTOR(15 downto 0) := "1000000000000100";	-- ADC Configuration: 	activate echo (Table 6)
	CONSTANT MSG_INIT_2_DIFF    : STD_LOGIC_VECTOR(15 downto 0) := "1001011111111000";	-- Bipolar register: 	1 bipolar fully-differential (Table 11)
	CONSTANT MSG_INIT_2_SING    : STD_LOGIC_VECTOR(15 downto 0) := "1001000000000000";	-- Bipolar register: 	0 unipolar (= single-ended) (Table 11)
	SIGNAL MSG_INIT_2 	       : STD_LOGIC_VECTOR(15 downto 0) := (others => '0'); -- assigned DIFF or SING depending on acquisition mode
	CONSTANT MSG_INIT_3	       : STD_LOGIC_VECTOR(15 downto 0) := "1000100000000000";	-- Unipolar register: 	1 pseudo-differential, 0 single-ended (Table 10)
	CONSTANT MSG_INIT_4	       : STD_LOGIC_VECTOR(15 downto 0) := "1001111111111000";	-- Range register:		1: -Vref..+Vref, 0: -Vref/2..+Vref/2 (only applicable for differential, for single-ended always 0..+Vref) (Table 7)
   
	-- ADC MODE CONTROL REGISTER see Table 2 + 3
	-- REG_CNTL Bit 15 = 0
	-- SCAN  Bit 14..11		e.g. 0001  = Manual selection of channel 
	-- CHSEL Bit 10..7		e.g. 0100  = Selection of AIN4
	CONSTANT MSG_MEAS_ASK_0 	: STD_LOGIC_VECTOR(15 downto 0) := "0000100000000100";
    CONSTANT MSG_MEAS_ASK_1 	: STD_LOGIC_VECTOR(15 downto 0) := "0000100010000100";
	CONSTANT MSG_MEAS_ASK_2		: STD_LOGIC_VECTOR(15 downto 0) := "0000100100000100";
	CONSTANT MSG_MEAS_ASK_3		: STD_LOGIC_VECTOR(15 downto 0) := "0000100110000100";
	CONSTANT MSG_MEAS_ASK_4		: STD_LOGIC_VECTOR(15 downto 0) := "0000101000000100";
	CONSTANT MSG_MEAS_ASK_5		: STD_LOGIC_VECTOR(15 downto 0) := "0000101010000100";
	CONSTANT MSG_MEAS_ASK_6		: STD_LOGIC_VECTOR(15 downto 0) := "0000101100000100";
	CONSTANT MSG_MEAS_ASK_7		: STD_LOGIC_VECTOR(15 downto 0) := "0000101110000100";
	CONSTANT MSG_MEAS_ASK_8		: STD_LOGIC_VECTOR(15 downto 0) := "0000110000000100";
	CONSTANT MSG_MEAS_ASK_9		: STD_LOGIC_VECTOR(15 downto 0) := "0000110010000100";
	CONSTANT MSG_MEAS_ASK_10	: STD_LOGIC_VECTOR(15 downto 0) := "0000110100000100";
	CONSTANT MSG_MEAS_ASK_11	: STD_LOGIC_VECTOR(15 downto 0) := "0000110110000100";
	CONSTANT MSG_MEAS_ASK_12	: STD_LOGIC_VECTOR(15 downto 0) := "0000111000000100";
	CONSTANT MSG_MEAS_ASK_13	: STD_LOGIC_VECTOR(15 downto 0) := "0000111010000100";
	CONSTANT MSG_MEAS_ASK_14	: STD_LOGIC_VECTOR(15 downto 0) := "0000111100000100";
	CONSTANT MSG_MEAS_ASK_15	: STD_LOGIC_VECTOR(15 downto 0) := "0000111110000100";
	
	CONSTANT ZERO_PADDING : STD_LOGIC_VECTOR(OUTPUT_WORD_WIDTH-1 downto C_ADC_DATA_BITS) := (others => '0');
	
	COMPONENT spi_master_multi_slave IS
		GENERIC(
			 NUMBER_OF_PERIPH: INTEGER := 2
		);
		PORT
		(
			clock   : IN     STD_LOGIC;                      --system clock
			reset_n : IN     STD_LOGIC;                      --asynchronous reset
			enable  : IN     STD_LOGIC;                      --initiate transaction
			clk_division : IN STD_LOGIC_VECTOR(3 DOWNTO 0);  --system clock cycles per 1/2 period of sclk
			tx_data : IN     STD_LOGIC_VECTOR(15 DOWNTO 0);  --data to transmit
			miso    : IN     STD_LOGIC_VECTOR(NUMBER_OF_ADCS downto 1);
			sclk    : OUT    STD_LOGIC;                         --spi clock
			ss_n    : OUT    STD_LOGIC;   --slave select
			mosi    : OUT    STD_LOGIC;                      --master out, slave in
			rx_data : OUT    t_array_message(NUMBER_OF_ADCS downto 1); --data received, array of size NUMBER_OF_ADCS
			busy    : OUT    STD_LOGIC                      --busy / data ready signal
		);
	END COMPONENT spi_master_multi_slave;

	COMPONENT unary_AND IS
	generic (N: positive := 8); --array size
	port (
		inp: in std_logic_vector(N-1 downto 0);
		outp: out STD_LOGIC);
	END COMPONENT unary_AND;

begin

	unary_AND_bipolar : unary_AND
	generic map
	(N => NUMBER_OF_ADCS)
	PORT MAP
    (
		inp	 => verify_echo_bipolar_detail,
		outp => verify_echo_bipolar 	
    );
    	 
	unary_AND_unipolar : unary_AND
	generic map
	(N => NUMBER_OF_ADCS)
	PORT MAP
    (
		inp	 => verify_echo_unipolar_detail,
		outp => verify_echo_unipolar 	
    );

	spi_master_multi_slave_0 : spi_master_multi_slave
	generic map
	(
		 NUMBER_OF_PERIPH => NUMBER_OF_ADCS
	)
	PORT MAP
   (
		clock   => clk,                --system clock
		reset_n => reset_n,              --asynchronous reset
		enable  => enable_spi_S,           --initiate transaction
		clk_division => clk_division,      --system clock cycles per 1/2 period of sclk
		tx_data => tx_data_S, --data to transmit
		miso     => miso,						 --master in, slave out
		sclk    => sclk,                --spi clock
		ss_n    => ss_n,                   --slave select
		mosi    => mosi,               --master out, slave in
		busy    => busy_spi_S,              --busy / data ready signal
		rx_data => rx_data_S 		--data received, array of size NUMBER_OF_ADCS
    );
    	 
	-- HANDLE INIT BEHAVIOR OF SINGLE-ENDED or DIFFERENTIAL MEASUREMENT
	MSG_INIT_2 <= MSG_INIT_2_DIFF when(DIFFERENTIAL_SAMPLING) else MSG_INIT_2_SING;
	 
	-- HANDLE DELAY_SIGNAL 
	DELAY <= to_integer(unsigned(clk_division));
	
    -- Slow ADC State Machine - Mealy / Moore
	State_Machine : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			state <= INIT_START;                      --return to initial state
			tx_data_S <= (others => '0'); 
			enable_spi_S <= '0';
			counter <= 0;
            
		ELSIF rising_edge(clk) THEN
			CASE state IS
			--Start the initialization sending the first word via SPI.
			WHEN INIT_START =>
				IF counter = DELAY THEN				
					tx_data_S <= MSG_INIT_1;
					enable_spi_S <= '1';
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_START;
					ELSE
						state <= INIT_ADC_REG;
					END IF;					
				ELSE
					state <= INIT_START;
					tx_data_S <= (others => '0'); 
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;				
 
			--Initializing ADC Register 
			WHEN INIT_ADC_REG =>
				tx_data_S <= MSG_INIT_1;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_0;
				ELSE
					state <= INIT_ADC_REG;
				END IF;

			--Delay after ADC Register write
			WHEN INIT_DELAY_0 =>	
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_2;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_0;
					ELSE
						state <= INIT_BIPOLAR_REG;
					END IF;
				ELSE
					state <= INIT_DELAY_0;
					tx_data_S <= MSG_INIT_1;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;			

			--Initializing BIPOLAR Register 
			WHEN INIT_BIPOLAR_REG =>
				tx_data_S <= MSG_INIT_2;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_1;
				ELSE
					state <= INIT_BIPOLAR_REG;
				END IF;

			--Delay after BIPOLAR Register write
			WHEN INIT_DELAY_1 =>
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_3;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends				
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_1;
					ELSE
						state <= INIT_UNIPOLAR_REG;
					END IF;
				ELSE
					state <= INIT_DELAY_1;
					tx_data_S <= MSG_INIT_2;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
				END IF;	
				
			--Initializing UNIPOLAR Register 
			WHEN INIT_UNIPOLAR_REG =>
				tx_data_S <= MSG_INIT_3;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_2;
				ELSE
					state <= INIT_UNIPOLAR_REG;
				END IF;

			--Delay after UNIPOLAR Register write
			WHEN INIT_DELAY_2 =>
				IF counter = DELAY THEN
					tx_data_S <= MSG_INIT_4;
					enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends				
					counter <= DELAY;
					IF busy_spi_S = '0' THEN
						state <= INIT_DELAY_2;
					ELSE
						state <= INIT_RANGE_REG;
					END IF;
				ELSE
					tx_data_S <= MSG_INIT_3;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					counter <= counter + 1;
					IF verify_echo_bipolar = '1' THEN	--check for echoed data
						state <= INIT_DELAY_2;
					ELSE
						state <= ERROR_STATE;
					END IF;
				END IF;

			--Initializing RANGE Register 
			WHEN INIT_RANGE_REG =>
				tx_data_S <= MSG_INIT_4;
				enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_3;
				ELSE
					state <= INIT_RANGE_REG;
				END IF;

			--Delay after RANGE Register write
			WHEN INIT_DELAY_3 =>				
				IF counter = DELAY THEN
					tx_data_S <= MSG_MEAS_ASK_0;	
					counter <= DELAY;
					if force_init = '1' then
						state <= MEAS_DELAY_IDLE;					
						enable_spi_S <= '1';			-- enable_spi must be LOW before the spi message ends
					else
						state <= IDLE;		
						enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends						
					end if;
				ELSE
					state <= INIT_DELAY_3;
					tx_data_S <= MSG_INIT_4;
					counter <= counter + 1;
					enable_spi_S <= '0';			-- enable_spi must be LOW before the spi message ends
					IF verify_echo_unipolar = '1' THEN	--check for echoed data
						state <= INIT_DELAY_3;
					ELSE
						state <= ERROR_STATE;
					END IF;						
				END IF;	
	
			WHEN IDLE =>
				counter <= 0;
				IF enable_measure = '1' THEN
					if force_init = '1' then
						state <= INIT_START;		
						tx_data_S <= MSG_INIT_1;	
						enable_spi_S <= '0';			
					else -- normal operation 
						state <= MEAS_DELAY_IDLE;	
						tx_data_S <= MSG_MEAS_ASK_0;
						enable_spi_S <= '1';	
					end if;
				ELSE
					state <= IDLE;
					enable_spi_S <= '0';
					tx_data_S <= MSG_MEAS_ASK_0;
				END IF;	

			WHEN MEAS_DELAY_IDLE =>					-- Delay after enable measure
				tx_data_S <= MSG_MEAS_ASK_0;		-- Prepare tx_data for the next message. Ask for ch0
				enable_spi_S <= '1';			-- After delay, latch data into SPI.						
				counter <= 0;
				IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
					state <= MEAS_ASK_0;
				ELSE
					state <= MEAS_DELAY_IDLE;
				END IF;				
				
			WHEN MEAS_ASK_0 =>					-- Asked ch0 to be measured. Wait until SPI transfer finish. Receive nothing usefull from SPI data
				tx_data_S <= MSG_MEAS_ASK_0;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					-- storage rx_data into the internal memory !!!!!!!!!!!. Do nothing here
					state <= MEAS_DELAY_ASK_0;
				ELSE
					state <= MEAS_ASK_0;
				END IF;
				
			WHEN MEAS_DELAY_ASK_0 =>				-- Delay after asked ch0 message
				tx_data_S <= MSG_MEAS_ASK_2;		-- Prepare tx_data for the next message. Ask for ch2
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_0;
					ELSE
						state <= MEAS_ASK_2;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_0;
				END IF;	
				
			WHEN MEAS_ASK_2 =>					-- Asked ch2 to be measured. Wait until SPI transfer finish. 
				tx_data_S <= MSG_MEAS_ASK_2;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,0) <= rx_data_S(ii); -- Receive ch0 data
					END LOOP;
					
					adc1_array_S(0)          <= rx_data_S(1); -- storage rx_data into the internal memory

					state <= MEAS_DELAY_ASK_2;
				ELSE
					state <= MEAS_ASK_2;
				END IF;
				
			WHEN MEAS_DELAY_ASK_2 =>				-- Delay after asked ch2 message
				tx_data_S <= MSG_MEAS_ASK_4;		-- Prepare tx_data for the next message. Ask for ch4
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_2;
					ELSE
						state <= MEAS_ASK_4;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_2;
				END IF;	

			WHEN MEAS_ASK_4 =>					-- Asked ch4 to be measured. Wait until SPI transfer finish. Receive ch2 data
				tx_data_S <= MSG_MEAS_ASK_4;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,1) <= rx_data_S(ii); -- Receive ch2 data
					END LOOP;
					
					adc1_array_S(2)          <=  rx_data_S(1); 

					state <= MEAS_DELAY_ASK_4;
				ELSE
					state <= MEAS_ASK_4;
				END IF;
				
			WHEN MEAS_DELAY_ASK_4 =>				-- Delay after asked ch4 message
				tx_data_S <= MSG_MEAS_ASK_6;		-- Prepare tx_data for the next message. Ask for ch6
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_4;
					ELSE
						state <= MEAS_ASK_6;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_4;
				END IF;	
				
			WHEN MEAS_ASK_6 =>					-- Asked ch6 to be measured. Wait until SPI transfer finish. Receive ch4 data
				tx_data_S <= MSG_MEAS_ASK_6;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,2) <= rx_data_S(ii); -- Receive ch4 data
					END LOOP;
					
					adc1_array_S(4)          <= rx_data_S(1);

					state <= MEAS_DELAY_ASK_6;
				ELSE
					state <= MEAS_ASK_6;
				END IF;
				
			WHEN MEAS_DELAY_ASK_6 =>				-- Delay after asked ch6 message
				tx_data_S <= MSG_MEAS_ASK_8;		-- Prepare tx_data for the next message. Ask for ch8
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_6;
					ELSE
						state <= MEAS_ASK_8;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_6;
				END IF;					
				
			WHEN MEAS_ASK_8 =>					-- Asked ch8 to be measured. Wait until SPI transfer finish. Receive ch6 data
				tx_data_S <= MSG_MEAS_ASK_8;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN

					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,3) <= rx_data_S(ii); -- Receive ch6 data
					END LOOP;
					
					adc1_array_S(6)          <=  rx_data_S(1);

					state <= MEAS_DELAY_ASK_8;
				ELSE
					state <= MEAS_ASK_8;
				END IF;
				
			WHEN MEAS_DELAY_ASK_8 =>				-- Delay after asked ch8 message
				tx_data_S <= MSG_MEAS_ASK_10;		-- Prepare tx_data for the next message. Ask for ch10
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_8;
					ELSE
						state <= MEAS_ASK_10;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_8;
				END IF;					

			WHEN MEAS_ASK_10 =>					-- Asked ch10 to be measured. Wait until SPI transfer finish. Receive ch8 data
				tx_data_S <= MSG_MEAS_ASK_10;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN

					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,4) <= rx_data_S(ii); -- Receive ch8 data
					END LOOP;

					adc1_array_S(8)          <= rx_data_S(1); 

					state <= MEAS_DELAY_ASK_10;
				ELSE
					state <= MEAS_ASK_10;
				END IF;
				
			WHEN MEAS_DELAY_ASK_10 =>				-- Delay after asked ch10 message
				tx_data_S <= MSG_MEAS_ASK_12;		-- Prepare tx_data for the next message. Ask for ch12
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_10;
					ELSE
						state <= MEAS_ASK_12;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_10;
				END IF;					

			WHEN MEAS_ASK_12 =>					-- Asked ch12 to be measured. Wait until SPI transfer finish. Receive ch10 data
				tx_data_S <= MSG_MEAS_ASK_12;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,5) <= rx_data_S(ii); -- Receive ch10 data
					END LOOP;
					
					adc1_array_S(10)         <=  rx_data_S(1);

					state <= MEAS_DELAY_ASK_12;
				ELSE
					state <= MEAS_ASK_12;
				END IF;
				
			WHEN MEAS_DELAY_ASK_12 =>				-- Delay after asked ch12 message
				tx_data_S <= MSG_MEAS_ASK_14;		-- Prepare tx_data for the next message. Ask for ch14
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_12;
					ELSE
						state <= MEAS_ASK_14;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_12;
				END IF;	
				
			WHEN MEAS_ASK_14 =>					-- Asked ch14 to be measured. Wait until SPI transfer finish. Receive ch12 data
				tx_data_S <= MSG_MEAS_ASK_14;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,6) <= rx_data_S(ii); -- Receive ch12 data
					END LOOP;
					
					adc1_array_S(12)         <=  rx_data_S(1); 
					state <= MEAS_DELAY_ASK_14;
				ELSE
					state <= MEAS_ASK_14;
				END IF;
				
			WHEN MEAS_DELAY_ASK_14 =>				-- Delay after asked ch14 message
				IF DIFFERENTIAL_SAMPLING THEN
					tx_data_S <= MSG_MEAS_ASK_0;	-- Prepare tx_data for the next message. Ask for ch0 in case of continuous sampling
				ELSE
					tx_data_S <= MSG_MEAS_ASK_1;	-- Prepare tx_data for the next message. Ask for ch1 in case of single-ended measurement
				END IF;
				 
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_14;
					ELSIF DIFFERENTIAL_SAMPLING then -- goto next state
						state <= MEAS_ASK_EXTRA_DIFF;
					ELSE -- single-ended sampling
						state <= MEAS_ASK_1;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_14;
				END IF;					

			WHEN MEAS_ASK_EXTRA_DIFF =>					-- Asked ch0 to be measured. Wait until SPI transfer finish. Receive ch14 data
				tx_data_S <= MSG_MEAS_ASK_0;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,7) <= rx_data_S(ii); -- Receive ch14 data
					END LOOP;
					
					adc1_array_S(2*7)         <=  rx_data_S(1); 
					state <= MEAS_DELAY_ASK_EXTRA;
				ELSE
					state <= MEAS_ASK_EXTRA_DIFF;
				END IF;
				
			WHEN MEAS_DELAY_ASK_EXTRA =>			-- Delay after asked extra ch0 message
				tx_data_S <= MSG_MEAS_ASK_0;		-- Prepare tx_data for the next message. Ask for ch0 in case of continuous sampling
				enable_spi_S <= '0';				-- Do not start a new SPI transfer because IDLE state is coming next
				IF counter = DELAY THEN				-- Delay added for increase chip_select (CS) time on '1'
					counter <= DELAY;
					state <= IDLE;		
				ELSE
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_EXTRA;
				END IF;

	-- START: Single-ended sampling of uneven channels 
-- CHANEL 1
			WHEN MEAS_ASK_1 =>					-- Ask ch1, Receive ch14 
				tx_data_S <= MSG_MEAS_ASK_1;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels(ii,7) <= rx_data_S(ii); -- Receive ch14 data
					END LOOP;
					adc1_array_S(14) <= rx_data_S(1); 
					
					state <= MEAS_DELAY_ASK_1;
				ELSE
					state <= MEAS_ASK_1;
				END IF;
				
			WHEN MEAS_DELAY_ASK_1 =>			-- Delay after asked ch1 message
				tx_data_S <= MSG_MEAS_ASK_3;	-- Prepare tx_data for the next message. Ask for ch3
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_1;
					ELSE
						state <= MEAS_ASK_3;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_1;
				END IF;
			
-- CHANNEL 3
			WHEN MEAS_ASK_3 =>					-- Ask ch3, Receive ch1
				tx_data_S <= MSG_MEAS_ASK_3;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,0) <= rx_data_S(ii); -- Receive ch1 data
					END LOOP;
					
					adc1_array_S(1) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_3;
				ELSE
					state <= MEAS_ASK_3;
				END IF;
				
			WHEN MEAS_DELAY_ASK_3 =>			-- Delay after asked ch3 message
				tx_data_S <= MSG_MEAS_ASK_5;	-- Prepare tx_data for the next message. Ask for ch5
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_3;
					ELSE
						state <= MEAS_ASK_5;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_3;
				END IF;
-- CHANNEL 5
			WHEN MEAS_ASK_5 =>					-- Ask ch5, Receive ch3
				tx_data_S <= MSG_MEAS_ASK_5;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,1) <= rx_data_S(ii); -- Receive ch3 data
					END LOOP;
					adc1_array_S(3) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_5;
				ELSE
					state <= MEAS_ASK_5;
				END IF;
				
			WHEN MEAS_DELAY_ASK_5 =>			-- Delay after asked ch3 message
				tx_data_S <= MSG_MEAS_ASK_7;	-- Prepare tx_data for the next message. Ask for ch5
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_5;
					ELSE
						state <= MEAS_ASK_7;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_5;
				END IF;
-- CHANNEL 7
			WHEN MEAS_ASK_7 =>					-- Ask ch7, Receive ch5
				tx_data_S <= MSG_MEAS_ASK_7;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,2) <= rx_data_S(ii); -- Receive ch5 data
					END LOOP;
					
					adc1_array_S(5) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_7;
				ELSE
					state <= MEAS_ASK_7;
				END IF;
				
			WHEN MEAS_DELAY_ASK_7 =>			-- Delay after asked ch7 message
				tx_data_S <= MSG_MEAS_ASK_9;	-- Prepare tx_data for the next message. Ask for ch9
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_7;
					ELSE
						state <= MEAS_ASK_9;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_7;
				END IF;
-- CHANNEL 9
			WHEN MEAS_ASK_9 =>					-- Ask ch9, Receive ch7
				tx_data_S <= MSG_MEAS_ASK_9;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
					adc1_array_S(7) <= rx_data_S(1); 
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,3) <= rx_data_S(ii); -- Receive ch7 data
					END LOOP;
						
					state <= MEAS_DELAY_ASK_9;
				ELSE
					state <= MEAS_ASK_9;
				END IF;
				
			WHEN MEAS_DELAY_ASK_9 =>			-- Delay after asked ch9 message
				tx_data_S <= MSG_MEAS_ASK_11;	-- Prepare tx_data for the next message. Ask for ch11
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_9;
					ELSE
						state <= MEAS_ASK_11;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_9;
				END IF;
-- CHANNEL 11
			WHEN MEAS_ASK_11 =>					-- Ask ch11, Receive ch9
				tx_data_S <= MSG_MEAS_ASK_11;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,4) <= rx_data_S(ii); -- Receive ch9 data
					END LOOP;
					
					adc1_array_S(9) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_11;
				ELSE
					state <= MEAS_ASK_11;
				END IF;
				
			WHEN MEAS_DELAY_ASK_11 =>			-- Delay after asked ch11 message
				tx_data_S <= MSG_MEAS_ASK_13;	-- Prepare tx_data for the next message. Ask for ch13
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_11;
					ELSE
						state <= MEAS_ASK_13;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_11;
				END IF;
-- CHANNEL 13
			WHEN MEAS_ASK_13 =>					-- Ask ch13, Receive ch11
				tx_data_S <= MSG_MEAS_ASK_13;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.
				
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,5) <= rx_data_S(ii); -- Receive ch11 data
					END LOOP;
					
					adc1_array_S(11) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_13;
				ELSE
					state <= MEAS_ASK_13;
				END IF;
				
			WHEN MEAS_DELAY_ASK_13 =>			-- Delay after asked ch3 message
				tx_data_S <= MSG_MEAS_ASK_15;	-- Prepare tx_data for the next message. Ask for ch15
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_13;
					ELSE
						state <= MEAS_ASK_15;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_13;
				END IF;
-- CHANNEL 15
			WHEN MEAS_ASK_15 =>					-- Ask ch15, Receive ch13
				tx_data_S <= MSG_MEAS_ASK_15;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN 		-- Wait until SPI transfer finish.

					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,6) <= rx_data_S(ii); -- Receive ch13 data
					END LOOP;
					
					adc1_array_S(13) <= rx_data_S(1); 
					state <= MEAS_DELAY_ASK_15;
				ELSE
					state <= MEAS_ASK_15;
				END IF;
				
			WHEN MEAS_DELAY_ASK_15 =>			-- Delay after asked ch15 message
				tx_data_S <= MSG_MEAS_ASK_0;	-- Prepare tx_data for the next message. Ask for ch0
				IF counter = DELAY THEN			-- Delay added for increase chip_select (CS) time on '1'
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY;
					IF busy_spi_S = '0' THEN	-- Wait until SPI transfer start, before change the state
						state <= MEAS_DELAY_ASK_15;
					ELSE
						state <= MEAS_ASK_EXTRA_SING;
					END IF;
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= MEAS_DELAY_ASK_15;
				END IF;
-- READ CHANNEL 15
			WHEN MEAS_ASK_EXTRA_SING =>		-- Asked ch0,  Receive ch15
				tx_data_S <= MSG_MEAS_ASK_0;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					
					FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
						adc_channels_single(ii,7) <= rx_data_S(ii); -- Receive ch15 data
					END LOOP;
					
					adc1_array_S(15)         <= rx_data_S(1); -- storage rx_data into the internal memory
					state <= MEAS_DELAY_ASK_EXTRA;
				ELSE
					state <= MEAS_ASK_EXTRA_SING;
				END IF;


	-- END: Single-ended sampling of uneven channels 
	
			WHEN ERROR_STATE =>						-- Error state rise the error flag to 1 and stop the state machine
				tx_data_S <= MSG_RESET;				-- Prepare tx_data for the next message. Reset adc chip register to defaults
				IF counter = DELAY_ERROR THEN		-- Extra delay added.
					enable_spi_S <= '1';			-- After delay, latch data into SPI.						
					counter <= DELAY_ERROR;
					IF busy_spi_S = '0' THEN		-- Wait until SPI transfer start, before change the state
						state <= ERROR_STATE;
					ELSE
						state <= INIT_RESET;
					END IF;				
				ELSE
					enable_spi_S <= '0';
					counter <= counter + 1;
					state <= ERROR_STATE;
				END IF;		

			WHEN INIT_RESET =>					-- Initializing ADC mode register to reset chip registers to defaults
				tx_data_S <= MSG_RESET;
				enable_spi_S <= '0';
				counter <= 0;
				IF busy_spi_S = '0' THEN
					state <= INIT_DELAY_RESET;
				ELSE
					state <= INIT_RESET;
				END IF;

			WHEN INIT_DELAY_RESET =>			-- Wait a long delay after reset chips
				tx_data_S <= (others => '0');
				enable_spi_S <= '0';			
				IF counter = DELAY_ERROR THEN
					state <= INIT_START;
					counter <= 0;
				ELSE
					state <= INIT_DELAY_RESET;
					counter <= counter + 1;
				END IF;						
			
			END CASE;
		END IF;
	END PROCESS;


    -- Assign meas done signal process
	meas_done_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			meas_done_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF state = IDLE THEN
				meas_done_S <= '1';
			ELSE
				meas_done_S <= '0';
			END IF;
		END IF;
	END PROCESS;	

    -- Assign init done signal process
	init_done_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			init_done_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_START) or (state = INIT_ADC_REG) or (state = INIT_DELAY_0) or (state = INIT_BIPOLAR_REG) or (state = INIT_DELAY_1) or (state = INIT_UNIPOLAR_REG) or (state = INIT_DELAY_2) or (state = INIT_RANGE_REG) or (state = INIT_DELAY_3) or (state = ERROR_STATE) or (state = INIT_RESET) or (state = INIT_DELAY_RESET)) THEN
				init_done_S <= '0';
			ELSE
				init_done_S <= '1';
			END IF;
		END IF;
	END PROCESS;	
	
    -- Assign echoed bipolar arrays process
	Echoed_bipolar_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_echo_bipolar_S <= (others => (others => '0'));
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_UNIPOLAR_REG) AND (busy_spi_S = '0')) THEN
				data_echo_bipolar_S <= rx_data_S;
			ELSE
				data_echo_bipolar_S <= data_echo_bipolar_S;
			END IF;
		END IF;
	END PROCESS;

    -- Assign echoed unipolar arrays process
	Echoed_unipolar_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_echo_unipolar_S <= (others => (others => '0'));
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_RANGE_REG) AND (busy_spi_S = '0')) THEN
				data_echo_unipolar_S <= rx_data_S;
			ELSE
				data_echo_unipolar_S <= data_echo_unipolar_S;
			END IF;
		END IF;
	END PROCESS;			
    
    -- Verify echoed bipolar message
	Verify_echoed_bipolar : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			adc_echoed_bipolar_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_UNIPOLAR_REG) AND (busy_spi_S = '0')) THEN

				check_echo_bipolar: FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
					-- sequential notation
					IF (rx_data_S(ii) = MSG_INIT_2)  THEN	-- check echo on adc chip 1
						adc_echoed_bipolar_S(ii) <= '1';
					ELSE 
						adc_echoed_bipolar_S(ii) <= '0';
					END IF;
				END LOOP;
				
			ELSIF state = INIT_START THEN
				adc_echoed_bipolar_S <= (others => '0');
			ELSE
				adc_echoed_bipolar_S <= adc_echoed_bipolar_S;
			END IF;
		END IF;
	END PROCESS;

    -- Verify echoed unipolar message
	Verify_echoed_unipolar : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			adc_echoed_unipolar_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = INIT_RANGE_REG) AND (busy_spi_S = '0')) THEN
				
				check_echo_unipolar: FOR ii IN NUMBER_OF_ADCS DOWNTO 1 LOOP 
					IF (rx_data_S(ii) = MSG_INIT_3) THEN
						adc_echoed_unipolar_S(ii) <= '1';
					ELSE 
						adc_echoed_unipolar_S(ii) <= '0';
					END IF;
				END LOOP;

			ELSIF state = INIT_START THEN
				adc_echoed_unipolar_S <= (others => '0');				
			ELSE
				adc_echoed_unipolar_S <= adc_echoed_unipolar_S;
			END IF;
		END IF;
	END PROCESS;	
	
    -- Error signal process
	error_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			error_S <= '0';
		ELSIF rising_edge(clk) THEN
			IF (state = ERROR_STATE) THEN
				error_S <= '1';
			ELSE
				error_S <= '0';
			END IF;
		END IF;
	END PROCESS;

    -- Error counter signal process
	error_counter_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			error_counter_S <= (others => '0');
		ELSIF rising_edge(clk) THEN
			IF ((state = ERROR_STATE) AND (counter = 1)) THEN
				error_counter_S <= std_logic_vector(to_unsigned(to_integer(unsigned( error_counter_S )) + 1, 32));
			ELSE
				error_counter_S <= error_counter_S;
			END IF;
		END IF;
	END PROCESS;
	
	-- Assign output measurement arrays process
	Output_assignment : PROCESS (clk, reset_n) IS
	BEGIN
		IF(reset_n = '0') THEN           --reset asserted
			data_ouput_register  <= (others=> (others => (others => '0')));
			data_ouput_register_single_ended  <= (others=> (others => (others => '0')));
			
			data_ch00_S <= (OTHERS => '0');
			data_ch01_S <= (OTHERS => '0');
			data_ch02_S <= (OTHERS => '0');
			data_ch03_S <= (OTHERS => '0');
			data_ch04_S <= (OTHERS => '0');
			data_ch05_S <= (OTHERS => '0');
			data_ch06_S <= (OTHERS => '0');
			data_ch07_S <= (OTHERS => '0');
			data_ch08_S <= (OTHERS => '0');
			data_ch09_S <= (OTHERS => '0');
			data_ch10_S <= (OTHERS => '0');
			data_ch11_S <= (OTHERS => '0');
			data_ch12_S <= (OTHERS => '0');
			data_ch13_S <= (OTHERS => '0');
			data_ch14_S <= (OTHERS => '0');
			data_ch15_S <= (OTHERS => '0');
			

			new_data_S <= '0';

		ELSIF rising_edge(clk) THEN
			IF meas_done_S = '1' THEN

				data_ouput_register <= adc_channels;
				
				IF DIFFERENTIAL_SAMPLING = false THEN
					data_ouput_register_single_ended <= adc_channels_single;

					data_ch00_S	 <= adc1_array_S(0);
					data_ch01_S	 <= adc1_array_S(1);
					data_ch02_S	 <= adc1_array_S(2);
					data_ch03_S	 <= adc1_array_S(3);
					data_ch04_S	 <= adc1_array_S(4);
					data_ch05_S	 <= adc1_array_S(5);
					data_ch06_S	 <= adc1_array_S(6);
					data_ch07_S	 <= adc1_array_S(7);
					data_ch08_S	 <= adc1_array_S(8);
					data_ch09_S	 <= adc1_array_S(9);
					data_ch10_S	 <= adc1_array_S(10);
					data_ch11_S	 <= adc1_array_S(11);
					data_ch12_S	 <= adc1_array_S(12);
					data_ch13_S	 <= adc1_array_S(13);
					data_ch14_S	 <= adc1_array_S(14);
					data_ch15_S	 <= adc1_array_S(15);
				ELSE
					data_ch00_S	 <= adc1_array_S(0);
					data_ch01_S	 <= adc1_array_S(2);
					data_ch02_S	 <= adc1_array_S(4);
					data_ch03_S	 <= adc1_array_S(6);
					data_ch04_S	 <= adc1_array_S(8);
					data_ch05_S	 <= adc1_array_S(10);
					data_ch06_S	 <= adc1_array_S(12);
					data_ch07_S	 <= adc1_array_S(14);

				END IF;


				new_data_S <= '1';
			ELSE --store value, i.e. create registers
				
				data_ouput_register <= data_ouput_register; 
				data_ouput_register_single_ended <= data_ouput_register_single_ended;

				data_ch00_S <= data_ch00_S;
				data_ch01_S <= data_ch01_S;
				data_ch02_S <= data_ch02_S;
				data_ch03_S <= data_ch03_S;
				data_ch04_S <= data_ch04_S;
				data_ch05_S <= data_ch05_S;
				data_ch06_S <= data_ch06_S;
				data_ch07_S <= data_ch07_S;
				data_ch08_S <= data_ch08_S;
				data_ch09_S <= data_ch09_S;
				data_ch10_S <= data_ch10_S;
				data_ch11_S <= data_ch11_S;
				data_ch12_S <= data_ch12_S;
				data_ch13_S <= data_ch13_S;
				data_ch14_S <= data_ch14_S;
				data_ch15_S <= data_ch15_S;
				

				new_data_S <= '0';
			END IF;
		END IF;
	END PROCESS;

	-- ASSIGN OUTPUTS 

	error <= error_S;
	error_counter <= error_counter_S;
	new_data <= new_data_S;
	init_done <= init_done_S;
	meas_done <= meas_done_S;

	-- echo is only evaluated if ADC is activated via "adc_selector" via AXI register
	echo:FOR ii IN NUMBER_OF_ADCS DOWNTO 1 GENERATE 
		verify_echo_bipolar_detail(ii)  <= '0' when ((adc_selector(ii) = '1') AND (adc_echoed_bipolar_S(ii)  = '0')) else '1';
		verify_echo_unipolar_detail(ii) <= '0' when ((adc_selector(ii) = '1') AND (adc_echoed_unipolar_S(ii) = '0')) else '1';
	END GENERATE;

	-- echo triggers error state via unary_AND process , pseudo code:
	-- verify_echo_bipolar  <= unary_AND(verify_echo_bipolar_detail); done in separate entity
	-- verify_echo_unipolar <= unary_AND(verify_echo_unipolar_detail); done in separate entity

	-- pass echoed message (sic!) upwards for debugging
	data_echo_bipolar     <= data_echo_bipolar_S;
	data_echo_unipolar    <= data_echo_unipolar_S;
	
    -- concurrent assignment of either (debug_message + data) or (ZERO_PADDING + data);
	ADC: FOR ii IN NUMBER_OF_ADCS DOWNTO 1 GENERATE 
		CHANNEL:FOR jj IN C_NUM_CHANNELS-1 DOWNTO 0 GENERATE 
	
		all_differential_channels(ii,jj) <= data_ouput_register(ii,jj)(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ouput_register(ii,jj)(C_ADC_DATA_BITS-1 downto 0));
			
		END GENERATE;
	END GENERATE;
	-- alternative naive routing the entire register
	-- data_all_channels_out <= data_ouput_register;

    data_ch0  <= data_ch00_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch00_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch1  <= data_ch01_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch01_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch2  <= data_ch02_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch02_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch3  <= data_ch03_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch03_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch4  <= data_ch04_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch04_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch5  <= data_ch05_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch05_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch6  <= data_ch06_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch06_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch7  <= data_ch07_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch07_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch8  <= data_ch08_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch08_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch9  <= data_ch09_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch09_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch10 <= data_ch10_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch10_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch11 <= data_ch11_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch11_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch12 <= data_ch12_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch12_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch13 <= data_ch13_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch13_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch14 <= data_ch14_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch14_S(C_ADC_DATA_BITS-1 downto 0));
    data_ch15 <= data_ch15_S(OUTPUT_WORD_WIDTH-1 downto 0) when(DEBUG_MESSAGE_INCLUDED) else (ZERO_PADDING & data_ch15_S(C_ADC_DATA_BITS-1 downto 0));


end Behavioral;
