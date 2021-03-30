library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ADC_LVDS_LTC2311_v3_0 is
	generic (
		-- Users to add parameters here
		SPI_WIDTH             : integer   := 16;
		CHANNELS_PER_MASTER   : integer   := 4;
		SPI_MASTER            : integer   := 2;
		SI_WIDTH              : integer   := 18;
	            
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 4
	);
	port (
		-- Users to add ports here
		ADC_RAW          : out std_logic_vector(SPI_WIDTH * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
	    ADC_CONVERTED    : out std_logic_vector(SI_WIDTH * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
	    
	    -- SPI ports
	    SCLK_P           : out std_logic_vector(SPI_MASTER - 1 downto 0);
	    SCLK_N           : out std_logic_vector(SPI_MASTER - 1 downto 0);
	    MISO_P           : out std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
	    MISO_N           : out std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
	    SS_N             : out std_logic_vector(SPI_MASTER - 1 downto 0);
	    
	    -- Control ports
	    TRIGGER_CNV      : in std_logic;
	    ADC_FINISH       : out std_logic_vector(SPI_MASTER - 1 downto 0);
	    SI_FINISH        : out std_logic_vector(SPI_MASTER - 1 downto 0);

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
end ADC_LVDS_LTC2311_v3_0;

architecture arch_imp of ADC_LVDS_LTC2311_v3_0 is

    
-- settings with constants
constant CLOCK_PERIOD               : TIME := 10 ns;
constant TEST_DATA_WIDTH            : natural := 16;
constant TEST_CHANNELS              : natural := 2;
constant TEST_OFFSET_WIDTH          : natural := 16;
constant TEST_CONVERSION_WIDTH      : natural := 18;
constant TEST_DELAY_WIDTH           : natural := 8;
constant TEST_CLK_DIV_WIDTH         : natural := 16;
constant TEST_RES_MSB               : natural := 23;
constant TEST_RES_LSB               : natural := 6;
constant TEST_CLK_DIV               : natural := 0;
constant TEST_DELAY                 : natural := 1;

-- values
constant RAW_VALUE      : integer := 150;
constant OFFSET         : integer := 150;
constant CONVERSION     : integer := 10;

signal S_RX_DATA        : std_logic_vector((TEST_CHANNELS * TEST_DATA_WIDTH) - 1 downto 0) := (others => '0');
signal S_RESULT         : std_logic_vector((TEST_CHANNELS * (TEST_RES_MSB - TEST_RES_LSB + 1)) - 1 downto 0);
signal S_OFFSET         : std_logic_vector(TEST_OFFSET_WIDTH - 1 downto 0);
signal S_CONVERSION     : std_logic_vector(TEST_CONVERSION_WIDTH - 1 downto 0);
signal S_OFF_CONV       : std_logic_vector(31 downto 0);

signal S_CPHA, S_CPOL, S_SCLK, S_SS_OUT_N, S_SS_IN_N, S_BUSY : std_logic := '0';

signal S_MISO                           : std_logic_vector(TEST_CHANNELS - 1 downto 0) := (others => '0');
signal S_CLK_DIV                        : std_logic_vector(TEST_CLK_DIV_WIDTH - 1 downto 0);
signal S_PRE_DELAY, S_POST_DELAY        : std_logic_vector(TEST_DELAY_WIDTH - 1 downto 0);

-- control signals
signal S_SET_CONVERSION, S_SET_OFFSET, S_ENABLE, S_READ_DONE, S_SI_VALID, S_RAW_VALID : std_logic := '0';
signal S_CLK, S_RESET_N : std_logic := '0';
signal S_CHANNEL_SELECT : std_logic_vector(31 downto 0);

-- SPI slave simulation
constant DCNVSDOV : time := 5 ns;
constant HSDO     : time := 2 ns;
constant DSCKSDOV : time := 7400 ps;
constant PCB_DEL  : time := 1 ns;

signal S_TX_DATA : std_logic_vector(TEST_DATA_WIDTH - 1 downto 0) := (others => '0');
signal S_TX_BIT_COUNT : integer := TEST_DATA_WIDTH - 1;

	-- component declaration
	component ADC_LVDS_LTC2311_v3_0_S00_AXI is
		generic (
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_ADDR_WIDTH	: integer	:= 4
		);
		port (
		S_AXI_ACLK	: in std_logic;
		S_AXI_ARESETN	: in std_logic;
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		S_AXI_AWVALID	: in std_logic;
		S_AXI_AWREADY	: out std_logic;
		S_AXI_WDATA	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_WSTRB	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		S_AXI_WVALID	: in std_logic;
		S_AXI_WREADY	: out std_logic;
		S_AXI_BRESP	: out std_logic_vector(1 downto 0);
		S_AXI_BVALID	: out std_logic;
		S_AXI_BREADY	: in std_logic;
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		S_AXI_ARVALID	: in std_logic;
		S_AXI_ARREADY	: out std_logic;
		S_AXI_RDATA	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_RRESP	: out std_logic_vector(1 downto 0);
		S_AXI_RVALID	: out std_logic;
		S_AXI_RREADY	: in std_logic
		);
	end component ADC_LVDS_LTC2311_v3_0_S00_AXI;
	
	component ADC_CONTROLLER is
    generic(
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS            : natural := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23;    -- MSB in the result vector of the multiplactor output
        
        -- SPI
        DELAY_WIDTH         : natural := 8;     -- Bit width of the vector that contains pre and post delay
                                                -- a.k.a. delay from SS_N -> low to first SCLK cycle and last before SS_N -> high
        CLK_DIV_WIDTH       : natural := 16     -- Bit width of the vector that contains pre and post clock devider
    );
    port (
        CLK         : in std_logic;
        RESET_N     : in std_logic;
        
        -- SPI ports
        CPHA        : in std_logic;
        CPOL        : in std_logic;
        SCLK        : out std_logic;
        MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
        SS_OUT_N    : out std_logic;
        SS_IN_N     : in std_logic;
        ENABLE      : in std_logic;
        
        -- SPI config ports
        PRE_DELAY   : in std_logic_vector(DELAY_WIDTH - 1 downto 0);
        POST_DELAY  : in std_logic_vector(DELAY_WIDTH - 1 downto 0);
        CLK_DIV     : in std_logic_vector(CLK_DIV_WIDTH - 1 downto 0);
        
        -- Control Ports
        SET_CONVERSION  : in std_logic;
        SET_OFFSET      : in std_logic;
        READ_DONE       : out std_logic;
        SI_VALID        : out std_logic;
        RAW_VALID       : out std_logic;
        BUSY            : out std_logic;
        
        -- Value Ports
        VALUE_OFF_CONV  : in std_logic_vector(31 downto 0);           -- input for conversion or offset value
        CHANNEL_SELECT  : in std_logic_vector(31 downto 0); -- selection which channels shall be updated with conversion factor or offset
        SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
        RAW_VALUE       : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0)
        
    );
    end component ADC_CONTROLLER;

begin

-- Instantiation of Axi Bus Interface S00_AXI
ADC_LVDS_LTC2311_v3_0_S00_AXI_inst : ADC_LVDS_LTC2311_v3_0_S00_AXI
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
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
	
	dut: ADC_CONTROLLER
    generic map(
        DATA_WIDTH          => TEST_DATA_WIDTH,         -- Number of bits per SPI frame
        CHANNELS            => TEST_CHANNELS,           -- Number of slaves that are controlled with the same SS_N and SCLK
        OFFSET_WIDTH        => TEST_OFFSET_WIDTH,       -- Bit width of the offset value
        CONVERSION_WIDTH    => TEST_CONVERSION_WIDTH,   -- Bit width of the conversion factor
        RES_LSB             => TEST_RES_LSB,            -- LSB in the result vector of the multiplactor output
        RES_MSB             => TEST_RES_MSB,            -- MSB in the result vector of the multiplactor output
        
        -- SPI
        DELAY_WIDTH         => TEST_DELAY_WIDTH,        -- Bit width of the vector that contains pre and post delay
                                                        -- a.k.a. delay from SS_N -> low to first SCLK cycle and last before SS_N -> high
        CLK_DIV_WIDTH       => TEST_CLK_DIV_WIDTH       -- Bit width of the vector that contains pre and post clock devider
    )
    port map(
        CLK                 => S_CLK,
        RESET_N             => S_RESET_N,
        
        -- SPI ports
        CPHA                => S_CPHA,
        CPOL                => S_CPOL,
        SCLK                => S_SCLK,
        MISO                => S_MISO,
        SS_OUT_N            => S_SS_OUT_N,
        SS_IN_N             => S_SS_IN_N,
        ENABLE              => S_ENABLE,
        
        -- SPI config ports
        PRE_DELAY           => S_PRE_DELAY,
        POST_DELAY          => S_POST_DELAY,
        CLK_DIV             => S_CLK_DIV,
        
        -- Control Ports
        SET_CONVERSION      => S_SET_CONVERSION,
        SET_OFFSET          => S_SET_OFFSET,
        READ_DONE           => S_READ_DONE,
        SI_VALID            => S_SI_VALID,
        RAW_VALID           => S_RAW_VALID,
        BUSY                => S_BUSY,
        
        -- Value Ports
        VALUE_OFF_CONV      => S_OFF_CONV,
        CHANNEL_SELECT      => S_CHANNEL_SELECT,
        SI_VALUE            => S_RESULT,
        RAW_VALUE           => S_RX_DATA
        
    );
	
	-- User logic ends

end arch_imp;

configuration conf_adc of ADC_LVDS_LTC2311_v3_0 is
    for arch_imp
    
        for dut : ADC_CONTROLLER use entity work.ADC_CONTROLLER(Behavioral);
        end for;
    end for;
end configuration conf_adc;
