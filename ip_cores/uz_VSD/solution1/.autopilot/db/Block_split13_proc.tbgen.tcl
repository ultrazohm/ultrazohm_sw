set moduleName Block_split13_proc
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
set C_modelName {Block_.split13_proc}
set C_modelType { void 0 }
set C_modelArgList {
	{ in_r int 32 regular {array 6 { 1 1 } 1 1 }  }
	{ cpy_in_0_out float 32 regular {fifo 1}  }
	{ cpy_in_1_out float 32 regular {fifo 1}  }
	{ cpy_in_2_out float 32 regular {fifo 1}  }
	{ cpy_in_3_out float 32 regular {fifo 1}  }
	{ cpy_in_4_out float 32 regular {fifo 1}  }
	{ cpy_in_5_out float 32 regular {fifo 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "in_r", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "cpy_in_0_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cpy_in_1_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cpy_in_2_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cpy_in_3_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cpy_in_4_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "cpy_in_5_out", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 34
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ start_full_n sc_in sc_logic 1 signal -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ start_out sc_out sc_logic 1 signal -1 } 
	{ start_write sc_out sc_logic 1 signal -1 } 
	{ in_r_address0 sc_out sc_lv 3 signal 0 } 
	{ in_r_ce0 sc_out sc_logic 1 signal 0 } 
	{ in_r_q0 sc_in sc_lv 32 signal 0 } 
	{ in_r_address1 sc_out sc_lv 3 signal 0 } 
	{ in_r_ce1 sc_out sc_logic 1 signal 0 } 
	{ in_r_q1 sc_in sc_lv 32 signal 0 } 
	{ cpy_in_0_out_din sc_out sc_lv 32 signal 1 } 
	{ cpy_in_0_out_full_n sc_in sc_logic 1 signal 1 } 
	{ cpy_in_0_out_write sc_out sc_logic 1 signal 1 } 
	{ cpy_in_1_out_din sc_out sc_lv 32 signal 2 } 
	{ cpy_in_1_out_full_n sc_in sc_logic 1 signal 2 } 
	{ cpy_in_1_out_write sc_out sc_logic 1 signal 2 } 
	{ cpy_in_2_out_din sc_out sc_lv 32 signal 3 } 
	{ cpy_in_2_out_full_n sc_in sc_logic 1 signal 3 } 
	{ cpy_in_2_out_write sc_out sc_logic 1 signal 3 } 
	{ cpy_in_3_out_din sc_out sc_lv 32 signal 4 } 
	{ cpy_in_3_out_full_n sc_in sc_logic 1 signal 4 } 
	{ cpy_in_3_out_write sc_out sc_logic 1 signal 4 } 
	{ cpy_in_4_out_din sc_out sc_lv 32 signal 5 } 
	{ cpy_in_4_out_full_n sc_in sc_logic 1 signal 5 } 
	{ cpy_in_4_out_write sc_out sc_logic 1 signal 5 } 
	{ cpy_in_5_out_din sc_out sc_lv 32 signal 6 } 
	{ cpy_in_5_out_full_n sc_in sc_logic 1 signal 6 } 
	{ cpy_in_5_out_write sc_out sc_logic 1 signal 6 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "start_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_full_n", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "start_out", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out", "role": "default" }} , 
 	{ "name": "start_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_write", "role": "default" }} , 
 	{ "name": "in_r_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "in_r", "role": "address0" }} , 
 	{ "name": "in_r_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "ce0" }} , 
 	{ "name": "in_r_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "q0" }} , 
 	{ "name": "in_r_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "in_r", "role": "address1" }} , 
 	{ "name": "in_r_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "ce1" }} , 
 	{ "name": "in_r_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "q1" }} , 
 	{ "name": "cpy_in_0_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_0_out", "role": "din" }} , 
 	{ "name": "cpy_in_0_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_0_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_0_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_0_out", "role": "write" }} , 
 	{ "name": "cpy_in_1_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_1_out", "role": "din" }} , 
 	{ "name": "cpy_in_1_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_1_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_1_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_1_out", "role": "write" }} , 
 	{ "name": "cpy_in_2_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_2_out", "role": "din" }} , 
 	{ "name": "cpy_in_2_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_2_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_2_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_2_out", "role": "write" }} , 
 	{ "name": "cpy_in_3_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_3_out", "role": "din" }} , 
 	{ "name": "cpy_in_3_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_3_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_3_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_3_out", "role": "write" }} , 
 	{ "name": "cpy_in_4_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_4_out", "role": "din" }} , 
 	{ "name": "cpy_in_4_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_4_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_4_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_4_out", "role": "write" }} , 
 	{ "name": "cpy_in_5_out_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cpy_in_5_out", "role": "din" }} , 
 	{ "name": "cpy_in_5_out_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_5_out", "role": "full_n" }} , 
 	{ "name": "cpy_in_5_out_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "cpy_in_5_out", "role": "write" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
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
			{"Name" : "cpy_in_0_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_0_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_1_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_1_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_2_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_2_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_3_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_3_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_4_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_4_out_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "cpy_in_5_out", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0", "DependentChanDepth" : "2",
				"BlockSignal" : [
					{"Name" : "cpy_in_5_out_blk_n", "Type" : "RtlSignal"}]}]}]}


set ArgLastReadFirstWriteLatency {
	Block_split13_proc {
		in_r {Type I LastRead 3 FirstWrite -1}
		cpy_in_0_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_1_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_2_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_3_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_4_out {Type O LastRead -1 FirstWrite 3}
		cpy_in_5_out {Type O LastRead -1 FirstWrite 3}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "3", "Max" : "3"}
	, {"Name" : "Interval", "Min" : "3", "Max" : "3"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	in_r { ap_memory {  { in_r_address0 mem_address 1 3 }  { in_r_ce0 mem_ce 1 1 }  { in_r_q0 mem_dout 0 32 }  { in_r_address1 MemPortADDR2 1 3 }  { in_r_ce1 MemPortCE2 1 1 }  { in_r_q1 MemPortDOUT2 0 32 } } }
	cpy_in_0_out { ap_fifo {  { cpy_in_0_out_din fifo_data 1 32 }  { cpy_in_0_out_full_n fifo_status 0 1 }  { cpy_in_0_out_write fifo_update 1 1 } } }
	cpy_in_1_out { ap_fifo {  { cpy_in_1_out_din fifo_data 1 32 }  { cpy_in_1_out_full_n fifo_status 0 1 }  { cpy_in_1_out_write fifo_update 1 1 } } }
	cpy_in_2_out { ap_fifo {  { cpy_in_2_out_din fifo_data 1 32 }  { cpy_in_2_out_full_n fifo_status 0 1 }  { cpy_in_2_out_write fifo_update 1 1 } } }
	cpy_in_3_out { ap_fifo {  { cpy_in_3_out_din fifo_data 1 32 }  { cpy_in_3_out_full_n fifo_status 0 1 }  { cpy_in_3_out_write fifo_update 1 1 } } }
	cpy_in_4_out { ap_fifo {  { cpy_in_4_out_din fifo_data 1 32 }  { cpy_in_4_out_full_n fifo_status 0 1 }  { cpy_in_4_out_write fifo_update 1 1 } } }
	cpy_in_5_out { ap_fifo {  { cpy_in_5_out_din fifo_data 1 32 }  { cpy_in_5_out_full_n fifo_status 0 1 }  { cpy_in_5_out_write fifo_update 1 1 } } }
}
