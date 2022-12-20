%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 16:22:30 on 14/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\test_switching_states_6Phase_without_delays\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'test_switching_states_6Phase_without_delays/HDL_DUT2'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','test_switching_states_6Phase_without_delays/HDL_DUT2');
%--------------------------------------------------------------------------

%% Load the Model
load_system('test_switching_states_6Phase_without_delays');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('test_switching_states_6Phase_without_delays/HDL_DUT2');

%% Model HDL Parameters
%% Set Model 'test_switching_states_6Phase_without_delays' HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays', 'CriticalPathEstimation', 'on');
hdlset_param('test_switching_states_6Phase_without_delays', 'HDLSubsystem', 'test_switching_states_6Phase_without_delays/HDL_DUT2');
hdlset_param('test_switching_states_6Phase_without_delays', 'OptimizationReport', 'on');
hdlset_param('test_switching_states_6Phase_without_delays', 'ResetType', 'Synchronous');
hdlset_param('test_switching_states_6Phase_without_delays', 'ResourceReport', 'on');
hdlset_param('test_switching_states_6Phase_without_delays', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('test_switching_states_6Phase_without_delays', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('test_switching_states_6Phase_without_delays', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('test_switching_states_6Phase_without_delays', 'SynthesisToolPackageName', '');
hdlset_param('test_switching_states_6Phase_without_delays', 'SynthesisToolSpeedValue', '');
hdlset_param('test_switching_states_6Phase_without_delays', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\test_switching_states_6Phase_without_delays\hdlsrc');
hdlset_param('test_switching_states_6Phase_without_delays', 'TargetFrequency', 100);
hdlset_param('test_switching_states_6Phase_without_delays', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('test_switching_states_6Phase_without_delays', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2', 'IPCoreName', 'test_swithcing_states_6Phase_without_delays');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/I', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/I', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/valid_in', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/valid_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB1T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB1T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB1B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB1B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB2T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB2T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB2B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB2B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB3T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB3T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB3B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB3B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB4T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB4T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB4B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB4B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB5T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB5T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB5B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB5B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB6T', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB6T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB6B', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/HB6B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/done', 'IOInterface', 'External Port');
hdlset_param('test_switching_states_6Phase_without_delays/HDL_DUT2/done', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\test_switching_states_6Phase_without_delays';
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
hdlcoder.runWorkflow('test_switching_states_6Phase_without_delays/HDL_DUT2', hWC);
