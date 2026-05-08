# {{ option_label }}: {{ choice_label }}
{% if enabled %}
{% for ip in ip_cores %}
set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} {{ ip.instance_name }}]
# Module: {{ ip.module }}
{% endfor %}
{% for port in ports %}
# {{ port.signal }} ({{ port.direction }}) -> {{ port.pin }}
{% endfor %}
{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
{% endif %}
