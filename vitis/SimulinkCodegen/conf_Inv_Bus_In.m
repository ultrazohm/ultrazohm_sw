% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'PWM_H_safe';
elems(1).DataType = 'single';
elems(1).Dimensions = '3';

elems(2) = Simulink.BusElement;
elems(2).Name = 'PWM_L_safe';
elems(2).DataType = 'single';
elems(2).Dimensions = '3';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Ualpha';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'Ubeta';
elems(4).DataType = 'single';

Bus_Inv_In = Simulink.Bus;
Bus_Inv_In.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.PWM_H_safe = 0; 
data.PWM_L_safe = 0; 
data.Ualpha = 0; 
data.Ubeta = 0; 

struct_Inv_In = Simulink.Parameter;
struct_Inv_In.Value = data;
struct_Inv_In.DataType = 'Bus: Bus_Inv_In';
clear data;