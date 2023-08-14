library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

Library UNISIM;
use UNISIM.vcomponents.all;

library work;
use work.ADC_LTC2311_PKG.all;

entity ADC_LTC2311_v3_0 is
	generic (
		-- Users to add parameters here
        DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
        CHANNELS_PER_MASTER : natural := 8;     -- Number of slaves that are controlled with the same SS_N and SCLK
        SPI_MASTER          : natural := 1;     -- Number of independent SPI Masters
        OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
        CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
        RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
        RES_MSB             : natural := 23;    -- MSB in the result vector of the multiplactor output
        DIFFERENTIAL        : boolean := true;
		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 6
	);
	port (
		-- Users to add ports here
		
        RAW_VALUE       : out std_logic_vector(DATA_WIDTH * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        RAW_VALID       : out std_logic_vector(SPI_MASTER - 1 downto 0);
        SI_VALUE        : out std_logic_vector((SPI_MASTER * CHANNELS_PER_MASTER * (RES_MSB - RES_LSB + 1) ) - 1  downto 0);
        SI_VALID        : out std_logic_vector(SPI_MASTER - 1 downto 0);
        TRIGGER_CNV     : in std_logic_vector(SPI_MASTER - 1 downto 0);
        SAMPLE_COUNTER  : out std_logic_vector((SPI_MASTER * C_S00_AXI_DATA_WIDTH) - 1 downto 0);
        
        -- SPI ports
        SCLK            : out std_logic_vector(SPI_MASTER - 1 downto 0);
        MISO            : in std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        SS_N            : out std_logic_vector(SPI_MASTER - 1 downto 0);
        
        -- Differential SPI Ports
        SCLK_DIFF       : out std_logic_vector(2 * SPI_MASTER - 1 downto 0);
        MISO_DIFF       : in std_logic_vector(2 * CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
        
        
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
end ADC_LTC2311_v3_0;

architecture arch_imp of ADC_LTC2311_v3_0 is
    
    constant STD_ZERO           : std_logic_vector(SPI_MASTER - 1 downto 0) := (others => '0');
    -- signal declarations
    
    -- SPI signals
    signal S_CPHA, S_CPOL         : std_logic;
    signal S_SCLK_IN, S_SS_IN_N, S_SCLK   : std_logic_vector(SPI_MASTER - 1 downto 0);
    signal S_MISO                 : std_logic_vector(CHANNELS_PER_MASTER * SPI_MASTER - 1 downto 0);
    signal S_PRE_DELAY, S_POST_DELAY              : std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
    signal S_CLK_DIV                              : std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0);
    signal S_SPI_MANUAL           : std_logic_vector(SPI_MASTER - 1 downto 0);
    
    -- control signals
    signal S_ENABLE, S_SET_CONVERSION, S_SET_OFFSET, S_SET_SAMPLES, S_SET_SAMPLE_TIME : std_logic_vector(SPI_MASTER - 1 downto 0);
    signal S_RESET_N, S_CLK : std_logic;
    signal S_TRIGGER_CNV_PIPE : std_logic_vector(SPI_MASTER - 1 downto 0);
    
    -- AXI values
    
    signal S_ADC_CR	                : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_CR_IN              : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_SPI_CR	            : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_SPI_CR_IN          : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_SPI_CFGR           : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_MASTER_CHANNEL     : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_CHANNEL            : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_MASTER_FINISH	    : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_MASTER_SI_FINISH	: std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_MASTER_BUSY	    : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_CONV_VALUE         : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    signal S_ADC_AVAILABLE          : std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
    
    type state_type is (TRIGGERED,CONTINUOUS,SPI_MANUAL);
    signal curstate, nxtstate : state_type := TRIGGERED;
    attribute fsm_encoding : string;
    attribute fsm_encoding of curstate, nxtstate : signal is "auto";
    attribute fsm_safe_state : string;
    attribute fsm_safe_state of curstate, nxtstate : signal is "power_on_state";
    

	-- component declaration AXI4 Lite interface
	component ADC_LTC2311_v3_0_S00_AXI is
		generic (
		C_S_AXI_DATA_WIDTH	: integer	:= C_C_S_AXI_DATA_WIDTH;
		C_S_AXI_ADDR_WIDTH	: integer	:= 6
		);
		port (
		-- registers
		P_ADC_CR	                 : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_CR_IN	                 : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_SPI_CR	             : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_SPI_CR_IN	             : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_SPI_CFGR	             : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_MASTER_CHANNEL	     : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_CHANNEL	             : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_MASTER_FINISH	         : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_MASTER_SI_FINISH	     : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_MASTER_BUSY	         : in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_CONV_VALUE	         : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        P_ADC_AVAILABLE              : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        -- communication
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
	end component ADC_LTC2311_v3_0_S00_AXI;
	
	-- user components
    
    component ADC_CONTROLLER is
        generic(
            DATA_WIDTH          : natural := 16;    -- Number of bits per SPI frame
            CHANNELS            : natural := 1;     -- Number of slaves that are controlled with the same SS_N and SCLK
            OFFSET_WIDTH        : natural := 16;    -- Bit width of the offset value
            CONVERSION_WIDTH    : natural := 18;    -- Bit width of the conversion factor
            RES_LSB             : natural := 6;     -- LSB in the result vector of the multiplactor output
            RES_MSB             : natural := 23    -- MSB in the result vector of the multiplactor output
            
        );
        port (
            CLK         : in std_logic;
            RESET_N     : in std_logic;
            
            -- SPI ports
            CPHA        : in std_logic;
            CPOL        : in std_logic;
            SCLK        : out std_logic;
            SCLK_IN     : in std_logic;
            MISO        : in std_logic_vector(CHANNELS - 1 downto 0);
            SS_OUT_N    : out std_logic;
            SS_IN_N     : in std_logic;
            MANUAL      : in std_logic;
            ENABLE      : in std_logic;
            
            -- SPI config ports
            PRE_DELAY   : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
            POST_DELAY  : in std_logic_vector(C_DELAY_WIDTH - 1 downto 0);
            CLK_DIV     : in std_logic_vector(C_CLK_DIV_WIDTH - 1 downto 0);
            
            -- Control Ports
            SET_CONVERSION  : in std_logic;
            SET_OFFSET      : in std_logic;
            SET_SAMPLES     : in std_logic;
            SET_SAMPLE_TIME : in std_logic;
            SI_VALID        : out std_logic;
            RAW_VALID       : out std_logic;
            BUSY            : out std_logic;
            
            -- Value Ports
            VALUE           : in std_logic_vector(31 downto 0);           -- input for conversion or offset value
            CHANNEL_SELECT  : in std_logic_vector(31 downto 0); -- selection which channels shall be updated with conversion factor or offset
            SI_VALUE        : out std_logic_vector((CHANNELS * (RES_MSB - RES_LSB + 1)) - 1 downto 0);
            RAW_VALUE       : out std_logic_vector((CHANNELS * DATA_WIDTH) - 1 downto 0);
            SAMPLE_COUNTER  : out std_logic_vector(31 downto 0)
            
        );
    end component ADC_CONTROLLER;
        
    function IS_BUSY (
        BUSY_VECTOR         : in std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0);
        SELECTION_VECTOR    : in std_logic_vector(C_C_S_AXI_DATA_WIDTH - 1 downto 0)
    ) return boolean is
        variable V_IS_BUSY : boolean;
    begin
        V_IS_BUSY := false;
        for i in SPI_MASTER - 1 downto 0 loop
           if(SELECTION_VECTOR(i) = '1') and (BUSY_VECTOR(i) = '1') then
               V_IS_BUSY := true;
           end if;
       end loop;
       
       return V_IS_BUSY;
    end function;
    
begin

    -- Add user logic here
    
    -- concurrent signal assignements
    S_CLK_DIV     <= S_ADC_SPI_CFGR(C_CLK_DIV_WIDTH - 1 downto 0);
    S_PRE_DELAY   <= S_ADC_SPI_CFGR(C_CLK_DIV_WIDTH + C_DELAY_WIDTH - 1 downto C_CLK_DIV_WIDTH);
    S_POST_DELAY  <= S_ADC_SPI_CFGR(C_CLK_DIV_WIDTH + 2 * C_DELAY_WIDTH - 1 downto C_CLK_DIV_WIDTH + C_DELAY_WIDTH);
    SI_VALID      <= S_ADC_MASTER_SI_FINISH(SPI_MASTER - 1 downto 0);
    RAW_VALID     <= S_ADC_MASTER_FINISH(SPI_MASTER - 1 downto 0);
    S_CPHA        <= S_ADC_SPI_CR(C_SPI_CPHA);
    S_CPOL        <= S_ADC_SPI_CR(C_SPI_CPOL);
    
    S_RESET_N     <= s00_axi_aresetn and (not S_ADC_CR(C_SW_RESET));
    
    -- Clock for AXI interface are the global signals for the whole IP core 
    S_CLK         <= s00_axi_aclk;
    
    -- sequential logic
    
    output_state_mem: process(S_CLK)
    begin
        if rising_edge(S_CLK) then
        
            if (S_RESET_N = '0') then
                S_ADC_CR_IN(C_TRIGGER) <= '1';
                S_ENABLE <= (others => '0');
                S_SPI_MANUAL <= (others => '0');
                S_ADC_SPI_CR_IN(C_SPI_CONTROL_STATUS) <= '0';
                curstate <= TRIGGERED;
                S_TRIGGER_CNV_PIPE <= (others => '0');
            else
                S_TRIGGER_CNV_PIPE <= TRIGGER_CNV;
                curstate <= nxtstate;
                case nxtstate is
                    when TRIGGERED =>
                        S_ADC_SPI_CR_IN(C_SPI_CONTROL_STATUS) <= '0';
                        S_SPI_MANUAL <= (others => '0');
                        
                        if (S_ADC_CR(C_SW_TRIGGER) = '0') then
                            -- check for rising edge on HW port
                            for i in SPI_MASTER - 1 downto 0 loop
                               if((S_TRIGGER_CNV_PIPE(i) = '0') and TRIGGER_CNV(i) = '1') then
                                   -- ADC_AVAILABLE is high activ ->
                                   -- if trigger event occurs TRIGGER_CNV == '1'
                                   -- S_ENABLE <= TRIGGER_CNV(i) and S_ADC_AVAILABLE(i)
                                   -- which is equivilant to S_ADC_AVAILABLE(i) because TRIGGER_CNV is always high  
                                   S_ENABLE(i) <= S_ADC_AVAILABLE(i);
                               else
                                   S_ENABLE(i) <= '0';
                               end if;
                           end loop;
                           
                       -- Triggered by AXI register
                       else
                            if (S_ADC_CR(C_TRIGGER) = '1') then
               
                                if (IS_BUSY(S_ADC_MASTER_BUSY, S_ADC_MASTER_CHANNEL) = false) then
                                    S_ENABLE <= (S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0) and S_ADC_AVAILABLE(SPI_MASTER - 1 downto 0));
                                    S_ADC_CR_IN(C_TRIGGER) <= '0';
                                end if;
                                
                            else
                                S_ENABLE <= (others => '0');
                            end if;
                       end if;
                    when CONTINUOUS =>
                        S_ADC_SPI_CR_IN(C_SPI_CONTROL_STATUS) <= '0';
                        S_ENABLE <= (S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0) and S_ADC_AVAILABLE(SPI_MASTER - 1 downto 0));
                        S_SPI_MANUAL <= (others => '0');
                    
                    when SPI_MANUAL =>
                        S_ENABLE <= (others => '0');
                        S_ADC_SPI_CR_IN(C_SPI_CONTROL_STATUS) <= '1';
                        S_ADC_SPI_CR_IN(C_SPI_SS_N_STATUS) <= S_ADC_SPI_CR(C_SPI_SS_N);
                        S_ADC_SPI_CR_IN(C_SPI_SCLK_STATUS) <= S_ADC_SPI_CR(C_SPI_SCLK);
                        S_SPI_MANUAL <= S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0);

                        for i in SPI_MASTER - 1 downto 0 loop
                            if(S_ADC_MASTER_CHANNEL(i) = '1') then
                                S_SCLK_IN(i)                       <= S_ADC_SPI_CR(C_SPI_SCLK);                        
                                S_SS_IN_N(i)                       <= S_ADC_SPI_CR(C_SPI_SS_N);
                            end if;
                        end loop;
                    
                    when others => curstate <= TRIGGERED;
                    report "Undecoded State" severity note;
                end case;
            end if;
        end if;
    end process output_state_mem;
    
    transition: process(curstate, S_ADC_MASTER_BUSY, S_ADC_MASTER_CHANNEL, S_ADC_CR, S_ADC_SPI_CR)
    begin
        case curstate is
            when TRIGGERED =>
                if ((IS_BUSY(S_ADC_MASTER_BUSY, S_ADC_MASTER_CHANNEL) = false) and (S_ADC_SPI_CR(C_SPI_CONTROL) = '1')) then
                    nxtstate <= SPI_MANUAL;
                elsif (S_ADC_CR(C_MODE) = '1') then
                    nxtstate <= CONTINUOUS;
                else
                    nxtstate <= TRIGGERED;
                end if;
            when CONTINUOUS =>
                if (S_ADC_CR(C_MODE) = '0') then 
                    nxtstate <= TRIGGERED;
                else 
                    nxtstate <= CONTINUOUS;
                end if;
            when SPI_MANUAL =>
                if ((S_ADC_SPI_CR(C_SPI_CONTROL) = '0') and (S_ADC_CR(C_MODE) = '0')) then
                    nxtstate <= TRIGGERED;
                elsif ((S_ADC_SPI_CR(C_SPI_CONTROL) = '0') and (S_ADC_CR(C_MODE) = '1')) then
                    nxtstate <= CONTINUOUS;
                else
                    nxtstate <= SPI_MANUAL;
                end if;
           when others => nxtstate <= TRIGGERED;
           report "Undecoded State" severity note;
       end case;
    end process transition;
	
	-- setting offset and conversion is independent of the other operation modes
	
	proc_set_conversion: process(S_CLK)
	begin
        if rising_edge(S_CLK) then
            
           if (S_RESET_N = '0') then
               S_SET_CONVERSION <= (others => '0');
               S_SET_OFFSET <= (others => '0');
               S_ADC_CR_IN(C_CONV_VALUE_VALID) <= '1';
           
           elsif (S_ADC_CR(C_CONV_VALUE_VALID) = '1') then
               -- reset the update request
               S_ADC_CR_IN(C_CONV_VALUE_VALID) <= '0';
               
               -- update the values
               
               S_SET_OFFSET     <= (others => '0');
               S_SET_CONVERSION <= (others => '0');
               S_SET_SAMPLES    <= (others => '0');
               
               case S_ADC_CR(C_CONFIG_VALUE_MSB downto C_CONFIG_VALUE_LSB) is
                    when "000" =>
                        S_SET_OFFSET     <= S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0);
                    when "001" =>
                        S_SET_CONVERSION <= S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0);
                    when "010" =>
                        S_SET_SAMPLES    <= S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0);
                    when "011" =>
                        S_SET_SAMPLE_TIME <= S_ADC_MASTER_CHANNEL(SPI_MASTER - 1 downto 0);
                    when others =>
                        S_SET_OFFSET     <= (others => '0');
                        S_SET_CONVERSION <= (others => '0');
                        S_SET_SAMPLES    <= (others => '0');
                        S_SET_SAMPLE_TIME <= (others => '0');
               end case;
            else
               S_ADC_CR_IN(C_CONV_VALUE_VALID)  <= '1';
               S_SET_CONVERSION                 <= (others => '0');
               S_SET_OFFSET                     <= (others => '0');
               S_SET_SAMPLES                    <= (others => '0');
            end if;
         end if;
               
	end process proc_set_conversion;
	
	-- User logic ends

