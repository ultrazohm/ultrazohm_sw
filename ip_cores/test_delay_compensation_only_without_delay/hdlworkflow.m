%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 10:29:45 on 14/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\test_delay_compensation_only_without_delay\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'test_delay_compensation_without_delay/HDL_DUT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','test_delay_compensation_without_delay/HDL_DUT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('test_delay_compensation_without_delay');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('test_delay_compensation_without_delay/HDL_DUT');

%% Model HDL Parameters
%% Set Model 'test_delay_compensation_without_delay' HDL parameters
hdlset_param('test_delay_compensation_without_delay', 'CriticalPathEstimation', 'on');
hdlset_param('test_delay_compensation_without_delay', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('test_delay_compensation_without_delay', 'HDLSubsystem', 'test_delay_compensation_without_delay/HDL_DUT');
hdlset_param('test_delay_compensation_without_delay', 'OptimizationReport', 'on');
hdlset_param('test_delay_compensation_without_delay', 'ResetType', 'Synchronous');
hdlset_param('test_delay_compensation_without_delay', 'ResourceReport', 'on');
hdlset_param('test_delay_compensation_without_delay', 'ScalarizePorts', 'DUTLevel');
hdlset_param('test_delay_compensation_without_delay', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('test_delay_compensation_without_delay', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('test_delay_compensation_without_delay', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('test_delay_compensation_without_delay', 'SynthesisToolPackageName', '');
hdlset_param('test_delay_compensation_without_delay', 'SynthesisToolSpeedValue', '');
hdlset_param('test_delay_compensation_without_delay', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\test_delay_compensation_only_without_delay\hdlsrc');
hdlset_param('test_delay_compensation_without_delay', 'TargetFrequency', 100);
hdlset_param('test_delay_compensation_without_delay', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('test_delay_compensation_without_delay', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT', 'IPCoreName', 'test_delay_compensation_without_delays');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_measured', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_measured', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_measured', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_measured', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/psiPM_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Lq_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/Rs_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/last_applied_optimal_voltages_in', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/last_applied_optimal_voltages_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/valid_in', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/valid_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_k_1', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_k_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/done', 'IOInterface', 'External Port');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/id_k_1_AXI', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iq_k_1_AXI', 'IOInterfaceMapping', 'x"150"');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/ix_k_1_AXI', 'IOInterfaceMapping', 'x"154"');

% Set Outport HDL parameters
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_delay_compensation_without_delay/HDL_DUT/iy_k_1_AXI', 'IOInterfaceMapping', 'x"158"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\test_delay_compensation_only_without_delay';
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
hdlcoder.runWorkflow('test_delay_compensation_without_delay/HDL_DUT', hWC);
