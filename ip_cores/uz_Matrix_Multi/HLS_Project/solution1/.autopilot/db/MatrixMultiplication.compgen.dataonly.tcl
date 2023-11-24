# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
A_input { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
B_input { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
C_output { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
A_rows { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 52
	offset_end 63
}
B_rows { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 64
	offset_end 75
}
B_columns { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 76
	offset_end 87
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


