%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 13:59:21 on 05/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_min_cost_function_vopt_6phase\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_min_cost_function_vopt_6phase');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt');

%% Model HDL Parameters
%% Set Model 'parallel_min_cost_function_vopt_6phase' HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'HDLSubsystem', 'parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'OptimizationReport', 'on');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'ResetType', 'Synchronous');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'ResourceReport', 'on');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'SynthesisToolPackageName', '');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_min_cost_function_vopt_6phase\hdlsrc');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'TargetFrequency', 100);
hdlset_param('parallel_min_cost_function_vopt_6phase', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_min_cost_function_vopt_6phase', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt', 'IPCoreName', 'parallel_min_cost_function_vopt_6Phase');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index_in', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/J_in', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/J_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/phase_voltages_per_switching_state_in', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/phase_voltages_per_switching_state_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/done', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/done_complete', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/done_complete', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/J_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/J_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/voltages', 'IOInterface', 'External Port');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/voltages', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt/Index_AXI', 'IOInterfaceMapping', 'x"104"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_min_cost_function_vopt_6phase';
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
hdlcoder.runWorkflow('parallel_min_cost_function_vopt_6phase/Min_cost_function_and_vopt', hWC);
