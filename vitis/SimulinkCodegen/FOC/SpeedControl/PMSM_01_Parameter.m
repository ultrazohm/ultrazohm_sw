%Script to declare parameters

%Motor parameters
zp = 21;                     %Number of polepairs
Lq = 16e-6;                  %H
Ld = Lq;                     %H
psi_pm = 0.0048;              %Vs
R = 0.040;                   %Ohm Strangwiderstand
J_M = 0.0025;                %kg m²
U_DC = 46;                   %V
%U_maxDQ = U_DC/sqrt(3);
I_max = 50;                 %A


%Inverter parameters
f_switchingInverter = 10000;            %Triangle signal frequency
f_MCU_PWM = 10e6;                       %Inverter frequency
T_dead = 2e-6;                        %Safety dead time of inverter
Capacitance_CircuitCondensator = 500e-6;%uF, Intermediate circuit condensator


%Controller Frequencies
f_CurrentController = 20000;            %Current and speed controller
T_controller = 1/f_CurrentController;
T_speedController = T_controller;

%PI-CurrentController (BO)
T_sigma = 0.5/f_switchingInverter + T_controller;
%T_sigma_cont = 0.5/f_switchingInverter;

%Iq_Controller - BO
%Kp_IqController = (Lq/R)/(2*T_sigma*1/R);
%Ki_IqController = R/Lq;
%Id_Controller - BO
%Kp_IdController = (Ld/R)/(2*T_sigma*1/R);
%Ki_IdController = R/Ld;

%Iq_Controller - TI: Set Current Bandwidth
BW = 400;
Kp_IqController = Lq*2*pi*BW;
Ki_IqController = R/Lq;
%Id_Controller - TI
Kp_IdController = Ld*2*pi*BW;
Ki_IdController = R/Ld;

%Parallel Controller transfer function
Kp_IqController = Kp_IqController;
Ki_IqController = Kp_IqController * Ki_IqController;
Kp_IdController = Kp_IdController;
Ki_IdController = Kp_IdController * Ki_IdController;

%Iq_Controller - TI: Set Speed Bandwidth
%BW_Speed = 150*2*pi;
%damping_factor = 6;
%BW_Current = BW_Speed*(damping_factor+2.16*exp(-damping_factor/2.8)-1.86);
%Kp_IqController = Lq*2*pi*BW_Current;
%Ki_IqController = R/Lq;
%Id_Controller - TI
%Kp_IdController = Ld*2*pi*BW_Current;
%Ki_IdController = R/Ld;


%Speed_Controller
%T1 = J_M*2*pi/(3*zp*psi_pm*30);
%T_summe = 2*T_sigma + T_speedController;
%Kp_SpeedController = T1/(2*T_summe);
%Ki_SpeedController = 1/(4*T_summe);

%Speed_Controller - TI: Set current Bandwidth
damping_factor = 6;
K = 3*30*zp*psi_pm/(2*J_M*pi);
Kp_SpeedController = Kp_IqController/(Lq*damping_factor*K);
Ki_SpeedController = Kp_IqController/(Lq*damping_factor^2);

%Parallel controller formulation
Kp_SpeedController = Kp_SpeedController;
Ki_SpeedController = Kp_SpeedController * Ki_SpeedController;

%Speed_Controller - TI: Set speed Bandwidth
% K = 3/2*zp*psi_pm/J_M;
% Kp_SpeedController = Kp_IqController/(Lq*damping_factor*K);
% Ki_SpeedController = Kp_IqController/(Lq*damping_factor^2);


%Discrete Prefilter Speed Controller
%T_filterC_speed = 4*T_summe;
%G_Gc_speed = tf([1],[T_filterC_speed 1]);
%G_Gd_speed = c2d(G_Gc_speed, T_speedController, 'tustin');
%[num_Gd_speed, denum_Gd_speed] = tfdata(G_Gd_speed, 'v');

%Torque_Controller
%T1_Torque = J_M*pi/30;
%T_summe_Torque = 2*T_sigma + T_speedController;
%Kp_TorqueController = T1_Torque/(2*T_summe_Torque);
%Ki_TorqueController = 1/(4*T_summe_Torque);

%Discrete Prefilter Torque Controller
%T_filterC_trq = 4*T_summe_Torque;
%G_Gc_trq = tf([1],[T_filterC_trq 1]);
%G_Gd_trq = c2d(G_Gc_trq, T_speedController, 'tustin');
%[num_Gd_trq, denum_Gd_trq] = tfdata(G_Gd_trq, 'v');