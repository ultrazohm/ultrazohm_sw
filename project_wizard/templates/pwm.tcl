# -----------------------------------------------------------------------------
# Project-level PWM hierarchy
# -----------------------------------------------------------------------------

{% if enabled %}
puts "Project Wizard: refreshing project-level PWM hierarchy"

set uz_pw_pwm_root {{ root_hier }}
set uz_pw_pwm_2l_hier {{ pwm_2l_hier }}
set uz_pw_pwm_3l_hier {{ pwm_3l_hier }}
set uz_pw_pwm_upstream_smartconnect {{ upstream_smartconnect }}
set uz_pw_pwm_clock_pin {{ clock_pin }}
set uz_pw_pwm_resetn_pin {{ resetn_pin }}
set uz_pw_pwm_address_space {{ address_space }}

proc uz_pw_pwm_assign_address {address_space addr_seg_path} {
  if {$address_space eq ""} {
    puts "WARNING: PWM address space is empty. Skipping address assignment for $addr_seg_path"
    return
  }
  set address_space_obj [get_bd_addr_spaces -quiet $address_space]
  if {[llength $address_space_obj] == 0} {
    puts "WARNING: PWM address space not found: $address_space"
    return
  }
  set addr_seg [get_bd_addr_segs -quiet $addr_seg_path]
  if {[llength $addr_seg] == 0} {
    puts "WARNING: PWM address segment not found: $addr_seg_path"
    return
  }
  if {[catch {assign_bd_address -target_address_space $address_space_obj $addr_seg -force} result]} {
    puts "WARNING: PWM automatic address assignment failed for $addr_seg_path: $result"
  }
}

proc uz_pw_pwm_connect_root_to_child_pin {root_pin child_pin} {
  if {[llength [get_bd_pins -quiet $root_pin]] == 0 || [llength [get_bd_pins -quiet $child_pin]] == 0} {
    puts "WARNING: Cannot connect PWM root pin $root_pin to child pin $child_pin"
    return
  }
  uz_pw_connect_upper_boundary_net_if_unconnected $root_pin $child_pin
}

proc uz_pw_pwm_attach_axi {upstream_smartconnect root_pin child_pin local_smartconnect} {
  if {$upstream_smartconnect eq "" || [llength [get_bd_cells -quiet $upstream_smartconnect]] == 0} {
    puts "WARNING: PWM upstream SmartConnect not found: $upstream_smartconnect"
    return
  }

  set upstream_hier_path [uz_pw_parent_path $upstream_smartconnect]
  set upstream_boundary_pin ${upstream_hier_path}/[uz_pw_leaf_name $root_pin]
  uz_pw_create_intf_pin_if_missing Master $upstream_boundary_pin
  uz_pw_create_intf_pin_if_missing Slave $root_pin
  uz_pw_create_intf_pin_if_missing Slave $child_pin

  set upstream_mi_pin [uz_pw_find_peer_intf_pin $upstream_boundary_pin "*${upstream_smartconnect}/M*_AXI"]
  if {$upstream_mi_pin eq ""} {
    set upstream_mi_pin [uz_pw_get_or_add_upstream_mi_pin $upstream_smartconnect]
  }

  uz_pw_connect_intf_if_unconnected $upstream_mi_pin $upstream_boundary_pin
  uz_pw_connect_intf_upper_if_unconnected $upstream_boundary_pin $root_pin
  uz_pw_connect_intf_upper_if_unconnected $root_pin $child_pin
  uz_pw_connect_intf_preserve_source_if_unconnected $child_pin ${local_smartconnect}/S00_AXI
}

uz_pw_create_hier_if_missing $uz_pw_pwm_root
uz_pw_delete_cell_if_exists $uz_pw_pwm_2l_hier
uz_pw_delete_cell_if_exists $uz_pw_pwm_3l_hier
uz_pw_delete_intf_pin_and_net_if_present ${uz_pw_pwm_root}/S00_AXI_2L
uz_pw_delete_intf_pin_and_net_if_present ${uz_pw_pwm_root}/S00_AXI_3L
set uz_pw_pwm_upstream_hier_path [uz_pw_parent_path $uz_pw_pwm_upstream_smartconnect]
if {$uz_pw_pwm_upstream_hier_path ne ""} {
  uz_pw_delete_intf_pin_and_net_if_present ${uz_pw_pwm_upstream_hier_path}/S00_AXI_2L
  uz_pw_delete_intf_pin_and_net_if_present ${uz_pw_pwm_upstream_hier_path}/S00_AXI_3L
}
uz_pw_create_hier_if_missing $uz_pw_pwm_2l_hier
uz_pw_create_hier_if_missing $uz_pw_pwm_3l_hier

uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_root}/clk
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_root}/resetn
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_root}/ADC_TriggerConversion
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_root}/Enable_Gate
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Gate_Signals_2L {{ gate_width }} 0
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Gate_Signals_3L 11 0
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Carrier_triangular_max
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Carrier_triangular_min
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Carrier_triangular_max_min
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Interrupt_Start
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Interrupt_Center
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_root}/Interrupt_Start_Center

if {$uz_pw_pwm_clock_pin ne ""} {
  uz_pw_connect_net_if_unconnected $uz_pw_pwm_clock_pin ${uz_pw_pwm_root}/clk
}
if {$uz_pw_pwm_resetn_pin ne ""} {
  uz_pw_connect_net_if_unconnected $uz_pw_pwm_resetn_pin ${uz_pw_pwm_root}/resetn
}

# 2L PWM ----------------------------------------------------------------------
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_2l_hier}/clk
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_2l_hier}/resetn
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_2l_hier}/ADC_TriggerConversion
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_2l_hier}/Gate_Signals_2L {{ gate_width }} 0
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_2l_hier}/Carrier_triangular_max
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_2l_hier}/Carrier_triangular_min
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min

uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/clk ${uz_pw_pwm_2l_hier}/clk
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/resetn ${uz_pw_pwm_2l_hier}/resetn
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/ADC_TriggerConversion ${uz_pw_pwm_2l_hier}/ADC_TriggerConversion
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Gate_Signals_2L ${uz_pw_pwm_2l_hier}/Gate_Signals_2L
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Carrier_triangular_max ${uz_pw_pwm_2l_hier}/Carrier_triangular_max
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Carrier_triangular_min ${uz_pw_pwm_2l_hier}/Carrier_triangular_min
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Carrier_triangular_max_min ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min

set pwm_2l_sc ${uz_pw_pwm_2l_hier}/axi_smartconnect
create_bd_cell -type ip -vlnv {{ local_smartconnect_vlnv }} $pwm_2l_sc
uz_pw_set_property_dict_if_objects [list CONFIG.NUM_SI 1 CONFIG.NUM_MI {{ pwm_2l_axi_count }}] [get_bd_cells $pwm_2l_sc] $pwm_2l_sc
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${pwm_2l_sc}/aclk
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/resetn ${pwm_2l_sc}/aresetn
uz_pw_pwm_attach_axi $uz_pw_pwm_upstream_smartconnect ${uz_pw_pwm_root}/S00_AXI_2L ${uz_pw_pwm_2l_hier}/S00_AXI $pwm_2l_sc

create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant ${uz_pw_pwm_2l_hier}/zero_modulation
set_property -dict [list CONFIG.CONST_WIDTH {18} CONFIG.CONST_VAL {0}] [get_bd_cells ${uz_pw_pwm_2l_hier}/zero_modulation]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant ${uz_pw_pwm_2l_hier}/zero_counter_reset
set_property -dict [list CONFIG.CONST_WIDTH {1} CONFIG.CONST_VAL {0}] [get_bd_cells ${uz_pw_pwm_2l_hier}/zero_counter_reset]
create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min_or
set_property -dict [list CONFIG.C_OPERATION {or} CONFIG.C_SIZE {1}] [get_bd_cells ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min_or]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat ${uz_pw_pwm_2l_hier}/Gate_Signals_2L_concat
set_property CONFIG.NUM_PORTS {{ instance_count }} [get_bd_cells ${uz_pw_pwm_2l_hier}/Gate_Signals_2L_concat]
create_bd_cell -type ip -vlnv xilinx.com:ip:vio ${uz_pw_pwm_2l_hier}/vio_Gates_2L
set_property -dict [list CONFIG.C_NUM_PROBE_IN {0} CONFIG.C_NUM_PROBE_OUT {{ vio_probe_count }} {% for probe in vio_probe_props %}CONFIG.C_PROBE_OUT{{ probe.index }}_WIDTH {1} {% endfor %}] [get_bd_cells ${uz_pw_pwm_2l_hier}/vio_Gates_2L]
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/vio_Gates_2L/clk

