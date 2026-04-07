%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 24.1 (R2024a) at 10:27:43 on 07/04/2026
% This script was generated using the following parameter values:
%     Filename  : 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_6ph_spacevector_decode\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_6ph_spacevector_decode/uz_6ph_spacevector_decode'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_6ph_spacevector_decode/uz_6ph_spacevector_decode');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_6ph_spacevector_decode');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode');

%% Model HDL Parameters
%% Set Model 'uz_6ph_spacevector_decode' HDL parameters
hdlset_param('uz_6ph_spacevector_decode', 'CriticalPathEstimation', 'on');
hdlset_param('uz_6ph_spacevector_decode', 'HDLSubsystem', 'uz_6ph_spacevector_decode/uz_6ph_spacevector_decode');
hdlset_param('uz_6ph_spacevector_decode', 'ProjectFolder', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_6ph_spacevector_decode\hdl_prj');
hdlset_param('uz_6ph_spacevector_decode', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_6ph_spacevector_decode', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_6ph_spacevector_decode', 'SynthesisToolDeviceName', 'xczu9eg-ffvb1156-1-e');
hdlset_param('uz_6ph_spacevector_decode', 'SynthesisToolPackageName', '');
hdlset_param('uz_6ph_spacevector_decode', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_6ph_spacevector_decode', 'TargetDirectory', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_6ph_spacevector_decode\hdl_prj\hdlsrc');
hdlset_param('uz_6ph_spacevector_decode', 'TargetFrequency', 100);
hdlset_param('uz_6ph_spacevector_decode', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_6ph_spacevector_decode', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode', 'IPCoreName', 'uz_6ph_sv_decode_ip');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in1', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in2', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in3', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in4', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in5', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in6', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/in6', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/trigger', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/trigger', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out1_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out1_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out2_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out2_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out3_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out3_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out4_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out4_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out5_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out5_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out6_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out6_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out7_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out7_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out8_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out8_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out9_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out9_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out10_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out10_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out11_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out11_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out12_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out12_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out13_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out13_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out14_AXI', 'IOInterface', 'AXI4');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out14_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out1', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out2', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out3', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out4', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out5', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out6', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out7', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out8', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out9', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out10', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out11', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out12', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out12', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out13', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out13', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out14', 'IOInterface', 'External Port');
hdlset_param('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode/out14', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_6ph_spacevector_decode\hdl_prj';
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
hWC.OperatingSystem = 'Linux';
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
hWC.MaxNumOfCoresForBuild = 'synthesis tool default';

% Set properties related to 'RunTaskProgramTargetDevice' Task
hWC.ProgrammingMethod = hdlcoder.ProgrammingMethod.JTAG;
hWC.IPAddress = '';
hWC.SSHUsername = '';
hWC.SSHPassword = '';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('uz_6ph_spacevector_decode/uz_6ph_spacevector_decode', hWC);
