open_system('gm_uz_pmsm_model_6LUT_pd');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_pmsm_model_6LUT_pd/uz_pmsm_model_6LUT/Tanh1', 'user1');
annotate_port('gm_uz_pmsm_model_6LUT_pd/uz_pmsm_model_6LUT/Tanh1', 0, 1, 'cp : 4.533 ns');
