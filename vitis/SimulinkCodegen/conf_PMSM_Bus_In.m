% Definition Motorparamter für Bus_Config_PMSM
clear elems;

elems(1) = Simulink.BusElement;
elems(1).Name = 'Last_M_Nm';
elems(1).DataType = 'single';

elems(2) = Simulink.BusElement;
elems(2).Name = 'Last_J_kgmsqr';
elems(2).DataType = 'single';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Bremse';
elems(3).DataType = 'boolean';

elems(4) = Simulink.BusElement;
elems(4).Name = 'Udq_V';
elems(4).DataType = 'single';
elems(4).Dimensions = '2';

elems(5) = Simulink.BusElement;
elems(5).Name = 'switchUabc_dq';
elems(5).DataType = 'boolean';


Bus_PMSM_In = Simulink.Bus;
Bus_PMSM_In.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Last_M_Nm = 0.5; % DC link voltage
data.Last_J_kgmsqr = 0; % Gain for PT1
data.Bremse = 0; % Time constant for PT1
data.Udq_V = [0 0];
data.switchUabc_dq = false; 
struct_PMSM_In = Simulink.Parameter;
struct_PMSM_In.Value = data;
struct_PMSM_In.DataType = 'Bus: Bus_PMSM_In';
struct_PMSM_Config.CoderInfo.StorageClass = 'ExportedGlobal';
clear data;