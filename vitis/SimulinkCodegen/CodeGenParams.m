% theoretische Parameter
R_s     = 0.079;                % [Ohm]
L_d     = 1.12e-3;               % [H]
L_q     = 2.75e-3;               % [H]
Psi_PM  = 0.08;                 % [Vs]
z_P     = 4;                    % [-]
f_pwm = 10e3;

T_sample = 1/f_pwm;
T_ab = T_sample;
%T_STEP = T_sample; 

L = (L_d + L_q)/2;
R = R_s;
T = L/R;
V = 1/R;
z_inf = exp(-T_ab/T);
z_inf_d = exp(-T_ab/(L_d/R));
z_inf_q = exp(-T_ab/(L_q/R));

% voltage source inverter system parameter
T_VSI = 1.5 * T_ab;     % time constant voltage source inverter (basically time constant of current controller)
K_VSI = 1;				% enumerator constant VSI

% V_R = T/(2*T_VSI*V*K_VSI);
% T_N = T;

V_R_d = 6; %T/(2*T_VSI*V*K_VSI);
T_N_d = 6/250;%T;

V_R_q = 6; %T/(2*T_VSI*V*K_VSI);
T_N_q = 6/250;%T;

%% ILR
% d-Impulsantwort
ILR_InvImp_d = getInvImp(z_inf_d,V,T_N_d,V_R_d,T_ab); 

% q-Impulsantwort
ILR_InvImp_q = getInvImp(z_inf_q,V,T_N_q,V_R_q,T_ab); 

% k = 0;
% i = 12;
% while i < 400
%     k = 1+k;
%     vec(k) = i;
%     i = floor(i*1.1);
% end
% vec(k+1) = 400;
% vec = flip(round(vec));
% ILR_NVec = vec;

ILR_learnFactor = 0.3; 
ILR_unlearnFactor = 0.001; 
FOC_ENABLE_HC = 0; 
FOC_RESET_ILR = 0; 
FOC_READ_ILR_Memory = 0; 

% ILR_NVec
% n_mech = 1000; 
% N_act = round(f_pwm*60/n_mech/z_P); 
% n_mech_act = f_pwm*60/N_act/z_P; 
% ILR_NVec = [N_act+50 N_act N_act-50]; 
ILR_NVec = [350 300 250 200 150 100 75 50 25];

correctionCurve_ini_d = zeros(length(ILR_NVec),max(ILR_NVec)); 
correctionCurve_ini_q = zeros(length(ILR_NVec),max(ILR_NVec)); 

%%
function [ILR_InvImp] = getInvImp(z_inf,V,T_N,V_R,T_s)

% z_inf,V --> Parameters of discrete PT1 Motormodell
% T_N, V_R --> Parameters of ideal PI-Currentcontroller
% T_s --> Samplingtime

%G_OL coefficients
a = (1-z_inf)*T_N*V_R*V;
b = (T_s - T_N + T_N*z_inf-T_s*z_inf)*V_R*V;
c = T_N; 
d = (-1-z_inf)*T_N;
e = T_N*z_inf;

%G_CL 
a_s = [0,    1,    0;...
       0,    0,    1;...
       (-b/c), (-(a+e)/c), (-d/c)];
b_s = [0;0;1];
c_s = [(b/c), (a/c), 0];
sys = ss(a_s,b_s, c_s,0,-1);

%plot system impulse response
[y,t] = impulse(sys);

L = 7; %L = Delta + Lambda (Wagner Diss 1998)
Delta = 3; % Delta is the delay between w[k] and y[k] in sample steps

r = zeros(1,L+1);
M_f = toeplitz(y,r);
ys= size(y,1);
v = zeros(ys,1);
v(Delta+1) = 1;
InvImp_toep = M_f\v; %InvImp is called beta in the equation
% figure
% stem(InvImp_toep)
% title('system inverse impulse response via Toeplitz');
ILR_InvImp = InvImp_toep'; 
end

