%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 12:11:26 on 08/12/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction_and_cost_function\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_prediction_and_cost_function/Prediction_and_cost_function1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_prediction_and_cost_function/Prediction_and_cost_function1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_prediction_and_cost_function');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1');

%% Model HDL Parameters
%% Set Model 'parallel_8_prediction_and_cost_function' HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_prediction_and_cost_function', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_8_prediction_and_cost_function', 'HDLSubsystem', 'parallel_8_prediction_and_cost_function/Prediction_and_cost_function1');
hdlset_param('parallel_8_prediction_and_cost_function', 'OptimizationReport', 'on');
hdlset_param('parallel_8_prediction_and_cost_function', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_prediction_and_cost_function', 'ResourceReport', 'on');
hdlset_param('parallel_8_prediction_and_cost_function', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_prediction_and_cost_function', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_prediction_and_cost_function', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_prediction_and_cost_function', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_prediction_and_cost_function', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_prediction_and_cost_function', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_prediction_and_cost_function', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction_and_cost_function\hdlsrc');
hdlset_param('parallel_8_prediction_and_cost_function', 'TargetFrequency', 100);
hdlset_param('parallel_8_prediction_and_cost_function', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_prediction_and_cost_function', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1', 'IPCoreName', 'parallel_8_sim_prediction_and_cost_function');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Lq_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Ld_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/id_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/id_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iq_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/ix_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iy_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Rs_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/psiPM_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/id_ref_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iq_ref_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/ix_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/ix_ref_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iy_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/iy_ref_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_phase_voltages', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_phase_voltages', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_vsd_and_park', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_vsd_and_park', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/current_valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/current_valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/dqxy_phase_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/dqxy_phase_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_Prediction_and_cost_function', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/done_Prediction_and_cost_function', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/J', 'IOInterface', 'External Port');
hdlset_param('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1/J', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_prediction_and_cost_function';
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
hdlcoder.runWorkflow('parallel_8_prediction_and_cost_function/Prediction_and_cost_function1', hWC);