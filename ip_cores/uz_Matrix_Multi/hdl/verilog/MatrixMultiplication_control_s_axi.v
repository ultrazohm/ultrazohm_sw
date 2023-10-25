// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module MatrixMultiplication_control_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 9,
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
    output wire [63:0]                   A_rows,
    input  wire [2:0]                    A_address0,
    input  wire                          A_ce0,
    output wire [31:0]                   A_q0,
    input  wire [2:0]                    C_out_address0,
    input  wire                          C_out_ce0,
    input  wire                          C_out_we0,
    input  wire [31:0]                   C_out_d0,
    output wire [31:0]                   C_out_q0,
    output wire [63:0]                   B_rows,
    output wire [63:0]                   B_columns,
    output wire [0:0]                    trigger,
    input  wire [4:0]                    B_address0,
    input  wire                          B_ce0,
    output wire [31:0]                   B_q0,
    output wire [0:0]                    is_done_i,
    input  wire [0:0]                    is_done_o,
    input  wire                          is_done_o_ap_vld
);
//------------------------Address Info-------------------
// 0x000 : reserved
// 0x004 : reserved
// 0x008 : reserved
// 0x00c : reserved
// 0x010 : Data signal of A_rows
//         bit 31~0 - A_rows[31:0] (Read/Write)
// 0x014 : Data signal of A_rows
//         bit 31~0 - A_rows[63:32] (Read/Write)
// 0x018 : reserved
// 0x060 : Data signal of B_rows
//         bit 31~0 - B_rows[31:0] (Read/Write)
// 0x064 : Data signal of B_rows
//         bit 31~0 - B_rows[63:32] (Read/Write)
// 0x068 : reserved
// 0x06c : Data signal of B_columns
//         bit 31~0 - B_columns[31:0] (Read/Write)
// 0x070 : Data signal of B_columns
//         bit 31~0 - B_columns[63:32] (Read/Write)
// 0x074 : reserved
// 0x078 : Data signal of trigger
//         bit 0  - trigger[0] (Read/Write)
//         others - reserved
// 0x07c : reserved
// 0x100 : Data signal of is_done_i
//         bit 0  - is_done_i[0] (Read/Write)
//         others - reserved
// 0x104 : reserved
// 0x108 : Data signal of is_done_o
//         bit 0  - is_done_o[0] (Read)
//         others - reserved
// 0x10c : Control signal of is_done_o
//         bit 0  - is_done_o_ap_vld (Read/COR)
//         others - reserved
// 0x020 ~
// 0x03f : Memory 'A' (5 * 32b)
//         Word n : bit [31:0] - A[n]
// 0x040 ~
// 0x05f : Memory 'C_out' (5 * 32b)
//         Word n : bit [31:0] - C_out[n]
// 0x080 ~
// 0x0ff : Memory 'B' (25 * 32b)
//         Word n : bit [31:0] - B[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_A_ROWS_DATA_0    = 9'h010,
    ADDR_A_ROWS_DATA_1    = 9'h014,
    ADDR_A_ROWS_CTRL      = 9'h018,
    ADDR_B_ROWS_DATA_0    = 9'h060,
    ADDR_B_ROWS_DATA_1    = 9'h064,
    ADDR_B_ROWS_CTRL      = 9'h068,
    ADDR_B_COLUMNS_DATA_0 = 9'h06c,
    ADDR_B_COLUMNS_DATA_1 = 9'h070,
    ADDR_B_COLUMNS_CTRL   = 9'h074,
    ADDR_TRIGGER_DATA_0   = 9'h078,
    ADDR_TRIGGER_CTRL     = 9'h07c,
    ADDR_IS_DONE_I_DATA_0 = 9'h100,
    ADDR_IS_DONE_I_CTRL   = 9'h104,
    ADDR_IS_DONE_O_DATA_0 = 9'h108,
    ADDR_IS_DONE_O_CTRL   = 9'h10c,
    ADDR_A_BASE           = 9'h020,
    ADDR_A_HIGH           = 9'h03f,
    ADDR_C_OUT_BASE       = 9'h040,
    ADDR_C_OUT_HIGH       = 9'h05f,
    ADDR_B_BASE           = 9'h080,
    ADDR_B_HIGH           = 9'h0ff,
    WRIDLE                = 2'd0,
    WRDATA                = 2'd1,
    WRRESP                = 2'd2,
    WRRESET               = 2'd3,
    RDIDLE                = 2'd0,
    RDDATA                = 2'd1,
    RDRESET               = 2'd2,
    ADDR_BITS                = 9;

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
    reg  [63:0]                   int_A_rows = 'b0;
    reg  [63:0]                   int_B_rows = 'b0;
    reg  [63:0]                   int_B_columns = 'b0;
    reg  [0:0]                    int_trigger = 'b0;
    reg  [0:0]                    int_is_done_i = 'b0;
    reg                           int_is_done_o_ap_vld;
    reg  [0:0]                    int_is_done_o = 'b0;
    // memory signals
    wire [2:0]                    int_A_address0;
    wire                          int_A_ce0;
    wire [31:0]                   int_A_q0;
    wire [2:0]                    int_A_address1;
    wire                          int_A_ce1;
    wire                          int_A_we1;
    wire [3:0]                    int_A_be1;
    wire [31:0]                   int_A_d1;
    wire [31:0]                   int_A_q1;
    reg                           int_A_read;
    reg                           int_A_write;
    wire [2:0]                    int_C_out_address0;
    wire                          int_C_out_ce0;
    wire [3:0]                    int_C_out_be0;
    wire [31:0]                   int_C_out_d0;
    wire [31:0]                   int_C_out_q0;
    wire [2:0]                    int_C_out_address1;
    wire                          int_C_out_ce1;
    wire                          int_C_out_we1;
    wire [3:0]                    int_C_out_be1;
    wire [31:0]                   int_C_out_d1;
    wire [31:0]                   int_C_out_q1;
    reg                           int_C_out_read;
    reg                           int_C_out_write;
    wire [4:0]                    int_B_address0;
    wire                          int_B_ce0;
    wire [31:0]                   int_B_q0;
    wire [4:0]                    int_B_address1;
    wire                          int_B_ce1;
    wire                          int_B_we1;
    wire [3:0]                    int_B_be1;
    wire [31:0]                   int_B_d1;
    wire [31:0]                   int_B_q1;
    reg                           int_B_read;
    reg                           int_B_write;

