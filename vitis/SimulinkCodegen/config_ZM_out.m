% Definition Motorparamter für Bus_Config_PMSM
clear elems;
i=1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Pulsfreigabe';
elems(i).DataType = 'boolean';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Ist_Status';
elems(i).DataType = 'Enum: Status_Ctrl';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Ist_Regelungsart';
elems(i).DataType = 'Enum: Soll_Regelungsart_en';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Drehzahl_Umin';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_id_A';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_iq_A';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'pwr_en';
elems(i).DataType = 'boolean';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'board_en';
elems(i).DataType = 'boolean';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'reset';
elems(i).DataType = 'boolean';
i = i +1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Drehzahl_CB_Grads';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Winkel_CB_Grad';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Beschleunigung_CB_Grads2';
elems(i).DataType = 'single';

i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Trapez_Phase';
elems(i).DataType = 'single';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Modus_Position';
elems(i).DataType = 'Enum: Modus_Position';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'Strom_gesperrt';
elems(i).DataType = 'boolean';


Bus_ZM_Out = Simulink.Bus;
Bus_ZM_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Pulsfreigabe = false; % DC link voltage
data.Ist_Status = Status_Ctrl.Ready; % Gain for PT1
data.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; % Time constant for PT1
data.Soll_Drehzahl_Umin = 0; % Reset value for PT1
data.Soll_id_A = 0;
data.Soll_iq_A = 0;
data.pwr_en = false;
ddata.board_en = false;
data.reset = false;
data.Soll_Drehzahl_CB_Grads = 0;
data.Soll_Winkel_CB_Grad = 0;
data.Soll_Beschleunigung_CB_Grads2 = 0;
data.Trapez_Phase = 0;
data.Modus_Position = Modus_Position.Warten;
data.Strom_gesperrt = false;

struct_ZM_Out = Simulink.Parameter;
struct_ZM_Out.Value = data;
struct_ZM_Out.DataType = 'Bus: Bus_ZM_Out';
struct_ZM_Out.CoderInfo.StorageClass = 'ExportedGlobal';

clear data;