// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module uz_NN_control_s_axi
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
    output wire [63:0]                   A_input,
    output wire [63:0]                   B1_input,
    output wire [63:0]                   B2_input,
    output wire [63:0]                   B3_input,
    output wire [63:0]                   B4_input,
    output wire [63:0]                   C_output,
    output wire [63:0]                   Bias1_input,
    output wire [63:0]                   Bias2_input,
    output wire [63:0]                   Bias3_input,
    output wire [63:0]                   Bias4_input,
    output wire [0:0]                    copy_mats_flag,
    output wire [31:0]                   A_rows,
    output wire [31:0]                   B1_rows,
    output wire [31:0]                   B1_columns,
    output wire [31:0]                   B2_columns,
    input  wire [0:0]                    copy_flag_out,
    input  wire [0:0]                    matrices_updated_out,
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
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of A_input
//        bit 31~0 - A_input[31:0] (Read/Write)
// 0x14 : Data signal of A_input
//        bit 31~0 - A_input[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of B1_input
//        bit 31~0 - B1_input[31:0] (Read/Write)
// 0x20 : Data signal of B1_input
//        bit 31~0 - B1_input[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of B2_input
//        bit 31~0 - B2_input[31:0] (Read/Write)
// 0x2c : Data signal of B2_input
//        bit 31~0 - B2_input[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of B3_input
//        bit 31~0 - B3_input[31:0] (Read/Write)
// 0x38 : Data signal of B3_input
//        bit 31~0 - B3_input[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of B4_input
//        bit 31~0 - B4_input[31:0] (Read/Write)
// 0x44 : Data signal of B4_input
//        bit 31~0 - B4_input[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of C_output
//        bit 31~0 - C_output[31:0] (Read/Write)
// 0x50 : Data signal of C_output
//        bit 31~0 - C_output[63:32] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of Bias1_input
//        bit 31~0 - Bias1_input[31:0] (Read/Write)
// 0x5c : Data signal of Bias1_input
//        bit 31~0 - Bias1_input[63:32] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of Bias2_input
//        bit 31~0 - Bias2_input[31:0] (Read/Write)
// 0x68 : Data signal of Bias2_input
//        bit 31~0 - Bias2_input[63:32] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of Bias3_input
//        bit 31~0 - Bias3_input[31:0] (Read/Write)
// 0x74 : Data signal of Bias3_input
//        bit 31~0 - Bias3_input[63:32] (Read/Write)
// 0x78 : reserved
// 0x7c : Data signal of Bias4_input
//        bit 31~0 - Bias4_input[31:0] (Read/Write)
// 0x80 : Data signal of Bias4_input
//        bit 31~0 - Bias4_input[63:32] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of copy_mats_flag
//        bit 0  - copy_mats_flag[0] (Read/Write)
//        others - reserved
// 0x8c : reserved
// 0x90 : Data signal of A_rows
//        bit 31~0 - A_rows[31:0] (Read/Write)
// 0x94 : reserved
// 0x98 : Data signal of B1_rows
//        bit 31~0 - B1_rows[31:0] (Read/Write)
// 0x9c : reserved
// 0xa0 : Data signal of B1_columns
//        bit 31~0 - B1_columns[31:0] (Read/Write)
// 0xa4 : reserved
// 0xa8 : Data signal of B2_columns
//        bit 31~0 - B2_columns[31:0] (Read/Write)
// 0xac : reserved
// 0xb0 : Data signal of copy_flag_out
//        bit 0  - copy_flag_out[0] (Read)
//        others - reserved
// 0xb4 : reserved
// 0xc0 : Data signal of matrices_updated_out
//        bit 0  - matrices_updated_out[0] (Read)
//        others - reserved
// 0xc4 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL                     = 8'h00,
    ADDR_GIE                         = 8'h04,
    ADDR_IER                         = 8'h08,
    ADDR_ISR                         = 8'h0c,
    ADDR_A_INPUT_DATA_0              = 8'h10,
    ADDR_A_INPUT_DATA_1              = 8'h14,
    ADDR_A_INPUT_CTRL                = 8'h18,
    ADDR_B1_INPUT_DATA_0             = 8'h1c,
    ADDR_B1_INPUT_DATA_1             = 8'h20,
    ADDR_B1_INPUT_CTRL               = 8'h24,
    ADDR_B2_INPUT_DATA_0             = 8'h28,
    ADDR_B2_INPUT_DATA_1             = 8'h2c,
    ADDR_B2_INPUT_CTRL               = 8'h30,
    ADDR_B3_INPUT_DATA_0             = 8'h34,
    ADDR_B3_INPUT_DATA_1             = 8'h38,
    ADDR_B3_INPUT_CTRL               = 8'h3c,
    ADDR_B4_INPUT_DATA_0             = 8'h40,
    ADDR_B4_INPUT_DATA_1             = 8'h44,
    ADDR_B4_INPUT_CTRL               = 8'h48,
    ADDR_C_OUTPUT_DATA_0             = 8'h4c,
    ADDR_C_OUTPUT_DATA_1             = 8'h50,
    ADDR_C_OUTPUT_CTRL               = 8'h54,
    ADDR_BIAS1_INPUT_DATA_0          = 8'h58,
    ADDR_BIAS1_INPUT_DATA_1          = 8'h5c,
    ADDR_BIAS1_INPUT_CTRL            = 8'h60,
    ADDR_BIAS2_INPUT_DATA_0          = 8'h64,
    ADDR_BIAS2_INPUT_DATA_1          = 8'h68,
    ADDR_BIAS2_INPUT_CTRL            = 8'h6c,
    ADDR_BIAS3_INPUT_DATA_0          = 8'h70,
    ADDR_BIAS3_INPUT_DATA_1          = 8'h74,
    ADDR_BIAS3_INPUT_CTRL            = 8'h78,
    ADDR_BIAS4_INPUT_DATA_0          = 8'h7c,
    ADDR_BIAS4_INPUT_DATA_1          = 8'h80,
    ADDR_BIAS4_INPUT_CTRL            = 8'h84,
    ADDR_COPY_MATS_FLAG_DATA_0       = 8'h88,
    ADDR_COPY_MATS_FLAG_CTRL         = 8'h8c,
    ADDR_A_ROWS_DATA_0               = 8'h90,
    ADDR_A_ROWS_CTRL                 = 8'h94,
    ADDR_B1_ROWS_DATA_0              = 8'h98,
    ADDR_B1_ROWS_CTRL                = 8'h9c,
    ADDR_B1_COLUMNS_DATA_0           = 8'ha0,
    ADDR_B1_COLUMNS_CTRL             = 8'ha4,
    ADDR_B2_COLUMNS_DATA_0           = 8'ha8,
    ADDR_B2_COLUMNS_CTRL             = 8'hac,
    ADDR_COPY_FLAG_OUT_DATA_0        = 8'hb0,
    ADDR_COPY_FLAG_OUT_CTRL          = 8'hb4,
    ADDR_MATRICES_UPDATED_OUT_DATA_0 = 8'hc0,
    ADDR_MATRICES_UPDATED_OUT_CTRL   = 8'hc4,
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
    reg                           int_ap_ready = 1'b0;
    wire                          task_ap_ready;
    reg                           int_ap_done = 1'b0;
    wire                          task_ap_done;
    reg                           int_task_ap_done = 1'b0;
    reg                           int_ap_start = 1'b0;
    reg                           int_interrupt = 1'b0;
    reg                           int_auto_restart = 1'b0;
    reg                           auto_restart_status = 1'b0;
    wire                          auto_restart_done;
    reg                           int_gie = 1'b0;
    reg  [1:0]                    int_ier = 2'b0;
    reg  [1:0]                    int_isr = 2'b0;
    reg  [63:0]                   int_A_input = 'b0;
    reg  [63:0]                   int_B1_input = 'b0;
    reg  [63:0]                   int_B2_input = 'b0;
    reg  [63:0]                   int_B3_input = 'b0;
    reg  [63:0]                   int_B4_input = 'b0;
    reg  [63:0]                   int_C_output = 'b0;
    reg  [63:0]                   int_Bias1_input = 'b0;
    reg  [63:0]                   int_Bias2_input = 'b0;
    reg  [63:0]                   int_Bias3_input = 'b0;
    reg  [63:0]                   int_Bias4_input = 'b0;
    reg  [0:0]                    int_copy_mats_flag = 'b0;
    reg  [31:0]                   int_A_rows = 'b0;
    reg  [31:0]                   int_B1_rows = 'b0;
    reg  [31:0]                   int_B1_columns = 'b0;
    reg  [31:0]                   int_B2_columns = 'b0;
    reg  [0:0]                    int_copy_flag_out = 'b0;
    reg  [0:0]                    int_matrices_updated_out = 'b0;

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
                    rdata[1] <= int_task_ap_done;
                    rdata[2] <= int_ap_idle;
                    rdata[3] <= int_ap_ready;
                    rdata[7] <= int_auto_restart;
                    rdata[9] <= int_interrupt;
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
                ADDR_A_INPUT_DATA_0: begin
                    rdata <= int_A_input[31:0];
                end
                ADDR_A_INPUT_DATA_1: begin
                    rdata <= int_A_input[63:32];
                end
                ADDR_B1_INPUT_DATA_0: begin
                    rdata <= int_B1_input[31:0];
                end
                ADDR_B1_INPUT_DATA_1: begin
                    rdata <= int_B1_input[63:32];
                end
                ADDR_B2_INPUT_DATA_0: begin
                    rdata <= int_B2_input[31:0];
                end
                ADDR_B2_INPUT_DATA_1: begin
                    rdata <= int_B2_input[63:32];
                end
                ADDR_B3_INPUT_DATA_0: begin
                    rdata <= int_B3_input[31:0];
                end
                ADDR_B3_INPUT_DATA_1: begin
                    rdata <= int_B3_input[63:32];
                end
                ADDR_B4_INPUT_DATA_0: begin
                    rdata <= int_B4_input[31:0];
                end
                ADDR_B4_INPUT_DATA_1: begin
                    rdata <= int_B4_input[63:32];
                end
                ADDR_C_OUTPUT_DATA_0: begin
                    rdata <= int_C_output[31:0];
                end
                ADDR_C_OUTPUT_DATA_1: begin
                    rdata <= int_C_output[63:32];
                end
                ADDR_BIAS1_INPUT_DATA_0: begin
                    rdata <= int_Bias1_input[31:0];
                end
                ADDR_BIAS1_INPUT_DATA_1: begin
                    rdata <= int_Bias1_input[63:32];
                end
                ADDR_BIAS2_INPUT_DATA_0: begin
                    rdata <= int_Bias2_input[31:0];
                end
                ADDR_BIAS2_INPUT_DATA_1: begin
                    rdata <= int_Bias2_input[63:32];
                end
                ADDR_BIAS3_INPUT_DATA_0: begin
                    rdata <= int_Bias3_input[31:0];
                end
                ADDR_BIAS3_INPUT_DATA_1: begin
                    rdata <= int_Bias3_input[63:32];
                end
                ADDR_BIAS4_INPUT_DATA_0: begin
                    rdata <= int_Bias4_input[31:0];
                end
                ADDR_BIAS4_INPUT_DATA_1: begin
                    rdata <= int_Bias4_input[63:32];
                end
                ADDR_COPY_MATS_FLAG_DATA_0: begin
                    rdata <= int_copy_mats_flag[0:0];
                end
                ADDR_A_ROWS_DATA_0: begin
                    rdata <= int_A_rows[31:0];
                end
                ADDR_B1_ROWS_DATA_0: begin
                    rdata <= int_B1_rows[31:0];
                end
                ADDR_B1_COLUMNS_DATA_0: begin
                    rdata <= int_B1_columns[31:0];
                end
                ADDR_B2_COLUMNS_DATA_0: begin
                    rdata <= int_B2_columns[31:0];
                end
                ADDR_COPY_FLAG_OUT_DATA_0: begin
                    rdata <= int_copy_flag_out[0:0];
                end
                ADDR_MATRICES_UPDATED_OUT_DATA_0: begin
                    rdata <= int_matrices_updated_out[0:0];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt         = int_interrupt;
