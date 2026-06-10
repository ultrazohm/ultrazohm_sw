clc
clear
pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');

handle=get_param('uz_pmsm_model_nonlinear','handle');
print(handle,'-dsvg','pmsm_model_nonlinear');

handle=get_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear','handle');
print(handle,'-dsvg','pmsm_model_nonlinear_inside');

handle=get_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/pmsm','handle');
print(handle,'-dsvg','pmsm_model_nonlinear_inside_pmsm');


handle=get_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/torque_calculation','handle');
print(handle,'-dsvg','pmsm_model_nonlinear_inside_torque');


handle=get_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mechanical_system','handle');
print(handle,'-dsvg','pmsm_model_nonlinear_inside_mechanical');