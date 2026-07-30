% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'step_size';
elems(1).DataType = 'single';

elems(2) = Simulink.BusElement;
elems(2).Name = 'FPGA_Freq';
elems(2).DataType = 'single';

Bus_Model_Config = Simulink.Bus;
Bus_Model_Config.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.step_size = 1e-8; % Grundschrittweite Model
data.FPGA_Freq = 1e-7;    % Schrittweite PWM Erzeugung


struct_Model_Config = Simulink.Parameter;
struct_Model_Config.Value = data;
struct_Model_Config.DataType = 'Bus: Bus_Model_Config';
clear data;