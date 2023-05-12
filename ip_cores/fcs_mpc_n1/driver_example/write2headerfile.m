%% this script creates a header file that can be included in the vitis project
% the header file includes the parameters of the discretized state matrices A and B

P_ab   = 2/3*[1,-1/2,-1/2;0,sqrt(3)/2,-sqrt(3)/2]; % abc -> alpha-beta transformation

isdouble = 1;
%% open file
fid = fopen('plant_model_from_matlab.h','w');

%% A
variable = A;
head = 'double A_mat[4][4] = {';
write_matrix2file(variable, head, fid, isdouble);

%% B in abc
variable = B*P_ab;
head = 'double B_mat[4][3] = {';
write_matrix2file(variable, head, fid, isdouble);

%% close file
fclose(fid);


