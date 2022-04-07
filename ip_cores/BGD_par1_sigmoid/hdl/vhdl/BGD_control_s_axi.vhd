-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity BGD_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 8;
    C_S_AXI_DATA_WIDTH    : INTEGER := 32);
port (
    ACLK                  :in   STD_LOGIC;
    ARESET                :in   STD_LOGIC;
    ACLK_EN               :in   STD_LOGIC;
    AWADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    AWVALID               :in   STD_LOGIC;
    AWREADY               :out  STD_LOGIC;
    WDATA                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    WSTRB                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH/8-1 downto 0);
    WVALID                :in   STD_LOGIC;
    WREADY                :out  STD_LOGIC;
    BRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    BVALID                :out  STD_LOGIC;
    BREADY                :in   STD_LOGIC;
    ARADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    ARVALID               :in   STD_LOGIC;
    ARREADY               :out  STD_LOGIC;
    RDATA                 :out  STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    RRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    RVALID                :out  STD_LOGIC;
    RREADY                :in   STD_LOGIC;
    axiMlpResultsInput    :out  STD_LOGIC_VECTOR(63 downto 0);
    axiClassesInput       :out  STD_LOGIC_VECTOR(63 downto 0);
    axiWeightInput        :out  STD_LOGIC_VECTOR(63 downto 0);
    axiBiasInput          :out  STD_LOGIC_VECTOR(63 downto 0);
    axiWeightOutput       :out  STD_LOGIC_VECTOR(63 downto 0);
    axiBiasOutput         :out  STD_LOGIC_VECTOR(63 downto 0);
    numberInputs          :out  STD_LOGIC_VECTOR(31 downto 0);
    numberOutputs         :out  STD_LOGIC_VECTOR(31 downto 0);
    numberLayers          :out  STD_LOGIC_VECTOR(31 downto 0);
    numberNeurons         :out  STD_LOGIC_VECTOR(31 downto 0);
    loadParameters        :out  STD_LOGIC_VECTOR(31 downto 0);
    batchSize             :out  STD_LOGIC_VECTOR(31 downto 0);
    learningRate          :out  STD_LOGIC_VECTOR(31 downto 0)
);
end entity BGD_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : reserved
-- 0x04 : reserved
-- 0x08 : reserved
-- 0x0c : reserved
-- 0x10 : Data signal of axiMlpResultsInput
--        bit 31~0 - axiMlpResultsInput[31:0] (Read/Write)
-- 0x14 : Data signal of axiMlpResultsInput
--        bit 31~0 - axiMlpResultsInput[63:32] (Read/Write)
-- 0x18 : reserved
-- 0x1c : Data signal of axiClassesInput
--        bit 31~0 - axiClassesInput[31:0] (Read/Write)
-- 0x20 : Data signal of axiClassesInput
--        bit 31~0 - axiClassesInput[63:32] (Read/Write)
-- 0x24 : reserved
-- 0x28 : Data signal of axiWeightInput
--        bit 31~0 - axiWeightInput[31:0] (Read/Write)
-- 0x2c : Data signal of axiWeightInput
--        bit 31~0 - axiWeightInput[63:32] (Read/Write)
-- 0x30 : reserved
-- 0x34 : Data signal of axiBiasInput
--        bit 31~0 - axiBiasInput[31:0] (Read/Write)
-- 0x38 : Data signal of axiBiasInput
--        bit 31~0 - axiBiasInput[63:32] (Read/Write)
-- 0x3c : reserved
-- 0x40 : Data signal of axiWeightOutput
--        bit 31~0 - axiWeightOutput[31:0] (Read/Write)
-- 0x44 : Data signal of axiWeightOutput
--        bit 31~0 - axiWeightOutput[63:32] (Read/Write)
-- 0x48 : reserved
-- 0x4c : Data signal of axiBiasOutput
--        bit 31~0 - axiBiasOutput[31:0] (Read/Write)
-- 0x50 : Data signal of axiBiasOutput
--        bit 31~0 - axiBiasOutput[63:32] (Read/Write)
-- 0x54 : reserved
-- 0x58 : Data signal of numberInputs
--        bit 31~0 - numberInputs[31:0] (Read/Write)
-- 0x5c : reserved
-- 0x60 : Data signal of numberOutputs
--        bit 31~0 - numberOutputs[31:0] (Read/Write)
-- 0x64 : reserved
-- 0x68 : Data signal of numberLayers
--        bit 31~0 - numberLayers[31:0] (Read/Write)
-- 0x6c : reserved
-- 0x70 : Data signal of numberNeurons
--        bit 31~0 - numberNeurons[31:0] (Read/Write)
-- 0x74 : reserved
-- 0x78 : Data signal of loadParameters
--        bit 31~0 - loadParameters[31:0] (Read/Write)
-- 0x7c : reserved
-- 0x80 : Data signal of batchSize
--        bit 31~0 - batchSize[31:0] (Read/Write)
-- 0x84 : reserved
-- 0x88 : Data signal of learningRate
--        bit 31~0 - learningRate[31:0] (Read/Write)
-- 0x8c : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of BGD_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_AXIMLPRESULTSINPUT_DATA_0 : INTEGER := 16#10#;
    constant ADDR_AXIMLPRESULTSINPUT_DATA_1 : INTEGER := 16#14#;
    constant ADDR_AXIMLPRESULTSINPUT_CTRL   : INTEGER := 16#18#;
    constant ADDR_AXICLASSESINPUT_DATA_0    : INTEGER := 16#1c#;
    constant ADDR_AXICLASSESINPUT_DATA_1    : INTEGER := 16#20#;
    constant ADDR_AXICLASSESINPUT_CTRL      : INTEGER := 16#24#;
    constant ADDR_AXIWEIGHTINPUT_DATA_0     : INTEGER := 16#28#;
    constant ADDR_AXIWEIGHTINPUT_DATA_1     : INTEGER := 16#2c#;
    constant ADDR_AXIWEIGHTINPUT_CTRL       : INTEGER := 16#30#;
    constant ADDR_AXIBIASINPUT_DATA_0       : INTEGER := 16#34#;
    constant ADDR_AXIBIASINPUT_DATA_1       : INTEGER := 16#38#;
    constant ADDR_AXIBIASINPUT_CTRL         : INTEGER := 16#3c#;
    constant ADDR_AXIWEIGHTOUTPUT_DATA_0    : INTEGER := 16#40#;
    constant ADDR_AXIWEIGHTOUTPUT_DATA_1    : INTEGER := 16#44#;
    constant ADDR_AXIWEIGHTOUTPUT_CTRL      : INTEGER := 16#48#;
    constant ADDR_AXIBIASOUTPUT_DATA_0      : INTEGER := 16#4c#;
    constant ADDR_AXIBIASOUTPUT_DATA_1      : INTEGER := 16#50#;
    constant ADDR_AXIBIASOUTPUT_CTRL        : INTEGER := 16#54#;
    constant ADDR_NUMBERINPUTS_DATA_0       : INTEGER := 16#58#;
    constant ADDR_NUMBERINPUTS_CTRL         : INTEGER := 16#5c#;
    constant ADDR_NUMBEROUTPUTS_DATA_0      : INTEGER := 16#60#;
    constant ADDR_NUMBEROUTPUTS_CTRL        : INTEGER := 16#64#;
    constant ADDR_NUMBERLAYERS_DATA_0       : INTEGER := 16#68#;
    constant ADDR_NUMBERLAYERS_CTRL         : INTEGER := 16#6c#;
    constant ADDR_NUMBERNEURONS_DATA_0      : INTEGER := 16#70#;
    constant ADDR_NUMBERNEURONS_CTRL        : INTEGER := 16#74#;
    constant ADDR_LOADPARAMETERS_DATA_0     : INTEGER := 16#78#;
    constant ADDR_LOADPARAMETERS_CTRL       : INTEGER := 16#7c#;
    constant ADDR_BATCHSIZE_DATA_0          : INTEGER := 16#80#;
    constant ADDR_BATCHSIZE_CTRL            : INTEGER := 16#84#;
    constant ADDR_LEARNINGRATE_DATA_0       : INTEGER := 16#88#;
    constant ADDR_LEARNINGRATE_CTRL         : INTEGER := 16#8c#;
    constant ADDR_BITS         : INTEGER := 8;

    signal waddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal wmask               : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal aw_hs               : STD_LOGIC;
    signal w_hs                : STD_LOGIC;
    signal rdata_data          : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal ar_hs               : STD_LOGIC;
    signal raddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal AWREADY_t           : STD_LOGIC;
    signal WREADY_t            : STD_LOGIC;
    signal ARREADY_t           : STD_LOGIC;
    signal RVALID_t            : STD_LOGIC;
    -- internal registers
    signal int_axiMlpResultsInput : UNSIGNED(63 downto 0) := (others => '0');
    signal int_axiClassesInput : UNSIGNED(63 downto 0) := (others => '0');
    signal int_axiWeightInput  : UNSIGNED(63 downto 0) := (others => '0');
    signal int_axiBiasInput    : UNSIGNED(63 downto 0) := (others => '0');
    signal int_axiWeightOutput : UNSIGNED(63 downto 0) := (others => '0');
    signal int_axiBiasOutput   : UNSIGNED(63 downto 0) := (others => '0');
    signal int_numberInputs    : UNSIGNED(31 downto 0) := (others => '0');
    signal int_numberOutputs   : UNSIGNED(31 downto 0) := (others => '0');
    signal int_numberLayers    : UNSIGNED(31 downto 0) := (others => '0');
    signal int_numberNeurons   : UNSIGNED(31 downto 0) := (others => '0');
    signal int_loadParameters  : UNSIGNED(31 downto 0) := (others => '0');
    signal int_batchSize       : UNSIGNED(31 downto 0) := (others => '0');
    signal int_learningRate    : UNSIGNED(31 downto 0) := (others => '0');


