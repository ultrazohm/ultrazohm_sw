set moduleName uz_FOC_sample
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {uz_FOC_sample}
set C_modelType { void 0 }
set C_modelArgList {
	{ Dout int 32 regular {axi_master 1}  }
	{ self int 256 regular {axi_slave 2}  }
	{ Controller_id int 160 regular {axi_slave 0}  }
	{ Controller_iq int 160 regular {axi_slave 0}  }
	{ i_reference_Ampere int 96 regular {axi_slave 0}  }
	{ i_actual_Ampere int 96 regular {axi_slave 0}  }
	{ V_dc_volts float 32 regular {axi_slave 0}  }
	{ omega_el_rad_per_sec float 32 regular {axi_slave 0}  }
	{ output_volts_d int 64 regular {axi_slave 0}  }
	{ output_volts_q int 64 regular {axi_slave 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "Dout", "interface" : "axi_master", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "output_volts_d","cData": "int","bit_use": { "low": 0,"up": 31},"offset": { "type": "dynamic","port_name": "output_volts_d","bundle": "control"},"direction": "WRITEONLY","cArray": [{"low" : 0,"up" : 49,"step" : 1}]},{"cName": "output_volts_q","cData": "int","bit_use": { "low": 0,"up": 31},"offset": { "type": "dynamic","port_name": "output_volts_q","bundle": "control"},"direction": "WRITEONLY","cArray": [{"low" : 0,"up" : 49,"step" : 1}]}]}]} , 
 	{ "Name" : "self", "interface" : "axi_slave", "bundle":"Din","type":"ap_ovld","bitwidth" : 256, "direction" : "READWRITE", "bitSlice":[{"low":0,"up":255,"cElement": [{"cName": "self","cData": "int256","bit_use": { "low": 0,"up": 255},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}], "offset" : {"in":32, "out":68}, "offset_end" : {"in":67, "out":103}} , 
 	{ "Name" : "Controller_id", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 160, "direction" : "READONLY", "bitSlice":[{"low":0,"up":159,"cElement": [{"cName": "Controller_id","cData": "int160","bit_use": { "low": 0,"up": 159},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}], "offset" : {"in":144}, "offset_end" : {"in":167}} , 
 	{ "Name" : "Controller_iq", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 160, "direction" : "READONLY", "bitSlice":[{"low":0,"up":159,"cElement": [{"cName": "Controller_iq","cData": "int160","bit_use": { "low": 0,"up": 159},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}], "offset" : {"in":168}, "offset_end" : {"in":191}} , 
 	{ "Name" : "i_reference_Ampere", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 96, "direction" : "READONLY", "bitSlice":[{"low":0,"up":95,"cElement": [{"cName": "i_reference_Ampere","cData": "int96","bit_use": { "low": 0,"up": 95},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":16}, "offset_end" : {"in":31}} , 
 	{ "Name" : "i_actual_Ampere", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 96, "direction" : "READONLY", "bitSlice":[{"low":0,"up":95,"cElement": [{"cName": "i_actual_Ampere","cData": "int96","bit_use": { "low": 0,"up": 95},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":112}, "offset_end" : {"in":127}} , 
 	{ "Name" : "V_dc_volts", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "V_dc_volts","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":128}, "offset_end" : {"in":135}} , 
 	{ "Name" : "omega_el_rad_per_sec", "interface" : "axi_slave", "bundle":"Din","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "omega_el_rad_per_sec","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}], "offset" : {"in":136}, "offset_end" : {"in":143}} , 
 	{ "Name" : "output_volts_d", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "output_volts_q", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} ]}
# RTL Port declarations: 
set portNum 82
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ m_axi_Dout_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_Dout_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_AWLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_Dout_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_Dout_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_Dout_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_Dout_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_Dout_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_WDATA sc_out sc_lv 32 signal 0 } 
	{ m_axi_Dout_WSTRB sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_Dout_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_ARLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_Dout_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_Dout_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_Dout_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_Dout_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_Dout_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_Dout_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_Dout_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_RDATA sc_in sc_lv 32 signal 0 } 
	{ m_axi_Dout_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_Dout_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_Dout_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_Dout_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_Dout_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_Dout_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_Dout_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_Dout_BUSER sc_in sc_lv 1 signal 0 } 
	{ s_axi_Din_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_Din_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_Din_AWADDR sc_in sc_lv 8 signal -1 } 
	{ s_axi_Din_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_Din_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_Din_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_Din_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_Din_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_Din_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_Din_ARADDR sc_in sc_lv 8 signal -1 } 
	{ s_axi_Din_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_Din_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_Din_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_Din_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_Din_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_Din_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_Din_BRESP sc_out sc_lv 2 signal -1 } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_Din_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "Din", "role": "AWADDR" },"address":[{"name":"uz_FOC_sample","role":"start","value":"0","valid_bit":"0"},{"name":"uz_FOC_sample","role":"continue","value":"0","valid_bit":"4"},{"name":"uz_FOC_sample","role":"auto_start","value":"0","valid_bit":"7"},{"name":"i_reference_Ampere","role":"data","value":"16"},{"name":"self","role":"data","value":"32"},{"name":"i_actual_Ampere","role":"data","value":"112"},{"name":"V_dc_volts","role":"data","value":"128"},{"name":"omega_el_rad_per_sec","role":"data","value":"136"},{"name":"Controller_id","role":"data","value":"144"},{"name":"Controller_iq","role":"data","value":"168"}] },
	{ "name": "s_axi_Din_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "AWVALID" } },
	{ "name": "s_axi_Din_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "AWREADY" } },
	{ "name": "s_axi_Din_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "WVALID" } },
	{ "name": "s_axi_Din_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "WREADY" } },
	{ "name": "s_axi_Din_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Din", "role": "WDATA" } },
	{ "name": "s_axi_Din_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Din", "role": "WSTRB" } },
	{ "name": "s_axi_Din_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "Din", "role": "ARADDR" },"address":[{"name":"uz_FOC_sample","role":"start","value":"0","valid_bit":"0"},{"name":"uz_FOC_sample","role":"done","value":"0","valid_bit":"1"},{"name":"uz_FOC_sample","role":"idle","value":"0","valid_bit":"2"},{"name":"uz_FOC_sample","role":"ready","value":"0","valid_bit":"3"},{"name":"uz_FOC_sample","role":"auto_start","value":"0","valid_bit":"7"},{"name":"self","role":"data","value":"68"}, {"name":"self","role":"valid","value":"100","valid_bit":"0"}] },
	{ "name": "s_axi_Din_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "ARVALID" } },
	{ "name": "s_axi_Din_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "ARREADY" } },
	{ "name": "s_axi_Din_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "RVALID" } },
	{ "name": "s_axi_Din_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "RREADY" } },
	{ "name": "s_axi_Din_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Din", "role": "RDATA" } },
	{ "name": "s_axi_Din_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Din", "role": "RRESP" } },
	{ "name": "s_axi_Din_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "BVALID" } },
	{ "name": "s_axi_Din_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "BREADY" } },
	{ "name": "s_axi_Din_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Din", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Din", "role": "interrupt" } },
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"output_volts_d","role":"data","value":"16"},{"name":"output_volts_q","role":"data","value":"28"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "m_axi_Dout_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "AWVALID" }} , 
 	{ "name": "m_axi_Dout_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "AWREADY" }} , 
 	{ "name": "m_axi_Dout_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "Dout", "role": "AWADDR" }} , 
 	{ "name": "m_axi_Dout_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "AWID" }} , 
 	{ "name": "m_axi_Dout_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "Dout", "role": "AWLEN" }} , 
 	{ "name": "m_axi_Dout_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "Dout", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_Dout_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "AWBURST" }} , 
 	{ "name": "m_axi_Dout_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_Dout_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_Dout_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "Dout", "role": "AWPROT" }} , 
 	{ "name": "m_axi_Dout_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "AWQOS" }} , 
 	{ "name": "m_axi_Dout_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "AWREGION" }} , 
 	{ "name": "m_axi_Dout_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "AWUSER" }} , 
 	{ "name": "m_axi_Dout_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "WVALID" }} , 
 	{ "name": "m_axi_Dout_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "WREADY" }} , 
 	{ "name": "m_axi_Dout_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Dout", "role": "WDATA" }} , 
 	{ "name": "m_axi_Dout_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "WSTRB" }} , 
 	{ "name": "m_axi_Dout_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "WLAST" }} , 
 	{ "name": "m_axi_Dout_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "WID" }} , 
 	{ "name": "m_axi_Dout_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "WUSER" }} , 
 	{ "name": "m_axi_Dout_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "ARVALID" }} , 
 	{ "name": "m_axi_Dout_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "ARREADY" }} , 
 	{ "name": "m_axi_Dout_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "Dout", "role": "ARADDR" }} , 
 	{ "name": "m_axi_Dout_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "ARID" }} , 
 	{ "name": "m_axi_Dout_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "Dout", "role": "ARLEN" }} , 
 	{ "name": "m_axi_Dout_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "Dout", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_Dout_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "ARBURST" }} , 
 	{ "name": "m_axi_Dout_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_Dout_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_Dout_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "Dout", "role": "ARPROT" }} , 
 	{ "name": "m_axi_Dout_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "ARQOS" }} , 
 	{ "name": "m_axi_Dout_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "Dout", "role": "ARREGION" }} , 
 	{ "name": "m_axi_Dout_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "ARUSER" }} , 
 	{ "name": "m_axi_Dout_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "RVALID" }} , 
 	{ "name": "m_axi_Dout_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "RREADY" }} , 
 	{ "name": "m_axi_Dout_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Dout", "role": "RDATA" }} , 
 	{ "name": "m_axi_Dout_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "RLAST" }} , 
 	{ "name": "m_axi_Dout_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "RID" }} , 
 	{ "name": "m_axi_Dout_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "RUSER" }} , 
 	{ "name": "m_axi_Dout_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "RRESP" }} , 
 	{ "name": "m_axi_Dout_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "BVALID" }} , 
 	{ "name": "m_axi_Dout_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "BREADY" }} , 
 	{ "name": "m_axi_Dout_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "Dout", "role": "BRESP" }} , 
 	{ "name": "m_axi_Dout_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "BID" }} , 
 	{ "name": "m_axi_Dout_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "Dout", "role": "BUSER" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62"],
		"CDFG" : "uz_FOC_sample",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "58", "EstimateLatencyMax" : "97",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state22", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265"}],
		"Port" : [
			{"Name" : "Dout", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "Dout_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "Dout_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "Dout_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "self", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "Controller_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "Controller_iq", "Type" : "None", "Direction" : "I"},
			{"Name" : "i_reference_Ampere", "Type" : "None", "Direction" : "I"},
			{"Name" : "i_actual_Ampere", "Type" : "None", "Direction" : "I"},
			{"Name" : "V_dc_volts", "Type" : "None", "Direction" : "I"},
			{"Name" : "omega_el_rad_per_sec", "Type" : "None", "Direction" : "I"},
			{"Name" : "output_volts_d", "Type" : "None", "Direction" : "I"},
			{"Name" : "output_volts_q", "Type" : "None", "Direction" : "I"},
			{"Name" : "I_sum_d", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "I_sum_q", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Port" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Din_s_axi_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Dout_m_axi_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265", "Parent" : "0", "Child" : ["5", "22", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48"],
		"CDFG" : "uz_FOC_SpaceVector_Limitation_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "30", "EstimateLatencyMax" : "69",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "p_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "u_input_Volts_0", "Type" : "None", "Direction" : "I"},
			{"Name" : "u_input_Volts_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "V_dc_volts", "Type" : "None", "Direction" : "I"},
			{"Name" : "omega_el_rad_per_sec", "Type" : "None", "Direction" : "I"},
			{"Name" : "i_actual_Ampere_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V"}]},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "5", "SubInstance" : "grp_pow_generic_float_s_fu_153", "Port" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V"},
					{"ID" : "22", "SubInstance" : "grp_pow_generic_float_s_fu_173", "Port" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V"}]}]},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153", "Parent" : "4", "Child" : ["6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"],
		"CDFG" : "pow_generic_float_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "15", "EstimateLatencyMin" : "15", "EstimateLatencyMax" : "15",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "base_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "6", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V_U", "Parent" : "5"},
	{"ID" : "7", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V_U", "Parent" : "5"},
	{"ID" : "8", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V_U", "Parent" : "5"},
	{"ID" : "9", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V_U", "Parent" : "5"},
	{"ID" : "10", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V_U", "Parent" : "5"},
	{"ID" : "11", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V_U", "Parent" : "5"},
	{"ID" : "12", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V_U", "Parent" : "5"},
	{"ID" : "13", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_4ns_39ns_43_1_1_U1", "Parent" : "5"},
	{"ID" : "14", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_6ns_41ns_47_1_1_U2", "Parent" : "5"},
	{"ID" : "15", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_6ns_44ns_50_1_1_U3", "Parent" : "5"},
	{"ID" : "16", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_9s_45ns_52_1_1_U4", "Parent" : "5"},
	{"ID" : "17", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_23ns_23ns_46_1_1_U5", "Parent" : "5"},
	{"ID" : "18", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_10s_36s_36_1_1_U6", "Parent" : "5"},
	{"ID" : "19", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_mul_6ns_25s_25_4_1_U7", "Parent" : "5"},
	{"ID" : "20", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mac_muladd_13s_13ns_16s_25_4_1_U8", "Parent" : "5"},
	{"ID" : "21", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_153.mul_mul_18ns_18ns_36_4_1_U9", "Parent" : "5"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173", "Parent" : "4", "Child" : ["23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38"],
		"CDFG" : "pow_generic_float_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "15", "EstimateLatencyMin" : "15", "EstimateLatencyMax" : "15",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "base_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "23", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V_U", "Parent" : "22"},
	{"ID" : "24", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V_U", "Parent" : "22"},
	{"ID" : "25", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V_U", "Parent" : "22"},
	{"ID" : "26", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V_U", "Parent" : "22"},
	{"ID" : "27", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V_U", "Parent" : "22"},
	{"ID" : "28", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V_U", "Parent" : "22"},
	{"ID" : "29", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V_U", "Parent" : "22"},
	{"ID" : "30", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_4ns_39ns_43_1_1_U1", "Parent" : "22"},
	{"ID" : "31", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_6ns_41ns_47_1_1_U2", "Parent" : "22"},
	{"ID" : "32", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_6ns_44ns_50_1_1_U3", "Parent" : "22"},
	{"ID" : "33", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_9s_45ns_52_1_1_U4", "Parent" : "22"},
	{"ID" : "34", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_23ns_23ns_46_1_1_U5", "Parent" : "22"},
	{"ID" : "35", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_10s_36s_36_1_1_U6", "Parent" : "22"},
	{"ID" : "36", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_mul_6ns_25s_25_4_1_U7", "Parent" : "22"},
	{"ID" : "37", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mac_muladd_13s_13ns_16s_25_4_1_U8", "Parent" : "22"},
	{"ID" : "38", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.grp_pow_generic_float_s_fu_173.mul_mul_18ns_18ns_36_4_1_U9", "Parent" : "22"},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.faddfsub_32ns_32ns_32_4_full_dsp_1_U27", "Parent" : "4"},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fmul_32ns_32ns_32_3_max_dsp_1_U28", "Parent" : "4"},
	{"ID" : "41", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fdiv_32ns_32ns_32_9_no_dsp_1_U29", "Parent" : "4"},
	{"ID" : "42", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U30", "Parent" : "4"},
	{"ID" : "43", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U31", "Parent" : "4"},
	{"ID" : "44", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U32", "Parent" : "4"},
	{"ID" : "45", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U33", "Parent" : "4"},
	{"ID" : "46", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U34", "Parent" : "4"},
	{"ID" : "47", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fcmp_32ns_32ns_1_2_no_dsp_1_U35", "Parent" : "4"},
	{"ID" : "48", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_uz_FOC_SpaceVector_Limitation_1_fu_265.fsqrt_32ns_32ns_32_8_no_dsp_1_U36", "Parent" : "4"},
	{"ID" : "49", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.faddfsub_32ns_32ns_32_4_full_dsp_1_U48", "Parent" : "0"},
	{"ID" : "50", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.faddfsub_32ns_32ns_32_4_full_dsp_1_U49", "Parent" : "0"},
	{"ID" : "51", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U50", "Parent" : "0"},
	{"ID" : "52", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U51", "Parent" : "0"},
	{"ID" : "53", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U52", "Parent" : "0"},
	{"ID" : "54", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_3_max_dsp_1_U53", "Parent" : "0"},
	{"ID" : "55", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U54", "Parent" : "0"},
	{"ID" : "56", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U55", "Parent" : "0"},
	{"ID" : "57", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U56", "Parent" : "0"},
	{"ID" : "58", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U57", "Parent" : "0"},
	{"ID" : "59", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U58", "Parent" : "0"},
	{"ID" : "60", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U59", "Parent" : "0"},
	{"ID" : "61", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U60", "Parent" : "0"},
	{"ID" : "62", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fcmp_32ns_32ns_1_2_no_dsp_1_U61", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	uz_FOC_sample {
		Dout {Type O LastRead 24 FirstWrite 22}
		self {Type IO LastRead 0 FirstWrite 22}
		Controller_id {Type I LastRead 0 FirstWrite -1}
		Controller_iq {Type I LastRead 0 FirstWrite -1}
		i_reference_Ampere {Type I LastRead 0 FirstWrite -1}
		i_actual_Ampere {Type I LastRead 0 FirstWrite -1}
		V_dc_volts {Type I LastRead 0 FirstWrite -1}
		omega_el_rad_per_sec {Type I LastRead 0 FirstWrite -1}
		output_volts_d {Type I LastRead 0 FirstWrite -1}
		output_volts_q {Type I LastRead 0 FirstWrite -1}
		I_sum_d {Type IO LastRead -1 FirstWrite -1}
		I_sum_q {Type IO LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}}
	uz_FOC_SpaceVector_Limitation_1 {
		p_read {Type I LastRead 29 FirstWrite -1}
		u_input_Volts_0 {Type I LastRead 0 FirstWrite -1}
		u_input_Volts_1 {Type I LastRead 0 FirstWrite -1}
		V_dc_volts {Type I LastRead 19 FirstWrite -1}
		omega_el_rad_per_sec {Type I LastRead 27 FirstWrite -1}
		i_actual_Ampere_1 {Type I LastRead 27 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}}
	pow_generic_float_s {
		base_r {Type I LastRead 0 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}}
	pow_generic_float_s {
		base_r {Type I LastRead 0 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_float_0_5_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_4_4_16_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_7_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_9_ap_q_mode_5_ap_o_mode_3_0_12_6_64_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_1_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_ap_q_mode_5_ap_o_mode_3_0_array_V {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "58", "Max" : "97"}
	, {"Name" : "Interval", "Min" : "59", "Max" : "98"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	Dout { m_axi {  { m_axi_Dout_AWVALID VALID 1 1 }  { m_axi_Dout_AWREADY READY 0 1 }  { m_axi_Dout_AWADDR ADDR 1 64 }  { m_axi_Dout_AWID ID 1 1 }  { m_axi_Dout_AWLEN LEN 1 8 }  { m_axi_Dout_AWSIZE SIZE 1 3 }  { m_axi_Dout_AWBURST BURST 1 2 }  { m_axi_Dout_AWLOCK LOCK 1 2 }  { m_axi_Dout_AWCACHE CACHE 1 4 }  { m_axi_Dout_AWPROT PROT 1 3 }  { m_axi_Dout_AWQOS QOS 1 4 }  { m_axi_Dout_AWREGION REGION 1 4 }  { m_axi_Dout_AWUSER USER 1 1 }  { m_axi_Dout_WVALID VALID 1 1 }  { m_axi_Dout_WREADY READY 0 1 }  { m_axi_Dout_WDATA DATA 1 32 }  { m_axi_Dout_WSTRB STRB 1 4 }  { m_axi_Dout_WLAST LAST 1 1 }  { m_axi_Dout_WID ID 1 1 }  { m_axi_Dout_WUSER USER 1 1 }  { m_axi_Dout_ARVALID VALID 1 1 }  { m_axi_Dout_ARREADY READY 0 1 }  { m_axi_Dout_ARADDR ADDR 1 64 }  { m_axi_Dout_ARID ID 1 1 }  { m_axi_Dout_ARLEN LEN 1 8 }  { m_axi_Dout_ARSIZE SIZE 1 3 }  { m_axi_Dout_ARBURST BURST 1 2 }  { m_axi_Dout_ARLOCK LOCK 1 2 }  { m_axi_Dout_ARCACHE CACHE 1 4 }  { m_axi_Dout_ARPROT PROT 1 3 }  { m_axi_Dout_ARQOS QOS 1 4 }  { m_axi_Dout_ARREGION REGION 1 4 }  { m_axi_Dout_ARUSER USER 1 1 }  { m_axi_Dout_RVALID VALID 0 1 }  { m_axi_Dout_RREADY READY 1 1 }  { m_axi_Dout_RDATA DATA 0 32 }  { m_axi_Dout_RLAST LAST 0 1 }  { m_axi_Dout_RID ID 0 1 }  { m_axi_Dout_RUSER USER 0 1 }  { m_axi_Dout_RRESP RESP 0 2 }  { m_axi_Dout_BVALID VALID 0 1 }  { m_axi_Dout_BREADY READY 1 1 }  { m_axi_Dout_BRESP RESP 0 2 }  { m_axi_Dout_BID ID 0 1 }  { m_axi_Dout_BUSER USER 0 1 } } }
}

set busDeadlockParameterList { 
	{ Dout { NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 } } \
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ Dout 1 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ Dout 1 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