assign ap_start          = int_ap_start;
assign task_ap_done      = (ap_done && !auto_restart_status) || auto_restart_done;
assign task_ap_ready     = ap_ready && !int_auto_restart;
assign auto_restart_done = auto_restart_status && (ap_idle && !int_ap_idle);
assign A_input           = int_A_input;
assign B1_input          = int_B1_input;
assign B2_input          = int_B2_input;
assign B3_input          = int_B3_input;
assign B4_input          = int_B4_input;
assign C_output          = int_C_output;
assign Bias1_input       = int_Bias1_input;
assign Bias2_input       = int_Bias2_input;
assign Bias3_input       = int_Bias3_input;
assign Bias4_input       = int_Bias4_input;
assign copy_mats_flag    = int_copy_mats_flag;
assign A_rows            = int_A_rows;
assign B1_rows           = int_B1_rows;
assign B1_columns        = int_B1_columns;
assign B2_columns        = int_B2_columns;
// int_interrupt
always @(posedge ACLK) begin
    if (ARESET)
        int_interrupt <= 1'b0;
    else if (ACLK_EN) begin
        if (int_gie && (|int_isr))
            int_interrupt <= 1'b1;
        else
            int_interrupt <= 1'b0;
    end
end

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
            int_ap_done <= ap_done;
    end
