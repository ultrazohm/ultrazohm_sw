open_system('gm_uz_d_inverter_adapter');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'lightblue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_uz_d_inverter_adapter/uz_d_inverter_adapter/PWMdutyFreqDetection_instance1', 'user2');
annotate_port('gm_uz_d_inverter_adapter/uz_d_inverter_adapter/PWMdutyFreqDetection_instance1', 0, 1, 'cp : 5.554 ns');
