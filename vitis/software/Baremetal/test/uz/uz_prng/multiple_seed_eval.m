clc
clear

files_halton = dir('halton_*.csv');
files_pcg= dir('pcg_*.csv');
files_squares= dir('squares_*.csv');
files_mtwister= dir('mtwister_*.csv');
files_xoshiro= dir('xoshiro_*.csv');


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

[halton_density_x,halton_density_y]=get_density(halton_mat);




figure
hold on
for i=1:10
plot(halton_density_x{i},halton_density_y{i})
end





function [x,f]=get_density(mat_input)

[f{1},x{1}]=ksdensity(mat_input(:,2) );
[f{2},x{2}]=ksdensity(mat_input(:,4) );
[f{3},x{3}]=ksdensity(mat_input(:,6) );
[f{4},x{4}]=ksdensity(mat_input(:,8) );
[f{5},x{5}]=ksdensity(mat_input(:,10) );
[f{6},x{6}]=ksdensity(mat_input(:,12) );
[f{7},x{7}]=ksdensity(mat_input(:,14) );
[f{8},x{8}]=ksdensity(mat_input(:,16) );
[f{9},x{9}]=ksdensity(mat_input(:,18) );
[f{10},x{10}]=ksdensity(mat_input(:,20) );

end