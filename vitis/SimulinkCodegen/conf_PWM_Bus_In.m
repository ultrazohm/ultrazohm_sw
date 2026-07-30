% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'act_pwm';
elems(1).DataType = 'boolean';

elems(2) = Simulink.BusElement;
elems(2).Name = 'Dutycycle';
elems(2).DataType = 'single';
elems(2).Dimensions = '3';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Referenzsignal';
elems(3).DataType = 'single';

Bus_PWM_In = Simulink.Bus;
Bus_PWM_In.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.act_pwm = 0; 
data.Dutycycle = 0; 
data.Referenzsignal = 0; 


struct_PWM_In = Simulink.Parameter;
struct_PWM_In.Value = data;
struct_PWM_In.DataType = 'Bus: Bus_PWM_In';
clear data;