begin
-- ----------------------- Instantiation------------------


-- ----------------------- AXI WRITE ---------------------
    AWREADY_t <=  '1' when wstate = wridle else '0';
    AWREADY   <=  AWREADY_t;
    WREADY_t  <=  '1' when wstate = wrdata else '0';
    WREADY    <=  WREADY_t;
    BRESP     <=  "00";  -- OKAY
    BVALID    <=  '1' when wstate = wrresp else '0';
    wmask     <=  (31 downto 24 => WSTRB(3), 23 downto 16 => WSTRB(2), 15 downto 8 => WSTRB(1), 7 downto 0 => WSTRB(0));
    aw_hs     <=  AWVALID and AWREADY_t;
    w_hs      <=  WVALID and WREADY_t;

    -- write FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                wstate <= wrreset;
            elsif (ACLK_EN = '1') then
                wstate <= wnext;
            end if;
        end if;
    end process;

    process (wstate, AWVALID, WVALID, BREADY)
    begin
        case (wstate) is
        when wridle =>
            if (AWVALID = '1') then
                wnext <= wrdata;
            else
                wnext <= wridle;
            end if;
        when wrdata =>
            if (WVALID = '1') then
                wnext <= wrresp;
            else
                wnext <= wrdata;
            end if;
        when wrresp =>
            if (BREADY = '1') then
                wnext <= wridle;
            else
                wnext <= wrresp;
            end if;
        when others =>
            wnext <= wridle;
        end case;
    end process;

    waddr_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (aw_hs = '1') then
                    waddr <= UNSIGNED(AWADDR(ADDR_BITS-1 downto 0));
                end if;
            end if;
        end if;
    end process;

