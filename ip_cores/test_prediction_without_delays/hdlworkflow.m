%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 14:38:38 on 14/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\test_prediction_without_delays\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'test_prediction_without_delays/Prediction_and_cost_function1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','test_prediction_without_delays/Prediction_and_cost_function1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('test_prediction_without_delays');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('test_prediction_without_delays/Prediction_and_cost_function1');

%% Model HDL Parameters
%% Set Model 'test_prediction_without_delays' HDL parameters
hdlset_param('test_prediction_without_delays', 'CriticalPathEstimation', 'on');
hdlset_param('test_prediction_without_delays', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('test_prediction_without_delays', 'HDLSubsystem', 'test_prediction_without_delays/Prediction_and_cost_function1');
hdlset_param('test_prediction_without_delays', 'OptimizationReport', 'on');
hdlset_param('test_prediction_without_delays', 'ResetType', 'Synchronous');
hdlset_param('test_prediction_without_delays', 'ResourceReport', 'on');
hdlset_param('test_prediction_without_delays', 'ScalarizePorts', 'DUTLevel');
hdlset_param('test_prediction_without_delays', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('test_prediction_without_delays', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('test_prediction_without_delays', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('test_prediction_without_delays', 'SynthesisToolPackageName', '');
hdlset_param('test_prediction_without_delays', 'SynthesisToolSpeedValue', '');
hdlset_param('test_prediction_without_delays', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\test_prediction_without_delays\hdlsrc');
hdlset_param('test_prediction_without_delays', 'TargetFrequency', 100);
hdlset_param('test_prediction_without_delays', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('test_prediction_without_delays', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1', 'IPCoreName', 'test_prediction_without_delays');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Lq_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Ld_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/id_k_1', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/id_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/iq_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/ix_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/iy_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Rs_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/psiPM_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/valid_in', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Reset', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Reset', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/dqxy_phase_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/dqxy_phase_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/done', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Index', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Prediction', 'IOInterface', 'External Port');
hdlset_param('test_prediction_without_delays/Prediction_and_cost_function1/Prediction', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\test_prediction_without_delays';
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
hdlcoder.runWorkflow('test_prediction_without_delays/Prediction_and_cost_function1', hWC);
