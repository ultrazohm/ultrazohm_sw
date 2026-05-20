% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'SwitchInv';
elems(1).DataType = 'Enum: Auswahl_Inverter';

elems(2) = Simulink.BusElement;
elems(2).Name = 'Udc';
elems(2).DataType = 'single';

elems(3) = Simulink.BusElement;
elems(3).Name = 'PT1_Gain';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'PT1_Ts';
elems(4).DataType = 'single';

elems(5) = Simulink.BusElement;
elems(5).Name = 'PT1_reset';
elems(5).DataType = 'boolean';

Bus_Inv_Config = Simulink.Bus;
Bus_Inv_Config.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.SwitchInv = Auswahl_Inverter.PT1; % Standard Inverter Modell ist PT1-Übertragungsglied
data.Udc = 678; % DC link voltage
data.PT1_Gain = 1.0; % Gain for PT1
data.PT1_Ts = 1/(0.5*struct_Ctrl_Config.Value.Tsample); % Time constant for PT1
data.PT1_reset = 0; % Reset value for PT1

struct_Inv_Config = Simulink.Parameter;
struct_Inv_Config.Value = data;
struct_Inv_Config.DataType = 'Bus: Bus_Inv_Config';
struct_Inv_Config.CoderInfo.StorageClass = 'ExportedGlobal';

clear data;