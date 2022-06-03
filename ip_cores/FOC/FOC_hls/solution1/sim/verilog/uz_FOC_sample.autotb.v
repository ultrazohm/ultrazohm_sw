// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
 `timescale 1ns/1ps


`define AUTOTB_DUT      uz_FOC_sample
`define AUTOTB_DUT_INST AESL_inst_uz_FOC_sample
`define AUTOTB_TOP      apatb_uz_FOC_sample_top
`define AUTOTB_LAT_RESULT_FILE "uz_FOC_sample.result.lat.rb"
`define AUTOTB_PER_RESULT_TRANS_FILE "uz_FOC_sample.performance.result.transaction.xml"
`define AUTOTB_TOP_INST AESL_inst_apatb_uz_FOC_sample_top
`define AUTOTB_MAX_ALLOW_LATENCY  15000000
`define AUTOTB_CLOCK_PERIOD_DIV2 5.00

`define AESL_DEPTH_Dout 1
`define AESL_DEPTH_self 1
`define AESL_DEPTH_i_reference_Ampere 1
`define AESL_DEPTH_i_actual_Ampere 1
`define AESL_DEPTH_V_dc_volts 1
`define AESL_DEPTH_omega_el_rad_per_sec 1
`define AESL_DEPTH_u_output_Volts 1
`define AUTOTB_TVIN_i_reference_Ampere  "../tv/cdatafile/c.uz_FOC_sample.autotvin_i_reference_Ampere.dat"
`define AUTOTB_TVIN_i_actual_Ampere  "../tv/cdatafile/c.uz_FOC_sample.autotvin_i_actual_Ampere.dat"
`define AUTOTB_TVIN_V_dc_volts  "../tv/cdatafile/c.uz_FOC_sample.autotvin_V_dc_volts.dat"
`define AUTOTB_TVIN_omega_el_rad_per_sec  "../tv/cdatafile/c.uz_FOC_sample.autotvin_omega_el_rad_per_sec.dat"
`define AUTOTB_TVIN_u_output_Volts  "../tv/cdatafile/c.uz_FOC_sample.autotvin_u_output_Volts.dat"
`define AUTOTB_TVIN_i_reference_Ampere_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvin_i_reference_Ampere.dat"
`define AUTOTB_TVIN_i_actual_Ampere_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvin_i_actual_Ampere.dat"
`define AUTOTB_TVIN_V_dc_volts_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvin_V_dc_volts.dat"
`define AUTOTB_TVIN_omega_el_rad_per_sec_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvin_omega_el_rad_per_sec.dat"
`define AUTOTB_TVIN_u_output_Volts_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvin_u_output_Volts.dat"
`define AUTOTB_TVOUT_Dout  "../tv/cdatafile/c.uz_FOC_sample.autotvout_Dout.dat"
`define AUTOTB_TVOUT_self  "../tv/cdatafile/c.uz_FOC_sample.autotvout_self.dat"
`define AUTOTB_TVOUT_Dout_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_Dout.dat"
`define AUTOTB_TVOUT_self_out_wrapc  "../tv/rtldatafile/rtl.uz_FOC_sample.autotvout_self.dat"
module `AUTOTB_TOP;

parameter AUTOTB_TRANSACTION_NUM = 11;
parameter PROGRESS_TIMEOUT = 10000000;
parameter LATENCY_ESTIMATION = 156;
parameter LENGTH_Dout = 150;
parameter LENGTH_self = 3;
parameter LENGTH_i_reference_Ampere = 1;
parameter LENGTH_i_actual_Ampere = 1;
parameter LENGTH_V_dc_volts = 1;
parameter LENGTH_omega_el_rad_per_sec = 1;
parameter LENGTH_u_output_Volts = 1;

task read_token;
    input integer fp;
    output reg [215 : 0] token;
    integer ret;
    begin
        token = "";
        ret = 0;
        ret = $fscanf(fp,"%s",token);
    end
endtask

reg AESL_clock;
reg rst;
reg dut_rst;
reg start;
reg ce;
reg tb_continue;
wire AESL_start;
wire AESL_reset;
wire AESL_ce;
wire AESL_ready;
wire AESL_idle;
wire AESL_continue;
wire AESL_done;
reg AESL_done_delay = 0;
reg AESL_done_delay2 = 0;
reg AESL_ready_delay = 0;
wire ready;
wire ready_wire;
wire [7 : 0] Din_AWADDR;
wire  Din_AWVALID;
wire  Din_AWREADY;
wire  Din_WVALID;
wire  Din_WREADY;
wire [31 : 0] Din_WDATA;
wire [3 : 0] Din_WSTRB;
wire [7 : 0] Din_ARADDR;
wire  Din_ARVALID;
wire  Din_ARREADY;
wire  Din_RVALID;
wire  Din_RREADY;
wire [31 : 0] Din_RDATA;
wire [1 : 0] Din_RRESP;
wire  Din_BVALID;
wire  Din_BREADY;
wire [1 : 0] Din_BRESP;
wire  Din_INTERRUPT;
wire [4 : 0] control_AWADDR;
wire  control_AWVALID;
wire  control_AWREADY;
wire  control_WVALID;
wire  control_WREADY;
wire [31 : 0] control_WDATA;
wire [3 : 0] control_WSTRB;
wire [4 : 0] control_ARADDR;
wire  control_ARVALID;
wire  control_ARREADY;
wire  control_RVALID;
wire  control_RREADY;
wire [31 : 0] control_RDATA;
wire [1 : 0] control_RRESP;
wire  control_BVALID;
wire  control_BREADY;
wire [1 : 0] control_BRESP;
wire  Dout_AWVALID;
wire  Dout_AWREADY;
wire [63 : 0] Dout_AWADDR;
wire [0 : 0] Dout_AWID;
wire [7 : 0] Dout_AWLEN;
wire [2 : 0] Dout_AWSIZE;
wire [1 : 0] Dout_AWBURST;
wire [1 : 0] Dout_AWLOCK;
wire [3 : 0] Dout_AWCACHE;
wire [2 : 0] Dout_AWPROT;
wire [3 : 0] Dout_AWQOS;
wire [3 : 0] Dout_AWREGION;
wire [0 : 0] Dout_AWUSER;
wire  Dout_WVALID;
wire  Dout_WREADY;
wire [31 : 0] Dout_WDATA;
wire [3 : 0] Dout_WSTRB;
wire  Dout_WLAST;
wire [0 : 0] Dout_WID;
wire [0 : 0] Dout_WUSER;
wire  Dout_ARVALID;
wire  Dout_ARREADY;
wire [63 : 0] Dout_ARADDR;
wire [0 : 0] Dout_ARID;
wire [7 : 0] Dout_ARLEN;
wire [2 : 0] Dout_ARSIZE;
wire [1 : 0] Dout_ARBURST;
wire [1 : 0] Dout_ARLOCK;
wire [3 : 0] Dout_ARCACHE;
wire [2 : 0] Dout_ARPROT;
wire [3 : 0] Dout_ARQOS;
wire [3 : 0] Dout_ARREGION;
wire [0 : 0] Dout_ARUSER;
wire  Dout_RVALID;
wire  Dout_RREADY;
wire [31 : 0] Dout_RDATA;
wire  Dout_RLAST;
wire [0 : 0] Dout_RID;
wire [0 : 0] Dout_RUSER;
wire [1 : 0] Dout_RRESP;
wire  Dout_BVALID;
wire  Dout_BREADY;
wire [1 : 0] Dout_BRESP;
wire [0 : 0] Dout_BID;
wire [0 : 0] Dout_BUSER;
wire [95 : 0] i_reference_Ampere;
integer done_cnt = 0;
integer AESL_ready_cnt = 0;
integer ready_cnt = 0;
reg ready_initial;
reg ready_initial_n;
reg ready_last_n;
reg ready_delay_last_n;
reg done_delay_last_n;
reg interface_done = 0;
wire Din_read_data_finish;
wire Din_write_data_finish;
wire control_write_data_finish;
wire AESL_slave_start;
reg AESL_slave_start_lock = 0;
wire AESL_slave_write_start_in;
wire AESL_slave_write_start_finish;
reg AESL_slave_ready;
wire AESL_slave_output_done;
wire AESL_slave_done;
reg ready_rise = 0;
reg start_rise = 0;
reg slave_start_status = 0;
reg slave_done_status = 0;
reg ap_done_lock = 0;

wire ap_clk;
wire ap_rst_n;
wire ap_rst_n_n;

`AUTOTB_DUT `AUTOTB_DUT_INST(
    .s_axi_Din_AWADDR(Din_AWADDR),
    .s_axi_Din_AWVALID(Din_AWVALID),
    .s_axi_Din_AWREADY(Din_AWREADY),
    .s_axi_Din_WVALID(Din_WVALID),
    .s_axi_Din_WREADY(Din_WREADY),
    .s_axi_Din_WDATA(Din_WDATA),
    .s_axi_Din_WSTRB(Din_WSTRB),
    .s_axi_Din_ARADDR(Din_ARADDR),
    .s_axi_Din_ARVALID(Din_ARVALID),
    .s_axi_Din_ARREADY(Din_ARREADY),
    .s_axi_Din_RVALID(Din_RVALID),
    .s_axi_Din_RREADY(Din_RREADY),
    .s_axi_Din_RDATA(Din_RDATA),
    .s_axi_Din_RRESP(Din_RRESP),
    .s_axi_Din_BVALID(Din_BVALID),
    .s_axi_Din_BREADY(Din_BREADY),
    .s_axi_Din_BRESP(Din_BRESP),
    .interrupt(Din_INTERRUPT),
    .s_axi_control_AWADDR(control_AWADDR),
    .s_axi_control_AWVALID(control_AWVALID),
    .s_axi_control_AWREADY(control_AWREADY),
    .s_axi_control_WVALID(control_WVALID),
    .s_axi_control_WREADY(control_WREADY),
    .s_axi_control_WDATA(control_WDATA),
    .s_axi_control_WSTRB(control_WSTRB),
    .s_axi_control_ARADDR(control_ARADDR),
    .s_axi_control_ARVALID(control_ARVALID),
    .s_axi_control_ARREADY(control_ARREADY),
    .s_axi_control_RVALID(control_RVALID),
    .s_axi_control_RREADY(control_RREADY),
    .s_axi_control_RDATA(control_RDATA),
    .s_axi_control_RRESP(control_RRESP),
    .s_axi_control_BVALID(control_BVALID),
    .s_axi_control_BREADY(control_BREADY),
    .s_axi_control_BRESP(control_BRESP),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .m_axi_Dout_AWVALID(Dout_AWVALID),
    .m_axi_Dout_AWREADY(Dout_AWREADY),
    .m_axi_Dout_AWADDR(Dout_AWADDR),
    .m_axi_Dout_AWID(Dout_AWID),
    .m_axi_Dout_AWLEN(Dout_AWLEN),
    .m_axi_Dout_AWSIZE(Dout_AWSIZE),
    .m_axi_Dout_AWBURST(Dout_AWBURST),
    .m_axi_Dout_AWLOCK(Dout_AWLOCK),
    .m_axi_Dout_AWCACHE(Dout_AWCACHE),
    .m_axi_Dout_AWPROT(Dout_AWPROT),
    .m_axi_Dout_AWQOS(Dout_AWQOS),
    .m_axi_Dout_AWREGION(Dout_AWREGION),
    .m_axi_Dout_AWUSER(Dout_AWUSER),
    .m_axi_Dout_WVALID(Dout_WVALID),
    .m_axi_Dout_WREADY(Dout_WREADY),
    .m_axi_Dout_WDATA(Dout_WDATA),
    .m_axi_Dout_WSTRB(Dout_WSTRB),
    .m_axi_Dout_WLAST(Dout_WLAST),
    .m_axi_Dout_WID(Dout_WID),
    .m_axi_Dout_WUSER(Dout_WUSER),
    .m_axi_Dout_ARVALID(Dout_ARVALID),
    .m_axi_Dout_ARREADY(Dout_ARREADY),
    .m_axi_Dout_ARADDR(Dout_ARADDR),
    .m_axi_Dout_ARID(Dout_ARID),
    .m_axi_Dout_ARLEN(Dout_ARLEN),
    .m_axi_Dout_ARSIZE(Dout_ARSIZE),
    .m_axi_Dout_ARBURST(Dout_ARBURST),
    .m_axi_Dout_ARLOCK(Dout_ARLOCK),
    .m_axi_Dout_ARCACHE(Dout_ARCACHE),
    .m_axi_Dout_ARPROT(Dout_ARPROT),
    .m_axi_Dout_ARQOS(Dout_ARQOS),
    .m_axi_Dout_ARREGION(Dout_ARREGION),
    .m_axi_Dout_ARUSER(Dout_ARUSER),
    .m_axi_Dout_RVALID(Dout_RVALID),
    .m_axi_Dout_RREADY(Dout_RREADY),
    .m_axi_Dout_RDATA(Dout_RDATA),
    .m_axi_Dout_RLAST(Dout_RLAST),
    .m_axi_Dout_RID(Dout_RID),
    .m_axi_Dout_RUSER(Dout_RUSER),
    .m_axi_Dout_RRESP(Dout_RRESP),
    .m_axi_Dout_BVALID(Dout_BVALID),
    .m_axi_Dout_BREADY(Dout_BREADY),
    .m_axi_Dout_BRESP(Dout_BRESP),
    .m_axi_Dout_BID(Dout_BID),
    .m_axi_Dout_BUSER(Dout_BUSER),
    .i_reference_Ampere(i_reference_Ampere));

// Assignment for control signal
assign ap_clk = AESL_clock;
assign ap_rst_n = dut_rst;
assign ap_rst_n_n = ~dut_rst;
assign AESL_reset = rst;
assign AESL_start = start;
assign AESL_ce = ce;
assign AESL_continue = tb_continue;
  assign AESL_slave_write_start_in = slave_start_status  & Din_write_data_finish & control_write_data_finish;
  assign AESL_slave_start = AESL_slave_write_start_finish;
  assign AESL_done = slave_done_status  & Din_read_data_finish;

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
    begin
        slave_start_status <= 1;
    end
    else begin
        if (AESL_start == 1 ) begin
            start_rise = 1;
        end
        if (start_rise == 1 && AESL_done == 1 ) begin
            slave_start_status <= 1;
        end
        if (AESL_slave_write_start_in == 1 && AESL_done == 0) begin 
            slave_start_status <= 0;
            start_rise = 0;
        end
    end
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
    begin
        AESL_slave_ready <= 0;
        ready_rise = 0;
    end
    else begin
        if (AESL_ready == 1 ) begin
            ready_rise = 1;
        end
        if (ready_rise == 1 && AESL_done_delay == 1 ) begin
            AESL_slave_ready <= 1;
        end
        if (AESL_slave_ready == 1) begin 
            AESL_slave_ready <= 0;
            ready_rise = 0;
        end
    end
end

always @ (posedge AESL_clock)
begin
    if (AESL_done == 1) begin
        slave_done_status <= 0;
    end
    else if (AESL_slave_output_done == 1 ) begin
        slave_done_status <= 1;
    end
end


// The signal of port i_reference_Ampere
reg [95: 0] AESL_REG_i_reference_Ampere = 0;
assign i_reference_Ampere = AESL_REG_i_reference_Ampere;
initial begin : read_file_process_i_reference_Ampere
    integer fp;
    integer err;
    integer ret;
    integer proc_rand;
    reg [215  : 0] token;
    integer i;
    reg transaction_finish;
    integer transaction_idx;
    transaction_idx = 0;
    wait(AESL_reset === 1);
    fp = $fopen(`AUTOTB_TVIN_i_reference_Ampere,"r");
    if(fp == 0) begin       // Failed to open file
        $display("Failed to open file \"%s\"!", `AUTOTB_TVIN_i_reference_Ampere);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    read_token(fp, token);
    if (token != "[[[runtime]]]") begin
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    read_token(fp, token);
    while (token != "[[[/runtime]]]") begin
        if (token != "[[transaction]]") begin
            $display("ERROR: Simulation using HLS TB failed.");
              $finish;
        end
        read_token(fp, token);  // skip transaction number
          read_token(fp, token);
            # 0.2;
            while(ready_wire !== 1) begin
                @(posedge AESL_clock);
                # 0.2;
            end
        if(token != "[[/transaction]]") begin
            ret = $sscanf(token, "0x%x", AESL_REG_i_reference_Ampere);
              if (ret != 1) begin
                  $display("Failed to parse token!");
                $display("ERROR: Simulation using HLS TB failed.");
                  $finish;
              end
            @(posedge AESL_clock);
              read_token(fp, token);
        end
          read_token(fp, token);
    end
    $fclose(fp);
end






wire    AESL_axi_master_Dout_ready;
wire    AESL_axi_master_Dout_done;
wire [64 - 1:0] u_output_Volts;
AESL_axi_master_Dout AESL_AXI_MASTER_Dout(
    .clk   (AESL_clock),
    .reset (AESL_reset),
    .TRAN_Dout_AWVALID (Dout_AWVALID),
    .TRAN_Dout_AWREADY (Dout_AWREADY),
    .TRAN_Dout_AWADDR (Dout_AWADDR),
    .TRAN_Dout_AWID (Dout_AWID),
    .TRAN_Dout_AWLEN (Dout_AWLEN),
    .TRAN_Dout_AWSIZE (Dout_AWSIZE),
    .TRAN_Dout_AWBURST (Dout_AWBURST),
    .TRAN_Dout_AWLOCK (Dout_AWLOCK),
    .TRAN_Dout_AWCACHE (Dout_AWCACHE),
    .TRAN_Dout_AWPROT (Dout_AWPROT),
    .TRAN_Dout_AWQOS (Dout_AWQOS),
    .TRAN_Dout_AWREGION (Dout_AWREGION),
    .TRAN_Dout_AWUSER (Dout_AWUSER),
    .TRAN_Dout_WVALID (Dout_WVALID),
    .TRAN_Dout_WREADY (Dout_WREADY),
    .TRAN_Dout_WDATA (Dout_WDATA),
    .TRAN_Dout_WSTRB (Dout_WSTRB),
    .TRAN_Dout_WLAST (Dout_WLAST),
    .TRAN_Dout_WID (Dout_WID),
    .TRAN_Dout_WUSER (Dout_WUSER),
    .TRAN_Dout_ARVALID (Dout_ARVALID),
    .TRAN_Dout_ARREADY (Dout_ARREADY),
    .TRAN_Dout_ARADDR (Dout_ARADDR),
    .TRAN_Dout_ARID (Dout_ARID),
    .TRAN_Dout_ARLEN (Dout_ARLEN),
    .TRAN_Dout_ARSIZE (Dout_ARSIZE),
    .TRAN_Dout_ARBURST (Dout_ARBURST),
    .TRAN_Dout_ARLOCK (Dout_ARLOCK),
    .TRAN_Dout_ARCACHE (Dout_ARCACHE),
    .TRAN_Dout_ARPROT (Dout_ARPROT),
    .TRAN_Dout_ARQOS (Dout_ARQOS),
    .TRAN_Dout_ARREGION (Dout_ARREGION),
    .TRAN_Dout_ARUSER (Dout_ARUSER),
    .TRAN_Dout_RVALID (Dout_RVALID),
    .TRAN_Dout_RREADY (Dout_RREADY),
    .TRAN_Dout_RDATA (Dout_RDATA),
    .TRAN_Dout_RLAST (Dout_RLAST),
    .TRAN_Dout_RID (Dout_RID),
    .TRAN_Dout_RUSER (Dout_RUSER),
    .TRAN_Dout_RRESP (Dout_RRESP),
    .TRAN_Dout_BVALID (Dout_BVALID),
    .TRAN_Dout_BREADY (Dout_BREADY),
    .TRAN_Dout_BRESP (Dout_BRESP),
    .TRAN_Dout_BID (Dout_BID),
    .TRAN_Dout_BUSER (Dout_BUSER),
    .TRAN_Dout_u_output_Volts (u_output_Volts),
    .ready (AESL_axi_master_Dout_ready),
    .done  (AESL_axi_master_Dout_done)
);
assign    AESL_axi_master_Dout_ready    =   ready;
assign    AESL_axi_master_Dout_done    =   AESL_done_delay;

AESL_axi_slave_Din AESL_AXI_SLAVE_Din(
    .clk   (AESL_clock),
    .reset (AESL_reset),
    .TRAN_s_axi_Din_AWADDR (Din_AWADDR),
    .TRAN_s_axi_Din_AWVALID (Din_AWVALID),
    .TRAN_s_axi_Din_AWREADY (Din_AWREADY),
    .TRAN_s_axi_Din_WVALID (Din_WVALID),
    .TRAN_s_axi_Din_WREADY (Din_WREADY),
    .TRAN_s_axi_Din_WDATA (Din_WDATA),
    .TRAN_s_axi_Din_WSTRB (Din_WSTRB),
    .TRAN_s_axi_Din_ARADDR (Din_ARADDR),
    .TRAN_s_axi_Din_ARVALID (Din_ARVALID),
    .TRAN_s_axi_Din_ARREADY (Din_ARREADY),
    .TRAN_s_axi_Din_RVALID (Din_RVALID),
    .TRAN_s_axi_Din_RREADY (Din_RREADY),
    .TRAN_s_axi_Din_RDATA (Din_RDATA),
    .TRAN_s_axi_Din_RRESP (Din_RRESP),
    .TRAN_s_axi_Din_BVALID (Din_BVALID),
    .TRAN_s_axi_Din_BREADY (Din_BREADY),
    .TRAN_s_axi_Din_BRESP (Din_BRESP),
    .TRAN_Din_interrupt (Din_INTERRUPT),
    .TRAN_Din_read_data_finish(Din_read_data_finish),
    .TRAN_Din_write_data_finish(Din_write_data_finish),
    .TRAN_Din_ready_out (AESL_ready),
    .TRAN_Din_ready_in (AESL_slave_ready),
    .TRAN_Din_done_out (AESL_slave_output_done),
    .TRAN_Din_idle_out (AESL_idle),
    .TRAN_Din_write_start_in     (AESL_slave_write_start_in),
    .TRAN_Din_write_start_finish (AESL_slave_write_start_finish),
    .TRAN_Din_transaction_done_in (AESL_done_delay),
    .TRAN_Din_start_in  (AESL_slave_start)
);
AESL_axi_slave_control AESL_AXI_SLAVE_control(
    .clk   (AESL_clock),
    .reset (AESL_reset),
    .TRAN_s_axi_control_AWADDR (control_AWADDR),
    .TRAN_s_axi_control_AWVALID (control_AWVALID),
    .TRAN_s_axi_control_AWREADY (control_AWREADY),
    .TRAN_s_axi_control_WVALID (control_WVALID),
    .TRAN_s_axi_control_WREADY (control_WREADY),
    .TRAN_s_axi_control_WDATA (control_WDATA),
    .TRAN_s_axi_control_WSTRB (control_WSTRB),
    .TRAN_s_axi_control_ARADDR (control_ARADDR),
    .TRAN_s_axi_control_ARVALID (control_ARVALID),
    .TRAN_s_axi_control_ARREADY (control_ARREADY),
    .TRAN_s_axi_control_RVALID (control_RVALID),
    .TRAN_s_axi_control_RREADY (control_RREADY),
    .TRAN_s_axi_control_RDATA (control_RDATA),
    .TRAN_s_axi_control_RRESP (control_RRESP),
    .TRAN_s_axi_control_BVALID (control_BVALID),
    .TRAN_s_axi_control_BREADY (control_BREADY),
    .TRAN_s_axi_control_BRESP (control_BRESP),
    .TRAN_u_output_Volts (u_output_Volts),
    .TRAN_control_write_data_finish(control_write_data_finish),
    .TRAN_control_ready_in (AESL_slave_ready),
    .TRAN_control_done_in (AESL_slave_output_done),
    .TRAN_control_idle_in (AESL_idle),
    .TRAN_control_transaction_done_in (AESL_done_delay),
    .TRAN_control_start_in  (AESL_slave_start)
);

initial begin : generate_AESL_ready_cnt_proc
    AESL_ready_cnt = 0;
    wait(AESL_reset === 1);
    while(AESL_ready_cnt != AUTOTB_TRANSACTION_NUM) begin
        while(AESL_ready !== 1) begin
            @(posedge AESL_clock);
            # 0.4;
        end
        @(negedge AESL_clock);
        AESL_ready_cnt = AESL_ready_cnt + 1;
        @(posedge AESL_clock);
        # 0.4;
    end
end

    event next_trigger_ready_cnt;
    
    initial begin : gen_ready_cnt
        ready_cnt = 0;
        wait (AESL_reset === 1);
        forever begin
            @ (posedge AESL_clock);
            if (ready == 1) begin
                if (ready_cnt < AUTOTB_TRANSACTION_NUM) begin
                    ready_cnt = ready_cnt + 1;
                end
            end
            -> next_trigger_ready_cnt;
        end
    end
    
    wire all_finish = (done_cnt == AUTOTB_TRANSACTION_NUM);
    
    // done_cnt
    always @ (posedge AESL_clock) begin
        if (~AESL_reset) begin
            done_cnt <= 0;
        end else begin
            if (AESL_done == 1) begin
                if (done_cnt < AUTOTB_TRANSACTION_NUM) begin
                    done_cnt <= done_cnt + 1;
                end
            end
        end
    end
    
    initial begin : finish_simulation
        wait (all_finish == 1);
        // last transaction is saved at negedge right after last done
        @ (posedge AESL_clock);
        @ (posedge AESL_clock);
        @ (posedge AESL_clock);
        @ (posedge AESL_clock);
        $finish;
    end
    
initial begin
    AESL_clock = 0;
    forever #`AUTOTB_CLOCK_PERIOD_DIV2 AESL_clock = ~AESL_clock;
end


reg end_i_reference_Ampere;
reg [31:0] size_i_reference_Ampere;
reg [31:0] size_i_reference_Ampere_backup;
reg end_i_actual_Ampere;
reg [31:0] size_i_actual_Ampere;
reg [31:0] size_i_actual_Ampere_backup;
reg end_V_dc_volts;
reg [31:0] size_V_dc_volts;
reg [31:0] size_V_dc_volts_backup;
reg end_omega_el_rad_per_sec;
reg [31:0] size_omega_el_rad_per_sec;
reg [31:0] size_omega_el_rad_per_sec_backup;
reg end_u_output_Volts;
reg [31:0] size_u_output_Volts;
reg [31:0] size_u_output_Volts_backup;
reg end_Dout;
reg [31:0] size_Dout;
reg [31:0] size_Dout_backup;
reg end_self;
reg [31:0] size_self;
reg [31:0] size_self_backup;

initial begin : initial_process
    integer proc_rand;
    rst = 0;
    # 100;
    repeat(100+3) @ (posedge AESL_clock);
    rst = 1;
end
initial begin : initial_process_for_dut_rst
    integer proc_rand;
    dut_rst = 0;
    # 100;
    repeat(3) @ (posedge AESL_clock);
    dut_rst = 1;
end
initial begin : start_process
    integer proc_rand;
    reg [31:0] start_cnt;
    ce = 1;
    start = 0;
    start_cnt = 0;
    wait (AESL_reset === 1);
    @ (posedge AESL_clock);
    #0 start = 1;
    start_cnt = start_cnt + 1;
    forever begin
        if (start_cnt >= AUTOTB_TRANSACTION_NUM + 1) begin
            #0 start = 0;
        end
        @ (posedge AESL_clock);
        if (AESL_ready) begin
            start_cnt = start_cnt + 1;
        end
    end
end

always @(AESL_done)
begin
    tb_continue = AESL_done;
end

initial begin : ready_initial_process
    ready_initial = 0;
    wait (AESL_start === 1);
    ready_initial = 1;
    @(posedge AESL_clock);
    ready_initial = 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      AESL_ready_delay = 0;
  else
      AESL_ready_delay = AESL_ready;
end
initial begin : ready_last_n_process
  ready_last_n = 1;
  wait(ready_cnt == AUTOTB_TRANSACTION_NUM)
  @(posedge AESL_clock);
  ready_last_n <= 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      ready_delay_last_n = 0;
  else
      ready_delay_last_n <= ready_last_n;
end
assign ready = (ready_initial | AESL_ready_delay);
assign ready_wire = ready_initial | AESL_ready_delay;
initial begin : done_delay_last_n_process
  done_delay_last_n = 1;
  while(done_cnt < AUTOTB_TRANSACTION_NUM)
      @(posedge AESL_clock);
  # 0.1;
  done_delay_last_n = 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
  begin
      AESL_done_delay <= 0;
      AESL_done_delay2 <= 0;
  end
  else begin
      AESL_done_delay <= AESL_done & done_delay_last_n;
      AESL_done_delay2 <= AESL_done_delay;
  end
end
always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      interface_done = 0;
  else begin
      # 0.01;
      if(ready === 1 && ready_cnt > 0 && ready_cnt < AUTOTB_TRANSACTION_NUM)
          interface_done = 1;
      else if(AESL_done_delay === 1 && done_cnt == AUTOTB_TRANSACTION_NUM)
          interface_done = 1;
      else
          interface_done = 0;
  end
end

reg dump_tvout_finish_Dout;

initial begin : dump_tvout_runtime_sign_Dout
    integer fp;
    dump_tvout_finish_Dout = 0;
    fp = $fopen(`AUTOTB_TVOUT_Dout_out_wrapc, "w");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_Dout_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    $fdisplay(fp,"[[[runtime]]]");
    $fclose(fp);
    wait (done_cnt == AUTOTB_TRANSACTION_NUM);
    // last transaction is saved at negedge right after last done
    @ (posedge AESL_clock);
    @ (posedge AESL_clock);
    @ (posedge AESL_clock);
    fp = $fopen(`AUTOTB_TVOUT_Dout_out_wrapc, "a");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_Dout_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    $fdisplay(fp,"[[[/runtime]]]");
    $fclose(fp);
    dump_tvout_finish_Dout = 1;
end


reg dump_tvout_finish_self;

initial begin : dump_tvout_runtime_sign_self
    integer fp;
    dump_tvout_finish_self = 0;
    fp = $fopen(`AUTOTB_TVOUT_self_out_wrapc, "w");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_self_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    $fdisplay(fp,"[[[runtime]]]");
    $fclose(fp);
    wait (done_cnt == AUTOTB_TRANSACTION_NUM);
    // last transaction is saved at negedge right after last done
    @ (posedge AESL_clock);
    @ (posedge AESL_clock);
    @ (posedge AESL_clock);
    fp = $fopen(`AUTOTB_TVOUT_self_out_wrapc, "a");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_self_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    $fdisplay(fp,"[[[/runtime]]]");
    $fclose(fp);
    dump_tvout_finish_self = 1;
end


////////////////////////////////////////////
// progress and performance
////////////////////////////////////////////

task wait_start();
    while (~AESL_start) begin
        @ (posedge AESL_clock);
    end
endtask

reg [31:0] clk_cnt = 0;
reg AESL_ready_p1;
reg AESL_start_p1;

always @ (posedge AESL_clock) begin
    if (AESL_reset == 0) begin
        clk_cnt <= 32'h0;
        AESL_ready_p1 <= 1'b0;
        AESL_start_p1 <= 1'b0;
    end
    else begin
        clk_cnt <= clk_cnt + 1;
        AESL_ready_p1 <= AESL_ready;
        AESL_start_p1 <= AESL_start;
    end
end

reg [31:0] start_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] start_cnt;
reg [31:0] ready_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] ap_ready_cnt;
reg [31:0] finish_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] finish_cnt;
reg [31:0] lat_total;
event report_progress;

