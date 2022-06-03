// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module uz_FOC_sample_Din_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 8,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire                          interrupt,
    output wire [159:0]                  Controller_id,
    output wire [159:0]                  Controller_iq,
    output wire [287:0]                  self_i,
    input  wire [287:0]                  self_o,
    input  wire                          self_o_ap_vld,
    output wire [95:0]                   i_actual_Ampere,
    output wire [31:0]                   V_dc_volts,
    output wire [31:0]                   omega_el_rad_per_sec,
    output wire                          ap_start,
    input  wire                          ap_done,
    input  wire                          ap_ready,
    input  wire                          ap_idle,
    output wire [95:0]                   i_reference_Ampere
);
//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of Controller_id
//        bit 31~0 - Controller_id[31:0] (Read/Write)
// 0x14 : Data signal of Controller_id
//        bit 31~0 - Controller_id[63:32] (Read/Write)
// 0x18 : Data signal of Controller_id
//        bit 31~0 - Controller_id[95:64] (Read/Write)
// 0x1c : Data signal of Controller_id
//        bit 31~0 - Controller_id[127:96] (Read/Write)
// 0x20 : Data signal of Controller_id
//        bit 31~0 - Controller_id[159:128] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[31:0] (Read/Write)
// 0x2c : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[63:32] (Read/Write)
// 0x30 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[95:64] (Read/Write)
// 0x34 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[127:96] (Read/Write)
// 0x38 : Data signal of Controller_iq
//        bit 31~0 - Controller_iq[159:128] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of self_i
//        bit 31~0 - self_i[31:0] (Read/Write)
// 0x44 : Data signal of self_i
//        bit 31~0 - self_i[63:32] (Read/Write)
// 0x48 : Data signal of self_i
//        bit 31~0 - self_i[95:64] (Read/Write)
// 0x4c : Data signal of self_i
//        bit 31~0 - self_i[127:96] (Read/Write)
// 0x50 : Data signal of self_i
//        bit 31~0 - self_i[159:128] (Read/Write)
// 0x54 : Data signal of self_i
//        bit 31~0 - self_i[191:160] (Read/Write)
// 0x58 : Data signal of self_i
//        bit 31~0 - self_i[223:192] (Read/Write)
// 0x5c : Data signal of self_i
//        bit 31~0 - self_i[255:224] (Read/Write)
// 0x60 : Data signal of self_i
//        bit 31~0 - self_i[287:256] (Read/Write)
// 0x64 : reserved
// 0x68 : Data signal of self_o
//        bit 31~0 - self_o[31:0] (Read)
// 0x6c : Data signal of self_o
//        bit 31~0 - self_o[63:32] (Read)
// 0x70 : Data signal of self_o
//        bit 31~0 - self_o[95:64] (Read)
// 0x74 : Data signal of self_o
//        bit 31~0 - self_o[127:96] (Read)
// 0x78 : Data signal of self_o
//        bit 31~0 - self_o[159:128] (Read)
// 0x7c : Data signal of self_o
//        bit 31~0 - self_o[191:160] (Read)
// 0x80 : Data signal of self_o
//        bit 31~0 - self_o[223:192] (Read)
// 0x84 : Data signal of self_o
//        bit 31~0 - self_o[255:224] (Read)
// 0x88 : Data signal of self_o
//        bit 31~0 - self_o[287:256] (Read)
// 0x8c : Control signal of self_o
//        bit 0  - self_o_ap_vld (Read/COR)
//        others - reserved
// 0x90 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[31:0] (Read/Write)
// 0x94 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[63:32] (Read/Write)
// 0x98 : Data signal of i_actual_Ampere
//        bit 31~0 - i_actual_Ampere[95:64] (Read/Write)
// 0x9c : reserved
// 0xa0 : Data signal of V_dc_volts
//        bit 31~0 - V_dc_volts[31:0] (Read/Write)
// 0xa4 : reserved
// 0xa8 : Data signal of omega_el_rad_per_sec
//        bit 31~0 - omega_el_rad_per_sec[31:0] (Read/Write)
// 0xac : reserved
// 0xb0 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[31:0] (Read/Write)
// 0xb4 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[63:32] (Read/Write)
// 0xb8 : Data signal of i_reference_Ampere
//        bit 31~0 - i_reference_Ampere[95:64] (Read/Write)
// 0xbc : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL                     = 8'h00,
    ADDR_GIE                         = 8'h04,
    ADDR_IER                         = 8'h08,
    ADDR_ISR                         = 8'h0c,
    ADDR_CONTROLLER_ID_DATA_0        = 8'h10,
    ADDR_CONTROLLER_ID_DATA_1        = 8'h14,
    ADDR_CONTROLLER_ID_DATA_2        = 8'h18,
    ADDR_CONTROLLER_ID_DATA_3        = 8'h1c,
    ADDR_CONTROLLER_ID_DATA_4        = 8'h20,
    ADDR_CONTROLLER_ID_CTRL          = 8'h24,
    ADDR_CONTROLLER_IQ_DATA_0        = 8'h28,
    ADDR_CONTROLLER_IQ_DATA_1        = 8'h2c,
    ADDR_CONTROLLER_IQ_DATA_2        = 8'h30,
    ADDR_CONTROLLER_IQ_DATA_3        = 8'h34,
    ADDR_CONTROLLER_IQ_DATA_4        = 8'h38,
    ADDR_CONTROLLER_IQ_CTRL          = 8'h3c,
    ADDR_SELF_I_DATA_0               = 8'h40,
    ADDR_SELF_I_DATA_1               = 8'h44,
    ADDR_SELF_I_DATA_2               = 8'h48,
    ADDR_SELF_I_DATA_3               = 8'h4c,
    ADDR_SELF_I_DATA_4               = 8'h50,
    ADDR_SELF_I_DATA_5               = 8'h54,
    ADDR_SELF_I_DATA_6               = 8'h58,
    ADDR_SELF_I_DATA_7               = 8'h5c,
    ADDR_SELF_I_DATA_8               = 8'h60,
    ADDR_SELF_I_CTRL                 = 8'h64,
    ADDR_SELF_O_DATA_0               = 8'h68,
    ADDR_SELF_O_DATA_1               = 8'h6c,
    ADDR_SELF_O_DATA_2               = 8'h70,
    ADDR_SELF_O_DATA_3               = 8'h74,
    ADDR_SELF_O_DATA_4               = 8'h78,
    ADDR_SELF_O_DATA_5               = 8'h7c,
    ADDR_SELF_O_DATA_6               = 8'h80,
    ADDR_SELF_O_DATA_7               = 8'h84,
    ADDR_SELF_O_DATA_8               = 8'h88,
    ADDR_SELF_O_CTRL                 = 8'h8c,
    ADDR_I_ACTUAL_AMPERE_DATA_0      = 8'h90,
    ADDR_I_ACTUAL_AMPERE_DATA_1      = 8'h94,
    ADDR_I_ACTUAL_AMPERE_DATA_2      = 8'h98,
    ADDR_I_ACTUAL_AMPERE_CTRL        = 8'h9c,
    ADDR_V_DC_VOLTS_DATA_0           = 8'ha0,
    ADDR_V_DC_VOLTS_CTRL             = 8'ha4,
    ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0 = 8'ha8,
    ADDR_OMEGA_EL_RAD_PER_SEC_CTRL   = 8'hac,
    ADDR_I_REFERENCE_AMPERE_DATA_0   = 8'hb0,
    ADDR_I_REFERENCE_AMPERE_DATA_1   = 8'hb4,
    ADDR_I_REFERENCE_AMPERE_DATA_2   = 8'hb8,
    ADDR_I_REFERENCE_AMPERE_CTRL     = 8'hbc,
    WRIDLE                           = 2'd0,
    WRDATA                           = 2'd1,
    WRRESP                           = 2'd2,
    WRRESET                          = 2'd3,
    RDIDLE                           = 2'd0,
    RDDATA                           = 2'd1,
    RDRESET                          = 2'd2,
    ADDR_BITS                = 8;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg                           int_ap_idle;
    reg                           int_ap_ready;
    reg                           int_ap_done = 1'b0;
    reg                           int_ap_start = 1'b0;
    reg                           int_auto_restart = 1'b0;
    reg                           int_gie = 1'b0;
    reg  [1:0]                    int_ier = 2'b0;
    reg  [1:0]                    int_isr = 2'b0;
    reg  [159:0]                  int_Controller_id = 'b0;
    reg  [159:0]                  int_Controller_iq = 'b0;
    reg  [287:0]                  int_self_i = 'b0;
    reg  [287:0]                  int_self_o = 'b0;
    reg                           int_self_o_ap_vld;
    reg  [95:0]                   int_i_actual_Ampere = 'b0;
    reg  [31:0]                   int_V_dc_volts = 'b0;
    reg  [31:0]                   int_omega_el_rad_per_sec = 'b0;
    reg  [95:0]                   int_i_reference_Ampere = 'b0;

