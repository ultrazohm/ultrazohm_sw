set moduleName uz_VSD_6ph_asym
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type dataflow
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {uz_VSD_6ph_asym}
set C_modelType { void 0 }
set C_modelArgList {
	{ in_r int 32 regular {array 6 { 1 1 } 1 1 }  }
	{ out_1 int 32 regular {pointer 1}  }
	{ out_2 int 32 regular {pointer 1}  }
	{ out_3 int 32 regular {pointer 1}  }
	{ out_4 int 32 regular {pointer 1}  }
	{ out_5 int 32 regular {pointer 1}  }
	{ out_6 int 32 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "in_r", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "in","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 5,"step" : 1}]}]}]} , 
 	{ "Name" : "out_1", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_1","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "out_2", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_2","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "out_3", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_3","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "out_4", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_4","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "out_5", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_5","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "out_6", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "out_6","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 28
set portList { 
	{ in_r_address0 sc_out sc_lv 3 signal 0 } 
	{ in_r_ce0 sc_out sc_logic 1 signal 0 } 
	{ in_r_d0 sc_out sc_lv 32 signal 0 } 
	{ in_r_q0 sc_in sc_lv 32 signal 0 } 
	{ in_r_we0 sc_out sc_logic 1 signal 0 } 
	{ in_r_address1 sc_out sc_lv 3 signal 0 } 
	{ in_r_ce1 sc_out sc_logic 1 signal 0 } 
	{ in_r_d1 sc_out sc_lv 32 signal 0 } 
	{ in_r_q1 sc_in sc_lv 32 signal 0 } 
	{ in_r_we1 sc_out sc_logic 1 signal 0 } 
	{ out_1 sc_out sc_lv 32 signal 1 } 
	{ out_2 sc_out sc_lv 32 signal 2 } 
	{ out_3 sc_out sc_lv 32 signal 3 } 
	{ out_4 sc_out sc_lv 32 signal 4 } 
	{ out_5 sc_out sc_lv 32 signal 5 } 
	{ out_6 sc_out sc_lv 32 signal 6 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ out_1_ap_vld sc_out sc_logic 1 outvld 1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ out_2_ap_vld sc_out sc_logic 1 outvld 2 } 
	{ out_3_ap_vld sc_out sc_logic 1 outvld 3 } 
	{ out_4_ap_vld sc_out sc_logic 1 outvld 4 } 
	{ out_5_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ out_6_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
}
set NewPortList {[ 
	{ "name": "in_r_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "in_r", "role": "address0" }} , 
 	{ "name": "in_r_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "ce0" }} , 
 	{ "name": "in_r_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "d0" }} , 
 	{ "name": "in_r_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "q0" }} , 
 	{ "name": "in_r_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "we0" }} , 
 	{ "name": "in_r_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "in_r", "role": "address1" }} , 
 	{ "name": "in_r_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "ce1" }} , 
 	{ "name": "in_r_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "d1" }} , 
 	{ "name": "in_r_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "q1" }} , 
 	{ "name": "in_r_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "we1" }} , 
 	{ "name": "out_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_1", "role": "default" }} , 
 	{ "name": "out_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_2", "role": "default" }} , 
 	{ "name": "out_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_3", "role": "default" }} , 
 	{ "name": "out_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_4", "role": "default" }} , 
 	{ "name": "out_5", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_5", "role": "default" }} , 
 	{ "name": "out_6", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_6", "role": "default" }} , 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_1", "role": "ap_vld" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_2", "role": "ap_vld" }} , 
 	{ "name": "out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_3", "role": "ap_vld" }} , 
 	{ "name": "out_4_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_4", "role": "ap_vld" }} , 
 	{ "name": "out_5_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_5", "role": "ap_vld" }} , 
 	{ "name": "out_6_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "out_6", "role": "ap_vld" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "27", "28", "30", "32", "34", "36", "38", "65", "66", "68", "70", "72", "74", "76", "103", "104", "106", "108", "110", "112", "114", "141", "142", "144", "146", "148", "150", "152", "179", "180", "182", "184", "186", "188", "190", "207", "208", "210", "212", "214", "216", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255", "256", "257", "258", "259", "260", "261", "262", "263", "264", "265", "266", "267", "268", "269", "270", "271", "272", "273", "274", "275", "276", "277", "278", "279", "280", "281", "282", "283", "284", "285", "286", "287", "288", "289", "290", "291", "292", "293", "294", "295", "296", "297", "298", "299", "300", "301", "302", "303", "304", "305", "306", "307", "308", "309", "310", "311", "312", "313", "314", "315", "316", "317", "318", "319", "320", "321", "322", "323", "324", "325", "326", "327", "328", "329", "330", "331"],
		"CDFG" : "uz_VSD_6ph_asym",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "20", "EstimateLatencyMax" : "20",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"InputProcess" : [
			{"ID" : "1", "Name" : "Block_split13_proc_U0"}],
		"OutputProcess" : [
			{"ID" : "36", "Name" : "Block_split1350_proc_U0"},
			{"ID" : "74", "Name" : "Block_split1388_proc_U0"},
			{"ID" : "112", "Name" : "Block_split13126_proc_U0"},
			{"ID" : "150", "Name" : "Block_split13164_proc_U0"},
			{"ID" : "188", "Name" : "Block_split13202_proc_U0"},
			{"ID" : "216", "Name" : "Block_split13240_proc_U0"}],
		"Port" : [
			{"Name" : "in_r", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "Block_split13_proc_U0", "Port" : "in_r"}]},
			{"Name" : "out_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "36", "SubInstance" : "Block_split1350_proc_U0", "Port" : "out_1"}]},
			{"Name" : "out_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "74", "SubInstance" : "Block_split1388_proc_U0", "Port" : "out_2"}]},
			{"Name" : "out_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "112", "SubInstance" : "Block_split13126_proc_U0", "Port" : "out_3"}]},
			{"Name" : "out_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "150", "SubInstance" : "Block_split13164_proc_U0", "Port" : "out_4"}]},
			{"Name" : "out_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "188", "SubInstance" : "Block_split13202_proc_U0", "Port" : "out_5"}]},
			{"Name" : "out_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "216", "SubInstance" : "Block_split13240_proc_U0", "Port" : "out_6"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split13_proc",
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
		"Port" : [
			{"Name" : "in_r", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "cpy_in_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "218", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "219", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "220", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "221", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "222", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "223", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0", "Parent" : "0", "Child" : ["3", "4", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"],
		"CDFG" : "multiply_line11",
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
		"StartSource" : "1",
		"StartFifo" : "start_for_multiply_line11_U0_U",
		"InputProcess" : [
			{"ID" : "3", "Name" : "multiply_line11_entry145_U0"}],
		"OutputProcess" : [
			{"ID" : "8", "Name" : "p_prop_ret_products_OC_0_dc_proc_U0"},
			{"ID" : "9", "Name" : "p_prop_ret_products_OC_1_dc_proc_U0"},
			{"ID" : "10", "Name" : "p_prop_ret_products_OC_2_dc_proc_U0"},
			{"ID" : "11", "Name" : "p_prop_ret_products_OC_3_dc_proc_U0"},
			{"ID" : "12", "Name" : "p_prop_ret_products_OC_4_dc_proc_U0"},
			{"ID" : "13", "Name" : "p_prop_ret_products_OC_5_dc_proc_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "218", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "219", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "220", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "221", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "222", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "223", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "multiply_line11_entry145_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "224", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "225", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "226", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "227", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "228", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "229", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "multiply_line11_Block_split1_proc144_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "27", "DependentChan" : "230", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "8", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "28", "DependentChan" : "231", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "9", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "30", "DependentChan" : "232", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "10", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "32", "DependentChan" : "233", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "11", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "34", "DependentChan" : "234", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "12", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "36", "DependentChan" : "235", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "13", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.multiply_line11_entry145_U0", "Parent" : "2",
		"CDFG" : "multiply_line11_entry145",
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
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "223", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "222", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "221", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "220", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "219", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "218", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "14", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "15", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "16", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "17", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "18", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "4", "DependentChan" : "19", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.multiply_line11_Block_split1_proc144_U0", "Parent" : "2", "Child" : ["5", "6", "7"],
		"CDFG" : "multiply_line11_Block_split1_proc144",
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
		"StartSource" : "3",
		"StartFifo" : "start_for_multiply_line11_Block_split1_proc144_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "19", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "224", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "18", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "225", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "17", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "226", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "16", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "227", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "15", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "228", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "3", "DependentChan" : "14", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "39", "DependentChan" : "229", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "5", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.multiply_line11_Block_split1_proc144_U0.fmul_32ns_32ns_32_3_max_dsp_1_U20", "Parent" : "4"},
	{"ID" : "6", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.multiply_line11_Block_split1_proc144_U0.fmul_32ns_32ns_32_3_max_dsp_1_U21", "Parent" : "4"},
	{"ID" : "7", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.multiply_line11_Block_split1_proc144_U0.fmul_32ns_32ns_32_3_max_dsp_1_U22", "Parent" : "4"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_0_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "20", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "27", "DependentChan" : "230", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_1_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "21", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "28", "DependentChan" : "231", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_2_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "22", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "30", "DependentChan" : "232", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_3_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "23", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "32", "DependentChan" : "233", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_4_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "24", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "34", "DependentChan" : "234", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.p_prop_ret_products_OC_5_dc_proc_U0", "Parent" : "2",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "25", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "36", "DependentChan" : "235", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_5_c_U", "Parent" : "2"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_4_c_U", "Parent" : "2"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_3_c_U", "Parent" : "2"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_2_c_U", "Parent" : "2"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_1_c_U", "Parent" : "2"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.scalar_val_0_c_U", "Parent" : "2"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_0_dc_channel_U", "Parent" : "2"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_1_dc_channel_U", "Parent" : "2"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_2_dc_channel_U", "Parent" : "2"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_3_dc_channel_U", "Parent" : "2"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_4_dc_channel_U", "Parent" : "2"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.products_5_dc_channel_U", "Parent" : "2"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line11_U0.start_for_multiply_line11_Block_split1_proc144_U0_U", "Parent" : "2"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1320_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split1320_proc",
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
		"StartSource" : "2",
		"StartFifo" : "start_for_Block_split1320_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "8", "DependentChan" : "230", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1326_proc_U0", "Parent" : "0", "Child" : ["29"],
		"CDFG" : "Block_split1326_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "9", "DependentChan" : "231", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "27", "DependentChan" : "236", "DependentChanDepth" : "2"}]},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1326_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U80", "Parent" : "28"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1332_proc_U0", "Parent" : "0", "Child" : ["31"],
		"CDFG" : "Block_split1332_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "10", "DependentChan" : "232", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "28", "DependentChan" : "237", "DependentChanDepth" : "2"}]},
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1332_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U84", "Parent" : "30"},
	{"ID" : "32", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1338_proc_U0", "Parent" : "0", "Child" : ["33"],
		"CDFG" : "Block_split1338_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "11", "DependentChan" : "233", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "30", "DependentChan" : "238", "DependentChanDepth" : "2"}]},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1338_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U87", "Parent" : "32"},
	{"ID" : "34", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1344_proc_U0", "Parent" : "0", "Child" : ["35"],
		"CDFG" : "Block_split1344_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "12", "DependentChan" : "234", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "32", "DependentChan" : "239", "DependentChanDepth" : "2"}]},
	{"ID" : "35", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1344_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U90", "Parent" : "34"},
	{"ID" : "36", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1350_proc_U0", "Parent" : "0", "Child" : ["37"],
		"CDFG" : "Block_split1350_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "13", "DependentChan" : "235", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "34", "DependentChan" : "240", "DependentChanDepth" : "2"},
			{"Name" : "out_1", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "37", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1350_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U93", "Parent" : "36"},
	{"ID" : "38", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0", "Parent" : "0", "Child" : ["39", "40", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64"],
		"CDFG" : "multiply_line12",
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
		"StartSource" : "2",
		"StartFifo" : "start_for_multiply_line12_U0_U",
		"InputProcess" : [
			{"ID" : "39", "Name" : "multiply_line12_entry155_U0"}],
		"OutputProcess" : [
			{"ID" : "46", "Name" : "p_prop_ret_products_OC_0_dc_proc62_U0"},
			{"ID" : "47", "Name" : "p_prop_ret_products_OC_1_dc_proc63_U0"},
			{"ID" : "48", "Name" : "p_prop_ret_products_OC_2_dc_proc64_U0"},
			{"ID" : "49", "Name" : "p_prop_ret_products_OC_3_dc_proc65_U0"},
			{"ID" : "50", "Name" : "p_prop_ret_products_OC_4_dc_proc66_U0"},
			{"ID" : "51", "Name" : "p_prop_ret_products_OC_5_dc_proc67_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "224", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "225", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "226", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "227", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "228", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "229", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "39", "SubInstance" : "multiply_line12_entry155_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "241", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "242", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "243", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "244", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "245", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "246", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "40", "SubInstance" : "multiply_line12_Block_split1_proc154_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "65", "DependentChan" : "247", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "46", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc62_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "66", "DependentChan" : "248", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "47", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc63_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "68", "DependentChan" : "249", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "48", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc64_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "70", "DependentChan" : "250", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "49", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc65_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "72", "DependentChan" : "251", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "50", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc66_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "74", "DependentChan" : "252", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "51", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc67_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_entry155_U0", "Parent" : "38",
		"CDFG" : "multiply_line12_entry155",
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
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "229", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "228", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "227", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "226", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "225", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "4", "DependentChan" : "224", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "52", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "53", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "54", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "55", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "56", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "40", "DependentChan" : "57", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0", "Parent" : "38", "Child" : ["41", "42", "43", "44", "45"],
		"CDFG" : "multiply_line12_Block_split1_proc154",
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
		"StartSource" : "39",
		"StartFifo" : "start_for_multiply_line12_Block_split1_proc154_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "57", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "241", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "56", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "242", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "55", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "243", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "54", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "244", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "53", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "245", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "39", "DependentChan" : "52", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "77", "DependentChan" : "246", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "41", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0.fmul_32ns_32ns_32_3_max_dsp_1_U109", "Parent" : "40"},
	{"ID" : "42", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0.fmul_32ns_32ns_32_3_max_dsp_1_U110", "Parent" : "40"},
	{"ID" : "43", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0.fmul_32ns_32ns_32_3_max_dsp_1_U111", "Parent" : "40"},
	{"ID" : "44", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0.fmul_32ns_32ns_32_3_max_dsp_1_U112", "Parent" : "40"},
	{"ID" : "45", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.multiply_line12_Block_split1_proc154_U0.fmul_32ns_32ns_32_3_max_dsp_1_U113", "Parent" : "40"},
	{"ID" : "46", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_0_dc_proc62_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc62",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "58", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "65", "DependentChan" : "247", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "47", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_1_dc_proc63_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc63",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "59", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "66", "DependentChan" : "248", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "48", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_2_dc_proc64_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc64",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "60", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "68", "DependentChan" : "249", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "49", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_3_dc_proc65_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc65",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "61", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "70", "DependentChan" : "250", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "50", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_4_dc_proc66_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc66",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "62", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "72", "DependentChan" : "251", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "51", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.p_prop_ret_products_OC_5_dc_proc67_U0", "Parent" : "38",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc67",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "63", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "74", "DependentChan" : "252", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "52", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_5_c_U", "Parent" : "38"},
	{"ID" : "53", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_4_c_U", "Parent" : "38"},
	{"ID" : "54", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_3_c_U", "Parent" : "38"},
	{"ID" : "55", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_2_c_U", "Parent" : "38"},
	{"ID" : "56", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_1_c_U", "Parent" : "38"},
	{"ID" : "57", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.scalar_val_0_c_U", "Parent" : "38"},
	{"ID" : "58", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_0_dc_channel_U", "Parent" : "38"},
	{"ID" : "59", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_1_dc_channel_U", "Parent" : "38"},
	{"ID" : "60", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_2_dc_channel_U", "Parent" : "38"},
	{"ID" : "61", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_3_dc_channel_U", "Parent" : "38"},
	{"ID" : "62", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_4_dc_channel_U", "Parent" : "38"},
	{"ID" : "63", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.products_5_dc_channel_U", "Parent" : "38"},
	{"ID" : "64", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line12_U0.start_for_multiply_line12_Block_split1_proc154_U0_U", "Parent" : "38"},
	{"ID" : "65", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1358_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split1358_proc",
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
		"StartSource" : "38",
		"StartFifo" : "start_for_Block_split1358_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "46", "DependentChan" : "247", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "66", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1364_proc_U0", "Parent" : "0", "Child" : ["67"],
		"CDFG" : "Block_split1364_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "47", "DependentChan" : "248", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "65", "DependentChan" : "253", "DependentChanDepth" : "2"}]},
	{"ID" : "67", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1364_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U170", "Parent" : "66"},
	{"ID" : "68", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1370_proc_U0", "Parent" : "0", "Child" : ["69"],
		"CDFG" : "Block_split1370_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "48", "DependentChan" : "249", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "66", "DependentChan" : "254", "DependentChanDepth" : "2"}]},
	{"ID" : "69", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1370_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U173", "Parent" : "68"},
	{"ID" : "70", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1376_proc_U0", "Parent" : "0", "Child" : ["71"],
		"CDFG" : "Block_split1376_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "49", "DependentChan" : "250", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "68", "DependentChan" : "255", "DependentChanDepth" : "2"}]},
	{"ID" : "71", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1376_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U176", "Parent" : "70"},
	{"ID" : "72", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1382_proc_U0", "Parent" : "0", "Child" : ["73"],
		"CDFG" : "Block_split1382_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "50", "DependentChan" : "251", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "70", "DependentChan" : "256", "DependentChanDepth" : "2"}]},
	{"ID" : "73", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1382_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U179", "Parent" : "72"},
	{"ID" : "74", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1388_proc_U0", "Parent" : "0", "Child" : ["75"],
		"CDFG" : "Block_split1388_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "51", "DependentChan" : "252", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "72", "DependentChan" : "257", "DependentChanDepth" : "2"},
			{"Name" : "out_2", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "75", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split1388_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U182", "Parent" : "74"},
	{"ID" : "76", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0", "Parent" : "0", "Child" : ["77", "78", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102"],
		"CDFG" : "multiply_line13",
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
		"StartSource" : "38",
		"StartFifo" : "start_for_multiply_line13_U0_U",
		"InputProcess" : [
			{"ID" : "77", "Name" : "multiply_line13_entry165_U0"}],
		"OutputProcess" : [
			{"ID" : "84", "Name" : "p_prop_ret_products_OC_0_dc_proc81_U0"},
			{"ID" : "85", "Name" : "p_prop_ret_products_OC_1_dc_proc82_U0"},
			{"ID" : "86", "Name" : "p_prop_ret_products_OC_2_dc_proc83_U0"},
			{"ID" : "87", "Name" : "p_prop_ret_products_OC_3_dc_proc84_U0"},
			{"ID" : "88", "Name" : "p_prop_ret_products_OC_4_dc_proc85_U0"},
			{"ID" : "89", "Name" : "p_prop_ret_products_OC_5_dc_proc86_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "241", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "242", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "243", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "244", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "245", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "246", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "77", "SubInstance" : "multiply_line13_entry165_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "258", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "259", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "260", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "261", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "262", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "263", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "78", "SubInstance" : "multiply_line13_Block_split1_proc164_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "103", "DependentChan" : "264", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "84", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc81_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "104", "DependentChan" : "265", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "85", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc82_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "106", "DependentChan" : "266", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "86", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc83_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "108", "DependentChan" : "267", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "87", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc84_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "110", "DependentChan" : "268", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "88", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc85_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "112", "DependentChan" : "269", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "89", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc86_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "77", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_entry165_U0", "Parent" : "76",
		"CDFG" : "multiply_line13_entry165",
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
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "246", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "245", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "244", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "243", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "242", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "40", "DependentChan" : "241", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "90", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "91", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "92", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "93", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "94", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "78", "DependentChan" : "95", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "78", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0", "Parent" : "76", "Child" : ["79", "80", "81", "82", "83"],
		"CDFG" : "multiply_line13_Block_split1_proc164",
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
		"StartSource" : "77",
		"StartFifo" : "start_for_multiply_line13_Block_split1_proc164_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "95", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "258", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "94", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "259", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "93", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "260", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "92", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "261", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "91", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "262", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "77", "DependentChan" : "90", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "115", "DependentChan" : "263", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "79", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0.fmul_32ns_32ns_32_3_max_dsp_1_U198", "Parent" : "78"},
	{"ID" : "80", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0.fmul_32ns_32ns_32_3_max_dsp_1_U199", "Parent" : "78"},
	{"ID" : "81", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0.fmul_32ns_32ns_32_3_max_dsp_1_U200", "Parent" : "78"},
	{"ID" : "82", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0.fmul_32ns_32ns_32_3_max_dsp_1_U201", "Parent" : "78"},
	{"ID" : "83", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.multiply_line13_Block_split1_proc164_U0.fmul_32ns_32ns_32_3_max_dsp_1_U202", "Parent" : "78"},
	{"ID" : "84", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_0_dc_proc81_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc81",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "96", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "103", "DependentChan" : "264", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "85", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_1_dc_proc82_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc82",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "97", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "104", "DependentChan" : "265", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "86", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_2_dc_proc83_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc83",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "98", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "106", "DependentChan" : "266", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "87", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_3_dc_proc84_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc84",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "99", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "108", "DependentChan" : "267", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "88", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_4_dc_proc85_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc85",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "100", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "110", "DependentChan" : "268", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "89", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.p_prop_ret_products_OC_5_dc_proc86_U0", "Parent" : "76",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc86",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "101", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "112", "DependentChan" : "269", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "90", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_5_c_U", "Parent" : "76"},
	{"ID" : "91", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_4_c_U", "Parent" : "76"},
	{"ID" : "92", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_3_c_U", "Parent" : "76"},
	{"ID" : "93", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_2_c_U", "Parent" : "76"},
	{"ID" : "94", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_1_c_U", "Parent" : "76"},
	{"ID" : "95", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.scalar_val_0_c_U", "Parent" : "76"},
	{"ID" : "96", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_0_dc_channel_U", "Parent" : "76"},
	{"ID" : "97", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_1_dc_channel_U", "Parent" : "76"},
	{"ID" : "98", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_2_dc_channel_U", "Parent" : "76"},
	{"ID" : "99", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_3_dc_channel_U", "Parent" : "76"},
	{"ID" : "100", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_4_dc_channel_U", "Parent" : "76"},
	{"ID" : "101", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.products_5_dc_channel_U", "Parent" : "76"},
	{"ID" : "102", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line13_U0.start_for_multiply_line13_Block_split1_proc164_U0_U", "Parent" : "76"},
	{"ID" : "103", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split1396_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split1396_proc",
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
		"StartSource" : "76",
		"StartFifo" : "start_for_Block_split1396_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "84", "DependentChan" : "264", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "104", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13102_proc_U0", "Parent" : "0", "Child" : ["105"],
		"CDFG" : "Block_split13102_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "85", "DependentChan" : "265", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "103", "DependentChan" : "270", "DependentChanDepth" : "2"}]},
	{"ID" : "105", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13102_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U259", "Parent" : "104"},
	{"ID" : "106", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13108_proc_U0", "Parent" : "0", "Child" : ["107"],
		"CDFG" : "Block_split13108_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "86", "DependentChan" : "266", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "104", "DependentChan" : "271", "DependentChanDepth" : "2"}]},
	{"ID" : "107", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13108_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U262", "Parent" : "106"},
	{"ID" : "108", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13114_proc_U0", "Parent" : "0", "Child" : ["109"],
		"CDFG" : "Block_split13114_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "87", "DependentChan" : "267", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "106", "DependentChan" : "272", "DependentChanDepth" : "2"}]},
	{"ID" : "109", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13114_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U265", "Parent" : "108"},
	{"ID" : "110", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13120_proc_U0", "Parent" : "0", "Child" : ["111"],
		"CDFG" : "Block_split13120_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "88", "DependentChan" : "268", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "108", "DependentChan" : "273", "DependentChanDepth" : "2"}]},
	{"ID" : "111", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13120_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U268", "Parent" : "110"},
	{"ID" : "112", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13126_proc_U0", "Parent" : "0", "Child" : ["113"],
		"CDFG" : "Block_split13126_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "89", "DependentChan" : "269", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "110", "DependentChan" : "274", "DependentChanDepth" : "2"},
			{"Name" : "out_3", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "113", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13126_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U271", "Parent" : "112"},
	{"ID" : "114", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0", "Parent" : "0", "Child" : ["115", "116", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140"],
		"CDFG" : "multiply_line14",
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
		"StartSource" : "76",
		"StartFifo" : "start_for_multiply_line14_U0_U",
		"InputProcess" : [
			{"ID" : "115", "Name" : "multiply_line14_entry175_U0"}],
		"OutputProcess" : [
			{"ID" : "122", "Name" : "p_prop_ret_products_OC_0_dc_proc100_U0"},
			{"ID" : "123", "Name" : "p_prop_ret_products_OC_1_dc_proc101_U0"},
			{"ID" : "124", "Name" : "p_prop_ret_products_OC_2_dc_proc102_U0"},
			{"ID" : "125", "Name" : "p_prop_ret_products_OC_3_dc_proc103_U0"},
			{"ID" : "126", "Name" : "p_prop_ret_products_OC_4_dc_proc104_U0"},
			{"ID" : "127", "Name" : "p_prop_ret_products_OC_5_dc_proc105_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "258", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "259", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "260", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "261", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "262", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "263", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "115", "SubInstance" : "multiply_line14_entry175_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "275", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "276", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "277", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "278", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "279", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "280", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "116", "SubInstance" : "multiply_line14_Block_split1_proc174_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "141", "DependentChan" : "281", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "122", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc100_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "142", "DependentChan" : "282", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "123", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc101_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "144", "DependentChan" : "283", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "124", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc102_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "146", "DependentChan" : "284", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "125", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc103_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "148", "DependentChan" : "285", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "126", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc104_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "150", "DependentChan" : "286", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "127", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc105_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "115", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_entry175_U0", "Parent" : "114",
		"CDFG" : "multiply_line14_entry175",
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
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "263", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "262", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "261", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "260", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "259", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "78", "DependentChan" : "258", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "128", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "129", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "130", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "131", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "132", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "116", "DependentChan" : "133", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "116", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0", "Parent" : "114", "Child" : ["117", "118", "119", "120", "121"],
		"CDFG" : "multiply_line14_Block_split1_proc174",
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
		"StartSource" : "115",
		"StartFifo" : "start_for_multiply_line14_Block_split1_proc174_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "133", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "275", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "132", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "276", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "131", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "277", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "130", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "278", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "129", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "279", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "115", "DependentChan" : "128", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "153", "DependentChan" : "280", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "117", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0.fmul_32ns_32ns_32_3_max_dsp_1_U287", "Parent" : "116"},
	{"ID" : "118", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0.fmul_32ns_32ns_32_3_max_dsp_1_U288", "Parent" : "116"},
	{"ID" : "119", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0.fmul_32ns_32ns_32_3_max_dsp_1_U289", "Parent" : "116"},
	{"ID" : "120", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0.fmul_32ns_32ns_32_3_max_dsp_1_U290", "Parent" : "116"},
	{"ID" : "121", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.multiply_line14_Block_split1_proc174_U0.fmul_32ns_32ns_32_3_max_dsp_1_U291", "Parent" : "116"},
	{"ID" : "122", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_0_dc_proc100_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc100",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "134", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "141", "DependentChan" : "281", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "123", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_1_dc_proc101_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc101",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "135", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "142", "DependentChan" : "282", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "124", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_2_dc_proc102_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc102",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "136", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "144", "DependentChan" : "283", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "125", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_3_dc_proc103_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc103",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "137", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "146", "DependentChan" : "284", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "126", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_4_dc_proc104_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc104",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "138", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "148", "DependentChan" : "285", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "127", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.p_prop_ret_products_OC_5_dc_proc105_U0", "Parent" : "114",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc105",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "139", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "150", "DependentChan" : "286", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "128", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_5_c_U", "Parent" : "114"},
	{"ID" : "129", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_4_c_U", "Parent" : "114"},
	{"ID" : "130", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_3_c_U", "Parent" : "114"},
	{"ID" : "131", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_2_c_U", "Parent" : "114"},
	{"ID" : "132", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_1_c_U", "Parent" : "114"},
	{"ID" : "133", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.scalar_val_0_c_U", "Parent" : "114"},
	{"ID" : "134", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_0_dc_channel_U", "Parent" : "114"},
	{"ID" : "135", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_1_dc_channel_U", "Parent" : "114"},
	{"ID" : "136", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_2_dc_channel_U", "Parent" : "114"},
	{"ID" : "137", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_3_dc_channel_U", "Parent" : "114"},
	{"ID" : "138", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_4_dc_channel_U", "Parent" : "114"},
	{"ID" : "139", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.products_5_dc_channel_U", "Parent" : "114"},
	{"ID" : "140", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line14_U0.start_for_multiply_line14_Block_split1_proc174_U0_U", "Parent" : "114"},
	{"ID" : "141", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13134_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split13134_proc",
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
		"StartSource" : "114",
		"StartFifo" : "start_for_Block_split13134_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "122", "DependentChan" : "281", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "142", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13140_proc_U0", "Parent" : "0", "Child" : ["143"],
		"CDFG" : "Block_split13140_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "123", "DependentChan" : "282", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "141", "DependentChan" : "287", "DependentChanDepth" : "2"}]},
	{"ID" : "143", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13140_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U348", "Parent" : "142"},
	{"ID" : "144", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13146_proc_U0", "Parent" : "0", "Child" : ["145"],
		"CDFG" : "Block_split13146_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "124", "DependentChan" : "283", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "142", "DependentChan" : "288", "DependentChanDepth" : "2"}]},
	{"ID" : "145", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13146_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U351", "Parent" : "144"},
	{"ID" : "146", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13152_proc_U0", "Parent" : "0", "Child" : ["147"],
		"CDFG" : "Block_split13152_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "125", "DependentChan" : "284", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "144", "DependentChan" : "289", "DependentChanDepth" : "2"}]},
	{"ID" : "147", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13152_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U354", "Parent" : "146"},
	{"ID" : "148", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13158_proc_U0", "Parent" : "0", "Child" : ["149"],
		"CDFG" : "Block_split13158_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "126", "DependentChan" : "285", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "146", "DependentChan" : "290", "DependentChanDepth" : "2"}]},
	{"ID" : "149", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13158_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U357", "Parent" : "148"},
	{"ID" : "150", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13164_proc_U0", "Parent" : "0", "Child" : ["151"],
		"CDFG" : "Block_split13164_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "127", "DependentChan" : "286", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "148", "DependentChan" : "291", "DependentChanDepth" : "2"},
			{"Name" : "out_4", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "151", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13164_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U360", "Parent" : "150"},
	{"ID" : "152", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0", "Parent" : "0", "Child" : ["153", "154", "160", "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178"],
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
		"StartSource" : "114",
		"StartFifo" : "start_for_multiply_line15_U0_U",
		"InputProcess" : [
			{"ID" : "153", "Name" : "multiply_line15_entry185_U0"}],
		"OutputProcess" : [
			{"ID" : "160", "Name" : "p_prop_ret_products_OC_0_dc_proc119_U0"},
			{"ID" : "161", "Name" : "p_prop_ret_products_OC_1_dc_proc120_U0"},
			{"ID" : "162", "Name" : "p_prop_ret_products_OC_2_dc_proc121_U0"},
			{"ID" : "163", "Name" : "p_prop_ret_products_OC_3_dc_proc122_U0"},
			{"ID" : "164", "Name" : "p_prop_ret_products_OC_4_dc_proc123_U0"},
			{"ID" : "165", "Name" : "p_prop_ret_products_OC_5_dc_proc124_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "275", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "276", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "277", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "278", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "279", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "280", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "153", "SubInstance" : "multiply_line15_entry185_U0", "Port" : "scalar_val_5"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "292", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_0_out"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "293", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_1_out"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "294", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_2_out"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "295", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_3_out"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "296", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_4_out"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "297", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "154", "SubInstance" : "multiply_line15_Block_split1_proc184_U0", "Port" : "val_5_out"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "179", "DependentChan" : "298", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "160", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc119_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "180", "DependentChan" : "299", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "161", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc120_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "182", "DependentChan" : "300", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "162", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc121_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "184", "DependentChan" : "301", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "163", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc122_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "186", "DependentChan" : "302", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "164", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc123_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "188", "DependentChan" : "303", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "165", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc124_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "153", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_entry185_U0", "Parent" : "152",
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
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "280", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "279", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "278", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "277", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "276", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "116", "DependentChan" : "275", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "166", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "167", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "168", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "169", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "170", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "154", "DependentChan" : "171", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "154", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0", "Parent" : "152", "Child" : ["155", "156", "157", "158", "159"],
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
		"StartSource" : "153",
		"StartFifo" : "start_for_multiply_line15_Block_split1_proc184_U0_U",
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "171", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "292", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "170", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "293", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "169", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "294", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "168", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "295", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "167", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "296", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "153", "DependentChan" : "166", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "191", "DependentChan" : "297", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "155", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U376", "Parent" : "154"},
	{"ID" : "156", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U377", "Parent" : "154"},
	{"ID" : "157", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U378", "Parent" : "154"},
	{"ID" : "158", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U379", "Parent" : "154"},
	{"ID" : "159", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.multiply_line15_Block_split1_proc184_U0.fmul_32ns_32ns_32_3_max_dsp_1_U380", "Parent" : "154"},
	{"ID" : "160", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_0_dc_proc119_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "172", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "179", "DependentChan" : "298", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "161", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_1_dc_proc120_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "173", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "180", "DependentChan" : "299", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "162", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_2_dc_proc121_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "174", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "182", "DependentChan" : "300", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "163", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_3_dc_proc122_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "175", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "184", "DependentChan" : "301", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "164", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_4_dc_proc123_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "176", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "186", "DependentChan" : "302", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "165", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.p_prop_ret_products_OC_5_dc_proc124_U0", "Parent" : "152",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "177", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "188", "DependentChan" : "303", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "166", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_5_c_U", "Parent" : "152"},
	{"ID" : "167", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_4_c_U", "Parent" : "152"},
	{"ID" : "168", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_3_c_U", "Parent" : "152"},
	{"ID" : "169", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_2_c_U", "Parent" : "152"},
	{"ID" : "170", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_1_c_U", "Parent" : "152"},
	{"ID" : "171", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.scalar_val_0_c_U", "Parent" : "152"},
	{"ID" : "172", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_0_dc_channel_U", "Parent" : "152"},
	{"ID" : "173", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_1_dc_channel_U", "Parent" : "152"},
	{"ID" : "174", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_2_dc_channel_U", "Parent" : "152"},
	{"ID" : "175", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_3_dc_channel_U", "Parent" : "152"},
	{"ID" : "176", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_4_dc_channel_U", "Parent" : "152"},
	{"ID" : "177", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.products_5_dc_channel_U", "Parent" : "152"},
	{"ID" : "178", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line15_U0.start_for_multiply_line15_Block_split1_proc184_U0_U", "Parent" : "152"},
	{"ID" : "179", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13172_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split13172_proc",
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
		"StartSource" : "152",
		"StartFifo" : "start_for_Block_split13172_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "160", "DependentChan" : "298", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "180", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13178_proc_U0", "Parent" : "0", "Child" : ["181"],
		"CDFG" : "Block_split13178_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "161", "DependentChan" : "299", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "179", "DependentChan" : "304", "DependentChanDepth" : "2"}]},
	{"ID" : "181", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13178_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U437", "Parent" : "180"},
	{"ID" : "182", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13184_proc_U0", "Parent" : "0", "Child" : ["183"],
		"CDFG" : "Block_split13184_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "162", "DependentChan" : "300", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "180", "DependentChan" : "305", "DependentChanDepth" : "2"}]},
	{"ID" : "183", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13184_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U440", "Parent" : "182"},
	{"ID" : "184", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13190_proc_U0", "Parent" : "0", "Child" : ["185"],
		"CDFG" : "Block_split13190_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "163", "DependentChan" : "301", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "182", "DependentChan" : "306", "DependentChanDepth" : "2"}]},
	{"ID" : "185", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13190_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U443", "Parent" : "184"},
	{"ID" : "186", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13196_proc_U0", "Parent" : "0", "Child" : ["187"],
		"CDFG" : "Block_split13196_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "164", "DependentChan" : "302", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "184", "DependentChan" : "307", "DependentChanDepth" : "2"}]},
	{"ID" : "187", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13196_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U446", "Parent" : "186"},
	{"ID" : "188", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13202_proc_U0", "Parent" : "0", "Child" : ["189"],
		"CDFG" : "Block_split13202_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "165", "DependentChan" : "303", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "186", "DependentChan" : "308", "DependentChanDepth" : "2"},
			{"Name" : "out_5", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "189", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13202_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U449", "Parent" : "188"},
	{"ID" : "190", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0", "Parent" : "0", "Child" : ["191", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206"],
		"CDFG" : "multiply_line16",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"StartSource" : "152",
		"StartFifo" : "start_for_multiply_line16_U0_U",
		"InputProcess" : [
			{"ID" : "191", "Name" : "multiply_line16_Block_split1_proc_U0"}],
		"OutputProcess" : [
			{"ID" : "195", "Name" : "p_prop_ret_products_OC_0_dc_proc132_U0"},
			{"ID" : "196", "Name" : "p_prop_ret_products_OC_1_dc_proc133_U0"},
			{"ID" : "197", "Name" : "p_prop_ret_products_OC_2_dc_proc134_U0"},
			{"ID" : "198", "Name" : "p_prop_ret_products_OC_3_dc_proc135_U0"},
			{"ID" : "199", "Name" : "p_prop_ret_products_OC_4_dc_proc136_U0"},
			{"ID" : "200", "Name" : "p_prop_ret_products_OC_5_dc_proc137_U0"}],
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "292", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_0"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "293", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_1"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "294", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_2"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "295", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_3"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "296", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_4"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "297", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "191", "SubInstance" : "multiply_line16_Block_split1_proc_U0", "Port" : "val_5"}]},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "207", "DependentChan" : "309", "DependentChanDepth" : "2",
				"SubConnect" : [
					{"ID" : "195", "SubInstance" : "p_prop_ret_products_OC_0_dc_proc132_U0", "Port" : "products_0_out"}]},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "208", "DependentChan" : "310", "DependentChanDepth" : "3",
				"SubConnect" : [
					{"ID" : "196", "SubInstance" : "p_prop_ret_products_OC_1_dc_proc133_U0", "Port" : "products_1_out"}]},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "210", "DependentChan" : "311", "DependentChanDepth" : "4",
				"SubConnect" : [
					{"ID" : "197", "SubInstance" : "p_prop_ret_products_OC_2_dc_proc134_U0", "Port" : "products_2_out"}]},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "212", "DependentChan" : "312", "DependentChanDepth" : "5",
				"SubConnect" : [
					{"ID" : "198", "SubInstance" : "p_prop_ret_products_OC_3_dc_proc135_U0", "Port" : "products_3_out"}]},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "214", "DependentChan" : "313", "DependentChanDepth" : "6",
				"SubConnect" : [
					{"ID" : "199", "SubInstance" : "p_prop_ret_products_OC_4_dc_proc136_U0", "Port" : "products_4_out"}]},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "216", "DependentChan" : "314", "DependentChanDepth" : "7",
				"SubConnect" : [
					{"ID" : "200", "SubInstance" : "p_prop_ret_products_OC_5_dc_proc137_U0", "Port" : "products_5_out"}]}]},
	{"ID" : "191", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.multiply_line16_Block_split1_proc_U0", "Parent" : "190", "Child" : ["192", "193", "194"],
		"CDFG" : "multiply_line16_Block_split1_proc",
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
		"Port" : [
			{"Name" : "val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "292", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "293", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "294", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "295", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "296", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "154", "DependentChan" : "297", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "192", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.multiply_line16_Block_split1_proc_U0.fmul_32ns_32ns_32_3_max_dsp_1_U453", "Parent" : "191"},
	{"ID" : "193", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.multiply_line16_Block_split1_proc_U0.fmul_32ns_32ns_32_3_max_dsp_1_U454", "Parent" : "191"},
	{"ID" : "194", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.multiply_line16_Block_split1_proc_U0.fmul_32ns_32ns_32_3_max_dsp_1_U455", "Parent" : "191"},
	{"ID" : "195", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_0_dc_proc132_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_0_dc_proc132",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "201", "DependentChanDepth" : "2"},
			{"Name" : "products_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "207", "DependentChan" : "309", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "196", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_1_dc_proc133_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_1_dc_proc133",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "202", "DependentChanDepth" : "2"},
			{"Name" : "products_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "208", "DependentChan" : "310", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "197", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_2_dc_proc134_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_2_dc_proc134",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "203", "DependentChanDepth" : "2"},
			{"Name" : "products_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "210", "DependentChan" : "311", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "198", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_3_dc_proc135_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_3_dc_proc135",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "204", "DependentChanDepth" : "2"},
			{"Name" : "products_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "212", "DependentChan" : "312", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "199", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_4_dc_proc136_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_4_dc_proc136",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "205", "DependentChanDepth" : "2"},
			{"Name" : "products_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "214", "DependentChan" : "313", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "200", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.p_prop_ret_products_OC_5_dc_proc137_U0", "Parent" : "190",
		"CDFG" : "p_prop_ret_products_OC_5_dc_proc137",
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
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "191", "DependentChan" : "206", "DependentChanDepth" : "2"},
			{"Name" : "products_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "216", "DependentChan" : "314", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "201", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_0_dc_channel_U", "Parent" : "190"},
	{"ID" : "202", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_1_dc_channel_U", "Parent" : "190"},
	{"ID" : "203", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_2_dc_channel_U", "Parent" : "190"},
	{"ID" : "204", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_3_dc_channel_U", "Parent" : "190"},
	{"ID" : "205", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_4_dc_channel_U", "Parent" : "190"},
	{"ID" : "206", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.multiply_line16_U0.products_5_dc_channel_U", "Parent" : "190"},
	{"ID" : "207", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13210_proc_U0", "Parent" : "0",
		"CDFG" : "Block_split13210_proc",
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
		"StartSource" : "190",
		"StartFifo" : "start_for_Block_split13210_proc_U0_U",
		"Port" : [
			{"Name" : "products_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "195", "DependentChan" : "309", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "products_0_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "208", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13216_proc_U0", "Parent" : "0", "Child" : ["209"],
		"CDFG" : "Block_split13216_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "196", "DependentChan" : "310", "DependentChanDepth" : "3",
				"BlockSignal" : [
					{"Name" : "products_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "207", "DependentChan" : "315", "DependentChanDepth" : "2"}]},
	{"ID" : "209", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13216_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U493", "Parent" : "208"},
	{"ID" : "210", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13222_proc_U0", "Parent" : "0", "Child" : ["211"],
		"CDFG" : "Block_split13222_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "197", "DependentChan" : "311", "DependentChanDepth" : "4",
				"BlockSignal" : [
					{"Name" : "products_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "208", "DependentChan" : "316", "DependentChanDepth" : "2"}]},
	{"ID" : "211", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13222_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U496", "Parent" : "210"},
	{"ID" : "212", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13228_proc_U0", "Parent" : "0", "Child" : ["213"],
		"CDFG" : "Block_split13228_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "198", "DependentChan" : "312", "DependentChanDepth" : "5",
				"BlockSignal" : [
					{"Name" : "products_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "210", "DependentChan" : "317", "DependentChanDepth" : "2"}]},
	{"ID" : "213", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13228_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U499", "Parent" : "212"},
	{"ID" : "214", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13234_proc_U0", "Parent" : "0", "Child" : ["215"],
		"CDFG" : "Block_split13234_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "199", "DependentChan" : "313", "DependentChanDepth" : "6",
				"BlockSignal" : [
					{"Name" : "products_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "212", "DependentChan" : "318", "DependentChanDepth" : "2"}]},
	{"ID" : "215", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13234_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U502", "Parent" : "214"},
	{"ID" : "216", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Block_split13240_proc_U0", "Parent" : "0", "Child" : ["217"],
		"CDFG" : "Block_split13240_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "products_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "200", "DependentChan" : "314", "DependentChanDepth" : "7",
				"BlockSignal" : [
					{"Name" : "products_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "p_read", "Type" : "None", "Direction" : "I", "DependentProc" : "214", "DependentChan" : "319", "DependentChanDepth" : "2"},
			{"Name" : "out_6", "Type" : "Vld", "Direction" : "O"}]},
	{"ID" : "217", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Block_split13240_proc_U0.fadd_32ns_32ns_32_4_full_dsp_1_U505", "Parent" : "216"},
	{"ID" : "218", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c_U", "Parent" : "0"},
	{"ID" : "219", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c_U", "Parent" : "0"},
	{"ID" : "220", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c_U", "Parent" : "0"},
	{"ID" : "221", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c_U", "Parent" : "0"},
	{"ID" : "222", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c_U", "Parent" : "0"},
	{"ID" : "223", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c_U", "Parent" : "0"},
	{"ID" : "224", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c283_U", "Parent" : "0"},
	{"ID" : "225", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c284_U", "Parent" : "0"},
	{"ID" : "226", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c285_U", "Parent" : "0"},
	{"ID" : "227", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c286_U", "Parent" : "0"},
	{"ID" : "228", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c287_U", "Parent" : "0"},
	{"ID" : "229", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c288_U", "Parent" : "0"},
	{"ID" : "230", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c_U", "Parent" : "0"},
	{"ID" : "231", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c_U", "Parent" : "0"},
	{"ID" : "232", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c_U", "Parent" : "0"},
	{"ID" : "233", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c_U", "Parent" : "0"},
	{"ID" : "234", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c_U", "Parent" : "0"},
	{"ID" : "235", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c_U", "Parent" : "0"},
	{"ID" : "236", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_loc_channel_U", "Parent" : "0"},
	{"ID" : "237", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i_loc_channel_U", "Parent" : "0"},
	{"ID" : "238", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i_loc_channel_U", "Parent" : "0"},
	{"ID" : "239", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i_loc_channel_U", "Parent" : "0"},
	{"ID" : "240", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i_loc_channel_U", "Parent" : "0"},
	{"ID" : "241", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c289_U", "Parent" : "0"},
	{"ID" : "242", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c290_U", "Parent" : "0"},
	{"ID" : "243", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c291_U", "Parent" : "0"},
	{"ID" : "244", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c292_U", "Parent" : "0"},
	{"ID" : "245", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c293_U", "Parent" : "0"},
	{"ID" : "246", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c294_U", "Parent" : "0"},
	{"ID" : "247", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c295_U", "Parent" : "0"},
	{"ID" : "248", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c296_U", "Parent" : "0"},
	{"ID" : "249", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c297_U", "Parent" : "0"},
	{"ID" : "250", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c298_U", "Parent" : "0"},
	{"ID" : "251", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c299_U", "Parent" : "0"},
	{"ID" : "252", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c300_U", "Parent" : "0"},
	{"ID" : "253", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_1_loc_channel_U", "Parent" : "0"},
	{"ID" : "254", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i1_loc_channel_U", "Parent" : "0"},
	{"ID" : "255", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i1_loc_channel_U", "Parent" : "0"},
	{"ID" : "256", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i1_loc_channel_U", "Parent" : "0"},
	{"ID" : "257", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i1_loc_channel_U", "Parent" : "0"},
	{"ID" : "258", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c301_U", "Parent" : "0"},
	{"ID" : "259", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c302_U", "Parent" : "0"},
	{"ID" : "260", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c303_U", "Parent" : "0"},
	{"ID" : "261", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c304_U", "Parent" : "0"},
	{"ID" : "262", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c305_U", "Parent" : "0"},
	{"ID" : "263", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c306_U", "Parent" : "0"},
	{"ID" : "264", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c307_U", "Parent" : "0"},
	{"ID" : "265", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c308_U", "Parent" : "0"},
	{"ID" : "266", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c309_U", "Parent" : "0"},
	{"ID" : "267", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c310_U", "Parent" : "0"},
	{"ID" : "268", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c311_U", "Parent" : "0"},
	{"ID" : "269", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c312_U", "Parent" : "0"},
	{"ID" : "270", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_2_loc_channel_U", "Parent" : "0"},
	{"ID" : "271", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i2_loc_channel_U", "Parent" : "0"},
	{"ID" : "272", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i2_loc_channel_U", "Parent" : "0"},
	{"ID" : "273", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i2_loc_channel_U", "Parent" : "0"},
	{"ID" : "274", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i2_loc_channel_U", "Parent" : "0"},
	{"ID" : "275", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c313_U", "Parent" : "0"},
	{"ID" : "276", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c314_U", "Parent" : "0"},
	{"ID" : "277", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c315_U", "Parent" : "0"},
	{"ID" : "278", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c316_U", "Parent" : "0"},
	{"ID" : "279", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c317_U", "Parent" : "0"},
	{"ID" : "280", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c318_U", "Parent" : "0"},
	{"ID" : "281", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c319_U", "Parent" : "0"},
	{"ID" : "282", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c320_U", "Parent" : "0"},
	{"ID" : "283", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c321_U", "Parent" : "0"},
	{"ID" : "284", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c322_U", "Parent" : "0"},
	{"ID" : "285", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c323_U", "Parent" : "0"},
	{"ID" : "286", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c324_U", "Parent" : "0"},
	{"ID" : "287", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_3_loc_channel_U", "Parent" : "0"},
	{"ID" : "288", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i3_loc_channel_U", "Parent" : "0"},
	{"ID" : "289", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i3_loc_channel_U", "Parent" : "0"},
	{"ID" : "290", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i3_loc_channel_U", "Parent" : "0"},
	{"ID" : "291", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i3_loc_channel_U", "Parent" : "0"},
	{"ID" : "292", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_0_c325_U", "Parent" : "0"},
	{"ID" : "293", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_1_c326_U", "Parent" : "0"},
	{"ID" : "294", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_2_c327_U", "Parent" : "0"},
	{"ID" : "295", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_3_c328_U", "Parent" : "0"},
	{"ID" : "296", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_4_c329_U", "Parent" : "0"},
	{"ID" : "297", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.cpy_in_5_c330_U", "Parent" : "0"},
	{"ID" : "298", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c331_U", "Parent" : "0"},
	{"ID" : "299", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c332_U", "Parent" : "0"},
	{"ID" : "300", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c333_U", "Parent" : "0"},
	{"ID" : "301", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c334_U", "Parent" : "0"},
	{"ID" : "302", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c335_U", "Parent" : "0"},
	{"ID" : "303", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c336_U", "Parent" : "0"},
	{"ID" : "304", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_4_loc_channel_U", "Parent" : "0"},
	{"ID" : "305", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i4_loc_channel_U", "Parent" : "0"},
	{"ID" : "306", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i4_loc_channel_U", "Parent" : "0"},
	{"ID" : "307", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i4_loc_channel_U", "Parent" : "0"},
	{"ID" : "308", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i4_loc_channel_U", "Parent" : "0"},
	{"ID" : "309", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_c337_U", "Parent" : "0"},
	{"ID" : "310", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_1_c338_U", "Parent" : "0"},
	{"ID" : "311", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_2_c339_U", "Parent" : "0"},
	{"ID" : "312", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_3_c340_U", "Parent" : "0"},
	{"ID" : "313", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_4_c341_U", "Parent" : "0"},
	{"ID" : "314", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_5_c342_U", "Parent" : "0"},
	{"ID" : "315", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.products_0_load_5_loc_channel_U", "Parent" : "0"},
	{"ID" : "316", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add_i5_loc_channel_U", "Parent" : "0"},
	{"ID" : "317", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add3_i5_loc_channel_U", "Parent" : "0"},
	{"ID" : "318", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add5_i5_loc_channel_U", "Parent" : "0"},
	{"ID" : "319", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.add7_i5_loc_channel_U", "Parent" : "0"},
	{"ID" : "320", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line11_U0_U", "Parent" : "0"},
	{"ID" : "321", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split1320_proc_U0_U", "Parent" : "0"},
	{"ID" : "322", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line12_U0_U", "Parent" : "0"},
	{"ID" : "323", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split1358_proc_U0_U", "Parent" : "0"},
	{"ID" : "324", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line13_U0_U", "Parent" : "0"},
	{"ID" : "325", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split1396_proc_U0_U", "Parent" : "0"},
	{"ID" : "326", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line14_U0_U", "Parent" : "0"},
	{"ID" : "327", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split13134_proc_U0_U", "Parent" : "0"},
	{"ID" : "328", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line15_U0_U", "Parent" : "0"},
	{"ID" : "329", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split13172_proc_U0_U", "Parent" : "0"},
	{"ID" : "330", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_multiply_line16_U0_U", "Parent" : "0"},
	{"ID" : "331", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_Block_split13210_proc_U0_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	uz_VSD_6ph_asym {
		in_r {Type I LastRead 3 FirstWrite -1}
		out_1 {Type O LastRead -1 FirstWrite 4}
		out_2 {Type O LastRead -1 FirstWrite 4}
		out_3 {Type O LastRead -1 FirstWrite 4}
		out_4 {Type O LastRead -1 FirstWrite 4}
		out_5 {Type O LastRead -1 FirstWrite 4}
		out_6 {Type O LastRead -1 FirstWrite 4}}
	Block_split13_proc {
		in_r {Type I LastRead 3 FirstWrite -1}
		cpy_in_0_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_1_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_2_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_3_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_4_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_5_out {Type O LastRead -1 FirstWrite 3}}
	multiply_line11 {
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
	multiply_line11_entry145 {
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
	multiply_line11_Block_split1_proc144 {
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
	p_prop_ret_products_OC_0_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split1320_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split1326_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1332_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1338_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1344_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1350_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_1 {Type O LastRead -1 FirstWrite 4}}
	multiply_line12 {
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
	multiply_line12_entry155 {
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
	multiply_line12_Block_split1_proc154 {
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
	p_prop_ret_products_OC_0_dc_proc62 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc63 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc64 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc65 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc66 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc67 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split1358_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split1364_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1370_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1376_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1382_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split1388_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_2 {Type O LastRead -1 FirstWrite 4}}
	multiply_line13 {
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
	multiply_line13_entry165 {
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
	multiply_line13_Block_split1_proc164 {
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
	p_prop_ret_products_OC_0_dc_proc81 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc82 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc83 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc84 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc85 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc86 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split1396_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split13102_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13108_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13114_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13120_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13126_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_3 {Type O LastRead -1 FirstWrite 4}}
	multiply_line14 {
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
	multiply_line14_entry175 {
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
	multiply_line14_Block_split1_proc174 {
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
	p_prop_ret_products_OC_0_dc_proc100 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc101 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc102 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc103 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc104 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc105 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split13134_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split13140_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13146_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13152_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13158_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13164_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_4 {Type O LastRead -1 FirstWrite 4}}
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
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split13172_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split13178_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13184_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13190_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13196_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13202_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_5 {Type O LastRead -1 FirstWrite 4}}
	multiply_line16 {
		val_0 {Type I LastRead 0 FirstWrite -1}
		val_1 {Type I LastRead 0 FirstWrite -1}
		val_2 {Type I LastRead 0 FirstWrite -1}
		val_3 {Type I LastRead 0 FirstWrite -1}
		val_4 {Type I LastRead 0 FirstWrite -1}
		val_5 {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}
		products_1_out {Type O LastRead -1 FirstWrite 0}
		products_2_out {Type O LastRead -1 FirstWrite 0}
		products_3_out {Type O LastRead -1 FirstWrite 0}
		products_4_out {Type O LastRead -1 FirstWrite 0}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	multiply_line16_Block_split1_proc {
		val_0 {Type I LastRead 0 FirstWrite -1}
		val_1 {Type I LastRead 0 FirstWrite -1}
		val_2 {Type I LastRead 0 FirstWrite -1}
		val_3 {Type I LastRead 0 FirstWrite -1}
		val_4 {Type I LastRead 0 FirstWrite -1}
		val_5 {Type I LastRead 0 FirstWrite -1}}
	p_prop_ret_products_OC_0_dc_proc132 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_0_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_1_dc_proc133 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_1_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_2_dc_proc134 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_2_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_3_dc_proc135 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_3_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_4_dc_proc136 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_4_out {Type O LastRead -1 FirstWrite 0}}
	p_prop_ret_products_OC_5_dc_proc137 {
		p_read {Type I LastRead 0 FirstWrite -1}
		products_5_out {Type O LastRead -1 FirstWrite 0}}
	Block_split13210_proc {
		products_0 {Type I LastRead 0 FirstWrite -1}}
	Block_split13216_proc {
		products_1 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13222_proc {
		products_2 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13228_proc {
		products_3 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13234_proc {
		products_4 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}}
	Block_split13240_proc {
		products_5 {Type I LastRead 0 FirstWrite -1}
		p_read {Type I LastRead 1 FirstWrite -1}
		out_6 {Type O LastRead -1 FirstWrite 4}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "20", "Max" : "20"}
	, {"Name" : "Interval", "Min" : "5", "Max" : "5"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	in_r { ap_memory {  { in_r_address0 mem_address 1 3 }  { in_r_ce0 mem_ce 1 1 }  { in_r_d0 mem_din 1 32 }  { in_r_q0 mem_dout 0 32 }  { in_r_we0 mem_we 1 1 }  { in_r_address1 MemPortADDR2 1 3 }  { in_r_ce1 MemPortCE2 1 1 }  { in_r_d1 mem_din 1 32 }  { in_r_q1 MemPortDOUT2 0 32 }  { in_r_we1 mem_we 1 1 } } }
	out_1 { ap_vld {  { out_1 out_data 1 32 }  { out_1_ap_vld out_vld 1 1 } } }
	out_2 { ap_vld {  { out_2 out_data 1 32 }  { out_2_ap_vld out_vld 1 1 } } }
	out_3 { ap_vld {  { out_3 out_data 1 32 }  { out_3_ap_vld out_vld 1 1 } } }
	out_4 { ap_vld {  { out_4 out_data 1 32 }  { out_4_ap_vld out_vld 1 1 } } }
	out_5 { ap_vld {  { out_5 out_data 1 32 }  { out_5_ap_vld out_vld 1 1 } } }
	out_6 { ap_vld {  { out_6 out_data 1 32 }  { out_6_ap_vld out_vld 1 1 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
