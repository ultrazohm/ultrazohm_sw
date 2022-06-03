# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_Din {
Controller_id { 
	dir I
	width 160
	depth 1
	mode ap_none
	offset 16
	offset_end 39
}
Controller_iq { 
	dir I
	width 160
	depth 1
	mode ap_none
	offset 40
	offset_end 63
}
self_i { 
	dir I
	width 288
	depth 1
	mode ap_none
	offset 64
	offset_end 103
}
self_o { 
	dir O
	width 288
	depth 1
	mode ap_vld
	offset 104
	offset_end 143
}
i_actual_Ampere { 
	dir I
	width 96
	depth 1
	mode ap_none
	offset 144
	offset_end 159
}
V_dc_volts { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 160
	offset_end 167
}
omega_el_rad_per_sec { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 168
	offset_end 175
}
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
i_reference_Ampere { 
	dir I
	width 96
	depth 1
	mode ap_none
	offset 176
	offset_end 191
}
}
dict set axilite_register_dict Din $port_Din


set port_control {
output_volts_d { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
output_volts_q { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
}
dict set axilite_register_dict control $port_control


