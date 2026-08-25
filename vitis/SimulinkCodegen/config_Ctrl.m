% Definition Motorparamter für Bus_Config_PMSM (parallele PI-Reglerform)
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
elems(i).Name = 'KIi';
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
elems(i).Name = 'KIn';
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

i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'sel_act_I';
elems(i).DataType = 'boolean';

Bus_Ctrl_Config = Simulink.Bus;
Bus_Ctrl_Config.Elements = elems;

clear i;
clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Tsample = 1/10000;    % Frequenz Regelung
data.T_PWM = 1/10000;      % PWM Frequenz

% --- Stromregler (Betragsoptimum) ---
data.TNi = struct_PMSM_Config.Value.mot_Ld_H / struct_PMSM_Config.Value.mot_R_PH_Ohm;
data.KPi = struct_PMSM_Config.Value.mot_R_PH_Ohm * data.TNi / (data.T_PWM + data.Tsample);
data.TEi = data.T_PWM + data.Tsample;% + 9.45e-6 + 0.2e-6;
data.KIi = data.KPi / data.TNi;    % Ki für parallele Form (= mot_R1 / TEi)

% --- Drehzahlregler (Symmetrisches Optimum) ---
data.TNn = 8 * data.TEi;
data.KPn = 0.5;%0.5 * 2 * pi * (struct_PMSM_Config.Value.mot_J_kgmsqr + struct_PMSM_In.Value.Last_J_kgmsqr) / (2*data.TEi);
data.KIn = 2;% data.KPn / data.TNn;    % Ki für parallele Form

data.n_hyst_upperlimit = struct_PMSM_Config.Value.mot_n_N_Umin/60/2/pi/100*1.0001; % Hysterese Drehzahlregler: 1% des Sollwerts
data.n_hyst_lowerlimit = -data.n_hyst_upperlimit;
data.t_traj = 0.2; % Zeit bis Ende Plateau Trapez
data.IGBT_dc_min = 0; %minimale Einschaltzeit IGBT
data.IGBT_deadtime = 0 ; % IGBT Totzeit zwischen Top und Bot Schalter
data.sel_act_I = false;

struct_Ctrl_Config = Simulink.Parameter;
struct_Ctrl_Config.Value = data;
struct_Ctrl_Config.DataType = 'Bus: Bus_Ctrl_Config';
struct_Ctrl_Config.CoderInfo.StorageClass = 'ExportedGlobal';
clear data;

% ctrl_Tsample = 1/10000;
% ctrl_TNi = mot_Ld / mot_R1;
% ctrl_KPi = mot_R1 * ctrl_TNi / (pwr_Tpwm + ctrl_Tsample);
% ctrl_KIi = ctrl_KPi / ctrl_TNi;
% ctrl_Tdelta = pwr_Tpwm*0.5 + ctrl_Tsample*0.5;
% ctrl_TEi = pwr_Tpwm + ctrl_Tsample;
% ctrl_TNn = 4 * ctrl_TEi;
% ctrl_KPn = 0.5 * 2 * pi * J_ges / ctrl_TEi;
% ctrl_KIn = ctrl_KPn / ctrl_TNn;