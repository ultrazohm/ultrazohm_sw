clc
clear
close all

files_halton = dir('halton_seed*.csv');
files_pcg= dir('pcg_seed*.csv');
files_squares= dir('squares_seed*.csv');
files_mtwister= dir('mtwister_seed*.csv');
files_xoshiro= dir('xoshiro_seed*.csv');


for i=1:length(files_halton)
    halton{i} = readmatrix(files_halton(i).name); % or csvread(files(i).name)
    halton_mat=cell2mat(halton);
    % process data
end

for i=1:length(files_pcg)
    pcg{i} = readmatrix(files_pcg(i).name); % or csvread(files(i).name)
        pcg_mat=cell2mat(pcg);
    % process data
end

for i=1:length(files_squares)
    squares{i} = readmatrix(files_squares(i).name); % or csvread(files(i).name)
        squares_mat=cell2mat(squares);
    % process data
end

for i=1:length(files_mtwister)
    mtwister{i} = readmatrix(files_mtwister(i).name); % or csvread(files(i).name)
        mtwister_mat=cell2mat(mtwister);
    % process data
end

for i=1:length(files_xoshiro)
    xoshiro{i} = readmatrix(files_xoshiro(i).name); % or csvread(files(i).name)
        xoshiro_mat=cell2mat(xoshiro);
    % process data
end

%%
% Expected values for std, mean, median according to https://de.wikipedia.org/wiki/Stetige_Gleichverteilung
% median=mean= (a+b)/2
a=1;
b=0;

mean_expected=(a+b)/2;
median_expected=mean_expected;

var_expected=1/12*(b-a)^2;
std_deviation=sqrt( var_expected );

%


%%

[halton_density_x,halton_density_y]=get_density(halton_mat);
[pcg_density_x,pcg_density_y]=get_density(pcg_mat);
[squares_density_x,squares_density_y]=get_density(squares_mat);
[mtwister_density_x,mtwister_density_y]=get_density(mtwister_mat);
[xoshiro_density_x,xoshiro_density_y]=get_density(xoshiro_mat);

