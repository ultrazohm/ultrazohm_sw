open_system('gm_uz_pmsm_model');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_pmsm_model/uz_pmsm_model/Tanh12', 'user1');
annotate_port('gm_uz_pmsm_model/uz_pmsm_model/Tanh12', 0, 1, 'cp : 4.533 ns');
