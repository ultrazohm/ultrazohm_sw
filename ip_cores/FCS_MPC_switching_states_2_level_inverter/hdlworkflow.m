%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:05:02 on 12/07/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\FCS_MPC_switching_states_2_level_inverter\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem');
%--------------------------------------------------------------------------

%% Load the Model
load_system('FCS_MPC_switching_states_2_level_inverter');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem');

%% Model HDL Parameters
%% Set Model 'FCS_MPC_switching_states_2_level_inverter' HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'CriticalPathEstimation', 'on');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'HDLSubsystem', 'FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'OptimizationReport', 'on');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'ResetType', 'Synchronous');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'ResourceReport', 'on');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'SynthesisToolPackageName', '');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'SynthesisToolSpeedValue', '');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\FCS_MPC_switching_states_2_level_inverter\hdlsrc');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'TargetFrequency', 100);
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('FCS_MPC_switching_states_2_level_inverter', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem', 'IPCoreName', 'FCS_MPC_switching_states_2_level_inverter');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/I', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/I', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/done_min_J', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/done_min_J', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB1T', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB1T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB1B', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB1B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB2T', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB2T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB2B', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB2B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB3T', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB3T', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB3B', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/HB3B', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/done', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem/done', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\FCS_MPC_switching_states_2_level_inverter';
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
hdlcoder.runWorkflow('FCS_MPC_switching_states_2_level_inverter/Microcontroller Software/Subsystem', hWC);
