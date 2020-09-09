% Sebastian Wendel

clc;        % command window löschen 
clear;      % alle Variablen löschen 
close all; % alle Fenster schließen

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

%% Times
SimulationsDauer = 0.3; %0.2%0.02

T_mech = 1e-08;    % 100MHz = 1e-08 //Sample time im FPGA Timer0
T_Generator = T_mech/100;
f_ISR = 10000; %(10kHz)
% Used FPGA frequency
f_fpga = 100e6; 
f_T_fpga=1/f_fpga;
T_fpga = 1/f_fpga;
% Weitere Frequenzen
f_150MHz = 150e6;   % [Hz] FPGA-Grundfrequenz für 150 MHz
f_100MHz = 100e6;   % [Hz] FPGA-Grundfrequenz für 100 MHz
f_50MHz  = 50e6;     % [Hz] FPGA-Grundfrequenz für 50 MHz
f_25MHz  = 25e6;     % [Hz] FPGA-Grundfrequenz für 25 MHz
f_10MHz  = 10e6;    % [Hz] FPGA-Grundfrequenz für 10 MHz
T_150MHz  = 1/f_150MHz;
T_100MHz  = 1/f_100MHz;
T_50MHz  = 1/f_50MHz;
T_25MHz  = 1/f_25MHz;


%% Configuration

TestDrehzahl_rpm =2021; %[rpm]

OverSamplingFactor = 5; % Muss zwischen 1 und 6 sein!
OverSamplingFactorInverse = 1/OverSamplingFactor ;
OmegaPerOverSampl = 500*((2*pi)/60); %Mit 500rpm Schritten wird der OversaplingFactor erhöht!
n_max = 6000; %Maximale Drehzahl als Begrenzung
IncPerTurn = 5000; % Bei einem Geber mit 2500 Strichen pro Umdrehung und 2 Spuren mit fallender und steigender Flanke macht das 4*2500
PolePair = 4;
QuadratureFactor = 4; %This Factor comes from the fact, that we have an A and B line with rising and falling edge respectively.

TestDrehzahl_1_s = TestDrehzahl_rpm/60; %[1/s]
Striche_pro_Sekunde = TestDrehzahl_1_s * IncPerTurn;
Periode = abs(1/Striche_pro_Sekunde); %[s]
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


