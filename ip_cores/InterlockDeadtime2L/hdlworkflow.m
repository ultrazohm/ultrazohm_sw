%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 19:00:06 on 02/10/2020
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/00_Master_Arbeit/1_Diss/ultrazohm_sw/ip_cores/Interlock_Module_AXI/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'interlock_deadtime/interlock_deadti'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','interlock_deadtime/interlock_deadti');
%--------------------------------------------------------------------------
%
% hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','/media/ts/f13ad169-6e5b-4247-967f-23485df37fde/Xilinx/Vivado/2020.1/bin')

% Get path to current file
% Use fullfile to create path names
% https://de.mathworks.com/help/matlab/ref/fullfile.html
%
clc
clear

try
    hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','/media/ts/f13ad169-6e5b-4247-967f-23485df37fde/Xilinx/Vivado/2020.1/bin');
catch
    % nothing
end

try
    hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','/tools/Xilinx/Vivado/2020.1/bin')
catch
    % nothing
end

pa=which('hdlworkflow.m'); %gets the current (absolute) Path of this script
pa_to_proj=regexprep(pa,'hdlworkflow.m','');



%% Load the Model
load_system('uz_interlockDeadtime2L');

%% Model HDL Parameters
%% Set Model 'uz_interlockDeadtime2L' HDL parameters
hdlset_param('uz_interlockDeadtime2L', 'HDLSubsystem', 'uz_interlockDeadtime2L/uz_interlockDeadtime2L');
hdlset_param('uz_interlockDeadtime2L', 'PackagePostfix', '_pac');
hdlset_param('uz_interlockDeadtime2L', 'ResetInputPort', 'reset_x');
hdlset_param('uz_interlockDeadtime2L', 'ResetType', 'Synchronous');
hdlset_param('uz_interlockDeadtime2L', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_interlockDeadtime2L', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_interlockDeadtime2L', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_interlockDeadtime2L', 'SynthesisToolDeviceName', 'xczu9eg-ffvb1156-2-i');
hdlset_param('uz_interlockDeadtime2L', 'SynthesisToolPackageName', '');
hdlset_param('uz_interlockDeadtime2L', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_interlockDeadtime2L', 'TargetDirectory', pa_to_proj );
hdlset_param('uz_interlockDeadtime2L', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_interlockDeadtime2L', 'Workflow', 'IP Core Generation');

hdlset_param('uz_interlockDeadtime2L', 'CriticalPathEstimation', 'on');
hdlset_param('uz_interlockDeadtime2L', 'OptimizationReport', 'on');
hdlset_param('uz_interlockDeadtime2L', 'ResourceReport', 'on');
hdlset_param('uz_interlockDeadtime2L', 'Traceability', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L', 'ProcessorFPGASynchronization', 'Free running');
% Set Inport HDL parameters
% Set SubSystem HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S0', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S0', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S1', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S2', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S3', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S4', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S5', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/S5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_DelayCycles', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_DelayCycles', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_EnableOutput', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_EnableOutput', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_InverseBotSwitch', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_InverseBotSwitch', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s0_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s0_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s1_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s1_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s2_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s2_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s3_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s3_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s4_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s4_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s5_out', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/s5_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_enable', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_enable', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_DelayCycles', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_DelayCycles', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_InverseBotSwitch', 'IOInterface', 'AXI4');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/axi_fb_InverseBotSwitch', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/enableFB', 'IOInterface', 'External Port');
hdlset_param('uz_interlockDeadtime2L/uz_interlockDeadtime2L/enableFB', 'IOInterfaceMapping', '');
%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = pa_to_proj;
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
%hWC.CriticalPathEstimation=true;
%hWC.OptimizationReport=true;
%hWC.ResourceReport=true;

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
hdlcoder.runWorkflow('uz_interlockDeadtime2L/uz_interlockDeadtime2L', hWC);