end

// int_task_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_task_ap_done <= 1'b0;
    else if (ACLK_EN) begin
        if (task_ap_done)
            int_task_ap_done <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_task_ap_done <= 1'b0; // clear on read
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
        if (task_ap_ready)
            int_ap_ready <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_ap_ready <= 1'b0;
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

// auto_restart_status
always @(posedge ACLK) begin
    if (ARESET)
        auto_restart_status <= 1'b0;
    else if (ACLK_EN) begin
        if (int_auto_restart)
            auto_restart_status <= 1'b1;
        else if (ap_idle)
            auto_restart_status <= 1'b0;
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

// int_A_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_A_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_A_INPUT_DATA_0)
            int_A_input[31:0] <= (WDATA[31:0] & wmask) | (int_A_input[31:0] & ~wmask);
    end
end

// int_A_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_A_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_A_INPUT_DATA_1)
            int_A_input[63:32] <= (WDATA[31:0] & wmask) | (int_A_input[63:32] & ~wmask);
    end
end

// int_B1_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B1_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B1_INPUT_DATA_0)
            int_B1_input[31:0] <= (WDATA[31:0] & wmask) | (int_B1_input[31:0] & ~wmask);
    end
end

// int_B1_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B1_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B1_INPUT_DATA_1)
            int_B1_input[63:32] <= (WDATA[31:0] & wmask) | (int_B1_input[63:32] & ~wmask);
    end
