%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 19:15:31 on 21/03/2021
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/ultrazohm_test/ultrazohm_sw/ip_cores/AXI_testIP/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'AXI_testIP/AXI_testIP'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','AXI_testIP/AXI_testIP');
%--------------------------------------------------------------------------
clc
clear
pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');
%% Load the Model
load_system('uz_axi_testIP');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('AXI_testIP/AXI_testIP');

%% Model HDL Parameters
%% Set Model 'AXI_testIP' HDL parameters
hdlset_param('uz_axi_testIP', 'CriticalPathEstimation', 'on');
hdlset_param('uz_axi_testIP', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('uz_axi_testIP', 'HDLSubsystem', 'uz_axi_testIP/uz_axi_testIP');
hdlset_param('uz_axi_testIP', 'ResetType', 'Synchronous');
hdlset_param('uz_axi_testIP', 'ResourceReport', 'on');
hdlset_param('uz_axi_testIP', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_axi_testIP', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_axi_testIP', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_axi_testIP', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-2-i');
hdlset_param('uz_axi_testIP', 'SynthesisToolPackageName', '');
hdlset_param('uz_axi_testIP', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_axi_testIP', 'TargetDirectory', 'uz_axi_testIP/hdlsrc');
hdlset_param('uz_axi_testIP', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_axi_testIP', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_axi_testIP/uz_axi_testIP', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_float', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_float', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_float', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_float', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_uint32', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_uint32', 'IOInterfaceMapping', 'x"160"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_int32', 'IOInterfaceMapping', 'x"180"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_int32', 'IOInterfaceMapping', 'x"1A0"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_fx_1_16_5', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/A_fx_1_16_5', 'IOInterfaceMapping', 'x"1C0"');

% Set Inport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_fx_1_16_5', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/B_fx_1_16_5', 'IOInterfaceMapping', 'x"1E0"');

% Set Outport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_float', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_float', 'IOInterfaceMapping', 'x"200"');

% Set Outport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_uint32', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_int32', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_fx_1_16_5', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_testIP/uz_axi_testIP/C_fx_1_16_5', 'IOInterfaceMapping', 'x"260"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'uz_axi_testIP';
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
hWC.GenerateSoftwareInterfaceScript = true;

% Set properties related to 'RunTaskBuildFPGABitstream' Task
hWC.RunExternalBuild = false;
hWC.TclFileForSynthesisBuild = hdlcoder.BuildOption.Default;
hWC.CustomBuildTclFile = '';

% Set properties related to 'RunTaskProgramTargetDevice' Task
hWC.ProgrammingMethod = hdlcoder.ProgrammingMethod.JTAG;
hWC.IPAddress = '';
hWC.SSHUsername = '';
hWC.SSHPassword = '';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('uz_axi_testIP/uz_axi_testIP', hWC);
