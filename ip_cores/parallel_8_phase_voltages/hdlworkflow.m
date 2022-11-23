%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 12:27:42 on 23/11/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_phase_voltages\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_phase_voltages/Phase_voltages_per_switching_state1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_phase_voltages/Phase_voltages_per_switching_state1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_phase_voltages');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_phase_voltages/Phase_voltages_per_switching_state1');

%% Model HDL Parameters
%% Set Model 'parallel_8_phase_voltages' HDL parameters
hdlset_param('parallel_8_phase_voltages', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_phase_voltages', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('parallel_8_phase_voltages', 'HDLSubsystem', 'parallel_8_phase_voltages/Phase_voltages_per_switching_state1');
hdlset_param('parallel_8_phase_voltages', 'OptimizationReport', 'on');
hdlset_param('parallel_8_phase_voltages', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_phase_voltages', 'ResourceReport', 'on');
hdlset_param('parallel_8_phase_voltages', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_phase_voltages', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_phase_voltages', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_phase_voltages', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_phase_voltages', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_phase_voltages', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_phase_voltages', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_phase_voltages\hdlsrc');
hdlset_param('parallel_8_phase_voltages', 'TargetFrequency', 100);
hdlset_param('parallel_8_phase_voltages', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_phase_voltages', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1', 'IPCoreName', 'parallel_8_sim_phase_voltages');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/theta_el', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/theta_el_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/theta_el_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/u_dc_link_voltage_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/u_dc_link_voltage_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Index', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_delay_compensation', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_delay_compensation', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_min_cost_function_and_vopt', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_min_cost_function_and_vopt', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/current_valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/current_valid_in', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Add4', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Add5', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Add6', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Compare Limit_High1', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Compare Limit_Low1', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Subsystem/MATLAB Function15', 'ConstMultiplierOptimization', 'auto');

% Set Outport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_phase_voltages', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/done_phase_voltages', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/phase_voltages_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/phase_voltages_per_switching_state', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Index_in_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_phase_voltages/Phase_voltages_per_switching_state1/Index_in_AXI', 'IOInterfaceMapping', 'x"108"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_phase_voltages';
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
hdlcoder.runWorkflow('parallel_8_phase_voltages/Phase_voltages_per_switching_state1', hWC);
