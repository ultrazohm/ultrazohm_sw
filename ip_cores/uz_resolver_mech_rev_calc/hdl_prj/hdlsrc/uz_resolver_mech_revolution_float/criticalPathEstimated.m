open_system('gm_uz_resolver_mech_revolution_float');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/Mod', 'user1');
annotate_port('gm_uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/Mod', 0, 1, 'cp : 3.019 ns');
