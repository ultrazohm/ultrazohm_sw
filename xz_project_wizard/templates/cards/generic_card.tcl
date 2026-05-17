# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

{% for ip in ip_cores %}
set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} {{ ip.instance_name }}]
# Module: {{ ip.module }}
{% endfor %}

{% for interface in interfaces %}
# Create interface pin {{ interface.name }} with VLNV {{ interface.vlnv }}
{% endfor %}

{% for port in ports %}
# {{ port.signal }} ({{ port.direction }}) -> {{ port.pin }}
{% endfor %}

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
