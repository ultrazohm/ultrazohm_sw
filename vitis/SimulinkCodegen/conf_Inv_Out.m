% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'Uuvw';
elems(1).DataType = 'single';
elems(1).Dimensions = '3';

Bus_Inv_Out = Simulink.Bus;
Bus_Inv_Out.Elements = elems;

clear elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.Uuvw = 0; % Standard Inverter Modell ist PT1-Übertragungsglied


struct_Inv_Out = Simulink.Parameter;
struct_Inv_Out.Value = data;
struct_Inv_Out.DataType = 'Bus: Bus_Inv_Out';
clear data;