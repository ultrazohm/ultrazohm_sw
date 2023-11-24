# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
A_rows { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
A { 
	dir I
	width 32
	depth 5
	mode ap_memory
	offset 32
	offset_end 63
	core_op ram_1p
	core_impl auto
	core_latency 1
	byte_write 0
}
C_out { 
	dir IO
	width 32
	depth 5
	mode ap_memory
	offset 64
	offset_end 95
	core_op ram_1p
	core_impl auto
	core_latency 1
	byte_write 0
}
B_rows { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 96
	offset_end 107
}
B_columns { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 108
	offset_end 119
}
B { 
	dir I
	width 32
	depth 25
	mode ap_memory
	offset 128
	offset_end 255
	core_op ram_1p
	core_impl auto
	core_latency 1
	byte_write 0
}
ap_start { }
ap_done { }
ap_ready { }
ap_continue { }
ap_idle { }
interrupt {
}
}
dict set axilite_register_dict control $port_control


