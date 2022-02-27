// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module BGD_control_s_axi
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
    output wire [63:0]                   axiMlpResultsInput,
    output wire [63:0]                   axiClassesInput,
    output wire [63:0]                   axiWeightInput,
    output wire [63:0]                   axiBiasInput,
    output wire [63:0]                   axiWeightOutput,
    output wire [63:0]                   axiBiasOutput,
    output wire [31:0]                   numberInputs,
    output wire [31:0]                   numberOutputs,
    output wire [31:0]                   numberLayers,
    output wire [31:0]                   numberNeurons,
    output wire [31:0]                   loadParameters,
    output wire [31:0]                   batchSize,
    output wire [31:0]                   learningRate,
    output wire                          ap_start,
    input  wire                          ap_done,
    input  wire                          ap_ready,
    input  wire                          ap_idle
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
// 0x10 : Data signal of axiMlpResultsInput
//        bit 31~0 - axiMlpResultsInput[31:0] (Read/Write)
// 0x14 : Data signal of axiMlpResultsInput
//        bit 31~0 - axiMlpResultsInput[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of axiClassesInput
//        bit 31~0 - axiClassesInput[31:0] (Read/Write)
// 0x20 : Data signal of axiClassesInput
//        bit 31~0 - axiClassesInput[63:32] (Read/Write)
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
// 0x58 : Data signal of numberInputs
//        bit 31~0 - numberInputs[31:0] (Read/Write)
// 0x5c : reserved
// 0x60 : Data signal of numberOutputs
//        bit 31~0 - numberOutputs[31:0] (Read/Write)
// 0x64 : reserved
// 0x68 : Data signal of numberLayers
//        bit 31~0 - numberLayers[31:0] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of numberNeurons
//        bit 31~0 - numberNeurons[31:0] (Read/Write)
// 0x74 : reserved
// 0x78 : Data signal of loadParameters
//        bit 31~0 - loadParameters[31:0] (Read/Write)
// 0x7c : reserved
// 0x80 : Data signal of batchSize
//        bit 31~0 - batchSize[31:0] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of learningRate
//        bit 31~0 - learningRate[31:0] (Read/Write)
// 0x8c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL                   = 8'h00,
    ADDR_GIE                       = 8'h04,
    ADDR_IER                       = 8'h08,
    ADDR_ISR                       = 8'h0c,
    ADDR_AXIMLPRESULTSINPUT_DATA_0 = 8'h10,
    ADDR_AXIMLPRESULTSINPUT_DATA_1 = 8'h14,
    ADDR_AXIMLPRESULTSINPUT_CTRL   = 8'h18,
    ADDR_AXICLASSESINPUT_DATA_0    = 8'h1c,
    ADDR_AXICLASSESINPUT_DATA_1    = 8'h20,
    ADDR_AXICLASSESINPUT_CTRL      = 8'h24,
    ADDR_AXIWEIGHTINPUT_DATA_0     = 8'h28,
    ADDR_AXIWEIGHTINPUT_DATA_1     = 8'h2c,
    ADDR_AXIWEIGHTINPUT_CTRL       = 8'h30,
    ADDR_AXIBIASINPUT_DATA_0       = 8'h34,
    ADDR_AXIBIASINPUT_DATA_1       = 8'h38,
    ADDR_AXIBIASINPUT_CTRL         = 8'h3c,
    ADDR_AXIWEIGHTOUTPUT_DATA_0    = 8'h40,
    ADDR_AXIWEIGHTOUTPUT_DATA_1    = 8'h44,
    ADDR_AXIWEIGHTOUTPUT_CTRL      = 8'h48,
    ADDR_AXIBIASOUTPUT_DATA_0      = 8'h4c,
    ADDR_AXIBIASOUTPUT_DATA_1      = 8'h50,
    ADDR_AXIBIASOUTPUT_CTRL        = 8'h54,
    ADDR_NUMBERINPUTS_DATA_0       = 8'h58,
    ADDR_NUMBERINPUTS_CTRL         = 8'h5c,
    ADDR_NUMBEROUTPUTS_DATA_0      = 8'h60,
    ADDR_NUMBEROUTPUTS_CTRL        = 8'h64,
    ADDR_NUMBERLAYERS_DATA_0       = 8'h68,
    ADDR_NUMBERLAYERS_CTRL         = 8'h6c,
    ADDR_NUMBERNEURONS_DATA_0      = 8'h70,
    ADDR_NUMBERNEURONS_CTRL        = 8'h74,
    ADDR_LOADPARAMETERS_DATA_0     = 8'h78,
    ADDR_LOADPARAMETERS_CTRL       = 8'h7c,
    ADDR_BATCHSIZE_DATA_0          = 8'h80,
    ADDR_BATCHSIZE_CTRL            = 8'h84,
    ADDR_LEARNINGRATE_DATA_0       = 8'h88,
    ADDR_LEARNINGRATE_CTRL         = 8'h8c,
    WRIDLE                         = 2'd0,
    WRDATA                         = 2'd1,
    WRRESP                         = 2'd2,
    WRRESET                        = 2'd3,
    RDIDLE                         = 2'd0,
    RDDATA                         = 2'd1,
    RDRESET                        = 2'd2,
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
    reg  [63:0]                   int_axiMlpResultsInput = 'b0;
    reg  [63:0]                   int_axiClassesInput = 'b0;
    reg  [63:0]                   int_axiWeightInput = 'b0;
    reg  [63:0]                   int_axiBiasInput = 'b0;
    reg  [63:0]                   int_axiWeightOutput = 'b0;
    reg  [63:0]                   int_axiBiasOutput = 'b0;
    reg  [31:0]                   int_numberInputs = 'b0;
    reg  [31:0]                   int_numberOutputs = 'b0;
    reg  [31:0]                   int_numberLayers = 'b0;
    reg  [31:0]                   int_numberNeurons = 'b0;
    reg  [31:0]                   int_loadParameters = 'b0;
    reg  [31:0]                   int_batchSize = 'b0;
    reg  [31:0]                   int_learningRate = 'b0;

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
                ADDR_AXIMLPRESULTSINPUT_DATA_0: begin
                    rdata <= int_axiMlpResultsInput[31:0];
                end
                ADDR_AXIMLPRESULTSINPUT_DATA_1: begin
                    rdata <= int_axiMlpResultsInput[63:32];
                end
                ADDR_AXICLASSESINPUT_DATA_0: begin
                    rdata <= int_axiClassesInput[31:0];
                end
                ADDR_AXICLASSESINPUT_DATA_1: begin
                    rdata <= int_axiClassesInput[63:32];
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
                ADDR_NUMBERINPUTS_DATA_0: begin
                    rdata <= int_numberInputs[31:0];
                end
                ADDR_NUMBEROUTPUTS_DATA_0: begin
                    rdata <= int_numberOutputs[31:0];
                end
                ADDR_NUMBERLAYERS_DATA_0: begin
                    rdata <= int_numberLayers[31:0];
                end
                ADDR_NUMBERNEURONS_DATA_0: begin
                    rdata <= int_numberNeurons[31:0];
                end
                ADDR_LOADPARAMETERS_DATA_0: begin
                    rdata <= int_loadParameters[31:0];
                end
                ADDR_BATCHSIZE_DATA_0: begin
                    rdata <= int_batchSize[31:0];
                end
                ADDR_LEARNINGRATE_DATA_0: begin
                    rdata <= int_learningRate[31:0];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt          = int_gie & (|int_isr);
