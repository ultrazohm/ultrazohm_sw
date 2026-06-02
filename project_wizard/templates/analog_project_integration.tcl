# -----------------------------------------------------------------------------
# Analog adapter project-level integration
# -----------------------------------------------------------------------------

puts "Applying A-slot analog project-level integration"

{% if has_axi2tcm_note %}
puts "WARNING: {{ axi2tcm_note }}"
{% endif %}

puts "Applying AXI2TCM DataMover packing for A-slot ADC streams"

set project_wizard_datamover_hier "uz_system/DataMover"
set project_wizard_axi2tcm "${project_wizard_datamover_hier}/AXI2TCM_0"
set project_wizard_axi2tcm_channels {{ axi2tcm_channel_count }}
set project_wizard_axi2tcm_data_width {{ axi2tcm_data_width }}

if {[llength [get_bd_cells -quiet $project_wizard_axi2tcm]] > 0} {
  uz_pw_set_property_if_objects CONFIG.C_M00_NUMBER_of_ADCs $project_wizard_axi2tcm_channels [get_bd_cells -quiet $project_wizard_axi2tcm] $project_wizard_axi2tcm
} else {
  puts "WARNING: AXI2TCM cell not found: $project_wizard_axi2tcm"
}

{% for pin in datamover_adc_pins %}
uz_pw_delete_pin_if_exists uz_system/{{ pin }}
uz_pw_delete_pin_if_exists uz_system/DataMover/{{ pin }}
{% endfor %}

uz_pw_delete_cell_if_exists uz_system/DataMover/xlconcat_0
uz_pw_delete_cell_if_exists uz_system/DataMover/project_wizard_axi2tcm_zero_input

{% if has_adc_streams %}
{% for stream in adc_streams %}
uz_pw_create_hier_pin_if_missing uz_system I {{ stream.pin_name }} {{ stream.left }} {{ stream.right }}
uz_pw_create_hier_pin_if_missing uz_system/DataMover I {{ stream.pin_name }} {{ stream.left }} {{ stream.right }}
uz_pw_connect_pin_pair_if_unconnected {{ stream.source_pin }} uz_system/{{ stream.pin_name }}
uz_pw_connect_pin_pair_if_unconnected uz_system/{{ stream.pin_name }} uz_system/DataMover/{{ stream.pin_name }}
{% endfor %}
{% endif %}

{% if use_adc_concat %}
uz_pw_create_ip_cell_if_missing uz_system/DataMover/xlconcat_0 xilinx.com:ip:xlconcat
uz_pw_set_property_if_objects CONFIG.NUM_PORTS {{ adc_stream_count }} [get_bd_cells -quiet uz_system/DataMover/xlconcat_0] uz_system/DataMover/xlconcat_0
{% for stream in adc_streams %}
uz_pw_connect_pin_pair_if_unconnected uz_system/DataMover/{{ stream.pin_name }} uz_system/DataMover/xlconcat_0/In{{ stream.concat_index }}
{% endfor %}
uz_pw_connect_pins_to_shared_net [list uz_system/DataMover/xlconcat_0/dout uz_system/DataMover/AXI2TCM_0/DATA_IN uz_system/DataMover/system_ila_0/probe0]
{% endif %}

{% if use_single_adc_stream %}
{% for stream in adc_streams %}
uz_pw_connect_pins_to_shared_net [list uz_system/DataMover/{{ stream.pin_name }} uz_system/DataMover/AXI2TCM_0/DATA_IN uz_system/DataMover/system_ila_0/probe0]
{% endfor %}
{% endif %}

{% if use_zero_datamover_input %}
uz_pw_create_ip_cell_if_missing uz_system/DataMover/project_wizard_axi2tcm_zero_input xilinx.com:ip:xlconstant
uz_pw_set_property_if_objects CONFIG.CONST_WIDTH $project_wizard_axi2tcm_data_width [get_bd_cells -quiet uz_system/DataMover/project_wizard_axi2tcm_zero_input] uz_system/DataMover/project_wizard_axi2tcm_zero_input
uz_pw_set_property_if_objects CONFIG.CONST_VAL 0 [get_bd_cells -quiet uz_system/DataMover/project_wizard_axi2tcm_zero_input] uz_system/DataMover/project_wizard_axi2tcm_zero_input
uz_pw_connect_pins_to_shared_net [list uz_system/DataMover/project_wizard_axi2tcm_zero_input/dout uz_system/DataMover/AXI2TCM_0/DATA_IN uz_system/DataMover/system_ila_0/probe0]
{% endif %}

uz_pw_create_ip_cell_if_missing uz_system/DataMover/util_vector_logic_0 xilinx.com:ip:util_vector_logic
uz_pw_set_property_if_objects CONFIG.C_SIZE 1 [get_bd_cells -quiet uz_system/DataMover/util_vector_logic_0] uz_system/DataMover/util_vector_logic_0
uz_pw_set_property_if_objects CONFIG.C_OPERATION and [get_bd_cells -quiet uz_system/DataMover/util_vector_logic_0] uz_system/DataMover/util_vector_logic_0
uz_pw_create_hier_pin_if_missing uz_system I Trigger_AXI2TCM
uz_pw_create_hier_pin_if_missing uz_system/DataMover I Trigger_AXI2TCM
uz_pw_create_hier_pin_if_missing uz_system/DataMover I Enable_AXI2TCM
uz_pw_connect_pin_pair_if_unconnected uz_system/DataMover/Trigger_AXI2TCM uz_system/DataMover/util_vector_logic_0/Op1
uz_pw_connect_pin_pair_if_unconnected uz_system/DataMover/Enable_AXI2TCM uz_system/DataMover/util_vector_logic_0/Op2
uz_pw_connect_pin_pair_if_unconnected uz_system/DataMover/util_vector_logic_0/Res uz_system/DataMover/AXI2TCM_0/init_axi_txn

{% if has_axi2tcm_trigger %}
uz_pw_connect_pin_pair_if_unconnected {{ axi2tcm_trigger_source }} {{ axi2tcm_trigger_target }}
uz_pw_connect_pin_pair_if_unconnected {{ axi2tcm_trigger_target }} uz_system/DataMover/Trigger_AXI2TCM
{% endif %}

{% if has_conversion_trigger %}
uz_pw_connect_pins_to_shared_net [list {{ conversion_trigger_pins }}]
{% endif %}
