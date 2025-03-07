%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 10:05:59 on 17/06/2021
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/ultrazohm_sw/ip_cores/uz_plantModel_pt1/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_plantModel_pt1/uz_plantModel_pt1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_plantModel_pt1/uz_plantModel_pt1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_plantModel_pt1');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_plantModel_pt1/uz_plantModel_pt1');

%% Model HDL Parameters
%% Set Model 'uz_plantModel_pt1' HDL parameters
hdlset_param('uz_plantModel_pt1', 'CriticalPathEstimation', 'on');
hdlset_param('uz_plantModel_pt1', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('uz_plantModel_pt1', 'HDLSubsystem', 'uz_plantModel_pt1/uz_plantModel_pt1');
hdlset_param('uz_plantModel_pt1', 'HierarchicalDistPipelining', 'on');
hdlset_param('uz_plantModel_pt1', 'OptimizationReport', 'on');
hdlset_param('uz_plantModel_pt1', 'Oversampling', 100);
hdlset_param('uz_plantModel_pt1', 'ResetType', 'Synchronous');
hdlset_param('uz_plantModel_pt1', 'ResourceReport', 'on');
hdlset_param('uz_plantModel_pt1', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_plantModel_pt1', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_plantModel_pt1', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_plantModel_pt1', 'SynthesisToolPackageName', '');
hdlset_param('uz_plantModel_pt1', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_plantModel_pt1', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_plantModel_pt1', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_plantModel_pt1', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1', 'IPCoreName', 'uz_plantModel_pt1');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1', 'OutputPipeline', 10);
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/input', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/input', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/gain', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/gain', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/reciprocal_time_constant', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/reciprocal_time_constant', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/reset', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/reset', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/output', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_plantModel_pt1/uz_plantModel_pt1/output', 'IOInterfaceMapping', 'x"110"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj';
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
hdlcoder.runWorkflow('uz_plantModel_pt1/uz_plantModel_pt1', hWC);
