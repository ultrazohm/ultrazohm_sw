clear
clc;

OriginalData1= '0.csv';%the final output figure name
%load(OriginalData1);
%Data = ScopeData1;
Data = readtable(OriginalData1);
id = Data.CH13_13_id_right;
Ts = 0.000025;
N = length(id);  % 数据长度
time = (0:N-1)' * Ts;
Id = timeseries(id, time);