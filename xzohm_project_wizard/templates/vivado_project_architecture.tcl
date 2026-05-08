# -----------------------------------------------------------------------------
# xZohm Project Wizard architecture setup
# -----------------------------------------------------------------------------
# Platform: {{ platform_name }}
# Platform ID: {{ platform_id }}
# Platform revision: {{ platform_revision }}

set xzohm_project_wizard_origin [pwd]
set xzohm_project_wizard_platform {{ platform_id }}
set xzohm_project_wizard_platform_name "{{ platform_name }}"
set xzohm_project_wizard_platform_revision "{{ platform_revision }}"

puts "xZohm Project Wizard: applying adapter card configuration"
puts "Target platform: {{ platform_name }} {{ platform_revision }}"

# TODO: Check that a Vivado project and block design are open.
# Example direction:
#   if {[current_project -quiet] eq ""} { error "No Vivado project open" }
#   if {[current_bd_design -quiet] eq ""} { error "No block design open" }

# TODO: Remove or reuse previously generated xZohm Project Wizard hierarchies.
# This should eventually be guarded by generated object names or a user choice.

{% for slot in configured_slots %}
# TODO: Create or refresh hierarchy for adapter slot {{ slot.slot }}.
# Suggested hierarchy path: uz_digital_Adapter/{{ slot.slot }}_adapter
{% endfor %}

{% for cpld in slot_cplds %}
# Slot CPLD {{ cpld.slot }}: {{ cpld.program_name }} ({{ cpld.program_id }})
{% endfor %}
