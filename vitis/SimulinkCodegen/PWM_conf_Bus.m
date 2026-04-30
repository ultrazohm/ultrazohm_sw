% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'IGBT_deadtime';
elems(1).DataType = 'single';


Bus_PWM_Config = Simulink.Bus;
Bus_PWM_Config.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.IGBT_deadtime = struct_Ctrl_Config.Value.IGBT_deadtime; % Standard Inverter Modell ist PT1-Übertragungsglied

struct_PWM_Config = Simulink.Parameter;
struct_PWM_Config.Value = data;
struct_PWM_Config.DataType = 'Bus: Bus_PWM_Config';
clear data;