{% if debug_ila %}
create_bd_cell -type ip -vlnv xilinx.com:ip:ila ${uz_pw_pwm_2l_hier}/ila_0
set_property -dict [list CONFIG.C_DATA_DEPTH {16384} CONFIG.C_MONITOR_TYPE {Native} CONFIG.C_NUM_OF_PROBES {20}] [get_bd_cells ${uz_pw_pwm_2l_hier}/ila_0]
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/ila_0/clk
{% endif %}

{% for instance in instances %}
create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}
create_bd_cell -type ip -vlnv user.org:ip:uz_interlockDeadtime2L ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat ${uz_pw_pwm_2l_hier}/{{ instance.gate_concat_cell }}
set_property CONFIG.NUM_PORTS {6} [get_bd_cells ${uz_pw_pwm_2l_hier}/{{ instance.gate_concat_cell }}]

uz_pw_connect_intf_if_unconnected [uz_pw_get_sc_mi_pin $pwm_2l_sc {{ instance.pwm_mi_index }}] ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/AXI4_Lite
uz_pw_connect_intf_if_unconnected [uz_pw_get_sc_mi_pin $pwm_2l_sc {{ instance.interlock_mi_index }}] ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/AXI4
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/AXI4_Lite_ACLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/IPCORE_CLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/AXI4_ACLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/clk ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/IPCORE_CLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/resetn ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/AXI4_Lite_ARESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/resetn ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/IPCORE_RESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/resetn ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/AXI4_ARESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/resetn ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/IPCORE_RESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/zero_modulation/dout ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/m_u1_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/zero_modulation/dout ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/m_u2_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/zero_modulation/dout ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/m_u3_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/zero_counter_reset/dout ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/pwm_counter_rst
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/triangle_out ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/triangle_in
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.gate_concat_cell }}/dout ${uz_pw_pwm_2l_hier}/Gate_Signals_2L_concat/In{{ instance.index }}
{% endfor %}

{% for gate in gate_concat_connections %}
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ gate.interlock_cell }}/{{ gate.output_pin }} ${uz_pw_pwm_2l_hier}/{{ gate.concat_cell }}/In{{ gate.concat_input }}
{% endfor %}

{% for connection in vio_connections %}
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/vio_Gates_2L/probe_out{{ connection.probe_index }} ${uz_pw_pwm_2l_hier}/{{ connection.pwm_cell }}/SS{{ connection.signal_index }}_IN_External
{% endfor %}

{% for instance in instances %}
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS0_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S0
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS1_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS2_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS3_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S3
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS4_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S4
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/{{ instance.pwm_cell }}/SS5_OUT ${uz_pw_pwm_2l_hier}/{{ instance.interlock_cell }}/S5
{% endfor %}

uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Max ${uz_pw_pwm_2l_hier}/Carrier_triangular_max
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Min ${uz_pw_pwm_2l_hier}/Carrier_triangular_min
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Max ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min_or/Op1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Min ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min_or/Op2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min_or/Res ${uz_pw_pwm_2l_hier}/Carrier_triangular_max_min
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/Gate_Signals_2L_concat/dout ${uz_pw_pwm_2l_hier}/Gate_Signals_2L

{% if debug_ila %}
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS0_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe0
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS1_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS2_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS3_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe3
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS4_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe4
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/SS5_OUT ${uz_pw_pwm_2l_hier}/ila_0/probe5
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/PWM_enb_out ${uz_pw_pwm_2l_hier}/ila_0/probe6
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Max ${uz_pw_pwm_2l_hier}/ila_0/probe7
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/Triangular_Min ${uz_pw_pwm_2l_hier}/ila_0/probe8
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/triangle_out ${uz_pw_pwm_2l_hier}/ila_0/probe9
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/dir_out ${uz_pw_pwm_2l_hier}/ila_0/probe10
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/PWM_and_SS_control_V_0/applied_new_reference_value ${uz_pw_pwm_2l_hier}/ila_0/probe11
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s0_out ${uz_pw_pwm_2l_hier}/ila_0/probe12
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s1_out ${uz_pw_pwm_2l_hier}/ila_0/probe13
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s2_out ${uz_pw_pwm_2l_hier}/ila_0/probe14
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s3_out ${uz_pw_pwm_2l_hier}/ila_0/probe15
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s4_out ${uz_pw_pwm_2l_hier}/ila_0/probe16
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/s5_out ${uz_pw_pwm_2l_hier}/ila_0/probe17
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/uz_interlockDeadtime_0/enableFB ${uz_pw_pwm_2l_hier}/ila_0/probe18
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_2l_hier}/ADC_TriggerConversion ${uz_pw_pwm_2l_hier}/ila_0/probe19
{% endif %}