assign ap_start           = int_ap_start;
assign axiMlpResultsInput = int_axiMlpResultsInput;
assign axiClassesInput    = int_axiClassesInput;
assign axiWeightInput     = int_axiWeightInput;
assign axiBiasInput       = int_axiBiasInput;
assign axiWeightOutput    = int_axiWeightOutput;
assign axiBiasOutput      = int_axiBiasOutput;
assign numberInputs       = int_numberInputs;
assign numberOutputs      = int_numberOutputs;
assign numberLayers       = int_numberLayers;
assign numberNeurons      = int_numberNeurons;
assign loadParameters     = int_loadParameters;
assign batchSize          = int_batchSize;
assign learningRate       = int_learningRate;
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

// int_axiMlpResultsInput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiMlpResultsInput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIMLPRESULTSINPUT_DATA_0)
            int_axiMlpResultsInput[31:0] <= (WDATA[31:0] & wmask) | (int_axiMlpResultsInput[31:0] & ~wmask);
    end
end

// int_axiMlpResultsInput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiMlpResultsInput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXIMLPRESULTSINPUT_DATA_1)
            int_axiMlpResultsInput[63:32] <= (WDATA[31:0] & wmask) | (int_axiMlpResultsInput[63:32] & ~wmask);
    end
end

// int_axiClassesInput[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiClassesInput[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXICLASSESINPUT_DATA_0)
            int_axiClassesInput[31:0] <= (WDATA[31:0] & wmask) | (int_axiClassesInput[31:0] & ~wmask);
    end
end

// int_axiClassesInput[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_axiClassesInput[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AXICLASSESINPUT_DATA_1)
            int_axiClassesInput[63:32] <= (WDATA[31:0] & wmask) | (int_axiClassesInput[63:32] & ~wmask);
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

// int_numberInputs[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_numberInputs[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NUMBERINPUTS_DATA_0)
            int_numberInputs[31:0] <= (WDATA[31:0] & wmask) | (int_numberInputs[31:0] & ~wmask);
    end
end

// int_numberOutputs[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_numberOutputs[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NUMBEROUTPUTS_DATA_0)
            int_numberOutputs[31:0] <= (WDATA[31:0] & wmask) | (int_numberOutputs[31:0] & ~wmask);
    end
end

// int_numberLayers[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_numberLayers[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NUMBERLAYERS_DATA_0)
            int_numberLayers[31:0] <= (WDATA[31:0] & wmask) | (int_numberLayers[31:0] & ~wmask);
    end
end

// int_numberNeurons[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_numberNeurons[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_NUMBERNEURONS_DATA_0)
            int_numberNeurons[31:0] <= (WDATA[31:0] & wmask) | (int_numberNeurons[31:0] & ~wmask);
    end
end

// int_loadParameters[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_loadParameters[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_LOADPARAMETERS_DATA_0)
            int_loadParameters[31:0] <= (WDATA[31:0] & wmask) | (int_loadParameters[31:0] & ~wmask);
    end
end

// int_batchSize[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_batchSize[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BATCHSIZE_DATA_0)
            int_batchSize[31:0] <= (WDATA[31:0] & wmask) | (int_batchSize[31:0] & ~wmask);
    end
end

// int_learningRate[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_learningRate[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_LEARNINGRATE_DATA_0)
            int_learningRate[31:0] <= (WDATA[31:0] & wmask) | (int_learningRate[31:0] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