//------------------------Instantiation------------------


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
            case (raddr)
                ADDR_AP_CTRL: begin
                    rdata[0] <= int_ap_start;
                    rdata[1] <= int_ap_done;
                    rdata[2] <= int_ap_idle;
                    rdata[3] <= int_ap_ready;
                    rdata[7] <= int_auto_restart;
                end
                ADDR_GIE: begin
                    rdata <= int_gie;
                end
                ADDR_IER: begin
                    rdata <= int_ier;
                end
                ADDR_ISR: begin
                    rdata <= int_isr;
                end
                ADDR_CONTROLLER_ID_DATA_0: begin
                    rdata <= int_Controller_id[31:0];
                end
                ADDR_CONTROLLER_ID_DATA_1: begin
                    rdata <= int_Controller_id[63:32];
                end
                ADDR_CONTROLLER_ID_DATA_2: begin
                    rdata <= int_Controller_id[95:64];
                end
                ADDR_CONTROLLER_ID_DATA_3: begin
                    rdata <= int_Controller_id[127:96];
                end
                ADDR_CONTROLLER_ID_DATA_4: begin
                    rdata <= int_Controller_id[159:128];
                end
                ADDR_CONTROLLER_IQ_DATA_0: begin
                    rdata <= int_Controller_iq[31:0];
                end
                ADDR_CONTROLLER_IQ_DATA_1: begin
                    rdata <= int_Controller_iq[63:32];
                end
                ADDR_CONTROLLER_IQ_DATA_2: begin
                    rdata <= int_Controller_iq[95:64];
                end
                ADDR_CONTROLLER_IQ_DATA_3: begin
                    rdata <= int_Controller_iq[127:96];
                end
                ADDR_CONTROLLER_IQ_DATA_4: begin
                    rdata <= int_Controller_iq[159:128];
                end
                ADDR_SELF_I_DATA_0: begin
                    rdata <= int_self_i[31:0];
                end
                ADDR_SELF_I_DATA_1: begin
                    rdata <= int_self_i[63:32];
                end
                ADDR_SELF_I_DATA_2: begin
                    rdata <= int_self_i[95:64];
                end
                ADDR_SELF_I_DATA_3: begin
                    rdata <= int_self_i[127:96];
                end
                ADDR_SELF_I_DATA_4: begin
                    rdata <= int_self_i[159:128];
                end
                ADDR_SELF_I_DATA_5: begin
                    rdata <= int_self_i[191:160];
                end
                ADDR_SELF_I_DATA_6: begin
                    rdata <= int_self_i[223:192];
                end
                ADDR_SELF_I_DATA_7: begin
                    rdata <= int_self_i[255:224];
                end
                ADDR_SELF_I_DATA_8: begin
                    rdata <= int_self_i[287:256];
                end
                ADDR_SELF_O_DATA_0: begin
                    rdata <= int_self_o[31:0];
                end
                ADDR_SELF_O_DATA_1: begin
                    rdata <= int_self_o[63:32];
                end
                ADDR_SELF_O_DATA_2: begin
                    rdata <= int_self_o[95:64];
                end
                ADDR_SELF_O_DATA_3: begin
                    rdata <= int_self_o[127:96];
                end
                ADDR_SELF_O_DATA_4: begin
                    rdata <= int_self_o[159:128];
                end
                ADDR_SELF_O_DATA_5: begin
                    rdata <= int_self_o[191:160];
                end
                ADDR_SELF_O_DATA_6: begin
                    rdata <= int_self_o[223:192];
                end
                ADDR_SELF_O_DATA_7: begin
                    rdata <= int_self_o[255:224];
                end
                ADDR_SELF_O_DATA_8: begin
                    rdata <= int_self_o[287:256];
                end
                ADDR_SELF_O_CTRL: begin
                    rdata[0] <= int_self_o_ap_vld;
                end
                ADDR_I_ACTUAL_AMPERE_DATA_0: begin
                    rdata <= int_i_actual_Ampere[31:0];
                end
                ADDR_I_ACTUAL_AMPERE_DATA_1: begin
                    rdata <= int_i_actual_Ampere[63:32];
                end
                ADDR_I_ACTUAL_AMPERE_DATA_2: begin
                    rdata <= int_i_actual_Ampere[95:64];
                end
                ADDR_V_DC_VOLTS_DATA_0: begin
                    rdata <= int_V_dc_volts[31:0];
                end
                ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0: begin
                    rdata <= int_omega_el_rad_per_sec[31:0];
                end
                ADDR_I_REFERENCE_AMPERE_DATA_0: begin
                    rdata <= int_i_reference_Ampere[31:0];
                end
                ADDR_I_REFERENCE_AMPERE_DATA_1: begin
                    rdata <= int_i_reference_Ampere[63:32];
                end
                ADDR_I_REFERENCE_AMPERE_DATA_2: begin
                    rdata <= int_i_reference_Ampere[95:64];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt            = int_gie & (|int_isr);
