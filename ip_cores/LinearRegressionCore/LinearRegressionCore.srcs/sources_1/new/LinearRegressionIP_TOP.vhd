----------------------------------------------------------------------------------
-- Company:     Univeristät Kassel - Elektrische Maschinen und Antriebe
-- Engineer:    Robert Zipprich
-- 
-- Create Date: 02.02.2023 11:12:33
-- Design Name: LinearRegressionIP
-- Module Name: LinearRegressionIP - Behavioral
-- Project Name: Diss
-- Target Devices: UZ
-- Tool Versions: 2020.1
-- Description: AWESOME
-- 
-- Dependencies: Nope
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments: 
--      Core computes the linear Regression of the given Signal with a fixed Number of Tabs
--      it will solve the equation  y = alpha_1 * x + alpha_0, where y is the calculated linear Regression, x ist the number of the last Tab and alpha_1/alpha_0 are factors, which 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity LinearRegressionIP_TOP is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 20;
    Fracbits    : integer := 16;
    Channels    : integer := 4;
    --S_AXI data bus generics
	C_S_AXI_DATA_WIDTH	: integer	:= 32;
	C_S_AXI_ADDR_WIDTH	: integer	:= 6
);
Port(
    clk             : in    std_logic;
    rst_n           : in    std_logic;
    Trigger_Calc    : in    std_logic;
    Data_in         : in    std_logic_vector((Channels*DataWidth)-1 downto 0);
    Alpha_0_out     : out   std_logic_vector((Channels*DataWidth)-1 downto 0);
    Alpha_1_out     : out   std_logic_vector((Channels*DataWidth)-1 downto 0);
    Data_out        : out   std_logic_vector((Channels*DataWidth)-1 downto 0);
    Data_valid      : out   std_logic;
    -- AXI-Bus
    S_AXI_ACLK      : in std_logic;
    S_AXI_ARESETN   : in std_logic;
    S_AXI_AWADDR    : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
    S_AXI_AWPROT    : in std_logic_vector(2 downto 0);
    S_AXI_AWVALID   : in std_logic;
    S_AXI_AWREADY   : out std_logic;
    S_AXI_WDATA     : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); 
    S_AXI_WSTRB	    : in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
    S_AXI_WVALID    : in std_logic;
    S_AXI_WREADY    : out std_logic;
    S_AXI_BRESP     : out std_logic_vector(1 downto 0);
    S_AXI_BVALID    : out std_logic;
    S_AXI_BREADY    : in std_logic;
    S_AXI_ARADDR    : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
    S_AXI_ARPROT    : in std_logic_vector(2 downto 0);
    S_AXI_ARVALID   : in std_logic;
    S_AXI_ARREADY   : out std_logic;
    S_AXI_RDATA     : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
    S_AXI_RRESP     : out std_logic_vector(1 downto 0);
    S_AXI_RVALID    : out std_logic;
    S_AXI_RREADY    : in std_logic
);
end LinearRegressionIP_TOP;

architecture Behavioral of LinearRegressionIP_TOP is

signal Data_out_LR_Calcer_s : std_logic_vector(DataWidth-1 downto 0);

component AXI_Interface_v1_0_S00_AXI is
	generic (
		-- Width of S_AXI data bus
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		-- Width of S_AXI address bus
		C_S_AXI_ADDR_WIDTH	: integer	:= 6
	);
	port (
		S_AXI_ACLK    : in std_logic;
		S_AXI_ARESETN : in std_logic;
		S_AXI_AWADDR  : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_AWPROT  : in std_logic_vector(2 downto 0);
		S_AXI_AWVALID : in std_logic;
		S_AXI_AWREADY : out std_logic;
		S_AXI_WDATA   : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0); 
		S_AXI_WSTRB	  : in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		S_AXI_WVALID  : in std_logic;
		S_AXI_WREADY  : out std_logic;
		S_AXI_BRESP   : out std_logic_vector(1 downto 0);
		S_AXI_BVALID  : out std_logic;
		S_AXI_BREADY  : in std_logic;
		S_AXI_ARADDR  : in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_ARPROT  : in std_logic_vector(2 downto 0);
		S_AXI_ARVALID : in std_logic;
		S_AXI_ARREADY : out std_logic;
		S_AXI_RDATA   : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_RRESP   : out std_logic_vector(1 downto 0);
		S_AXI_RVALID  : out std_logic;
		S_AXI_RREADY  : in std_logic;
		-- exposed Regs
		slv_reg_00_o  : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0)
	);
end component AXI_Interface_v1_0_S00_AXI;

