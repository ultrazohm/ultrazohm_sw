open_system('gm_test_delay_compensation_without_delay');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_test_delay_compensation_without_delay/HDL_DUT/Add', 'user1');
annotate_port('gm_test_delay_compensation_without_delay/HDL_DUT/Add', 0, 1, 'cp : 3.239 ns');
