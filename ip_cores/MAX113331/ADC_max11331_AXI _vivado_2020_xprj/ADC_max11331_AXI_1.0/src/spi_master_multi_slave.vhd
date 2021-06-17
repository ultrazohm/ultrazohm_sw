--------------------------------------------------------------------------------
--
--   FileName:         spi_master.vhd
--   Dependencies:     none
--   Design Software:  Quartus II Version 16.0 Build 211 Standart Version
--
--   HDL CODE IS PROVIDED "AS IS."  DIGI-KEY EXPRESSLY DISCLAIMS ANY
--   WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
--   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
--   PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL DIGI-KEY
--   BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
--   DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
--   PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
--   BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
--   ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
--
--   Version History
--   Version 1.0 7/23/2010 Scott Larson
--     Initial Public Release
--   Version 1.1 4/11/2013 Scott Larson
--     Corrected ModelSim simulation error (explicitly reset clk_toggles signal)
--   Version 2.0 9/10/2018 David Arancibia
--		 Simplified code and added 6 multi-slave miso's
--   Version 2.1 15/01/2019 David Arancibia
--		 Remove continuous mode
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
--use ieee.numeric_std.all;

ENTITY spi_master_multi_slave IS
	GENERIC
	(
		d_width : INTEGER		:= 16;				--data bus width
		cpol    : STD_LOGIC := '1';         --spi clock polarity
		cpha    : STD_LOGIC := '1'         --spi clock phase
	); 
  PORT
  (
		clock		: IN	STD_LOGIC;                             --system clock
		reset_n	: IN	STD_LOGIC;                             --asynchronous reset
		enable	: IN	STD_LOGIC;                             --initiate transaction
		clk_division : IN 	STD_LOGIC_VECTOR(3 DOWNTO 0);          --system clock cycles per 1/2 period of sclk
		tx_data	: IN	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);  --data to transmit
		miso1    : IN	STD_LOGIC;                             --master in, slave out
		miso2    : IN	STD_LOGIC;                             --master in, slave out
		miso3    : IN	STD_LOGIC;                             --master in, slave out
		miso4    : IN	STD_LOGIC;                             --master in, slave out
		miso5    : IN	STD_LOGIC;                             --master in, slave out
		miso6    : IN	STD_LOGIC;                             --master in, slave out
		sclk		: OUT	STD_LOGIC;                          	--spi clock
		mosi		: OUT	STD_LOGIC;                             --master out, slave in
		ss_n 		: OUT	STD_LOGIC;									   --slave select
		rx_data1 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel1
		rx_data2 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel2
		rx_data3 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel3
		rx_data4 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel4
		rx_data5 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel5
		rx_data6 : OUT	STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);	--data received channel6
		busy		: OUT	STD_LOGIC                            	--busy / data ready signal
	 );
END spi_master_multi_slave;

ARCHITECTURE logic OF spi_master_multi_slave IS
  SIGNAL sclk_S : STD_LOGIC; 
  SIGNAL ss_n_S : STD_LOGIC; 
  TYPE machine IS(ready, execute);                           --state machine data type
  SIGNAL state       : machine;                              --current state
  SIGNAL clk_ratio   : INTEGER RANGE 0 TO 15;                              --current clk_div
  SIGNAL count       : INTEGER RANGE 0 TO 15;                             --counter to trigger sclk from system clock
  SIGNAL clk_toggles : INTEGER RANGE 0 TO d_width*2 + 1;     --count spi clock toggles
  SIGNAL assert_data : STD_LOGIC;                            --'1' is tx sclk toggle, '0' is rx sclk toggle
  SIGNAL rx_buffer1   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL rx_buffer2   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL rx_buffer3   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL rx_buffer4   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL rx_buffer5   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL rx_buffer6   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --receive data buffer
  SIGNAL tx_buffer   : STD_LOGIC_VECTOR(d_width-1 DOWNTO 0); --transmit data buffer
  SIGNAL last_bit_rx : INTEGER RANGE 0 TO d_width*2;         --last rx data bit location
  SIGNAL clk_div 	: INTEGER RANGE 0 TO 15;
