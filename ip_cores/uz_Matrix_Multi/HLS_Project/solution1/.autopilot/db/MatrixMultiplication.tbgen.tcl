set moduleName MatrixMultiplication
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_chain
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set C_modelName {MatrixMultiplication}
set C_modelType { void 0 }
set C_modelArgList {
	{ arrays int 32 regular {axi_master 2}  }
	{ A_input int 64 regular {axi_slave 0}  }
	{ B_input int 64 regular {axi_slave 0}  }
	{ C_output int 64 regular {axi_slave 0}  }
	{ A_rows int 64 regular {axi_slave 0}  }
	{ B_rows int 64 regular {axi_slave 0}  }
	{ B_columns int 64 regular {axi_slave 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "arrays", "interface" : "axi_master", "bitwidth" : 32, "direction" : "READWRITE", "bitSlice":[ {"cElement": [{"cName": "A_input","offset": { "type": "dynamic","port_name": "A_input","bundle": "control"},"direction": "READONLY"},{"cName": "B_input","offset": { "type": "dynamic","port_name": "B_input","bundle": "control"},"direction": "READONLY"},{"cName": "C_output","offset": { "type": "dynamic","port_name": "C_output","bundle": "control"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "A_input", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "B_input", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "C_output", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":51}} , 
 	{ "Name" : "A_rows", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":52}, "offset_end" : {"in":63}} , 
 	{ "Name" : "B_rows", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":64}, "offset_end" : {"in":75}} , 
 	{ "Name" : "B_columns", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":76}, "offset_end" : {"in":87}} ]}
# RTL Port declarations: 
set portNum 65
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ m_axi_arrays_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_arrays_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_arrays_AWLEN sc_out sc_lv 8 signal 0 } 
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
	{ m_axi_arrays_ARLEN sc_out sc_lv 8 signal 0 } 
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
	{ m_axi_arrays_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_arrays_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_arrays_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_arrays_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_arrays_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_arrays_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_arrays_BUSER sc_in sc_lv 1 signal 0 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 7 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 7 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"MatrixMultiplication","role":"start","value":"0","valid_bit":"0"},{"name":"MatrixMultiplication","role":"continue","value":"0","valid_bit":"4"},{"name":"MatrixMultiplication","role":"auto_start","value":"0","valid_bit":"7"},{"name":"A_input","role":"data","value":"16"},{"name":"B_input","role":"data","value":"28"},{"name":"C_output","role":"data","value":"40"},{"name":"A_rows","role":"data","value":"52"},{"name":"B_rows","role":"data","value":"64"},{"name":"B_columns","role":"data","value":"76"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[{"name":"MatrixMultiplication","role":"start","value":"0","valid_bit":"0"},{"name":"MatrixMultiplication","role":"done","value":"0","valid_bit":"1"},{"name":"MatrixMultiplication","role":"idle","value":"0","valid_bit":"2"},{"name":"MatrixMultiplication","role":"ready","value":"0","valid_bit":"3"},{"name":"MatrixMultiplication","role":"auto_start","value":"0","valid_bit":"7"}] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "interrupt" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "m_axi_arrays_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWVALID" }} , 
 	{ "name": "m_axi_arrays_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWREADY" }} , 
 	{ "name": "m_axi_arrays_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "arrays", "role": "AWADDR" }} , 
 	{ "name": "m_axi_arrays_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "AWID" }} , 
 	{ "name": "m_axi_arrays_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "arrays", "role": "AWLEN" }} , 
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
 	{ "name": "m_axi_arrays_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "arrays", "role": "ARLEN" }} , 
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
 	{ "name": "m_axi_arrays_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "RUSER" }} , 
 	{ "name": "m_axi_arrays_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "RRESP" }} , 
 	{ "name": "m_axi_arrays_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BVALID" }} , 
 	{ "name": "m_axi_arrays_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BREADY" }} , 
 	{ "name": "m_axi_arrays_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "arrays", "role": "BRESP" }} , 
 	{ "name": "m_axi_arrays_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BID" }} , 
 	{ "name": "m_axi_arrays_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "arrays", "role": "BUSER" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "7", "9", "11", "13", "15", "17", "20", "23", "25", "26", "27", "28"],
		"CDFG" : "MatrixMultiplication",
		"Protocol" : "ap_ctrl_chain",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "arrays", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "arrays_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "arrays_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "arrays_blk_n_B", "Type" : "RtlSignal"}],
				"SubConnect" : [
					{"ID" : "11", "SubInstance" : "grp_MatrixMultiplication_Pipeline_VITIS_LOOP_20_1_fu_236", "Port" : "arrays", "Inst_start_state" : "72", "Inst_end_state" : "73"},
					{"ID" : "13", "SubInstance" : "grp_MatrixMultiplication_Pipeline_VITIS_LOOP_24_2_fu_244", "Port" : "arrays", "Inst_start_state" : "144", "Inst_end_state" : "145"},
					{"ID" : "23", "SubInstance" : "grp_MatrixMultiplication_Pipeline_VITIS_LOOP_41_7_fu_277", "Port" : "arrays", "Inst_start_state" : "154", "Inst_end_state" : "155"}]},
			{"Name" : "A_input", "Type" : "None", "Direction" : "I"},
			{"Name" : "B_input", "Type" : "None", "Direction" : "I"},
			{"Name" : "C_output", "Type" : "None", "Direction" : "I"},
			{"Name" : "A_rows", "Type" : "None", "Direction" : "I"},
			{"Name" : "B_rows", "Type" : "None", "Direction" : "I"},
			{"Name" : "B_columns", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_30_4", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "223", "FirstState" : "ap_ST_fsm_state148", "LastState" : ["ap_ST_fsm_state152"], "QuitState" : ["ap_ST_fsm_state148"], "PreState" : ["ap_ST_fsm_state147"], "PostState" : ["ap_ST_fsm_state146"], "OneDepthLoop" : "0", "OneStateBlock": ""}},
			{"Name" : "VITIS_LOOP_28_3", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "223", "FirstState" : "ap_ST_fsm_state146", "LastState" : ["ap_ST_fsm_state148"], "QuitState" : ["ap_ST_fsm_state146"], "PreState" : ["ap_ST_fsm_state145"], "PostState" : ["ap_ST_fsm_state153"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.A_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.B_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.C_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.acc_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_1_fu_218", "Parent" : "0", "Child" : ["6"],
		"CDFG" : "MatrixMultiplication_Pipeline_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "7", "EstimateLatencyMax" : "7",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "A", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "Loop 1", "PipelineType" : "NotSupport"}]},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_1_fu_218.flow_control_loop_pipe_sequential_init_U", "Parent" : "5"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_2_fu_224", "Parent" : "0", "Child" : ["8"],
		"CDFG" : "MatrixMultiplication_Pipeline_2",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "27", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "B", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "Loop 1", "PipelineType" : "NotSupport"}]},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_2_fu_224.flow_control_loop_pipe_sequential_init_U", "Parent" : "7"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_3_fu_230", "Parent" : "0", "Child" : ["10"],
		"CDFG" : "MatrixMultiplication_Pipeline_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "7", "EstimateLatencyMax" : "7",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "C", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "Loop 1", "PipelineType" : "NotSupport"}]},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_3_fu_230.flow_control_loop_pipe_sequential_init_U", "Parent" : "9"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_20_1_fu_236", "Parent" : "0", "Child" : ["12"],
		"CDFG" : "MatrixMultiplication_Pipeline_VITIS_LOOP_20_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "8", "EstimateLatencyMax" : "8",
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
			{"Name" : "sext_ln20", "Type" : "None", "Direction" : "I"},
			{"Name" : "A", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_20_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_20_1_fu_236.flow_control_loop_pipe_sequential_init_U", "Parent" : "11"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_24_2_fu_244", "Parent" : "0", "Child" : ["14"],
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
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_24_2_fu_244.flow_control_loop_pipe_sequential_init_U", "Parent" : "13"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_6_fu_252", "Parent" : "0", "Child" : ["16"],
		"CDFG" : "MatrixMultiplication_Pipeline_6",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "27", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "acc", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "Loop 1", "PipelineType" : "NotSupport"}]},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_6_fu_252.flow_control_loop_pipe_sequential_init_U", "Parent" : "15"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_31_5_fu_257", "Parent" : "0", "Child" : ["18", "19"],
		"CDFG" : "MatrixMultiplication_Pipeline_VITIS_LOOP_31_5",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "B_rows", "Type" : "None", "Direction" : "I"},
			{"Name" : "mul", "Type" : "None", "Direction" : "I"},
			{"Name" : "A", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "trunc_ln4", "Type" : "None", "Direction" : "I"},
			{"Name" : "trunc_ln5", "Type" : "None", "Direction" : "I"},
			{"Name" : "B", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "acc", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_31_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter4", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter4", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_31_5_fu_257.fmul_32ns_32ns_32_4_max_dsp_1_U11", "Parent" : "17"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_31_5_fu_257.flow_control_loop_pipe_sequential_init_U", "Parent" : "17"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_34_6_fu_268", "Parent" : "0", "Child" : ["21", "22"],
		"CDFG" : "MatrixMultiplication_Pipeline_VITIS_LOOP_34_6",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "2", "EstimateLatencyMax" : "127",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "C_load_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "B_rows", "Type" : "None", "Direction" : "I"},
			{"Name" : "acc", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "add4518_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_34_6", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "4", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage1", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage1_subdone", "QuitState" : "ap_ST_fsm_pp0_stage1", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage1_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_34_6_fu_268.fadd_32ns_32ns_32_5_full_dsp_1_U20", "Parent" : "20"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_34_6_fu_268.flow_control_loop_pipe_sequential_init_U", "Parent" : "20"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_41_7_fu_277", "Parent" : "0", "Child" : ["24"],
		"CDFG" : "MatrixMultiplication_Pipeline_VITIS_LOOP_41_7",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "8", "EstimateLatencyMax" : "8",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "arrays", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "arrays_blk_n_W", "Type" : "RtlSignal"}]},
			{"Name" : "sext_ln41", "Type" : "None", "Direction" : "I"},
			{"Name" : "C", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_41_7", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_MatrixMultiplication_Pipeline_VITIS_LOOP_41_7_fu_277.flow_control_loop_pipe_sequential_init_U", "Parent" : "23"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.arrays_m_axi_U", "Parent" : "0"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_3s_3s_3_1_1_U29", "Parent" : "0"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_3s_3s_3_1_1_U30", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	MatrixMultiplication {
		arrays {Type IO LastRead 149 FirstWrite -1}
		A_input {Type I LastRead 0 FirstWrite -1}
		B_input {Type I LastRead 0 FirstWrite -1}
		C_output {Type I LastRead 0 FirstWrite -1}
		A_rows {Type I LastRead 144 FirstWrite -1}
		B_rows {Type I LastRead 144 FirstWrite -1}
		B_columns {Type I LastRead 144 FirstWrite -1}}
	MatrixMultiplication_Pipeline_1 {
		A {Type O LastRead -1 FirstWrite 0}}
	MatrixMultiplication_Pipeline_2 {
		B {Type O LastRead -1 FirstWrite 0}}
	MatrixMultiplication_Pipeline_3 {
		C {Type O LastRead -1 FirstWrite 0}}
	MatrixMultiplication_Pipeline_VITIS_LOOP_20_1 {
		arrays {Type I LastRead 1 FirstWrite -1}
		sext_ln20 {Type I LastRead 0 FirstWrite -1}
		A {Type O LastRead -1 FirstWrite 2}}
	MatrixMultiplication_Pipeline_VITIS_LOOP_24_2 {
		arrays {Type I LastRead 1 FirstWrite -1}
		sext_ln24 {Type I LastRead 0 FirstWrite -1}
		B {Type O LastRead -1 FirstWrite 2}}
	MatrixMultiplication_Pipeline_6 {
		acc {Type O LastRead -1 FirstWrite 0}}
	MatrixMultiplication_Pipeline_VITIS_LOOP_31_5 {
		B_rows {Type I LastRead 0 FirstWrite -1}
		mul {Type I LastRead 0 FirstWrite -1}
		A {Type I LastRead 0 FirstWrite -1}
		trunc_ln4 {Type I LastRead 0 FirstWrite -1}
		trunc_ln5 {Type I LastRead 0 FirstWrite -1}
		B {Type I LastRead 0 FirstWrite -1}
		acc {Type O LastRead -1 FirstWrite 4}}
	MatrixMultiplication_Pipeline_VITIS_LOOP_34_6 {
		C_load_1 {Type I LastRead 0 FirstWrite -1}
		B_rows {Type I LastRead 0 FirstWrite -1}
		acc {Type I LastRead 0 FirstWrite -1}
		add4518_out {Type O LastRead -1 FirstWrite 1}}
	MatrixMultiplication_Pipeline_VITIS_LOOP_41_7 {
		arrays {Type O LastRead -1 FirstWrite 2}
		sext_ln41 {Type I LastRead 0 FirstWrite -1}
		C {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	arrays { m_axi {  { m_axi_arrays_AWVALID VALID 1 1 }  { m_axi_arrays_AWREADY READY 0 1 }  { m_axi_arrays_AWADDR ADDR 1 64 }  { m_axi_arrays_AWID ID 1 1 }  { m_axi_arrays_AWLEN SIZE 1 8 }  { m_axi_arrays_AWSIZE BURST 1 3 }  { m_axi_arrays_AWBURST LOCK 1 2 }  { m_axi_arrays_AWLOCK CACHE 1 2 }  { m_axi_arrays_AWCACHE PROT 1 4 }  { m_axi_arrays_AWPROT QOS 1 3 }  { m_axi_arrays_AWQOS REGION 1 4 }  { m_axi_arrays_AWREGION USER 1 4 }  { m_axi_arrays_AWUSER DATA 1 1 }  { m_axi_arrays_WVALID VALID 1 1 }  { m_axi_arrays_WREADY READY 0 1 }  { m_axi_arrays_WDATA FIFONUM 1 32 }  { m_axi_arrays_WSTRB STRB 1 4 }  { m_axi_arrays_WLAST LAST 1 1 }  { m_axi_arrays_WID ID 1 1 }  { m_axi_arrays_WUSER DATA 1 1 }  { m_axi_arrays_ARVALID VALID 1 1 }  { m_axi_arrays_ARREADY READY 0 1 }  { m_axi_arrays_ARADDR ADDR 1 64 }  { m_axi_arrays_ARID ID 1 1 }  { m_axi_arrays_ARLEN SIZE 1 8 }  { m_axi_arrays_ARSIZE BURST 1 3 }  { m_axi_arrays_ARBURST LOCK 1 2 }  { m_axi_arrays_ARLOCK CACHE 1 2 }  { m_axi_arrays_ARCACHE PROT 1 4 }  { m_axi_arrays_ARPROT QOS 1 3 }  { m_axi_arrays_ARQOS REGION 1 4 }  { m_axi_arrays_ARREGION USER 1 4 }  { m_axi_arrays_ARUSER DATA 1 1 }  { m_axi_arrays_RVALID VALID 0 1 }  { m_axi_arrays_RREADY READY 1 1 }  { m_axi_arrays_RDATA FIFONUM 0 32 }  { m_axi_arrays_RLAST LAST 0 1 }  { m_axi_arrays_RID ID 0 1 }  { m_axi_arrays_RUSER DATA 0 1 }  { m_axi_arrays_RRESP RESP 0 2 }  { m_axi_arrays_BVALID VALID 0 1 }  { m_axi_arrays_BREADY READY 1 1 }  { m_axi_arrays_BRESP RESP 0 2 }  { m_axi_arrays_BID ID 0 1 }  { m_axi_arrays_BUSER DATA 0 1 } } }
}

set maxi_interface_dict [dict create]
dict set maxi_interface_dict arrays {NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_WRITE}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ arrays 64 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ arrays 64 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