assign ap_start             = int_ap_start;
assign Controller_id        = int_Controller_id;
assign Controller_iq        = int_Controller_iq;
assign self_i               = int_self_i;
assign i_actual_Ampere      = int_i_actual_Ampere;
assign V_dc_volts           = int_V_dc_volts;
assign omega_el_rad_per_sec = int_omega_el_rad_per_sec;
assign i_reference_Ampere   = int_i_reference_Ampere;
// int_ap_start
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_start <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0] && WDATA[0])
            int_ap_start <= 1'b1;
        else if (ap_ready)
            int_ap_start <= int_auto_restart; // clear on handshake/auto restart
    end
end

// int_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_done <= 1'b0;
    else if (ACLK_EN) begin
        if (ap_done)
            int_ap_done <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_ap_done <= 1'b0; // clear on read
    end
end

// int_ap_idle
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_idle <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_idle <= ap_idle;
    end
end

// int_ap_ready
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_ready <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_ready <= ap_ready;
    end
end

// int_auto_restart
always @(posedge ACLK) begin
    if (ARESET)
        int_auto_restart <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0])
            int_auto_restart <=  WDATA[7];
    end
end

// int_gie
always @(posedge ACLK) begin
    if (ARESET)
        int_gie <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_GIE && WSTRB[0])
            int_gie <= WDATA[0];
    end
