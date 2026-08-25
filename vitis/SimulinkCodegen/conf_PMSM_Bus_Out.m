% Definition Motorparamter für Bus_Config_PMSM
clear elems;

i = 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_Iuvw_P_A';
elems(i).DataType = 'single';
elems(i).Dimensions = '3';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_Iuvw_I_A';
elems(i).DataType = 'single';
elems(i).Dimensions = '3';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_Omega_mech_rad_s';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_Omega_el_rad_s';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_theta_mech_rad';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_theta_el_rad';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pmsm_m_mot_Nm';
elems(i).DataType = 'single';

Bus_PMSM_Out = Simulink.Bus;
Bus_PMSM_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.pmsm_Iuvw_P_A = [0,0,0]; 
data.pmsm_Iuvw_I_A = [0,0,0]; 
data.pmsm_Omega_mech_rad_s = 0; % DC link voltage
data.pmsm_Omega_el_rad_s = 0;
data.pmsm_theta_mech_rad = 0; % Gain for PT1
data.pmsm_theta_el_rad = 0;
data.pmsm_m_mot_Nm = 0; % Time constant for PT1

struct_PMSM_Out = Simulink.Parameter;
struct_PMSM_Out.Value = data;
struct_PMSM_Out.DataType = 'Bus: Bus_PMSM_Out';
clear data;