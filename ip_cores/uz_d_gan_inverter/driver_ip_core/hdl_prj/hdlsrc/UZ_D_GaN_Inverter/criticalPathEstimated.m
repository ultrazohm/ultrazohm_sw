open_system('gm_UZ_D_GaN_Inverter');
cs.HiliteType = 'user2';
cs.ForegroundColor = 'black';
cs.BackgroundColor = 'lightblue';
set_param(0, 'HiliteAncestorsData', cs);
hilite_system('gm_UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutyFreqDetection_instance1', 'user2');
annotate_port('gm_UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutyFreqDetection_instance1', 0, 1, 'cp : 5.554 ns');
