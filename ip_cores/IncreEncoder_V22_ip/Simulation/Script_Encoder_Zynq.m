% Sebastian Wendel

clc;        % command window löschen 
clear;      % alle Variablen löschen 
close all; % alle Fenster schließen

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

SimulationsDauer = 0.3; %0.2%0.02

%Modelzeiten 
%T_c = 125e-6;       %= 8kHz für Siemens 50e-6 = 20Khz bei FOC...%20e-6 = 50Khz bei MPC...167e-6 = ungefähr 6kHz //125e-6 = 8kHz || 50e-6 = 20kHz //Sample time controller und ADC-Messung
%T_mech = 1e-08;    % 100MHz = 1e-08 //Sample time im FPGA Timer0
T_mech = 2e-08;    % 50MHz = 2e-08 //"IncreEncoder_V18" Sample time im FPGA Timer0 da sonst negative SLack-Time im System auftritt
TestDrehzahl_rpm = 5000; %[rpm]
T_Generator = T_mech/100;
f_ISR = 10000; %(10kHz)
%T = T_c;
%T_pwm = T_c;      %100kHz = 10e-6 %%50kHz = 20e-6; ((10e-6;= "ohne_Continous" )// 125e-6 = 8kHz || 50e-6 = 20kHz PWM Period //Sample time for PWM-modulation
%f_pwm = 1/T_pwm;
%f_uC = 150000000;   %Taktfrequenz des Mikrocontrollers (uC)
%PERIOD = f_uC/(f_pwm*2);    %Period-Register für den Mikrocontroller (2 ist drin da PWM-Counter in up-down läuft)

OverSamplingFactor = 6; % Muss zwischen 1 und 6 sein!
OverSamplingFactorInverse = 1/OverSamplingFactor ;
n_max = 6000; %Maximale Drehzahl als Begrenzung
IncPerTurn = 5000; % Bei einem Geber mit 2500 Strichen pro Umdrehung und 2 Spuren mit fallender und steigender Flanke macht das 4*2500
PolePair = 4;

TestDrehzahl_1_s = TestDrehzahl_rpm/60; %[1/s]
Striche_pro_Sekunde = TestDrehzahl_1_s * IncPerTurn;
Periode = 1/Striche_pro_Sekunde; %[s]
if (TestDrehzahl_rpm > 0)
    Phase_Delay_A = -Periode/8;
    Phase_Delay_B = Periode/8;
elseif (TestDrehzahl_rpm <= 0)
    Phase_Delay_A = Periode/8;
    Phase_Delay_B = -Periode/8;
end

SamplesPeriode = Periode/T_Generator;
SamplesPulseWidth = (Periode/T_Generator)/2; %for 50% DutyCycle    
SamplesPhaseDelayA = (Phase_Delay_A/T_Generator);
SamplesPhaseDelayB = (Phase_Delay_B/T_Generator);

