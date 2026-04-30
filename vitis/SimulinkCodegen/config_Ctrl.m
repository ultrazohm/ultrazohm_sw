% Definition Motorparamter für Bus_Config_PMSM
clear elems;
i = 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Tsample';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'T_PWM';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'TNi';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'KPi';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'TEi';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'TNn';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'KPn';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'n_hyst_upperlimit';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'n_hyst_lowerlimit';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 't_traj';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'IGBT_dc_min';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'IGBT_deadtime';
elems(i).DataType = 'single';


Bus_Ctrl_Config = Simulink.Bus;
Bus_Ctrl_Config.Elements = elems;
clear i;
clear elems;
% --- Parameter-Definition (Die Werte) ---
clear data;

data.Tsample = 1/10000;    % Frequenz Regelung
data.T_PWM = 1/10000;      % PWM Frequenz
data.TNi     = struct_PMSM_Config.Value.mot_Ld / struct_PMSM_Config.Value.mot_R1;
data.KPi = struct_PMSM_Config.Value.mot_R1 * data.TNi / (data.T_PWM + data.Tsample);
data.TEi = data.T_PWM + data.Tsample;
data.TNn = 4 * data.TEi;
data.KPn = 0.5 * 2 * pi * (struct_PMSM_Config.Value.mot_J+struct_PMSM_In.Value.Last_J) / data.TEi;
data.n_hyst_upperlimit = struct_PMSM_Config.Value.mot_n_N/60/2/pi/100*1.01; % Hysterese Drehzahlregler: 1% des Sollwerts
data.n_hyst_lowerlimit = -data.n_hyst_upperlimit;
data.t_traj = 0.2; % Zeit bis Ende Plateau Trapez
data.IGBT_dc_min = 5e-6; %minimale Einschaltzeit IGBT
data.IGBT_deadtime = 5e-7 ; % IGBT Totzeit zwischen Top und Bot Schalter

struct_Ctrl_Config = Simulink.Parameter;
struct_Ctrl_Config.Value = data;
struct_Ctrl_Config.DataType = 'Bus: Bus_Ctrl_Config';
struct_Ctrl_Config.CoderInfo.StorageClass = 'ExportedGlobal';
clear data;
% ctrl_Tsample = 1/10000;
% ctrl_TNi = mot_Ld / mot_R1;
% ctrl_KPi = mot_R1 * ctrl_TNi / (pwr_Tpwm + ctrl_Tsample);
% ctrl_Tdelta = pwr_Tpwm*0.5 + ctrl_Tsample*0.5;
% ctrl_TEi = pwr_Tpwm + ctrl_Tsample;
% ctrl_TNn = 4 * ctrl_TEi;
% ctrl_KPn = 0.5 * 2 * pi * J_ges / ctrl_TEi;