BEGIN

	clk_div <= conv_integer(unsigned(clk_division));
	sclk <= sclk_S;
	ss_n <= ss_n_S;
	
  PROCESS(clock, reset_n)
  BEGIN

    IF(reset_n = '0') THEN        --reset system
      busy <= '1';                --set busy signal
      ss_n_S <= '1';    				--deassert all slave select lines
      mosi <= 'Z';                --set master out to high impedance
      rx_data1 <= (OTHERS => '0'); --clear receive data port 1
		rx_data2 <= (OTHERS => '0'); --clear receive data port 1
		rx_data3 <= (OTHERS => '0'); --clear receive data port 1
		rx_data4 <= (OTHERS => '0'); --clear receive data port 1
		rx_data5 <= (OTHERS => '0'); --clear receive data port 1
		rx_data6 <= (OTHERS => '0'); --clear receive data port 1
      state <= ready;             --go to ready state when reset is exited

    ELSIF(clock'EVENT AND clock = '1') THEN
      CASE state IS               --state machine

        WHEN ready =>
          busy <= '0';             --clock out not busy signal
          ss_n_S <= '1'; --set all slave select outputs high
          mosi <= 'Z';             --set mosi output high impedance

          --user input to initiate transaction
          IF(enable = '1') THEN       
            busy <= '1';             --set busy signal

            IF(clk_div = 0) THEN     --check for valid spi speed
              clk_ratio <= 1;        --set to maximum speed if zero
              count <= 1;            --initiate system-to-spi clock counter
            ELSE
              clk_ratio <= clk_div;  --set to input selection if valid
              count <= clk_div;      --initiate system-to-spi clock counter
            END IF;
            sclk_S <= cpol;            --set spi clock polarity
            assert_data <= NOT cpha; --set spi clock phase
            tx_buffer <= tx_data;    --clock in data for transmit into buffer
            clk_toggles <= 0;        --initiate clock toggle counter
            last_bit_rx <= d_width*2 + conv_integer(cpha) - 1; --set last rx data bit
            state <= execute;        --proceed to execute state
          ELSE
            state <= ready;          --remain in ready state
          END IF;

        WHEN execute =>
          busy <= '1';        --set busy signal
          ss_n_S <= '0'; --set proper slave select output
          
          --system clock to sclk ratio is met
          IF(count = clk_ratio) THEN        
            count <= 1;                     --reset system-to-spi clock counter
            assert_data <= NOT assert_data; --switch transmit/receive indicator
            IF(clk_toggles = d_width*2 + 1) THEN
              clk_toggles <= 0;               --reset spi clock toggles counter
            ELSE
              clk_toggles <= clk_toggles + 1; --increment spi clock toggles counter
            END IF;
            
            --spi clock toggle needed
            IF(clk_toggles <= d_width*2 AND ss_n_S = '0') THEN 
              sclk_S <= NOT sclk_S; --toggle spi clock
            END IF;
            
            --receive spi clock toggle
            IF(assert_data = '0' AND clk_toggles < last_bit_rx + 1 AND ss_n_S = '0') THEN 
              rx_buffer1 <= rx_buffer1(d_width-2 DOWNTO 0) & miso1; --shift in received bit
				  rx_buffer2 <= rx_buffer2(d_width-2 DOWNTO 0) & miso2; --shift in received bit
				  rx_buffer3 <= rx_buffer3(d_width-2 DOWNTO 0) & miso3; --shift in received bit
				  rx_buffer4 <= rx_buffer4(d_width-2 DOWNTO 0) & miso4; --shift in received bit
				  rx_buffer5 <= rx_buffer5(d_width-2 DOWNTO 0) & miso5; --shift in received bit
				  rx_buffer6 <= rx_buffer6(d_width-2 DOWNTO 0) & miso6; --shift in received bit
            END IF;
            
            --transmit spi clock toggle
            IF(assert_data = '1' AND clk_toggles < last_bit_rx) THEN 
              mosi <= tx_buffer(d_width-1);                     --clock out data bit
              tx_buffer <= tx_buffer(d_width-2 DOWNTO 0) & '0'; --shift data transmit buffer
            END IF;
            
            --end of transaction
            IF(clk_toggles = d_width*2 + 1) THEN   
              busy <= '0';             --clock out not busy signal
              ss_n_S <= '1'; --set all slave selects high
              mosi <= 'Z';             --set mosi output high impedance
              rx_data1 <= rx_buffer1;    --clock out received data to output port
			  rx_data2 <= rx_buffer2;    --clock out received data to output port
			  rx_data3 <= rx_buffer3;    --clock out received data to output port
			  rx_data4 <= rx_buffer4;    --clock out received data to output port
			  rx_data5 <= rx_buffer5;    --clock out received data to output port
			  rx_data6 <= rx_buffer6;    --clock out received data to output port
              state <= ready;          --return to ready state
            ELSE                       --not end of transaction
              state <= execute;        --remain in execute state
            END IF;
          
          ELSE        --system clock to sclk ratio not met
            count <= count + 1; --increment counter
            state <= execute;   --remain in execute state
          END IF;

      END CASE;
    END IF;
  END PROCESS; 
END logic;
