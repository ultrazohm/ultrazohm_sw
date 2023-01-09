open_system('gm_uz_pmsm_model');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_pmsm_model/uz_pmsm_model_3ph_dq/Product8', 'user1');
annotate_port('gm_uz_pmsm_model/uz_pmsm_model_3ph_dq/Product8', 0, 1, 'cp : 5.196 ns');
