open_system('mux_axi');
open_system('gm_mux_axi');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_mux_axi/mux_axi/Subsystem1/Detect Fall Nonpositive2', 'user2');
annotate_port('gm_mux_axi/mux_axi/Subsystem1/Detect Fall Nonpositive2', 1, 1, 'Block not characterized');
hilite_system('mux_axi/mux_axi/Subsystem1/Detect Fall Nonpositive2', 'user2');
annotate_port('mux_axi/mux_axi/Subsystem1/Detect Fall Nonpositive2', 1, 1, 'Block not characterized');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_mux_axi/mux_axi/Subsystem1/Detect Rise Positive', 'user2');
annotate_port('gm_mux_axi/mux_axi/Subsystem1/Detect Rise Positive', 1, 1, 'Block not characterized');
hilite_system('mux_axi/mux_axi/Subsystem1/Detect Rise Positive', 'user2');
annotate_port('mux_axi/mux_axi/Subsystem1/Detect Rise Positive', 1, 1, 'Block not characterized');