# 3L PWM ----------------------------------------------------------------------
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_3l_hier}/clk
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_3l_hier}/resetn
uz_pw_create_bd_pin_if_missing I ${uz_pw_pwm_3l_hier}/Enable_Gate
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_3l_hier}/Gate_Signals_3L 11 0
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_3l_hier}/Interrupt_Center
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_3l_hier}/Interrupt_Start
uz_pw_create_bd_pin_if_missing O ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/clk ${uz_pw_pwm_3l_hier}/clk
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/resetn ${uz_pw_pwm_3l_hier}/resetn
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Enable_Gate ${uz_pw_pwm_3l_hier}/Enable_Gate
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Gate_Signals_3L ${uz_pw_pwm_3l_hier}/Gate_Signals_3L
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Interrupt_Center ${uz_pw_pwm_3l_hier}/Interrupt_Center
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Interrupt_Start ${uz_pw_pwm_3l_hier}/Interrupt_Start
uz_pw_pwm_connect_root_to_child_pin ${uz_pw_pwm_root}/Interrupt_Start_Center ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center

set pwm_3l_sc ${uz_pw_pwm_3l_hier}/axi_smartconnect
create_bd_cell -type ip -vlnv {{ local_smartconnect_vlnv }} $pwm_3l_sc
uz_pw_set_property_dict_if_objects [list CONFIG.NUM_SI 1 CONFIG.NUM_MI 1] [get_bd_cells $pwm_3l_sc] $pwm_3l_sc
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${pwm_3l_sc}/aclk
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/resetn ${pwm_3l_sc}/aresetn
uz_pw_pwm_attach_axi $uz_pw_pwm_upstream_smartconnect ${uz_pw_pwm_root}/S00_AXI_3L ${uz_pw_pwm_3l_hier}/S00_AXI $pwm_3l_sc

create_bd_cell -type ip -vlnv mwn.de:ip:PWM_SS_3L_ip ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat ${uz_pw_pwm_3l_hier}/Gates_Vector
set_property CONFIG.NUM_PORTS {6} [get_bd_cells ${uz_pw_pwm_3l_hier}/Gates_Vector]
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat ${uz_pw_pwm_3l_hier}/xlconcat_0
set_property CONFIG.NUM_PORTS {12} [get_bd_cells ${uz_pw_pwm_3l_hier}/xlconcat_0]
create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or
set_property -dict [list CONFIG.C_OPERATION {or} CONFIG.C_SIZE {1}] [get_bd_cells ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or]
create_bd_cell -type ip -vlnv xilinx.com:ip:vio ${uz_pw_pwm_3l_hier}/Set_Deadtime_3L
set_property -dict [list CONFIG.C_NUM_PROBE_IN {0} CONFIG.C_PROBE_OUT0_INIT_VAL {0x0C8} CONFIG.C_PROBE_OUT0_WIDTH {10}] [get_bd_cells ${uz_pw_pwm_3l_hier}/Set_Deadtime_3L]
create_bd_cell -type ip -vlnv xilinx.com:ip:vio ${uz_pw_pwm_3l_hier}/vio_Gates_3L
set_property -dict [list CONFIG.C_NUM_PROBE_IN {0} CONFIG.C_NUM_PROBE_OUT {9} CONFIG.C_PROBE_OUT0_WIDTH {14} CONFIG.C_PROBE_OUT1_WIDTH {14} CONFIG.C_PROBE_OUT2_WIDTH {14} CONFIG.C_PROBE_OUT6_WIDTH {1} CONFIG.C_PROBE_OUT7_WIDTH {1} CONFIG.C_PROBE_OUT8_WIDTH {1}] [get_bd_cells ${uz_pw_pwm_3l_hier}/vio_Gates_3L]
create_bd_cell -type ip -vlnv xilinx.com:ip:system_ila ${uz_pw_pwm_3l_hier}/system_ila_0
set_property -dict [list CONFIG.C_DATA_DEPTH {16384} CONFIG.C_MON_TYPE {NATIVE} CONFIG.C_NUM_OF_PROBES {23}] [get_bd_cells ${uz_pw_pwm_3l_hier}/system_ila_0]
if {[catch {create_bd_cell -type module -reference top_npc_state_machine ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0} result]} {
  error "Unable to add referenced module top_npc_state_machine for PWM 3L: $result"
}

