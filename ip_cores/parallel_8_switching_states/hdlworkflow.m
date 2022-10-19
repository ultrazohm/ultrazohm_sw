%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 13:27:22 on 18/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_switching_states\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_switching_states/HDL_DUT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_switching_states/HDL_DUT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_switching_states');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_switching_states/HDL_DUT');

%% Model HDL Parameters
%% Set Model 'parallel_8_switching_states' HDL parameters
hdlset_param('parallel_8_switching_states', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_switching_states', 'HDLSubsystem', 'parallel_8_switching_states/HDL_DUT');
hdlset_param('parallel_8_switching_states', 'OptimizationReport', 'on');
hdlset_param('parallel_8_switching_states', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_switching_states', 'ResourceReport', 'on');
hdlset_param('parallel_8_switching_states', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_switching_states', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_switching_states', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_switching_states', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_switching_states', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_switching_states', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_switching_states\hdlsrc');
hdlset_param('parallel_8_switching_states', 'TargetFrequency', 100);
hdlset_param('parallel_8_switching_states', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_switching_states', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT', 'IPCoreName', 'parallel_8_switching_states');
hdlset_param('parallel_8_switching_states/HDL_DUT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/I', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/I', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/valid_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB1T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB1T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB1B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB1B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB2T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB2T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB2B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB2B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB3T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB3T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB3B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB3B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB4T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB4T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB4B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB4B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB5T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB5T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB5B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB5B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB6T', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB6T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/HB6B', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/HB6B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_switching_states/HDL_DUT/done', 'IOInterface', 'External Port');
hdlset_param('parallel_8_switching_states/HDL_DUT/done', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_switching_states';
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
hdlcoder.runWorkflow('parallel_8_switching_states/HDL_DUT', hWC);
