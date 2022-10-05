%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:37:12 on 05/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_phase_voltages_per_switching_state_6');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');

%% Model HDL Parameters
%% Set Model 'parallel_phase_voltages_per_switching_state_6' HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'HDLSubsystem', 'parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'OptimizationReport', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'ResetType', 'Synchronous');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'ResourceReport', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolPackageName', '');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\hdlsrc');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetFrequency', 100);
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', 'IPCoreName', 'parallel_phase_voltages_per_switching_state');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/u_dc_link_voltage_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/u_dc_link_voltage_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_delay_compensation', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_delay_compensation', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_min_cost_function-and_vopt', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_min_cost_function-and_vopt', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add3', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Compare Limit_High', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Compare Limit_Low', 'OutputPipeline', 1);

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/done', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/phase_voltages_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/phase_voltages_per_switching_state', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase';
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
hdlcoder.runWorkflow('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', hWC);
