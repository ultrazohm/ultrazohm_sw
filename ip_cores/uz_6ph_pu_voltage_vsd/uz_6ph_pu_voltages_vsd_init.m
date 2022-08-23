clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =100e3;           % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s


% machine parameters
p = 5;                  % pole pairs

VR = 400;               % Rated eff. line-line voltage in V
IR = 7.071;             % Rated eff. phase current in A
nR = 3000;              % Rated mechanical speed in 1/min

% p.u. base units acc. to T.Geyer, Model predictive control of high power
% converters and industrial drives. Hoboken, NJ, USA: Wiley, 2016, Chapter 2.1.2
VB = sqrt(2/3)*VR; 

% reference values for simulation
v_dc = 565.0;
n_rpm = 3000;
omega_m = n_rpm*pi/30;

% parameters for sine waves
f = n_rpm/60.0*p;     % fundamental frequency

fixdt_type_voltage = fixdt(1,18,15);
fixdt_type_sin_cos = fixdt(1,18,16);