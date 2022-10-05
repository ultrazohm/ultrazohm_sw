%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:49:34 on 12/05/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\uz_axi_mytestIP\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_axi_mytestIP/uz_axi_mytestIP'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_axi_mytestIP/uz_axi_mytestIP');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_axi_mytestIP');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_axi_mytestIP/uz_axi_mytestIP');

%% Model HDL Parameters
%% Set Model 'uz_axi_mytestIP' HDL parameters
hdlset_param('uz_axi_mytestIP', 'CriticalPathEstimation', 'on');
hdlset_param('uz_axi_mytestIP', 'HDLSubsystem', 'uz_axi_mytestIP/uz_axi_mytestIP');
hdlset_param('uz_axi_mytestIP', 'OptimizationReport', 'on');
hdlset_param('uz_axi_mytestIP', 'ResetType', 'Synchronous');
hdlset_param('uz_axi_mytestIP', 'ResourceReport', 'on');
hdlset_param('uz_axi_mytestIP', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_axi_mytestIP', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_axi_mytestIP', 'SynthesisToolDeviceName', 'xczu9eg-ffvb1156-1-e');
hdlset_param('uz_axi_mytestIP', 'SynthesisToolPackageName', '');
hdlset_param('uz_axi_mytestIP', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_axi_mytestIP', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\uz_axi_mytestIP\hdl_prj\hdlsrc');
hdlset_param('uz_axi_mytestIP', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_axi_mytestIP', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/A_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/A_int32', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/B_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/B_int32', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/A_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/A_uint32', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/B_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/B_uint32', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/In5', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/In5', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/In6', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/In6', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/C_int32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/C_int32', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/C_uint32', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/C_uint32', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/Out3', 'IOInterface', 'AXI4');
hdlset_param('uz_axi_mytestIP/uz_axi_mytestIP/Out3', 'IOInterfaceMapping', 'x"120"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\uz_axi_mytestIP\hdl_prj';
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
hdlcoder.runWorkflow('uz_axi_mytestIP/uz_axi_mytestIP', hWC);
