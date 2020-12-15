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
load_system('interlock_deadtime');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('interlock_deadtime/interlock_deadtime');

%% Model HDL Parameters
%% Set Model 'interlock_deadtime' HDL parameters
hdlset_param('interlock_deadtime', 'HDLSubsystem', 'interlock_deadtime/interlock_deadtime');
hdlset_param('interlock_deadtime', 'PackagePostfix', '_pac');
hdlset_param('interlock_deadtime', 'ResetInputPort', 'reset_x');
hdlset_param('interlock_deadtime', 'ResetType', 'Synchronous');
hdlset_param('interlock_deadtime', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('interlock_deadtime', 'ScalarizePorts', 'DUTLevel');
hdlset_param('interlock_deadtime', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('interlock_deadtime', 'SynthesisToolDeviceName', 'xczu9eg-ffvb1156-2-i');
hdlset_param('interlock_deadtime', 'SynthesisToolPackageName', '');
hdlset_param('interlock_deadtime', 'SynthesisToolSpeedValue', '');
hdlset_param('interlock_deadtime', 'TargetDirectory', pa_to_proj );
hdlset_param('interlock_deadtime', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('interlock_deadtime', 'Workflow', 'IP Core Generation');

hdlset_param('interlock_deadtime', 'CriticalPathEstimation', 'on');
hdlset_param('interlock_deadtime', 'OptimizationReport', 'on');
hdlset_param('interlock_deadtime', 'ResourceReport', 'on');
hdlset_param('interlock_deadtime', 'Traceability', 'on');

% Set SubSystem HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime', 'ProcessorFPGASynchronization', 'Free running');
% Set Inport HDL parameters
% Set SubSystem HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime', 'AXI4SlaveIDWidth', '12');
hdlset_param('interlock_deadtime/interlock_deadtime', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S0', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S0', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S1', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S2', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S3', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S4', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/S5', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/S5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_DelayCycles', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_DelayCycles', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_EnableOutput', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_EnableOutput', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_InverseBotSwitch', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_InverseBotSwitch', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s0_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s0_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s1_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s1_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s2_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s2_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s3_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s3_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s4_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s4_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/s5_out', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/s5_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_enable', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_enable', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_DelayCycles', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_DelayCycles', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_InverseBotSwitch', 'IOInterface', 'AXI4');
hdlset_param('interlock_deadtime/interlock_deadtime/AXI_fb_InverseBotSwitch', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('interlock_deadtime/interlock_deadtime/enableFB', 'IOInterface', 'External Port');
hdlset_param('interlock_deadtime/interlock_deadtime/enableFB', 'IOInterfaceMapping', '');
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
hdlcoder.runWorkflow('interlock_deadtime/interlock_deadtime', hWC);
