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
    output wire [31:0]                   axi_id_reference,
    output wire [31:0]                   axi_iq_reference,
    output wire [31:0]                   axi_sampletime,
    output wire [31:0]                   axi_id_KI,
    output wire [31:0]                   axi_id_KP,
    output wire [31:0]                   axi_iq_KI,
    output wire [31:0]                   axi_iq_KP,
    output wire [31:0]                   axi_limit,
    output wire [0:0]                    axi_reset
);
//------------------------Address Info-------------------
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of axi_id_reference
//        bit 31~0 - axi_id_reference[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of axi_iq_reference
//        bit 31~0 - axi_iq_reference[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of axi_sampletime
//        bit 31~0 - axi_sampletime[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of axi_id_KI
//        bit 31~0 - axi_id_KI[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of axi_id_KP
//        bit 31~0 - axi_id_KP[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of axi_iq_KI
//        bit 31~0 - axi_iq_KI[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of axi_iq_KP
//        bit 31~0 - axi_iq_KP[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of axi_limit
//        bit 31~0 - axi_limit[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of axi_reset
//        bit 0  - axi_reset[0] (Read/Write)
//        others - reserved
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AXI_ID_REFERENCE_DATA_0 = 7'h10,
    ADDR_AXI_ID_REFERENCE_CTRL   = 7'h14,
    ADDR_AXI_IQ_REFERENCE_DATA_0 = 7'h18,
    ADDR_AXI_IQ_REFERENCE_CTRL   = 7'h1c,
    ADDR_AXI_SAMPLETIME_DATA_0   = 7'h20,
    ADDR_AXI_SAMPLETIME_CTRL     = 7'h24,
    ADDR_AXI_ID_KI_DATA_0        = 7'h28,
    ADDR_AXI_ID_KI_CTRL          = 7'h2c,
    ADDR_AXI_ID_KP_DATA_0        = 7'h30,
    ADDR_AXI_ID_KP_CTRL          = 7'h34,
    ADDR_AXI_IQ_KI_DATA_0        = 7'h38,
    ADDR_AXI_IQ_KI_CTRL          = 7'h3c,
    ADDR_AXI_IQ_KP_DATA_0        = 7'h40,
    ADDR_AXI_IQ_KP_CTRL          = 7'h44,
    ADDR_AXI_LIMIT_DATA_0        = 7'h48,
    ADDR_AXI_LIMIT_CTRL          = 7'h4c,
    ADDR_AXI_RESET_DATA_0        = 7'h50,
    ADDR_AXI_RESET_CTRL          = 7'h54,
    WRIDLE                       = 2'd0,
    WRDATA                       = 2'd1,
    WRRESP                       = 2'd2,
    WRRESET                      = 2'd3,
    RDIDLE                       = 2'd0,
    RDDATA                       = 2'd1,
    RDRESET                      = 2'd2,
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
    reg  [31:0]                   int_axi_id_reference = 'b0;
    reg  [31:0]                   int_axi_iq_reference = 'b0;
    reg  [31:0]                   int_axi_sampletime = 'b0;
    reg  [31:0]                   int_axi_id_KI = 'b0;
    reg  [31:0]                   int_axi_id_KP = 'b0;
    reg  [31:0]                   int_axi_iq_KI = 'b0;
    reg  [31:0]                   int_axi_iq_KP = 'b0;
    reg  [31:0]                   int_axi_limit = 'b0;
    reg  [0:0]                    int_axi_reset = 'b0;

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
                ADDR_AXI_ID_REFERENCE_DATA_0: begin
                    rdata <= int_axi_id_reference[31:0];
                end
                ADDR_AXI_IQ_REFERENCE_DATA_0: begin
                    rdata <= int_axi_iq_reference[31:0];
                end
                ADDR_AXI_SAMPLETIME_DATA_0: begin
                    rdata <= int_axi_sampletime[31:0];
                end
                ADDR_AXI_ID_KI_DATA_0: begin
                    rdata <= int_axi_id_KI[31:0];
                end
                ADDR_AXI_ID_KP_DATA_0: begin
                    rdata <= int_axi_id_KP[31:0];
                end
                ADDR_AXI_IQ_KI_DATA_0: begin
                    rdata <= int_axi_iq_KI[31:0];
                end
                ADDR_AXI_IQ_KP_DATA_0: begin
                    rdata <= int_axi_iq_KP[31:0];
                end
                ADDR_AXI_LIMIT_DATA_0: begin
                    rdata <= int_axi_limit[31:0];
                end
                ADDR_AXI_RESET_DATA_0: begin
                    rdata <= int_axi_reset[0:0];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign axi_id_reference = int_axi_id_reference;
assign axi_iq_reference = int_axi_iq_reference;
assign axi_sampletime   = int_axi_sampletime;
assign axi_id_KI        = int_axi_id_KI;
assign axi_id_KP        = int_axi_id_KP;
assign axi_iq_KI        = int_axi_iq_KI;
assign axi_iq_KP        = int_axi_iq_KP;
assign axi_limit        = int_axi_limit;
assign axi_reset        = int_axi_reset;
// int_axi_id_reference[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_id_reference[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_ID_REFERENCE_DATA_0)
            int_axi_id_reference[31:0] <= (WDATA[31:0] & wmask) | (int_axi_id_reference[31:0] & ~wmask);
    end
end

// int_axi_iq_reference[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_iq_reference[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_IQ_REFERENCE_DATA_0)
            int_axi_iq_reference[31:0] <= (WDATA[31:0] & wmask) | (int_axi_iq_reference[31:0] & ~wmask);
    end
end

// int_axi_sampletime[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_sampletime[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_SAMPLETIME_DATA_0)
            int_axi_sampletime[31:0] <= (WDATA[31:0] & wmask) | (int_axi_sampletime[31:0] & ~wmask);
    end
end

// int_axi_id_KI[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_id_KI[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_ID_KI_DATA_0)
            int_axi_id_KI[31:0] <= (WDATA[31:0] & wmask) | (int_axi_id_KI[31:0] & ~wmask);
    end
end

// int_axi_id_KP[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_id_KP[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_ID_KP_DATA_0)
            int_axi_id_KP[31:0] <= (WDATA[31:0] & wmask) | (int_axi_id_KP[31:0] & ~wmask);
    end
end

// int_axi_iq_KI[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_iq_KI[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_IQ_KI_DATA_0)
            int_axi_iq_KI[31:0] <= (WDATA[31:0] & wmask) | (int_axi_iq_KI[31:0] & ~wmask);
    end
end

// int_axi_iq_KP[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_iq_KP[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_IQ_KP_DATA_0)
            int_axi_iq_KP[31:0] <= (WDATA[31:0] & wmask) | (int_axi_iq_KP[31:0] & ~wmask);
    end
end

// int_axi_limit[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_limit[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_LIMIT_DATA_0)
            int_axi_limit[31:0] <= (WDATA[31:0] & wmask) | (int_axi_limit[31:0] & ~wmask);
    end
end

// int_axi_reset[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axi_reset[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXI_RESET_DATA_0)
            int_axi_reset[0:0] <= (WDATA[31:0] & wmask) | (int_axi_reset[0:0] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
