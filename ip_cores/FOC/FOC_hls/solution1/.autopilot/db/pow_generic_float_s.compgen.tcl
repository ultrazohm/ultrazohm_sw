# This script segment is generated automatically by AutoPilot

set id 1
set name uz_FOC_sample_mul_4ns_39ns_43_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 4
set in0_signed 0
set in1_width 39
set in1_signed 0
set out_width 43
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 2
set name uz_FOC_sample_mul_6ns_41ns_47_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 6
set in0_signed 0
set in1_width 41
set in1_signed 0
set out_width 47
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 3
set name uz_FOC_sample_mul_6ns_44ns_50_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 6
set in0_signed 0
set in1_width 44
set in1_signed 0
set out_width 50
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 4
set name uz_FOC_sample_mul_9s_45ns_52_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 9
set in0_signed 1
set in1_width 45
set in1_signed 0
set out_width 52
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 5
set name uz_FOC_sample_mul_23ns_23ns_46_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 23
set in0_signed 0
set in1_width 23
set in1_signed 0
set out_width 46
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 6
set name uz_FOC_sample_mul_10s_36s_36_1_1
set corename simcore_mul
set op mul
set stage_num 1
set max_latency -1
set registered_input 1
set in0_width 10
set in0_signed 1
set in1_width 36
set in1_signed 1
set out_width 36
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename Multiplier
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul] == "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul"} {
eval "::AESL_LIB_VIRTEX::xil_gen_multicycle_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    out_width ${out_width} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_multicycle_mul, check your platform lib"
}
}


