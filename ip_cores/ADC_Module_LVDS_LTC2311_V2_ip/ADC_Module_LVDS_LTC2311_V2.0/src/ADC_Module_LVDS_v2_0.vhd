-- -------------------------------------------------------------
-- Created: 2019-07-29 14:30:00
-- 
-- Author S. Wendel
-- 
-- 
-- -------------------------------------------------------------
-- Description
-- -------------------------------------------------------------
-- Top Level VHD-File and instantiation of the AXI-Slave Interface 
-- and the ADC_Block with the SPI-Master and Voltage, Current 
-- Calculation
-- -------------------------------------------------------------
-- Version 1.1
-- -------------------------------------------------------------
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ADC_Module_LVDS_v2_0 is
	generic (
		-- Users to add parameters here
		Number_of_ADCs          : integer := 1;
        INPUT_CLK_FREQUENCY     : integer := 100000000; -- Hz 
        SPI_CLK_FREQUENCY       : integer := 20000000; -- Hz / value will be used to calculate the Reload-Value of the Clock divider
        PRE_DELAY               : integer := 0; -- 0 := 10ns / DELAY BETWEEN CNV TO ACTIVE AND DATA TRANSMISSION
        -- Datasheet 9.5ns  => 0 := 10ns
        POST_DELAY              : integer := 0; -- 0 := 10ns / DELAY BETWEEN END OF DATA TRANSMISSION AND CNV TO DISABLE 
        -- Datasheet 19.1   => 1 := 20ns                       -- 1    
        CONV_DELAY              : integer := 0; -- 0 := 10ns / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
        -- Datasheet 25     => 2 := 30ns    
        TRIGGER_ADC             : boolean := true; -- 0 := Continous Mode; 1 := Triggered Mode
        Enable_Multiple_CLK     : boolean := false; -- 0 := Single Clock; 1 := Multiple Clock signals           
        ADC_BITS                : integer := 16; -- Number of ADC BITs
        W_LENGTH                : integer := 18; -- WORDLENGTH
      --  CONVERSION_RATE_ADC     : integer := 48; ---CASR = 0.000732398*2^16 = 48(dec) = 30(hex)-- STEPS_A_out1 <= to_unsigned(16#0030#, 16);
  		ADC_SET_USER_OFFSET_1   : boolean := false; --SW:If False (0), than the flag uses the measured value as offset. If True (1), than the flag uses the falue in ADC_USER_OFFSET.
		--ADC_USER_OFFSET_1       : integer := 32768; --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
		-- User parameters ends
		-- Do not modify the parameters beyond this line

		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 5
	);
	port (
		-- Users to add ports here
        clk              : in std_logic;
        reset_n          : in std_logic;
        Trigger_cnv      : in std_logic; --SW: Wenn Pin auf 1 geht, wird neue Wandlung angestoßen, ansonsten muss er immer auf Low (0) bleiben!
  		SCLK_spi_1_P	 : out std_logic;
        SCLK_spi_1_N     : out std_logic;
        SCLK_spi_2_P	 : out std_logic;
        SCLK_spi_2_N     : out std_logic;
        SCLK_spi_3_P	 : out std_logic;
        SCLK_spi_3_N     : out std_logic;
        SCLK_spi_4_P	 : out std_logic;
        SCLK_spi_4_N     : out std_logic;
        SS_N_spi         : out std_logic;
        DATA_IN_P        : in std_logic_vector(Number_of_ADCs-1 downto 0);
        DATA_IN_N        : in std_logic_vector(Number_of_ADCs-1 downto 0);
		OverSampling	 : in  unsigned(15 downto 0);
        ADC_SET_OFFSET   : in STD_LOGIC;
        ADC_data_raw_1   : out std_logic_vector(ADC_BITS - 1 downto 0);
        ADC_data_raw_2   : out std_logic_vector(ADC_BITS - 1 downto 0); 
        ADC_data_raw_3   : out std_logic_vector(ADC_BITS - 1 downto 0);
        ADC_data_raw_4   : out std_logic_vector(ADC_BITS - 1 downto 0);
        ADC_converted_1   : out std_logic_vector(W_LENGTH - 1 downto 0);
        ADC_converted_2   : out std_logic_vector(W_LENGTH - 1 downto 0);
        ADC_converted_3   : out std_logic_vector(W_LENGTH - 1 downto 0);
        ADC_converted_4   : out std_logic_vector(W_LENGTH - 1 downto 0);
--        calculated_value : out std_logic_vector(W_LENGTH*Number_of_ADCs-1 downto 0);
        calculated_value_valid : out std_logic_vector(Number_of_ADCs-1 downto 0);
        ADC_end_cnv      : out STD_LOGIC;  --'1' => ADC ist gesampelt und muss nur noch ausgelsen werden -> Steigende High-Flanke kann schalten ausloesen fuer FCS! Uebergang von "0" auf "1" gibt Freigabe fuer FCS!
		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S00_AXI
		s00_axi_aclk	: in std_logic;
		s00_axi_aresetn	: in std_logic;
		s00_axi_awaddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_awprot	: in std_logic_vector(2 downto 0);
		s00_axi_awvalid	: in std_logic;
		s00_axi_awready	: out std_logic;
		s00_axi_wdata	: in std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_wstrb	: in std_logic_vector((C_S00_AXI_DATA_WIDTH/8)-1 downto 0);
		s00_axi_wvalid	: in std_logic;
		s00_axi_wready	: out std_logic;
		s00_axi_bresp	: out std_logic_vector(1 downto 0);
		s00_axi_bvalid	: out std_logic;
		s00_axi_bready	: in std_logic;
		s00_axi_araddr	: in std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		s00_axi_arprot	: in std_logic_vector(2 downto 0);
		s00_axi_arvalid	: in std_logic;
		s00_axi_arready	: out std_logic;
		s00_axi_rdata	: out std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		s00_axi_rresp	: out std_logic_vector(1 downto 0);
		s00_axi_rvalid	: out std_logic;
		s00_axi_rready	: in std_logic
	);
end ADC_Module_LVDS_v2_0;

architecture arch_imp of ADC_Module_LVDS_v2_0 is

    signal ADC_data_raw     : std_logic_vector(Number_of_ADCs*ADC_BITS-1 downto 0);
    signal ADC_converted    : std_logic_vector(Number_of_ADCs*W_LENGTH-1 downto 0);
    signal SCLK_spi_P       : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal SCLK_spi_N       : std_logic_vector(Number_of_ADCs-1 downto 0);
    signal USER_REG0Out     : std_logic_vector(32-1 downto 0); --Conversion factor Current 1
    signal USER_REG1Out     : std_logic_vector(32-1 downto 0); --Conversion factor Current 2
    signal USER_REG0In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 1
    signal USER_REG1In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 2
    signal USER_REG2In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 3
    signal USER_REG3In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 4
    signal USER_REG4In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 5
    signal USER_REG5In      : std_logic_vector(32-1 downto 0); --RAW Value ADC 6 
	-- component declaration
	component ADC_Module_LVDS_v2_0_S00_AXI is
		generic (
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_ADDR_WIDTH	: integer	:= 5
		);
		port (
		USER_REG0       : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); --Conversion factor Current 1
        USER_REG1       : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); --Conversion factor Current 2
        USER_REG2       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 1
        USER_REG3       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 2
        USER_REG4       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 3 
        USER_REG5       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 4  
        USER_REG6       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 1
        USER_REG7       : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); -- DATA RAW Value 1     
		S_AXI_ACLK	    : in std_logic;
		S_AXI_ARESETN	: in std_logic;
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		S_AXI_AWVALID	: in std_logic;
		S_AXI_AWREADY	: out std_logic;
		S_AXI_WDATA	    : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_WSTRB	    : in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		S_AXI_WVALID	: in std_logic;
		S_AXI_WREADY	: out std_logic;
		S_AXI_BRESP	    : out std_logic_vector(1 downto 0);
		S_AXI_BVALID	: out std_logic;
		S_AXI_BREADY	: in std_logic;
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		S_AXI_ARVALID	: in std_logic;
		S_AXI_ARREADY	: out std_logic;
		S_AXI_RDATA	    : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_RRESP	    : out std_logic_vector(1 downto 0);
		S_AXI_RVALID	: out std_logic;
		S_AXI_RREADY	: in std_logic
		);
	end component ADC_Module_LVDS_v2_0_S00_AXI;
	
    component ADC_Module_v2_0 is
    generic (
        -- Users to add parameters here
		Number_of_ADCs          : integer := 1;
        INPUT_CLK_FREQUENCY     : integer := 100000000; -- Hz 
        SPI_CLK_FREQUENCY       : integer :=  25000000; -- Hz / value will be used to calculate the Reload-Value of the Clock divider
        PRE_DELAY               : integer := 0; -- 0 := 10ns / DELAY BETWEEN CNV TO ACTIVE AND DATA TRANSMISSION
        -- Datasheet 9.5ns  => 0 := 10ns
        POST_DELAY              : integer := 1; -- 0 := 10ns / DELAY BETWEEN END OF DATA TRANSMISSION AND CNV TO DISABLE 
        -- Datasheet 19.1ns  => 1 := 20ns                          
        CONV_DELAY              : integer := 2; -- 0 := 10ns / DELAY BETWEEN CS TO DISABLE AND CS TO ENABLE
        -- Datasheet 25ns    => 2 := 30ns    
        TRIGGER_ADC             : boolean := true; -- 0 := Continous Mode; 1 := Triggered Mode
        ADC_BITS                : integer := 16; -- Number of ADC BITs
        W_LENGTH                : integer := 18; -- WORDLENGTH
    --    CONVERSION_RATE_ADC     : integer := 48; ---CASR = 0.000732398*2^16 = 48(dec) = 30(hex)-- STEPS_A_out1 <= to_unsigned(16#0030#, 16);
  		ADC_SET_USER_OFFSET_1   : boolean := false --SW:If False (0), than the flag uses the measured value as offset. If True (1), than the flag uses the falue in ADC_USER_OFFSET.
	--	ADC_USER_OFFSET_1       : integer := 32768 --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
		-- User parameters ends
        -- Do not modify the parameters beyond this line 

        -- Parameters of Axi Slave Bus Interface S00_AXI
    );
    port (
        -- Users to add ports here
        clk                     : in std_logic;
        reset_n                 : in std_logic;
        Trigger_cnv             : in std_logic; --SW: Wenn Pin auf 1 geht, wird neue Wandlung angestoßen, ansonsten muss er immer auf Low (0) bleiben!
  		SCLK_spi_P	            : out std_logic_vector(Number_of_ADCs-1 downto 0);
        SCLK_spi_N              : out std_logic_vector(Number_of_ADCs-1 downto 0);
        SS_N_spi                : out std_logic;
        DATA_IN_P               : in std_logic_vector(Number_of_ADCs-1 downto 0);
        DATA_IN_N               : in std_logic_vector(Number_of_ADCs-1 downto 0);
		Oversampling	        : in  unsigned(ADC_BITS - 1 downto 0);
		ADC_SET_OFFSET          : in STD_LOGIC;
        ADC_data_raw            : out std_logic_vector(Number_of_ADCs*ADC_BITS-1 downto 0);
        ADC_converted           : out std_logic_vector(Number_of_ADCs*W_LENGTH-1 downto 0);
   --     calculated_value      : out std_logic_vector(W_LENGTH*Number_of_ADCs-1 downto 0);
        calculated_value_valid  : out std_logic_vector(Number_of_ADCs-1 downto 0);
        ADC_end_cnv             : out STD_LOGIC;  --'1' => ADC ist gesampelt und muss nur noch ausgelsen werden -> Steigende High-Flanke kann schalten ausloesen fuer FCS! Uebergang von "0" auf "1" gibt Freigabe fuer FCS!
 		ADC_USER_OFFSET_1       : in std_logic_vector(32-1 downto 0); --SW: ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
        CONVERSION_RATE_ADC     : in std_logic_vector(32-1 downto 0)
        );
    end component ADC_Module_v2_0;

begin

-- Instantiation of Axi Bus Interface S00_AXI
ADC_Module_LVDS_v2_0_S00_AXI_inst : ADC_Module_LVDS_v2_0_S00_AXI
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
	    USER_REG0 => USER_REG0Out,
        USER_REG1 => USER_REG1Out,
        USER_REG2 => USER_REG0In,
        USER_REG3 => USER_REG1In,
        USER_REG4 => USER_REG2In,
        USER_REG5 => USER_REG3In,
        USER_REG6 => USER_REG4In,
        USER_REG7 => USER_REG5In,
		S_AXI_ACLK	=> s00_axi_aclk,
		S_AXI_ARESETN	=> s00_axi_aresetn,
		S_AXI_AWADDR	=> s00_axi_awaddr,
		S_AXI_AWPROT	=> s00_axi_awprot,
		S_AXI_AWVALID	=> s00_axi_awvalid,
		S_AXI_AWREADY	=> s00_axi_awready,
		S_AXI_WDATA	=> s00_axi_wdata,
		S_AXI_WSTRB	=> s00_axi_wstrb,
		S_AXI_WVALID	=> s00_axi_wvalid,
		S_AXI_WREADY	=> s00_axi_wready,
		S_AXI_BRESP	=> s00_axi_bresp,
		S_AXI_BVALID	=> s00_axi_bvalid,
		S_AXI_BREADY	=> s00_axi_bready,
		S_AXI_ARADDR	=> s00_axi_araddr,
		S_AXI_ARPROT	=> s00_axi_arprot,
		S_AXI_ARVALID	=> s00_axi_arvalid,
		S_AXI_ARREADY	=> s00_axi_arready,
		S_AXI_RDATA	=> s00_axi_rdata,
		S_AXI_RRESP	=> s00_axi_rresp,
		S_AXI_RVALID	=> s00_axi_rvalid,
		S_AXI_RREADY	=> s00_axi_rready
	);

	-- Add user logic here
    DUT : ADC_Module_v2_0
     generic map(Number_of_ADCs => Number_of_ADCs,
                 INPUT_CLK_FREQUENCY => INPUT_CLK_FREQUENCY,  
                 SPI_CLK_FREQUENCY => SPI_CLK_FREQUENCY,
                 PRE_DELAY => PRE_DELAY, 
                 POST_DELAY => POST_DELAY, 
                 CONV_DELAY => CONV_DELAY, 
                 TRIGGER_ADC => TRIGGER_ADC,
                 ADC_BITS => ADC_BITS,
                 W_LENGTH => W_LENGTH,
                -- CONVERSION_RATE_ADC => CONVERSION_RATE_ADC,
			     ADC_SET_USER_OFFSET_1 => ADC_SET_USER_OFFSET_1
                 )
    port map(
               clk => clk,
               reset_n => reset_n,
               SCLK_spi_P   => SCLK_spi_P,
               SCLK_spi_N   => SCLK_spi_N,
               Trigger_cnv => Trigger_cnv,
               SS_N_spi => SS_N_spi,    
               DATA_IN_P => DATA_IN_P,
               DATA_IN_N => DATA_IN_N,			   
			   Oversampling => OverSampling,
               ADC_set_offset => ADC_SET_OFFSET,
               ADC_data_raw => ADC_data_raw, 
               ADC_converted => ADC_converted,             
               calculated_value_valid => calculated_value_valid,
               ADC_end_cnv  => ADC_end_cnv,
               ADC_USER_OFFSET_1 => USER_REG1Out,
               CONVERSION_RATE_ADC => USER_REG0Out
             );  
	-- User logic ends
