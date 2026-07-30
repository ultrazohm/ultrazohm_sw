% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'PWM_H_safe';
elems(1).DataType = 'boolean';
elems(1).Dimensions = '3';

elems(2) = Simulink.BusElement;
elems(2).Name = 'PWM_L_safe';
elems(2).DataType = 'boolean';
elems(2).Dimensions = '3';

Bus_PWM_Out = Simulink.Bus;
Bus_PWM_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.PWM_H_safe = 0; 
data.PWM_l_safe = 0; 


struct_PWM_Out = Simulink.Parameter;
struct_PWM_Out.Value = data;
struct_PWM_Out.DataType = 'Bus: Bus_PWM_Out';
clear data;