set id 7
set name uz_FOC_sample_mul_mul_6ns_25s_25_4_1
set corename simcore_mul
set op mul
set stage_num 4
set max_latency -1
set registered_input 1
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 6
set in0_signed 0
set in1_width 25
set in1_signed 1
set ce_width 1
set ce_signed 0
set out_width 25
set exp i0*i1
set arg_lists {i0 {6 0 +} i1 {25 1 +} p {25 1 +} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


set id 8
set name uz_FOC_sample_mac_muladd_13s_13ns_16s_25_4_1
set corename simcore_mac
set op mac
set stage_num 4
set max_latency -1
set registered_input 1
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 13
set in0_signed 1
set in1_width 13
set in1_signed 0
set in2_width 16
set in2_signed 1
set ce_width 1
set ce_signed 0
set out_width 25
set exp i0*i1+i2
set arg_lists {i0 {13 1 +} i1 {13 0 +} m {25 1 +} i2 {16 1 +} p {25 1 +} c_reg {1} rnd {0} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mac] == "ap_gen_simcore_mac"} {
eval "ap_gen_simcore_mac { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    in2_width ${in2_width} \
    in2_signed ${in2_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mac, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mac
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    in2_width ${in2_width} \
    in2_signed ${in2_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


set id 9
set name uz_FOC_sample_mul_mul_18ns_18ns_36_4_1
set corename simcore_mul
set op mul
set stage_num 4
set max_latency -1
set registered_input 1
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 18
set in0_signed 0
set in1_width 18
set in1_signed 0
set ce_width 1
set ce_signed 0
set out_width 36
set exp i0*i1
set arg_lists {i0 {18 0 +} i1 {18 0 +} p {36 0 +} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mul] == "ap_gen_simcore_mul"} {
eval "ap_gen_simcore_mul { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-100\] Cannot find ap_gen_simcore_mul, check your AutoPilot builtin lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler ${name}
}


set op mul
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    max_latency ${max_latency} \
    registered_input ${registered_input} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    exp ${exp} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


# Memory (RAM/ROM)  definition:
set ID 19
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_bkb
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 6
set AddrRange 64
set AddrWd 6
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "100000" "100000" "100000" "011111" "011111" "011110" "011110" "011101" "011101" "011101" "011100" "011100" "011011" "011011" "011011" "011010" "011010" "011010" "011001" "011001" "011001" "011001" "011000" "011000" "011000" "011000" "010111" "010111" "010111" "010111" "010110" "010110" "101011" "101011" "101010" "101010" "101001" "101001" "101001" "101000" "101000" "101000" "100111" "100111" "100110" "100110" "100110" "100101" "100101" "100101" "100100" "100100" "100100" "100100" "100011" "100011" "100011" "100010" "100010" "100010" "100010" "100001" "100001" "100001" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 0.677
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 20
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log0_lut_table_ap_fixed_65cud
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 56
set AddrRange 64
set AddrWd 6
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "11111111011111000001111011111101010110010011111011101000" "11111111011111000001111011111101010110010011111011101000" "11111111011111000001111011111101010110010011111011101000" "00000111100111001100110111000010010011001110000100001001" "00000111100111001100110111000010010011001110000100001001" "00010000000000011011011110110010111101110111100011101101" "00010000000000011011011110110010111101110111100011101101" "00011000101011110111110101011010101100101000100001101111" "00011000101011110111110101011010101100101000100001101111" "00011000101011110111110101011010101100101000100001101111" "00100001101010110011110000000001101010010000011111011111" "00100001101010110011110000000001101010010000011111011111" "00101010111110101001111111010100000000011011101001001011" "00101010111110101001111111010100000000011011101001001011" "00101010111110101001111111010100000000011011101001001011" "00110100101000111111100101110110011011101111001010101110" "00110100101000111111100101110110011011101111001010101110" "00110100101000111111100101110110011011101111001010101110" "00111110101011100101011111010110110000001010010111011010" "00111110101011100101011111010110110000001010010111011010" "00111110101011100101011111010110110000001010010111011010" "00111110101011100101011111010110110000001010010111011010" "01001001001000011010011101000010001011001010110100110001" "01001001001000011010011101000010001011001010110100110001" "01001001001000011010011101000010001011001010110100110001" "01001001001000011010011101000010001011001010110100110001" "01010100000001101101011100011010001110111100111001000110" "01010100000001101101011100011010001110111100111001000110" "01010100000001101101011100011010001110111100111001000110" "01010100000001101101011100011010001110111100111001000110" "01011111011010000000011111101100101110011001001101010111" "01011111011010000000011111101100101110011001001101010111" "10110011110110001001010000010001110101001100101000100101" "10110011110110001001010000010001110101001100101000100101" "10111001110111101010110001001110101010101010011010110000" "10111001110111101010110001001110101010101010011010110000" "11000000000010011110111000100010100111001100001010010011" "11000000000010011110111000100010100111001100001010010011" "11000000000010011110111000100010100111001100001010010011" "11000110010111000010111101101110001001000000101010100100" "11000110010111000010111101101110001001000000101010100100" "11000110010111000010111101101110001001000000101010100100" "11001100110101110110100111000011011100001001000101111111" "11001100110101110110100111000011011100001001000101111111" "11010011011111011011111000011100000010100001011101000000" "11010011011111011011111000011100000010100001011101000000" "11010011011111011011111000011100000010100001011101000000" "11011010010100010111100100001101000110010101010010100001" "11011010010100010111100100001101000110010101010010100001" "11011010010100010111100100001101000110010101010010100001" "11100001010101010001011110001111001011100100110000000010" "11100001010101010001011110001111001011100100110000000010" "11100001010101010001011110001111001011100100110000000010" "11100001010101010001011110001111001011100100110000000010" "11101000100010110100110001110010011100111101001110011100" "11101000100010110100110001110010011100111101001110011100" "11101000100010110100110001110010011100111101001110011100" "11101111111101110000011010011101010100001000110110010101" "11101111111101110000011010011101010100001000110110010101" "11101111111101110000011010011101010100001000110110010101" "11101111111101110000011010011101010100001000110110010101" "11110111100110110111100000111001101110110011001000101000" "11110111100110110111100000111001101110110011001000101000" "11110111100110110111100000111001101110110011001000101000" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 1.237
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 21
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_dEe
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 52
set AddrRange 16
set AddrWd 4
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "0000000000000000000000000000000000000000000000000000" "0001000000000000000000010101010101010101100010001000" "0010000000010000000100101011111011000011001011111000" "0011000000110000010101001001110100111011001010100001" "0100000001100000111001111011001111111001100000100100" "0101000010100001111011010010101000010011011111001101" "0110000011110011100001101000110000001110111100111001" "0111000101010101110101011100110110000001110101010011" "0111100110001101010011000101101010111101011011111111" "1000101000001000111011001111100110100100111001100101" "1001101010010101100110100010011011010011100001100010" "1010101100110011011101110100101111011001111000111000" "1011101111100010101010000100000100010000100111101111" "1100110010100011010100010100111101101000010111100101" "1101110101110101100101110011001001000011010011000001" "1110111001011001100111110001100101011000010110101001" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 0.677
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 22
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_eOg
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 49
set AddrRange 64
set AddrWd 6
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "0000000000000000000000000000000000000000000000000" "0000010000000000000000000000000000010101010101010" "0000100000000000001000000000000100101010101101001" "0000110000000000011000000000010101000000010011100" "0001000000000000110000000000111001010110100000010" "0001010000000001010000000001111001101101110111110" "0001100000000001111000000011011110000111001001101" "0001110000000010101000000101101110100011010010011" "0010000000000011100000001000110011000011011001110" "0010010000000100100000001100110011101000110100001" "0010100000000101101000010001111000010101000001100" "0010110000000110111000011000001001001001101110011" "0011000000001000010000011111101110001000110010110" "0011010000001001110000101000101111010100010011010" "0011100000001011011000110011010100101110100000000" "0011110000001101001000111111100110011001110101110" "0100000000001111000001001101101100011000111101000" "0100010000010001000001011101101110101110101010011" "0100100000010011001001101111110101011101111110110" "0100110000010101011010000100001000101010000110110" "0101000000010111110010011010110000010110011011100" "0101010000011010010010110011110100100110100010001" "0101100000011100111011001111011101011110001011101" "0101110000011111101011101101110011000001010101011" "0110000000100010100100001110111101010100001000110" "0110010000100101100100110011000100011010111011011" "0110100000101000101101011010010000011010001111000" "0110110000101011111110000100101001010110110001010" "0111000000101111010110110010010111010101011100011" "0111010000110010110111100011100010011011010110011" "0111100000110110100000011000010010101101110001101" "0111110000111010010001010000110000010010001100100" "1000000000111110001010001101000011001110010001110" "1000010001000010001011001101010011100111111000010" "1000100001000110010100010001101001100101000011000" "1000110001001010100101011010001101001100000001000" "1001000001001110111110100111000110100011001110000" "1001010001010011011111111000011101110001010001011" "1001100001011000001001001110011010111100111111000" "1001110001011100111010101001000110001101010110111" "1010000001100001110100001000100111101001100101011" "1010010001100110110101101101000111011001000011000" "1010100001101011111111010110101101100011010100011" "1010110001110001010001000101100010010000001010101" "1011000001110110101010111001101101100111100010110" "1011010001111100001100110011010111110001100110010" "1011100010000001110110110010101000110110101011000" "1011110010000111101000110111101000111111010010111" "1100000010001101100011000010100000010100001100010" "1100010010010011100101010011010110111110010001100" "1100100010011001101111101010010101000110101001100" "1100110010100000000010000111100010110110100111011" "1101000010100110011100101011001000010111101010100" "1101010010101100111111010101001101110011011110110" "1101100010110011101010000101111011010011111011110" "1101110010111010011100111101011001000011000110010" "1110000011000001010111111011101111001011001110100" "1110010011001000011011000001000101110110110001110" "1110100011001111100110001101100101010000011001010" "1110110011010110111001100001010101100010111010100" "1111000011011110010100111100011110111001010111101" "1111010011100101111000011111001001011110111110110" "1111100011101101100100001001011101011111001010110" "1111110011110101010111111011100011000101100010101" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 1.237
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 23
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_65_fYi
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 44
set AddrRange 64
set AddrWd 6
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "00000000000000000000000000000000000000000000" "00000100000000000000000001111100000000000001" "00001000000000000000000111111000000000001010" "00001100000000000000010001110100000000100011" "00010000000000000000011111110000000001010100" "00010100000000000000110001101100000010100101" "00011000000000000001000111101000000100011101" "00011100000000000001100001100100000111000110" "00100000000000000001111111100000001010100110" "00100100000000000010100001011100001111000110" "00101000000000000011000111011000010100101111" "00101100000000000011110001010100011011100111" "00110000000000000100011111010000100011110111" "00110100000000000101010001001100101101100110" "00111000000000000110000111001000111000111110" "00111100000000000111000001000101000110000110" "01000000000000000111111111000001010101000101" "01000100000000001001000000111101100110000100" "01001000000000001010000110111001111001001100" "01001100000000001011010000110110001110100011" "01010000000000001100011110110010100110010010" "01010100000000001101110000101111000000100001" "01011000000000001111000110101011011101010111" "01011100000000010000100000100111111100111110" "01100000000000010001111110100100011111011101" "01100100000000010011100000100001000100111011" "01101000000000010101000110011101101101100010" "01101100000000010110110000011010011001011000" "01110000000000011000011110010111001000100110" "01110100000000011010010000010011111011010100" "01111000000000011100000110010000110001101010" "01111100000000011110000000001101101011110000" "10000000000000011111111110001010101001101110" "10000100000000100010000000000111101011101100" "10001000000000100100000110000100110001110010" "10001100000000100110010000000001111100000111" "10010000000000101000011101111111001010110101" "10010100000000101010101111111100011110000010" "10011000000000101101000101111001110101111000" "10011100000000101111011111110111010010011101" "10100000000000110001111101110100110011111011" "10100100000000110100011111110010011010011000" "10101000000000110111000101110000000101111101" "10101100000000111001101111101101110110110010" "10110000000000111100011101101011101100111111" "10110100000000111111001111101001101000101101" "10111000000001000010000101100111101010000010" "10111100000001000100111111100101110001000111" "11000000000001000111111101100011111110000100" "11000100000001001010111111100010010001000001" "11001000000001001110000101100000101010000110" "11001100000001010001001111011111001001011011" "11010000000001010100011101011101101111001000" "11010100000001010111101111011100011011010101" "11011000000001011011000101011011001110001010" "11011100000001011110011111011010000111101111" "11100000000001100001111101011001001000001100" "11100100000001100101011111011000001111101001" "11101000000001101001000101010111011110001110" "11101100000001101100101111010110110100000011" "11110000000001110000011101010110010001010000" "11110100000001110100001111010101110101111101" "11111000000001111000000101010101100010010010" "11111100000001111011111111010101010110011000" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 1.237
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 24
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_27_g8j
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 27
set AddrRange 512
set AddrWd 9
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "100000000000000000000000000" "100000000100000000010000000" "100000001000000001000000000" "100000001100000010010000010" "100000010000000100000000101" "100000010100000110010001010" "100000011000001001000010010" "100000011100001100010011100" "100000100000010000000101010" "100000100100010100010111101" "100000101000011001001010011" "100000101100011110011101111" "100000110000100100010010000" "100000110100101010100111000" "100000111000110001011100110" "100000111100111000110011011" "100001000001000000101011000" "100001000101001001000011100" "100001001001010001111101010" "100001001101011011011000000" "100001010001100101010100001" "100001010101101111110001011" "100001011001111010110000000" "100001011110000110010000001" "100001100010010010010001101" "100001100110011110110100110" "100001101010101011111001011" "100001101110111001011111110" "100001110011000111100111110" "100001110111010110010001101" "100001111011100101011101011" "100001111111110101001011000" "100010000100000101011010101" "100010001000010110001100011" "100010001100100111100000010" "100010010000111001010110010" "100010010101001011101110101" "100010011001011110101001010" "100010011101110010000110010" "100010100010000110000101110" "100010100110011010100111111" "100010101010101111101100100" "100010101111000101010011110" "100010110011011011011101111" "100010110111110010001010101" "100010111100001001011010011" "100011000000100001001101000" "100011000100111001100010110" "100011001001010010011011100" "100011001101101011110111011" "100011010010000101110110100" "100011010110100000011000111" "100011011010111011011110100" "100011011111010111000111110" "100011100011110011010100011" "100011101000010000000100101" "100011101100101101011000011" "100011110001001011010000000" "100011110101101001101011010" "100011111010001000101010011" "100011111110101000001101011" "100100000011001000010100100" "100100000111101000111111100" "100100001100001010001110110" "100100010000101100000010001" "100100010101001110011001110" "100100011001110001010101110" "100100011110010100110110001" "100100100010111000111011000" "100100100111011101100100011" "100100101100000010110010011" "100100110000101000100101001" "100100110101001110111100100" "100100111001110101111000111" "100100111110011101011010000" "100101000011000101100000010" "100101000111101110001011100" "100101001100010111011011110" "100101010001000001010001011" "100101010101101011101100001" "100101011010010110101100010" "100101011111000010010001111" "100101100011101110011100111" "100101101000011011001101100" "100101101101001000100011110" "100101110001110110011111101" "100101110110100101000001011" "100101111011010100001000111" "100110000000000011110110011" "100110000100110100001001111" "100110001001100101000011100" "100110001110010110100011010" "100110010011001000101001001" "100110010111111011010101011" "100110011100101110101000000" "100110100001100010100001001" "100110100110010111000000101" "100110101011001100000110111" "100110110000000001110011110" "100110110100111000000111011" "100110111001101111000001110" "100110111110100110100011001" "100111000011011110101011011" "100111001000010111011010110" "100111001101010000110001010" "100111010010001010101111000" "100111010111000101010100000" "100111011100000000100000011" "100111100000111100010100001" "100111100101111000101111100" "100111101010110101110010011" "100111101111110011011101000" "100111110100110001101111010" "100111111001110000101001011" "100111111110110000001011100" "101000000011110000010101100" "101000001000110001000111101" "101000001101110010100001110" "101000010010110100100100010" "101000010111110111001111000" "101000011100111010100010000" "101000100001111110011101101" "101000100111000011000001110" "101000101100001000001110011" "101000110001001110000011110" "101000110110010100100010000" "101000111011011011101001000" "101001000000100011011000111" "101001000101101011110001111" "101001001010110100110011111" "101001001111111110011111000" "101001010101001000110011100" "101001011010010011110001010" "101001011111011111011000100" "101001100100101011101001001" "101001101001111000100011011" "101001101111000110000111011" "101001110100010100010101000" "101001111001100011001100011" "101001111110110010101101110" "101010000100000010111001001" "101010001001010011101110100" "101010001110100101001110001" "101010010011110111010111111" "101010011001001010001100000" "101010011110011101101010100" "101010100011110001110011011" "101010101001000110100110111" "101010101110011100000101001" "101010110011110010001110000" "101010111001001001000001101" "101010111110100000100000010" "101011000011111000101001111" "101011001001010001011110100" "101011001110101010111110010" "101011010100000101001001010" "101011011001011111111111100" "101011011110111011100001010" "101011100100010111101110100" "101011101001110100100111010" "101011101111010010001011101" "101011110100110000011011110" "101011111010001111010111110" "101011111111101110111111101" "101100000101001111010011100" "101100001010110000010011100" "101100010000010001111111101" "101100010101110100011000000" "101100011011010111011100110" "101100100000111011001101111" "101100100110011111101011101" "101100101100000100110101111" "101100110001101010101100111" "101100110111010001010000101" "101100111100111000100001001" "101101000010100000011110110" "101101001000001001001001011" "101101001101110010100001000" "101101010011011100100110000" "101101011001000111011000010" "101101011110110010110111111" "101101100100011111000101000" "101101101010001011111111101" "101101101111111001101000000" "101101110101100111111110001" "101101111011010111000010000" "101110000001000110110011111" "101110000110110111010011110" "101110001100101000100001110" "101110010010011010011101111" "101110011000001101001000011" "101110011110000000100001010" "101110100011110100101000100" "101110101001101001011110011" "101110101111011111000011000" "101110110101010101010110010" "101110111011001100011000011" "101111000001000100001001011" "101111000110111100101001011" "101111001100110101111000100" "101111010010101111110110111" "101111011000101010100100100" "101111011110100110000001101" "101111100100100010001110001" "101111101010011111001010001" "101111110000011100110101111" "101111110110011011010001011" "101111111100011010011100110" "110000000010011010011000000" "110000001000011011000011011" "110000001110011100011110111" "110000010100011110101010100" "110000011010100001100110100" "110000100000100101010011000" "110000100110101001101111111" "110000101100101110111101011" "110000110010110100111011101" "110000111000111011101010110" "110000111111000011001010101" "110001000101001011011011100" "110001001011010100011101100" "110001010001011110010000101" "110001010111101000110101001" "110001011101110100001010111" "110001100100000000010010001" "110001101010001101001011000" "110001110000011010110101100" "110001110110101001010001110" "110001111100111000011111111" "110010000011001000011111111" "110010001001011001010010000" "110010001111101010110110010" "110010010101111101001100110" "110010011100010000010101101" "110010100010100100010000111" "110010101000111000111110110" "110010101111001110011111001" "110010110101100100110010011" "110010111011111011111000011" "110011000010010011110001011" "110011001000101100011101011" "110011001111000101111100100" "110011010101100000001110111" "110011011011111011010100101" "110011100010010111001101110" "110011101000110011111010011" "110011101111010001011010110" "110011110101101111101110111" "110011111100001110110110110" "110100000010101110110010100" "110100001001001111100010100" "110100001111110001000110100" "110100010110010011011110110" "110100011100110110101011011" "110100100011011010101100100" "110100101001111111100010001" "010011011010001011001011111" "010011011100100110100111000" "010011011111000010010101100" "010011100001011110010111101" "010011100011111010101101001" "010011100110010111010110010" "010011101000110100010011000" "010011101011010001100011011" "010011101101101111000111011" "010011110000001100111111001" "010011110010101011001010101" "010011110101001001101010000" "010011110111101000011101001" "010011111010000111100100001" "010011111100100110111111000" "010011111111000110101101111" "010100000001100110110000101" "010100000100000111000111100" "010100000110100111110010100" "010100001001001000110001100" "010100001011101010000100101" "010100001110001011101100000" "010100010000101101100111101" "010100010011001111110111100" "010100010101110010011011101" "010100011000010101010100001" "010100011010111000100001000" "010100011101011100000010010" "010100011111111111111000000" "010100100010100100000010010" "010100100101001000100001000" "010100100111101101010100011" "010100101010010010011100011" "010100101100110111111001000" "010100101111011101101010011" "010100110010000011110000011" "010100110100101010001011010" "010100110111010000111011000" "010100111001110111111111100" "010100111100011111011001000" "010100111111000111000111011" "010101000001101111001010110" "010101000100010111100011001" "010101000111000000010000101" "010101001001101001010011010" "010101001100010010101011000" "010101001110111100011000000" "010101010001100110011010001" "010101010100010000110001100" "010101010110111011011110011" "010101011001100110100000100" "010101011100010001111000000" "010101011110111101100100111" "010101100001101001100111011" "010101100100010101111111011" "010101100111000010101100111" "010101101001101111110000000" "010101101100011101001000111" "010101101111001010110111011" "010101110001111000111011101" "010101110100100111010101101" "010101110111010110000101011" "010101111010000101001011001" "010101111100110100100110110" "010101111111100100011000010" "010110000010010100011111111" "010110000101000100111101011" "010110000111110101110001001" "010110001010100110111010111" "010110001101011000011010111" "010110010000001010010001000" "010110010010111100011101011" "010110010101101111000000001" "010110011000100001111001001" "010110011011010101001000101" "010110011110001000101110100" "010110100000111100101010110" "010110100011110000111101101" "010110100110100101100111001" "010110101001011010100111001" "010110101100001111111101110" "010110101111000101101011001" "010110110001111011101111001" "010110110100110010001010000" "010110110111101000111011110" "010110111010100000000100010" "010110111101010111100011110" "010111000000001111011010001" "010111000011000111100111101" "010111000110000000001100001" "010111001000111001000111101" "010111001011110010011010011" "010111001110101100000100010" "010111010001100110000101011" "010111010100100000011101111" "010111010111011011001101101" "010111011010010110010100101" "010111011101010001110011001" "010111100000001101101001001" "010111100011001001110110101" "010111100110000110011011101" "010111101001000011011000010" "010111101100000000101100100" "010111101110111110011000011" "010111110001111100011100001" "010111110100111010110111100" "010111110111111001101010110" "010111111010111000110110000" "010111111101111000011001000" "011000000000111000010100001" "011000000011111000100111001" "011000000110111001010010010" "011000001001111010010101100" "011000001100111011110000111" "011000001111111101100100011" "011000010010111111110000010" "011000010110000010010100011" "011000011001000101010000111" "011000011100001000100101110" "011000011111001100010011000" "011000100010010000011000110" "011000100101010100110111001" "011000101000011001101110000" "011000101011011110111101101" "011000101110100100100101110" "011000110001101010100110110" "011000110100110001000000100" "011000110111110111110011000" "011000111010111110111110011" "011000111110000110100010110" "011001000001001110100000001" "011001000100010110110110011" "011001000111011111100101110" "011001001010101000101110011" "011001001101110010010000000" "011001010000111100001010111" "011001010100000110011111000" "011001010111010001001100100" "011001011010011100010011011" "011001011101100111110011101" "011001100000110011101101011" "011001100100000000000000101" "011001100111001100101101011" "011001101010011001110011110" "011001101101100111010011111" "011001110000110101001101101" "011001110100000011100001001" "011001110111010010001110100" "011001111010100001010101110" "011001111101110000110110111" "011010000001000000110010000" "011010000100010001000111001" "011010000111100001110110010" "011010001010110010111111100" "011010001110000100100011000" "011010010001010110100000110" "011010010100101000111000101" "011010010111111011101011000" "011010011011001110110111101" "011010011110100010011110101" "011010100001110110100000010" "011010100101001010111100011" "011010101000011111110011000" "011010101011110101000100010" "011010101111001010110000010" "011010110010100000110111000" "011010110101110111011000100" "011010111001001110010100111" "011010111100100101101100001" "011010111111111101011110010" "011011000011010101101011100" "011011000110101110010011110" "011011001010000111010111001" "011011001101100000110101101" "011011010000111010101111010" "011011010100010101000100010" "011011010111101111110100101" "011011011011001011000000010" "011011011110100110100111011" "011011100010000010101001111" "011011100101011111001000000" "011011101000111100000001110" "011011101100011001010111001" "011011101111110111001000001" "011011110011010101010100111" "011011110110110011111101100" "011011111010010011000001111" "011011111101110010100010010" "011100000001010010011110100" "011100000100110010110110111" "011100001000010011101011010" "011100001011110100111011110" "011100001111010110101000100" "011100010010111000110001100" "011100010110011011010110110" "011100011001111110011000011" "011100011101100001110110011" "011100100001000101110000110" "011100100100101010000111110" "011100101000001110111011011" "011100101011110100001011100" "011100101111011001111000011" "011100110011000000000010000" "011100110110100110101000100" "011100111010001101101011110" "011100111101110101001011111" "011101000001011101001001000" "011101000101000101100011010" "011101001000101110011010100" "011101001100010111101110111" "011101010000000001100000011" "011101010011101011101111010" "011101010111010110011011011" "011101011011000001100100111" "011101011110101101001011110" "011101100010011001010000001" "011101100110000101110010001" "011101101001110010110001101" "011101101101100000001110110" "011101110001001110001001110" "011101110100111100100010011" "011101111000101011011000111" "011101111100011010101101010" "011110000000001010011111100" "011110000011111010101111111" "011110000111101011011110010" "011110001011011100101010110" "011110001111001110010101100" "011110010011000000011110011" "011110010110110011000101101" "011110011010100110001011001" "011110011110011001101111001" "011110100010001101110001101" "011110100110000010010010101" "011110101001110111010010010" "011110101101101100110000100" "011110110001100010101101011" "011110110101011001001001001" "011110111001010000000011110" "011110111101000111011101001" "011111000000111111010101101" "011111000100110111101101000" "011111001000110000100011100" "011111001100101001111001010" "011111010000100011101110000" "011111010100011110000010001" "011111011000011000110101101" "011111011100010100001000011" "011111100000001111111010101" "011111100100001100001100011" "011111101000001000111101110" "011111101100000110001110101" "011111110000000011111111010" "011111110100000010001111101" "011111111000000000111111111" "011111111100000000001111111" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 1.237
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# Memory (RAM/ROM)  definition:
set ID 25
set hasByteEnable 0
set MemName uz_FOC_sample_pow_generic_float_s_pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_27_0_hbi
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 8
set AddrRange 32
set AddrWd 5
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "00000000" "00000000" "00000001" "00000010" "00000100" "00000110" "00001001" "00001100" "00010000" "00010100" "00011001" "00011110" "00100100" "00101010" "00110001" "00111000" "01000000" "01001000" "01010001" "01011010" "01100100" "01101110" "01111001" "10000100" "10010000" "10011100" "10101001" "10110110" "11000100" "11010010" "11100001" "11110000" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set MaxLatency -1
set DelayBudget 0.677
set ClkPeriod 10
set RegisteredInput 0
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
  ::AP::rtl_comp_handler $MemName
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    registered_input ${RegisteredInput} \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 26 \
    name base_r \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_base_r \
    op interface \
    ports { base_r { I 32 vector } } \
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
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -2 \
    name ap_return \
    type ap_return \
    reset_level 1 \
    sync_rst true \
    corename ap_return \
    op interface \
    ports { ap_return { O 32 vector } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -3 \
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
    id -4 \
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


# Adapter definition:
set PortName ap_ce
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_ce] == "cg_default_interface_gen_ce"} {
eval "cg_default_interface_gen_ce { \
    id -5 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_ce \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


