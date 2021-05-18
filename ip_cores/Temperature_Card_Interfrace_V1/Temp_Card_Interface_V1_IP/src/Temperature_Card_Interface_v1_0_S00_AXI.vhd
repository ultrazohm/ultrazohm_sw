library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Temperature_Card_Interface_v1_0_S00_AXI is
	generic (
		-- Users to add parameters here

		-- User parameters ends
		-- Do not modify the parameters beyond this line

		-- Width of S_AXI data bus
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		-- Width of S_AXI address bus
		C_S_AXI_ADDR_WIDTH	: integer	:= 9
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

		-- Global Clock Signal
		S_AXI_ACLK	: in std_logic;
		-- Global Reset Signal. This Signal is Active LOW
		S_AXI_ARESETN	: in std_logic;
		-- Write address (issued by master, acceped by Slave)
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		-- Write channel Protection type. This signal indicates the
    		-- privilege and security level of the transaction, and whether
    		-- the transaction is a data access or an instruction access.
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		-- Write address valid. This signal indicates that the master signaling
    		-- valid write address and control information.
		S_AXI_AWVALID	: in std_logic;
		-- Write address ready. This signal indicates that the slave is ready
    		-- to accept an address and associated control signals.
		S_AXI_AWREADY	: out std_logic;
		-- Write data (issued by master, acceped by Slave) 
		S_AXI_WDATA	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		-- Write strobes. This signal indicates which byte lanes hold
    		-- valid data. There is one write strobe bit for each eight
    		-- bits of the write data bus.    
		S_AXI_WSTRB	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		-- Write valid. This signal indicates that valid write
    		-- data and strobes are available.
		S_AXI_WVALID	: in std_logic;
		-- Write ready. This signal indicates that the slave
    		-- can accept the write data.
		S_AXI_WREADY	: out std_logic;
		-- Write response. This signal indicates the status
    		-- of the write transaction.
		S_AXI_BRESP	: out std_logic_vector(1 downto 0);
		-- Write response valid. This signal indicates that the channel
    		-- is signaling a valid write response.
		S_AXI_BVALID	: out std_logic;
		-- Response ready. This signal indicates that the master
    		-- can accept a write response.
		S_AXI_BREADY	: in std_logic;
		-- Read address (issued by master, acceped by Slave)
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		-- Protection type. This signal indicates the privilege
    		-- and security level of the transaction, and whether the
    		-- transaction is a data access or an instruction access.
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		-- Read address valid. This signal indicates that the channel
    		-- is signaling valid read address and control information.
		S_AXI_ARVALID	: in std_logic;
		-- Read address ready. This signal indicates that the slave is
    		-- ready to accept an address and associated control signals.
		S_AXI_ARREADY	: out std_logic;
		-- Read data (issued by slave)
		S_AXI_RDATA	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		-- Read response. This signal indicates the status of the
    		-- read transfer.
		S_AXI_RRESP	: out std_logic_vector(1 downto 0);
		-- Read valid. This signal indicates that the channel is
    		-- signaling the required read data.
		S_AXI_RVALID	: out std_logic;
		-- Read ready. This signal indicates that the master can
    		-- accept the read data and response information.
		S_AXI_RREADY	: in std_logic
	);
end Temperature_Card_Interface_v1_0_S00_AXI;

architecture arch_imp of Temperature_Card_Interface_v1_0_S00_AXI is

	-- AXI4LITE signals
	signal axi_awaddr	: std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
	signal axi_awready	: std_logic;
	signal axi_wready	: std_logic;
	signal axi_bresp	: std_logic_vector(1 downto 0);
	signal axi_bvalid	: std_logic;
	signal axi_araddr	: std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
	signal axi_arready	: std_logic;
	signal axi_rdata	: std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal axi_rresp	: std_logic_vector(1 downto 0);
	signal axi_rvalid	: std_logic;

	-- Example-specific design signals
	-- local parameter for addressing 32 bit / 64 bit C_S_AXI_DATA_WIDTH
	-- ADDR_LSB is used for addressing 32/64 bit registers/memories
	-- ADDR_LSB = 2 for 32 bits (n downto 2)
	-- ADDR_LSB = 3 for 64 bits (n downto 3)
	constant ADDR_LSB  : integer := (C_S_AXI_DATA_WIDTH/32)+ 1;
	constant OPT_MEM_ADDR_BITS : integer := 6;
	------------------------------------------------
	---- Signals for user logic register space example
	--------------------------------------------------
	---- Number of Slave Registers 128
	signal slv_reg0	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg1	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg2	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg3	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg4	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg5	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg6	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg7	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg8	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg9	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg10	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg11	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg12	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg13	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg14	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg15	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg16	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg17	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg18	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg19	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg20	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg21	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg22	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg23	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg24	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg25	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg26	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg27	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg28	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg29	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg30	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg31	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg32	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg33	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg34	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg35	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg36	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg37	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg38	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg39	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg40	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg41	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg42	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg43	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg44	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg45	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg46	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg47	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg48	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg49	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg50	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg51	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg52	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg53	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg54	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg55	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg56	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg57	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg58	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg59	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg60	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg61	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg62	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg63	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg64	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg65	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg66	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg67	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg68	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg69	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg70	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg71	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg72	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg73	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg74	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg75	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg76	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg77	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg78	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg79	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg80	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg81	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg82	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg83	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg84	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg85	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg86	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg87	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg88	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg89	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg90	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg91	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg92	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg93	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg94	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg95	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg96	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg97	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg98	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg99	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg100	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg101	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg102	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg103	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg104	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg105	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg106	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg107	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg108	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg109	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg110	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg111	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg112	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg113	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg114	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg115	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg116	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg117	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg118	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg119	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg120	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg121	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg122	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg123	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg124	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg125	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg126	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg127	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal slv_reg_rden	: std_logic;
	signal slv_reg_wren	: std_logic;
	signal reg_data_out	:std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
	signal byte_index	: integer;
	signal aw_en	: std_logic;
	
	--Signals to map the compoents--------------------------------------------------------
	signal enable  				: STD_LOGIC;                    --System enable
    signal go_sig				: STD_LOGIC;					--global Trigger
    signal handlerreset         : STD_LOGIC;
    
    signal busy_1_s		        : STD_LOGIC;
    signal busy_2_s		        : STD_LOGIC;
    signal busy_3_s		        : STD_LOGIC;
    signal ready_1_s		    : STD_LOGIC;
    signal ready_2_s		    : STD_LOGIC;
    signal ready_3_s		    : STD_LOGIC;
    signal error_flag_1_s		: STD_LOGIC;					--Error occured, need reset
    signal error_flag_2_s		: STD_LOGIC;					--Error occured, need reset
    signal error_flag_3_s		: STD_LOGIC;					--Error occured, need reset
    
    signal Temp_00_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_01_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_02_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_03_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_04_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_05_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_06_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_07_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_08_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_09_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_10_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_11_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_12_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_13_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_14_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_15_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_16_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_17_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_18_out_LTC_1_s    : std_logic_vector(31 downto 0);				
    signal Temp_19_out_LTC_1_s    : std_logic_vector(31 downto 0);
    
    signal Temp_00_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_01_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_02_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_03_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_04_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_05_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_06_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_07_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_08_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_09_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_10_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_11_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_12_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_13_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_14_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_15_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_16_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_17_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_18_out_LTC_2_s    : std_logic_vector(31 downto 0);				
    signal Temp_19_out_LTC_2_s    : std_logic_vector(31 downto 0);
    
    signal Temp_00_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_01_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_02_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_03_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_04_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_05_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_06_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_07_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_08_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_09_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_10_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_11_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_12_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_13_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_14_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_15_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_16_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_17_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_18_out_LTC_3_s    : std_logic_vector(31 downto 0);				
    signal Temp_19_out_LTC_3_s    : std_logic_vector(31 downto 0);				
		
    
    -- Counter-------------------------------------------------------------------
    signal GO_sig_counter       : unsigned(31 downto 0);
    
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
		LTC_CH_19_config_in		: IN  std_logic_vector(31 DOWNTO 0)
	);
