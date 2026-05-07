open_system('gm_uz_JL_invModel_PT1');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_JL_invModel_PT1/HDL_DUT/Gain5', 'user1');
annotate_port('gm_uz_JL_invModel_PT1/HDL_DUT/Gain5', 0, 1, 'cp : 2.016 ns');