initial begin
    start_cnt = 0;
    finish_cnt = 0;
    ap_ready_cnt = 0;
    wait (AESL_reset == 1);
    wait_start();
    start_timestamp[start_cnt] = clk_cnt;
    start_cnt = start_cnt + 1;
    if (AESL_done) begin
        finish_timestamp[finish_cnt] = clk_cnt;
        finish_cnt = finish_cnt + 1;
    end
    -> report_progress;
    forever begin
        @ (posedge AESL_clock);
        if (start_cnt < AUTOTB_TRANSACTION_NUM) begin
            if ((AESL_start && AESL_ready_p1)||(AESL_start && ~AESL_start_p1)) begin
                start_timestamp[start_cnt] = clk_cnt;
                start_cnt = start_cnt + 1;
            end
        end
        if (ap_ready_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_start_p1 && AESL_ready_p1) begin
                ready_timestamp[ap_ready_cnt] = clk_cnt;
                ap_ready_cnt = ap_ready_cnt + 1;
            end
        end
        if (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_done) begin
                finish_timestamp[finish_cnt] = clk_cnt;
                finish_cnt = finish_cnt + 1;
            end
        end
        -> report_progress;
    end
end

reg [31:0] progress_timeout;

initial begin : simulation_progress
    real intra_progress;
    wait (AESL_reset == 1);
    progress_timeout = PROGRESS_TIMEOUT;
    $display("////////////////////////////////////////////////////////////////////////////////////");
    $display("// Inter-Transaction Progress: Completed Transaction / Total Transaction");
    $display("// Intra-Transaction Progress: Measured Latency / Latency Estimation * 100%%");
    $display("//");
    $display("// RTL Simulation : \"Inter-Transaction Progress\" [\"Intra-Transaction Progress\"] @ \"Simulation Time\"");
    $display("////////////////////////////////////////////////////////////////////////////////////");
    print_progress();
    while (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
        @ (report_progress);
        if (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_done) begin
                print_progress();
                progress_timeout = PROGRESS_TIMEOUT;
            end else begin
                if (progress_timeout == 0) begin
                    print_progress();
                    progress_timeout = PROGRESS_TIMEOUT;
                end else begin
                    progress_timeout = progress_timeout - 1;
                end
            end
        end
    end
    print_progress();
    $display("////////////////////////////////////////////////////////////////////////////////////");
    calculate_performance();
end

task get_intra_progress(output real intra_progress);
    begin
        if (start_cnt > finish_cnt) begin
            intra_progress = clk_cnt - start_timestamp[finish_cnt];
        end else if(finish_cnt > 0) begin
            intra_progress = LATENCY_ESTIMATION;
        end else begin
            intra_progress = 0;
        end
        intra_progress = intra_progress / LATENCY_ESTIMATION;
    end
endtask

task print_progress();
    real intra_progress;
    begin
        if (LATENCY_ESTIMATION > 0) begin
            get_intra_progress(intra_progress);
            $display("// RTL Simulation : %0d / %0d [%2.2f%%] @ \"%0t\"", finish_cnt, AUTOTB_TRANSACTION_NUM, intra_progress * 100, $time);
        end else begin
            $display("// RTL Simulation : %0d / %0d [n/a] @ \"%0t\"", finish_cnt, AUTOTB_TRANSACTION_NUM, $time);
        end
    end
endtask

task calculate_performance();
    integer i;
    integer fp;
    reg [31:0] latency [0:AUTOTB_TRANSACTION_NUM - 1];
    reg [31:0] latency_min;
    reg [31:0] latency_max;
    reg [31:0] latency_total;
    reg [31:0] latency_average;
    reg [31:0] interval [0:AUTOTB_TRANSACTION_NUM - 2];
    reg [31:0] interval_min;
    reg [31:0] interval_max;
    reg [31:0] interval_total;
    reg [31:0] interval_average;
    reg [31:0] total_execute_time;
    begin
        latency_min = -1;
        latency_max = 0;
        latency_total = 0;
        interval_min = -1;
        interval_max = 0;
        interval_total = 0;
        total_execute_time = lat_total;

        for (i = 0; i < AUTOTB_TRANSACTION_NUM; i = i + 1) begin
            // calculate latency
            latency[i] = finish_timestamp[i] - start_timestamp[i];
            if (latency[i] > latency_max) latency_max = latency[i];
            if (latency[i] < latency_min) latency_min = latency[i];
            latency_total = latency_total + latency[i];
            // calculate interval
            if (AUTOTB_TRANSACTION_NUM == 1) begin
                interval[i] = 0;
                interval_max = 0;
                interval_min = 0;
                interval_total = 0;
            end else if (i < AUTOTB_TRANSACTION_NUM - 1) begin
                interval[i] = start_timestamp[i + 1] - start_timestamp[i];
                if (interval[i] > interval_max) interval_max = interval[i];
                if (interval[i] < interval_min) interval_min = interval[i];
                interval_total = interval_total + interval[i];
            end
        end

        latency_average = latency_total / AUTOTB_TRANSACTION_NUM;
        if (AUTOTB_TRANSACTION_NUM == 1) begin
            interval_average = 0;
        end else begin
            interval_average = interval_total / (AUTOTB_TRANSACTION_NUM - 1);
        end

        fp = $fopen(`AUTOTB_LAT_RESULT_FILE, "w");

        $fdisplay(fp, "$MAX_LATENCY = \"%0d\"", latency_max);
        $fdisplay(fp, "$MIN_LATENCY = \"%0d\"", latency_min);
        $fdisplay(fp, "$AVER_LATENCY = \"%0d\"", latency_average);
        $fdisplay(fp, "$MAX_THROUGHPUT = \"%0d\"", interval_max);
        $fdisplay(fp, "$MIN_THROUGHPUT = \"%0d\"", interval_min);
        $fdisplay(fp, "$AVER_THROUGHPUT = \"%0d\"", interval_average);
        $fdisplay(fp, "$TOTAL_EXECUTE_TIME = \"%0d\"", total_execute_time);

        $fclose(fp);

        fp = $fopen(`AUTOTB_PER_RESULT_TRANS_FILE, "w");

        $fdisplay(fp, "%20s%16s%16s", "", "latency", "interval");
        if (AUTOTB_TRANSACTION_NUM == 1) begin
            i = 0;
            $fdisplay(fp, "transaction%8d:%16d%16d", i, latency[i], interval[i]);
        end else begin
            for (i = 0; i < AUTOTB_TRANSACTION_NUM; i = i + 1) begin
                if (i < AUTOTB_TRANSACTION_NUM - 1) begin
                    $fdisplay(fp, "transaction%8d:%16d%16d", i, latency[i], interval[i]);
                end else begin
                    $fdisplay(fp, "transaction%8d:%16d               x", i, latency[i]);
                end
            end
        end

        $fclose(fp);
    end
endtask

always @(posedge AESL_clock)
begin
    if (done_cnt == AUTOTB_TRANSACTION_NUM - 1 && AESL_done == 1'b1)
        lat_total = clk_cnt - start_timestamp[0];
end

////////////////////////////////////////////
// Dependence Check
////////////////////////////////////////////

`ifndef POST_SYN

`endif

endmodule