end component LTC2983_Interface;


begin
	-- I/O Connections assignments

	S_AXI_AWREADY	<= axi_awready;
	S_AXI_WREADY	<= axi_wready;
	S_AXI_BRESP	<= axi_bresp;
	S_AXI_BVALID	<= axi_bvalid;
	S_AXI_ARREADY	<= axi_arready;
	S_AXI_RDATA	<= axi_rdata;
	S_AXI_RRESP	<= axi_rresp;
	S_AXI_RVALID	<= axi_rvalid;
	-- Implement axi_awready generation
	-- axi_awready is asserted for one S_AXI_ACLK clock cycle when both
	-- S_AXI_AWVALID and S_AXI_WVALID are asserted. axi_awready is
	-- de-asserted when reset is low.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_awready <= '0';
	      aw_en <= '1';
	    else
	      if (axi_awready = '0' and S_AXI_AWVALID = '1' and S_AXI_WVALID = '1' and aw_en = '1') then
	        -- slave is ready to accept write address when
	        -- there is a valid write address and write data
	        -- on the write address and data bus. This design 
	        -- expects no outstanding transactions. 
	           axi_awready <= '1';
	           aw_en <= '0';
	        elsif (S_AXI_BREADY = '1' and axi_bvalid = '1') then
	           aw_en <= '1';
	           axi_awready <= '0';
	      else
	        axi_awready <= '0';
	      end if;
	    end if;
	  end if;
	end process;

	-- Implement axi_awaddr latching
	-- This process is used to latch the address when both 
	-- S_AXI_AWVALID and S_AXI_WVALID are valid. 

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_awaddr <= (others => '0');
	    else
	      if (axi_awready = '0' and S_AXI_AWVALID = '1' and S_AXI_WVALID = '1' and aw_en = '1') then
	        -- Write Address latching
	        axi_awaddr <= S_AXI_AWADDR;
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_wready generation
	-- axi_wready is asserted for one S_AXI_ACLK clock cycle when both
	-- S_AXI_AWVALID and S_AXI_WVALID are asserted. axi_wready is 
	-- de-asserted when reset is low. 

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_wready <= '0';
	    else
	      if (axi_wready = '0' and S_AXI_WVALID = '1' and S_AXI_AWVALID = '1' and aw_en = '1') then
	          -- slave is ready to accept write data when 
	          -- there is a valid write address and write data
	          -- on the write address and data bus. This design 
	          -- expects no outstanding transactions.           
	          axi_wready <= '1';
	      else
	        axi_wready <= '0';
	      end if;
	    end if;
	  end if;
	end process; 

	-- Implement memory mapped register select and write logic generation
	-- The write data is accepted and written to memory mapped registers when
	-- axi_awready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted. Write strobes are used to
	-- select byte enables of slave registers while writing.
	-- These registers are cleared when reset (active low) is applied.
	-- Slave register write enable is asserted when valid address and data are available
	-- and the slave is ready to accept the write address and write data.
	slv_reg_wren <= axi_wready and S_AXI_WVALID and axi_awready and S_AXI_AWVALID ;

	process (S_AXI_ACLK)
	variable loc_addr :std_logic_vector(OPT_MEM_ADDR_BITS downto 0); 
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      slv_reg0 <= (others => '0');
	      slv_reg1 <= (others => '0');
	      slv_reg2 <= (others => '0');
	      slv_reg3 <= (others => '0');
	      slv_reg4 <= (others => '0');
	      slv_reg5 <= (others => '0');
	      slv_reg6 <= (others => '0');
	      slv_reg7 <= (others => '0');
	      slv_reg8 <= (others => '0');
	      slv_reg9 <= (others => '0');
	      slv_reg10 <= (others => '0');
	      slv_reg11 <= (others => '0');
	      slv_reg12 <= (others => '0');
	      slv_reg13 <= (others => '0');
	      slv_reg14 <= (others => '0');
	      slv_reg15 <= (others => '0');
	      slv_reg16 <= (others => '0');
	      slv_reg17 <= (others => '0');
	      slv_reg18 <= (others => '0');
	      slv_reg19 <= (others => '0');
	      slv_reg20 <= (others => '0');
	      slv_reg21 <= (others => '0');
	      slv_reg22 <= (others => '0');
	      slv_reg23 <= (others => '0');
	      slv_reg24 <= (others => '0');
	      slv_reg25 <= (others => '0');
	      slv_reg26 <= (others => '0');
	      slv_reg27 <= (others => '0');
	      slv_reg28 <= (others => '0');
	      slv_reg29 <= (others => '0');
	      slv_reg30 <= (others => '0');
	      slv_reg31 <= (others => '0');
	      slv_reg32 <= (others => '0');
	      slv_reg33 <= (others => '0');
	      slv_reg34 <= (others => '0');
	      slv_reg35 <= (others => '0');
	      slv_reg36 <= (others => '0');
	      slv_reg37 <= (others => '0');
	      slv_reg38 <= (others => '0');
	      slv_reg39 <= (others => '0');
	      slv_reg40 <= (others => '0');
	      slv_reg41 <= (others => '0');
	      slv_reg42 <= (others => '0');
	      slv_reg43 <= (others => '0');
	      slv_reg44 <= (others => '0');
	      slv_reg45 <= (others => '0');
	      slv_reg46 <= (others => '0');
	      slv_reg47 <= (others => '0');
	      slv_reg48 <= (others => '0');
	      slv_reg49 <= (others => '0');
	      slv_reg50 <= (others => '0');
	      slv_reg51 <= (others => '0');
	      slv_reg52 <= (others => '0');
	      slv_reg53 <= (others => '0');
	      slv_reg54 <= (others => '0');
	      slv_reg55 <= (others => '0');
	      slv_reg56 <= (others => '0');
	      slv_reg57 <= (others => '0');
	      slv_reg58 <= (others => '0');
	      slv_reg59 <= (others => '0');
	      slv_reg60 <= (others => '0');
	      slv_reg61 <= (others => '0');
	      slv_reg62 <= (others => '0');
	      slv_reg63 <= (others => '0');
	      slv_reg64 <= (others => '0');
	      slv_reg65 <= (others => '0');
	      slv_reg66 <= (others => '0');
	      slv_reg67 <= (others => '0');
	      slv_reg68 <= (others => '0');
	      slv_reg69 <= (others => '0');
	      slv_reg70 <= (others => '0');
	      slv_reg71 <= (others => '0');
	      slv_reg72 <= (others => '0');
	      slv_reg73 <= (others => '0');
	      slv_reg74 <= (others => '0');
	      slv_reg75 <= (others => '0');
	      slv_reg76 <= (others => '0');
	      slv_reg77 <= (others => '0');
	      slv_reg78 <= (others => '0');
	      slv_reg79 <= (others => '0');
	      slv_reg80 <= (others => '0');
	      slv_reg81 <= (others => '0');
	      slv_reg82 <= (others => '0');
	      slv_reg83 <= (others => '0');
	      slv_reg84 <= (others => '0');
	      slv_reg85 <= (others => '0');
	      slv_reg86 <= (others => '0');
	      slv_reg87 <= (others => '0');
	      slv_reg88 <= (others => '0');
	      slv_reg89 <= (others => '0');
	      slv_reg90 <= (others => '0');
	      slv_reg91 <= (others => '0');
	      slv_reg92 <= (others => '0');
	      slv_reg93 <= (others => '0');
	      slv_reg94 <= (others => '0');
	      slv_reg95 <= (others => '0');
	      slv_reg96 <= (others => '0');
	      slv_reg97 <= (others => '0');
	      slv_reg98 <= (others => '0');
	      slv_reg99 <= (others => '0');
	      slv_reg100 <= (others => '0');
	      slv_reg101 <= (others => '0');
	      slv_reg102 <= (others => '0');
	      slv_reg103 <= (others => '0');
	      slv_reg104 <= (others => '0');
	      slv_reg105 <= (others => '0');
	      slv_reg106 <= (others => '0');
	      slv_reg107 <= (others => '0');
	      slv_reg108 <= (others => '0');
	      slv_reg109 <= (others => '0');
	      slv_reg110 <= (others => '0');
	      slv_reg111 <= (others => '0');
	      slv_reg112 <= (others => '0');
	      slv_reg113 <= (others => '0');
	      slv_reg114 <= (others => '0');
	      slv_reg115 <= (others => '0');
	      slv_reg116 <= (others => '0');
	      slv_reg117 <= (others => '0');
	      slv_reg118 <= (others => '0');
	      slv_reg119 <= (others => '0');
	      slv_reg120 <= (others => '0');
	      slv_reg121 <= (others => '0');
	      slv_reg122 <= (others => '0');
	      slv_reg123 <= (others => '0');
	      slv_reg124 <= (others => '0');
	      slv_reg125 <= (others => '0');
	      slv_reg126 <= (others => '0');
	      slv_reg127 <= (others => '0');
	    else
	      loc_addr := axi_awaddr(ADDR_LSB + OPT_MEM_ADDR_BITS downto ADDR_LSB);
	      if (slv_reg_wren = '1') then
	        case loc_addr is
	          when b"0000000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 0
	                slv_reg0(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 1
	                slv_reg1(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 2
	                slv_reg2(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 3
	                slv_reg3(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 4
	                slv_reg4(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 5
	                slv_reg5(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 6
	                slv_reg6(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0000111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 7
	                slv_reg7(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 8
	                slv_reg8(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 9
	                slv_reg9(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 10
	                slv_reg10(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 11
	                slv_reg11(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 12
	                slv_reg12(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 13
	                slv_reg13(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 14
	                slv_reg14(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0001111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 15
	                slv_reg15(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 16
	                slv_reg16(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 17
	                slv_reg17(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 18
	                slv_reg18(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 19
	                slv_reg19(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 20
	                slv_reg20(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 21
	                slv_reg21(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 22
	                slv_reg22(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0010111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 23
	                slv_reg23(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 24
	                slv_reg24(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 25
	                slv_reg25(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 26
	                slv_reg26(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 27
	                slv_reg27(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 28
	                slv_reg28(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 29
	                slv_reg29(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 30
	                slv_reg30(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0011111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 31
	                slv_reg31(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 32
	                slv_reg32(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 33
	                slv_reg33(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 34
	                slv_reg34(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 35
	                slv_reg35(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 36
	                slv_reg36(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 37
	                slv_reg37(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 38
	                slv_reg38(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0100111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 39
	                slv_reg39(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 40
	                slv_reg40(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 41
	                slv_reg41(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 42
	                slv_reg42(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 43
	                slv_reg43(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 44
	                slv_reg44(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 45
	                slv_reg45(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 46
	                slv_reg46(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0101111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 47
	                slv_reg47(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 48
	                slv_reg48(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 49
	                slv_reg49(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 50
	                slv_reg50(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 51
	                slv_reg51(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 52
	                slv_reg52(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 53
	                slv_reg53(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 54
	                slv_reg54(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0110111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 55
	                slv_reg55(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 56
	                slv_reg56(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 57
	                slv_reg57(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 58
	                slv_reg58(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 59
	                slv_reg59(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 60
	                slv_reg60(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 61
	                slv_reg61(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 62
	                slv_reg62(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"0111111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 63
	                slv_reg63(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 64
	                slv_reg64(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 65
	                slv_reg65(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 66
	                slv_reg66(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 67
	                slv_reg67(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 68
	                slv_reg68(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 69
	                slv_reg69(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 70
	                slv_reg70(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1000111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 71
	                slv_reg71(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 72
	                slv_reg72(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 73
	                slv_reg73(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 74
	                slv_reg74(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 75
	                slv_reg75(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 76
	                slv_reg76(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 77
	                slv_reg77(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 78
	                slv_reg78(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1001111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 79
	                slv_reg79(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 80
	                slv_reg80(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 81
	                slv_reg81(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 82
	                slv_reg82(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 83
	                slv_reg83(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 84
	                slv_reg84(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 85
	                slv_reg85(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 86
	                slv_reg86(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1010111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 87
	                slv_reg87(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 88
	                slv_reg88(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 89
	                slv_reg89(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 90
	                slv_reg90(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 91
	                slv_reg91(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 92
	                slv_reg92(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 93
	                slv_reg93(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 94
	                slv_reg94(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1011111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 95
	                slv_reg95(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 96
	                slv_reg96(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 97
	                slv_reg97(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 98
	                slv_reg98(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 99
	                slv_reg99(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 100
	                slv_reg100(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 101
	                slv_reg101(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 102
	                slv_reg102(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1100111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 103
	                slv_reg103(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 104
	                slv_reg104(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 105
	                slv_reg105(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 106
	                slv_reg106(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 107
	                slv_reg107(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 108
	                slv_reg108(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 109
	                slv_reg109(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 110
	                slv_reg110(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1101111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 111
	                slv_reg111(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 112
	                slv_reg112(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 113
	                slv_reg113(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 114
	                slv_reg114(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 115
	                slv_reg115(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 116
	                slv_reg116(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 117
	                slv_reg117(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 118
	                slv_reg118(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1110111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 119
	                slv_reg119(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111000" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 120
	                slv_reg120(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111001" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 121
	                slv_reg121(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111010" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 122
	                slv_reg122(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111011" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 123
	                slv_reg123(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111100" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 124
	                slv_reg124(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111101" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 125
	                slv_reg125(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111110" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 126
	                slv_reg126(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when b"1111111" =>
	            for byte_index in 0 to (C_S_AXI_DATA_WIDTH/8-1) loop
	              if ( S_AXI_WSTRB(byte_index) = '1' ) then
	                -- Respective byte enables are asserted as per write strobes                   
	                -- slave registor 127
	                slv_reg127(byte_index*8+7 downto byte_index*8) <= S_AXI_WDATA(byte_index*8+7 downto byte_index*8);
	              end if;
	            end loop;
	          when others =>
	            slv_reg0 <= slv_reg0;
	            slv_reg1 <= slv_reg1;
	            slv_reg2 <= slv_reg2;
	            slv_reg3 <= slv_reg3;
	            slv_reg4 <= slv_reg4;
	            slv_reg5 <= slv_reg5;
	            slv_reg6 <= slv_reg6;
	            slv_reg7 <= slv_reg7;
	            slv_reg8 <= slv_reg8;
	            slv_reg9 <= slv_reg9;
	            slv_reg10 <= slv_reg10;
	            slv_reg11 <= slv_reg11;
	            slv_reg12 <= slv_reg12;
	            slv_reg13 <= slv_reg13;
	            slv_reg14 <= slv_reg14;
	            slv_reg15 <= slv_reg15;
	            slv_reg16 <= slv_reg16;
	            slv_reg17 <= slv_reg17;
	            slv_reg18 <= slv_reg18;
	            slv_reg19 <= slv_reg19;
	            slv_reg20 <= slv_reg20;
	            slv_reg21 <= slv_reg21;
	            slv_reg22 <= slv_reg22;
	            slv_reg23 <= slv_reg23;
	            slv_reg24 <= slv_reg24;
	            slv_reg25 <= slv_reg25;
	            slv_reg26 <= slv_reg26;
	            slv_reg27 <= slv_reg27;
	            slv_reg28 <= slv_reg28;
	            slv_reg29 <= slv_reg29;
	            slv_reg30 <= slv_reg30;
	            slv_reg31 <= slv_reg31;
	            slv_reg32 <= slv_reg32;
	            slv_reg33 <= slv_reg33;
	            slv_reg34 <= slv_reg34;
	            slv_reg35 <= slv_reg35;
	            slv_reg36 <= slv_reg36;
	            slv_reg37 <= slv_reg37;
	            slv_reg38 <= slv_reg38;
	            slv_reg39 <= slv_reg39;
	            slv_reg40 <= slv_reg40;
	            slv_reg41 <= slv_reg41;
	            slv_reg42 <= slv_reg42;
	            slv_reg43 <= slv_reg43;
	            slv_reg44 <= slv_reg44;
	            slv_reg45 <= slv_reg45;
	            slv_reg46 <= slv_reg46;
	            slv_reg47 <= slv_reg47;
	            slv_reg48 <= slv_reg48;
	            slv_reg49 <= slv_reg49;
	            slv_reg50 <= slv_reg50;
	            slv_reg51 <= slv_reg51;
	            slv_reg52 <= slv_reg52;
	            slv_reg53 <= slv_reg53;
	            slv_reg54 <= slv_reg54;
	            slv_reg55 <= slv_reg55;
	            slv_reg56 <= slv_reg56;
	            slv_reg57 <= slv_reg57;
	            slv_reg58 <= slv_reg58;
	            slv_reg59 <= slv_reg59;
	            slv_reg60 <= slv_reg60;
	            slv_reg61 <= slv_reg61;
	            slv_reg62 <= slv_reg62;
	            slv_reg63 <= slv_reg63;
	            slv_reg64 <= slv_reg64;
	            slv_reg65 <= slv_reg65;
	            slv_reg66 <= slv_reg66;
	            slv_reg67 <= slv_reg67;
	            slv_reg68 <= slv_reg68;
	            slv_reg69 <= slv_reg69;
	            slv_reg70 <= slv_reg70;
	            slv_reg71 <= slv_reg71;
	            slv_reg72 <= slv_reg72;
	            slv_reg73 <= slv_reg73;
	            slv_reg74 <= slv_reg74;
	            slv_reg75 <= slv_reg75;
	            slv_reg76 <= slv_reg76;
	            slv_reg77 <= slv_reg77;
	            slv_reg78 <= slv_reg78;
	            slv_reg79 <= slv_reg79;
	            slv_reg80 <= slv_reg80;
	            slv_reg81 <= slv_reg81;
	            slv_reg82 <= slv_reg82;
	            slv_reg83 <= slv_reg83;
	            slv_reg84 <= slv_reg84;
	            slv_reg85 <= slv_reg85;
	            slv_reg86 <= slv_reg86;
	            slv_reg87 <= slv_reg87;
	            slv_reg88 <= slv_reg88;
	            slv_reg89 <= slv_reg89;
	            slv_reg90 <= slv_reg90;
	            slv_reg91 <= slv_reg91;
	            slv_reg92 <= slv_reg92;
	            slv_reg93 <= slv_reg93;
	            slv_reg94 <= slv_reg94;
	            slv_reg95 <= slv_reg95;
	            slv_reg96 <= slv_reg96;
	            slv_reg97 <= slv_reg97;
	            slv_reg98 <= slv_reg98;
	            slv_reg99 <= slv_reg99;
	            slv_reg100 <= slv_reg100;
	            slv_reg101 <= slv_reg101;
	            slv_reg102 <= slv_reg102;
	            slv_reg103 <= slv_reg103;
	            slv_reg104 <= slv_reg104;
	            slv_reg105 <= slv_reg105;
	            slv_reg106 <= slv_reg106;
	            slv_reg107 <= slv_reg107;
	            slv_reg108 <= slv_reg108;
	            slv_reg109 <= slv_reg109;
	            slv_reg110 <= slv_reg110;
	            slv_reg111 <= slv_reg111;
	            slv_reg112 <= slv_reg112;
	            slv_reg113 <= slv_reg113;
	            slv_reg114 <= slv_reg114;
	            slv_reg115 <= slv_reg115;
	            slv_reg116 <= slv_reg116;
	            slv_reg117 <= slv_reg117;
	            slv_reg118 <= slv_reg118;
	            slv_reg119 <= slv_reg119;
	            slv_reg120 <= slv_reg120;
	            slv_reg121 <= slv_reg121;
	            slv_reg122 <= slv_reg122;
	            slv_reg123 <= slv_reg123;
	            slv_reg124 <= slv_reg124;
	            slv_reg125 <= slv_reg125;
	            slv_reg126 <= slv_reg126;
	            slv_reg127 <= slv_reg127;
	        end case;
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement write response logic generation
	-- The write response and response valid signals are asserted by the slave 
	-- when axi_wready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted.  
	-- This marks the acceptance of address and indicates the status of 
	-- write transaction.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_bvalid  <= '0';
	      axi_bresp   <= "00"; --need to work more on the responses
	    else
	      if (axi_awready = '1' and S_AXI_AWVALID = '1' and axi_wready = '1' and S_AXI_WVALID = '1' and axi_bvalid = '0'  ) then
	        axi_bvalid <= '1';
	        axi_bresp  <= "00"; 
	      elsif (S_AXI_BREADY = '1' and axi_bvalid = '1') then   --check if bready is asserted while bvalid is high)
	        axi_bvalid <= '0';                                 -- (there is a possibility that bready is always asserted high)
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_arready generation
	-- axi_arready is asserted for one S_AXI_ACLK clock cycle when
	-- S_AXI_ARVALID is asserted. axi_awready is 
	-- de-asserted when reset (active low) is asserted. 
	-- The read address is also latched when S_AXI_ARVALID is 
	-- asserted. axi_araddr is reset to zero on reset assertion.

	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then 
	    if S_AXI_ARESETN = '0' then
	      axi_arready <= '0';
	      axi_araddr  <= (others => '1');
	    else
	      if (axi_arready = '0' and S_AXI_ARVALID = '1') then
	        -- indicates that the slave has acceped the valid read address
	        axi_arready <= '1';
	        -- Read Address latching 
	        axi_araddr  <= S_AXI_ARADDR;           
	      else
	        axi_arready <= '0';
	      end if;
	    end if;
	  end if;                   
	end process; 

	-- Implement axi_arvalid generation
	-- axi_rvalid is asserted for one S_AXI_ACLK clock cycle when both 
	-- S_AXI_ARVALID and axi_arready are asserted. The slave registers 
	-- data are available on the axi_rdata bus at this instance. The 
	-- assertion of axi_rvalid marks the validity of read data on the 
	-- bus and axi_rresp indicates the status of read transaction.axi_rvalid 
	-- is deasserted on reset (active low). axi_rresp and axi_rdata are 
	-- cleared to zero on reset (active low).  
	process (S_AXI_ACLK)
	begin
	  if rising_edge(S_AXI_ACLK) then
	    if S_AXI_ARESETN = '0' then
	      axi_rvalid <= '0';
	      axi_rresp  <= "00";
	    else
	      if (axi_arready = '1' and S_AXI_ARVALID = '1' and axi_rvalid = '0') then
	        -- Valid read data is available at the read data bus
	        axi_rvalid <= '1';
	        axi_rresp  <= "00"; -- 'OKAY' response
	      elsif (axi_rvalid = '1' and S_AXI_RREADY = '1') then
	        -- Read data is accepted by the master
	        axi_rvalid <= '0';
	      end if;            
	    end if;
	  end if;
	end process;

	-- Implement memory mapped register select and read logic generation
	-- Slave register read enable is asserted when valid address is available
	-- and the slave is ready to accept the read address.
	slv_reg_rden <= axi_arready and S_AXI_ARVALID and (not axi_rvalid) ;

	process (slv_reg0, slv_reg1, slv_reg2, slv_reg3, slv_reg4, slv_reg5, slv_reg6, slv_reg7, slv_reg8, slv_reg9, slv_reg10, slv_reg11, slv_reg12, slv_reg13, slv_reg14, slv_reg15, slv_reg16, slv_reg17, slv_reg18, slv_reg19, slv_reg20, slv_reg21, slv_reg22, slv_reg23, slv_reg24, slv_reg25, slv_reg26, slv_reg27, slv_reg28, slv_reg29, slv_reg30, slv_reg31, slv_reg32, slv_reg33, slv_reg34, slv_reg35, slv_reg36, slv_reg37, slv_reg38, slv_reg39, slv_reg40, slv_reg41, slv_reg42, slv_reg43, slv_reg44, slv_reg45, slv_reg46, slv_reg47, slv_reg48, slv_reg49, slv_reg50, slv_reg51, slv_reg52, slv_reg53, slv_reg54, slv_reg55, slv_reg56, slv_reg57, slv_reg58, slv_reg59, slv_reg60, slv_reg61, slv_reg62, slv_reg63, slv_reg64, slv_reg65, slv_reg66, slv_reg67, slv_reg68, slv_reg69, slv_reg70, slv_reg71, slv_reg72, slv_reg73, slv_reg74, slv_reg75, slv_reg76, slv_reg77, slv_reg78, slv_reg79, slv_reg80, slv_reg81, slv_reg82, slv_reg83, slv_reg84, slv_reg85, slv_reg86, slv_reg87, slv_reg88, slv_reg89, slv_reg90, slv_reg91, slv_reg92, slv_reg93, slv_reg94, slv_reg95, slv_reg96, slv_reg97, slv_reg98, slv_reg99, slv_reg100, slv_reg101, slv_reg102, slv_reg103, slv_reg104, slv_reg105, slv_reg106, slv_reg107, slv_reg108, slv_reg109, slv_reg110, slv_reg111, slv_reg112, slv_reg113, slv_reg114, slv_reg115, slv_reg116, slv_reg117, slv_reg118, slv_reg119, slv_reg120, slv_reg121, slv_reg122, slv_reg123, slv_reg124, slv_reg125, slv_reg126, slv_reg127, axi_araddr, S_AXI_ARESETN, slv_reg_rden)
	variable loc_addr :std_logic_vector(OPT_MEM_ADDR_BITS downto 0);
	begin
	    -- Address decoding for reading registers
	    loc_addr := axi_araddr(ADDR_LSB + OPT_MEM_ADDR_BITS downto ADDR_LSB);
	    case loc_addr is
	      when b"0000000" =>
	        reg_data_out <= slv_reg0;
	      when b"0000001" =>
	        reg_data_out <= slv_reg1;
	      when b"0000010" =>
	        reg_data_out <= slv_reg2;
	      when b"0000011" =>
	        reg_data_out <= slv_reg3;
	      when b"0000100" =>
	        reg_data_out <= slv_reg4;
	      when b"0000101" =>
	        reg_data_out <= slv_reg5;
	      when b"0000110" =>
	        reg_data_out <= b"00000000000000000000000000000" & error_flag_1_s & error_flag_2_s & error_flag_3_s;
	      when b"0000111" =>
	        reg_data_out <= x"AFFEAFFE";
	      when b"0001000" =>
	        reg_data_out <= Temp_00_out_LTC_1_s;
	      when b"0001001" =>                  
	        reg_data_out <= Temp_01_out_LTC_1_s;
	      when b"0001010" =>                  
	        reg_data_out <= Temp_02_out_LTC_1_s;
	      when b"0001011" =>                  
	        reg_data_out <= Temp_03_out_LTC_1_s;
	      when b"0001100" =>                  
	        reg_data_out <= Temp_04_out_LTC_1_s;
	      when b"0001101" =>                  
	        reg_data_out <= Temp_05_out_LTC_1_s;
	      when b"0001110" =>                  
	        reg_data_out <= Temp_06_out_LTC_1_s;
	      when b"0001111" =>                  
	        reg_data_out <= Temp_07_out_LTC_1_s;
	      when b"0010000" =>                  
	        reg_data_out <= Temp_08_out_LTC_1_s;
	      when b"0010001" =>                  
	        reg_data_out <= Temp_09_out_LTC_1_s;
	      when b"0010010" =>                  
	        reg_data_out <= Temp_10_out_LTC_1_s;
	      when b"0010011" =>                  
	        reg_data_out <= Temp_11_out_LTC_1_s;
	      when b"0010100" =>                  
	        reg_data_out <= Temp_12_out_LTC_1_s;
	      when b"0010101" =>                  
	        reg_data_out <= Temp_13_out_LTC_1_s;
	      when b"0010110" =>                  
	        reg_data_out <= Temp_14_out_LTC_1_s;
	      when b"0010111" =>                  
	        reg_data_out <= Temp_15_out_LTC_1_s;
	      when b"0011000" =>                  
	        reg_data_out <= Temp_16_out_LTC_1_s;
	      when b"0011001" =>                  
	        reg_data_out <= Temp_17_out_LTC_1_s;
	      when b"0011010" =>                  
	        reg_data_out <= Temp_18_out_LTC_1_s;
	      when b"0011011" =>                  
	        reg_data_out <= Temp_19_out_LTC_1_s;
	      when b"0011100" =>
	        reg_data_out <= slv_reg28;
	      when b"0011101" =>
	        reg_data_out <= slv_reg29;
	      when b"0011110" =>
	        reg_data_out <= slv_reg30;
	      when b"0011111" =>
	        reg_data_out <= slv_reg31;
	      when b"0100000" =>
	        reg_data_out <= slv_reg32;
	      when b"0100001" =>
	        reg_data_out <= slv_reg33;
	      when b"0100010" =>
	        reg_data_out <= slv_reg34;
	      when b"0100011" =>
	        reg_data_out <= slv_reg35;
	      when b"0100100" =>
	        reg_data_out <= slv_reg36;
	      when b"0100101" =>
	        reg_data_out <= slv_reg37;
	      when b"0100110" =>
	        reg_data_out <= slv_reg38;
	      when b"0100111" =>
	        reg_data_out <= slv_reg39;
	      when b"0101000" =>
	        reg_data_out <= slv_reg40;
	      when b"0101001" =>
	        reg_data_out <= slv_reg41;
	      when b"0101010" =>
	        reg_data_out <= slv_reg42;
	      when b"0101011" =>
	        reg_data_out <= slv_reg43;
	      when b"0101100" =>
	        reg_data_out <= slv_reg44;
	      when b"0101101" =>
	        reg_data_out <= slv_reg45;
	      when b"0101110" =>
	        reg_data_out <= slv_reg46;
	      when b"0101111" =>
	        reg_data_out <= slv_reg47;
	      when b"0110000" =>
	        reg_data_out <= Temp_00_out_LTC_2_s;
	      when b"0110001" =>                  
	        reg_data_out <= Temp_01_out_LTC_2_s;
	      when b"0110010" =>                  
	        reg_data_out <= Temp_02_out_LTC_2_s;
	      when b"0110011" =>                  
	        reg_data_out <= Temp_03_out_LTC_2_s;
	      when b"0110100" =>                  
	        reg_data_out <= Temp_04_out_LTC_2_s;
	      when b"0110101" =>                  
	        reg_data_out <= Temp_05_out_LTC_2_s;
	      when b"0110110" =>                  
	        reg_data_out <= Temp_06_out_LTC_2_s;
	      when b"0110111" =>                  
	        reg_data_out <= Temp_07_out_LTC_2_s;
	      when b"0111000" =>                  
	        reg_data_out <= Temp_08_out_LTC_2_s;
	      when b"0111001" =>                  
	        reg_data_out <= Temp_09_out_LTC_2_s;
	      when b"0111010" =>                  
	        reg_data_out <= Temp_10_out_LTC_2_s;
	      when b"0111011" =>                  
	        reg_data_out <= Temp_11_out_LTC_2_s;
	      when b"0111100" =>                  
	        reg_data_out <= Temp_12_out_LTC_2_s;
	      when b"0111101" =>                  
	        reg_data_out <= Temp_13_out_LTC_2_s;
	      when b"0111110" =>                  
	        reg_data_out <= Temp_14_out_LTC_2_s;
	      when b"0111111" =>                  
	        reg_data_out <= Temp_15_out_LTC_2_s;
	      when b"1000000" =>                  
	        reg_data_out <= Temp_16_out_LTC_2_s;
	      when b"1000001" =>                  
	        reg_data_out <= Temp_17_out_LTC_2_s;
	      when b"1000010" =>                  
	        reg_data_out <= Temp_18_out_LTC_2_s;
	      when b"1000011" =>                  
	        reg_data_out <= Temp_19_out_LTC_2_s;
	      when b"1000100" =>
	        reg_data_out <= slv_reg68;
	      when b"1000101" =>
	        reg_data_out <= slv_reg69;
	      when b"1000110" =>
	        reg_data_out <= slv_reg70;
	      when b"1000111" =>
	        reg_data_out <= slv_reg71;
	      when b"1001000" =>
	        reg_data_out <= slv_reg72;
	      when b"1001001" =>
	        reg_data_out <= slv_reg73;
	      when b"1001010" =>
	        reg_data_out <= slv_reg74;
	      when b"1001011" =>
	        reg_data_out <= slv_reg75;
	      when b"1001100" =>
	        reg_data_out <= slv_reg76;
	      when b"1001101" =>
	        reg_data_out <= slv_reg77;
	      when b"1001110" =>
	        reg_data_out <= slv_reg78;
	      when b"1001111" =>
	        reg_data_out <= slv_reg79;
	      when b"1010000" =>
	        reg_data_out <= slv_reg80;
	      when b"1010001" =>
	        reg_data_out <= slv_reg81;
	      when b"1010010" =>
	        reg_data_out <= slv_reg82;
	      when b"1010011" =>
	        reg_data_out <= slv_reg83;
	      when b"1010100" =>
	        reg_data_out <= slv_reg84;
	      when b"1010101" =>
	        reg_data_out <= slv_reg85;
	      when b"1010110" =>
	        reg_data_out <= slv_reg86;
	      when b"1010111" =>
	        reg_data_out <= slv_reg87;
	      when b"1011000" =>
	        reg_data_out <= Temp_00_out_LTC_3_s;
	      when b"1011001" =>
	        reg_data_out <= Temp_01_out_LTC_3_s;
	      when b"1011010" =>
	        reg_data_out <= Temp_02_out_LTC_3_s;
	      when b"1011011" =>
	        reg_data_out <= Temp_03_out_LTC_3_s;
	      when b"1011100" =>
	        reg_data_out <= Temp_04_out_LTC_3_s;
	      when b"1011101" =>
	        reg_data_out <= Temp_05_out_LTC_3_s;
	      when b"1011110" =>
	        reg_data_out <= Temp_06_out_LTC_3_s;
	      when b"1011111" =>
	        reg_data_out <= Temp_07_out_LTC_3_s;
	      when b"1100000" =>
	        reg_data_out <= Temp_08_out_LTC_3_s;
	      when b"1100001" =>
	        reg_data_out <= Temp_09_out_LTC_3_s;
	      when b"1100010" =>
	        reg_data_out <= Temp_10_out_LTC_3_s;
	      when b"1100011" =>
	        reg_data_out <= Temp_11_out_LTC_3_s;
	      when b"1100100" =>
	        reg_data_out <= Temp_12_out_LTC_3_s;
	      when b"1100101" =>
	        reg_data_out <= Temp_13_out_LTC_3_s;
	      when b"1100110" =>
	        reg_data_out <= Temp_14_out_LTC_3_s;
	      when b"1100111" =>
	        reg_data_out <= Temp_15_out_LTC_3_s;
	      when b"1101000" =>
	        reg_data_out <= Temp_16_out_LTC_3_s;
	      when b"1101001" =>
	        reg_data_out <= Temp_17_out_LTC_3_s;
	      when b"1101010" =>
	        reg_data_out <= Temp_18_out_LTC_3_s;
	      when b"1101011" =>
	        reg_data_out <= Temp_19_out_LTC_3_s;
	      when b"1101100" =>
	        reg_data_out <= slv_reg108;
	      when b"1101101" =>
	        reg_data_out <= slv_reg109;
	      when b"1101110" =>
	        reg_data_out <= slv_reg110;
	      when b"1101111" =>
	        reg_data_out <= slv_reg111;
	      when b"1110000" =>
	        reg_data_out <= slv_reg112;
	      when b"1110001" =>
	        reg_data_out <= slv_reg113;
	      when b"1110010" =>
	        reg_data_out <= slv_reg114;
	      when b"1110011" =>
	        reg_data_out <= slv_reg115;
	      when b"1110100" =>
	        reg_data_out <= slv_reg116;
	      when b"1110101" =>
	        reg_data_out <= slv_reg117;
	      when b"1110110" =>
	        reg_data_out <= slv_reg118;
	      when b"1110111" =>
	        reg_data_out <= slv_reg119;
	      when b"1111000" =>
	        reg_data_out <= slv_reg120;
	      when b"1111001" =>
	        reg_data_out <= slv_reg121;
	      when b"1111010" =>
	        reg_data_out <= slv_reg122;
	      when b"1111011" =>
	        reg_data_out <= slv_reg123;
	      when b"1111100" =>
	        reg_data_out <= slv_reg124;
	      when b"1111101" =>
	        reg_data_out <= slv_reg125;
	      when b"1111110" =>
	        reg_data_out <= slv_reg126;
	      when b"1111111" =>
	        reg_data_out <= slv_reg127;
	      when others =>
	        reg_data_out  <= (others => '0');
	    end case;
	end process; 

	-- Output register or memory read data
	process( S_AXI_ACLK ) is
	begin
	  if (rising_edge (S_AXI_ACLK)) then
	    if ( S_AXI_ARESETN = '0' ) then
	      axi_rdata  <= (others => '0');
	    else
	      if (slv_reg_rden = '1') then
	        -- When there is a valid read address (S_AXI_ARVALID) with 
	        -- acceptance of read address by the slave (axi_arready), 
	        -- output the read dada 
	        -- Read address mux
	          axi_rdata <= reg_data_out;     -- register read data
	      end if;   
	    end if;
	  end if;
	end process;


	-- Add user logic here
LTC2983_Handler_1 : LTC2983_Interface 
	Port map(
		clock   				=> S_AXI_ACLK,
		reset_n 				=> handlerreset,
		enable  				=> enable,
		go_sig					=> go_sig,
		busy    				=> busy_1_s,
		ready 					=> ready_1_s,
		error_flag				=> error_flag_1_s,
		--
		SPI_MOSI				=> SPI_MOSI_1,
		SPI_MISO				=> SPI_MISO_1,
		SPI_SCLK				=> SPI_SCLK_1,
		SPI_SS					=> SPI_SS_1,
		LTC_Interrupt			=> LTC_Interrupt_1,
		LTC_resetn				=> LTC_resetn_1,
		--
		Temp_00_out				=> Temp_00_out_LTC_1_s,
		Temp_01_out				=> Temp_01_out_LTC_1_s,
		Temp_02_out				=> Temp_02_out_LTC_1_s,
		Temp_03_out				=> Temp_03_out_LTC_1_s,
		Temp_04_out				=> Temp_04_out_LTC_1_s,
		Temp_05_out				=> Temp_05_out_LTC_1_s,
		Temp_06_out				=> Temp_06_out_LTC_1_s,
		Temp_07_out				=> Temp_07_out_LTC_1_s,
		Temp_08_out				=> Temp_08_out_LTC_1_s,
		Temp_09_out				=> Temp_09_out_LTC_1_s,
		Temp_10_out				=> Temp_10_out_LTC_1_s,
		Temp_11_out				=> Temp_11_out_LTC_1_s,
		Temp_12_out				=> Temp_12_out_LTC_1_s,
		Temp_13_out				=> Temp_13_out_LTC_1_s,
		Temp_14_out				=> Temp_14_out_LTC_1_s,
		Temp_15_out				=> Temp_15_out_LTC_1_s,
		Temp_16_out				=> Temp_16_out_LTC_1_s,
		Temp_17_out				=> Temp_17_out_LTC_1_s,
		Temp_18_out				=> Temp_18_out_LTC_1_s,
		Temp_19_out				=> Temp_19_out_LTC_1_s,

		LTC_CH_0_config_in		=> slv_reg28,
		LTC_CH_1_config_in		=> slv_reg29,
		LTC_CH_2_config_in		=> slv_reg30,
		LTC_CH_3_config_in		=> slv_reg31,
		LTC_CH_4_config_in		=> slv_reg32,
		LTC_CH_5_config_in		=> slv_reg33,
		LTC_CH_6_config_in		=> slv_reg34,
		LTC_CH_7_config_in		=> slv_reg35,
		LTC_CH_8_config_in		=> slv_reg36,
		LTC_CH_9_config_in		=> slv_reg37,
		LTC_CH_10_config_in		=> slv_reg38,
		LTC_CH_11_config_in		=> slv_reg39,
		LTC_CH_12_config_in		=> slv_reg40,
		LTC_CH_13_config_in		=> slv_reg41,
		LTC_CH_14_config_in		=> slv_reg42,
		LTC_CH_15_config_in		=> slv_reg43,
		LTC_CH_16_config_in		=> slv_reg44,
		LTC_CH_17_config_in		=> slv_reg45,
		LTC_CH_18_config_in		=> slv_reg46,
		LTC_CH_19_config_in		=> slv_reg47
	);

LTC2983_Handler_2 : LTC2983_Interface 
	Port map(
		clock   				=> S_AXI_ACLK,
		reset_n 				=> handlerreset,
		enable  				=> enable,
		go_sig					=> go_sig,
		busy    				=> busy_2_s,
		ready 					=> ready_2_s,
		error_flag				=> error_flag_2_s,
		--
		SPI_MOSI				=> SPI_MOSI_2,
		SPI_MISO				=> SPI_MISO_2,
		SPI_SCLK				=> SPI_SCLK_2,
		SPI_SS					=> SPI_SS_2,
		LTC_Interrupt			=> LTC_Interrupt_2,
		LTC_resetn				=> LTC_resetn_2,
		--
		Temp_00_out				=> Temp_00_out_LTC_2_s,
		Temp_01_out				=> Temp_01_out_LTC_2_s,
		Temp_02_out				=> Temp_02_out_LTC_2_s,
		Temp_03_out				=> Temp_03_out_LTC_2_s,
		Temp_04_out				=> Temp_04_out_LTC_2_s,
		Temp_05_out				=> Temp_05_out_LTC_2_s,
		Temp_06_out				=> Temp_06_out_LTC_2_s,
		Temp_07_out				=> Temp_07_out_LTC_2_s,
		Temp_08_out				=> Temp_08_out_LTC_2_s,
		Temp_09_out				=> Temp_09_out_LTC_2_s,
		Temp_10_out				=> Temp_10_out_LTC_2_s,
		Temp_11_out				=> Temp_11_out_LTC_2_s,
		Temp_12_out				=> Temp_12_out_LTC_2_s,
		Temp_13_out				=> Temp_13_out_LTC_2_s,
		Temp_14_out				=> Temp_14_out_LTC_2_s,
		Temp_15_out				=> Temp_15_out_LTC_2_s,
		Temp_16_out				=> Temp_16_out_LTC_2_s,
		Temp_17_out				=> Temp_17_out_LTC_2_s,
		Temp_18_out				=> Temp_18_out_LTC_2_s,
		Temp_19_out				=> Temp_19_out_LTC_2_s,

		LTC_CH_0_config_in		=> slv_reg68,
		LTC_CH_1_config_in		=> slv_reg69,
		LTC_CH_2_config_in		=> slv_reg70,
		LTC_CH_3_config_in		=> slv_reg71,
		LTC_CH_4_config_in		=> slv_reg72,
		LTC_CH_5_config_in		=> slv_reg73,
		LTC_CH_6_config_in		=> slv_reg74,
		LTC_CH_7_config_in		=> slv_reg75,
		LTC_CH_8_config_in		=> slv_reg76,
		LTC_CH_9_config_in		=> slv_reg77,
		LTC_CH_10_config_in		=> slv_reg78,
		LTC_CH_11_config_in		=> slv_reg79,
		LTC_CH_12_config_in		=> slv_reg80,
		LTC_CH_13_config_in		=> slv_reg81,
		LTC_CH_14_config_in		=> slv_reg82,
		LTC_CH_15_config_in		=> slv_reg83,
		LTC_CH_16_config_in		=> slv_reg84,
		LTC_CH_17_config_in		=> slv_reg85,
		LTC_CH_18_config_in		=> slv_reg86,
		LTC_CH_19_config_in		=> slv_reg87
	);
	
LTC2983_Handler_3 : LTC2983_Interface 
	Port map(
		clock   				=> S_AXI_ACLK,
		reset_n 				=> handlerreset,
		enable  				=> enable,
		go_sig					=> go_sig,
		busy    				=> busy_3_s,
		ready 					=> ready_3_s,
		error_flag				=> error_flag_3_s,
		--
		SPI_MOSI				=> SPI_MOSI_3,
		SPI_MISO				=> SPI_MISO_3,
		SPI_SCLK				=> SPI_SCLK_3,
		SPI_SS					=> SPI_SS_3,
		LTC_Interrupt			=> LTC_Interrupt_3,
		LTC_resetn				=> LTC_resetn_3,
		--
		Temp_00_out				=> Temp_00_out_LTC_3_s,
		Temp_01_out				=> Temp_01_out_LTC_3_s,
		Temp_02_out				=> Temp_02_out_LTC_3_s,
		Temp_03_out				=> Temp_03_out_LTC_3_s,
		Temp_04_out				=> Temp_04_out_LTC_3_s,
		Temp_05_out				=> Temp_05_out_LTC_3_s,
		Temp_06_out				=> Temp_06_out_LTC_3_s,
		Temp_07_out				=> Temp_07_out_LTC_3_s,
		Temp_08_out				=> Temp_08_out_LTC_3_s,
		Temp_09_out				=> Temp_09_out_LTC_3_s,
		Temp_10_out				=> Temp_10_out_LTC_3_s,
		Temp_11_out				=> Temp_11_out_LTC_3_s,
		Temp_12_out				=> Temp_12_out_LTC_3_s,
		Temp_13_out				=> Temp_13_out_LTC_3_s,
		Temp_14_out				=> Temp_14_out_LTC_3_s,
		Temp_15_out				=> Temp_15_out_LTC_3_s,
		Temp_16_out				=> Temp_16_out_LTC_3_s,
		Temp_17_out				=> Temp_17_out_LTC_3_s,
		Temp_18_out				=> Temp_18_out_LTC_3_s,
		Temp_19_out				=> Temp_19_out_LTC_3_s,

		LTC_CH_0_config_in		=> slv_reg108,
		LTC_CH_1_config_in		=> slv_reg109,
		LTC_CH_2_config_in		=> slv_reg110,
		LTC_CH_3_config_in		=> slv_reg111,
		LTC_CH_4_config_in		=> slv_reg112,
		LTC_CH_5_config_in		=> slv_reg113,
		LTC_CH_6_config_in		=> slv_reg114,
		LTC_CH_7_config_in		=> slv_reg115,
		LTC_CH_8_config_in		=> slv_reg116,
		LTC_CH_9_config_in		=> slv_reg117,
		LTC_CH_10_config_in		=> slv_reg118,
		LTC_CH_11_config_in		=> slv_reg119,
		LTC_CH_12_config_in		=> slv_reg120,
		LTC_CH_13_config_in		=> slv_reg121,
		LTC_CH_14_config_in		=> slv_reg122,
		LTC_CH_15_config_in		=> slv_reg123,
		LTC_CH_16_config_in		=> slv_reg124,
		LTC_CH_17_config_in		=> slv_reg125,
		LTC_CH_18_config_in		=> slv_reg126,
		LTC_CH_19_config_in		=> slv_reg127
	);
	
	-- Generate Trigger
    GO_sig_Stage1_process:Process (S_AXI_ACLK) is
    begin
        if rising_edge (S_AXI_ACLK) then
            if (S_AXI_ARESETN = '0') then
                GO_sig_counter       <= (others =>'0');
                go_sig               <= '0';
            else
                if (slv_reg0(0) = '1') then                         -- enabled
                    if(GO_sig_counter  > unsigned(slv_reg1))  then
                        go_sig               <= '1';
                        GO_sig_counter       <= (others =>'0');
                    else
                        go_sig               <= '0';
                        GO_sig_counter       <= GO_sig_counter +1;
                    end if; 
                end if;   
            end if;
        end if;
    end process;
	
	--Maps
	handlerreset   <= S_AXI_ARESETN AND slv_reg0(1);       -- second Reset-Source for the Handlers
	 
	busy_1         <= busy_1_s       ;
	ready_1        <= ready_1_s      ;
	error_flag_1   <= error_flag_1_s ;
	busy_2         <= busy_2_s       ;
	ready_2        <= ready_2_s      ;
	error_flag_2   <= error_flag_2_s ;
	busy_3         <= busy_3_s       ;
	ready_3        <= ready_3_s      ;
	error_flag_3   <= error_flag_3_s ;
	
	Temp_00_out_LTC_1       <=    Temp_00_out_LTC_1_s;
    Temp_01_out_LTC_1       <=    Temp_01_out_LTC_1_s;
    Temp_02_out_LTC_1       <=    Temp_02_out_LTC_1_s;
    Temp_03_out_LTC_1       <=    Temp_03_out_LTC_1_s;
    Temp_04_out_LTC_1       <=    Temp_04_out_LTC_1_s;
    Temp_05_out_LTC_1       <=    Temp_05_out_LTC_1_s;
    Temp_06_out_LTC_1       <=    Temp_06_out_LTC_1_s;
    Temp_07_out_LTC_1       <=    Temp_07_out_LTC_1_s;
    Temp_08_out_LTC_1       <=    Temp_08_out_LTC_1_s;
    Temp_09_out_LTC_1       <=    Temp_09_out_LTC_1_s;
    Temp_10_out_LTC_1       <=    Temp_10_out_LTC_1_s;
    Temp_11_out_LTC_1       <=    Temp_11_out_LTC_1_s;
    Temp_12_out_LTC_1       <=    Temp_12_out_LTC_1_s;
    Temp_13_out_LTC_1       <=    Temp_13_out_LTC_1_s;
    Temp_14_out_LTC_1       <=    Temp_14_out_LTC_1_s;
    Temp_15_out_LTC_1       <=    Temp_15_out_LTC_1_s;
    Temp_16_out_LTC_1       <=    Temp_16_out_LTC_1_s;
    Temp_17_out_LTC_1       <=    Temp_17_out_LTC_1_s;
    Temp_18_out_LTC_1       <=    Temp_18_out_LTC_1_s;
    Temp_19_out_LTC_1       <=    Temp_19_out_LTC_1_s;

    Temp_00_out_LTC_2       <=    Temp_00_out_LTC_2_s;
    Temp_01_out_LTC_2       <=    Temp_01_out_LTC_2_s;
    Temp_02_out_LTC_2       <=    Temp_02_out_LTC_2_s;
    Temp_03_out_LTC_2       <=    Temp_03_out_LTC_2_s;
    Temp_04_out_LTC_2       <=    Temp_04_out_LTC_2_s;
    Temp_05_out_LTC_2       <=    Temp_05_out_LTC_2_s;
    Temp_06_out_LTC_2       <=    Temp_06_out_LTC_2_s;
    Temp_07_out_LTC_2       <=    Temp_07_out_LTC_2_s;
    Temp_08_out_LTC_2       <=    Temp_08_out_LTC_2_s;
    Temp_09_out_LTC_2       <=    Temp_09_out_LTC_2_s;
    Temp_10_out_LTC_2       <=    Temp_10_out_LTC_2_s;
    Temp_11_out_LTC_2       <=    Temp_11_out_LTC_2_s;
    Temp_12_out_LTC_2       <=    Temp_12_out_LTC_2_s;
    Temp_13_out_LTC_2       <=    Temp_13_out_LTC_2_s;
    Temp_14_out_LTC_2       <=    Temp_14_out_LTC_2_s;
    Temp_15_out_LTC_2       <=    Temp_15_out_LTC_2_s;
    Temp_16_out_LTC_2       <=    Temp_16_out_LTC_2_s;
    Temp_17_out_LTC_2       <=    Temp_17_out_LTC_2_s;
    Temp_18_out_LTC_2       <=    Temp_18_out_LTC_2_s;
    Temp_19_out_LTC_2       <=    Temp_19_out_LTC_2_s;

    Temp_00_out_LTC_3       <=    Temp_00_out_LTC_3_s;
    Temp_01_out_LTC_3       <=    Temp_01_out_LTC_3_s;
    Temp_02_out_LTC_3       <=    Temp_02_out_LTC_3_s;
    Temp_03_out_LTC_3       <=    Temp_03_out_LTC_3_s;
    Temp_04_out_LTC_3       <=    Temp_04_out_LTC_3_s;
    Temp_05_out_LTC_3       <=    Temp_05_out_LTC_3_s;
    Temp_06_out_LTC_3       <=    Temp_06_out_LTC_3_s;
    Temp_07_out_LTC_3       <=    Temp_07_out_LTC_3_s;
    Temp_08_out_LTC_3       <=    Temp_08_out_LTC_3_s;
    Temp_09_out_LTC_3       <=    Temp_09_out_LTC_3_s;
    Temp_10_out_LTC_3       <=    Temp_10_out_LTC_3_s;
    Temp_11_out_LTC_3       <=    Temp_11_out_LTC_3_s;
    Temp_12_out_LTC_3       <=    Temp_12_out_LTC_3_s;
    Temp_13_out_LTC_3       <=    Temp_13_out_LTC_3_s;
    Temp_14_out_LTC_3       <=    Temp_14_out_LTC_3_s;
    Temp_15_out_LTC_3       <=    Temp_15_out_LTC_3_s;
    Temp_16_out_LTC_3       <=    Temp_16_out_LTC_3_s;
    Temp_17_out_LTC_3       <=    Temp_17_out_LTC_3_s;
    Temp_18_out_LTC_3       <=    Temp_18_out_LTC_3_s;
    Temp_19_out_LTC_3       <=    Temp_19_out_LTC_3_s;
	-- User logic ends

end arch_imp;
