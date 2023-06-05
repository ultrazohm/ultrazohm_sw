// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module uz_PI_controller_control_s_axi
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
    output wire [31:0]                   referenceValue,
    output wire [31:0]                   sampletime,
    output wire [31:0]                   KI,
    output wire [31:0]                   KP,
    output wire [31:0]                   limit,
    output wire [0:0]                    reset,
    input  wire [31:0]                   axi_referenceValue,
    input  wire                          axi_referenceValue_ap_vld,
    input  wire [31:0]                   axi_actualValue,
    input  wire                          axi_actualValue_ap_vld,
    input  wire [31:0]                   error,
    input  wire                          error_ap_vld,
    input  wire [31:0]                   P_sum,
    input  wire                          P_sum_ap_vld
);
//------------------------Address Info-------------------
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of referenceValue
//        bit 31~0 - referenceValue[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of sampletime
//        bit 31~0 - sampletime[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of KI
//        bit 31~0 - KI[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of KP
//        bit 31~0 - KP[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of limit
//        bit 31~0 - limit[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of reset
//        bit 0  - reset[0] (Read/Write)
//        others - reserved
// 0x3c : reserved
// 0x40 : Data signal of axi_referenceValue
//        bit 31~0 - axi_referenceValue[31:0] (Read)
// 0x44 : Control signal of axi_referenceValue
//        bit 0  - axi_referenceValue_ap_vld (Read/COR)
//        others - reserved
// 0x50 : Data signal of axi_actualValue
//        bit 31~0 - axi_actualValue[31:0] (Read)
// 0x54 : Control signal of axi_actualValue
//        bit 0  - axi_actualValue_ap_vld (Read/COR)
//        others - reserved
// 0x60 : Data signal of error
//        bit 31~0 - error[31:0] (Read)
// 0x64 : Control signal of error
//        bit 0  - error_ap_vld (Read/COR)
//        others - reserved
// 0x70 : Data signal of P_sum
//        bit 31~0 - P_sum[31:0] (Read)
// 0x74 : Control signal of P_sum
//        bit 0  - P_sum_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_REFERENCEVALUE_DATA_0     = 7'h10,
    ADDR_REFERENCEVALUE_CTRL       = 7'h14,
    ADDR_SAMPLETIME_DATA_0         = 7'h18,
    ADDR_SAMPLETIME_CTRL           = 7'h1c,
    ADDR_KI_DATA_0                 = 7'h20,
    ADDR_KI_CTRL                   = 7'h24,
    ADDR_KP_DATA_0                 = 7'h28,
    ADDR_KP_CTRL                   = 7'h2c,
    ADDR_LIMIT_DATA_0              = 7'h30,
    ADDR_LIMIT_CTRL                = 7'h34,
    ADDR_RESET_DATA_0              = 7'h38,
    ADDR_RESET_CTRL                = 7'h3c,
    ADDR_AXI_REFERENCEVALUE_DATA_0 = 7'h40,
    ADDR_AXI_REFERENCEVALUE_CTRL   = 7'h44,
    ADDR_AXI_ACTUALVALUE_DATA_0    = 7'h50,
    ADDR_AXI_ACTUALVALUE_CTRL      = 7'h54,
    ADDR_ERROR_DATA_0              = 7'h60,
    ADDR_ERROR_CTRL                = 7'h64,
    ADDR_P_SUM_DATA_0              = 7'h70,
    ADDR_P_SUM_CTRL                = 7'h74,
    WRIDLE                         = 2'd0,
    WRDATA                         = 2'd1,
    WRRESP                         = 2'd2,
    WRRESET                        = 2'd3,
    RDIDLE                         = 2'd0,
    RDDATA                         = 2'd1,
    RDRESET                        = 2'd2,
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
    reg  [31:0]                   int_referenceValue = 'b0;
    reg  [31:0]                   int_sampletime = 'b0;
    reg  [31:0]                   int_KI = 'b0;
    reg  [31:0]                   int_KP = 'b0;
    reg  [31:0]                   int_limit = 'b0;
    reg  [0:0]                    int_reset = 'b0;
    reg                           int_axi_referenceValue_ap_vld;
    reg  [31:0]                   int_axi_referenceValue = 'b0;
    reg                           int_axi_actualValue_ap_vld;
    reg  [31:0]                   int_axi_actualValue = 'b0;
    reg                           int_error_ap_vld;
    reg  [31:0]                   int_error = 'b0;
    reg                           int_P_sum_ap_vld;
    reg  [31:0]                   int_P_sum = 'b0;

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
                ADDR_REFERENCEVALUE_DATA_0: begin
                    rdata <= int_referenceValue[31:0];
                end
                ADDR_SAMPLETIME_DATA_0: begin
                    rdata <= int_sampletime[31:0];
                end
                ADDR_KI_DATA_0: begin
                    rdata <= int_KI[31:0];
                end
                ADDR_KP_DATA_0: begin
                    rdata <= int_KP[31:0];
                end
                ADDR_LIMIT_DATA_0: begin
                    rdata <= int_limit[31:0];
                end
                ADDR_RESET_DATA_0: begin
                    rdata <= int_reset[0:0];
                end
                ADDR_AXI_REFERENCEVALUE_DATA_0: begin
                    rdata <= int_axi_referenceValue[31:0];
                end
                ADDR_AXI_REFERENCEVALUE_CTRL: begin
                    rdata[0] <= int_axi_referenceValue_ap_vld;
                end
                ADDR_AXI_ACTUALVALUE_DATA_0: begin
                    rdata <= int_axi_actualValue[31:0];
                end
                ADDR_AXI_ACTUALVALUE_CTRL: begin
                    rdata[0] <= int_axi_actualValue_ap_vld;
                end
                ADDR_ERROR_DATA_0: begin
                    rdata <= int_error[31:0];
                end
                ADDR_ERROR_CTRL: begin
                    rdata[0] <= int_error_ap_vld;
                end
                ADDR_P_SUM_DATA_0: begin
                    rdata <= int_P_sum[31:0];
                end
                ADDR_P_SUM_CTRL: begin
                    rdata[0] <= int_P_sum_ap_vld;
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign referenceValue = int_referenceValue;
assign sampletime     = int_sampletime;
assign KI             = int_KI;
assign KP             = int_KP;
assign limit          = int_limit;
assign reset          = int_reset;
// int_referenceValue[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_referenceValue[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_REFERENCEVALUE_DATA_0)
            int_referenceValue[31:0] <= (WDATA[31:0] & wmask) | (int_referenceValue[31:0] & ~wmask);
    end
