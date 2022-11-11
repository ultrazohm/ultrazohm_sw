clc
clear
close all

f=100;
time_start=10000;
t_single_late=single(10000:1/10000:(10000+10) );
t_single_zero=single(0:1/10000:(10) );

t_double_late=(10000:1/10000:(10000+10) );
t_double_super_late=(3e12:1/10000:(3e12+10) ); % Should be about 100 years in seconds
t_double_zero=(0:1/10000:(10) );

x_single_late=sin( single(2*pi*f*t_single_late) );
x_single_zero=sin( single(2*pi*f*t_single_zero) );
x_double_late=sin( (2*pi*f*t_double_late) );
x_double_super_late=sin( (2*pi*f*t_double_super_late) );
x_double_zero=sin( (2*pi*f*t_double_zero) );


figure;
subplot(2,1,1)
hold on
grid on
plot(x_single_late);
plot(x_single_zero);
xlim([0 300]);

subplot(2,1,2)
hold on
grid on
plot(x_double_late);
plot(x_double_zero);
plot(x_double_super_late);
xlim([0 300]);


%% Normalize time to prevent float precision problem

t_zero_uint=0:1:10*100e6; % 100 MHz clk
t_zero_form_uint= single(t_zero_uint*1/100e6);

x_single_zero_from_uint=sin( single(2*pi*f*t_zero_form_uint) );
figure
plot(x_single_zero_from_uint);
xlim([0 30000]);
%% 