end

// int_B2_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B2_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B2_INPUT_DATA_0)
            int_B2_input[31:0] <= (WDATA[31:0] & wmask) | (int_B2_input[31:0] & ~wmask);
    end
end

// int_B2_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B2_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B2_INPUT_DATA_1)
            int_B2_input[63:32] <= (WDATA[31:0] & wmask) | (int_B2_input[63:32] & ~wmask);
    end
end

// int_B3_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B3_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B3_INPUT_DATA_0)
            int_B3_input[31:0] <= (WDATA[31:0] & wmask) | (int_B3_input[31:0] & ~wmask);
    end
end

// int_B3_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B3_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B3_INPUT_DATA_1)
            int_B3_input[63:32] <= (WDATA[31:0] & wmask) | (int_B3_input[63:32] & ~wmask);
    end
end

// int_B4_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B4_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B4_INPUT_DATA_0)
            int_B4_input[31:0] <= (WDATA[31:0] & wmask) | (int_B4_input[31:0] & ~wmask);
    end
end

// int_B4_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B4_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B4_INPUT_DATA_1)
            int_B4_input[63:32] <= (WDATA[31:0] & wmask) | (int_B4_input[63:32] & ~wmask);
    end
end

// int_C_output[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_C_output[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_C_OUTPUT_DATA_0)
            int_C_output[31:0] <= (WDATA[31:0] & wmask) | (int_C_output[31:0] & ~wmask);
    end
end

