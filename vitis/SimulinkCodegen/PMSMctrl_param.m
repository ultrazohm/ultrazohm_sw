model_conf;
PMSM_Config;  % Laden PMSM Parameter
conf_PMSM_Bus_In;
conf_PMSM_Bus_Out;

config_Ctrl;
config_Bus_ZM_in;
config_ZM_out;
conf_Ctrl_Bus_Out;

PWM_conf_Bus;
conf_PWM_Bus_In;
conf_PWM_Out;

Inverter_Config;
conf_Inv_Bus_In;
conf_Inv_Out;
step_size = struct_Model_Config.Value.step_size;

% Defines

GAIN_UMIN_TO_HZ = Simulink.Parameter;
GAIN_UMIN_TO_HZ.Value = 1/(2*pi*60);
GAIN_UMIN_TO_HZ.DataType = 'single';
GAIN_UMIN_TO_HZ.StorageClass = 'Define';

GAIN_RADS_TO_HZ = Simulink.Parameter;
GAIN_RADS_TO_HZ.Value = 1/(2*pi);
GAIN_RADS_TO_HZ.DataType = 'single';
GAIN_RADS_TO_HZ.StorageClass = 'Define';

DIVIDE_SQRT_THREE_BY_TWO = Simulink.Parameter;
DIVIDE_SQRT_THREE_BY_TWO.Value = sqrt(3)/2;
DIVIDE_SQRT_THREE_BY_TWO.DataType = 'single';
DIVIDE_SQRT_THREE_BY_TWO.StorageClass = 'Define';

DIVIDE_TWO_BY_THREE = Simulink.Parameter;
DIVIDE_TWO_BY_THREE.Value = 2/3;
DIVIDE_TWO_BY_THREE.DataType = 'single';
DIVIDE_TWO_BY_THREE.StorageClass = 'Define';

DIVIDE_ONE_BY_SQRT_THREE = Simulink.Parameter;
DIVIDE_ONE_BY_SQRT_THREE.Value = 1/sqrt(3);
DIVIDE_ONE_BY_SQRT_THREE.DataType = 'single';
DIVIDE_ONE_BY_SQRT_THREE.StorageClass = 'Define';

DIVIDE_ONE_BY_TWO_THIRDS = Simulink.Parameter;
DIVIDE_ONE_BY_TWO_THIRDS.Value = 1/(2/3);
DIVIDE_ONE_BY_TWO_THIRDS.DataType = 'single';
DIVIDE_ONE_BY_TWO_THIRDS.StorageClass = 'Define';

DIVIDE_TWO_BY_TWO_THIRDS = Simulink.Parameter;
DIVIDE_TWO_BY_TWO_THIRDS.Value = 2/(2/3);
DIVIDE_TWO_BY_TWO_THIRDS.DataType = 'single';
DIVIDE_TWO_BY_TWO_THIRDS.StorageClass = 'Define';


