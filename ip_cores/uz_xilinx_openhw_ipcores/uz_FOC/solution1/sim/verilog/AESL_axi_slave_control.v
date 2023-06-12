// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module AESL_axi_slave_control (
    clk,
    reset,
    TRAN_s_axi_control_AWADDR,
    TRAN_s_axi_control_AWVALID,
    TRAN_s_axi_control_AWREADY,
    TRAN_s_axi_control_WVALID,
    TRAN_s_axi_control_WREADY,
    TRAN_s_axi_control_WDATA,
    TRAN_s_axi_control_WSTRB,
    TRAN_s_axi_control_ARADDR,
    TRAN_s_axi_control_ARVALID,
    TRAN_s_axi_control_ARREADY,
    TRAN_s_axi_control_RVALID,
    TRAN_s_axi_control_RREADY,
    TRAN_s_axi_control_RDATA,
    TRAN_s_axi_control_RRESP,
    TRAN_s_axi_control_BVALID,
    TRAN_s_axi_control_BREADY,
    TRAN_s_axi_control_BRESP,
    TRAN_control_write_data_finish,
    TRAN_control_start_in,
    TRAN_control_idle_in,
    TRAN_control_ready_in,
    TRAN_control_done_in,
    TRAN_control_transaction_done_in
    );

