open_system('gm_gmStateSpaceHDL_HalfWaveRectifier_HDL');
cs.HiliteType = 'user1';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'blue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_gmStateSpaceHDL_HalfWaveRectifier_HDL/Simscape_system/HDL Subsystem/Output Sum', 'user1');
annotate_port('gm_gmStateSpaceHDL_HalfWaveRectifier_HDL/Simscape_system/HDL Subsystem/Output Sum', 0, 1, 'cp : 4.797 ns');