--User definitions

--SW: Reallocate the ADC-RAW values in order to output from the IP Core 
ADC_data_raw_1 <= ADC_data_raw((0+1)*ADC_BITS - 1 downto 0*ADC_BITS); --erster ADC Wert
ADC_data_raw_2 <= ADC_data_raw((1+1)*ADC_BITS - 1 downto 1*ADC_BITS); --zweiter ADC Wert
ADC_data_raw_3 <= ADC_data_raw((2+1)*ADC_BITS - 1 downto 2*ADC_BITS); --dritter ADC Wert
ADC_data_raw_4 <= ADC_data_raw((3+1)*ADC_BITS - 1 downto 3*ADC_BITS);  --vierter ADC Wert
--    calculated_value <= slv_calculated_value;

--SW: Reallocate the converted and scaled ADC values values in order to output from the IP Core 
ADC_converted_1 <= ADC_converted((0+1)*W_LENGTH - 1 downto 0*W_LENGTH); --erster ADC Wert
ADC_converted_2 <= ADC_converted((1+1)*W_LENGTH - 1 downto 1*W_LENGTH); --zweiter ADC Wert
ADC_converted_3 <= ADC_converted((2+1)*W_LENGTH - 1 downto 2*W_LENGTH); --dritter ADC Wert
ADC_converted_4 <= ADC_converted((3+1)*W_LENGTH - 1 downto 3*W_LENGTH);  --vierter ADC Wert

