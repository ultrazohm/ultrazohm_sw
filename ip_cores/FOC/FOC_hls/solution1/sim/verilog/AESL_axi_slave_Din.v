// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module AESL_axi_slave_Din (
    clk,
    reset,
    TRAN_s_axi_Din_AWADDR,
    TRAN_s_axi_Din_AWVALID,
    TRAN_s_axi_Din_AWREADY,
    TRAN_s_axi_Din_WVALID,
    TRAN_s_axi_Din_WREADY,
    TRAN_s_axi_Din_WDATA,
    TRAN_s_axi_Din_WSTRB,
    TRAN_s_axi_Din_ARADDR,
    TRAN_s_axi_Din_ARVALID,
    TRAN_s_axi_Din_ARREADY,
    TRAN_s_axi_Din_RVALID,
    TRAN_s_axi_Din_RREADY,
    TRAN_s_axi_Din_RDATA,
    TRAN_s_axi_Din_RRESP,
    TRAN_s_axi_Din_BVALID,
    TRAN_s_axi_Din_BREADY,
    TRAN_s_axi_Din_BRESP,
    TRAN_Din_write_data_finish,
    TRAN_Din_read_data_finish,
    TRAN_Din_start_in,
    TRAN_Din_idle_out,
    TRAN_Din_ready_out,
    TRAN_Din_ready_in,
    TRAN_Din_done_out,
    TRAN_Din_write_start_in   ,
    TRAN_Din_write_start_finish,
    TRAN_Din_interrupt,
    TRAN_Din_transaction_done_in
    );