uz_pw_connect_intf_if_unconnected [uz_pw_get_sc_mi_pin $pwm_3l_sc 0] ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/AXI4_Lite
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/AXI4_Lite_ACLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/IPCORE_CLK
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/Set_Deadtime_3L/clk
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/vio_Gates_3L/clk
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/system_ila_0/clk
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/clk ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/clock
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/resetn ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/AXI4_Lite_ARESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/resetn ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/IPCORE_RESETN
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Enable_Gate ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/enable
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Gates_Vector/dout ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/switching_signals
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Gates_Vector/dout ${uz_pw_pwm_3l_hier}/system_ila_0/probe13
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Center ${uz_pw_pwm_3l_hier}/Interrupt_Center
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Center ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or/Op1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Center ${uz_pw_pwm_3l_hier}/system_ila_0/probe20
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Start ${uz_pw_pwm_3l_hier}/Interrupt_Start
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Start ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or/Op2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/Period_Start ${uz_pw_pwm_3l_hier}/system_ila_0/probe21
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or/Res ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Interrupt_Start_Center_or/Res ${uz_pw_pwm_3l_hier}/system_ila_0/probe12
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Set_Deadtime_3L/probe_out0 ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/deadtime
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/Set_Deadtime_3L/probe_out0 ${uz_pw_pwm_3l_hier}/system_ila_0/probe22

uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa1_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In0
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa2_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb1_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb2_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In3
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc1_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In4
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc2_OUT ${uz_pw_pwm_3l_hier}/Gates_Vector/In5
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa1_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe14
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa2_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe15
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb1_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe16
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb2_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe17
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc1_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe18
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc2_OUT ${uz_pw_pwm_3l_hier}/system_ila_0/probe19

uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/A_S1 ${uz_pw_pwm_3l_hier}/xlconcat_0/In0
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/A_S2 ${uz_pw_pwm_3l_hier}/xlconcat_0/In1
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/A_S3 ${uz_pw_pwm_3l_hier}/xlconcat_0/In2
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/A_S4 ${uz_pw_pwm_3l_hier}/xlconcat_0/In3
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/B_S1 ${uz_pw_pwm_3l_hier}/xlconcat_0/In4
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/B_S2 ${uz_pw_pwm_3l_hier}/xlconcat_0/In5
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/B_S3 ${uz_pw_pwm_3l_hier}/xlconcat_0/In6
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/B_S4 ${uz_pw_pwm_3l_hier}/xlconcat_0/In7
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/C_S1 ${uz_pw_pwm_3l_hier}/xlconcat_0/In8
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/C_S2 ${uz_pw_pwm_3l_hier}/xlconcat_0/In9
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/C_S3 ${uz_pw_pwm_3l_hier}/xlconcat_0/In10
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/top_npc_state_machine_0/C_S4 ${uz_pw_pwm_3l_hier}/xlconcat_0/In11
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/xlconcat_0/dout ${uz_pw_pwm_3l_hier}/Gate_Signals_3L

uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out0 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/m_u1_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out1 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/m_u2_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out2 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/m_u3_norm
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out3 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa1_IN_External
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out4 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSa2_IN_External
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out5 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb1_IN_External
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out6 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSb2_IN_External
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out7 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc1_IN_External
uz_pw_connect_net_if_unconnected ${uz_pw_pwm_3l_hier}/vio_Gates_3L/probe_out8 ${uz_pw_pwm_3l_hier}/PWM_SS_3L_ip_0/SSc2_IN_External

{% for segment in address_segments %}
uz_pw_pwm_assign_address {{ segment.address_space }} {{ segment.path }}
{% endfor %}

uz_pw_compact_upstream_mi_connections $uz_pw_pwm_upstream_smartconnect
{% endif %}
