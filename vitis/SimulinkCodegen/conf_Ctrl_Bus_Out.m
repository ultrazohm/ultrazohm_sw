% Definition Motorparamter für Bus_Config_PMSM
clear elems;
i =1;
elems(1) = Simulink.BusElement;
elems(i).Name = 'Dutycycle';
elems(i).DataType = 'single';
elems(i).Dimensions = '3';
i = i + 1;
elems(i) = Simulink.BusElement;
elems(i).Name = 'act_pwm';
elems(i).DataType = 'boolean';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'ctrl_Ualpha_V';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'ctrl_Ubeta_V';
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
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'ZM_Ist_Status';
elems(i).DataType = 'Enum: Status_Ctrl';
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
elems(i).Name = 'Strom_gesperrt';
elems(i).DataType = 'boolean';

Bus_Ctrl_Out = Simulink.Bus;
Bus_Ctrl_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Dutycycle = 0; 
data.act_pwm = 0; 
data.ctrl_Ualpha = 0; 
data.ctrl_Ubeta = 0; 
data.pwr_en = false;
ddata.board_en = false;
data.reset = false;
data.ZM_Ist_Status = Status_Ctrl.Ready;
data.Soll_Drehzahl_CB_Grads = 0;
data.Soll_Winkel_CB_Grad = 0;
data.Soll_Beschleunigung_CB_Grads2 = 0;
data.Trapez_Phase = 0;
data.Strom_gesperrt = false;

struct_Ctrl_Out = Simulink.Parameter;
struct_Ctrl_Out.Value = data;
struct_Ctrl_Out.DataType = 'Bus: Bus_Ctrl_Out';
clear data;