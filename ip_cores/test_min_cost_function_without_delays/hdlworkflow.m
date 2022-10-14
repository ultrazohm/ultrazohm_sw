%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 16:13:58 on 14/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\test_min_cost_function_without_delays\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'test_min_cost_function_without_delays/Min_cost_function_and_vopt1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','test_min_cost_function_without_delays/Min_cost_function_and_vopt1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('test_min_cost_function_without_delays');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('test_min_cost_function_without_delays/Min_cost_function_and_vopt1');

%% Model HDL Parameters
%% Set Model 'test_min_cost_function_without_delays' HDL parameters
hdlset_param('test_min_cost_function_without_delays', 'CriticalPathEstimation', 'on');
hdlset_param('test_min_cost_function_without_delays', 'HDLSubsystem', 'test_min_cost_function_without_delays/Min_cost_function_and_vopt1');
hdlset_param('test_min_cost_function_without_delays', 'OptimizationReport', 'on');
hdlset_param('test_min_cost_function_without_delays', 'ResetType', 'Synchronous');
hdlset_param('test_min_cost_function_without_delays', 'ResourceReport', 'on');
hdlset_param('test_min_cost_function_without_delays', 'ScalarizePorts', 'DUTLevel');
hdlset_param('test_min_cost_function_without_delays', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('test_min_cost_function_without_delays', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('test_min_cost_function_without_delays', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('test_min_cost_function_without_delays', 'SynthesisToolPackageName', '');
hdlset_param('test_min_cost_function_without_delays', 'SynthesisToolSpeedValue', '');
hdlset_param('test_min_cost_function_without_delays', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\test_min_cost_function_without_delays\hdlsrc');
hdlset_param('test_min_cost_function_without_delays', 'TargetFrequency', 100);
hdlset_param('test_min_cost_function_without_delays', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('test_min_cost_function_without_delays', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1', 'IPCoreName', 'test_min_cost_function_without_delays');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index_in', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/valid_in', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/J_in', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/J_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/phase_voltages_per_switching_state_in', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/phase_voltages_per_switching_state_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/done', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/done_complete', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/done_complete', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/J_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/J_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/voltages', 'IOInterface', 'External Port');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/voltages', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('test_min_cost_function_without_delays/Min_cost_function_and_vopt1/Index_AXI', 'IOInterfaceMapping', 'x"104"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\test_min_cost_function_without_delays';
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
hdlcoder.runWorkflow('test_min_cost_function_without_delays/Min_cost_function_and_vopt1', hWC);