end

// int_ier
always @(posedge ACLK) begin
    if (ARESET)
        int_ier <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IER && WSTRB[0])
            int_ier <= WDATA[1:0];
    end
end

// int_isr[0]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[0] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[0] & ap_done)
            int_isr[0] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[0] <= int_isr[0] ^ WDATA[0]; // toggle on write
    end
end

// int_isr[1]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[1] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[1] & ap_ready)
            int_isr[1] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[1] <= int_isr[1] ^ WDATA[1]; // toggle on write
    end
end

// int_Controller_id[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_id[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_ID_DATA_0)
            int_Controller_id[31:0] <= (WDATA[31:0] & wmask) | (int_Controller_id[31:0] & ~wmask);
    end
end

// int_Controller_id[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_id[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_ID_DATA_1)
            int_Controller_id[63:32] <= (WDATA[31:0] & wmask) | (int_Controller_id[63:32] & ~wmask);
    end
end

// int_Controller_id[95:64]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_id[95:64] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_ID_DATA_2)
            int_Controller_id[95:64] <= (WDATA[31:0] & wmask) | (int_Controller_id[95:64] & ~wmask);
    end
end

// int_Controller_id[127:96]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_id[127:96] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_ID_DATA_3)
            int_Controller_id[127:96] <= (WDATA[31:0] & wmask) | (int_Controller_id[127:96] & ~wmask);
    end
end

// int_Controller_id[159:128]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_id[159:128] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_ID_DATA_4)
            int_Controller_id[159:128] <= (WDATA[31:0] & wmask) | (int_Controller_id[159:128] & ~wmask);
    end
end

// int_Controller_iq[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_iq[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_IQ_DATA_0)
            int_Controller_iq[31:0] <= (WDATA[31:0] & wmask) | (int_Controller_iq[31:0] & ~wmask);
    end
end

// int_Controller_iq[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_iq[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_IQ_DATA_1)
            int_Controller_iq[63:32] <= (WDATA[31:0] & wmask) | (int_Controller_iq[63:32] & ~wmask);
    end
end

// int_Controller_iq[95:64]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_iq[95:64] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_IQ_DATA_2)
            int_Controller_iq[95:64] <= (WDATA[31:0] & wmask) | (int_Controller_iq[95:64] & ~wmask);
    end
end

// int_Controller_iq[127:96]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_iq[127:96] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_IQ_DATA_3)
            int_Controller_iq[127:96] <= (WDATA[31:0] & wmask) | (int_Controller_iq[127:96] & ~wmask);
    end
end

// int_Controller_iq[159:128]
always @(posedge ACLK) begin
    if (ARESET)
        int_Controller_iq[159:128] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CONTROLLER_IQ_DATA_4)
            int_Controller_iq[159:128] <= (WDATA[31:0] & wmask) | (int_Controller_iq[159:128] & ~wmask);
    end
