% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'pmsm_Iuvw';
elems(1).DataType = 'single';
elems(1).Dimensions = '3';

elems(2) = Simulink.BusElement;
elems(2).Name = 'pmsm_Omega_mech';
elems(2).DataType = 'single';

elems(3) = Simulink.BusElement;
elems(3).Name = 'pmsm_phi_mech';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'pmsm_m_mot';
elems(4).DataType = 'single';

Bus_PMSM_Out = Simulink.Bus;
Bus_PMSM_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.pmsm_Iuvw = [0,0,0]; % Standard Inverter Modell ist PT1-Übertragungsglied
data.pmsm_Omega_mech = 0; % DC link voltage
data.pmsm_phi_mech = 0; % Gain for PT1
data.pmsm_m_mot = 0; % Time constant for PT1

struct_PMSM_Out = Simulink.Parameter;
struct_PMSM_Out.Value = data;
struct_PMSM_Out.DataType = 'Bus: Bus_PMSM_Out';
clear data;