% init script for uz_pos_to_speed_pll.slx

clc
clear all

%%
PLL.f_S = 10000;        % Hz % sampling frequency
PLL.T_S = 1/PLL.f_S;    % s % sampling time

PLL.fn  =  50;           % Hz closed-loop nominal frequency of PLL
PLL.d   =  1;            %  closed-loop damping factor of PLL
PLL.Ki_Ta = (2*pi*PLL.fn)^2;    % 1/s^2 integral gain of PLL controller
PLL.Kp = 2*PLL.d*2*pi*PLL.fn;   % 1/s proportional gain of PLL controller

motor.p = 2;            % motor pole pair number