//------------------------Parameter----------------------
`define TV_IN_axi_id_reference "../tv/cdatafile/c.uz_FOC.autotvin_axi_id_reference.dat"
`define TV_IN_axi_iq_reference "../tv/cdatafile/c.uz_FOC.autotvin_axi_iq_reference.dat"
`define TV_IN_axi_sampletime "../tv/cdatafile/c.uz_FOC.autotvin_axi_sampletime.dat"
`define TV_IN_axi_id_KI "../tv/cdatafile/c.uz_FOC.autotvin_axi_id_KI.dat"
`define TV_IN_axi_id_KP "../tv/cdatafile/c.uz_FOC.autotvin_axi_id_KP.dat"
`define TV_IN_axi_iq_KI "../tv/cdatafile/c.uz_FOC.autotvin_axi_iq_KI.dat"
`define TV_IN_axi_iq_KP "../tv/cdatafile/c.uz_FOC.autotvin_axi_iq_KP.dat"
`define TV_IN_axi_limit "../tv/cdatafile/c.uz_FOC.autotvin_axi_limit.dat"
`define TV_IN_axi_reset "../tv/cdatafile/c.uz_FOC.autotvin_axi_reset.dat"
parameter ADDR_WIDTH = 7;
parameter DATA_WIDTH = 32;
parameter axi_id_reference_DEPTH = 1;
reg [31 : 0] axi_id_reference_OPERATE_DEPTH = 0;
parameter axi_id_reference_c_bitwidth = 32;
parameter axi_iq_reference_DEPTH = 1;
reg [31 : 0] axi_iq_reference_OPERATE_DEPTH = 0;
parameter axi_iq_reference_c_bitwidth = 32;
parameter axi_sampletime_DEPTH = 1;
reg [31 : 0] axi_sampletime_OPERATE_DEPTH = 0;
parameter axi_sampletime_c_bitwidth = 32;
parameter axi_id_KI_DEPTH = 1;
reg [31 : 0] axi_id_KI_OPERATE_DEPTH = 0;
parameter axi_id_KI_c_bitwidth = 32;
parameter axi_id_KP_DEPTH = 1;
reg [31 : 0] axi_id_KP_OPERATE_DEPTH = 0;
parameter axi_id_KP_c_bitwidth = 32;
parameter axi_iq_KI_DEPTH = 1;
reg [31 : 0] axi_iq_KI_OPERATE_DEPTH = 0;
parameter axi_iq_KI_c_bitwidth = 32;
parameter axi_iq_KP_DEPTH = 1;
reg [31 : 0] axi_iq_KP_OPERATE_DEPTH = 0;
parameter axi_iq_KP_c_bitwidth = 32;
parameter axi_limit_DEPTH = 1;
reg [31 : 0] axi_limit_OPERATE_DEPTH = 0;
parameter axi_limit_c_bitwidth = 32;
parameter axi_reset_DEPTH = 1;
reg [31 : 0] axi_reset_OPERATE_DEPTH = 0;
parameter axi_reset_c_bitwidth = 1;
parameter axi_id_reference_data_in_addr = 16;
parameter axi_iq_reference_data_in_addr = 24;
parameter axi_sampletime_data_in_addr = 32;
parameter axi_id_KI_data_in_addr = 40;
parameter axi_id_KP_data_in_addr = 48;
parameter axi_iq_KI_data_in_addr = 56;
parameter axi_iq_KP_data_in_addr = 64;
parameter axi_limit_data_in_addr = 72;
parameter axi_reset_data_in_addr = 80;

output [ADDR_WIDTH - 1 : 0] TRAN_s_axi_control_AWADDR;
output  TRAN_s_axi_control_AWVALID;
input  TRAN_s_axi_control_AWREADY;
output  TRAN_s_axi_control_WVALID;
input  TRAN_s_axi_control_WREADY;
output [DATA_WIDTH - 1 : 0] TRAN_s_axi_control_WDATA;
output [DATA_WIDTH/8 - 1 : 0] TRAN_s_axi_control_WSTRB;
output [ADDR_WIDTH - 1 : 0] TRAN_s_axi_control_ARADDR;
output  TRAN_s_axi_control_ARVALID;
input  TRAN_s_axi_control_ARREADY;
input  TRAN_s_axi_control_RVALID;
output  TRAN_s_axi_control_RREADY;
input [DATA_WIDTH - 1 : 0] TRAN_s_axi_control_RDATA;
input [2 - 1 : 0] TRAN_s_axi_control_RRESP;
input  TRAN_s_axi_control_BVALID;
output  TRAN_s_axi_control_BREADY;
input [2 - 1 : 0] TRAN_s_axi_control_BRESP;
output TRAN_control_write_data_finish;
input     clk;
input     reset;
input     TRAN_control_start_in;
input     TRAN_control_done_in;
input     TRAN_control_ready_in;
input     TRAN_control_idle_in;
input     TRAN_control_transaction_done_in;

reg [ADDR_WIDTH - 1 : 0] AWADDR_reg = 0;
reg  AWVALID_reg = 0;
reg  WVALID_reg = 0;
reg [DATA_WIDTH - 1 : 0] WDATA_reg = 0;
reg [DATA_WIDTH/8 - 1 : 0] WSTRB_reg = 0;
reg [ADDR_WIDTH - 1 : 0] ARADDR_reg = 0;
reg  ARVALID_reg = 0;
reg  RREADY_reg = 0;
reg [DATA_WIDTH - 1 : 0] RDATA_reg = 0;
reg  BREADY_reg = 0;
reg [DATA_WIDTH - 1 : 0] mem_axi_id_reference [axi_id_reference_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_id_reference [ (axi_id_reference_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_id_reference_DEPTH -1 : 0] = '{default : 'hz};
reg axi_id_reference_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_iq_reference [axi_iq_reference_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_iq_reference [ (axi_iq_reference_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_iq_reference_DEPTH -1 : 0] = '{default : 'hz};
reg axi_iq_reference_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_sampletime [axi_sampletime_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_sampletime [ (axi_sampletime_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_sampletime_DEPTH -1 : 0] = '{default : 'hz};
reg axi_sampletime_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_id_KI [axi_id_KI_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_id_KI [ (axi_id_KI_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_id_KI_DEPTH -1 : 0] = '{default : 'hz};
reg axi_id_KI_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_id_KP [axi_id_KP_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_id_KP [ (axi_id_KP_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_id_KP_DEPTH -1 : 0] = '{default : 'hz};
reg axi_id_KP_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_iq_KI [axi_iq_KI_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_iq_KI [ (axi_iq_KI_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_iq_KI_DEPTH -1 : 0] = '{default : 'hz};
reg axi_iq_KI_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_iq_KP [axi_iq_KP_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_iq_KP [ (axi_iq_KP_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_iq_KP_DEPTH -1 : 0] = '{default : 'hz};
reg axi_iq_KP_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_limit [axi_limit_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_limit [ (axi_limit_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_limit_DEPTH -1 : 0] = '{default : 'hz};
reg axi_limit_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_axi_reset [axi_reset_DEPTH - 1 : 0] = '{default : 'h0};
reg [DATA_WIDTH-1 : 0] image_mem_axi_reset [ (axi_reset_c_bitwidth+DATA_WIDTH-1)/DATA_WIDTH * axi_reset_DEPTH -1 : 0] = '{default : 'hz};
reg axi_reset_write_data_finish;
reg AESL_ready_out_index_reg = 0;
reg AESL_write_start_finish = 0;
reg AESL_ready_reg;
reg ready_initial;
reg AESL_done_index_reg = 0;
reg AESL_idle_index_reg = 0;
reg AESL_auto_restart_index_reg;
reg process_0_finish = 0;
reg process_1_finish = 0;
reg process_2_finish = 0;
reg process_3_finish = 0;
reg process_4_finish = 0;
reg process_5_finish = 0;
reg process_6_finish = 0;
reg process_7_finish = 0;
reg process_8_finish = 0;
//write axi_id_reference reg
reg [31 : 0] write_axi_id_reference_count = 0;
reg write_axi_id_reference_run_flag = 0;
reg write_one_axi_id_reference_data_done = 0;
//write axi_iq_reference reg
reg [31 : 0] write_axi_iq_reference_count = 0;
reg write_axi_iq_reference_run_flag = 0;
reg write_one_axi_iq_reference_data_done = 0;
//write axi_sampletime reg
reg [31 : 0] write_axi_sampletime_count = 0;
reg write_axi_sampletime_run_flag = 0;
reg write_one_axi_sampletime_data_done = 0;
//write axi_id_KI reg
reg [31 : 0] write_axi_id_KI_count = 0;
reg write_axi_id_KI_run_flag = 0;
reg write_one_axi_id_KI_data_done = 0;
//write axi_id_KP reg
reg [31 : 0] write_axi_id_KP_count = 0;
reg write_axi_id_KP_run_flag = 0;
reg write_one_axi_id_KP_data_done = 0;
//write axi_iq_KI reg
reg [31 : 0] write_axi_iq_KI_count = 0;
reg write_axi_iq_KI_run_flag = 0;
reg write_one_axi_iq_KI_data_done = 0;
//write axi_iq_KP reg
reg [31 : 0] write_axi_iq_KP_count = 0;
reg write_axi_iq_KP_run_flag = 0;
reg write_one_axi_iq_KP_data_done = 0;
//write axi_limit reg
reg [31 : 0] write_axi_limit_count = 0;
reg write_axi_limit_run_flag = 0;
reg write_one_axi_limit_data_done = 0;
//write axi_reset reg
reg [31 : 0] write_axi_reset_count = 0;
reg write_axi_reset_run_flag = 0;
reg write_one_axi_reset_data_done = 0;

//===================process control=================
reg [31 : 0] ongoing_process_number = 0;
//process number depends on how much processes needed.
reg process_busy = 0;

//=================== signal connection ==============
assign TRAN_s_axi_control_AWADDR = AWADDR_reg;
assign TRAN_s_axi_control_AWVALID = AWVALID_reg;
assign TRAN_s_axi_control_WVALID = WVALID_reg;
assign TRAN_s_axi_control_WDATA = WDATA_reg;
assign TRAN_s_axi_control_WSTRB = WSTRB_reg;
assign TRAN_s_axi_control_ARADDR = ARADDR_reg;
assign TRAN_s_axi_control_ARVALID = ARVALID_reg;
assign TRAN_s_axi_control_RREADY = RREADY_reg;
assign TRAN_s_axi_control_BREADY = BREADY_reg;
assign TRAN_control_write_data_finish = 1 & axi_id_reference_write_data_finish & axi_iq_reference_write_data_finish & axi_sampletime_write_data_finish & axi_id_KI_write_data_finish & axi_id_KP_write_data_finish & axi_iq_KI_write_data_finish & axi_iq_KP_write_data_finish & axi_limit_write_data_finish & axi_reset_write_data_finish;
always @(TRAN_control_done_in) 
begin
    AESL_done_index_reg <= TRAN_control_done_in;
end
always @(TRAN_control_ready_in or ready_initial) 
begin
    AESL_ready_reg <= TRAN_control_ready_in | ready_initial;
end

always @(reset or process_0_finish or process_1_finish or process_2_finish or process_3_finish or process_4_finish or process_5_finish or process_6_finish or process_7_finish or process_8_finish ) begin
    if (reset == 0) begin
        ongoing_process_number <= 0;
    end
    else if (ongoing_process_number == 0 && process_0_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 1 && process_1_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 2 && process_2_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 3 && process_3_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 4 && process_4_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 5 && process_5_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 6 && process_6_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 7 && process_7_finish == 1) begin
            ongoing_process_number <= ongoing_process_number + 1;
    end
    else if (ongoing_process_number == 8 && process_8_finish == 1) begin
            ongoing_process_number <= 0;
    end
end

task count_c_data_four_byte_num_by_bitwidth;
input  integer bitwidth;
output integer num;
integer factor;
integer i;
begin
    factor = 32;
    for (i = 1; i <= 1024; i = i + 1) begin
        if (bitwidth <= factor && bitwidth > factor - 32) begin
            num = i;
        end
        factor = factor + 32;
    end
end    
endtask

task count_seperate_factor_by_bitwidth;
input  integer bitwidth;
output integer factor;
begin
    if (bitwidth <= 8) begin
        factor=4;
    end
    if (bitwidth <= 16 & bitwidth > 8 ) begin
        factor=2;
    end
    if (bitwidth <= 32 & bitwidth > 16 ) begin
        factor=1;
    end
    if (bitwidth > 32 ) begin
        factor=1;
    end
end    
endtask

task count_operate_depth_by_bitwidth_and_depth;
input  integer bitwidth;
input  integer depth;
output integer operate_depth;
integer factor;
integer remain;
begin
    count_seperate_factor_by_bitwidth (bitwidth , factor);
    operate_depth = depth / factor;
    remain = depth % factor;
    if (remain > 0) begin
        operate_depth = operate_depth + 1;
    end
end    
endtask

task write; /*{{{*/
    input  reg [ADDR_WIDTH - 1:0] waddr;   // write address
    input  reg [DATA_WIDTH - 1:0] wdata;   // write data
    output reg wresp;
    reg aw_flag;
    reg w_flag;
    reg [DATA_WIDTH/8 - 1:0] wstrb_reg;
    integer i;
begin 
    wresp = 0;
    aw_flag = 0;
    w_flag = 0;
//=======================one single write operate======================
    AWADDR_reg <= waddr;
    AWVALID_reg <= 1;
    WDATA_reg <= wdata;
    WVALID_reg <= 1;
    for (i = 0; i < DATA_WIDTH/8; i = i + 1) begin
        wstrb_reg [i] = 1;
    end    
    WSTRB_reg <= wstrb_reg;
    while (!(aw_flag && w_flag)) begin
        @(posedge clk);
        if (aw_flag != 1)
            aw_flag = TRAN_s_axi_control_AWREADY & AWVALID_reg;
        if (w_flag != 1)
            w_flag = TRAN_s_axi_control_WREADY & WVALID_reg;
        AWVALID_reg <= !aw_flag;
        WVALID_reg <= !w_flag;
    end

    BREADY_reg <= 1;
    while (TRAN_s_axi_control_BVALID != 1) begin
        //wait for response 
        @(posedge clk);
    end
    @(posedge clk);
    BREADY_reg <= 0;
    if (TRAN_s_axi_control_BRESP === 2'b00) begin
        wresp = 1;
        //input success. in fact BRESP is always 2'b00
    end   
//=======================one single write operate======================

end
endtask/*}}}*/

task read (/*{{{*/
    input  [ADDR_WIDTH - 1:0] raddr ,   // write address
    output [DATA_WIDTH - 1:0] RDATA_result ,
    output rresp
);
begin 
    rresp = 0;
//=======================one single read operate======================
    ARADDR_reg <= raddr;
    ARVALID_reg <= 1;
    while (TRAN_s_axi_control_ARREADY !== 1) begin
        @(posedge clk);
    end
    @(posedge clk);
    ARVALID_reg <= 0;
    RREADY_reg <= 1;
    while (TRAN_s_axi_control_RVALID !== 1) begin
        //wait for response 
        @(posedge clk);
    end
    @(posedge clk);
    RDATA_result  <= TRAN_s_axi_control_RDATA;
    RREADY_reg <= 0;
    if (TRAN_s_axi_control_RRESP === 2'b00 ) begin
        rresp <= 1;
        //output success. in fact RRESP is always 2'b00
    end  
    @(posedge clk);

//=======================one single read operate end======================

end
endtask/*}}}*/

initial begin : ready_initial_process
    ready_initial = 0;
    wait(reset === 1);
    @(posedge clk);
    ready_initial = 1;
    @(posedge clk);
    ready_initial = 0;
end

always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_id_reference_write_data_finish <= 0;
        write_axi_id_reference_run_flag <= 0; 
        write_axi_id_reference_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_id_reference_c_bitwidth, axi_id_reference_DEPTH, axi_id_reference_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_id_reference_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_id_reference_run_flag <= 1; 
            write_axi_id_reference_count = 0;
        end
        if (write_one_axi_id_reference_data_done === 1) begin
            write_axi_id_reference_count = write_axi_id_reference_count + 1;
            if (write_axi_id_reference_count == axi_id_reference_OPERATE_DEPTH) begin
                write_axi_id_reference_run_flag <= 0; 
                axi_id_reference_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_id_reference
    integer write_axi_id_reference_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_id_reference_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_id_reference_c_bitwidth;
    process_num = 0;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_0_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_id_reference_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_id_reference data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_id_reference_c_bitwidth < 32) begin
                        axi_id_reference_data_tmp_reg = mem_axi_id_reference[write_axi_id_reference_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_id_reference_c_bitwidth) begin
                                axi_id_reference_data_tmp_reg[j] = mem_axi_id_reference[write_axi_id_reference_count][i*32 + j];
                            end
                            else begin
                                axi_id_reference_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_id_reference[write_axi_id_reference_count * four_byte_num  + i]!==axi_id_reference_data_tmp_reg) begin
                    write (axi_id_reference_data_in_addr + write_axi_id_reference_count * four_byte_num * 4 + i * 4, axi_id_reference_data_tmp_reg, write_axi_id_reference_resp);
                    image_mem_axi_id_reference[write_axi_id_reference_count * four_byte_num + i]=axi_id_reference_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_id_reference_data_done <= 1;
                @(posedge clk);
                write_one_axi_id_reference_data_done <= 0;
            end   
            process_0_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_iq_reference_write_data_finish <= 0;
        write_axi_iq_reference_run_flag <= 0; 
        write_axi_iq_reference_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_iq_reference_c_bitwidth, axi_iq_reference_DEPTH, axi_iq_reference_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_iq_reference_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_iq_reference_run_flag <= 1; 
            write_axi_iq_reference_count = 0;
        end
        if (write_one_axi_iq_reference_data_done === 1) begin
            write_axi_iq_reference_count = write_axi_iq_reference_count + 1;
            if (write_axi_iq_reference_count == axi_iq_reference_OPERATE_DEPTH) begin
                write_axi_iq_reference_run_flag <= 0; 
                axi_iq_reference_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_iq_reference
    integer write_axi_iq_reference_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_iq_reference_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_iq_reference_c_bitwidth;
    process_num = 1;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_1_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_iq_reference_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_iq_reference data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_iq_reference_c_bitwidth < 32) begin
                        axi_iq_reference_data_tmp_reg = mem_axi_iq_reference[write_axi_iq_reference_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_iq_reference_c_bitwidth) begin
                                axi_iq_reference_data_tmp_reg[j] = mem_axi_iq_reference[write_axi_iq_reference_count][i*32 + j];
                            end
                            else begin
                                axi_iq_reference_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_iq_reference[write_axi_iq_reference_count * four_byte_num  + i]!==axi_iq_reference_data_tmp_reg) begin
                    write (axi_iq_reference_data_in_addr + write_axi_iq_reference_count * four_byte_num * 4 + i * 4, axi_iq_reference_data_tmp_reg, write_axi_iq_reference_resp);
                    image_mem_axi_iq_reference[write_axi_iq_reference_count * four_byte_num + i]=axi_iq_reference_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_iq_reference_data_done <= 1;
                @(posedge clk);
                write_one_axi_iq_reference_data_done <= 0;
            end   
            process_1_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_sampletime_write_data_finish <= 0;
        write_axi_sampletime_run_flag <= 0; 
        write_axi_sampletime_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_sampletime_c_bitwidth, axi_sampletime_DEPTH, axi_sampletime_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_sampletime_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_sampletime_run_flag <= 1; 
            write_axi_sampletime_count = 0;
        end
        if (write_one_axi_sampletime_data_done === 1) begin
            write_axi_sampletime_count = write_axi_sampletime_count + 1;
            if (write_axi_sampletime_count == axi_sampletime_OPERATE_DEPTH) begin
                write_axi_sampletime_run_flag <= 0; 
                axi_sampletime_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_sampletime
    integer write_axi_sampletime_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_sampletime_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_sampletime_c_bitwidth;
    process_num = 2;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_2_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_sampletime_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_sampletime data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_sampletime_c_bitwidth < 32) begin
                        axi_sampletime_data_tmp_reg = mem_axi_sampletime[write_axi_sampletime_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_sampletime_c_bitwidth) begin
                                axi_sampletime_data_tmp_reg[j] = mem_axi_sampletime[write_axi_sampletime_count][i*32 + j];
                            end
                            else begin
                                axi_sampletime_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_sampletime[write_axi_sampletime_count * four_byte_num  + i]!==axi_sampletime_data_tmp_reg) begin
                    write (axi_sampletime_data_in_addr + write_axi_sampletime_count * four_byte_num * 4 + i * 4, axi_sampletime_data_tmp_reg, write_axi_sampletime_resp);
                    image_mem_axi_sampletime[write_axi_sampletime_count * four_byte_num + i]=axi_sampletime_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_sampletime_data_done <= 1;
                @(posedge clk);
                write_one_axi_sampletime_data_done <= 0;
            end   
            process_2_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_id_KI_write_data_finish <= 0;
        write_axi_id_KI_run_flag <= 0; 
        write_axi_id_KI_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_id_KI_c_bitwidth, axi_id_KI_DEPTH, axi_id_KI_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_id_KI_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_id_KI_run_flag <= 1; 
            write_axi_id_KI_count = 0;
        end
        if (write_one_axi_id_KI_data_done === 1) begin
            write_axi_id_KI_count = write_axi_id_KI_count + 1;
            if (write_axi_id_KI_count == axi_id_KI_OPERATE_DEPTH) begin
                write_axi_id_KI_run_flag <= 0; 
                axi_id_KI_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_id_KI
    integer write_axi_id_KI_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_id_KI_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_id_KI_c_bitwidth;
    process_num = 3;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_3_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_id_KI_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_id_KI data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_id_KI_c_bitwidth < 32) begin
                        axi_id_KI_data_tmp_reg = mem_axi_id_KI[write_axi_id_KI_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_id_KI_c_bitwidth) begin
                                axi_id_KI_data_tmp_reg[j] = mem_axi_id_KI[write_axi_id_KI_count][i*32 + j];
                            end
                            else begin
                                axi_id_KI_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_id_KI[write_axi_id_KI_count * four_byte_num  + i]!==axi_id_KI_data_tmp_reg) begin
                    write (axi_id_KI_data_in_addr + write_axi_id_KI_count * four_byte_num * 4 + i * 4, axi_id_KI_data_tmp_reg, write_axi_id_KI_resp);
                    image_mem_axi_id_KI[write_axi_id_KI_count * four_byte_num + i]=axi_id_KI_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_id_KI_data_done <= 1;
                @(posedge clk);
                write_one_axi_id_KI_data_done <= 0;
            end   
            process_3_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_id_KP_write_data_finish <= 0;
        write_axi_id_KP_run_flag <= 0; 
        write_axi_id_KP_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_id_KP_c_bitwidth, axi_id_KP_DEPTH, axi_id_KP_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_id_KP_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_id_KP_run_flag <= 1; 
            write_axi_id_KP_count = 0;
        end
        if (write_one_axi_id_KP_data_done === 1) begin
            write_axi_id_KP_count = write_axi_id_KP_count + 1;
            if (write_axi_id_KP_count == axi_id_KP_OPERATE_DEPTH) begin
                write_axi_id_KP_run_flag <= 0; 
                axi_id_KP_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_id_KP
    integer write_axi_id_KP_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_id_KP_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_id_KP_c_bitwidth;
    process_num = 4;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_4_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_id_KP_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_id_KP data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_id_KP_c_bitwidth < 32) begin
                        axi_id_KP_data_tmp_reg = mem_axi_id_KP[write_axi_id_KP_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_id_KP_c_bitwidth) begin
                                axi_id_KP_data_tmp_reg[j] = mem_axi_id_KP[write_axi_id_KP_count][i*32 + j];
                            end
                            else begin
                                axi_id_KP_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_id_KP[write_axi_id_KP_count * four_byte_num  + i]!==axi_id_KP_data_tmp_reg) begin
                    write (axi_id_KP_data_in_addr + write_axi_id_KP_count * four_byte_num * 4 + i * 4, axi_id_KP_data_tmp_reg, write_axi_id_KP_resp);
                    image_mem_axi_id_KP[write_axi_id_KP_count * four_byte_num + i]=axi_id_KP_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_id_KP_data_done <= 1;
                @(posedge clk);
                write_one_axi_id_KP_data_done <= 0;
            end   
            process_4_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_iq_KI_write_data_finish <= 0;
        write_axi_iq_KI_run_flag <= 0; 
        write_axi_iq_KI_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_iq_KI_c_bitwidth, axi_iq_KI_DEPTH, axi_iq_KI_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_iq_KI_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_iq_KI_run_flag <= 1; 
            write_axi_iq_KI_count = 0;
        end
        if (write_one_axi_iq_KI_data_done === 1) begin
            write_axi_iq_KI_count = write_axi_iq_KI_count + 1;
            if (write_axi_iq_KI_count == axi_iq_KI_OPERATE_DEPTH) begin
                write_axi_iq_KI_run_flag <= 0; 
                axi_iq_KI_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_iq_KI
    integer write_axi_iq_KI_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_iq_KI_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_iq_KI_c_bitwidth;
    process_num = 5;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_5_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_iq_KI_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_iq_KI data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_iq_KI_c_bitwidth < 32) begin
                        axi_iq_KI_data_tmp_reg = mem_axi_iq_KI[write_axi_iq_KI_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_iq_KI_c_bitwidth) begin
                                axi_iq_KI_data_tmp_reg[j] = mem_axi_iq_KI[write_axi_iq_KI_count][i*32 + j];
                            end
                            else begin
                                axi_iq_KI_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_iq_KI[write_axi_iq_KI_count * four_byte_num  + i]!==axi_iq_KI_data_tmp_reg) begin
                    write (axi_iq_KI_data_in_addr + write_axi_iq_KI_count * four_byte_num * 4 + i * 4, axi_iq_KI_data_tmp_reg, write_axi_iq_KI_resp);
                    image_mem_axi_iq_KI[write_axi_iq_KI_count * four_byte_num + i]=axi_iq_KI_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_iq_KI_data_done <= 1;
                @(posedge clk);
                write_one_axi_iq_KI_data_done <= 0;
            end   
            process_5_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_iq_KP_write_data_finish <= 0;
        write_axi_iq_KP_run_flag <= 0; 
        write_axi_iq_KP_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_iq_KP_c_bitwidth, axi_iq_KP_DEPTH, axi_iq_KP_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_iq_KP_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_iq_KP_run_flag <= 1; 
            write_axi_iq_KP_count = 0;
        end
        if (write_one_axi_iq_KP_data_done === 1) begin
            write_axi_iq_KP_count = write_axi_iq_KP_count + 1;
            if (write_axi_iq_KP_count == axi_iq_KP_OPERATE_DEPTH) begin
                write_axi_iq_KP_run_flag <= 0; 
                axi_iq_KP_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_iq_KP
    integer write_axi_iq_KP_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_iq_KP_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_iq_KP_c_bitwidth;
    process_num = 6;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_6_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_iq_KP_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_iq_KP data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_iq_KP_c_bitwidth < 32) begin
                        axi_iq_KP_data_tmp_reg = mem_axi_iq_KP[write_axi_iq_KP_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_iq_KP_c_bitwidth) begin
                                axi_iq_KP_data_tmp_reg[j] = mem_axi_iq_KP[write_axi_iq_KP_count][i*32 + j];
                            end
                            else begin
                                axi_iq_KP_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_iq_KP[write_axi_iq_KP_count * four_byte_num  + i]!==axi_iq_KP_data_tmp_reg) begin
                    write (axi_iq_KP_data_in_addr + write_axi_iq_KP_count * four_byte_num * 4 + i * 4, axi_iq_KP_data_tmp_reg, write_axi_iq_KP_resp);
                    image_mem_axi_iq_KP[write_axi_iq_KP_count * four_byte_num + i]=axi_iq_KP_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_iq_KP_data_done <= 1;
                @(posedge clk);
                write_one_axi_iq_KP_data_done <= 0;
            end   
            process_6_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_limit_write_data_finish <= 0;
        write_axi_limit_run_flag <= 0; 
        write_axi_limit_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_limit_c_bitwidth, axi_limit_DEPTH, axi_limit_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_limit_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_limit_run_flag <= 1; 
            write_axi_limit_count = 0;
        end
        if (write_one_axi_limit_data_done === 1) begin
            write_axi_limit_count = write_axi_limit_count + 1;
            if (write_axi_limit_count == axi_limit_OPERATE_DEPTH) begin
                write_axi_limit_run_flag <= 0; 
                axi_limit_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_limit
    integer write_axi_limit_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_limit_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_limit_c_bitwidth;
    process_num = 7;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_7_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_limit_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_limit data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_limit_c_bitwidth < 32) begin
                        axi_limit_data_tmp_reg = mem_axi_limit[write_axi_limit_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_limit_c_bitwidth) begin
                                axi_limit_data_tmp_reg[j] = mem_axi_limit[write_axi_limit_count][i*32 + j];
                            end
                            else begin
                                axi_limit_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_limit[write_axi_limit_count * four_byte_num  + i]!==axi_limit_data_tmp_reg) begin
                    write (axi_limit_data_in_addr + write_axi_limit_count * four_byte_num * 4 + i * 4, axi_limit_data_tmp_reg, write_axi_limit_resp);
                    image_mem_axi_limit[write_axi_limit_count * four_byte_num + i]=axi_limit_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_limit_data_done <= 1;
                @(posedge clk);
                write_one_axi_limit_data_done <= 0;
            end   
            process_7_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        axi_reset_write_data_finish <= 0;
        write_axi_reset_run_flag <= 0; 
        write_axi_reset_count = 0;
        count_operate_depth_by_bitwidth_and_depth (axi_reset_c_bitwidth, axi_reset_DEPTH, axi_reset_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_control_start_in === 1) begin
            axi_reset_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_axi_reset_run_flag <= 1; 
            write_axi_reset_count = 0;
        end
        if (write_one_axi_reset_data_done === 1) begin
            write_axi_reset_count = write_axi_reset_count + 1;
            if (write_axi_reset_count == axi_reset_OPERATE_DEPTH) begin
                write_axi_reset_run_flag <= 0; 
                axi_reset_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_axi_reset
    integer write_axi_reset_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] axi_reset_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = axi_reset_c_bitwidth;
    process_num = 8;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_8_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_axi_reset_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write axi_reset data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (axi_reset_c_bitwidth < 32) begin
                        axi_reset_data_tmp_reg = mem_axi_reset[write_axi_reset_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < axi_reset_c_bitwidth) begin
                                axi_reset_data_tmp_reg[j] = mem_axi_reset[write_axi_reset_count][i*32 + j];
                            end
                            else begin
                                axi_reset_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    if(image_mem_axi_reset[write_axi_reset_count * four_byte_num  + i]!==axi_reset_data_tmp_reg) begin
                    write (axi_reset_data_in_addr + write_axi_reset_count * four_byte_num * 4 + i * 4, axi_reset_data_tmp_reg, write_axi_reset_resp);
                    image_mem_axi_reset[write_axi_reset_count * four_byte_num + i]=axi_reset_data_tmp_reg;
                    end
                end
                process_busy = 0;
                write_one_axi_reset_data_done <= 1;
                @(posedge clk);
                write_one_axi_reset_data_done <= 0;
            end   
            process_8_finish <= 1;
        end
        @(posedge clk);
    end    
end

//------------------------Task and function-------------- 
task read_token; 
    input integer fp; 
    output reg [127 : 0] token;
    integer ret;
    begin
        token = "";
        ret = 0;
        ret = $fscanf(fp,"%s",token);
    end 
endtask 
 
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_id_reference_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_id_reference_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_id_reference_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_id_reference ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_id_reference); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_id_reference_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_id_reference [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_id_reference [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_id_reference [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_id_reference [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_id_reference [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_id_reference;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_iq_reference_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_iq_reference_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_iq_reference_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_iq_reference ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_iq_reference); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_iq_reference_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_iq_reference [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_iq_reference [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_iq_reference [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_iq_reference [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_iq_reference [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_iq_reference;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_sampletime_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_sampletime_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_sampletime_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_sampletime ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_sampletime); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_sampletime_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_sampletime [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_sampletime [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_sampletime [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_sampletime [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_sampletime [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_sampletime;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_id_KI_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_id_KI_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_id_KI_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_id_KI ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_id_KI); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_id_KI_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_id_KI [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_id_KI [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_id_KI [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_id_KI [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_id_KI [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_id_KI;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_id_KP_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_id_KP_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_id_KP_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_id_KP ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_id_KP); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_id_KP_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_id_KP [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_id_KP [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_id_KP [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_id_KP [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_id_KP [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_id_KP;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_iq_KI_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_iq_KI_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_iq_KI_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_iq_KI ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_iq_KI); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_iq_KI_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_iq_KI [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_iq_KI [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_iq_KI [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_iq_KI [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_iq_KI [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_iq_KI;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_iq_KP_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_iq_KP_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_iq_KP_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_iq_KP ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_iq_KP); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_iq_KP_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_iq_KP [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_iq_KP [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_iq_KP [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_iq_KP [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_iq_KP [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_iq_KP;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_limit_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_limit_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_limit_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_limit ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_limit); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_limit_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_limit [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_limit [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_limit [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_limit [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_limit [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_limit;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_axi_reset_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [axi_reset_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] tmp_cache_mem; 
  reg [ 8*5 : 1] str;
    reg [63:0] trans_depth;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (axi_reset_c_bitwidth , factor);
  fp = $fopen(`TV_IN_axi_reset ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_axi_reset); 
      $finish; 
  end 
  read_token(fp, token); 
  if (token != "[[[runtime]]]") begin             // Illegal format 
      $display("ERROR: Simulation using HLS TB failed.");
      $finish; 
  end 
  read_token(fp, token); 
  while (token != "[[[/runtime]]]") begin 
      if (token != "[[transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token);                        // skip transaction number 
      @(posedge clk);
      # 0.2;
      while(AESL_ready_reg !== 1) begin
          @(posedge clk); 
          # 0.2;
      end
      for(i = 0; i < axi_reset_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  tmp_cache_mem [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  tmp_cache_mem [31 : 24] = token_tmp;
                  mem_axi_reset [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  tmp_cache_mem [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  tmp_cache_mem [31 : 16] = token_tmp;
                  mem_axi_reset [i/factor] = tmp_cache_mem;
                  tmp_cache_mem [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_axi_reset [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_axi_reset [i/factor] = tmp_cache_mem;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_axi_reset [i/factor] = tmp_cache_mem;
          end
      end 
      read_token(fp, token); 
      if(token != "[[/transaction]]") begin 
          $display("ERROR: Simulation using HLS TB failed.");
          $finish; 
      end 
      read_token(fp, token); 
      transaction_idx = transaction_idx + 1; 
  end 
  $fclose(fp); 
end 
 
task write_binary_axi_reset;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
endmodule
