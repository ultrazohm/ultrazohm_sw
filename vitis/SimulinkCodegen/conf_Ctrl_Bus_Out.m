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

struct_Ctrl_Out = Simulink.Parameter;
struct_Ctrl_Out.Value = data;
struct_Ctrl_Out.DataType = 'Bus: Bus_Ctrl_Out';
clear data;