// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module MultiLayerPerceptronDecoupled_control_s_axi
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
    output wire [63:0]                   input_r,
    output wire [63:0]                   output_r,
    output wire [63:0]                   axiWeightInput,
    output wire [63:0]                   axiBiasInput,
    output wire [63:0]                   axiWeightOutput,
    output wire [63:0]                   axiBiasOutput
);
//------------------------Address Info-------------------
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of input_r
//        bit 31~0 - input_r[31:0] (Read/Write)
// 0x14 : Data signal of input_r
//        bit 31~0 - input_r[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of output_r
//        bit 31~0 - output_r[31:0] (Read/Write)
// 0x20 : Data signal of output_r
//        bit 31~0 - output_r[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of axiWeightInput
//        bit 31~0 - axiWeightInput[31:0] (Read/Write)
// 0x2c : Data signal of axiWeightInput
//        bit 31~0 - axiWeightInput[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of axiBiasInput
//        bit 31~0 - axiBiasInput[31:0] (Read/Write)
// 0x38 : Data signal of axiBiasInput
//        bit 31~0 - axiBiasInput[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of axiWeightOutput
//        bit 31~0 - axiWeightOutput[31:0] (Read/Write)
// 0x44 : Data signal of axiWeightOutput
//        bit 31~0 - axiWeightOutput[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of axiBiasOutput
//        bit 31~0 - axiBiasOutput[31:0] (Read/Write)
// 0x50 : Data signal of axiBiasOutput
//        bit 31~0 - axiBiasOutput[63:32] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_INPUT_R_DATA_0         = 7'h10,
    ADDR_INPUT_R_DATA_1         = 7'h14,
    ADDR_INPUT_R_CTRL           = 7'h18,
    ADDR_OUTPUT_R_DATA_0        = 7'h1c,
    ADDR_OUTPUT_R_DATA_1        = 7'h20,
    ADDR_OUTPUT_R_CTRL          = 7'h24,
    ADDR_AXIWEIGHTINPUT_DATA_0  = 7'h28,
    ADDR_AXIWEIGHTINPUT_DATA_1  = 7'h2c,
    ADDR_AXIWEIGHTINPUT_CTRL    = 7'h30,
    ADDR_AXIBIASINPUT_DATA_0    = 7'h34,
    ADDR_AXIBIASINPUT_DATA_1    = 7'h38,
    ADDR_AXIBIASINPUT_CTRL      = 7'h3c,
    ADDR_AXIWEIGHTOUTPUT_DATA_0 = 7'h40,
    ADDR_AXIWEIGHTOUTPUT_DATA_1 = 7'h44,
    ADDR_AXIWEIGHTOUTPUT_CTRL   = 7'h48,
    ADDR_AXIBIASOUTPUT_DATA_0   = 7'h4c,
    ADDR_AXIBIASOUTPUT_DATA_1   = 7'h50,
    ADDR_AXIBIASOUTPUT_CTRL     = 7'h54,
    WRIDLE                      = 2'd0,
    WRDATA                      = 2'd1,
    WRRESP                      = 2'd2,
    WRRESET                     = 2'd3,
    RDIDLE                      = 2'd0,
    RDDATA                      = 2'd1,
    RDRESET                     = 2'd2,
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
    reg  [63:0]                   int_input_r = 'b0;
    reg  [63:0]                   int_output_r = 'b0;
    reg  [63:0]                   int_axiWeightInput = 'b0;
    reg  [63:0]                   int_axiBiasInput = 'b0;
    reg  [63:0]                   int_axiWeightOutput = 'b0;
    reg  [63:0]                   int_axiBiasOutput = 'b0;

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
                ADDR_INPUT_R_DATA_0: begin
                    rdata <= int_input_r[31:0];
                end
                ADDR_INPUT_R_DATA_1: begin
                    rdata <= int_input_r[63:32];
                end
                ADDR_OUTPUT_R_DATA_0: begin
                    rdata <= int_output_r[31:0];
                end
                ADDR_OUTPUT_R_DATA_1: begin
                    rdata <= int_output_r[63:32];
                end
                ADDR_AXIWEIGHTINPUT_DATA_0: begin
                    rdata <= int_axiWeightInput[31:0];
                end
                ADDR_AXIWEIGHTINPUT_DATA_1: begin
                    rdata <= int_axiWeightInput[63:32];
                end
                ADDR_AXIBIASINPUT_DATA_0: begin
                    rdata <= int_axiBiasInput[31:0];
                end
                ADDR_AXIBIASINPUT_DATA_1: begin
                    rdata <= int_axiBiasInput[63:32];
                end
                ADDR_AXIWEIGHTOUTPUT_DATA_0: begin
                    rdata <= int_axiWeightOutput[31:0];
                end
                ADDR_AXIWEIGHTOUTPUT_DATA_1: begin
                    rdata <= int_axiWeightOutput[63:32];
                end
                ADDR_AXIBIASOUTPUT_DATA_0: begin
                    rdata <= int_axiBiasOutput[31:0];
                end
                ADDR_AXIBIASOUTPUT_DATA_1: begin
                    rdata <= int_axiBiasOutput[63:32];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign input_r         = int_input_r;
