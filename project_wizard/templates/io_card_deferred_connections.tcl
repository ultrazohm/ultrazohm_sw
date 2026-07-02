# -----------------------------------------------------------------------------
# IO card deferred cross-slot and top-level output connections
# -----------------------------------------------------------------------------
# All IO card hierarchies and parent boundary pins have been placed before this
# pass runs. This keeps custom BD source routing independent of slot order.

puts "Project Wizard: connecting deferred IO card routes"

{% for connection in connections %}
# {{ connection.slot }} {{ connection.pin_name }} <= {{ connection.source_path }}
uz_pw_connect_pin_pair_if_unconnected {{ connection.source_path }} {{ connection.parent_pin_path }}
uz_pw_connect_port_if_unconnected {{ connection.parent_pin_path }} {{ connection.pin_name }}
{% endfor %}
