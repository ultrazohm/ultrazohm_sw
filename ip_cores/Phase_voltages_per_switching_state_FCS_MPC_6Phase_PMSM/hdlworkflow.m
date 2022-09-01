%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 10:37:45 on 01/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\Phase_voltages_per_switching_state_FCS_MPC_6Phase_PMSM\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('Phase_voltages_per_switching_state_MPC_6Phase');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT');

%% Model HDL Parameters
%% Set Model 'Phase_voltages_per_switching_state_MPC_6Phase' HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'CriticalPathEstimation', 'on');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'HDLSubsystem', 'Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'OptimizationReport', 'on');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'ResetType', 'Synchronous');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'ResourceReport', 'on');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'SynthesisToolPackageName', '');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'SynthesisToolSpeedValue', '');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\Phase_voltages_per_switching_state_FCS_MPC_6Phase_PMSM\hdlsrc');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'TargetFrequency', 100);
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT', 'IPCoreName', 'Phase_voltages_per_switching_state_MPC_6Phase');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/u_dc_link_voltage_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/u_dc_link_voltage_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Index', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Index', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/use_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/use_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/theta_el_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Index_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Index_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_delay_compensation', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_delay_compensation', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_min_cost_function-and_vopt', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/valid_in_min_cost_function-and_vopt', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Add3', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Compare Limit_High', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/Compare Limit_Low', 'OutputPipeline', 1);

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/d_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/d_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/q_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/q_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/x_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/x_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/y_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/y_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/d_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/d_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/q_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/q_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/x_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/x_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/y_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/y_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/done', 'IOInterface', 'External Port');
hdlset_param('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT/done', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\Phase_voltages_per_switching_state_FCS_MPC_6Phase_PMSM';
hWC.ReferenceDesignToolVersion = '';
hWC.IgnoreToolVersionMismatch = false;

% Set Workflow tasks to run
hWC.RunTaskGenerateRTLCodeAndIPCore = true;
hWC.RunTaskCreateProject = false;
hWC.RunTaskGenerateSoftwareInterface = false;
hWC.RunTaskBuildFPGABitstream = false;
hWC.RunTaskProgramTargetDevice = false;

% Set properties related to 'RunTaskGenerateRTLCodeAndIPCore' Task
hWC.IPCoreRepository = '';
hWC.GenerateIPCoreReport = true;

% Set properties related to 'RunTaskCreateProject' Task
hWC.Objective = hdlcoder.Objective.None;
hWC.AdditionalProjectCreationTclFiles = '';
hWC.EnableIPCaching = false;

% Set properties related to 'RunTaskGenerateSoftwareInterface' Task
hWC.GenerateSoftwareInterfaceModel = true;
hWC.OperatingSystem = '';
hWC.HostTargetInterface = '';
hWC.GenerateHostInterfaceModel = false;
hWC.GenerateHostInterfaceScript = false;

% Set properties related to 'RunTaskBuildFPGABitstream' Task
hWC.RunExternalBuild = false;
hWC.EnableDesignCheckpoint = false;
hWC.TclFileForSynthesisBuild = hdlcoder.BuildOption.Default;
hWC.CustomBuildTclFile = '';
hWC.DefaultCheckpointFile = 'Default';
hWC.RoutedDesignCheckpointFilePath = '';
hWC.MaxNumOfCoresForBuild = '';

% Set properties related to 'RunTaskProgramTargetDevice' Task
hWC.ProgrammingMethod = hdlcoder.ProgrammingMethod.JTAG;
hWC.IPAddress = '';
hWC.SSHUsername = '';
hWC.SSHPassword = '';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('Phase_voltages_per_switching_state_MPC_6Phase/HDL_DUT', hWC);
