open_system('gm_uz_inverter_3phgm');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_inverter_3phgm/uz_inverter_3ph/Output Sum', 'user1');
annotate_port('gm_uz_inverter_3phgm/uz_inverter_3ph/Output Sum', 0, 1, 'cp : 3.239 ns');
