% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'Dutycycle';
elems(1).DataType = 'single';
elems(1).Dimensions = '3';

elems(2) = Simulink.BusElement;
elems(2).Name = 'act_pwm';
elems(2).DataType = 'boolean';

elems(3) = Simulink.BusElement;
elems(3).Name = 'ctrl_Ualpha';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'ctrl_Ubeta';
elems(4).DataType = 'single';

elems(5) = Simulink.BusElement;
elems(5).Name = 'pwr_en';
elems(5).DataType = 'boolean';

elems(6) = Simulink.BusElement;
elems(6).Name = 'board_en';
elems(6).DataType = 'boolean';

elems(7) = Simulink.BusElement;
elems(7).Name = 'reset';
elems(7).DataType = 'boolean';


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

struct_Ctrl_Out = Simulink.Parameter;
struct_Ctrl_Out.Value = data;
struct_Ctrl_Out.DataType = 'Bus: Bus_Ctrl_Out';
clear data;