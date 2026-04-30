% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'En_Traj';
elems(1).DataType = 'boolean';

elems(2) = Simulink.BusElement;
elems(2).Name = 'Pulsfreigabe';
elems(2).DataType = 'boolean';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Ist_Status';
elems(3).DataType = 'Enum: Status_Ctrl';

elems(4) = Simulink.BusElement;
elems(4).Name = 'Ist_Regelungsart';
elems(4).DataType = 'Enum: Soll_Regelungsart_en';

elems(5) = Simulink.BusElement;
elems(5).Name = 'Soll_Drehzahl';
elems(5).DataType = 'single';

elems(6) = Simulink.BusElement;
elems(6).Name = 'Soll_id';
elems(6).DataType = 'single';

elems(7) = Simulink.BusElement;
elems(7).Name = 'Soll_iq';
elems(7).DataType = 'single';

Bus_ZM_Out = Simulink.Bus;
Bus_ZM_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.En_Traj = false; % Standard Inverter Modell ist PT1-Übertragungsglied
data.Pulsfreigabe = false; % DC link voltage
data.Ist_Status = Status_Ctrl.Ready; % Gain for PT1
data.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; % Time constant for PT1
data.Soll_Drehzahl = 0; % Reset value for PT1
data.Soll_id = 0;
data.Soll_iq = 0;

struct_ZM_Out = Simulink.Parameter;
struct_ZM_Out.Value = data;
struct_ZM_Out.DataType = 'Bus: Bus_ZM_Out';
struct_ZM_Out.CoderInfo.StorageClass = 'ExportedGlobal';

clear data;