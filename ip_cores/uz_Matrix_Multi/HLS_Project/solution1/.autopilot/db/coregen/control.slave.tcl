dict set slaves control {ports {A_rows {type i_ap_none width 64} A {type i_ap_memory width 32} C_out {type io_ap_memory width 32} B_rows {type i_ap_none width 64} B_columns {type i_ap_none width 64} B {type i_ap_memory width 32} ap_start {type ap_ctrl width 1} ap_done {type ap_ctrl width 1} ap_ready {type ap_ctrl width 1} ap_continue {type ap_ctrl width 1} ap_idle {type ap_ctrl width 1}} mems {A {width 32} C_out {width 32} B {width 32}} has_ctrl 1}
set datawidth 32
set addrwidth 64
set intr_clr_mode TOW
