open_system('gm_UZ_EnDat');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_UZ_EnDat/UZ_ENDAT_ABZ_ADDON/Mod1', 'user1');
annotate_port('gm_UZ_EnDat/UZ_ENDAT_ABZ_ADDON/Mod1', 0, 1, 'cp : 3.359 ns');
