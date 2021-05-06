load_system('uz_interlockDeadtime2L');
handle=get_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L','handle');
print(handle,'-dsvg','uz_interlockDeadtime2L');

handle=get_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/DeadtimeModule','handle');
print(handle,'-dsvg','deadtime_module');

handle=get_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/InterlockModule','handle');
print(handle,'-dsvg','interlock_module1');

handle=get_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/InverseBotSwitchModule','handle');
print(handle,'-dsvg','inverse_bottom_switch');

handle=get_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/EnableOutputModule','handle');
print(handle,'-dsvg','enable_output');