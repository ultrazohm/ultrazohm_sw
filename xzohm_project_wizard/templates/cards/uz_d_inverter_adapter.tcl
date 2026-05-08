# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

# TODO: Create hierarchy uz_pw_slot_{{ slot_lower }} for {{ slot }}.
{% for ip in ip_cores %}
set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} {{ ip.instance_name }}]
# Module: {{ ip.module }}
{% endfor %}

{% for interface in interfaces %}
# TODO: Create and connect interface pin {{ interface.name }} with VLNV {{ interface.vlnv }}.
{% endfor %}

# TODO: Check active constraint files and enable the packed constraint file for {{ slot }}.
{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