//------------------------Instantiation------------------
// int_A
MatrixMultiplication_control_s_axi_ram #(
    .MEM_STYLE ( "auto" ),
    .MEM_TYPE  ( "2P" ),
    .BYTES     ( 4 ),
    .DEPTH     ( 5 )
) int_A (
    .clk0      ( ACLK ),
    .address0  ( int_A_address0 ),
    .ce0       ( int_A_ce0 ),
    .we0       ( {4{1'b0}} ),
    .d0        ( {32{1'b0}} ),
    .q0        ( int_A_q0 ),
    .clk1      ( ACLK ),
    .address1  ( int_A_address1 ),
    .ce1       ( int_A_ce1 ),
    .we1       ( int_A_be1 ),
    .d1        ( int_A_d1 ),
    .q1        ( int_A_q1 )
);
// int_C_out
MatrixMultiplication_control_s_axi_ram #(
    .MEM_STYLE ( "auto" ),
    .MEM_TYPE  ( "T2P" ),
    .BYTES     ( 4 ),
    .DEPTH     ( 5 )
) int_C_out (
    .clk0      ( ACLK ),
    .address0  ( int_C_out_address0 ),
    .ce0       ( int_C_out_ce0 ),
    .we0       ( int_C_out_be0 ),
    .d0        ( int_C_out_d0 ),
    .q0        ( int_C_out_q0 ),
    .clk1      ( ACLK ),
    .address1  ( int_C_out_address1 ),
    .ce1       ( int_C_out_ce1 ),
    .we1       ( int_C_out_be1 ),
    .d1        ( int_C_out_d1 ),
    .q1        ( int_C_out_q1 )
);
// int_B
MatrixMultiplication_control_s_axi_ram #(
    .MEM_STYLE ( "auto" ),
    .MEM_TYPE  ( "2P" ),
    .BYTES     ( 4 ),
    .DEPTH     ( 25 )
) int_B (
    .clk0      ( ACLK ),
    .address0  ( int_B_address0 ),
    .ce0       ( int_B_ce0 ),
    .we0       ( {4{1'b0}} ),
    .d0        ( {32{1'b0}} ),
    .q0        ( int_B_q0 ),
    .clk1      ( ACLK ),
    .address1  ( int_B_address1 ),
    .ce1       ( int_B_ce1 ),
    .we1       ( int_B_be1 ),
    .d1        ( int_B_d1 ),
    .q1        ( int_B_q1 )
);


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA) && (!ar_hs);
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
            if (w_hs)
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
assign RVALID  = (rstate == RDDATA) & !int_A_read & !int_C_out_read & !int_B_read;
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
                ADDR_A_ROWS_DATA_0: begin
                    rdata <= int_A_rows[31:0];
                end
                ADDR_A_ROWS_DATA_1: begin
                    rdata <= int_A_rows[63:32];
                end
                ADDR_B_ROWS_DATA_0: begin
                    rdata <= int_B_rows[31:0];
                end
                ADDR_B_ROWS_DATA_1: begin
                    rdata <= int_B_rows[63:32];
                end
                ADDR_B_COLUMNS_DATA_0: begin
                    rdata <= int_B_columns[31:0];
                end
                ADDR_B_COLUMNS_DATA_1: begin
                    rdata <= int_B_columns[63:32];
                end
                ADDR_TRIGGER_DATA_0: begin
                    rdata <= int_trigger[0:0];
                end
                ADDR_IS_DONE_I_DATA_0: begin
                    rdata <= int_is_done_i[0:0];
                end
                ADDR_IS_DONE_O_DATA_0: begin
                    rdata <= int_is_done_o[0:0];
                end
                ADDR_IS_DONE_O_CTRL: begin
                    rdata[0] <= int_is_done_o_ap_vld;
                end
            endcase
        end
        else if (int_A_read) begin
            rdata <= int_A_q1;
        end
        else if (int_C_out_read) begin
            rdata <= int_C_out_q1;
        end
        else if (int_B_read) begin
            rdata <= int_B_q1;
        end
    end
end


//------------------------Register logic-----------------
assign A_rows    = int_A_rows;
assign B_rows    = int_B_rows;
assign B_columns = int_B_columns;
assign trigger   = int_trigger;
assign is_done_i = int_is_done_i;
// int_A_rows[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_A_rows[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_A_ROWS_DATA_0)
            int_A_rows[31:0] <= (WDATA[31:0] & wmask) | (int_A_rows[31:0] & ~wmask);
    end
end

// int_A_rows[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_A_rows[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_A_ROWS_DATA_1)
            int_A_rows[63:32] <= (WDATA[31:0] & wmask) | (int_A_rows[63:32] & ~wmask);
    end
end

// int_B_rows[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B_rows[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B_ROWS_DATA_0)
            int_B_rows[31:0] <= (WDATA[31:0] & wmask) | (int_B_rows[31:0] & ~wmask);
    end
end

// int_B_rows[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B_rows[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B_ROWS_DATA_1)
            int_B_rows[63:32] <= (WDATA[31:0] & wmask) | (int_B_rows[63:32] & ~wmask);
    end
end

// int_B_columns[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_B_columns[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B_COLUMNS_DATA_0)
            int_B_columns[31:0] <= (WDATA[31:0] & wmask) | (int_B_columns[31:0] & ~wmask);
    end
end

// int_B_columns[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_B_columns[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_B_COLUMNS_DATA_1)
            int_B_columns[63:32] <= (WDATA[31:0] & wmask) | (int_B_columns[63:32] & ~wmask);
    end
end

// int_trigger[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_trigger[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_TRIGGER_DATA_0)
            int_trigger[0:0] <= (WDATA[31:0] & wmask) | (int_trigger[0:0] & ~wmask);
    end
end

// int_is_done_i[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_is_done_i[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IS_DONE_I_DATA_0)
            int_is_done_i[0:0] <= (WDATA[31:0] & wmask) | (int_is_done_i[0:0] & ~wmask);
    end
end

// int_is_done_o
always @(posedge ACLK) begin
    if (ARESET)
        int_is_done_o <= 0;
    else if (ACLK_EN) begin
        if (is_done_o_ap_vld)
            int_is_done_o <= is_done_o;
    end
end

// int_is_done_o_ap_vld
always @(posedge ACLK) begin
    if (ARESET)
        int_is_done_o_ap_vld <= 1'b0;
    else if (ACLK_EN) begin
        if (is_done_o_ap_vld)
            int_is_done_o_ap_vld <= 1'b1;
        else if (ar_hs && raddr == ADDR_IS_DONE_O_CTRL)
            int_is_done_o_ap_vld <= 1'b0; // clear on read
    end
end


//------------------------Memory logic-------------------
// A
assign int_A_address0     = A_address0;
assign int_A_ce0          = A_ce0;
assign A_q0               = int_A_q0;
assign int_A_address1     = ar_hs? raddr[4:2] : waddr[4:2];
assign int_A_ce1          = ar_hs | (int_A_write & WVALID);
assign int_A_we1          = int_A_write & w_hs;
assign int_A_be1          = int_A_we1 ? WSTRB : 'b0;
assign int_A_d1           = WDATA;
// C_out
assign int_C_out_address0 = C_out_address0;
assign int_C_out_ce0      = C_out_ce0;
assign int_C_out_be0      = {4{C_out_we0}};
assign int_C_out_d0       = C_out_d0;
assign C_out_q0           = int_C_out_q0;
assign int_C_out_address1 = ar_hs? raddr[4:2] : waddr[4:2];
assign int_C_out_ce1      = ar_hs | (int_C_out_write & WVALID);
assign int_C_out_we1      = int_C_out_write & w_hs;
assign int_C_out_be1      = int_C_out_we1 ? WSTRB : 'b0;
assign int_C_out_d1       = WDATA;
// B
assign int_B_address0     = B_address0;
assign int_B_ce0          = B_ce0;
assign B_q0               = int_B_q0;
assign int_B_address1     = ar_hs? raddr[6:2] : waddr[6:2];
assign int_B_ce1          = ar_hs | (int_B_write & WVALID);
assign int_B_we1          = int_B_write & w_hs;
assign int_B_be1          = int_B_we1 ? WSTRB : 'b0;
assign int_B_d1           = WDATA;
// int_A_read
always @(posedge ACLK) begin
    if (ARESET)
        int_A_read <= 1'b0;
    else if (ACLK_EN) begin
        if (ar_hs && raddr >= ADDR_A_BASE && raddr <= ADDR_A_HIGH)
            int_A_read <= 1'b1;
        else
            int_A_read <= 1'b0;
    end
end

// int_A_write
always @(posedge ACLK) begin
    if (ARESET)
        int_A_write <= 1'b0;
    else if (ACLK_EN) begin
        if (aw_hs && AWADDR[ADDR_BITS-1:0] >= ADDR_A_BASE && AWADDR[ADDR_BITS-1:0] <= ADDR_A_HIGH)
            int_A_write <= 1'b1;
        else if (w_hs)
            int_A_write <= 1'b0;
    end
end

// int_C_out_read
always @(posedge ACLK) begin
    if (ARESET)
        int_C_out_read <= 1'b0;
    else if (ACLK_EN) begin
        if (ar_hs && raddr >= ADDR_C_OUT_BASE && raddr <= ADDR_C_OUT_HIGH)
            int_C_out_read <= 1'b1;
        else
            int_C_out_read <= 1'b0;
    end
end

// int_C_out_write
always @(posedge ACLK) begin
    if (ARESET)
        int_C_out_write <= 1'b0;
    else if (ACLK_EN) begin
        if (aw_hs && AWADDR[ADDR_BITS-1:0] >= ADDR_C_OUT_BASE && AWADDR[ADDR_BITS-1:0] <= ADDR_C_OUT_HIGH)
            int_C_out_write <= 1'b1;
        else if (w_hs)
            int_C_out_write <= 1'b0;
    end
end

// int_B_read
always @(posedge ACLK) begin
    if (ARESET)
        int_B_read <= 1'b0;
    else if (ACLK_EN) begin
        if (ar_hs && raddr >= ADDR_B_BASE && raddr <= ADDR_B_HIGH)
            int_B_read <= 1'b1;
        else
            int_B_read <= 1'b0;
    end
end

// int_B_write
always @(posedge ACLK) begin
    if (ARESET)
        int_B_write <= 1'b0;
    else if (ACLK_EN) begin
        if (aw_hs && AWADDR[ADDR_BITS-1:0] >= ADDR_B_BASE && AWADDR[ADDR_BITS-1:0] <= ADDR_B_HIGH)
            int_B_write <= 1'b1;
        else if (w_hs)
            int_B_write <= 1'b0;
    end
end


endmodule


`timescale 1ns/1ps

module MatrixMultiplication_control_s_axi_ram
#(parameter
    MEM_STYLE = "auto",
    MEM_TYPE  = "S2P",
    BYTES  = 4,
    DEPTH  = 256,
    AWIDTH = log2(DEPTH)
) (
    input  wire               clk0,
    input  wire [AWIDTH-1:0]  address0,
    input  wire               ce0,
    input  wire [BYTES-1:0]   we0,
    input  wire [BYTES*8-1:0] d0,
    output reg  [BYTES*8-1:0] q0,
    input  wire               clk1,
    input  wire [AWIDTH-1:0]  address1,
    input  wire               ce1,
    input  wire [BYTES-1:0]   we1,
    input  wire [BYTES*8-1:0] d1,
    output reg  [BYTES*8-1:0] q1
);
//------------------------ Parameters -------------------
localparam
    BYTE_WIDTH = 8,
    PORT0 = (MEM_TYPE == "S2P") ? "WO" : ((MEM_TYPE == "2P") ? "RO" : "RW"),
    PORT1 = (MEM_TYPE == "S2P") ? "RO" : "RW";
//------------------------Local signal-------------------
(* ram_style = MEM_STYLE*)
reg  [BYTES*8-1:0] mem[0:DEPTH-1];
wire re0, re1;
//------------------------Task and function--------------
function integer log2;
    input integer x;
    integer n, m;
begin
    n = 1;
    m = 2;
    while (m < x) begin
        n = n + 1;
        m = m * 2;
    end
    log2 = n;
end
endfunction
//------------------------Body---------------------------
generate
    if (MEM_STYLE == "hls_ultra" && PORT0 == "RW") begin
        assign re0 = ce0 & ~|we0;
    end else begin
        assign re0 = ce0;
    end
endgenerate

generate
    if (MEM_STYLE == "hls_ultra" && PORT1 == "RW") begin
        assign re1 = ce1 & ~|we1;
    end else begin
        assign re1 = ce1;
    end
endgenerate

// read port 0
generate if (PORT0 != "WO") begin
    always @(posedge clk0) begin
        if (re0) q0 <= mem[address0];
    end
end
endgenerate

// read port 1
generate if (PORT1 != "WO") begin
    always @(posedge clk1) begin
        if (re1) q1 <= mem[address1];
    end
end
endgenerate

integer i;
// write port 0
generate if (PORT0 != "RO") begin
    always @(posedge clk0) begin
        if (ce0)
        for (i = 0; i < BYTES; i = i + 1)
            if (we0[i])
                mem[address0][i*BYTE_WIDTH +: BYTE_WIDTH] <= d0[i*BYTE_WIDTH +: BYTE_WIDTH];
    end
end
endgenerate

// write port 1
generate if (PORT1 != "RO") begin
    always @(posedge clk1) begin
        if (ce1)
        for (i = 0; i < BYTES; i = i + 1)
            if (we1[i])
                mem[address1][i*BYTE_WIDTH +: BYTE_WIDTH] <= d1[i*BYTE_WIDTH +: BYTE_WIDTH];
    end
end
endgenerate

endmodule

