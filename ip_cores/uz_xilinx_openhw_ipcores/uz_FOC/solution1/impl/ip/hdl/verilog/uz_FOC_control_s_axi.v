// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module uz_FOC_control_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 7,
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
    output wire [31:0]                   sampletime,
    output wire [31:0]                   set_i_d,
    output wire [31:0]                   set_i_q,
    output wire [31:0]                   KP_d,
    output wire [31:0]                   KI_d,
    output wire [31:0]                   KP_q,
    output wire [31:0]                   KI_q,
    output wire [0:0]                    reset_PS,
    output wire [31:0]                   limit,
    input  wire [31:0]                   out_KP_d,
    input  wire                          out_KP_d_ap_vld,
    input  wire [31:0]                   out_idref,
    input  wire                          out_idref_ap_vld,
    input  wire [0:0]                    out_status,
    input  wire                          out_status_ap_vld
);
//------------------------Address Info-------------------
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of sampletime
//        bit 31~0 - sampletime[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of set_i_d
//        bit 31~0 - set_i_d[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of set_i_q
//        bit 31~0 - set_i_q[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of KP_d
//        bit 31~0 - KP_d[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of KI_d
//        bit 31~0 - KI_d[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of KP_q
//        bit 31~0 - KP_q[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of KI_q
//        bit 31~0 - KI_q[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of reset_PS
//        bit 0  - reset_PS[0] (Read/Write)
//        others - reserved
// 0x4c : reserved
// 0x50 : Data signal of limit
//        bit 31~0 - limit[31:0] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of out_KP_d
//        bit 31~0 - out_KP_d[31:0] (Read)
// 0x5c : Control signal of out_KP_d
//        bit 0  - out_KP_d_ap_vld (Read/COR)
//        others - reserved
// 0x68 : Data signal of out_idref
//        bit 31~0 - out_idref[31:0] (Read)
// 0x6c : Control signal of out_idref
//        bit 0  - out_idref_ap_vld (Read/COR)
//        others - reserved
// 0x78 : Data signal of out_status
//        bit 0  - out_status[0] (Read)
//        others - reserved
// 0x7c : Control signal of out_status
//        bit 0  - out_status_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_SAMPLETIME_DATA_0 = 7'h10,
    ADDR_SAMPLETIME_CTRL   = 7'h14,
    ADDR_SET_I_D_DATA_0    = 7'h18,
    ADDR_SET_I_D_CTRL      = 7'h1c,
    ADDR_SET_I_Q_DATA_0    = 7'h20,
    ADDR_SET_I_Q_CTRL      = 7'h24,
    ADDR_KP_D_DATA_0       = 7'h28,
    ADDR_KP_D_CTRL         = 7'h2c,
    ADDR_KI_D_DATA_0       = 7'h30,
    ADDR_KI_D_CTRL         = 7'h34,
    ADDR_KP_Q_DATA_0       = 7'h38,
    ADDR_KP_Q_CTRL         = 7'h3c,
    ADDR_KI_Q_DATA_0       = 7'h40,
    ADDR_KI_Q_CTRL         = 7'h44,
    ADDR_RESET_PS_DATA_0   = 7'h48,
    ADDR_RESET_PS_CTRL     = 7'h4c,
    ADDR_LIMIT_DATA_0      = 7'h50,
    ADDR_LIMIT_CTRL        = 7'h54,
    ADDR_OUT_KP_D_DATA_0   = 7'h58,
    ADDR_OUT_KP_D_CTRL     = 7'h5c,
    ADDR_OUT_IDREF_DATA_0  = 7'h68,
    ADDR_OUT_IDREF_CTRL    = 7'h6c,
    ADDR_OUT_STATUS_DATA_0 = 7'h78,
    ADDR_OUT_STATUS_CTRL   = 7'h7c,
    WRIDLE                 = 2'd0,
    WRDATA                 = 2'd1,
    WRRESP                 = 2'd2,
    WRRESET                = 2'd3,
    RDIDLE                 = 2'd0,
    RDDATA                 = 2'd1,
    RDRESET                = 2'd2,
    ADDR_BITS                = 7;

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
    reg  [31:0]                   int_sampletime = 'b0;
    reg  [31:0]                   int_set_i_d = 'b0;
    reg  [31:0]                   int_set_i_q = 'b0;
    reg  [31:0]                   int_KP_d = 'b0;
    reg  [31:0]                   int_KI_d = 'b0;
    reg  [31:0]                   int_KP_q = 'b0;
    reg  [31:0]                   int_KI_q = 'b0;
    reg  [0:0]                    int_reset_PS = 'b0;
    reg  [31:0]                   int_limit = 'b0;
    reg                           int_out_KP_d_ap_vld;
    reg  [31:0]                   int_out_KP_d = 'b0;
    reg                           int_out_idref_ap_vld;
    reg  [31:0]                   int_out_idref = 'b0;
    reg                           int_out_status_ap_vld;
    reg  [0:0]                    int_out_status = 'b0;

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
                ADDR_SAMPLETIME_DATA_0: begin
                    rdata <= int_sampletime[31:0];
                end
                ADDR_SET_I_D_DATA_0: begin
                    rdata <= int_set_i_d[31:0];
                end
                ADDR_SET_I_Q_DATA_0: begin
                    rdata <= int_set_i_q[31:0];
                end
                ADDR_KP_D_DATA_0: begin
                    rdata <= int_KP_d[31:0];
                end
                ADDR_KI_D_DATA_0: begin
                    rdata <= int_KI_d[31:0];
                end
                ADDR_KP_Q_DATA_0: begin
                    rdata <= int_KP_q[31:0];
                end
                ADDR_KI_Q_DATA_0: begin
                    rdata <= int_KI_q[31:0];
                end
                ADDR_RESET_PS_DATA_0: begin
                    rdata <= int_reset_PS[0:0];
                end
                ADDR_LIMIT_DATA_0: begin
                    rdata <= int_limit[31:0];
                end
                ADDR_OUT_KP_D_DATA_0: begin
                    rdata <= int_out_KP_d[31:0];
                end
                ADDR_OUT_KP_D_CTRL: begin
                    rdata[0] <= int_out_KP_d_ap_vld;
                end
                ADDR_OUT_IDREF_DATA_0: begin
                    rdata <= int_out_idref[31:0];
                end
                ADDR_OUT_IDREF_CTRL: begin
                    rdata[0] <= int_out_idref_ap_vld;
                end
                ADDR_OUT_STATUS_DATA_0: begin
                    rdata <= int_out_status[0:0];
                end
                ADDR_OUT_STATUS_CTRL: begin
                    rdata[0] <= int_out_status_ap_vld;
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign sampletime = int_sampletime;
assign set_i_d    = int_set_i_d;
assign set_i_q    = int_set_i_q;
assign KP_d       = int_KP_d;
assign KI_d       = int_KI_d;
assign KP_q       = int_KP_q;
assign KI_q       = int_KI_q;
assign reset_PS   = int_reset_PS;
assign limit      = int_limit;
// int_sampletime[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_sampletime[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SAMPLETIME_DATA_0)
            int_sampletime[31:0] <= (WDATA[31:0] & wmask) | (int_sampletime[31:0] & ~wmask);
    end
