-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Tool Version Limit: 2019.12
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity uz_FOC_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 7;
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
    sampletime            :out  STD_LOGIC_VECTOR(31 downto 0);
    set_i_d               :out  STD_LOGIC_VECTOR(31 downto 0);
    set_i_q               :out  STD_LOGIC_VECTOR(31 downto 0);
    KP_d                  :out  STD_LOGIC_VECTOR(31 downto 0);
    KI_d                  :out  STD_LOGIC_VECTOR(31 downto 0);
    KP_q                  :out  STD_LOGIC_VECTOR(31 downto 0);
    KI_q                  :out  STD_LOGIC_VECTOR(31 downto 0);
    reset_PS              :out  STD_LOGIC_VECTOR(0 downto 0);
    limit                 :out  STD_LOGIC_VECTOR(31 downto 0);
    out_KP_d              :in   STD_LOGIC_VECTOR(31 downto 0);
    out_KP_d_ap_vld       :in   STD_LOGIC;
    out_idref             :in   STD_LOGIC_VECTOR(31 downto 0);
    out_idref_ap_vld      :in   STD_LOGIC;
    out_status            :in   STD_LOGIC_VECTOR(0 downto 0);
    out_status_ap_vld     :in   STD_LOGIC
);
end entity uz_FOC_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : reserved
-- 0x04 : reserved
-- 0x08 : reserved
-- 0x0c : reserved
-- 0x10 : Data signal of sampletime
--        bit 31~0 - sampletime[31:0] (Read/Write)
-- 0x14 : reserved
-- 0x18 : Data signal of set_i_d
--        bit 31~0 - set_i_d[31:0] (Read/Write)
-- 0x1c : reserved
-- 0x20 : Data signal of set_i_q
--        bit 31~0 - set_i_q[31:0] (Read/Write)
-- 0x24 : reserved
-- 0x28 : Data signal of KP_d
--        bit 31~0 - KP_d[31:0] (Read/Write)
-- 0x2c : reserved
-- 0x30 : Data signal of KI_d
--        bit 31~0 - KI_d[31:0] (Read/Write)
-- 0x34 : reserved
-- 0x38 : Data signal of KP_q
--        bit 31~0 - KP_q[31:0] (Read/Write)
-- 0x3c : reserved
-- 0x40 : Data signal of KI_q
--        bit 31~0 - KI_q[31:0] (Read/Write)
-- 0x44 : reserved
-- 0x48 : Data signal of reset_PS
--        bit 0  - reset_PS[0] (Read/Write)
--        others - reserved
-- 0x4c : reserved
-- 0x50 : Data signal of limit
--        bit 31~0 - limit[31:0] (Read/Write)
-- 0x54 : reserved
-- 0x58 : Data signal of out_KP_d
--        bit 31~0 - out_KP_d[31:0] (Read)
-- 0x5c : Control signal of out_KP_d
--        bit 0  - out_KP_d_ap_vld (Read/COR)
--        others - reserved
-- 0x68 : Data signal of out_idref
--        bit 31~0 - out_idref[31:0] (Read)
-- 0x6c : Control signal of out_idref
--        bit 0  - out_idref_ap_vld (Read/COR)
--        others - reserved
-- 0x78 : Data signal of out_status
--        bit 0  - out_status[0] (Read)
--        others - reserved
-- 0x7c : Control signal of out_status
--        bit 0  - out_status_ap_vld (Read/COR)
--        others - reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of uz_FOC_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_SAMPLETIME_DATA_0 : INTEGER := 16#10#;
    constant ADDR_SAMPLETIME_CTRL   : INTEGER := 16#14#;
    constant ADDR_SET_I_D_DATA_0    : INTEGER := 16#18#;
    constant ADDR_SET_I_D_CTRL      : INTEGER := 16#1c#;
    constant ADDR_SET_I_Q_DATA_0    : INTEGER := 16#20#;
    constant ADDR_SET_I_Q_CTRL      : INTEGER := 16#24#;
    constant ADDR_KP_D_DATA_0       : INTEGER := 16#28#;
    constant ADDR_KP_D_CTRL         : INTEGER := 16#2c#;
    constant ADDR_KI_D_DATA_0       : INTEGER := 16#30#;
    constant ADDR_KI_D_CTRL         : INTEGER := 16#34#;
    constant ADDR_KP_Q_DATA_0       : INTEGER := 16#38#;
    constant ADDR_KP_Q_CTRL         : INTEGER := 16#3c#;
    constant ADDR_KI_Q_DATA_0       : INTEGER := 16#40#;
    constant ADDR_KI_Q_CTRL         : INTEGER := 16#44#;
    constant ADDR_RESET_PS_DATA_0   : INTEGER := 16#48#;
    constant ADDR_RESET_PS_CTRL     : INTEGER := 16#4c#;
    constant ADDR_LIMIT_DATA_0      : INTEGER := 16#50#;
    constant ADDR_LIMIT_CTRL        : INTEGER := 16#54#;
    constant ADDR_OUT_KP_D_DATA_0   : INTEGER := 16#58#;
    constant ADDR_OUT_KP_D_CTRL     : INTEGER := 16#5c#;
    constant ADDR_OUT_IDREF_DATA_0  : INTEGER := 16#68#;
    constant ADDR_OUT_IDREF_CTRL    : INTEGER := 16#6c#;
    constant ADDR_OUT_STATUS_DATA_0 : INTEGER := 16#78#;
    constant ADDR_OUT_STATUS_CTRL   : INTEGER := 16#7c#;
    constant ADDR_BITS         : INTEGER := 7;

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
    signal int_sampletime      : UNSIGNED(31 downto 0) := (others => '0');
    signal int_set_i_d         : UNSIGNED(31 downto 0) := (others => '0');
    signal int_set_i_q         : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KP_d            : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KI_d            : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KP_q            : UNSIGNED(31 downto 0) := (others => '0');
    signal int_KI_q            : UNSIGNED(31 downto 0) := (others => '0');
    signal int_reset_PS        : UNSIGNED(0 downto 0) := (others => '0');
    signal int_limit           : UNSIGNED(31 downto 0) := (others => '0');
    signal int_out_KP_d_ap_vld : STD_LOGIC;
    signal int_out_KP_d        : UNSIGNED(31 downto 0) := (others => '0');
    signal int_out_idref_ap_vld : STD_LOGIC;
    signal int_out_idref       : UNSIGNED(31 downto 0) := (others => '0');
    signal int_out_status_ap_vld : STD_LOGIC;
    signal int_out_status      : UNSIGNED(0 downto 0) := (others => '0');


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
                    when ADDR_SAMPLETIME_DATA_0 =>
                        rdata_data <= RESIZE(int_sampletime(31 downto 0), 32);
                    when ADDR_SET_I_D_DATA_0 =>
                        rdata_data <= RESIZE(int_set_i_d(31 downto 0), 32);
                    when ADDR_SET_I_Q_DATA_0 =>
                        rdata_data <= RESIZE(int_set_i_q(31 downto 0), 32);
                    when ADDR_KP_D_DATA_0 =>
                        rdata_data <= RESIZE(int_KP_d(31 downto 0), 32);
                    when ADDR_KI_D_DATA_0 =>
                        rdata_data <= RESIZE(int_KI_d(31 downto 0), 32);
                    when ADDR_KP_Q_DATA_0 =>
                        rdata_data <= RESIZE(int_KP_q(31 downto 0), 32);
                    when ADDR_KI_Q_DATA_0 =>
                        rdata_data <= RESIZE(int_KI_q(31 downto 0), 32);
                    when ADDR_RESET_PS_DATA_0 =>
                        rdata_data <= RESIZE(int_reset_PS(0 downto 0), 32);
                    when ADDR_LIMIT_DATA_0 =>
                        rdata_data <= RESIZE(int_limit(31 downto 0), 32);
                    when ADDR_OUT_KP_D_DATA_0 =>
                        rdata_data <= RESIZE(int_out_KP_d(31 downto 0), 32);
                    when ADDR_OUT_KP_D_CTRL =>
                        rdata_data(0) <= int_out_KP_d_ap_vld;
                    when ADDR_OUT_IDREF_DATA_0 =>
                        rdata_data <= RESIZE(int_out_idref(31 downto 0), 32);
                    when ADDR_OUT_IDREF_CTRL =>
                        rdata_data(0) <= int_out_idref_ap_vld;
                    when ADDR_OUT_STATUS_DATA_0 =>
                        rdata_data <= RESIZE(int_out_status(0 downto 0), 32);
                    when ADDR_OUT_STATUS_CTRL =>
                        rdata_data(0) <= int_out_status_ap_vld;
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    sampletime           <= STD_LOGIC_VECTOR(int_sampletime);
    set_i_d              <= STD_LOGIC_VECTOR(int_set_i_d);
    set_i_q              <= STD_LOGIC_VECTOR(int_set_i_q);
    KP_d                 <= STD_LOGIC_VECTOR(int_KP_d);
    KI_d                 <= STD_LOGIC_VECTOR(int_KI_d);
    KP_q                 <= STD_LOGIC_VECTOR(int_KP_q);
    KI_q                 <= STD_LOGIC_VECTOR(int_KI_q);
    reset_PS             <= STD_LOGIC_VECTOR(int_reset_PS);
    limit                <= STD_LOGIC_VECTOR(int_limit);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SAMPLETIME_DATA_0) then
                    int_sampletime(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_sampletime(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SET_I_D_DATA_0) then
                    int_set_i_d(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_set_i_d(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_SET_I_Q_DATA_0) then
                    int_set_i_q(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_set_i_q(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KP_D_DATA_0) then
                    int_KP_d(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KP_d(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KI_D_DATA_0) then
                    int_KI_d(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KI_d(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KP_Q_DATA_0) then
                    int_KP_q(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KP_q(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_KI_Q_DATA_0) then
                    int_KI_q(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_KI_q(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_RESET_PS_DATA_0) then
                    int_reset_PS(0 downto 0) <= (UNSIGNED(WDATA(0 downto 0)) and wmask(0 downto 0)) or ((not wmask(0 downto 0)) and int_reset_PS(0 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_LIMIT_DATA_0) then
                    int_limit(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_limit(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_KP_d <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (out_KP_d_ap_vld = '1') then
                    int_out_KP_d <= UNSIGNED(out_KP_d);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_KP_d_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (out_KP_d_ap_vld = '1') then
                    int_out_KP_d_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_OUT_KP_D_CTRL) then
                    int_out_KP_d_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_idref <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (out_idref_ap_vld = '1') then
                    int_out_idref <= UNSIGNED(out_idref);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_idref_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (out_idref_ap_vld = '1') then
                    int_out_idref_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_OUT_IDREF_CTRL) then
                    int_out_idref_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_status <= (others => '0');
            elsif (ACLK_EN = '1') then
                if (out_status_ap_vld = '1') then
                    int_out_status <= UNSIGNED(out_status);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_out_status_ap_vld <= '0';
            elsif (ACLK_EN = '1') then
                if (out_status_ap_vld = '1') then
                    int_out_status_ap_vld <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_OUT_STATUS_CTRL) then
                    int_out_status_ap_vld <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