squares_density=[cell2mat(squares_density_x')' cell2mat(squares_density_y')'];
titles={'squares_density_x_1', 'squares_density_x_2', 'squares_density_x_3', 'squares_density_x_4', 'squares_density_x_5', 'squares_density_x_6', 'squares_density_x_7', 'squares_density_x_8', 'squares_density_x_9', 'squares_density_x_10','squares_density_y_1', 'squares_density_y_2', 'squares_density_y_3', 'squares_density_y_4', 'squares_density_y_5', 'squares_density_y_6', 'squares_density_y_7', 'squares_density_y_8', 'squares_density_y_9', 'squares_density_y_10' };
squares_dens = [titles; num2cell(squares_density)];
writecell(squares_dens,'squares_density.csv');

pcg_density=[cell2mat(pcg_density_x')' cell2mat(pcg_density_y')'];
titles={'pcg_density_x_1', 'pcg_density_x_2', 'pcg_density_x_3', 'pcg_density_x_4', 'pcg_density_x_5', 'pcg_density_x_6', 'pcg_density_x_7', 'pcg_density_x_8', 'pcg_density_x_9', 'pcg_density_x_10','pcg_density_y_1', 'pcg_density_y_2', 'pcg_density_y_3', 'pcg_density_y_4', 'pcg_density_y_5', 'pcg_density_y_6', 'pcg_density_y_7', 'pcg_density_y_8', 'pcg_density_y_9', 'pcg_density_y_10' };
pcg_dens = [titles; num2cell(pcg_density)];
writecell(pcg_dens,'pcg_density.csv');

mtwister_density=[cell2mat(mtwister_density_x')' cell2mat(mtwister_density_y')'];
titles={'mtwister_density_x_1', 'mtwister_density_x_2', 'mtwister_density_x_3', 'mtwister_density_x_4', 'mtwister_density_x_5', 'mtwister_density_x_6', 'mtwister_density_x_7', 'mtwister_density_x_8', 'mtwister_density_x_9', 'mtwister_density_x_10','mtwister_density_y_1', 'mtwister_density_y_2', 'mtwister_density_y_3', 'mtwister_density_y_4', 'mtwister_density_y_5', 'mtwister_density_y_6', 'mtwister_density_y_7', 'mtwister_density_y_8', 'mtwister_density_y_9', 'mtwister_density_y_10' };
mtwister_dens = [titles; num2cell(mtwister_density)];
writecell(mtwister_dens,'mtwister_density.csv');

xoshiro_density=[cell2mat(xoshiro_density_x')' cell2mat(xoshiro_density_y')'];
titles={'xoshiro_density_x_1', 'xoshiro_density_x_2', 'xoshiro_density_x_3', 'xoshiro_density_x_4', 'xoshiro_density_x_5', 'xoshiro_density_x_6', 'xoshiro_density_x_7', 'xoshiro_density_x_8', 'xoshiro_density_x_9', 'xoshiro_density_x_10','xoshiro_density_y_1', 'xoshiro_density_y_2', 'xoshiro_density_y_3', 'xoshiro_density_y_4', 'xoshiro_density_y_5', 'xoshiro_density_y_6', 'xoshiro_density_y_7', 'xoshiro_density_y_8', 'xoshiro_density_y_9', 'xoshiro_density_y_10' };
xoshiro_dens = [titles; num2cell(xoshiro_density)];
writecell(xoshiro_dens,'xoshiro_density.csv');

halton_density=[cell2mat(halton_density_x')' cell2mat(halton_density_y')'];
titles={'halton_density_x_1', 'halton_density_x_2', 'halton_density_x_3', 'halton_density_x_4', 'halton_density_x_5', 'halton_density_x_6', 'halton_density_x_7', 'halton_density_x_8', 'halton_density_x_9', 'halton_density_x_10','halton_density_y_1', 'halton_density_y_2', 'halton_density_y_3', 'halton_density_y_4', 'halton_density_y_5', 'halton_density_y_6', 'halton_density_y_7', 'halton_density_y_8', 'halton_density_y_9', 'halton_density_y_10' };
halton_dens = [titles; num2cell(halton_density)];
writecell(halton_dens,'halton_density.csv');

[pcg_mean,pcg_median,pcg_variance,pcg_std_deviation]=get_stochastic_properties(pcg_mat);
[mtwister_mean,mtwister_median,mtwister_variance,mtwister_std_deviation]=get_stochastic_properties(mtwister_mat);
[squares_mean,squares_median,squares_variance,squares_std_deviation]=get_stochastic_properties(squares_mat);
[halton_mean,halton_median,halton_variance,halton_std_deviation]=get_stochastic_properties(halton_mat);
[xoshiro_mean,xoshiro_median,xoshiro_variance,xoshiro_std_deviation]=get_stochastic_properties(xoshiro_mat);


pcg_stat=cell2mat([pcg_mean',pcg_median',pcg_variance',pcg_std_deviation']);
mtwister_stat=cell2mat([mtwister_mean',mtwister_median',mtwister_variance',mtwister_std_deviation']);
squares_stat=cell2mat([squares_mean',squares_median',squares_variance',squares_std_deviation']);
halton_stat=cell2mat([halton_mean',halton_median',halton_variance',halton_std_deviation']);
xoshiro_stat=cell2mat([xoshiro_mean',xoshiro_median',xoshiro_variance',xoshiro_std_deviation']);

titles_stats={'pcg_mean','pcg_median','pcg_variance','pcg_std_deviation','mtwister_mean','mtwister_median','mtwister_variance','mtwister_std_deviation','squares_mean','squares_median','squares_variance','squares_std_deviation','halton_mean','halton_median','halton_variance','halton_std_deviation','xoshiro_mean','xoshiro_median','xoshiro_variance','xoshiro_std_deviation' };

stat_properties = [titles_stats; [num2cell(pcg_stat) num2cell(mtwister_stat) num2cell(squares_stat) num2cell(halton_stat) num2cell(xoshiro_stat)] ];
writecell(stat_properties,'prng_statistical_properties.csv');

figure

subplot(1,5,1);         
title('Mersenne Twister')
hold on
for i=1:10
plot(mtwister_density_x{i},mtwister_density_y{i})
end
grid on

subplot(1,5,2);         
hold on
for i=1:10
plot(halton_density_x{i},halton_density_y{i})
end
grid on

subplot(1,5,3);         
hold on
for i=1:10
plot(squares_density_x{i},squares_density_y{i})
end
grid on


subplot(1,5,4);         
hold on
for i=1:10
plot(xoshiro_density_x{i},xoshiro_density_y{i})
end
grid on

subplot(1,5,5);         
hold on
for i=1:10
plot(pcg_density_x{i},pcg_density_y{i})
end
grid on




function [mean_value,median_value,variance_value,std_deviation_value]=get_stochastic_properties(mat_input)

mean_value{1}=mean(mat_input(:,2) );
mean_value{2}=mean(mat_input(:,4) );
mean_value{3}=mean(mat_input(:,6) );
mean_value{4}=mean(mat_input(:,8) );
mean_value{5}=mean(mat_input(:,10) );
mean_value{6}=mean(mat_input(:,12) );
mean_value{7}=mean(mat_input(:,14) );
mean_value{8}=mean(mat_input(:,16) );
mean_value{9}=mean(mat_input(:,18) );
mean_value{10}=mean(mat_input(:,20) );

median_value{1}=median(mat_input(:,2) );
median_value{2}=median(mat_input(:,4) );
median_value{3}=median(mat_input(:,6) );
median_value{4}=median(mat_input(:,8) );
median_value{5}=median(mat_input(:,10) );
median_value{6}=median(mat_input(:,12) );
median_value{7}=median(mat_input(:,14) );
median_value{8}=median(mat_input(:,16) );
median_value{9}=median(mat_input(:,18) );
median_value{10}=median(mat_input(:,20) );

variance_value{1}=var(mat_input(:,2) );
variance_value{2}=var(mat_input(:,4) );
variance_value{3}=var(mat_input(:,6) );
variance_value{4}=var(mat_input(:,8) );
variance_value{5}=var(mat_input(:,10) );
variance_value{6}=var(mat_input(:,12) );
variance_value{7}=var(mat_input(:,14) );
variance_value{8}=var(mat_input(:,16) );
variance_value{9}=var(mat_input(:,18) );
variance_value{10}=var(mat_input(:,20) );

std_deviation_value{1}=std(mat_input(:,2) );
std_deviation_value{2}=std(mat_input(:,4) );
std_deviation_value{3}=std(mat_input(:,6) );
std_deviation_value{4}=std(mat_input(:,8) );
std_deviation_value{5}=std(mat_input(:,10) );
std_deviation_value{6}=std(mat_input(:,12) );
std_deviation_value{7}=std(mat_input(:,14) );
std_deviation_value{8}=std(mat_input(:,16) );
std_deviation_value{9}=std(mat_input(:,18) );
std_deviation_value{10}=std(mat_input(:,20) );

end

function [x,f]=get_density(mat_input)

[f{1},x{1}]=ksdensity(mat_input(:,2)    ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{2},x{2}]=ksdensity(mat_input(:,4)    ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{3},x{3}]=ksdensity(mat_input(:,6)    ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{4},x{4}]=ksdensity(mat_input(:,8)    ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{5},x{5}]=ksdensity(mat_input(:,10)   ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{6},x{6}]=ksdensity(mat_input(:,12)   ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{7},x{7}]=ksdensity(mat_input(:,14)   ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{8},x{8}]=ksdensity(mat_input(:,16)   ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{9},x{9}]=ksdensity(mat_input(:,18)   ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
[f{10},x{10}]=ksdensity(mat_input(:,20) ,'Support',[0-eps 1+eps],'BoundaryCorrection','reflection',NumPoints=200);
end