--SW: Reallocate the Clock signals 
SCLK_spi_1_P <= SCLK_spi_P(0); --erster ADC Clock
SCLK_spi_2_P <= SCLK_spi_P(1); --zweiter ADC Clock
SCLK_spi_3_P <= SCLK_spi_P(2); --dritter ADC Clock
SCLK_spi_4_P <= SCLK_spi_P(3); --vierter ADC Clock
SCLK_spi_1_N <= SCLK_spi_N(0); --erster ADC Clock
SCLK_spi_2_N <= SCLK_spi_N(1); --zweiter ADC Clock
SCLK_spi_3_N <= SCLK_spi_N(2); --dritter ADC Clock
SCLK_spi_4_N <= SCLK_spi_N(3); --vierter ADC Clock
 
--SW: Reallocate the Ofset values
--ADC_USER_OFFSET_1 <=  unsigned(USER_REG1Out); --ADC_USER_OFFSET_1
--ADC_USER_OFFSET_1 <=  to_unsigned(USER_REG1Out, 16); --ADC_USER_OFFSET_1


USER_REG0In <= std_logic_vector(resize(signed(ADC_data_raw((0+1)*ADC_BITS - 1 downto 0*ADC_BITS)),32)); --erster ADC Wert
USER_REG1In <= std_logic_vector(resize(signed(ADC_data_raw((1+1)*ADC_BITS - 1 downto 1*ADC_BITS)),32)); --zweiter ADC Wert
USER_REG2In <= std_logic_vector(resize(signed(ADC_data_raw((2+1)*ADC_BITS - 1 downto 2*ADC_BITS)),32)); --dritter ADC Wert
USER_REG3In <= std_logic_vector(resize(signed(ADC_data_raw((3+1)*ADC_BITS - 1 downto 3*ADC_BITS)),32)); --vierter ADC Wert
USER_REG4In <= std_logic_vector(resize(to_signed(16#00010#, 18),32)); --fuenfter ADC Wert
USER_REG5In <= std_logic_vector(resize(to_signed(16#00020#, 18),32)); --sechster ADC Wert

end arch_imp;