component Valid_Generator is
Generic(
    Wait_Cycles	    : integer	:= 11
);
Port (
    clk             : in    std_logic;
    rst_n           : in    std_logic;
    Trigger_Calc    : in    std_logic;
    Data_valid      : out   std_logic
);
end component Valid_Generator;

component LinearRegressionIP is
Generic(
    DataWidth   : integer := 32;
    Tabs        : integer := 50;
    Fracbits    : integer := 16
);
Port(
    clk             : in    std_logic;
    rst_n           : in    std_logic;
    Trigger_Calc    : in    std_logic;
    Calc_enable     : in    std_logic;
    Data_in         : in    std_logic_vector(DataWidth-1 downto 0);
    Alpha_0_out     : out   std_logic_vector(DataWidth-1 downto 0);
    Alpha_1_out     : out   std_logic_vector(DataWidth-1 downto 0);
    Data_out        : out   std_logic_vector(DataWidth-1 downto 0)
);
end component LinearRegressionIP;

-- Signals
signal slv_reg_00_s     : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);

signal Data_out_vec     : std_logic_vector((Channels*DataWidth)-1 downto 0);
signal Alpha_0_out_vec  : std_logic_vector((Channels*DataWidth)-1 downto 0);
signal Alpha_1_out_vec  : std_logic_vector((Channels*DataWidth)-1 downto 0);

begin

AXI_Interface : AXI_Interface_v1_0_S00_AXI
Generic map(
    C_S_AXI_DATA_WIDTH =>  C_S_AXI_DATA_WIDTH,
    C_S_AXI_ADDR_WIDTH => C_S_AXI_ADDR_WIDTH
)
Port map(
    S_AXI_ACLK    => S_AXI_ACLK     ,
    S_AXI_ARESETN => S_AXI_ARESETN  ,
    S_AXI_AWADDR  => S_AXI_AWADDR   ,
    S_AXI_AWPROT  => S_AXI_AWPROT   ,
    S_AXI_AWVALID => S_AXI_AWVALID  ,
    S_AXI_AWREADY => S_AXI_AWREADY  ,
    S_AXI_WDATA   => S_AXI_WDATA    ,
    S_AXI_WSTRB	  => S_AXI_WSTRB    ,
    S_AXI_WVALID  => S_AXI_WVALID   ,
    S_AXI_WREADY  => S_AXI_WREADY   ,
    S_AXI_BRESP   => S_AXI_BRESP    ,
    S_AXI_BVALID  => S_AXI_BVALID   ,
    S_AXI_BREADY  => S_AXI_BREADY   ,
    S_AXI_ARADDR  => S_AXI_ARADDR   ,
    S_AXI_ARPROT  => S_AXI_ARPROT   ,
    S_AXI_ARVALID => S_AXI_ARVALID  ,
    S_AXI_ARREADY => S_AXI_ARREADY  ,
    S_AXI_RDATA   => S_AXI_RDATA    ,
    S_AXI_RRESP   => S_AXI_RRESP    ,
    S_AXI_RVALID  => S_AXI_RVALID   ,
    S_AXI_RREADY  => S_AXI_RREADY   ,
    -- exposed Regs
    slv_reg_00_o  => slv_reg_00_s
);

GenerateCannel: for i in 1 to Channels generate
    LR_IP : LinearRegressionIP
    Generic map(
        DataWidth   => DataWidth,
        Tabs        => Tabs     ,
        Fracbits    => Fracbits 
    )
    Port map(
        clk            => clk          ,
        rst_n          => rst_n        ,
        Trigger_Calc   => Trigger_Calc ,
        Calc_enable    => slv_reg_00_s(i),
        Data_in        => Data_in((DataWidth*(i))-1 downto (DataWidth)*(i-1))      ,
        Alpha_0_out    => Alpha_0_out_vec((DataWidth*(i))-1 downto (DataWidth)*(i-1)),
        Alpha_1_out    => Alpha_1_out_vec((DataWidth*(i))-1 downto (DataWidth)*(i-1)),
        Data_out       => Data_out_vec((DataWidth*(i))-1 downto (DataWidth)*(i-1))     
    );
end generate;

Valid_Gen:Valid_Generator
Port map (
    clk                 => clk,
    rst_n               => rst_n,
    Trigger_Calc        => Trigger_Calc,
    Data_valid          => Data_valid
);

-- Mapping
 Alpha_0_out    <= Alpha_0_out_vec; 
 Alpha_1_out    <= Alpha_1_out_vec; 
 Data_out       <= Data_out_vec; 

end Behavioral;
