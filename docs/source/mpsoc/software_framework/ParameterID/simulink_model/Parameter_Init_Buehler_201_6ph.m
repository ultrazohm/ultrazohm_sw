%Init Script for 6ph Parameter Identification Simulink Modell

%Author: Valentin Hoppe
%Date 2023

run("Parameter_Init_Buehler_201.m");
addpath('Subsystems','function_references'); 

% VSD Matrix --------------------------------------------------------------
gamma = pi/6;
tl1 = [1  cos(4*gamma) cos(8*gamma)   cos(1*gamma)  cos(5*gamma) cos(9*gamma)];
tl2 = [0  sin(4*gamma) sin(8*gamma)   sin(1*gamma)  sin(5*gamma) sin(9*gamma)];
tl3 = [1  cos(5*4*gamma) cos(5*8*gamma)   cos(5*1*gamma)  cos(5*5*gamma) cos(5*9*gamma)];
tl4 = [0  sin(5*4*gamma) sin(5*8*gamma)   sin(5*1*gamma)  sin(5*5*gamma) sin(5*9*gamma)];
tl5 = [1  cos(3*4*gamma) cos(3*8*gamma)   cos(3*1*gamma)  cos(3*5*gamma) cos(3*9*gamma)];
tl6 = [0  sin(3*4*gamma) sin(3*8*gamma)   sin(3*1*gamma)  sin(3*5*gamma) sin(3*9*gamma)];
c = 2/6*cat(1,tl1,tl2,tl3,tl4,tl5,tl6);
VSD = single(c);
inv_VSD = single(inv(c));