// int_C_output[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_C_output[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_C_OUTPUT_DATA_1)
            int_C_output[63:32] <= (WDATA[31:0] & wmask) | (int_C_output[63:32] & ~wmask);
    end
end

// int_Bias1_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias1_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS1_INPUT_DATA_0)
            int_Bias1_input[31:0] <= (WDATA[31:0] & wmask) | (int_Bias1_input[31:0] & ~wmask);
    end
end

// int_Bias1_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias1_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS1_INPUT_DATA_1)
            int_Bias1_input[63:32] <= (WDATA[31:0] & wmask) | (int_Bias1_input[63:32] & ~wmask);
    end
end

// int_Bias2_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias2_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS2_INPUT_DATA_0)
            int_Bias2_input[31:0] <= (WDATA[31:0] & wmask) | (int_Bias2_input[31:0] & ~wmask);
    end
end

// int_Bias2_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias2_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS2_INPUT_DATA_1)
            int_Bias2_input[63:32] <= (WDATA[31:0] & wmask) | (int_Bias2_input[63:32] & ~wmask);
    end
end

// int_Bias3_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias3_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS3_INPUT_DATA_0)
            int_Bias3_input[31:0] <= (WDATA[31:0] & wmask) | (int_Bias3_input[31:0] & ~wmask);
    end
end

// int_Bias3_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias3_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS3_INPUT_DATA_1)
            int_Bias3_input[63:32] <= (WDATA[31:0] & wmask) | (int_Bias3_input[63:32] & ~wmask);
    end
end

// int_Bias4_input[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias4_input[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS4_INPUT_DATA_0)
            int_Bias4_input[31:0] <= (WDATA[31:0] & wmask) | (int_Bias4_input[31:0] & ~wmask);
    end
end

// int_Bias4_input[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_Bias4_input[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS4_INPUT_DATA_1)
            int_Bias4_input[63:32] <= (WDATA[31:0] & wmask) | (int_Bias4_input[63:32] & ~wmask);
    end
end

// int_copy_mats_flag[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_copy_mats_flag[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_COPY_MATS_FLAG_DATA_0)
            int_copy_mats_flag[0:0] <= (WDATA[31:0] & wmask) | (int_copy_mats_flag[0:0] & ~wmask);
    end
end

// int_A_rows[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_A_rows[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_A_ROWS_DATA_0)
            int_A_rows[31:0] <= (WDATA[31:0] & wmask) | (int_A_rows[31:0] & ~wmask);
    end
end

// int_B1_rows[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B1_rows[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B1_ROWS_DATA_0)
            int_B1_rows[31:0] <= (WDATA[31:0] & wmask) | (int_B1_rows[31:0] & ~wmask);
    end
end

// int_B1_columns[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B1_columns[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B1_COLUMNS_DATA_0)
            int_B1_columns[31:0] <= (WDATA[31:0] & wmask) | (int_B1_columns[31:0] & ~wmask);
    end
end

// int_B2_columns[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B2_columns[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B2_COLUMNS_DATA_0)
            int_B2_columns[31:0] <= (WDATA[31:0] & wmask) | (int_B2_columns[31:0] & ~wmask);
    end
end

// int_copy_flag_out
always @(posedge ACLK) begin
    if (ARESET)
        int_copy_flag_out <= 0;
    else if (ACLK_EN) begin
        if (ap_done)
            int_copy_flag_out <= copy_flag_out;
    end
end

// int_matrices_updated_out
always @(posedge ACLK) begin
    if (ARESET)
        int_matrices_updated_out <= 0;
    else if (ACLK_EN) begin
        if (ap_done)
            int_matrices_updated_out <= matrices_updated_out;
    end
end

//synthesis translate_off
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (int_gie & ~int_isr[0] & int_ier[0] & ap_done)
            $display ("// Interrupt Monitor : interrupt for ap_done detected @ \"%0t\"", $time);
        if (int_gie & ~int_isr[1] & int_ier[1] & ap_ready)
            $display ("// Interrupt Monitor : interrupt for ap_ready detected @ \"%0t\"", $time);
    end
end
//synthesis translate_on

//------------------------Memory logic-------------------

endmodule
