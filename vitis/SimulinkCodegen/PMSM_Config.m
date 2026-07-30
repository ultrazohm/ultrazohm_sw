% Definition Motorparamter für Bus_Config_PMSM
clear elems;
elems(1) = Simulink.BusElement;
elems(1).Name = 'mot_R1';
elems(1).DataType = 'single';

elems(2) = Simulink.BusElement;
elems(2).Name = 'mot_psi_pm';
elems(2).DataType = 'single';

elems(3) = Simulink.BusElement;
elems(3).Name = 'mot_Ld';
elems(3).DataType = 'single';

elems(4) = Simulink.BusElement;
elems(4).Name = 'mot_Lq';
elems(4).DataType = 'single';



elems(5) = Simulink.BusElement;
elems(5).Name = 'mot_p';
elems(5).DataType = 'single';

elems(6) = Simulink.BusElement;
elems(6).Name = 'mot_J';
elems(6).DataType = 'single';

elems(7) = Simulink.BusElement;
elems(7).Name = 'mot_n_N';
elems(7).DataType = 'single';

elems(8) = Simulink.BusElement;
elems(8).Name = 'mot_M_N';
elems(8).DataType = 'single';

elems(9) = Simulink.BusElement;
elems(9).Name = 'mot_I_max';
elems(9).DataType = 'single';

elems(10) = Simulink.BusElement;
elems(10).Name = 'Coulomb_Reibung';
elems(10).DataType = 'single';

elems(11) = Simulink.BusElement;
elems(11).Name = 'Reibungskoeffizient';
elems(11).DataType = 'single';

Bus_PMSM_Config = Simulink.Bus;
Bus_PMSM_Config.Elements = elems;

% --- Parameter-Definition (Die Werte) ---
clear data;
data.mot_R1 = 1.8;          % Strangwiderstand in Ohm
data.mot_psi_pm = 0.1423;   % Flussverkettung Permanentmagente in Vs
data.mot_Ld = 7.2e-3;       % d-Induktivität in Henry
data.mot_Lq = 7.2e-3;       % q-Induktivität in Henry
data.mot_p = 4;             % Polpaarzahl
data.mot_J = 8.75e-4;       % Motorträgheit in kg*m^2
data.mot_n_N = 5700;        % Nenndrehzahl in U/min
data.mot_M_N = 4.3;         % Nenndrehmoment in Nm
data.mot_I_max = 20.9;      %Maximaler Phasenstrom in A
data.Coulomb_Reibung = 0.1;
data.Reibungskoeffizient = 0.001;

struct_PMSM_Config = Simulink.Parameter;
struct_PMSM_Config.Value = data;
struct_PMSM_Config.DataType = 'Bus: Bus_PMSM_Config';
struct_PMSM_Config.CoderInfo.StorageClass = 'ExportedGlobal';