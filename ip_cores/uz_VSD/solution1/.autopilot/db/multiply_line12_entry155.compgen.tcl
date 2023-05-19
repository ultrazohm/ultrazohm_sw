# This script segment is generated automatically by AutoPilot

# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 97 \
    name scalar_val_5 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_5 \
    op interface \
    ports { scalar_val_5_dout { I 32 vector } scalar_val_5_empty_n { I 1 bit } scalar_val_5_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 98 \
    name scalar_val_4 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_4 \
    op interface \
    ports { scalar_val_4_dout { I 32 vector } scalar_val_4_empty_n { I 1 bit } scalar_val_4_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 99 \
    name scalar_val_3 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_3 \
    op interface \
    ports { scalar_val_3_dout { I 32 vector } scalar_val_3_empty_n { I 1 bit } scalar_val_3_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 100 \
    name scalar_val_2 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_2 \
    op interface \
    ports { scalar_val_2_dout { I 32 vector } scalar_val_2_empty_n { I 1 bit } scalar_val_2_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 101 \
    name scalar_val_1 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_1 \
    op interface \
    ports { scalar_val_1_dout { I 32 vector } scalar_val_1_empty_n { I 1 bit } scalar_val_1_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 102 \
    name scalar_val_0 \
    type fifo \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_0 \
    op interface \
    ports { scalar_val_0_dout { I 32 vector } scalar_val_0_empty_n { I 1 bit } scalar_val_0_read { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 103 \
    name scalar_val_5_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_5_out \
    op interface \
    ports { scalar_val_5_out_din { O 32 vector } scalar_val_5_out_full_n { I 1 bit } scalar_val_5_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 104 \
    name scalar_val_4_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_4_out \
    op interface \
    ports { scalar_val_4_out_din { O 32 vector } scalar_val_4_out_full_n { I 1 bit } scalar_val_4_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 105 \
    name scalar_val_3_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_3_out \
    op interface \
    ports { scalar_val_3_out_din { O 32 vector } scalar_val_3_out_full_n { I 1 bit } scalar_val_3_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 106 \
    name scalar_val_2_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_2_out \
    op interface \
    ports { scalar_val_2_out_din { O 32 vector } scalar_val_2_out_full_n { I 1 bit } scalar_val_2_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 107 \
    name scalar_val_1_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_1_out \
    op interface \
    ports { scalar_val_1_out_din { O 32 vector } scalar_val_1_out_full_n { I 1 bit } scalar_val_1_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 108 \
    name scalar_val_0_out \
    type fifo \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_scalar_val_0_out \
    op interface \
    ports { scalar_val_0_out_din { O 32 vector } scalar_val_0_out_full_n { I 1 bit } scalar_val_0_out_write { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_done { O 1 bit } ap_idle { O 1 bit } ap_continue { I 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


