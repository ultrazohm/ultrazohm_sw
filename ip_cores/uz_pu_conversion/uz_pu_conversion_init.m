clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;    % IP core clock freq in Hz
ts = 1/f_clock;     % IP core sample time in s

f_ADC =100e3;       % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;    % ADC sample time in s

pu_fixdt_type = fixdt(1,18,15); % output data type of pu values

% rated values of a maschine

    % voltage
    V_R = 400;      % terminal_eff
    % current
    I_R = 100;      % A_eff
    % angular frequency (electrical)
    ws_R = 104.7;   % rad/s
    % resistance, reactance, impedance
    Rph = 0.1;      % Ohm
    % inductance
    L_R = 1e-3;     % Henry
    % power factor
    pf = 1;
    % pole pairs
    p = 2;


% pu base values (Tobias Geyer - Model Predictive Control of High Power
% Converters and Industrial Drives, Table 2.1)

    % voltage
    V_B = sqrt(2/3)*V_R;      
    % current
    I_B = sqrt(2)*I_R;
    % angular frequency (electrical)
    w_B = ws_R;
    % resistance, reactance, impedance
    Z_B = V_B/I_B;
    % inductance
    L_B = Z_B/w_B;
    % capacitance
    C_B = 1/(w_B*Z_B);
    % apparent power
    S_B = 3/2*V_B*I_B;
    % flux linkage
    lambda_B = V_B/w_B;
    % torque
    T_B = pf*p*S_B/w_B;
    
    
    
ampl = 100*sqrt(2); % A
freq_Hz = 100;      % Hz
v_dc = 565;         % volt
