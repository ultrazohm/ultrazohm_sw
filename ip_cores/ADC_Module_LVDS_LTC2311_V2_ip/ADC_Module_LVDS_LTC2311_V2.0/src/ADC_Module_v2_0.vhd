-- -------------------------------------------------------------
-- Created: 2019-07-29 14:30:00
-- 
-- Author S. Wendel
-- 
-- -------------------------------------------------------------
-- Description
-- -------------------------------------------------------------
-- ADC_Module
-- Top Level File of the ADC Block
-- Instantiation of the LVDS Buffers, SPI_Module and Calculate
-- Current and Calculate Voltage Module 
-- -------------------------------------------------------------
-- Version 1.0
-- -------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
library UNISIM;
use UNISIM.VComponents.all;


entity ADC_Module_v2_0 is
	generic(
		-- Users to add parameters here
        Number_of_ADCs          : integer := 1;
        INPUT_CLK_FREQUENCY     : integer := 100000000; -- Hz 
        SPI_CLK_FREQUENCY       : integer :=  25000000; -- Hz / value will be used to calculate the Reload-Value of the Clock divider
        PRE_DELAY               : integer := 0; -- 0 := 10ns / DELAY BETWEEN CNV TO ACTIVE AND DATA TRANSMISSION
        -- Datasheet 9.5ns  => 0 := 10ns
        POST_DELAY              : integer := 1; -- 0 := 10ns / DELAY BETWEEN END OF DATA TRANSMISSION AND CNV TO DISABLE 
        -- Datasheet 19.1   => 1 := 20ns                       -- 1    
        CONV_DELAY              : integer := 2; -- 0 := 10ns / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
        -- Datasheet 25     => 2 := 30ns    
        TRIGGER_ADC             : boolean := true; -- 0 := Continous Mode; 1 := Triggered Mode
        ADC_BITS                : integer := 16; -- Number of ADC BITs
        W_LENGTH                : integer := 18; -- WORDLENGTH
     --   CONVERSION_RATE_ADC     : integer := 48; ---CASR = 0.000732398*2^16 = 48(dec) = 30(hex)-- STEPS_A_out1 <= to_unsigned(16#0030#, 16);
  		ADC_SET_USER_OFFSET_1   : boolean := false --SW:If False (0), than the flag uses the measured value as offset. If True (1), than the flag uses the falue in ADC_USER_OFFSET.
		--ADC_USER_OFFSET_1       : integer := 32768 --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
		-- User parameters ends
		-- Do not modify the parameters beyond this line      

		-- Parameters of Axi Slave Bus Interface S00_AXI
	);
	port (
		-- Users to add ports here
		clk             : in std_logic;
		reset_n         : in std_logic;
        Trigger_cnv     : in std_logic; --SW: Wenn Pin auf 1 geht, wird neue Wandlung angestoßen, ansonsten muss er immer auf Low (0) bleiben!
  		SCLK_spi_P	    : out std_logic_vector(Number_of_ADCs-1 downto 0);
  		SCLK_spi_N	    : out std_logic_vector(Number_of_ADCs-1 downto 0);
		SS_N_spi        : out std_logic;
		DATA_IN_P	    : in std_logic_vector(Number_of_ADCs-1 downto 0);
        DATA_IN_N       : in std_logic_vector(Number_of_ADCs-1 downto 0);
		Oversampling    : in  unsigned(15 downto 0);		
		ADC_set_offset  : in STD_LOGIC;
		ADC_data_raw  : out std_logic_vector(Number_of_ADCs*ADC_BITS-1 downto 0);
		ADC_converted  : out std_logic_vector(Number_of_ADCs*W_LENGTH-1 downto 0);
		calculated_value_valid : out std_logic_vector(Number_of_ADCs-1 downto 0);
        ADC_end_cnv       : out STD_LOGIC;  --'1' => ADC ist gesampelt und muss nur noch ausgelsen werden -> Steigende High-Flanke kann schalten ausloesen fuer FCS! Uebergang von "0" auf "1" gibt Freigabe fuer FCS!
     	ADC_USER_OFFSET_1  : in std_logic_vector(32-1 downto 0); --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
        CONVERSION_RATE_ADC     : in std_logic_vector(32-1 downto 0)
		);
end ADC_Module_v2_0;

architecture arch_imp of ADC_Module_v2_0 is

    signal DATA_IN : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal slv_spi_rx_data_16bit : std_logic_vector(4*ADC_BITS - 1 downto 0); --One vector for all ADCs --SW: Immer 4 anstatt  "Number_of_ADCs"
--    signal slv_calculated_voltage : std_logic_vector(Number_of_ADCs*16-1 downto 0);
    signal slv_calculated_value : std_logic_vector(Number_of_ADCs*W_LENGTH-1 downto 0);
    signal ResetTrigger_n : STD_LOGIC;
    signal clk_en : STD_LOGIC := '1';
    signal enable_spi : STD_LOGIC := '1';
	signal spi_clk : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal adc_data_valid : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal ADC_end_conversion : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal ADC_SS_N_spi : std_logic_vector(Number_of_ADCs-1 downto 0);

	-- component declaration
--    component IBUFDS
----	        generic(DIFF_TERM : boolean :=FALSE);
--            port (
--               O: out std_logic;
--                I: in std_logic
--            );
--    end component;
    
    component OBUFDS
        port (
            I: in std_logic;
            O: out std_logic;
            OB: out std_logic
        );
    end component;
	
	    -- component spi_master    
    component spi_master is
        generic(INPUT_CLK_FREQUENCY : integer := 200000000; -- Hz 
                SPI_CLK_FREQUENCY   : integer := 100000000; -- hz / value will be used to calculate the Reload-Value of the Clock divider
                PRE_DELAY           : integer := 1; -- 1 := 10 ns / DELAY BETWEEN CS TO ACTIVE AND DATA TRANSMISSION
                POST_DELAY          : integer := 0; -- 1 := 20 ns / DELAY BETWEEN END OF DATA TRANSMISSION AND CS TO DISABLE 
                CONV_DELAY          : integer := 0; -- us / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
                TRIGGER_ADC         : boolean := true;
                ADC_BITS            : integer := 16 -- WORDLENGTH
        );
        port(TX_DATA : in  STD_LOGIC_VECTOR(ADC_BITS - 1 downto 0); -- SENDWORD
             RX_DATA : out STD_LOGIC_VECTOR(ADC_BITS - 1 downto 0); -- RECEIVEDWORD
             CPHA    : in  STD_LOGIC;       -- Clock Phase
             CPOL    : in  STD_LOGIC;       -- Clock Polarity
             MOSI    : out STD_LOGIC;
             ADC_DATA_Valid  : out STD_LOGIC;
             ADC_END_CNV : out STD_LOGIC;
             TRIGGER_TRANSMISSION : in STD_LOGIC;
             MISO    : in  STD_LOGIC;
             SCLK    : out STD_LOGIC;
             SS_N    : out STD_LOGIC;
             BUSY    : out STD_LOGIC;
             ENABLE  : in  STD_LOGIC;
             RESET   : in  std_logic;
             --TX_Done  : out STD_LOGIC;
             CLOCK   : in  STD_LOGIC
        );
    end component spi_master;

    component ADC_RAW_TO_VALUE IS
	   generic(--CONVERSION_RATE_ADC : integer := 48; --SW:CASR = 0.000732398*2^16 = 48(dec) = 30(hex)-- STEPS_A_out1 <= to_unsigned(16#0030#, 16);
			   ADC_SET_USER_OFFSET : boolean := false --SW:If False (0), than the flag uses the measured value as offset. If True (1), than the flag uses the falue in ADC_USER_OFFSET.
			--   ADC_USER_OFFSET : integer := 32768 --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
	  );
      PORT(clk                               :   IN    std_logic;
           reset                             :   IN    std_logic;
           clk_enable                        :   IN    std_logic;
           ADC_IN                            :   IN    std_logic_vector(15 DOWNTO 0);  -- int16
           ADC_DATA_VALID                    :   IN    std_logic;
           ADC_SET_OFFSET                    :   IN    std_logic;
           ce_out                            :   OUT   std_logic;
           CALC_VALUE                        :   OUT   std_logic_vector(17 DOWNTO 0);  -- sfix18_En11
           CALC_VALUE_VALID                  :   OUT   std_logic;
           ADC_USER_OFFSET                   :   IN    std_logic_vector(32-1 downto 0); --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
           CONVERSION_RATE_ADC               :   IN    std_logic_vector(32-1 downto 0)
           );
    end component ADC_RAW_TO_VALUE;
    
begin

    ResetTrigger_n   <= not(Trigger_cnv);

-- Instantiation of the IBUFDS
GEN_IBUFDS: for I in 0 to Number_of_ADCs-1 generate
    instantiation_IBUFDS: IBUFDS
        generic map (DIFF_TERM=>TRUE)
        port map (
            O => DATA_IN(I),
            I => DATA_IN_P(I),
            IB => DATA_IN_N(I)
        );
end generate GEN_IBUFDS; 

-- Instantiation of the OBUFDS
GEN_OBUFDS: for I in 0 to Number_of_ADCs-1 generate
    instantiation_OBUFDS: OBUFDS
            port map (
                I => spi_clk(I),
                O => SCLK_spi_P(I),
                OB => SCLK_spi_N(I)
            );
end generate GEN_OBUFDS;   

-- Instantiation of the spi_master module
GEN_SPI: for I in 0 to Number_of_ADCs-1 generate
    instantiation_spi: spi_master
         generic map(INPUT_CLK_FREQUENCY => INPUT_CLK_FREQUENCY, -- Hz 
                     SPI_CLK_FREQUENCY => SPI_CLK_FREQUENCY, -- hz / value will be used to calculate the Reload-Value of the Clock divider
                     PRE_DELAY => PRE_DELAY, -- us / DELAY BETWEEN CS TO ACTIVE AND DATA TRANSMISSION
                     POST_DELAY => POST_DELAY, -- us / DELAY BETWEEN END OF DATA TRANSMISSION AND CS TO DISABLE 
                     CONV_DELAY => CONV_DELAY, -- us / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
                     TRIGGER_ADC => TRIGGER_ADC,
                     ADC_BITS => ADC_BITS
                     )
        port map(
             TX_DATA => x"0000",
             RX_DATA => slv_spi_rx_data_16bit((I+1)*ADC_BITS-1 downto I*ADC_BITS),
             CPHA    => '0',  -- datatransmission at the first edge -> falling edge (CPHA=0, CPOL=1)
             CPOL    => '1',  -- Clock IDLE HIGH
             MOSI    => open,
             MISO    => DATA_IN(I),
             SCLK    => spi_clk(I),       
             SS_N    => ADC_SS_N_spi(I),
			 ADC_DATA_Valid  =>  adc_data_valid(I),
             ADC_END_CNV     => ADC_end_conversion(I),
             TRIGGER_TRANSMISSION => Trigger_cnv,
             BUSY    => open,
             ENABLE  => enable_spi,
             RESET   => not(reset_n), 
             --TX_Done  
             CLOCK   => clk
        );
end generate GEN_SPI;

ADC_end_cnv <= ADC_end_conversion(0); 
SS_N_spi <= ADC_SS_N_spi(0); 


GEN_calc_value: for I in 0 to Number_of_ADCs-1 generate
    calc_value: ADC_RAW_TO_VALUE
         generic map(ADC_SET_USER_OFFSET => ADC_SET_USER_OFFSET_1					
          )
          port map(ADC_IN => slv_spi_rx_data_16bit((I+1)*ADC_BITS - 1 downto I*ADC_BITS),
                   ADC_DATA_VALID => adc_data_valid(I), 
                   CALC_VALUE   => slv_calculated_value((I+1)*W_LENGTH - 1 downto I*W_LENGTH),
                   clk => clk,
                   ADC_SET_OFFSET => ADC_set_offset,
                   reset => not(reset_n),
                   clk_enable => clk_en,
                   CALC_VALUE_VALID => calculated_value_valid(I),
                   ADC_USER_OFFSET => ADC_USER_OFFSET_1,  
                   CONVERSION_RATE_ADC => CONVERSION_RATE_ADC,                     
                   ce_out => open                         
          );
end generate GEN_calc_value;

ADC_data_raw <= slv_spi_rx_data_16bit;
ADC_converted <= slv_calculated_value;

end arch_imp;