assign output_r        = int_output_r;
assign axiWeightInput  = int_axiWeightInput;
assign axiBiasInput    = int_axiBiasInput;
assign axiWeightOutput = int_axiWeightOutput;
assign axiBiasOutput   = int_axiBiasOutput;
// int_input_r[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_input_r[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_INPUT_R_DATA_0)
            int_input_r[31:0] <= (WDATA[31:0] & wmask) | (int_input_r[31:0] & ~wmask);
    end
end

// int_input_r[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_input_r[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_INPUT_R_DATA_1)
            int_input_r[63:32] <= (WDATA[31:0] & wmask) | (int_input_r[63:32] & ~wmask);
    end
end

// int_output_r[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_output_r[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OUTPUT_R_DATA_0)
            int_output_r[31:0] <= (WDATA[31:0] & wmask) | (int_output_r[31:0] & ~wmask);
    end
end

// int_output_r[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_output_r[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OUTPUT_R_DATA_1)
            int_output_r[63:32] <= (WDATA[31:0] & wmask) | (int_output_r[63:32] & ~wmask);
    end
end

// int_axiWeightInput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiWeightInput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIWEIGHTINPUT_DATA_0)
            int_axiWeightInput[31:0] <= (WDATA[31:0] & wmask) | (int_axiWeightInput[31:0] & ~wmask);
    end
end

// int_axiWeightInput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiWeightInput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIWEIGHTINPUT_DATA_1)
            int_axiWeightInput[63:32] <= (WDATA[31:0] & wmask) | (int_axiWeightInput[63:32] & ~wmask);
    end
end

// int_axiBiasInput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiBiasInput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIBIASINPUT_DATA_0)
            int_axiBiasInput[31:0] <= (WDATA[31:0] & wmask) | (int_axiBiasInput[31:0] & ~wmask);
    end
end

// int_axiBiasInput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiBiasInput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIBIASINPUT_DATA_1)
            int_axiBiasInput[63:32] <= (WDATA[31:0] & wmask) | (int_axiBiasInput[63:32] & ~wmask);
    end
end

// int_axiWeightOutput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiWeightOutput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIWEIGHTOUTPUT_DATA_0)
            int_axiWeightOutput[31:0] <= (WDATA[31:0] & wmask) | (int_axiWeightOutput[31:0] & ~wmask);
    end
end

// int_axiWeightOutput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiWeightOutput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIWEIGHTOUTPUT_DATA_1)
            int_axiWeightOutput[63:32] <= (WDATA[31:0] & wmask) | (int_axiWeightOutput[63:32] & ~wmask);
    end
end

// int_axiBiasOutput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiBiasOutput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIBIASOUTPUT_DATA_0)
            int_axiBiasOutput[31:0] <= (WDATA[31:0] & wmask) | (int_axiBiasOutput[31:0] & ~wmask);
    end
end

// int_axiBiasOutput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiBiasOutput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIBIASOUTPUT_DATA_1)
            int_axiBiasOutput[63:32] <= (WDATA[31:0] & wmask) | (int_axiBiasOutput[63:32] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