-- Instantiation of Axi Bus Interface S00_AXI
ADC_LTC2311_v3_0_S00_AXI_inst : ADC_LTC2311_v3_0_S00_AXI
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
	    -- AXI registers
	    P_ADC_CR	                 => S_ADC_CR,
	    P_ADC_CR_IN	                 => S_ADC_CR_IN,
        P_ADC_SPI_CR	             => S_ADC_SPI_CR,
        P_ADC_SPI_CR_IN	             => S_ADC_SPI_CR_IN,
        P_ADC_SPI_CFGR	             => S_ADC_SPI_CFGR,
        P_ADC_MASTER_CHANNEL	     => S_ADC_MASTER_CHANNEL,
        P_ADC_CHANNEL	             => S_ADC_CHANNEL,
        P_ADC_MASTER_FINISH	         => S_ADC_MASTER_FINISH,
        P_ADC_MASTER_SI_FINISH	     => S_ADC_MASTER_SI_FINISH,
        P_ADC_MASTER_BUSY	         => S_ADC_MASTER_BUSY,
        P_ADC_CONV_VALUE	         => S_ADC_CONV_VALUE,
        P_ADC_AVAILABLE              => S_ADC_AVAILABLE,
	    -- AXI Ports
		S_AXI_ACLK	=> s00_axi_aclk,
		S_AXI_ARESETN	=> S_RESET_N,
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
	
	-- instantiation of the ADC channels
	
	GEN_ADC_CONT: for i in 0 to SPI_MASTER - 1 generate
	   inst_adc: ADC_CONTROLLER
	   generic map(
	        DATA_WIDTH          => DATA_WIDTH,              -- Number of bits per SPI frame
            CHANNELS            => CHANNELS_PER_MASTER,     -- Number of slaves that are controlled with the same SS_N and SCLK
            OFFSET_WIDTH        => OFFSET_WIDTH,            -- Bit width of the offset value
            CONVERSION_WIDTH    => CONVERSION_WIDTH,        -- Bit width of the conversion factor
            RES_LSB             => RES_LSB,                 -- LSB in the result vector of the multiplactor output
            RES_MSB             => RES_MSB                 -- MSB in the result vector of the multiplactor output
	   )
	   
	   port map(
	        CLK         => S_CLK,
            RESET_N     => S_RESET_N,
            
            -- SPI ports
            CPHA        => S_CPHA,
            CPOL        => S_CPOL,
            SCLK        => S_SCLK(i),
            SCLK_IN     => S_SCLK_IN(i),
            MISO        => S_MISO((i + 1) * CHANNELS_PER_MASTER - 1 downto i * CHANNELS_PER_MASTER),
            SS_OUT_N    => SS_N(i),
            SS_IN_N     => S_SS_IN_N(i),
            MANUAL      => S_SPI_MANUAL(i),
            ENABLE      => S_ENABLE(i),
            
            -- SPI config ports
            PRE_DELAY   => S_PRE_DELAY,
            POST_DELAY  => S_POST_DELAY,
            CLK_DIV     => S_CLK_DIV,
            
            -- Control Ports
            SET_CONVERSION  => S_SET_CONVERSION(i),
            SET_OFFSET      => S_SET_OFFSET(i),
            SET_SAMPLES     => S_SET_SAMPLES(i),
            SET_SAMPLE_TIME => S_SET_SAMPLE_TIME(i),
            SI_VALID        => S_ADC_MASTER_SI_FINISH(i),
            RAW_VALID       => S_ADC_MASTER_FINISH(i),
            BUSY            => S_ADC_MASTER_BUSY(i),
            
            -- Value Ports
            VALUE  => S_ADC_CONV_VALUE,           -- input for conversion or offset value
            CHANNEL_SELECT  => S_ADC_CHANNEL, -- selection which channels shall be updated with conversion factor or offset
            SI_VALUE        => SI_VALUE( (i + 1) * CHANNELS_PER_MASTER * (RES_MSB - RES_LSB + 1) - 1 downto i * CHANNELS_PER_MASTER * (RES_MSB - RES_LSB + 1)),
            RAW_VALUE       => RAW_VALUE( (i + 1) * CHANNELS_PER_MASTER * DATA_WIDTH - 1 downto i * CHANNELS_PER_MASTER * DATA_WIDTH),
            SAMPLE_COUNTER  => SAMPLE_COUNTER( (i + 1) * C_S00_AXI_DATA_WIDTH - 1 downto i * C_S00_AXI_DATA_WIDTH)
	   );
	end generate GEN_ADC_CONT;


    -- Generate differential output buffers
    gen_diff: if DIFFERENTIAL = true generate
        gen_diff1: for i in 0 to SPI_MASTER - 1 generate
            
            OBUFDS_inst : OBUFDS
                port map (   
                O => SCLK_DIFF(2 * i),   -- 1-bit output: Diff_p output (connect directly to top-level port)   
                OB => SCLK_DIFF(2 * i + 1), -- 1-bit output: Diff_n output (connect directly to top-level port)   
                I => S_SCLK(i)    -- 1-bit input: Buffer input
                );
                
            gen_diff2: for j in 0 to CHANNELS_PER_MASTER - 1 generate
            
                IBUFDS_inst : IBUFDS
                    generic map (DIFF_TERM=>TRUE)
                    port map (   
                    O => S_MISO(i * CHANNELS_PER_MASTER + j),   -- 1-bit output: Buffer output   
                    I => MISO_DIFF(2 * i * CHANNELS_PER_MASTER + 2 * j),   -- 1-bit input: Diff_p buffer input (connect directly to top-level port)   
                    IB => MISO_DIFF(2 * i * CHANNELS_PER_MASTER + 2 * j + 1)  -- 1-bit input: Diff_n buffer input (connect directly to top-level port)
                    );
                    
            end generate gen_diff2;
        end generate gen_diff1;
    end generate gen_diff;
    
    gen_single: if DIFFERENTIAL = false generate
        SCLK <= S_SCLK;
        S_MISO <= MISO;
    end generate gen_single;
    
    
end arch_imp;
