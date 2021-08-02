clc
clear
pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');

handle=get_param('uz_plantModel_pt1','handle');
print(handle,'-dsvg','uz_plantModel_pt1_top');

handle=get_param('uz_plantModel_pt1/uz_plantModel_pt1','handle');
print(handle,'-dsvg','uz_plantModel_pt1_inside');