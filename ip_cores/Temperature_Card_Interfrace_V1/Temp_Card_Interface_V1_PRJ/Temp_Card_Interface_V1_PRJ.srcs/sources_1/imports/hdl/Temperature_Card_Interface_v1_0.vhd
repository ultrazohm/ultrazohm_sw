library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Temperature_Card_Interface_v1_0 is
	generic (
		-- Users to add parameters here
        SPI_clk_div			: INTEGER	:=  50 ;
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 9
	);
	port (
		-- Users to add ports here
        --LTC2983 1
        SPI_MOSI_1				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_1				: IN	 STD_LOGIC;	
		SPI_SCLK_1				: OUT	 STD_LOGIC;	
		SPI_SS_1				: OUT	 STD_LOGIC;
		LTC_Interrupt_1			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_1			: OUT	 STD_LOGIC;
		busy_1                  : OUT    STD_LOGIC;
		ready_1                 : OUT    STD_LOGIC;
		error_flag_1            : OUT    STD_LOGIC;
		
		--LTC2983 2
		SPI_MOSI_2				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_2				: IN	 STD_LOGIC;	
		SPI_SCLK_2				: OUT	 STD_LOGIC;	
		SPI_SS_2				: OUT	 STD_LOGIC;
		LTC_Interrupt_2			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_2			: OUT	 STD_LOGIC;
		busy_2                  : OUT    STD_LOGIC;
		ready_2                 : OUT    STD_LOGIC;
		error_flag_2            : OUT    STD_LOGIC;
		
		--LTC2983 3
		SPI_MOSI_3				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_3				: IN	 STD_LOGIC;	
		SPI_SCLK_3				: OUT	 STD_LOGIC;	
		SPI_SS_3				: OUT	 STD_LOGIC;
		LTC_Interrupt_3			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_3			: OUT	 STD_LOGIC;
		busy_3                  : OUT    STD_LOGIC;
		ready_3                 : OUT    STD_LOGIC;
		error_flag_3            : OUT    STD_LOGIC;

    -- Temperature_ports_out
        Temp_00_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);

        Temp_00_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);

        Temp_00_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
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
end Temperature_Card_Interface_v1_0;

