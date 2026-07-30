% Definition Motorparamter für Bus_Config_PMSM
clear elems;
i = 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Drehzahl';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_id';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_iq';
elems(i).DataType = 'single';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Start_Traj';
elems(i).DataType = 'boolean';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Fehlermeldung';
elems(i).DataType = 'boolean';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Status';
elems(i).DataType = 'Enum: Status_Ctrl';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Soll_Regelungsart';
elems(i).DataType = 'Enum: Soll_Regelungsart_en';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'Inv_Ready';
elems(i).DataType = 'boolean';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'UZ_Platform_State';
elems(i).DataType = 'Enum: platform_state_t';
i = i + 1;

elems(i) = Simulink.BusElement;
elems(i).Name = 'IGBT_desat';
elems(i).DataType = 'boolean';
i = i + 1;



Bus_ZM_In = Simulink.Bus;
Bus_ZM_In.Elements = elems;
clear i;
clear elems;
% --- Parameter-Definition (Die Werte) ---
clear data;

data.Soll_Drehzahl = 2000; 
data.Soll_id = 0; 
data.Soll_iq = 0; 
data.Start_Traj = 0; 
data.Fehlermeldung = 0; 
data.Soll_Status = Status_Ctrl.Ready; 
data.Soll_Regelungsart = Soll_Regelungsart_en.Drehzahl; 
data.Inv_Ready = false;
data.UZ_Platform_State = platform_state_t.idle_state;
data.IGBT_desat = false;


struct_ZM_In = Simulink.Parameter;
struct_ZM_In.Value = data;
struct_ZM_In.DataType = 'Bus: Bus_ZM_In';
struct_ZM_In.CoderInfo.StorageClass = 'ExportedGlobal';
clear data;
