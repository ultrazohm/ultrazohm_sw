set moduleName MatrixMultiplication_Pipeline_VITIS_LOOP_24_2
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set C_modelName {MatrixMultiplication_Pipeline_VITIS_LOOP_24_2}
set C_modelType { void 0 }
set C_modelArgList {
	{ arrays int 32 regular {axi_master 0}  }
	{ sext_ln24 int 62 regular  }
	{ B float 32 regular {array 25 { 0 3 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "arrays", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "A_input","offset": { "type": "dynamic","port_name": "A_input","bundle": "control"},"direction": "READONLY"},{"cName": "B_input","offset": { "type": "dynamic","port_name": "B_input","bundle": "control"},"direction": "READONLY"},{"cName": "C_output","offset": { "type": "dynamic","port_name": "C_output","bundle": "control"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "sext_ln24", "interface" : "wire", "bitwidth" : 62, "direction" : "READONLY"} , 
 	{ "Name" : "B", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 57
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ m_axi_arrays_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_arrays_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_AWLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_arrays_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_arrays_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_arrays_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_arrays_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_arrays_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_WDATA sc_out sc_lv 32 signal 0 } 
	{ m_axi_arrays_WSTRB sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_arrays_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_ARLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_arrays_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_arrays_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_arrays_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_arrays_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_arrays_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_arrays_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_RDATA sc_in sc_lv 32 signal 0 } 
	{ m_axi_arrays_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_arrays_RFIFONUM sc_in sc_lv 9 signal 0 } 
	{ m_axi_arrays_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_arrays_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_arrays_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_arrays_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_arrays_BUSER sc_in sc_lv 1 signal 0 } 
	{ sext_ln24 sc_in sc_lv 62 signal 1 } 
	{ B_address0 sc_out sc_lv 5 signal 2 } 
	{ B_ce0 sc_out sc_logic 1 signal 2 } 
	{ B_we0 sc_out sc_logic 1 signal 2 } 
	{ B_d0 sc_out sc_lv 32 signal 2 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "m_axi_arrays_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWVALID" }} , 
 	{ "name": "m_axi_arrays_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWREADY" }} , 
 	{ "name": "m_axi_arrays_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "arrays", "role": "AWADDR" }} , 
 	{ "name": "m_axi_arrays_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWID" }} , 
 	{ "name": "m_axi_arrays_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "arrays", "role": "AWLEN" }} , 
 	{ "name": "m_axi_arrays_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "arrays", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_arrays_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "AWBURST" }} , 
 	{ "name": "m_axi_arrays_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_arrays_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_arrays_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "arrays", "role": "AWPROT" }} , 
 	{ "name": "m_axi_arrays_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "AWQOS" }} , 
 	{ "name": "m_axi_arrays_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "AWREGION" }} , 
 	{ "name": "m_axi_arrays_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWUSER" }} , 
 	{ "name": "m_axi_arrays_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "WVALID" }} , 
 	{ "name": "m_axi_arrays_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "WREADY" }} , 
 	{ "name": "m_axi_arrays_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "arrays", "role": "WDATA" }} , 
 	{ "name": "m_axi_arrays_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "WSTRB" }} , 
 	{ "name": "m_axi_arrays_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "WLAST" }} , 
 	{ "name": "m_axi_arrays_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "WID" }} , 
 	{ "name": "m_axi_arrays_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "WUSER" }} , 
 	{ "name": "m_axi_arrays_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "ARVALID" }} , 
 	{ "name": "m_axi_arrays_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "ARREADY" }} , 
 	{ "name": "m_axi_arrays_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "arrays", "role": "ARADDR" }} , 
 	{ "name": "m_axi_arrays_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "ARID" }} , 
 	{ "name": "m_axi_arrays_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "arrays", "role": "ARLEN" }} , 
 	{ "name": "m_axi_arrays_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "arrays", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_arrays_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "ARBURST" }} , 
 	{ "name": "m_axi_arrays_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_arrays_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_arrays_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "arrays", "role": "ARPROT" }} , 
 	{ "name": "m_axi_arrays_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "ARQOS" }} , 
 	{ "name": "m_axi_arrays_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "arrays", "role": "ARREGION" }} , 
 	{ "name": "m_axi_arrays_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "ARUSER" }} , 
 	{ "name": "m_axi_arrays_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RVALID" }} , 
 	{ "name": "m_axi_arrays_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RREADY" }} , 
 	{ "name": "m_axi_arrays_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "arrays", "role": "RDATA" }} , 
 	{ "name": "m_axi_arrays_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RLAST" }} , 
 	{ "name": "m_axi_arrays_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RID" }} , 
 	{ "name": "m_axi_arrays_RFIFONUM", "direction": "in", "datatype": "sc_lv", "bitwidth":9, "type": "signal", "bundle":{"name": "arrays", "role": "RFIFONUM" }} , 
 	{ "name": "m_axi_arrays_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RUSER" }} , 
 	{ "name": "m_axi_arrays_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "RRESP" }} , 
 	{ "name": "m_axi_arrays_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BVALID" }} , 
 	{ "name": "m_axi_arrays_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BREADY" }} , 
 	{ "name": "m_axi_arrays_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "BRESP" }} , 
 	{ "name": "m_axi_arrays_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BID" }} , 
 	{ "name": "m_axi_arrays_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BUSER" }} , 
 	{ "name": "sext_ln24", "direction": "in", "datatype": "sc_lv", "bitwidth":62, "type": "signal", "bundle":{"name": "sext_ln24", "role": "default" }} , 
 	{ "name": "B_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "B", "role": "address0" }} , 
 	{ "name": "B_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "B", "role": "ce0" }} , 
 	{ "name": "B_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "B", "role": "we0" }} , 
 	{ "name": "B_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "B", "role": "d0" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "MatrixMultiplication_Pipeline_VITIS_LOOP_24_2",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "28", "EstimateLatencyMax" : "28",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "arrays", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "arrays_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln24", "Type" : "None", "Direction" : "I"},
			{"Name" : "B", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_24_2", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	MatrixMultiplication_Pipeline_VITIS_LOOP_24_2 {
		arrays {Type I LastRead 1 FirstWrite -1}
		sext_ln24 {Type I LastRead 0 FirstWrite -1}
		B {Type O LastRead -1 FirstWrite 2}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "28", "Max" : "28"}
	, {"Name" : "Interval", "Min" : "28", "Max" : "28"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	 { m_axi {  { m_axi_arrays_AWVALID VALID 1 1 }  { m_axi_arrays_AWREADY READY 0 1 }  { m_axi_arrays_AWADDR ADDR 1 64 }  { m_axi_arrays_AWID ID 1 1 }  { m_axi_arrays_AWLEN SIZE 1 32 }  { m_axi_arrays_AWSIZE BURST 1 3 }  { m_axi_arrays_AWBURST LOCK 1 2 }  { m_axi_arrays_AWLOCK CACHE 1 2 }  { m_axi_arrays_AWCACHE PROT 1 4 }  { m_axi_arrays_AWPROT QOS 1 3 }  { m_axi_arrays_AWQOS REGION 1 4 }  { m_axi_arrays_AWREGION USER 1 4 }  { m_axi_arrays_AWUSER DATA 1 1 }  { m_axi_arrays_WVALID VALID 1 1 }  { m_axi_arrays_WREADY READY 0 1 }  { m_axi_arrays_WDATA FIFONUM 1 32 }  { m_axi_arrays_WSTRB STRB 1 4 }  { m_axi_arrays_WLAST LAST 1 1 }  { m_axi_arrays_WID ID 1 1 }  { m_axi_arrays_WUSER DATA 1 1 }  { m_axi_arrays_ARVALID VALID 1 1 }  { m_axi_arrays_ARREADY READY 0 1 }  { m_axi_arrays_ARADDR ADDR 1 64 }  { m_axi_arrays_ARID ID 1 1 }  { m_axi_arrays_ARLEN SIZE 1 32 }  { m_axi_arrays_ARSIZE BURST 1 3 }  { m_axi_arrays_ARBURST LOCK 1 2 }  { m_axi_arrays_ARLOCK CACHE 1 2 }  { m_axi_arrays_ARCACHE PROT 1 4 }  { m_axi_arrays_ARPROT QOS 1 3 }  { m_axi_arrays_ARQOS REGION 1 4 }  { m_axi_arrays_ARREGION USER 1 4 }  { m_axi_arrays_ARUSER DATA 1 1 }  { m_axi_arrays_RVALID VALID 0 1 }  { m_axi_arrays_RREADY READY 1 1 }  { m_axi_arrays_RDATA FIFONUM 0 32 }  { m_axi_arrays_RLAST LAST 0 1 }  { m_axi_arrays_RID ID 0 1 }  { m_axi_arrays_RFIFONUM LEN 0 9 }  { m_axi_arrays_RUSER DATA 0 1 }  { m_axi_arrays_RRESP RESP 0 2 }  { m_axi_arrays_BVALID VALID 0 1 }  { m_axi_arrays_BREADY READY 1 1 }  { m_axi_arrays_BRESP RESP 0 2 }  { m_axi_arrays_BID ID 0 1 }  { m_axi_arrays_BUSER DATA 0 1 } } }
	sext_ln24 { ap_none {  { sext_ln24 in_data 0 62 } } }
	B { ap_memory {  { B_address0 mem_address 1 5 }  { B_ce0 mem_ce 1 1 }  { B_we0 mem_we 1 1 }  { B_d0 mem_din 1 32 } } }
}
