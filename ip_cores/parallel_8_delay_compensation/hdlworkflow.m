%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 16:31:48 on 07/12/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_delay_compensation\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_delay_compensation/Delay_compensation'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_delay_compensation/Delay_compensation');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_delay_compensation');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_delay_compensation/Delay_compensation');

%% Model HDL Parameters
%% Set Model 'parallel_8_delay_compensation' HDL parameters
hdlset_param('parallel_8_delay_compensation', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_delay_compensation', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_8_delay_compensation', 'HDLSubsystem', 'parallel_8_delay_compensation/Delay_compensation');
hdlset_param('parallel_8_delay_compensation', 'OptimizationReport', 'on');
hdlset_param('parallel_8_delay_compensation', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_delay_compensation', 'ResourceReport', 'on');
hdlset_param('parallel_8_delay_compensation', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_delay_compensation', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_delay_compensation', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_delay_compensation', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_delay_compensation', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_delay_compensation', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_delay_compensation', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_delay_compensation\hdlsrc');
hdlset_param('parallel_8_delay_compensation', 'TargetFrequency', 100);
hdlset_param('parallel_8_delay_compensation', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_delay_compensation', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation', 'IPCoreName', 'parallel_8_sim_delay_compensation');
hdlset_param('parallel_8_delay_compensation/Delay_compensation', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/psiPM_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Lq_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/Rs_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/last_applied_optimal_voltages_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/last_applied_optimal_voltages_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/current_valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/current_valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/done_switching_states', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/done_switching_states', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/done_delay_compensation', 'IOInterface', 'External Port');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/done_delay_compensation', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/id_k_1_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iq_k_1_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/ix_k_1_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_delay_compensation/Delay_compensation/iy_k_1_AXI', 'IOInterfaceMapping', 'x"130"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_delay_compensation';
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
hdlcoder.runWorkflow('parallel_8_delay_compensation/Delay_compensation', hWC);
