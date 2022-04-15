%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 09:39:22 on 17/02/2021
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_9ph\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_9ph/uz_pmsm_model_9ph'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_9ph/uz_pmsm_model_9ph');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_9ph');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_9ph/uz_pmsm_model_9ph');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model_9ph' HDL parameters
hdlset_param('uz_pmsm_model_9ph', 'CriticalPathEstimation', 'on');
hdlset_param('uz_pmsm_model_9ph', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'MIN',  'HandleDenormals', 'on') ...
);
hdlset_param('uz_pmsm_model_9ph', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model_9ph', 'HDLSubsystem', 'uz_pmsm_model_9ph/uz_pmsm_model_9ph');
hdlset_param('uz_pmsm_model_9ph', 'HierarchicalDistPipelining', 'on');
hdlset_param('uz_pmsm_model_9ph', 'LUTMapToRAM', 'off');
hdlset_param('uz_pmsm_model_9ph', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_9ph', 'Oversampling', 100);
hdlset_param('uz_pmsm_model_9ph', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_9ph', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_9ph', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_9ph', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_9ph', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_9ph', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model_9ph', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_9ph', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_9ph', 'TargetDirectory', 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_9ph\hdl_prj\hdlsrc');
hdlset_param('uz_pmsm_model_9ph', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_9ph', 'Workflow', 'IP Core Generation');



%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_9ph\hdl_prj';
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
hdlcoder.runWorkflow('uz_pmsm_model_9ph/uz_pmsm_model_9ph', hWC);