-- ----------------------- AXI READ ----------------------
    ARREADY_t <= '1' when (rstate = rdidle) else '0';
    ARREADY <= ARREADY_t;
    RDATA   <= STD_LOGIC_VECTOR(rdata_data);
    RRESP   <= "00";  -- OKAY
    RVALID_t  <= '1' when (rstate = rddata) else '0';
    RVALID    <= RVALID_t;
    ar_hs   <= ARVALID and ARREADY_t;
    raddr   <= UNSIGNED(ARADDR(ADDR_BITS-1 downto 0));

    -- read FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                rstate <= rdreset;
            elsif (ACLK_EN = '1') then
                rstate <= rnext;
            end if;
        end if;
    end process;

    process (rstate, ARVALID, RREADY, RVALID_t)
    begin
        case (rstate) is
        when rdidle =>
            if (ARVALID = '1') then
                rnext <= rddata;
            else
                rnext <= rdidle;
            end if;
        when rddata =>
            if (RREADY = '1' and RVALID_t = '1') then
                rnext <= rdidle;
            else
                rnext <= rddata;
            end if;
        when others =>
            rnext <= rdidle;
        end case;
    end process;

    rdata_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (ar_hs = '1') then
                    rdata_data <= (others => '0');
                    case (TO_INTEGER(raddr)) is
                    when ADDR_AXIMLPRESULTSINPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiMlpResultsInput(31 downto 0), 32);
                    when ADDR_AXIMLPRESULTSINPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiMlpResultsInput(63 downto 32), 32);
                    when ADDR_AXICLASSESINPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiClassesInput(31 downto 0), 32);
                    when ADDR_AXICLASSESINPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiClassesInput(63 downto 32), 32);
                    when ADDR_AXIWEIGHTINPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiWeightInput(31 downto 0), 32);
                    when ADDR_AXIWEIGHTINPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiWeightInput(63 downto 32), 32);
                    when ADDR_AXIBIASINPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiBiasInput(31 downto 0), 32);
                    when ADDR_AXIBIASINPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiBiasInput(63 downto 32), 32);
                    when ADDR_AXIWEIGHTOUTPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiWeightOutput(31 downto 0), 32);
                    when ADDR_AXIWEIGHTOUTPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiWeightOutput(63 downto 32), 32);
                    when ADDR_AXIBIASOUTPUT_DATA_0 =>
                        rdata_data <= RESIZE(int_axiBiasOutput(31 downto 0), 32);
                    when ADDR_AXIBIASOUTPUT_DATA_1 =>
                        rdata_data <= RESIZE(int_axiBiasOutput(63 downto 32), 32);
                    when ADDR_NUMBERINPUTS_DATA_0 =>
                        rdata_data <= RESIZE(int_numberInputs(31 downto 0), 32);
                    when ADDR_NUMBEROUTPUTS_DATA_0 =>
                        rdata_data <= RESIZE(int_numberOutputs(31 downto 0), 32);
                    when ADDR_NUMBERLAYERS_DATA_0 =>
                        rdata_data <= RESIZE(int_numberLayers(31 downto 0), 32);
                    when ADDR_NUMBERNEURONS_DATA_0 =>
                        rdata_data <= RESIZE(int_numberNeurons(31 downto 0), 32);
                    when ADDR_LOADPARAMETERS_DATA_0 =>
                        rdata_data <= RESIZE(int_loadParameters(31 downto 0), 32);
                    when ADDR_BATCHSIZE_DATA_0 =>
                        rdata_data <= RESIZE(int_batchSize(31 downto 0), 32);
                    when ADDR_LEARNINGRATE_DATA_0 =>
                        rdata_data <= RESIZE(int_learningRate(31 downto 0), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    axiMlpResultsInput   <= STD_LOGIC_VECTOR(int_axiMlpResultsInput);
    axiClassesInput      <= STD_LOGIC_VECTOR(int_axiClassesInput);
    axiWeightInput       <= STD_LOGIC_VECTOR(int_axiWeightInput);
    axiBiasInput         <= STD_LOGIC_VECTOR(int_axiBiasInput);
    axiWeightOutput      <= STD_LOGIC_VECTOR(int_axiWeightOutput);
    axiBiasOutput        <= STD_LOGIC_VECTOR(int_axiBiasOutput);
    numberInputs         <= STD_LOGIC_VECTOR(int_numberInputs);
    numberOutputs        <= STD_LOGIC_VECTOR(int_numberOutputs);
    numberLayers         <= STD_LOGIC_VECTOR(int_numberLayers);
    numberNeurons        <= STD_LOGIC_VECTOR(int_numberNeurons);
    loadParameters       <= STD_LOGIC_VECTOR(int_loadParameters);
    batchSize            <= STD_LOGIC_VECTOR(int_batchSize);
    learningRate         <= STD_LOGIC_VECTOR(int_learningRate);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIMLPRESULTSINPUT_DATA_0) then
                    int_axiMlpResultsInput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiMlpResultsInput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIMLPRESULTSINPUT_DATA_1) then
                    int_axiMlpResultsInput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiMlpResultsInput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXICLASSESINPUT_DATA_0) then
                    int_axiClassesInput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiClassesInput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXICLASSESINPUT_DATA_1) then
                    int_axiClassesInput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiClassesInput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIWEIGHTINPUT_DATA_0) then
                    int_axiWeightInput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiWeightInput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIWEIGHTINPUT_DATA_1) then
                    int_axiWeightInput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiWeightInput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIBIASINPUT_DATA_0) then
                    int_axiBiasInput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiBiasInput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIBIASINPUT_DATA_1) then
                    int_axiBiasInput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiBiasInput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIWEIGHTOUTPUT_DATA_0) then
                    int_axiWeightOutput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiWeightOutput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIWEIGHTOUTPUT_DATA_1) then
                    int_axiWeightOutput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiWeightOutput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIBIASOUTPUT_DATA_0) then
                    int_axiBiasOutput(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiBiasOutput(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AXIBIASOUTPUT_DATA_1) then
                    int_axiBiasOutput(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_axiBiasOutput(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NUMBERINPUTS_DATA_0) then
                    int_numberInputs(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_numberInputs(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NUMBEROUTPUTS_DATA_0) then
                    int_numberOutputs(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_numberOutputs(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NUMBERLAYERS_DATA_0) then
                    int_numberLayers(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_numberLayers(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_NUMBERNEURONS_DATA_0) then
                    int_numberNeurons(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_numberNeurons(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_LOADPARAMETERS_DATA_0) then
                    int_loadParameters(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_loadParameters(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_BATCHSIZE_DATA_0) then
                    int_batchSize(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_batchSize(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_LEARNINGRATE_DATA_0) then
                    int_learningRate(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_learningRate(31 downto 0));
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
