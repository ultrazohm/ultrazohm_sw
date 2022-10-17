%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:12:53 on 17/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_prediction/Prediction_and_cost_function2'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_prediction/Prediction_and_cost_function2');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_prediction');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_prediction/Prediction_and_cost_function2');

%% Model HDL Parameters
%% Set Model 'parallel_8_prediction' HDL parameters
hdlset_param('parallel_8_prediction', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_prediction', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_8_prediction', 'HDLSubsystem', 'parallel_8_prediction/Prediction_and_cost_function2');
hdlset_param('parallel_8_prediction', 'OptimizationReport', 'on');
hdlset_param('parallel_8_prediction', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_prediction', 'ResourceReport', 'on');
hdlset_param('parallel_8_prediction', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_prediction', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_prediction', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_prediction', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_prediction', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_prediction', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_prediction', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction\hdlsrc');
hdlset_param('parallel_8_prediction', 'TargetFrequency', 100);
hdlset_param('parallel_8_prediction', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_prediction', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2', 'IPCoreName', 'parallel_8_prediction');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Lq_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Ld_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/id_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/id_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/iq_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/ix_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/iy_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Rs_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/psiPM_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Reset', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Reset', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/dqxy_phase_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/dqxy_phase_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/done', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Prediction', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction/Prediction_and_cost_function2/Prediction', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction';
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
hdlcoder.runWorkflow('parallel_8_prediction/Prediction_and_cost_function2', hWC);
