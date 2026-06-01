# -----------------------------------------------------------------------------
# Analog adapter project-level integration
# -----------------------------------------------------------------------------

puts "Applying A-slot analog project-level integration"

{% if has_axi2tcm_note %}
puts "WARNING: {{ axi2tcm_note }}"
{% endif %}

{% for connection in raw_value_connections %}
uz_pw_connect_pin_pair_if_unconnected {{ connection.source_pin }} {{ connection.target_pin }}
{% endfor %}

{% if has_axi2tcm_trigger %}
uz_pw_connect_pin_pair_if_unconnected {{ axi2tcm_trigger_source }} {{ axi2tcm_trigger_target }}
{% endif %}

{% if has_conversion_trigger %}
uz_pw_connect_pins_to_shared_net [list {{ conversion_trigger_pins }}]
{% endif %}
