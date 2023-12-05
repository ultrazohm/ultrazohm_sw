open_system('uz_pmsm_model_6LUT_pd');
open_system('gm_uz_pmsm_model_6LUT_pd');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_pmsm_model_6LUT_pd/uz_pmsm_model_6LUT/Product7_to_gain', 'user2');
annotate_port('gm_uz_pmsm_model_6LUT_pd/uz_pmsm_model_6LUT/Product7_to_gain', 1, 1, 'Block not characterized for this configuration');
