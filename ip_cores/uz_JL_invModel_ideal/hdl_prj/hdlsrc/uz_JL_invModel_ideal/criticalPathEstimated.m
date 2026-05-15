open_system('gm_uz_JL_invModel_ideal');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_JL_invModel_ideal/uz_JL_invModel_ideal/Gain', 'user1');
annotate_port('gm_uz_JL_invModel_ideal/uz_JL_invModel_ideal/Gain', 0, 1, 'cp : 1.804 ns');
