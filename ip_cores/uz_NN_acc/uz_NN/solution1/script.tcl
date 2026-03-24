############################################################
## This file is generated automatically by Vitis HLS.
############################################################

# -----------------------------
# USER-CONFIGURABLE PARAMETERS
# -----------------------------
set ip_name "uz_NN_2_64"
set ip_version "1.0"
set ip_description "2x64_setup"
set ip_display_name "uz_NN_2_64_acc"
set solution_name "solution1"

# -----------------------------
# PROJECT SETUP
# -----------------------------
open_project uz_NN
set_top uz_NN_acc

add_files uz_NN/uz_layers.h
add_files uz_NN/uz_layers.cpp
add_files uz_NN/uz_dense_relu.h
add_files uz_NN/uz_dense_relu.cpp
add_files uz_NN/uz_dense.h
add_files uz_NN/uz_dense.cpp
add_files uz_NN/uz_copy_L_Output_Weights.h
add_files uz_NN/uz_copy_L_Output_Weights.cpp
add_files uz_NN/uz_NN_acc.h
add_files uz_NN/uz_NN_acc.cpp
add_files uz_NN/uz_MMult_MaxSize.h

add_files -tb uz_NN/tb_uz_NN_acc.cpp \
-cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" \
-csimflags "-Wno-unknown-pragmas"

open_solution $solution_name -flow_target vitis
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 10 -name default

config_interface -m_axi_addr64=0 -m_axi_alignment_byte_size 32 -m_axi_latency 64 -m_axi_max_bitwidth 32 -m_axi_max_widen_bitwidth 32
config_rtl -register_reset_num 3
config_array_partition -complete_threshold 2
config_compile -no_signed_zeros -unsafe_math_optimizations

# -----------------------------
# EXPORT CONFIG (uses variables)
# -----------------------------
config_export -format ip_catalog \
    -rtl verilog \
    -version $ip_version \
    -description $ip_description \
    -display_name $ip_display_name \
    -ipname $ip_name

source "./uz_NN/$solution_name/directives.tcl"

csynth_design
export_design -format ip_catalog

# ---------------------------------------------------------
# AUTOMATIC ZIP DETECTION + EXTRACTION (OS-independent)
# ---------------------------------------------------------

# Construct expected zip path
set proj_dir [pwd]
set zipfile [file normalize "$proj_dir/uz_NN/$solution_name/impl/export.zip"]
puts "Looking for ZIP at: $zipfile"

# Fallback: auto-detect if naming differs
if {![file exists $zipfile]} {
    puts "ZIP not found at expected location. Searching..."
    set zip_candidates [glob -nocomplain "$solution_name/impl/*.zip"]

    if {[llength $zip_candidates] == 0} {
        error "No ZIP file found in $solution_name/impl/"
    }

    # Take first match
    set zipfile [lindex $zip_candidates 0]
}

puts "Using ZIP file: $zipfile"

# Output directory
set outdir "$proj_dir/uz_NN/$solution_name/$ip_name"
file mkdir $outdir

# ----------------------------------------
# OS detection
# ----------------------------------------
set os $tcl_platform(os)
puts "Detected OS: $os"

# ----------------------------------------
# Extract ZIP (OS-specific)
# ----------------------------------------
if {$os eq "Windows NT"} {
    puts "Using PowerShell to extract ZIP..."
    exec powershell -command "Expand-Archive -Path '$zipfile' -DestinationPath '$outdir' -Force"
} else {
    puts "Using unzip to extract ZIP..."
    exec unzip -o "$zipfile" -d "$outdir"
}

puts "IP successfully extracted to $outdir"

#Delete folders so no duplicate IP-core is visible in vivado
file delete -force "$proj_dir/uz_NN/$solution_name/impl" 
file delete -force "$proj_dir/uz_NN/$solution_name/syn"