end

// int_self_i[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_0)
            int_self_i[31:0] <= (WDATA[31:0] & wmask) | (int_self_i[31:0] & ~wmask);
    end
end

// int_self_i[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_1)
            int_self_i[63:32] <= (WDATA[31:0] & wmask) | (int_self_i[63:32] & ~wmask);
    end
end

// int_self_i[95:64]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[95:64] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_2)
            int_self_i[95:64] <= (WDATA[31:0] & wmask) | (int_self_i[95:64] & ~wmask);
    end
end

// int_self_i[127:96]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[127:96] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_3)
            int_self_i[127:96] <= (WDATA[31:0] & wmask) | (int_self_i[127:96] & ~wmask);
    end
end

// int_self_i[159:128]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[159:128] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_4)
            int_self_i[159:128] <= (WDATA[31:0] & wmask) | (int_self_i[159:128] & ~wmask);
    end
end

// int_self_i[191:160]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[191:160] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_5)
            int_self_i[191:160] <= (WDATA[31:0] & wmask) | (int_self_i[191:160] & ~wmask);
    end
end

// int_self_i[223:192]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[223:192] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_6)
            int_self_i[223:192] <= (WDATA[31:0] & wmask) | (int_self_i[223:192] & ~wmask);
    end
end

// int_self_i[255:224]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[255:224] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_7)
            int_self_i[255:224] <= (WDATA[31:0] & wmask) | (int_self_i[255:224] & ~wmask);
    end
end

// int_self_i[287:256]
always @(posedge ACLK) begin
    if (ARESET)
        int_self_i[287:256] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SELF_I_DATA_8)
            int_self_i[287:256] <= (WDATA[31:0] & wmask) | (int_self_i[287:256] & ~wmask);
    end
end

// int_self_o
always @(posedge ACLK) begin
    if (ARESET)
        int_self_o <= 0;
    else if (ACLK_EN) begin
        if (self_o_ap_vld)
            int_self_o <= self_o;
    end
end

// int_self_o_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_self_o_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (self_o_ap_vld)
            int_self_o_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_SELF_O_CTRL)
            int_self_o_ap_vld <= 1'b0; // clear on read
    end
end

// int_i_actual_Ampere[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_actual_Ampere[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_ACTUAL_AMPERE_DATA_0)
            int_i_actual_Ampere[31:0] <= (WDATA[31:0] & wmask) | (int_i_actual_Ampere[31:0] & ~wmask);
    end
end

// int_i_actual_Ampere[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_actual_Ampere[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_ACTUAL_AMPERE_DATA_1)
            int_i_actual_Ampere[63:32] <= (WDATA[31:0] & wmask) | (int_i_actual_Ampere[63:32] & ~wmask);
    end
end

// int_i_actual_Ampere[95:64]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_actual_Ampere[95:64] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_ACTUAL_AMPERE_DATA_2)
            int_i_actual_Ampere[95:64] <= (WDATA[31:0] & wmask) | (int_i_actual_Ampere[95:64] & ~wmask);
    end
end

// int_V_dc_volts[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_V_dc_volts[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_V_DC_VOLTS_DATA_0)
            int_V_dc_volts[31:0] <= (WDATA[31:0] & wmask) | (int_V_dc_volts[31:0] & ~wmask);
    end
end

// int_omega_el_rad_per_sec[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_omega_el_rad_per_sec[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OMEGA_EL_RAD_PER_SEC_DATA_0)
            int_omega_el_rad_per_sec[31:0] <= (WDATA[31:0] & wmask) | (int_omega_el_rad_per_sec[31:0] & ~wmask);
    end
end

// int_i_reference_Ampere[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_reference_Ampere[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_REFERENCE_AMPERE_DATA_0)
            int_i_reference_Ampere[31:0] <= (WDATA[31:0] & wmask) | (int_i_reference_Ampere[31:0] & ~wmask);
    end
end

// int_i_reference_Ampere[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_reference_Ampere[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_REFERENCE_AMPERE_DATA_1)
            int_i_reference_Ampere[63:32] <= (WDATA[31:0] & wmask) | (int_i_reference_Ampere[63:32] & ~wmask);
    end
end

// int_i_reference_Ampere[95:64]
always @(posedge ACLK) begin
    if (ARESET)
        int_i_reference_Ampere[95:64] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_REFERENCE_AMPERE_DATA_2)
            int_i_reference_Ampere[95:64] <= (WDATA[31:0] & wmask) | (int_i_reference_Ampere[95:64] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
