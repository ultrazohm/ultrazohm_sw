%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.14 (R2023a) at 14:55:44 on 28/07/2023
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_nonlinear');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model_nonlinear' HDL parameters
hdlset_param('uz_pmsm_model_nonlinear', 'AdaptivePipelining', 'on');
hdlset_param('uz_pmsm_model_nonlinear', 'CriticalPathEstimation', 'on');
fpconfig = hdlcoder.createFloatingPointTargetConfig('NATIVEFLOATINGPOINT' ...
, 'LatencyStrategy', 'Min',  'HandleDenormals', 'On' ...
);
hdlset_param('uz_pmsm_model_nonlinear', 'FloatingPointTargetConfiguration', fpconfig);
hdlset_param('uz_pmsm_model_nonlinear', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model_nonlinear', 'HDLSubsystem', 'uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear');
hdlset_param('uz_pmsm_model_nonlinear', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_nonlinear', 'Oversampling', 200);
hdlset_param('uz_pmsm_model_nonlinear', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_nonlinear', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_nonlinear', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_nonlinear', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_nonlinear', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_nonlinear', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model_nonlinear', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_nonlinear', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_nonlinear', 'TargetDirectory', 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear\hdl_prj\hdlsrc');
hdlset_param('uz_pmsm_model_nonlinear', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_nonlinear', 'UseFloatingPoint', 'on');
hdlset_param('uz_pmsm_model_nonlinear', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear', 'IPCoreName', 'uz_pmsm_model_nonlinear');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/simulate_mechanical', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_J', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_J', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mu', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mu', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/M_n0', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/M_n0', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_L_d', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_L_d', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_L_q', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/reciprocal_L_q', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/R1', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/R1', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/polepairs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/polepairs', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/psi_pm', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/psi_pm', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/inputs', 'IOInterfaceMapping', 'x"130"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/mechanical_system/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/outputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear/outputs', 'IOInterfaceMapping', 'x"150"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear\hdl_prj';
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
hdlcoder.runWorkflow('uz_pmsm_model_nonlinear/uz_pmsm_model_nonlinear', hWC);
