set moduleName multiply_line15
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type dataflow
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {multiply_line15}
set C_modelType { void 0 }
set C_modelArgList {
	{ val_0 float 32 regular {fifo 0}  }
	{ val_1 float 32 regular {fifo 0}  }
	{ val_2 float 32 regular {fifo 0}  }
	{ val_3 float 32 regular {fifo 0}  }
	{ val_4 float 32 regular {fifo 0}  }
	{ val_5 float 32 regular {fifo 0}  }
	{ val_0_out float 32 regular {fifo 1}  }
	{ val_1_out float 32 regular {fifo 1}  }
	{ val_2_out float 32 regular {fifo 1}  }
	{ val_3_out float 32 regular {fifo 1}  }
	{ val_4_out float 32 regular {fifo 1}  }
	{ val_5_out float 32 regular {fifo 1}  }
	{ products_0_out float 32 regular {fifo 1}  }
	{ products_1_out float 32 regular {fifo 1}  }
	{ products_2_out float 32 regular {fifo 1}  }
	{ products_3_out float 32 regular {fifo 1}  }
	{ products_4_out float 32 regular {fifo 1}  }
	{ products_5_out float 32 regular {fifo 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "val_0", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_1", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_2", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_3", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_4", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_5", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_0_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "val_1_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "val_2_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "val_3_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "val_4_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "val_5_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_0_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_1_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_2_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_3_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_4_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "products_5_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 64
set portList { 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ start_full_n sc_in sc_logic 1 signal -1 } 
	{ start_out sc_out sc_logic 1 signal -1 } 
	{ start_write sc_out sc_logic 1 signal -1 } 
	{ val_0_dout sc_in sc_lv 32 signal 0 } 
	{ val_0_empty_n sc_in sc_logic 1 signal 0 } 
	{ val_0_read sc_out sc_logic 1 signal 0 } 
	{ val_1_dout sc_in sc_lv 32 signal 1 } 
	{ val_1_empty_n sc_in sc_logic 1 signal 1 } 
	{ val_1_read sc_out sc_logic 1 signal 1 } 
	{ val_2_dout sc_in sc_lv 32 signal 2 } 
	{ val_2_empty_n sc_in sc_logic 1 signal 2 } 
	{ val_2_read sc_out sc_logic 1 signal 2 } 
	{ val_3_dout sc_in sc_lv 32 signal 3 } 
	{ val_3_empty_n sc_in sc_logic 1 signal 3 } 
	{ val_3_read sc_out sc_logic 1 signal 3 } 
	{ val_4_dout sc_in sc_lv 32 signal 4 } 
	{ val_4_empty_n sc_in sc_logic 1 signal 4 } 
	{ val_4_read sc_out sc_logic 1 signal 4 } 
	{ val_5_dout sc_in sc_lv 32 signal 5 } 
	{ val_5_empty_n sc_in sc_logic 1 signal 5 } 
	{ val_5_read sc_out sc_logic 1 signal 5 } 
	{ val_0_out_din sc_out sc_lv 32 signal 6 } 
	{ val_0_out_full_n sc_in sc_logic 1 signal 6 } 
	{ val_0_out_write sc_out sc_logic 1 signal 6 } 
	{ val_1_out_din sc_out sc_lv 32 signal 7 } 
	{ val_1_out_full_n sc_in sc_logic 1 signal 7 } 
	{ val_1_out_write sc_out sc_logic 1 signal 7 } 
	{ val_2_out_din sc_out sc_lv 32 signal 8 } 
	{ val_2_out_full_n sc_in sc_logic 1 signal 8 } 
	{ val_2_out_write sc_out sc_logic 1 signal 8 } 
	{ val_3_out_din sc_out sc_lv 32 signal 9 } 
	{ val_3_out_full_n sc_in sc_logic 1 signal 9 } 
	{ val_3_out_write sc_out sc_logic 1 signal 9 } 
	{ val_4_out_din sc_out sc_lv 32 signal 10 } 
	{ val_4_out_full_n sc_in sc_logic 1 signal 10 } 
	{ val_4_out_write sc_out sc_logic 1 signal 10 } 
	{ val_5_out_din sc_out sc_lv 32 signal 11 } 
	{ val_5_out_full_n sc_in sc_logic 1 signal 11 } 
	{ val_5_out_write sc_out sc_logic 1 signal 11 } 
	{ products_0_out_din sc_out sc_lv 32 signal 12 } 
	{ products_0_out_full_n sc_in sc_logic 1 signal 12 } 
	{ products_0_out_write sc_out sc_logic 1 signal 12 } 
	{ products_1_out_din sc_out sc_lv 32 signal 13 } 
	{ products_1_out_full_n sc_in sc_logic 1 signal 13 } 
	{ products_1_out_write sc_out sc_logic 1 signal 13 } 
	{ products_2_out_din sc_out sc_lv 32 signal 14 } 
	{ products_2_out_full_n sc_in sc_logic 1 signal 14 } 
	{ products_2_out_write sc_out sc_logic 1 signal 14 } 
	{ products_3_out_din sc_out sc_lv 32 signal 15 } 
	{ products_3_out_full_n sc_in sc_logic 1 signal 15 } 
	{ products_3_out_write sc_out sc_logic 1 signal 15 } 
	{ products_4_out_din sc_out sc_lv 32 signal 16 } 
	{ products_4_out_full_n sc_in sc_logic 1 signal 16 } 
	{ products_4_out_write sc_out sc_logic 1 signal 16 } 
	{ products_5_out_din sc_out sc_lv 32 signal 17 } 
	{ products_5_out_full_n sc_in sc_logic 1 signal 17 } 
	{ products_5_out_write sc_out sc_logic 1 signal 17 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
}
set NewPortList {[ 
	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "start_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_full_n", "role": "default" }} , 
 	{ "name": "start_out", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out", "role": "default" }} , 
 	{ "name": "start_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_write", "role": "default" }} , 
 	{ "name": "val_0_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_0", "role": "dout" }} , 
 	{ "name": "val_0_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0", "role": "empty_n" }} , 
 	{ "name": "val_0_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0", "role": "read" }} , 
 	{ "name": "val_1_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_1", "role": "dout" }} , 
 	{ "name": "val_1_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1", "role": "empty_n" }} , 
 	{ "name": "val_1_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1", "role": "read" }} , 
 	{ "name": "val_2_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_2", "role": "dout" }} , 
 	{ "name": "val_2_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2", "role": "empty_n" }} , 
 	{ "name": "val_2_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2", "role": "read" }} , 
 	{ "name": "val_3_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_3", "role": "dout" }} , 
 	{ "name": "val_3_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3", "role": "empty_n" }} , 
 	{ "name": "val_3_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3", "role": "read" }} , 
 	{ "name": "val_4_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_4", "role": "dout" }} , 
 	{ "name": "val_4_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4", "role": "empty_n" }} , 
 	{ "name": "val_4_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4", "role": "read" }} , 
 	{ "name": "val_5_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_5", "role": "dout" }} , 
 	{ "name": "val_5_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5", "role": "empty_n" }} , 
 	{ "name": "val_5_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5", "role": "read" }} , 
 	{ "name": "val_0_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_0_out", "role": "din" }} , 
 	{ "name": "val_0_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0_out", "role": "full_n" }} , 
 	{ "name": "val_0_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0_out", "role": "write" }} , 
 	{ "name": "val_1_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_1_out", "role": "din" }} , 
 	{ "name": "val_1_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1_out", "role": "full_n" }} , 
 	{ "name": "val_1_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1_out", "role": "write" }} , 
 	{ "name": "val_2_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_2_out", "role": "din" }} , 
 	{ "name": "val_2_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2_out", "role": "full_n" }} , 
 	{ "name": "val_2_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2_out", "role": "write" }} , 
 	{ "name": "val_3_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_3_out", "role": "din" }} , 
 	{ "name": "val_3_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3_out", "role": "full_n" }} , 
 	{ "name": "val_3_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3_out", "role": "write" }} , 
 	{ "name": "val_4_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_4_out", "role": "din" }} , 
 	{ "name": "val_4_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4_out", "role": "full_n" }} , 
 	{ "name": "val_4_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4_out", "role": "write" }} , 
 	{ "name": "val_5_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_5_out", "role": "din" }} , 
 	{ "name": "val_5_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5_out", "role": "full_n" }} , 
 	{ "name": "val_5_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5_out", "role": "write" }} , 
 	{ "name": "products_0_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_0_out", "role": "din" }} , 
 	{ "name": "products_0_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_0_out", "role": "full_n" }} , 
 	{ "name": "products_0_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_0_out", "role": "write" }} , 
 	{ "name": "products_1_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_1_out", "role": "din" }} , 
 	{ "name": "products_1_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_1_out", "role": "full_n" }} , 
 	{ "name": "products_1_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_1_out", "role": "write" }} , 
 	{ "name": "products_2_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_2_out", "role": "din" }} , 
 	{ "name": "products_2_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_2_out", "role": "full_n" }} , 
 	{ "name": "products_2_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_2_out", "role": "write" }} , 
 	{ "name": "products_3_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_3_out", "role": "din" }} , 
 	{ "name": "products_3_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_3_out", "role": "full_n" }} , 
 	{ "name": "products_3_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_3_out", "role": "write" }} , 
 	{ "name": "products_4_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_4_out", "role": "din" }} , 
 	{ "name": "products_4_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_4_out", "role": "full_n" }} , 
 	{ "name": "products_4_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_4_out", "role": "write" }} , 
 	{ "name": "products_5_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "products_5_out", "role": "din" }} , 
 	{ "name": "products_5_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_5_out", "role": "full_n" }} , 
 	{ "name": "products_5_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "products_5_out", "role": "write" }} , 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"],
		"CDFG" : "multiply_line15",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "5", "EstimateLatencyMax" : "5",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"InputProcess" : [
			{"ID" : "1", "Name" : "multiply_line15_entry185_U0"}],
		"OutputProcess" : [
			{"ID" : "8", "Name" : "p_prop_ret_products_OC_0_dc_proc119_U0"},
			{"ID" : "9", "Name" : "p_prop_ret_products_OC_1_dc_proc120_U0"},
			{"ID" : "10", "Name" : "p_prop_ret_products_OC_2_dc_proc121_U0"},
			{"ID" : "11", "Name" : "p_prop_ret_products_OC_3_dc_proc122_U0"},
			{"ID" : "12", "Name" : "p_prop_ret_products_OC_4_dc_proc123_U0"},
			{"ID" : "13", "Name" : "p_prop_ret_products_OC_5_dc_proc124_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "8", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc119_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "9", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc120_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "10", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc121_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "11", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc122_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "12", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc123_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "13", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc124_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line15_entry185_U0", "Parent" : "0",
		"CDFG" : "multiply_line15_entry185",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "14", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "15", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "16", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "17", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "18", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "19", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0", "Parent" : "0", "Child" : ["3", "4", "5", "6", "7"],
		"CDFG" : "multiply_line15_Block_split1_proc184",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "3", "EstimateLatencyMax" : "3",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"StartSource" : "1",
		"StartFifo" : "start_for_multiply_line15_Block_split1_proc184_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "19", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "18", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "17", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "16", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "15", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "14", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U376", "Parent" : "2"},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U377", "Parent" : "2"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U378", "Parent" : "2"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U379", "Parent" : "2"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U380", "Parent" : "2"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_0_dc_proc119_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc119",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "20", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_1_dc_proc120_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc120",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "21", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_2_dc_proc121_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc121",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "22", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_3_dc_proc122_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc122",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "23", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_4_dc_proc123_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc123",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "24", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_prop_ret_products_OC_5_dc_proc124_U0", "Parent" : "0",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc124",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "25", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_5_c_U", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_4_c_U", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_3_c_U", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_2_c_U", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_1_c_U", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.scalar_val_0_c_U", "Parent" : "0"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_dc_channel_U", "Parent" : "0"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_dc_channel_U", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_dc_channel_U", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_dc_channel_U", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_dc_channel_U", "Parent" : "0"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_dc_channel_U", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line15_Block_split1_proc184_U0_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	multiply_line15 {
		val_0 {Type I LastRead 0 FirstWrite -1}
		val_1 {Type I LastRead 0 FirstWrite -1}
		val_2 {Type I LastRead 0 FirstWrite -1}
		val_3 {Type I LastRead 0 FirstWrite -1}
		val_4 {Type I LastRead 0 FirstWrite -1}
		val_5 {Type I LastRead 0 FirstWrite -1}
		val_0_out {Type O LastRead -1 FirstWrite 0}
		val_1_out {Type O LastRead -1 FirstWrite 0}
		val_2_out {Type O LastRead -1 FirstWrite 0}
		val_3_out {Type O LastRead -1 FirstWrite 0}
		val_4_out {Type O LastRead -1 FirstWrite 0}
		val_5_out {Type O LastRead -1 FirstWrite 0}
		products_0_out {Type O LastRead -1 FirstWrite 0}
		products_1_out {Type O LastRead -1 FirstWrite 0}
		products_2_out {Type O LastRead -1 FirstWrite 0}
		products_3_out {Type O LastRead -1 FirstWrite 0}
		products_4_out {Type O LastRead -1 FirstWrite 0}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	multiply_line15_entry185 {
		scalar_val_5 {Type I LastRead 0 FirstWrite -1}
		scalar_val_4 {Type I LastRead 0 FirstWrite -1}
		scalar_val_3 {Type I LastRead 0 FirstWrite -1}
		scalar_val_2 {Type I LastRead 0 FirstWrite -1}
		scalar_val_1 {Type I LastRead 0 FirstWrite -1}
		scalar_val_0 {Type I LastRead 0 FirstWrite -1}
		scalar_val_5_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_4_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_3_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_2_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_1_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_0_out {Type O LastRead -1 FirstWrite 0}}
	multiply_line15_Block_split1_proc184 {
		scalar_val_0 {Type I LastRead 0 FirstWrite -1}
		val_0_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_1 {Type I LastRead 0 FirstWrite -1}
		val_1_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_2 {Type I LastRead 0 FirstWrite -1}
		val_2_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_3 {Type I LastRead 0 FirstWrite -1}
		val_3_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_4 {Type I LastRead 0 FirstWrite -1}
		val_4_out {Type O LastRead -1 FirstWrite 0}
		scalar_val_5 {Type I LastRead 0 FirstWrite -1}
		val_5_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_0_dc_proc119 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc120 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc121 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc122 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc123 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc124 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "5", "Max" : "5"}
	, {"Name" : "Interval", "Min" : "4", "Max" : "4"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	val_0 { ap_fifo {  { val_0_dout fifo_data 0 32 }  { val_0_empty_n fifo_status 0 1 }  { val_0_read fifo_update 1 1 } } }
	val_1 { ap_fifo {  { val_1_dout fifo_data 0 32 }  { val_1_empty_n fifo_status 0 1 }  { val_1_read fifo_update 1 1 } } }
	val_2 { ap_fifo {  { val_2_dout fifo_data 0 32 }  { val_2_empty_n fifo_status 0 1 }  { val_2_read fifo_update 1 1 } } }
	val_3 { ap_fifo {  { val_3_dout fifo_data 0 32 }  { val_3_empty_n fifo_status 0 1 }  { val_3_read fifo_update 1 1 } } }
	val_4 { ap_fifo {  { val_4_dout fifo_data 0 32 }  { val_4_empty_n fifo_status 0 1 }  { val_4_read fifo_update 1 1 } } }
	val_5 { ap_fifo {  { val_5_dout fifo_data 0 32 }  { val_5_empty_n fifo_status 0 1 }  { val_5_read fifo_update 1 1 } } }
	val_0_out { ap_fifo {  { val_0_out_din fifo_data 1 32 }  { val_0_out_full_n fifo_status 0 1 }  { val_0_out_write fifo_update 1 1 } } }
	val_1_out { ap_fifo {  { val_1_out_din fifo_data 1 32 }  { val_1_out_full_n fifo_status 0 1 }  { val_1_out_write fifo_update 1 1 } } }
	val_2_out { ap_fifo {  { val_2_out_din fifo_data 1 32 }  { val_2_out_full_n fifo_status 0 1 }  { val_2_out_write fifo_update 1 1 } } }
	val_3_out { ap_fifo {  { val_3_out_din fifo_data 1 32 }  { val_3_out_full_n fifo_status 0 1 }  { val_3_out_write fifo_update 1 1 } } }
	val_4_out { ap_fifo {  { val_4_out_din fifo_data 1 32 }  { val_4_out_full_n fifo_status 0 1 }  { val_4_out_write fifo_update 1 1 } } }
	val_5_out { ap_fifo {  { val_5_out_din fifo_data 1 32 }  { val_5_out_full_n fifo_status 0 1 }  { val_5_out_write fifo_update 1 1 } } }
	products_0_out { ap_fifo {  { products_0_out_din fifo_data 1 32 }  { products_0_out_full_n fifo_status 0 1 }  { products_0_out_write fifo_update 1 1 } } }
	products_1_out { ap_fifo {  { products_1_out_din fifo_data 1 32 }  { products_1_out_full_n fifo_status 0 1 }  { products_1_out_write fifo_update 1 1 } } }
	products_2_out { ap_fifo {  { products_2_out_din fifo_data 1 32 }  { products_2_out_full_n fifo_status 0 1 }  { products_2_out_write fifo_update 1 1 } } }
	products_3_out { ap_fifo {  { products_3_out_din fifo_data 1 32 }  { products_3_out_full_n fifo_status 0 1 }  { products_3_out_write fifo_update 1 1 } } }
	products_4_out { ap_fifo {  { products_4_out_din fifo_data 1 32 }  { products_4_out_full_n fifo_status 0 1 }  { products_4_out_write fifo_update 1 1 } } }
	products_5_out { ap_fifo {  { products_5_out_din fifo_data 1 32 }  { products_5_out_full_n fifo_status 0 1 }  { products_5_out_write fifo_update 1 1 } } }
}