end

// int_set_i_d[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_set_i_d[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SET_I_D_DATA_0)
            int_set_i_d[31:0] <= (WDATA[31:0] & wmask) | (int_set_i_d[31:0] & ~wmask);
    end
end

// int_set_i_q[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_set_i_q[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SET_I_Q_DATA_0)
            int_set_i_q[31:0] <= (WDATA[31:0] & wmask) | (int_set_i_q[31:0] & ~wmask);
    end
end

// int_KP_d[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KP_d[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KP_D_DATA_0)
            int_KP_d[31:0] <= (WDATA[31:0] & wmask) | (int_KP_d[31:0] & ~wmask);
    end
end

// int_KI_d[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KI_d[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KI_D_DATA_0)
            int_KI_d[31:0] <= (WDATA[31:0] & wmask) | (int_KI_d[31:0] & ~wmask);
    end
end

// int_KP_q[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KP_q[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KP_Q_DATA_0)
            int_KP_q[31:0] <= (WDATA[31:0] & wmask) | (int_KP_q[31:0] & ~wmask);
    end
end

// int_KI_q[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KI_q[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KI_Q_DATA_0)
            int_KI_q[31:0] <= (WDATA[31:0] & wmask) | (int_KI_q[31:0] & ~wmask);
    end
end

// int_reset_PS[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_reset_PS[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_RESET_PS_DATA_0)
            int_reset_PS[0:0] <= (WDATA[31:0] & wmask) | (int_reset_PS[0:0] & ~wmask);
    end
end

// int_limit[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_limit[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_LIMIT_DATA_0)
            int_limit[31:0] <= (WDATA[31:0] & wmask) | (int_limit[31:0] & ~wmask);
    end
end

// int_out_KP_d
always @(posedge ACLK) begin
    if (ARESET)
        int_out_KP_d <= 0;
    else if (ACLK_EN) begin
        if (out_KP_d_ap_vld)
            int_out_KP_d <= out_KP_d;
    end
end

// int_out_KP_d_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_out_KP_d_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (out_KP_d_ap_vld)
            int_out_KP_d_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_OUT_KP_D_CTRL)
            int_out_KP_d_ap_vld <= 1'b0; // clear on read
    end
end

// int_out_idref
always @(posedge ACLK) begin
    if (ARESET)
        int_out_idref <= 0;
    else if (ACLK_EN) begin
        if (out_idref_ap_vld)
            int_out_idref <= out_idref;
    end
end

// int_out_idref_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_out_idref_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (out_idref_ap_vld)
            int_out_idref_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_OUT_IDREF_CTRL)
            int_out_idref_ap_vld <= 1'b0; // clear on read
    end
end

// int_out_status
always @(posedge ACLK) begin
    if (ARESET)
        int_out_status <= 0;
    else if (ACLK_EN) begin
        if (out_status_ap_vld)
            int_out_status <= out_status;
    end
end

// int_out_status_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_out_status_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (out_status_ap_vld)
            int_out_status_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_OUT_STATUS_CTRL)
            int_out_status_ap_vld <= 1'b0; // clear on read
    end
end


//------------------------Memory logic-------------------

endmodule
