% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'Uuvw';
elems(1).DataType = 'single';
elems(1).Dimensions = '3';

elems(2) = Simulink.BusElement;
elems(2).Name = 'Last_M';
elems(2).DataType = 'single';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Last_J';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'Bremse';
elems(4).DataType = 'boolean';

Bus_PMSM_In = Simulink.Bus;
Bus_PMSM_In.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Uuvw = [0,0,0]; % Standard Inverter Modell ist PT1-Übertragungsglied
data.Last_M = 2; % DC link voltage
data.Last_J = 0; % Gain for PT1
data.Bremse = 0; % Time constant for PT1

struct_PMSM_In = Simulink.Parameter;
struct_PMSM_In.Value = data;
struct_PMSM_In.DataType = 'Bus: Bus_PMSM_In';
struct_PMSM_Config.CoderInfo.StorageClass = 'ExportedGlobal';
clear data;