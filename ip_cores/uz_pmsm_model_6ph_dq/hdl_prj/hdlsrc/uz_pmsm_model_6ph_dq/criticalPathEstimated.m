open_system('gm_uz_pmsm_model_6ph_dq');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/Product1', 'user1');
annotate_port('gm_uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/Product1', 0, 1, 'cp : 3.596 ns');
