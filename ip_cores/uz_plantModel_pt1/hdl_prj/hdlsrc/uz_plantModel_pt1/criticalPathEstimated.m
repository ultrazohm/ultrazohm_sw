open_system('gm_uz_plantModel_pt1');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_plantModel_pt1/uz_plantModel_pt1/Product', 'user1');
annotate_port('gm_uz_plantModel_pt1/uz_plantModel_pt1/Product', 0, 1, 'cp : 3.722 ns');
