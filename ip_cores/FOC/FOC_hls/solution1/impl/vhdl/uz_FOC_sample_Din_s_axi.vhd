-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity uz_FOC_sample_Din_s_axi is
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
    interrupt             :out  STD_LOGIC;
    i_reference_Ampere    :out  STD_LOGIC_VECTOR(95 downto 0);
    self_i                :out  STD_LOGIC_VECTOR(255 downto 0);
    self_o                :in   STD_LOGIC_VECTOR(255 downto 0);
    self_o_ap_vld         :in   STD_LOGIC;
    i_actual_Ampere       :out  STD_LOGIC_VECTOR(95 downto 0);
    V_dc_volts            :out  STD_LOGIC_VECTOR(31 downto 0);
    omega_el_rad_per_sec  :out  STD_LOGIC_VECTOR(31 downto 0);
    ap_start              :out  STD_LOGIC;
    ap_done               :in   STD_LOGIC;
    ap_ready              :in   STD_LOGIC;
    ap_idle               :in   STD_LOGIC;
    Controller_id         :out  STD_LOGIC_VECTOR(159 downto 0);
    Controller_iq         :out  STD_LOGIC_VECTOR(159 downto 0)
);
end entity uz_FOC_sample_Din_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : Control signals
--        bit 0  - ap_start (Read/Write/COH)
--        bit 1  - ap_done (Read/COR)
--        bit 2  - ap_idle (Read)
--        bit 3  - ap_ready (Read)
--        bit 7  - auto_restart (Read/Write)
--        others - reserved
-- 0x04 : Global Interrupt Enable Register
--        bit 0  - Global Interrupt Enable (Read/Write)
--        others - reserved
-- 0x08 : IP Interrupt Enable Register (Read/Write)
--        bit 0  - enable ap_done interrupt (Read/Write)
--        bit 1  - enable ap_ready interrupt (Read/Write)
--        others - reserved
-- 0x0c : IP Interrupt Status Register (Read/TOW)
--        bit 0  - ap_done (COR/TOW)
--        bit 1  - ap_ready (COR/TOW)
--        others - reserved
-- 0x10 : Data signal of i_reference_Ampere
--        bit 31~0 - i_reference_Ampere[31:0] (Read/Write)
-- 0x14 : Data signal of i_reference_Ampere
--        bit 31~0 - i_reference_Ampere[63:32] (Read/Write)
-- 0x18 : Data signal of i_reference_Ampere
--        bit 31~0 - i_reference_Ampere[95:64] (Read/Write)
-- 0x1c : reserved
-- 0x20 : Data signal of self_i
--        bit 31~0 - self_i[31:0] (Read/Write)
-- 0x24 : Data signal of self_i
--        bit 31~0 - self_i[63:32] (Read/Write)
-- 0x28 : Data signal of self_i
--        bit 31~0 - self_i[95:64] (Read/Write)
-- 0x2c : Data signal of self_i
--        bit 31~0 - self_i[127:96] (Read/Write)
-- 0x30 : Data signal of self_i
--        bit 31~0 - self_i[159:128] (Read/Write)
-- 0x34 : Data signal of self_i
--        bit 31~0 - self_i[191:160] (Read/Write)
-- 0x38 : Data signal of self_i
--        bit 31~0 - self_i[223:192] (Read/Write)
-- 0x3c : Data signal of self_i
--        bit 31~0 - self_i[255:224] (Read/Write)
-- 0x40 : reserved
-- 0x44 : Data signal of self_o
--        bit 31~0 - self_o[31:0] (Read)
-- 0x48 : Data signal of self_o
--        bit 31~0 - self_o[63:32] (Read)
-- 0x4c : Data signal of self_o
--        bit 31~0 - self_o[95:64] (Read)
-- 0x50 : Data signal of self_o
--        bit 31~0 - self_o[127:96] (Read)
-- 0x54 : Data signal of self_o
--        bit 31~0 - self_o[159:128] (Read)
-- 0x58 : Data signal of self_o
--        bit 31~0 - self_o[191:160] (Read)
-- 0x5c : Data signal of self_o
--        bit 31~0 - self_o[223:192] (Read)
-- 0x60 : Data signal of self_o
--        bit 31~0 - self_o[255:224] (Read)
-- 0x64 : Control signal of self_o
--        bit 0  - self_o_ap_vld (Read/COR)
--        others - reserved
-- 0x70 : Data signal of i_actual_Ampere
--        bit 31~0 - i_actual_Ampere[31:0] (Read/Write)
-- 0x74 : Data signal of i_actual_Ampere
--        bit 31~0 - i_actual_Ampere[63:32] (Read/Write)
-- 0x78 : Data signal of i_actual_Ampere
--        bit 31~0 - i_actual_Ampere[95:64] (Read/Write)
-- 0x7c : reserved
-- 0x80 : Data signal of V_dc_volts
--        bit 31~0 - V_dc_volts[31:0] (Read/Write)
-- 0x84 : reserved
-- 0x88 : Data signal of omega_el_rad_per_sec
--        bit 31~0 - omega_el_rad_per_sec[31:0] (Read/Write)
-- 0x8c : reserved
-- 0x90 : Data signal of Controller_id
--        bit 31~0 - Controller_id[31:0] (Read/Write)
-- 0x94 : Data signal of Controller_id
--        bit 31~0 - Controller_id[63:32] (Read/Write)
-- 0x98 : Data signal of Controller_id
--        bit 31~0 - Controller_id[95:64] (Read/Write)
-- 0x9c : Data signal of Controller_id
--        bit 31~0 - Controller_id[127:96] (Read/Write)
-- 0xa0 : Data signal of Controller_id
--        bit 31~0 - Controller_id[159:128] (Read/Write)
-- 0xa4 : reserved
-- 0xa8 : Data signal of Controller_iq
--        bit 31~0 - Controller_iq[31:0] (Read/Write)
-- 0xac : Data signal of Controller_iq
--        bit 31~0 - Controller_iq[63:32] (Read/Write)
-- 0xb0 : Data signal of Controller_iq
--        bit 31~0 - Controller_iq[95:64] (Read/Write)
-- 0xb4 : Data signal of Controller_iq
--        bit 31~0 - Controller_iq[127:96] (Read/Write)
-- 0xb8 : Data signal of Controller_iq
--        bit 31~0 - Controller_iq[159:128] (Read/Write)
-- 0xbc : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of uz_FOC_sample_Din_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_AP_CTRL                     : INTEGER := 16#00#;
    constant ADDR_GIE                         : INTEGER := 16#04#;
    constant ADDR_IER                         : INTEGER := 16#08#;
    constant ADDR_ISR                         : INTEGER := 16#0c#;
    constant ADDR_I_REFERENCE_AMPERE_DATA_0   : INTEGER := 16#10#;
    constant ADDR_I_REFERENCE_AMPERE_DATA_1   : INTEGER := 16#14#;
    constant ADDR_I_REFERENCE_AMPERE_DATA_2   : INTEGER := 16#18#;
    constant ADDR_I_REFERENCE_AMPERE_CTRL     : INTEGER := 16#1c#;
    constant ADDR_SELF_I_DATA_0               : INTEGER := 16#20#;
    constant ADDR_SELF_I_DATA_1               : INTEGER := 16#24#;
    constant ADDR_SELF_I_DATA_2               : INTEGER := 16#28#;
    constant ADDR_SELF_I_DATA_3               : INTEGER := 16#2c#;
    constant ADDR_SELF_I_DATA_4               : INTEGER := 16#30#;
    constant ADDR_SELF_I_DATA_5               : INTEGER := 16#34#;
    constant ADDR_SELF_I_DATA_6               : INTEGER := 16#38#;
    constant ADDR_SELF_I_DATA_7               : INTEGER := 16#3c#;
    constant ADDR_SELF_I_CTRL                 : INTEGER := 16#40#;
    constant ADDR_SELF_O_DATA_0               : INTEGER := 16#44#;
    constant ADDR_SELF_O_DATA_1               : INTEGER := 16#48#;
    constant ADDR_SELF_O_DATA_2               : INTEGER := 16#4c#;
    constant ADDR_SELF_O_DATA_3               : INTEGER := 16#50#;
    constant ADDR_SELF_O_DATA_4               : INTEGER := 16#54#;
    constant ADDR_SELF_O_DATA_5               : INTEGER := 16#58#;
    constant ADDR_SELF_O_DATA_6               : INTEGER := 16#5c#;
    constant ADDR_SELF_O_DATA_7               : INTEGER := 16#60#;
    constant ADDR_SELF_O_CTRL                 : INTEGER := 16#64#;
    constant ADDR_I_ACTUAL_AMPERE_DATA_0      : INTEGER := 16#70#;
    constant ADDR_I_ACTUAL_AMPERE_DATA_1      : INTEGER := 16#74#;
    constant ADDR_I_ACTUAL_AMPERE_DATA_2      : INTEGER := 16#78#;
    constant ADDR_I_ACTUAL_AMPERE_CTRL        : INTEGER := 16#7c#;
    constant ADDR_V_DC_VOLTS_DATA_0           : INTEGER := 16#80#;
    constant ADDR_V_DC_VOLTS_CTRL             : INTEGER := 16#84#;
    constant ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0 : INTEGER := 16#88#;
    constant ADDR_OMEGA_EL_RAD_PER_SEC_CTRL   : INTEGER := 16#8c#;
    constant ADDR_CONTROLLER_ID_DATA_0        : INTEGER := 16#90#;
    constant ADDR_CONTROLLER_ID_DATA_1        : INTEGER := 16#94#;
    constant ADDR_CONTROLLER_ID_DATA_2        : INTEGER := 16#98#;
    constant ADDR_CONTROLLER_ID_DATA_3        : INTEGER := 16#9c#;
    constant ADDR_CONTROLLER_ID_DATA_4        : INTEGER := 16#a0#;
    constant ADDR_CONTROLLER_ID_CTRL          : INTEGER := 16#a4#;
    constant ADDR_CONTROLLER_IQ_DATA_0        : INTEGER := 16#a8#;
    constant ADDR_CONTROLLER_IQ_DATA_1        : INTEGER := 16#ac#;
    constant ADDR_CONTROLLER_IQ_DATA_2        : INTEGER := 16#b0#;
    constant ADDR_CONTROLLER_IQ_DATA_3        : INTEGER := 16#b4#;
    constant ADDR_CONTROLLER_IQ_DATA_4        : INTEGER := 16#b8#;
    constant ADDR_CONTROLLER_IQ_CTRL          : INTEGER := 16#bc#;
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
    signal int_ap_idle         : STD_LOGIC;
    signal int_ap_ready        : STD_LOGIC;
    signal int_ap_done         : STD_LOGIC := '0';
    signal int_ap_start        : STD_LOGIC := '0';
    signal int_auto_restart    : STD_LOGIC := '0';
    signal int_gie             : STD_LOGIC := '0';
    signal int_ier             : UNSIGNED(1 downto 0) := (others => '0');
    signal int_isr             : UNSIGNED(1 downto 0) := (others => '0');
    signal int_i_reference_Ampere : UNSIGNED(95 downto 0) := (others => '0');
    signal int_self_i          : UNSIGNED(255 downto 0) := (others => '0');
    signal int_self_o          : UNSIGNED(255 downto 0) := (others => '0');
    signal int_self_o_ap_vld   : STD_LOGIC;
    signal int_i_actual_Ampere : UNSIGNED(95 downto 0) := (others => '0');
    signal int_V_dc_volts      : UNSIGNED(31 downto 0) := (others => '0');
    signal int_omega_el_rad_per_sec : UNSIGNED(31 downto 0) := (others => '0');
    signal int_Controller_id   : UNSIGNED(159 downto 0) := (others => '0');
    signal int_Controller_iq   : UNSIGNED(159 downto 0) := (others => '0');


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
                    when ADDR_AP_CTRL =>
                        rdata_data(7) <= int_auto_restart;
                        rdata_data(3) <= int_ap_ready;
                        rdata_data(2) <= int_ap_idle;
                        rdata_data(1) <= int_ap_done;
                        rdata_data(0) <= int_ap_start;
                    when ADDR_GIE =>
                        rdata_data(0) <= int_gie;
                    when ADDR_IER =>
                        rdata_data(1 downto 0) <= int_ier;
                    when ADDR_ISR =>
                        rdata_data(1 downto 0) <= int_isr;
                    when ADDR_I_REFERENCE_AMPERE_DATA_0 =>
                        rdata_data <= RESIZE(int_i_reference_Ampere(31 downto 0), 32);
                    when ADDR_I_REFERENCE_AMPERE_DATA_1 =>
                        rdata_data <= RESIZE(int_i_reference_Ampere(63 downto 32), 32);
                    when ADDR_I_REFERENCE_AMPERE_DATA_2 =>
                        rdata_data <= RESIZE(int_i_reference_Ampere(95 downto 64), 32);
                    when ADDR_SELF_I_DATA_0 =>
                        rdata_data <= RESIZE(int_self_i(31 downto 0), 32);
                    when ADDR_SELF_I_DATA_1 =>
                        rdata_data <= RESIZE(int_self_i(63 downto 32), 32);
                    when ADDR_SELF_I_DATA_2 =>
                        rdata_data <= RESIZE(int_self_i(95 downto 64), 32);
                    when ADDR_SELF_I_DATA_3 =>
                        rdata_data <= RESIZE(int_self_i(127 downto 96), 32);
                    when ADDR_SELF_I_DATA_4 =>
                        rdata_data <= RESIZE(int_self_i(159 downto 128), 32);
                    when ADDR_SELF_I_DATA_5 =>
                        rdata_data <= RESIZE(int_self_i(191 downto 160), 32);
                    when ADDR_SELF_I_DATA_6 =>
                        rdata_data <= RESIZE(int_self_i(223 downto 192), 32);
                    when ADDR_SELF_I_DATA_7 =>
                        rdata_data <= RESIZE(int_self_i(255 downto 224), 32);
                    when ADDR_SELF_O_DATA_0 =>
                        rdata_data <= RESIZE(int_self_o(31 downto 0), 32);
                    when ADDR_SELF_O_DATA_1 =>
                        rdata_data <= RESIZE(int_self_o(63 downto 32), 32);
                    when ADDR_SELF_O_DATA_2 =>
                        rdata_data <= RESIZE(int_self_o(95 downto 64), 32);
                    when ADDR_SELF_O_DATA_3 =>
                        rdata_data <= RESIZE(int_self_o(127 downto 96), 32);
                    when ADDR_SELF_O_DATA_4 =>
                        rdata_data <= RESIZE(int_self_o(159 downto 128), 32);
                    when ADDR_SELF_O_DATA_5 =>
                        rdata_data <= RESIZE(int_self_o(191 downto 160), 32);
                    when ADDR_SELF_O_DATA_6 =>
                        rdata_data <= RESIZE(int_self_o(223 downto 192), 32);
                    when ADDR_SELF_O_DATA_7 =>
                        rdata_data <= RESIZE(int_self_o(255 downto 224), 32);
                    when ADDR_SELF_O_CTRL =>
                        rdata_data(0) <= int_self_o_ap_vld;
                    when ADDR_I_ACTUAL_AMPERE_DATA_0 =>
                        rdata_data <= RESIZE(int_i_actual_Ampere(31 downto 0), 32);
                    when ADDR_I_ACTUAL_AMPERE_DATA_1 =>
                        rdata_data <= RESIZE(int_i_actual_Ampere(63 downto 32), 32);
                    when ADDR_I_ACTUAL_AMPERE_DATA_2 =>
                        rdata_data <= RESIZE(int_i_actual_Ampere(95 downto 64), 32);
                    when ADDR_V_DC_VOLTS_DATA_0 =>
                        rdata_data <= RESIZE(int_V_dc_volts(31 downto 0), 32);
                    when ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0 =>
                        rdata_data <= RESIZE(int_omega_el_rad_per_sec(31 downto 0), 32);
                    when ADDR_CONTROLLER_ID_DATA_0 =>
                        rdata_data <= RESIZE(int_Controller_id(31 downto 0), 32);
                    when ADDR_CONTROLLER_ID_DATA_1 =>
                        rdata_data <= RESIZE(int_Controller_id(63 downto 32), 32);
                    when ADDR_CONTROLLER_ID_DATA_2 =>
                        rdata_data <= RESIZE(int_Controller_id(95 downto 64), 32);
                    when ADDR_CONTROLLER_ID_DATA_3 =>
                        rdata_data <= RESIZE(int_Controller_id(127 downto 96), 32);
                    when ADDR_CONTROLLER_ID_DATA_4 =>
                        rdata_data <= RESIZE(int_Controller_id(159 downto 128), 32);
                    when ADDR_CONTROLLER_IQ_DATA_0 =>
                        rdata_data <= RESIZE(int_Controller_iq(31 downto 0), 32);
                    when ADDR_CONTROLLER_IQ_DATA_1 =>
                        rdata_data <= RESIZE(int_Controller_iq(63 downto 32), 32);
                    when ADDR_CONTROLLER_IQ_DATA_2 =>
                        rdata_data <= RESIZE(int_Controller_iq(95 downto 64), 32);
                    when ADDR_CONTROLLER_IQ_DATA_3 =>
                        rdata_data <= RESIZE(int_Controller_iq(127 downto 96), 32);
                    when ADDR_CONTROLLER_IQ_DATA_4 =>
                        rdata_data <= RESIZE(int_Controller_iq(159 downto 128), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    interrupt            <= int_gie and (int_isr(0) or int_isr(1));
    ap_start             <= int_ap_start;
    i_reference_Ampere   <= STD_LOGIC_VECTOR(int_i_reference_Ampere);
    self_i               <= STD_LOGIC_VECTOR(int_self_i);
    i_actual_Ampere      <= STD_LOGIC_VECTOR(int_i_actual_Ampere);
    V_dc_volts           <= STD_LOGIC_VECTOR(int_V_dc_volts);
    omega_el_rad_per_sec <= STD_LOGIC_VECTOR(int_omega_el_rad_per_sec);
    Controller_id        <= STD_LOGIC_VECTOR(int_Controller_id);
    Controller_iq        <= STD_LOGIC_VECTOR(int_Controller_iq);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_start <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1' and WDATA(0) = '1') then
                    int_ap_start <= '1';
                elsif (ap_ready = '1') then
                    int_ap_start <= int_auto_restart; -- clear on handshake/auto restart
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_done <= '0';
            elsif (ACLK_EN = '1') then
                if (ap_done = '1') then
                    int_ap_done <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AP_CTRL) then
                    int_ap_done <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_idle <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_idle <= ap_idle;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_ready <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_ready <= ap_ready;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_auto_restart <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1') then
                    int_auto_restart <= WDATA(7);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_gie <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_GIE and WSTRB(0) = '1') then
                    int_gie <= WDATA(0);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ier <= "00";
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IER and WSTRB(0) = '1') then
                    int_ier <= UNSIGNED(WDATA(1 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_isr(0) <= '0';
            elsif (ACLK_EN = '1') then
                if (int_ier(0) = '1' and ap_done = '1') then
                    int_isr(0) <= '1';
                elsif (w_hs = '1' and waddr = ADDR_ISR and WSTRB(0) = '1') then
                    int_isr(0) <= int_isr(0) xor WDATA(0); -- toggle on write
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_isr(1) <= '0';
            elsif (ACLK_EN = '1') then
                if (int_ier(1) = '1' and ap_ready = '1') then
                    int_isr(1) <= '1';
                elsif (w_hs = '1' and waddr = ADDR_ISR and WSTRB(0) = '1') then
                    int_isr(1) <= int_isr(1) xor WDATA(1); -- toggle on write
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_REFERENCE_AMPERE_DATA_0) then
                    int_i_reference_Ampere(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_reference_Ampere(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_REFERENCE_AMPERE_DATA_1) then
                    int_i_reference_Ampere(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_reference_Ampere(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_REFERENCE_AMPERE_DATA_2) then
                    int_i_reference_Ampere(95 downto 64) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_reference_Ampere(95 downto 64));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_0) then
                    int_self_i(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_1) then
                    int_self_i(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_2) then
                    int_self_i(95 downto 64) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(95 downto 64));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_3) then
                    int_self_i(127 downto 96) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(127 downto 96));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_4) then
                    int_self_i(159 downto 128) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(159 downto 128));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_5) then
                    int_self_i(191 downto 160) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(191 downto 160));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_6) then
                    int_self_i(223 downto 192) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(223 downto 192));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SELF_I_DATA_7) then
                    int_self_i(255 downto 224) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_self_i(255 downto 224));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_self_o <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (self_o_ap_vld = '1') then
                    int_self_o <= UNSIGNED(self_o); -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_self_o_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (self_o_ap_vld = '1') then
                    int_self_o_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_SELF_O_CTRL) then
                    int_self_o_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_ACTUAL_AMPERE_DATA_0) then
                    int_i_actual_Ampere(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_actual_Ampere(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_ACTUAL_AMPERE_DATA_1) then
                    int_i_actual_Ampere(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_actual_Ampere(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_I_ACTUAL_AMPERE_DATA_2) then
                    int_i_actual_Ampere(95 downto 64) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_i_actual_Ampere(95 downto 64));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_V_DC_VOLTS_DATA_0) then
                    int_V_dc_volts(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_V_dc_volts(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0) then
                    int_omega_el_rad_per_sec(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_omega_el_rad_per_sec(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_ID_DATA_0) then
                    int_Controller_id(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_id(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_ID_DATA_1) then
                    int_Controller_id(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_id(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_ID_DATA_2) then
                    int_Controller_id(95 downto 64) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_id(95 downto 64));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_ID_DATA_3) then
                    int_Controller_id(127 downto 96) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_id(127 downto 96));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_ID_DATA_4) then
                    int_Controller_id(159 downto 128) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_id(159 downto 128));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_IQ_DATA_0) then
                    int_Controller_iq(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_iq(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_IQ_DATA_1) then
                    int_Controller_iq(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_iq(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_IQ_DATA_2) then
                    int_Controller_iq(95 downto 64) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_iq(95 downto 64));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_IQ_DATA_3) then
                    int_Controller_iq(127 downto 96) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_iq(127 downto 96));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_CONTROLLER_IQ_DATA_4) then
                    int_Controller_iq(159 downto 128) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_Controller_iq(159 downto 128));
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
