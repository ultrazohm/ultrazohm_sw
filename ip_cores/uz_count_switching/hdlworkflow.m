%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 24.1 (R2024a) at 13:27:11 on 18/03/2026
% This script was generated using the following parameter values:
%     Filename  : 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_count_switching\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_count_switching/uz_count_switching'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_count_switching/uz_count_switching');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_count_switching');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_count_switching/uz_count_switching');

%% Model HDL Parameters
%% Set Model 'uz_count_switching' HDL parameters
hdlset_param('uz_count_switching', 'CriticalPathEstimation', 'on');
hdlset_param('uz_count_switching', 'HDLSubsystem', 'uz_count_switching/uz_count_switching');
hdlset_param('uz_count_switching', 'ProjectFolder', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_count_switching\hdl_prj');
hdlset_param('uz_count_switching', 'ResetInputPort', 'reset_x');
hdlset_param('uz_count_switching', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_count_switching', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_count_switching', 'SynthesisToolDeviceName', 'xqzu7ev-ffrc1156-2-i');
hdlset_param('uz_count_switching', 'SynthesisToolPackageName', '');
hdlset_param('uz_count_switching', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_count_switching', 'TargetDirectory', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_count_switching\hdl_prj\hdlsrc');
hdlset_param('uz_count_switching', 'TargetFrequency', 100);
hdlset_param('uz_count_switching', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_count_switching', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_count_switching/uz_count_switching', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_0', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_0', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_2', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_3', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_4', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_5', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_6', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_6', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_7', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_7', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/ss_in_8', 'IOInterface', 'External Port');
hdlset_param('uz_count_switching/uz_count_switching/ss_in_8', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/bResetAXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/bResetAXI', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_0_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_0_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_1_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_1_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_2_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_2_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_3_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_3_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_4_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_4_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_5_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_5_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_6_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_6_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_7_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_7_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_8_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_8_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('uz_count_switching/uz_count_switching/count_out_sum_AXI1', 'IOInterface', 'AXI4');
hdlset_param('uz_count_switching/uz_count_switching/count_out_sum_AXI1', 'IOInterfaceMapping', 'x"124"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_count_switching\hdl_prj';
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
hWC.RunExternalBuild = true;
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
hdlcoder.runWorkflow('uz_count_switching/uz_count_switching', hWC);
