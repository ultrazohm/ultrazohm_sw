%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 12:09:00 on 09/12/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_min_cost_function\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_min_cost_function/Min_cost_function_and_vopt1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_min_cost_function/Min_cost_function_and_vopt1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_min_cost_function');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_min_cost_function/Min_cost_function_and_vopt1');

%% Model HDL Parameters
%% Set Model 'parallel_8_min_cost_function' HDL parameters
hdlset_param('parallel_8_min_cost_function', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_min_cost_function', 'HDLSubsystem', 'parallel_8_min_cost_function/Min_cost_function_and_vopt1');
hdlset_param('parallel_8_min_cost_function', 'OptimizationReport', 'on');
hdlset_param('parallel_8_min_cost_function', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_min_cost_function', 'ResourceReport', 'on');
hdlset_param('parallel_8_min_cost_function', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_min_cost_function', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_min_cost_function', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_min_cost_function', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_min_cost_function', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_min_cost_function', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_min_cost_function', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_min_cost_function\hdlsrc');
hdlset_param('parallel_8_min_cost_function', 'TargetFrequency', 100);
hdlset_param('parallel_8_min_cost_function', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_min_cost_function', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1', 'IPCoreName', 'parallel_8_sim_min_cost_function');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/Index_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/Index_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/done_prediction_and_cost_function', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/done_prediction_and_cost_function', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/J_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/J_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/phase_voltages_per_switching_state_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/phase_voltages_per_switching_state_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/done_min_cost_function_and_vopt', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/done_min_cost_function_and_vopt', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/voltages', 'IOInterface', 'External Port');
hdlset_param('parallel_8_min_cost_function/Min_cost_function_and_vopt1/voltages', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_min_cost_function';
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
hdlcoder.runWorkflow('parallel_8_min_cost_function/Min_cost_function_and_vopt1', hWC);
