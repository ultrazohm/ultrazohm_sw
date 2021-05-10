clc
clear
pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');

handle=get_param('uz_axi_testIP','handle');
print(handle,'-dsvg','axi_testip_topview');

handle=get_param('uz_axi_testIP/uz_axi_testIP','handle');
print(handle,'-dsvg','axi_testip_innerview');