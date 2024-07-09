%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.14 (R2023a) at 16:13:54 on 09/07/2024
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Documents/ultrazohm_sw/ip_cores/uz_sine_generator_16bit/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_sine_generator_16bit/uz_sine_generator_16bit '
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_sine_generator_16bit/uz_sine_generator_16bit ');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_sine_generator_16bit');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_sine_generator_16bit/uz_sine_generator_16bit ');

%% Model HDL Parameters
%% Set Model 'uz_sine_generator_16bit' HDL parameters
hdlset_param('uz_sine_generator_16bit', 'AdaptivePipelining', 'on');
hdlset_param('uz_sine_generator_16bit', 'BalanceDelaysForTunableParam', 'off');
hdlset_param('uz_sine_generator_16bit', 'CriticalPathEstimation', 'on');
hdlset_param('uz_sine_generator_16bit', 'DistributedPipelining', 'on');
hdlset_param('uz_sine_generator_16bit', 'GenDUTPortForTunableParam', 'off');
hdlset_param('uz_sine_generator_16bit', 'HDLSubsystem', 'uz_sine_generator_16bit/uz_sine_generator_16bit ');
hdlset_param('uz_sine_generator_16bit', 'OptimizationReport', 'on');
hdlset_param('uz_sine_generator_16bit', 'PreserveDesignDelays', 'on');
hdlset_param('uz_sine_generator_16bit', 'ResetInputPort', 'reset_x');
hdlset_param('uz_sine_generator_16bit', 'ResetType', 'Synchronous');
hdlset_param('uz_sine_generator_16bit', 'ResourceReport', 'on');
hdlset_param('uz_sine_generator_16bit', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_sine_generator_16bit', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_sine_generator_16bit', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_sine_generator_16bit', 'SynthesisToolPackageName', '');
hdlset_param('uz_sine_generator_16bit', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_sine_generator_16bit', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_sine_generator_16bit', 'TargetFrequency', 100);
hdlset_param('uz_sine_generator_16bit', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_sine_generator_16bit', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit ', 'IPCoreName', 'uz_sine_generator_16bit');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit ', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_1', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_1', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_1', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /enable_sine', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /enable_sine', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /reset_sine', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /reset_sine', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_2', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_2', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_2', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_3', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_3', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_3', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_4', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_4', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_4', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_5', 'IOInterfaceMapping', 'x"138"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_5', 'IOInterfaceMapping', 'x"13C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_5', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_6', 'IOInterfaceMapping', 'x"144"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_6', 'IOInterfaceMapping', 'x"148"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_6', 'IOInterfaceMapping', 'x"150"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_7', 'IOInterfaceMapping', 'x"14C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_7', 'IOInterfaceMapping', 'x"154"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_7', 'IOInterfaceMapping', 'x"158"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /amplitude_8', 'IOInterfaceMapping', 'x"15C"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /phase_shift_8', 'IOInterfaceMapping', 'x"160"');

% Set Inport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /frequency_8', 'IOInterfaceMapping', 'x"164"');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_1', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_2', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_3', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_4', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_5', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_6', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_7', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_8', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /data_out_8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /cnv_trigger', 'IOInterface', 'External Port');
hdlset_param('uz_sine_generator_16bit/uz_sine_generator_16bit /cnv_trigger', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj';
hWC.AllowUnsupportedToolVersion = true;
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
hWC.GenerateSoftwareInterfaceModel = false;
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
hdlcoder.runWorkflow('uz_sine_generator_16bit/uz_sine_generator_16bit ', hWC);
