open_system('uz_axi_testIP');
open_system('gm_uz_axi_testIP');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_axi_testIP/uz_axi_testIP/transpose', 'user2');
annotate_port('gm_uz_axi_testIP/uz_axi_testIP/transpose', 1, 1, 'Block not characterized');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_axi_testIP/uz_axi_testIP/Reshape', 'user2');
annotate_port('gm_uz_axi_testIP/uz_axi_testIP/Reshape', 1, 1, 'Block not characterized');
hilite_system('uz_axi_testIP/uz_axi_testIP/Reshape', 'user2');
annotate_port('uz_axi_testIP/uz_axi_testIP/Reshape', 1, 1, 'Block not characterized');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_axi_testIP/uz_axi_testIP/Reshape1', 'user2');
annotate_port('gm_uz_axi_testIP/uz_axi_testIP/Reshape1', 1, 1, 'Block not characterized');
hilite_system('uz_axi_testIP/uz_axi_testIP/Reshape1', 'user2');
annotate_port('uz_axi_testIP/uz_axi_testIP/Reshape1', 1, 1, 'Block not characterized');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'gray';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_axi_testIP/uz_axi_testIP/Reshape2', 'user2');
annotate_port('gm_uz_axi_testIP/uz_axi_testIP/Reshape2', 1, 1, 'Block not characterized');
hilite_system('uz_axi_testIP/uz_axi_testIP/Reshape2', 'user2');
annotate_port('uz_axi_testIP/uz_axi_testIP/Reshape2', 1, 1, 'Block not characterized');