architecture arch_imp of Temperature_Card_Interface_v1_0 is

	-- component declaration
	component Temperature_Card_Interface_v1_0_S00_AXI is
		generic (
	    SPI_clk_div         : integer   := 2;
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_ADDR_WIDTH	: integer	:= 9
		);
		port (
		--LTC2983 1
        SPI_MOSI_1				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_1				: IN	 STD_LOGIC;	
		SPI_SCLK_1				: OUT	 STD_LOGIC;	
		SPI_SS_1				: OUT	 STD_LOGIC;
		LTC_Interrupt_1			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_1			: OUT	 STD_LOGIC;
		busy_1                  : OUT    STD_LOGIC;
		ready_1                 : OUT    STD_LOGIC;
		error_flag_1            : OUT    STD_LOGIC;
		
		--LTC2983 2
		SPI_MOSI_2				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_2				: IN	 STD_LOGIC;	
		SPI_SCLK_2				: OUT	 STD_LOGIC;	
		SPI_SS_2				: OUT	 STD_LOGIC;
		LTC_Interrupt_2			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_2			: OUT	 STD_LOGIC;
		busy_2                  : OUT    STD_LOGIC;
		ready_2                 : OUT    STD_LOGIC;
		error_flag_2            : OUT    STD_LOGIC;
		
		--LTC2983 3
		SPI_MOSI_3				: OUT	 STD_LOGIC;					-- SPI-Port
		SPI_MISO_3				: IN	 STD_LOGIC;	
		SPI_SCLK_3				: OUT	 STD_LOGIC;	
		SPI_SS_3				: OUT	 STD_LOGIC;
		LTC_Interrupt_3			: IN	 STD_LOGIC;					--zusätzliche Steuersignale für den LTC2983
		LTC_resetn_3			: OUT	 STD_LOGIC;
		busy_3                  : OUT    STD_LOGIC;
		ready_3                 : OUT    STD_LOGIC;
		error_flag_3            : OUT    STD_LOGIC;
		
		-- Temperature_ports_out
        Temp_00_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_1       : OUT STD_LOGIC_VECTOR(31 downto 0);

        Temp_00_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_2       : OUT STD_LOGIC_VECTOR(31 downto 0);

        Temp_00_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_01_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_02_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_03_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_04_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_05_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_06_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_07_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_08_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_09_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_10_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_11_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_12_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_13_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_14_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_15_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_16_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_17_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_18_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
        Temp_19_out_LTC_3       : OUT STD_LOGIC_VECTOR(31 downto 0);
		
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
	end component Temperature_Card_Interface_v1_0_S00_AXI;

begin

-- Instantiation of Axi Bus Interface S00_AXI
Temperature_Card_Interface_v1_0_S00_AXI_inst : Temperature_Card_Interface_v1_0_S00_AXI
	generic map (
	    SPI_clk_div         => SPI_clk_div,
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
        SPI_MOSI_1        => SPI_MOSI_1,
		SPI_MISO_1        => SPI_MISO_1,
		SPI_SCLK_1        => SPI_SCLK_1,
		SPI_SS_1          => SPI_SS_1,
		LTC_Interrupt_1   => LTC_Interrupt_1,
		LTC_resetn_1      => LTC_resetn_1,
		busy_1            => busy_1,                 
		ready_1           => ready_1,
		error_flag_1      => error_flag_1,        
		SPI_MOSI_2        => SPI_MOSI_2,
		SPI_MISO_2        => SPI_MISO_2,
		SPI_SCLK_2        => SPI_SCLK_2,
		SPI_SS_2          => SPI_SS_2,
		LTC_Interrupt_2   => LTC_Interrupt_2,
		LTC_resetn_2      => LTC_resetn_2,
		busy_2            => busy_2,                  
		ready_2           => ready_2,
		error_flag_2      => error_flag_2,           
		SPI_MOSI_3        => SPI_MOSI_3,
		SPI_MISO_3        => SPI_MISO_3,
		SPI_SCLK_3        => SPI_SCLK_3,
		SPI_SS_3          => SPI_SS_3,
		LTC_Interrupt_3   => LTC_Interrupt_3,
		LTC_resetn_3      => LTC_resetn_3,
		busy_3            => busy_3,                
		ready_3           => ready_3,
		error_flag_3      => error_flag_3,           
		
		-- Temperature_ports_out
        Temp_00_out_LTC_1      => Temp_00_out_LTC_1,
        Temp_01_out_LTC_1      => Temp_01_out_LTC_1,
        Temp_02_out_LTC_1      => Temp_02_out_LTC_1,
        Temp_03_out_LTC_1      => Temp_03_out_LTC_1,
        Temp_04_out_LTC_1      => Temp_04_out_LTC_1,
        Temp_05_out_LTC_1      => Temp_05_out_LTC_1,
        Temp_06_out_LTC_1      => Temp_06_out_LTC_1,
        Temp_07_out_LTC_1      => Temp_07_out_LTC_1,
        Temp_08_out_LTC_1      => Temp_08_out_LTC_1,
        Temp_09_out_LTC_1      => Temp_09_out_LTC_1,
        Temp_10_out_LTC_1      => Temp_10_out_LTC_1,
        Temp_11_out_LTC_1      => Temp_11_out_LTC_1,
        Temp_12_out_LTC_1      => Temp_12_out_LTC_1,
        Temp_13_out_LTC_1      => Temp_13_out_LTC_1,
        Temp_14_out_LTC_1      => Temp_14_out_LTC_1,
        Temp_15_out_LTC_1      => Temp_15_out_LTC_1,
        Temp_16_out_LTC_1      => Temp_16_out_LTC_1,
        Temp_17_out_LTC_1      => Temp_17_out_LTC_1,
        Temp_18_out_LTC_1      => Temp_18_out_LTC_1,
        Temp_19_out_LTC_1      => Temp_19_out_LTC_1,

        Temp_00_out_LTC_2      => Temp_00_out_LTC_2,
        Temp_01_out_LTC_2      => Temp_01_out_LTC_2,
        Temp_02_out_LTC_2      => Temp_02_out_LTC_2,
        Temp_03_out_LTC_2      => Temp_03_out_LTC_2,
        Temp_04_out_LTC_2      => Temp_04_out_LTC_2,
        Temp_05_out_LTC_2      => Temp_05_out_LTC_2,
        Temp_06_out_LTC_2      => Temp_06_out_LTC_2,
        Temp_07_out_LTC_2      => Temp_07_out_LTC_2,
        Temp_08_out_LTC_2      => Temp_08_out_LTC_2,
        Temp_09_out_LTC_2      => Temp_09_out_LTC_2,
        Temp_10_out_LTC_2      => Temp_10_out_LTC_2,
        Temp_11_out_LTC_2      => Temp_11_out_LTC_2,
        Temp_12_out_LTC_2      => Temp_12_out_LTC_2,
        Temp_13_out_LTC_2      => Temp_13_out_LTC_2,
        Temp_14_out_LTC_2      => Temp_14_out_LTC_2,
        Temp_15_out_LTC_2      => Temp_15_out_LTC_2,
        Temp_16_out_LTC_2      => Temp_16_out_LTC_2,
        Temp_17_out_LTC_2      => Temp_17_out_LTC_2,
        Temp_18_out_LTC_2      => Temp_18_out_LTC_2,
        Temp_19_out_LTC_2      => Temp_19_out_LTC_2,

        Temp_00_out_LTC_3      => Temp_00_out_LTC_3,
        Temp_01_out_LTC_3      => Temp_01_out_LTC_3,
        Temp_02_out_LTC_3      => Temp_02_out_LTC_3,
        Temp_03_out_LTC_3      => Temp_03_out_LTC_3,
        Temp_04_out_LTC_3      => Temp_04_out_LTC_3,
        Temp_05_out_LTC_3      => Temp_05_out_LTC_3,
        Temp_06_out_LTC_3      => Temp_06_out_LTC_3,
        Temp_07_out_LTC_3      => Temp_07_out_LTC_3,
        Temp_08_out_LTC_3      => Temp_08_out_LTC_3,
        Temp_09_out_LTC_3      => Temp_09_out_LTC_3,
        Temp_10_out_LTC_3      => Temp_10_out_LTC_3,
        Temp_11_out_LTC_3      => Temp_11_out_LTC_3,
        Temp_12_out_LTC_3      => Temp_12_out_LTC_3,
        Temp_13_out_LTC_3      => Temp_13_out_LTC_3,
        Temp_14_out_LTC_3      => Temp_14_out_LTC_3,
        Temp_15_out_LTC_3      => Temp_15_out_LTC_3,
        Temp_16_out_LTC_3      => Temp_16_out_LTC_3,
        Temp_17_out_LTC_3      => Temp_17_out_LTC_3,
        Temp_18_out_LTC_3      => Temp_18_out_LTC_3,
        Temp_19_out_LTC_3      => Temp_19_out_LTC_3,
		
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

	-- User logic ends

end arch_imp;
