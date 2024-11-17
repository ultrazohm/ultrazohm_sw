clc
clear
close all

current=load('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/d1_current_a.mat');
current.variable_names=regexprep(current.variable_names, 'CH\d+=\(\d+\)\s*', '');
current.log.Properties.VariableNames=current.variable_names;
voltage=load('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/d1_voltage_abgleich.mat');
voltage.variable_names=regexprep(voltage.variable_names, 'CH\d+=\(\d+\)\s*', '');
voltage.log.Properties.VariableNames=voltage.variable_names;

%%
figure
plot(voltage.log.input,voltage.log.d1_phase_voltage_a,'x');


d1_voltage_fit=fitlm(voltage.log.input,voltage.log.d1_phase_voltage_a);
d1_voltage_fit2=polyfit(voltage.log.input,voltage.log.d1_phase_voltage_a,1);
f = polyval(d1_voltage_fit2,voltage.log.input); 
hold on
plot(voltage.log.input,f,'--');

%%
[voltage.log.operating_point, ~] = findgroups(voltage.log.input);
groupedTable = groupsummary(voltage.log, 'operating_point', 'mean');

figure
plot(groupedTable.mean_input,groupedTable.mean_d1_phase_voltage_a,'x');

d1_voltage_fit=fitlm(groupedTable.mean_input,groupedTable.mean_d1_phase_voltage_a);
d1_voltage_fit2=polyfit(groupedTable.mean_input,groupedTable.mean_d1_phase_voltage_a,1);
f = polyval(d1_voltage_fit2,groupedTable.mean_input); 
hold on
plot(groupedTable.mean_input,f,'--');

%%
[voltage.log.operating_point, ~] = findgroups(voltage.log.input);
groupedTable = groupsummary(voltage.log, 'operating_point', 'mean');

figure
plot(groupedTable.mean_d1_phase_voltage_b,groupedTable.mean_input,'x');

d1_voltage_fit=fitlm(groupedTable.mean_d1_phase_voltage_b,groupedTable.mean_input);
d1_voltage_fit2=polyfit(groupedTable.mean_d1_phase_voltage_b,groupedTable.mean_input,1);
f = polyval(d1_voltage_fit2,groupedTable.mean_d1_phase_voltage_b); 
hold on
plot(groupedTable.mean_d1_phase_voltage_b,f,'--');

%%
figure
plot(voltage.log.input,voltage.log.input./voltage.log.d1_phase_voltage_a,'x');
title('This nonlinear behavior is probably due to the offset');
hold on
plot(voltage.log.input,(voltage.log.input-0.0378)./(voltage.log.d1_phase_voltage_a),'o');
%%

[current.log.operating_point, ~] = findgroups(current.log.input);
groupedTable = groupsummary(current.log, 'operating_point', 'mean');

figure
plot(groupedTable.mean_d1_phase_current_a,groupedTable.mean_input,'x');

d1_voltage_fit=fitlm(groupedTable.mean_d1_phase_current_a,groupedTable.mean_input);
d1_voltage_fit2=polyfit(groupedTable.mean_d1_phase_current_a,groupedTable.mean_input,1);
f = polyval(d1_voltage_fit2,groupedTable.mean_d1_phase_current_a); 
hold on
plot(groupedTable.mean_d1_phase_current_a,f,'--');