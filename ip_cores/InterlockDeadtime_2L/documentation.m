handle=get_param('interlock_deadtime/interlock_deadtime','handle');
print(handle,'-dsvg','interlock_deadtime');

handle=get_param('interlock_deadtime/interlock_deadtime/DeadtimeModule','handle');
print(handle,'-dsvg','deadtime_module');

handle=get_param('interlock_deadtime/interlock_deadtime/InterlockModule','handle');
print(handle,'-dsvg','interlock_module1');

handle=get_param('interlock_deadtime/interlock_deadtime/InverseBotSwitchModule','handle');
print(handle,'-dsvg','inverse_bottom_switch');

handle=get_param('interlock_deadtime/interlock_deadtime/EnableOutputModule','handle');
print(handle,'-dsvg','enable_output');