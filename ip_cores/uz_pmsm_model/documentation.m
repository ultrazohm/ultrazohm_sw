clc
clear
pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');

handle=get_param('uz_pmsm_model','handle');
print(handle,'-dsvg','pmsm_model');

handle=get_param('uz_pmsm_model/uz_pmsm_model','handle');
print(handle,'-dsvg','pmsm_model_inside');

handle=get_param('uz_pmsm_model/uz_pmsm_model/pmsm','handle');
print(handle,'-dsvg','pmsm_model_inside_pmsm');


handle=get_param('uz_pmsm_model/uz_pmsm_model/torque_calculation','handle');
print(handle,'-dsvg','pmsm_model_inside_torque');


handle=get_param('uz_pmsm_model/uz_pmsm_model/mechanical_system','handle');
print(handle,'-dsvg','pmsm_model_inside_mechanical');