end

// int_sampletime[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_sampletime[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_SAMPLETIME_DATA_0)
            int_sampletime[31:0] <= (WDATA[31:0] & wmask) | (int_sampletime[31:0] & ~wmask);
    end
end

// int_KI[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KI[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KI_DATA_0)
            int_KI[31:0] <= (WDATA[31:0] & wmask) | (int_KI[31:0] & ~wmask);
    end
end

// int_KP[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_KP[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KP_DATA_0)
            int_KP[31:0] <= (WDATA[31:0] & wmask) | (int_KP[31:0] & ~wmask);
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

// int_reset[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_reset[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_RESET_DATA_0)
            int_reset[0:0] <= (WDATA[31:0] & wmask) | (int_reset[0:0] & ~wmask);
    end
end

// int_axi_referenceValue
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_referenceValue <= 0;
    else if (ACLK_EN) begin
        if (axi_referenceValue_ap_vld)
            int_axi_referenceValue <= axi_referenceValue;
    end
end

// int_axi_referenceValue_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_referenceValue_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (axi_referenceValue_ap_vld)
            int_axi_referenceValue_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_AXI_REFERENCEVALUE_CTRL)
            int_axi_referenceValue_ap_vld <= 1'b0; // clear on read
    end
end

// int_axi_actualValue
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_actualValue <= 0;
    else if (ACLK_EN) begin
        if (axi_actualValue_ap_vld)
            int_axi_actualValue <= axi_actualValue;
    end
end

// int_axi_actualValue_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_actualValue_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (axi_actualValue_ap_vld)
            int_axi_actualValue_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_AXI_ACTUALVALUE_CTRL)
            int_axi_actualValue_ap_vld <= 1'b0; // clear on read
    end
end

// int_error
always @(posedge ACLK) begin
    if (ARESET)
        int_error <= 0;
    else if (ACLK_EN) begin
        if (error_ap_vld)
            int_error <= error;
    end
end

// int_error_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_error_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (error_ap_vld)
            int_error_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_ERROR_CTRL)
            int_error_ap_vld <= 1'b0; // clear on read
    end
end

// int_P_sum
always @(posedge ACLK) begin
    if (ARESET)
        int_P_sum <= 0;
    else if (ACLK_EN) begin
        if (P_sum_ap_vld)
            int_P_sum <= P_sum;
    end
end

// int_P_sum_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_P_sum_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (P_sum_ap_vld)
            int_P_sum_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_P_SUM_CTRL)
            int_P_sum_ap_vld <= 1'b0; // clear on read
    end
end


//------------------------Memory logic-------------------

endmodule
