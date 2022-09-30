%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 13:33:52 on 30/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_Prediction_and_cost_function_6phase\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_prediction_and_cost_function_6phase');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function');

%% Model HDL Parameters
%% Set Model 'parallel_prediction_and_cost_function_6phase' HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_prediction_and_cost_function_6phase', 'HDLSubsystem', 'parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'OptimizationReport', 'on');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'ResetType', 'Synchronous');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'ResourceReport', 'on');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'SynthesisToolPackageName', '');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_Prediction_and_cost_function_6phase\hdlsrc');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'TargetFrequency', 100);
hdlset_param('parallel_prediction_and_cost_function_6phase', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_prediction_and_cost_function_6phase', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function', 'IPCoreName', 'parallel_prediction_and_cost_function_6phase');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Lq_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Ld_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Rs_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/psiPM_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_ref_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_ref_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_ref_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_ref_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/use_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/use_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/id_k_1_AXI', 'IOInterfaceMapping', 'x"138"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iq_k_1_AXI', 'IOInterfaceMapping', 'x"13C"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/ix_k_1_AXI', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/iy_k_1_AXI', 'IOInterfaceMapping', 'x"144"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/omega_m_measured_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/omega_m_measured_AXI', 'IOInterfaceMapping', 'x"148"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/d_voltage_per_switching_state_AXI_61_64', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/d_voltage_per_switching_state_AXI_61_64', 'IOInterfaceMapping', 'x"14C"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/q_voltage_per_switching_state_AXI_61_64', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/q_voltage_per_switching_state_AXI_61_64', 'IOInterfaceMapping', 'x"150"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/x_voltage_per_switching_state_AXI_61_64', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/x_voltage_per_switching_state_AXI_61_64', 'IOInterfaceMapping', 'x"154"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/y_volatge_per_switching_state_AXI_61_64', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/y_volatge_per_switching_state_AXI_61_64', 'IOInterfaceMapping', 'x"158"');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Reset', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Reset', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/dqxy_phase_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/dqxy_phase_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/done', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/J', 'IOInterface', 'External Port');
hdlset_param('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function/J', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_Prediction_and_cost_function_6phase';
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
hdlcoder.runWorkflow('parallel_prediction_and_cost_function_6phase/Prediction_and_cost_function', hWC);
