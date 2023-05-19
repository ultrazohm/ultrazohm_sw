set moduleName multiply_line12_Block_split1_proc154
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {multiply_line12_Block_.split1_proc154}
set C_modelType { int 192 }
set C_modelArgList {
	{ scalar_val_0 float 32 regular {fifo 0}  }
	{ val_0_out float 32 regular {fifo 1}  }
	{ scalar_val_1 float 32 regular {fifo 0}  }
	{ val_1_out float 32 regular {fifo 1}  }
	{ scalar_val_2 float 32 regular {fifo 0}  }
	{ val_2_out float 32 regular {fifo 1}  }
	{ scalar_val_3 float 32 regular {fifo 0}  }
	{ val_3_out float 32 regular {fifo 1}  }
	{ scalar_val_4 float 32 regular {fifo 0}  }
	{ val_4_out float 32 regular {fifo 1}  }
	{ scalar_val_5 float 32 regular {fifo 0}  }
	{ val_5_out float 32 regular {fifo 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "scalar_val_0", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_0_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "scalar_val_1", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_1_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "scalar_val_2", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_2_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "scalar_val_3", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_3_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "scalar_val_4", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_4_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "scalar_val_5", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "val_5_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 192} ]}
# RTL Port declarations: 
set portNum 49
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ scalar_val_0_dout sc_in sc_lv 32 signal 0 } 
	{ scalar_val_0_empty_n sc_in sc_logic 1 signal 0 } 
	{ scalar_val_0_read sc_out sc_logic 1 signal 0 } 
	{ val_0_out_din sc_out sc_lv 32 signal 1 } 
	{ val_0_out_full_n sc_in sc_logic 1 signal 1 } 
	{ val_0_out_write sc_out sc_logic 1 signal 1 } 
	{ scalar_val_1_dout sc_in sc_lv 32 signal 2 } 
	{ scalar_val_1_empty_n sc_in sc_logic 1 signal 2 } 
	{ scalar_val_1_read sc_out sc_logic 1 signal 2 } 
	{ val_1_out_din sc_out sc_lv 32 signal 3 } 
	{ val_1_out_full_n sc_in sc_logic 1 signal 3 } 
	{ val_1_out_write sc_out sc_logic 1 signal 3 } 
	{ scalar_val_2_dout sc_in sc_lv 32 signal 4 } 
	{ scalar_val_2_empty_n sc_in sc_logic 1 signal 4 } 
	{ scalar_val_2_read sc_out sc_logic 1 signal 4 } 
	{ val_2_out_din sc_out sc_lv 32 signal 5 } 
	{ val_2_out_full_n sc_in sc_logic 1 signal 5 } 
	{ val_2_out_write sc_out sc_logic 1 signal 5 } 
	{ scalar_val_3_dout sc_in sc_lv 32 signal 6 } 
	{ scalar_val_3_empty_n sc_in sc_logic 1 signal 6 } 
	{ scalar_val_3_read sc_out sc_logic 1 signal 6 } 
	{ val_3_out_din sc_out sc_lv 32 signal 7 } 
	{ val_3_out_full_n sc_in sc_logic 1 signal 7 } 
	{ val_3_out_write sc_out sc_logic 1 signal 7 } 
	{ scalar_val_4_dout sc_in sc_lv 32 signal 8 } 
	{ scalar_val_4_empty_n sc_in sc_logic 1 signal 8 } 
	{ scalar_val_4_read sc_out sc_logic 1 signal 8 } 
	{ val_4_out_din sc_out sc_lv 32 signal 9 } 
	{ val_4_out_full_n sc_in sc_logic 1 signal 9 } 
	{ val_4_out_write sc_out sc_logic 1 signal 9 } 
	{ scalar_val_5_dout sc_in sc_lv 32 signal 10 } 
	{ scalar_val_5_empty_n sc_in sc_logic 1 signal 10 } 
	{ scalar_val_5_read sc_out sc_logic 1 signal 10 } 
	{ val_5_out_din sc_out sc_lv 32 signal 11 } 
	{ val_5_out_full_n sc_in sc_logic 1 signal 11 } 
	{ val_5_out_write sc_out sc_logic 1 signal 11 } 
	{ ap_return_0 sc_out sc_lv 32 signal -1 } 
	{ ap_return_1 sc_out sc_lv 32 signal -1 } 
	{ ap_return_2 sc_out sc_lv 32 signal -1 } 
	{ ap_return_3 sc_out sc_lv 32 signal -1 } 
	{ ap_return_4 sc_out sc_lv 32 signal -1 } 
	{ ap_return_5 sc_out sc_lv 32 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "scalar_val_0_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_0", "role": "dout" }} , 
 	{ "name": "scalar_val_0_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_0", "role": "empty_n" }} , 
 	{ "name": "scalar_val_0_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_0", "role": "read" }} , 
 	{ "name": "val_0_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_0_out", "role": "din" }} , 
 	{ "name": "val_0_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0_out", "role": "full_n" }} , 
 	{ "name": "val_0_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_0_out", "role": "write" }} , 
 	{ "name": "scalar_val_1_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_1", "role": "dout" }} , 
 	{ "name": "scalar_val_1_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_1", "role": "empty_n" }} , 
 	{ "name": "scalar_val_1_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_1", "role": "read" }} , 
 	{ "name": "val_1_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_1_out", "role": "din" }} , 
 	{ "name": "val_1_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1_out", "role": "full_n" }} , 
 	{ "name": "val_1_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_1_out", "role": "write" }} , 
 	{ "name": "scalar_val_2_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_2", "role": "dout" }} , 
 	{ "name": "scalar_val_2_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_2", "role": "empty_n" }} , 
 	{ "name": "scalar_val_2_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_2", "role": "read" }} , 
 	{ "name": "val_2_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_2_out", "role": "din" }} , 
 	{ "name": "val_2_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2_out", "role": "full_n" }} , 
 	{ "name": "val_2_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_2_out", "role": "write" }} , 
 	{ "name": "scalar_val_3_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_3", "role": "dout" }} , 
 	{ "name": "scalar_val_3_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_3", "role": "empty_n" }} , 
 	{ "name": "scalar_val_3_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_3", "role": "read" }} , 
 	{ "name": "val_3_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_3_out", "role": "din" }} , 
 	{ "name": "val_3_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3_out", "role": "full_n" }} , 
 	{ "name": "val_3_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_3_out", "role": "write" }} , 
 	{ "name": "scalar_val_4_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_4", "role": "dout" }} , 
 	{ "name": "scalar_val_4_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_4", "role": "empty_n" }} , 
 	{ "name": "scalar_val_4_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_4", "role": "read" }} , 
 	{ "name": "val_4_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_4_out", "role": "din" }} , 
 	{ "name": "val_4_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4_out", "role": "full_n" }} , 
 	{ "name": "val_4_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_4_out", "role": "write" }} , 
 	{ "name": "scalar_val_5_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "scalar_val_5", "role": "dout" }} , 
 	{ "name": "scalar_val_5_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_5", "role": "empty_n" }} , 
 	{ "name": "scalar_val_5_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "scalar_val_5", "role": "read" }} , 
 	{ "name": "val_5_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "val_5_out", "role": "din" }} , 
 	{ "name": "val_5_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5_out", "role": "full_n" }} , 
 	{ "name": "val_5_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "val_5_out", "role": "write" }} , 
 	{ "name": "ap_return_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_0", "role": "default" }} , 
 	{ "name": "ap_return_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_1", "role": "default" }} , 
 	{ "name": "ap_return_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_2", "role": "default" }} , 
 	{ "name": "ap_return_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_3", "role": "default" }} , 
 	{ "name": "ap_return_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_4", "role": "default" }} , 
 	{ "name": "ap_return_5", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_5", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5"],
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
		"Port" : [
			{"Name" : "scalar_val_0", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_0_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_1", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_1_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_3", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_3_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_4", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_4_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "scalar_val_5", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "scalar_val_5_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "val_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "val_5_out_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U109", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U110", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U111", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U112", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U113", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
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
		val_5_out {Type O LastRead -1 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "3", "Max" : "3"}
	, {"Name" : "Interval", "Min" : "3", "Max" : "3"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	scalar_val_0 { ap_fifo {  { scalar_val_0_dout fifo_data 0 32 }  { scalar_val_0_empty_n fifo_status 0 1 }  { scalar_val_0_read fifo_update 1 1 } } }
	val_0_out { ap_fifo {  { val_0_out_din fifo_data 1 32 }  { val_0_out_full_n fifo_status 0 1 }  { val_0_out_write fifo_update 1 1 } } }
	scalar_val_1 { ap_fifo {  { scalar_val_1_dout fifo_data 0 32 }  { scalar_val_1_empty_n fifo_status 0 1 }  { scalar_val_1_read fifo_update 1 1 } } }
	val_1_out { ap_fifo {  { val_1_out_din fifo_data 1 32 }  { val_1_out_full_n fifo_status 0 1 }  { val_1_out_write fifo_update 1 1 } } }
	scalar_val_2 { ap_fifo {  { scalar_val_2_dout fifo_data 0 32 }  { scalar_val_2_empty_n fifo_status 0 1 }  { scalar_val_2_read fifo_update 1 1 } } }
	val_2_out { ap_fifo {  { val_2_out_din fifo_data 1 32 }  { val_2_out_full_n fifo_status 0 1 }  { val_2_out_write fifo_update 1 1 } } }
	scalar_val_3 { ap_fifo {  { scalar_val_3_dout fifo_data 0 32 }  { scalar_val_3_empty_n fifo_status 0 1 }  { scalar_val_3_read fifo_update 1 1 } } }
	val_3_out { ap_fifo {  { val_3_out_din fifo_data 1 32 }  { val_3_out_full_n fifo_status 0 1 }  { val_3_out_write fifo_update 1 1 } } }
	scalar_val_4 { ap_fifo {  { scalar_val_4_dout fifo_data 0 32 }  { scalar_val_4_empty_n fifo_status 0 1 }  { scalar_val_4_read fifo_update 1 1 } } }
	val_4_out { ap_fifo {  { val_4_out_din fifo_data 1 32 }  { val_4_out_full_n fifo_status 0 1 }  { val_4_out_write fifo_update 1 1 } } }
	scalar_val_5 { ap_fifo {  { scalar_val_5_dout fifo_data 0 32 }  { scalar_val_5_empty_n fifo_status 0 1 }  { scalar_val_5_read fifo_update 1 1 } } }
	val_5_out { ap_fifo {  { val_5_out_din fifo_data 1 32 }  { val_5_out_full_n fifo_status 0 1 }  { val_5_out_write fifo_update 1 1 } } }
}
