% Sebastian Wendel

clc;        % command window löschen 
clear;      % alle Variablen löschen 
close all; % alle Fenster schließen

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

%% Times
SimulationsDauer = 1.7e-3%0.3; %0.2%0.02

T_mech = 1e-08;    % 100MHz = 1e-08 //Sample time im FPGA Timer0
T_Generator = T_mech/100;
f_ISR = 40e3; 
% Used FPGA frequency
f_fpga = 100e6; 
T_fpga = 1/f_fpga;

%% HDL Coder Settings
reciprocal_iterations = 3; % 1/u in speed calculation
speed_timeout_in_s = 0.05e-3;
inital_zero_speed_timeout = speed_timeout_in_s*f_fpga;%after how many FPGA_Clocks ticks the speed calculation times out and jumps to zero

%% Configuration

TestDrehzahl_rpm = 3000; %[rpm]

OmegaPerOverSampl = 1500*((2*pi)/60); %in diesen Schritten wird der OversaplingFactor erhöht!
n_max = 6000; %maximum speed - not used in IP Core
IncPerTurn = 1024; % e.g. number of positive A edges
PolePair = 1;
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

%% read ila data
% opts = detectImportOptions('iladata_encoder.csv');
% iladata = readmatrix('iladata_encoder.csv');
% iladata = readmatrix('iladata_sw2.csv');
% iladata = readmatrix('iladata_sw3.csv');
% iladata = readmatrix('iladata_el.csv');
% iladata = readmatrix('iladata_el2.csv');
iladata = readmatrix('iladata_el3.csv');

A_ila = iladata(:,4);
B_ila = iladata(:,5);
% I_ila = iladata(:,7); % for all < el3
I_ila = iladata(:,6);

% SimulationsDauer = size(A_ila,1)* T_mech;

%% plots
figure(10)
ylim ([-0.1 1.1])
plot(A_ila,'LineWidth',2)
hold on
plot(B_ila)

A_diff = diff(A_ila);
B_diff = diff(B_ila);

 plot(A_diff)
% plot(B_diff)

A_diff_pos = A_diff; 
A_diff_pos(A_diff<0)=0;

B_diff_pos = B_diff; 
B_diff_pos(B_diff<0)=0;

A_diff_neg = A_diff; 
A_diff_neg(A_diff>0)=0;
A_diff_neg = abs(A_diff_neg);

B_diff_neg = B_diff; 
B_diff_neg(B_diff>0)=0;
B_diff_neg = abs(B_diff_neg);

figure(11)
hold on
ylim ([-0.1 1.1])
plot(A_diff_pos)
plot(B_diff_pos)
plot(A_diff_neg)
plot(B_diff_neg)

%%
close all

a_index= find(A_diff);
a_window = diff(a_index);
b_index= find(B_diff);
b_window = diff(b_index);

a_win_neg = diff(find(A_diff_neg));
b_win_neg = diff(find(B_diff_neg));
a_win_pos = diff(find(A_diff_pos));
b_win_pos = diff(find(B_diff_pos));

figure(21)
hold on
plot(a_win_neg)
plot(b_win_neg)
plot(a_win_pos)
plot(b_win_pos)
legend('a neg','b neg','a pos','b pos')
%% interleaved
win_length = min([size(a_win_neg,1), size(a_win_pos,1), size(b_win_neg,1), size(b_win_pos,1)]);

interleaved_windows_mat = [a_win_neg(1:win_length), b_win_neg(1:win_length), ...
    a_win_pos(1:win_length), b_win_pos(1:win_length)];
interleaved_windows_trans = interleaved_windows_mat';
interleaved_windows = interleaved_windows_trans(:);

figure(22)
plot(interleaved_windows);

close all