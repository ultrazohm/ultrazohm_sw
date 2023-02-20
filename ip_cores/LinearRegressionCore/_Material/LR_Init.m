%% Setup Sim
%clear;
%clc;

%% Setup Sim
ADC_Freq            = 1e6;
ADC_SampleTime      = 1/ADC_Freq;

StopTime            = 55e-6;

Signal_Freq         = 333;
Signale_Period      = 1/Signal_Freq;
Signal_Amp          = 35;
Signal_Phase        = pi/2;

Noise_Power         = 0.00005;
Noise_SampleTime    = ADC_SampleTime;
Noise_Seed          = 14984651;

Harmonics_Power     = 1/2;

Spike_Level_min     = 10;

% 1= No Noise, 2= White Noise, 3= Harmonic Noise, 4= Spike Noise
Noise_Source        = 4;    