//------------------------Parameter----------------------
`define TV_IN_self "../tv/cdatafile/c.uz_FOC_sample.autotvin_self.dat"
`define TV_OUT_self "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_self.dat"
`define TV_IN_i_actual_Ampere "../tv/cdatafile/c.uz_FOC_sample.autotvin_i_actual_Ampere.dat"
`define TV_IN_V_dc_volts "../tv/cdatafile/c.uz_FOC_sample.autotvin_V_dc_volts.dat"
`define TV_IN_omega_el_rad_per_sec "../tv/cdatafile/c.uz_FOC_sample.autotvin_omega_el_rad_per_sec.dat"
parameter ADDR_WIDTH = 8;
parameter DATA_WIDTH = 32;
parameter self_DEPTH = 3;
reg [31 : 0] self_OPERATE_DEPTH = 0;
parameter self_c_bitwidth = 224;
parameter i_actual_Ampere_DEPTH = 1;
reg [31 : 0] i_actual_Ampere_OPERATE_DEPTH = 0;
parameter i_actual_Ampere_c_bitwidth = 96;
parameter V_dc_volts_DEPTH = 1;
reg [31 : 0] V_dc_volts_OPERATE_DEPTH = 0;
parameter V_dc_volts_c_bitwidth = 32;
parameter omega_el_rad_per_sec_DEPTH = 1;
reg [31 : 0] omega_el_rad_per_sec_OPERATE_DEPTH = 0;
parameter omega_el_rad_per_sec_c_bitwidth = 32;
parameter START_ADDR = 0;
parameter uz_FOC_sample_continue_addr = 0;
parameter uz_FOC_sample_auto_start_addr = 0;
parameter i_actual_Ampere_data_in_addr = 16;
parameter V_dc_volts_data_in_addr = 64;
parameter omega_el_rad_per_sec_data_in_addr = 72;
parameter self_data_in_addr = 128;
parameter self_data_out_addr = 128;
parameter STATUS_ADDR = 0;

output [ADDR_WIDTH - 1 : 0] TRAN_s_axi_Din_AWADDR;
output  TRAN_s_axi_Din_AWVALID;
input  TRAN_s_axi_Din_AWREADY;
output  TRAN_s_axi_Din_WVALID;
input  TRAN_s_axi_Din_WREADY;
output [DATA_WIDTH - 1 : 0] TRAN_s_axi_Din_WDATA;
output [DATA_WIDTH/8 - 1 : 0] TRAN_s_axi_Din_WSTRB;
output [ADDR_WIDTH - 1 : 0] TRAN_s_axi_Din_ARADDR;
output  TRAN_s_axi_Din_ARVALID;
input  TRAN_s_axi_Din_ARREADY;
input  TRAN_s_axi_Din_RVALID;
output  TRAN_s_axi_Din_RREADY;
input [DATA_WIDTH - 1 : 0] TRAN_s_axi_Din_RDATA;
input [2 - 1 : 0] TRAN_s_axi_Din_RRESP;
input  TRAN_s_axi_Din_BVALID;
output  TRAN_s_axi_Din_BREADY;
input [2 - 1 : 0] TRAN_s_axi_Din_BRESP;
output TRAN_Din_write_data_finish;
output TRAN_Din_read_data_finish;
input     clk;
input     reset;
input     TRAN_Din_start_in;
output    TRAN_Din_done_out;
output    TRAN_Din_ready_out;
input     TRAN_Din_ready_in;
output    TRAN_Din_idle_out;
input  TRAN_Din_write_start_in   ;
output TRAN_Din_write_start_finish;
input     TRAN_Din_interrupt;
input     TRAN_Din_transaction_done_in;

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
reg [self_c_bitwidth - 1 : 0] mem_self [self_DEPTH - 1 : 0];
reg self_write_data_finish;
reg self_read_data_finish;
reg [i_actual_Ampere_c_bitwidth - 1 : 0] mem_i_actual_Ampere [i_actual_Ampere_DEPTH - 1 : 0];
reg i_actual_Ampere_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_V_dc_volts [V_dc_volts_DEPTH - 1 : 0];
reg V_dc_volts_write_data_finish;
reg [DATA_WIDTH - 1 : 0] mem_omega_el_rad_per_sec [omega_el_rad_per_sec_DEPTH - 1 : 0];
reg omega_el_rad_per_sec_write_data_finish;
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
//write self reg
reg [31 : 0] write_self_count = 0;
reg write_self_run_flag = 0;
reg write_one_self_data_done = 0;
//write i_actual_Ampere reg
reg [31 : 0] write_i_actual_Ampere_count = 0;
reg write_i_actual_Ampere_run_flag = 0;
reg write_one_i_actual_Ampere_data_done = 0;
//write V_dc_volts reg
reg [31 : 0] write_V_dc_volts_count = 0;
reg write_V_dc_volts_run_flag = 0;
reg write_one_V_dc_volts_data_done = 0;
//write omega_el_rad_per_sec reg
reg [31 : 0] write_omega_el_rad_per_sec_count = 0;
reg write_omega_el_rad_per_sec_run_flag = 0;
reg write_one_omega_el_rad_per_sec_data_done = 0;
//read self reg
reg [31 : 0] read_self_count = 0;
reg read_self_run_flag = 0;
reg read_one_self_data_done = 0;
reg [31 : 0] write_start_count = 0;
reg write_start_run_flag = 0;

//===================process control=================
reg [31 : 0] ongoing_process_number = 0;
//process number depends on how much processes needed.
reg process_busy = 0;

//=================== signal connection ==============
assign TRAN_s_axi_Din_AWADDR = AWADDR_reg;
assign TRAN_s_axi_Din_AWVALID = AWVALID_reg;
assign TRAN_s_axi_Din_WVALID = WVALID_reg;
assign TRAN_s_axi_Din_WDATA = WDATA_reg;
assign TRAN_s_axi_Din_WSTRB = WSTRB_reg;
assign TRAN_s_axi_Din_ARADDR = ARADDR_reg;
assign TRAN_s_axi_Din_ARVALID = ARVALID_reg;
assign TRAN_s_axi_Din_RREADY = RREADY_reg;
assign TRAN_s_axi_Din_BREADY = BREADY_reg;
assign TRAN_Din_write_start_finish = AESL_write_start_finish;
assign TRAN_Din_done_out = AESL_done_index_reg;
assign TRAN_Din_ready_out = AESL_ready_out_index_reg;
assign TRAN_Din_idle_out = AESL_idle_index_reg;
assign TRAN_Din_read_data_finish = 1 & self_read_data_finish;
assign TRAN_Din_write_data_finish = 1 & self_write_data_finish & i_actual_Ampere_write_data_finish & V_dc_volts_write_data_finish & omega_el_rad_per_sec_write_data_finish;
always @(TRAN_Din_ready_in or ready_initial) 
begin
    AESL_ready_reg <= TRAN_Din_ready_in | ready_initial;
end

always @(reset or process_0_finish or process_1_finish or process_2_finish or process_3_finish or process_4_finish or process_5_finish or process_6_finish ) begin
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
    for (i = 1; i <= 32; i = i + 1) begin
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
    if (bitwidth <= 1024 & bitwidth > 32 ) begin
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
            aw_flag = TRAN_s_axi_Din_AWREADY & AWVALID_reg;
        if (w_flag != 1)
            w_flag = TRAN_s_axi_Din_WREADY & WVALID_reg;
        AWVALID_reg <= !aw_flag;
        WVALID_reg <= !w_flag;
    end

    BREADY_reg <= 1;
    while (TRAN_s_axi_Din_BVALID != 1) begin
        //wait for response 
        @(posedge clk);
    end
    @(posedge clk);
    BREADY_reg <= 0;
    if (TRAN_s_axi_Din_BRESP === 2'b00) begin
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
    while (TRAN_s_axi_Din_ARREADY !== 1) begin
        @(posedge clk);
    end
    @(posedge clk);
    ARVALID_reg <= 0;
    RREADY_reg <= 1;
    while (TRAN_s_axi_Din_RVALID !== 1) begin
        //wait for response 
        @(posedge clk);
    end
    @(posedge clk);
    RDATA_result  <= TRAN_s_axi_Din_RDATA;
    RREADY_reg <= 0;
    if (TRAN_s_axi_Din_RRESP === 2'b00 ) begin
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

initial begin : update_status
    integer process_num ;
    integer read_status_resp;
    wait(reset === 1);
    @(posedge clk);
    process_num = 0;
    while (1) begin
        process_0_finish = 0;
        AESL_done_index_reg         <= 0;
        AESL_ready_out_index_reg        <= 0;
        if (ongoing_process_number === process_num && process_busy === 0) begin
            process_busy = 1;
            read (STATUS_ADDR, RDATA_reg, read_status_resp);
                AESL_done_index_reg         <= RDATA_reg[1 : 1];
                AESL_ready_out_index_reg    <= RDATA_reg[1 : 1];
                AESL_idle_index_reg         <= RDATA_reg[2 : 2];
            process_0_finish = 1;
            process_busy = 0;
        end 
        @(posedge clk);
    end
end

always @(reset or posedge clk) begin
    if (reset == 0) begin
        self_write_data_finish <= 0;
        write_self_run_flag <= 0; 
        write_self_count = 0;
        count_operate_depth_by_bitwidth_and_depth (self_c_bitwidth, self_DEPTH, self_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_Din_start_in === 1) begin
            self_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_self_run_flag <= 1; 
            write_self_count = 0;
        end
        if (write_one_self_data_done === 1) begin
            write_self_count = write_self_count + 1;
            if (write_self_count == self_OPERATE_DEPTH) begin
                write_self_run_flag <= 0; 
                self_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_self
    integer write_self_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] self_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = self_c_bitwidth;
    process_num = 1;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_1_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_self_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write self data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (self_c_bitwidth < 32) begin
                        self_data_tmp_reg = mem_self[write_self_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < self_c_bitwidth) begin
                                self_data_tmp_reg[j] = mem_self[write_self_count][i*32 + j];
                            end
                            else begin
                                self_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    write (self_data_in_addr + write_self_count * four_byte_num * 4 + i * 4, self_data_tmp_reg, write_self_resp);
                end
                process_busy = 0;
                write_one_self_data_done <= 1;
                @(posedge clk);
                write_one_self_data_done <= 0;
            end   
            process_1_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        i_actual_Ampere_write_data_finish <= 0;
        write_i_actual_Ampere_run_flag <= 0; 
        write_i_actual_Ampere_count = 0;
        count_operate_depth_by_bitwidth_and_depth (i_actual_Ampere_c_bitwidth, i_actual_Ampere_DEPTH, i_actual_Ampere_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_Din_start_in === 1) begin
            i_actual_Ampere_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_i_actual_Ampere_run_flag <= 1; 
            write_i_actual_Ampere_count = 0;
        end
        if (write_one_i_actual_Ampere_data_done === 1) begin
            write_i_actual_Ampere_count = write_i_actual_Ampere_count + 1;
            if (write_i_actual_Ampere_count == i_actual_Ampere_OPERATE_DEPTH) begin
                write_i_actual_Ampere_run_flag <= 0; 
                i_actual_Ampere_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_i_actual_Ampere
    integer write_i_actual_Ampere_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] i_actual_Ampere_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = i_actual_Ampere_c_bitwidth;
    process_num = 2;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_2_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_i_actual_Ampere_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write i_actual_Ampere data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (i_actual_Ampere_c_bitwidth < 32) begin
                        i_actual_Ampere_data_tmp_reg = mem_i_actual_Ampere[write_i_actual_Ampere_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < i_actual_Ampere_c_bitwidth) begin
                                i_actual_Ampere_data_tmp_reg[j] = mem_i_actual_Ampere[write_i_actual_Ampere_count][i*32 + j];
                            end
                            else begin
                                i_actual_Ampere_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    write (i_actual_Ampere_data_in_addr + write_i_actual_Ampere_count * four_byte_num * 4 + i * 4, i_actual_Ampere_data_tmp_reg, write_i_actual_Ampere_resp);
                end
                process_busy = 0;
                write_one_i_actual_Ampere_data_done <= 1;
                @(posedge clk);
                write_one_i_actual_Ampere_data_done <= 0;
            end   
            process_2_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        V_dc_volts_write_data_finish <= 0;
        write_V_dc_volts_run_flag <= 0; 
        write_V_dc_volts_count = 0;
        count_operate_depth_by_bitwidth_and_depth (V_dc_volts_c_bitwidth, V_dc_volts_DEPTH, V_dc_volts_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_Din_start_in === 1) begin
            V_dc_volts_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_V_dc_volts_run_flag <= 1; 
            write_V_dc_volts_count = 0;
        end
        if (write_one_V_dc_volts_data_done === 1) begin
            write_V_dc_volts_count = write_V_dc_volts_count + 1;
            if (write_V_dc_volts_count == V_dc_volts_OPERATE_DEPTH) begin
                write_V_dc_volts_run_flag <= 0; 
                V_dc_volts_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_V_dc_volts
    integer write_V_dc_volts_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] V_dc_volts_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = V_dc_volts_c_bitwidth;
    process_num = 3;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_3_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_V_dc_volts_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write V_dc_volts data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (V_dc_volts_c_bitwidth < 32) begin
                        V_dc_volts_data_tmp_reg = mem_V_dc_volts[write_V_dc_volts_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < V_dc_volts_c_bitwidth) begin
                                V_dc_volts_data_tmp_reg[j] = mem_V_dc_volts[write_V_dc_volts_count][i*32 + j];
                            end
                            else begin
                                V_dc_volts_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    write (V_dc_volts_data_in_addr + write_V_dc_volts_count * four_byte_num * 4 + i * 4, V_dc_volts_data_tmp_reg, write_V_dc_volts_resp);
                end
                process_busy = 0;
                write_one_V_dc_volts_data_done <= 1;
                @(posedge clk);
                write_one_V_dc_volts_data_done <= 0;
            end   
            process_3_finish <= 1;
        end
        @(posedge clk);
    end    
end
always @(reset or posedge clk) begin
    if (reset == 0) begin
        omega_el_rad_per_sec_write_data_finish <= 0;
        write_omega_el_rad_per_sec_run_flag <= 0; 
        write_omega_el_rad_per_sec_count = 0;
        count_operate_depth_by_bitwidth_and_depth (omega_el_rad_per_sec_c_bitwidth, omega_el_rad_per_sec_DEPTH, omega_el_rad_per_sec_OPERATE_DEPTH);
    end
    else begin
        if (TRAN_Din_start_in === 1) begin
            omega_el_rad_per_sec_write_data_finish <= 0;
        end
        if (AESL_ready_reg === 1) begin
            write_omega_el_rad_per_sec_run_flag <= 1; 
            write_omega_el_rad_per_sec_count = 0;
        end
        if (write_one_omega_el_rad_per_sec_data_done === 1) begin
            write_omega_el_rad_per_sec_count = write_omega_el_rad_per_sec_count + 1;
            if (write_omega_el_rad_per_sec_count == omega_el_rad_per_sec_OPERATE_DEPTH) begin
                write_omega_el_rad_per_sec_run_flag <= 0; 
                omega_el_rad_per_sec_write_data_finish <= 1;
            end
        end
    end
end

initial begin : write_omega_el_rad_per_sec
    integer write_omega_el_rad_per_sec_resp;
    integer process_num ;
    integer get_ack;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;
    reg [31 : 0] omega_el_rad_per_sec_data_tmp_reg;
    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = omega_el_rad_per_sec_c_bitwidth;
    process_num = 4;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_4_finish <= 0;

        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            get_ack = 1;
            if (write_omega_el_rad_per_sec_run_flag === 1 && get_ack === 1) begin
                process_busy = 1;
                //write omega_el_rad_per_sec data 
                for (i = 0 ; i < four_byte_num ; i = i+1) begin
                    if (omega_el_rad_per_sec_c_bitwidth < 32) begin
                        omega_el_rad_per_sec_data_tmp_reg = mem_omega_el_rad_per_sec[write_omega_el_rad_per_sec_count];
                    end
                    else begin
                        for (j=0 ; j<32 ; j = j + 1) begin
                            if (i*32 + j < omega_el_rad_per_sec_c_bitwidth) begin
                                omega_el_rad_per_sec_data_tmp_reg[j] = mem_omega_el_rad_per_sec[write_omega_el_rad_per_sec_count][i*32 + j];
                            end
                            else begin
                                omega_el_rad_per_sec_data_tmp_reg[j] = 0;
                            end
                        end
                    end
                    write (omega_el_rad_per_sec_data_in_addr + write_omega_el_rad_per_sec_count * four_byte_num * 4 + i * 4, omega_el_rad_per_sec_data_tmp_reg, write_omega_el_rad_per_sec_resp);
                end
                process_busy = 0;
                write_one_omega_el_rad_per_sec_data_done <= 1;
                @(posedge clk);
                write_one_omega_el_rad_per_sec_data_done <= 0;
            end   
            process_4_finish <= 1;
        end
        @(posedge clk);
    end    
end

always @(reset or posedge clk) begin
    if (reset == 0) begin
        write_start_run_flag <= 0; 
        write_start_count <= 0;
    end
    else begin
        if (write_start_count >= 11) begin
            write_start_run_flag <= 0; 
        end
        else if (TRAN_Din_write_start_in === 1) begin
            write_start_run_flag <= 1; 
        end
        if (AESL_write_start_finish === 1) begin
            write_start_count <= write_start_count + 1;
            write_start_run_flag <= 0; 
        end
    end
end

initial begin : write_start
    reg [DATA_WIDTH - 1 : 0] write_start_tmp;
    integer process_num;
    integer write_start_resp;
    wait(reset === 1);
    @(posedge clk);
    process_num = 5;
    while (1) begin
        process_5_finish = 0;
        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            if (write_start_run_flag === 1) begin
                process_busy = 1;
                write_start_tmp=0;
                write_start_tmp[0 : 0] = 1;
                write (START_ADDR, write_start_tmp, write_start_resp);
                process_busy = 0;
                AESL_write_start_finish <= 1;
                @(posedge clk);
                AESL_write_start_finish <= 0;
            end
            process_5_finish <= 1;
        end 
        @(posedge clk);
    end
end

always @(reset or posedge clk) begin
    if (reset == 0) begin
        self_read_data_finish <= 0;
        read_self_run_flag <= 0; 
        read_self_count = 0;
    end
    else begin
        if (AESL_done_index_reg === 1) begin
            read_self_run_flag = 1; 
        end
        if (TRAN_Din_transaction_done_in === 1) begin
            self_read_data_finish <= 0;
            read_self_count = 0; 
        end
        if (read_one_self_data_done === 1) begin
            read_self_count = read_self_count + 1;
            if (read_self_count == self_OPERATE_DEPTH) begin
                read_self_run_flag <= 0; 
                self_read_data_finish <= 1;
            end
        end
    end
end

initial begin : read_self
    integer read_self_resp;
    integer process_num;
    integer get_vld;
    integer four_byte_num;
    integer c_bitwidth;
    integer i;
    integer j;

    wait(reset === 1);
    @(posedge clk);
    c_bitwidth = self_c_bitwidth;
    process_num = 6;
    count_c_data_four_byte_num_by_bitwidth (c_bitwidth , four_byte_num) ;
    while (1) begin
        process_6_finish <= 0;
        if (ongoing_process_number === process_num && process_busy === 0 ) begin
            if (read_self_run_flag === 1) begin
                process_busy = 1;
                get_vld = 1;
                if (get_vld == 1) begin
                    //read self data 
                    for (i = 0 ; i < four_byte_num ; i = i+1) begin
                        read (self_data_out_addr + read_self_count * four_byte_num * 4 + i * 4, RDATA_reg, read_self_resp);
                        if (self_c_bitwidth < 32) begin
                            mem_self[read_self_count] <= RDATA_reg;
                        end
                        else begin
                            for (j=0 ; j < 32 ; j = j + 1) begin
                                if (i*32 + j < self_c_bitwidth) begin
                                    mem_self[read_self_count][i*32 + j] <= RDATA_reg[j];
                                end
                            end
                        end
                    end
                    
                    read_one_self_data_done <= 1;
                    @(posedge clk);
                    read_one_self_data_done <= 0;
                end    
                process_busy = 0;
            end    
            process_6_finish <= 1;
        end
        @(posedge clk);
    end    
end
//------------------------Task and function-------------- 
task read_token; 
    input integer fp; 
    output reg [471 : 0] token;
    integer ret;
    begin
        token = "";
        ret = 0;
        ret = $fscanf(fp,"%s",token);
    end 
endtask 
 
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_self_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [471 : 0] token; 
  reg [471 : 0] token_tmp; 
  //reg [self_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] mem_tmp; 
  reg [ 8*5 : 1] str;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (self_c_bitwidth , factor);
  fp = $fopen(`TV_IN_self ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_self); 
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
      for(i = 0; i < self_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  mem_tmp [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  mem_tmp [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  mem_tmp [31 : 24] = token_tmp;
                  mem_self [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  mem_tmp [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [31 : 16] = token_tmp;
                  mem_self [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_self [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_self [i/factor] = mem_tmp;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_self [i/factor] = mem_tmp;
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
 
//------------------------Write file----------------------- 
 
// Write data to file 
 
initial begin : write_self_file_proc 
  integer fp; 
  integer factor; 
  integer transaction_idx; 
  reg [self_c_bitwidth - 1 : 0] mem_tmp; 
  reg [ 100*8 : 1] str;
  integer i; 
  transaction_idx = 0; 
  count_seperate_factor_by_bitwidth (self_c_bitwidth , factor);
  while(1) begin 
      @(posedge clk);
      while (self_read_data_finish !== 1 || TRAN_Din_transaction_done_in === 1) begin
          @(posedge clk);
      end
      # 0.1;
      fp = $fopen(`TV_OUT_self, "a"); 
      if(fp == 0) begin       // Failed to open file 
          $display("Failed to open file \"%s\"!", `TV_OUT_self); 
          $finish; 
      end 
      $fdisplay(fp, "[[transaction]] %d", transaction_idx);
      for (i = 0; i < (self_DEPTH - self_DEPTH % factor); i = i + 1) begin
          if (factor == 4) begin
              if (i%factor == 0) begin
                  mem_tmp = mem_self[i/factor][7:0];
              end
              if (i%factor == 1) begin
                  mem_tmp = mem_self[i/factor][15:8];
              end
              if (i%factor == 2) begin
                  mem_tmp = mem_self[i/factor][23:16];
              end
              if (i%factor == 3) begin
                  mem_tmp = mem_self[i/factor][31:24];
              end
              $fdisplay(fp,"0x%x",mem_tmp);
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  mem_tmp = mem_self[i/factor][15:0];
              end
              if (i%factor == 1) begin
                  mem_tmp = mem_self[i/factor][31:16];
              end
              $fdisplay(fp,"0x%x",mem_tmp);
          end
          if (factor == 1) begin
              $fdisplay(fp,"0x%x",mem_self[i]);
          end
      end 
      if (factor == 4) begin
          if ((self_DEPTH - 1) % factor == 2) begin
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][7:0]);
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][15:8]);
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][23:16]);
          end
          if ((self_DEPTH - 1) % factor == 1) begin
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][7:0]);
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][15:8]);
          end
          if ((self_DEPTH - 1) % factor == 0) begin
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][7:0]);
          end
      end
      if (factor == 2) begin
          if ((self_DEPTH - 1) % factor == 0) begin
              $fdisplay(fp,"0x%x",mem_self[self_DEPTH / factor][15:0]);
          end
      end
      $fdisplay(fp, "[[/transaction]]");
      transaction_idx = transaction_idx + 1;
      $fclose(fp); 
      while (TRAN_Din_start_in !== 1) begin
          @(posedge clk);
      end
  end 
end 
 
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_i_actual_Ampere_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [215 : 0] token; 
  reg [215 : 0] token_tmp; 
  //reg [i_actual_Ampere_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] mem_tmp; 
  reg [ 8*5 : 1] str;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (i_actual_Ampere_c_bitwidth , factor);
  fp = $fopen(`TV_IN_i_actual_Ampere ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_i_actual_Ampere); 
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
      for(i = 0; i < i_actual_Ampere_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  mem_tmp [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  mem_tmp [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  mem_tmp [31 : 24] = token_tmp;
                  mem_i_actual_Ampere [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  mem_tmp [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [31 : 16] = token_tmp;
                  mem_i_actual_Ampere [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_i_actual_Ampere [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_i_actual_Ampere [i/factor] = mem_tmp;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_i_actual_Ampere [i/factor] = mem_tmp;
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
 
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_V_dc_volts_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [V_dc_volts_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] mem_tmp; 
  reg [ 8*5 : 1] str;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (V_dc_volts_c_bitwidth , factor);
  fp = $fopen(`TV_IN_V_dc_volts ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_V_dc_volts); 
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
      for(i = 0; i < V_dc_volts_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  mem_tmp [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  mem_tmp [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  mem_tmp [31 : 24] = token_tmp;
                  mem_V_dc_volts [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  mem_tmp [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [31 : 16] = token_tmp;
                  mem_V_dc_volts [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_V_dc_volts [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_V_dc_volts [i/factor] = mem_tmp;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_V_dc_volts [i/factor] = mem_tmp;
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
 
//------------------------Read file------------------------ 
 
// Read data from file 
initial begin : read_omega_el_rad_per_sec_file_process 
  integer fp; 
  integer ret; 
  integer factor; 
  reg [127 : 0] token; 
  reg [127 : 0] token_tmp; 
  //reg [omega_el_rad_per_sec_c_bitwidth - 1 : 0] token_tmp; 
  reg [DATA_WIDTH - 1 : 0] mem_tmp; 
  reg [ 8*5 : 1] str;
  integer transaction_idx; 
  integer i; 
  transaction_idx = 0; 
  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
  count_seperate_factor_by_bitwidth (omega_el_rad_per_sec_c_bitwidth , factor);
  fp = $fopen(`TV_IN_omega_el_rad_per_sec ,"r"); 
  if(fp == 0) begin                               // Failed to open file 
      $display("Failed to open file \"%s\"!", `TV_IN_omega_el_rad_per_sec); 
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
      for(i = 0; i < omega_el_rad_per_sec_DEPTH; i = i + 1) begin 
          read_token(fp, token); 
          ret = $sscanf(token, "0x%x", token_tmp); 
          if (factor == 4) begin
              if (i%factor == 0) begin
                  mem_tmp [7 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [15 : 8] = token_tmp;
              end
              if (i%factor == 2) begin
                  mem_tmp [23 : 16] = token_tmp;
              end
              if (i%factor == 3) begin
                  mem_tmp [31 : 24] = token_tmp;
                  mem_omega_el_rad_per_sec [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1 : 0] = 0;
              end
          end
          if (factor == 2) begin
              if (i%factor == 0) begin
                  mem_tmp [15 : 0] = token_tmp;
              end
              if (i%factor == 1) begin
                  mem_tmp [31 : 16] = token_tmp;
                  mem_omega_el_rad_per_sec [i/factor] = mem_tmp;
                  mem_tmp [DATA_WIDTH - 1: 0] = 0;
              end
          end
          if (factor == 1) begin
              mem_omega_el_rad_per_sec [i] = token_tmp;
          end
      end 
      if (factor == 4) begin
          if (i%factor != 0) begin
              mem_omega_el_rad_per_sec [i/factor] = mem_tmp;
          end
      end
      if (factor == 2) begin
          if (i%factor != 0) begin
              mem_omega_el_rad_per_sec [i/factor] = mem_tmp;
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
 
endmodule
