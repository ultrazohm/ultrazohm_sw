%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 23.2 (R2023b) at 15:34:25 on 12/12/2023
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_6LUT_pd');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model_6LUT_pd' HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd', 'CriticalPathEstimation', 'on');
fpconfig = hdlcoder.createFloatingPointTargetConfig('NATIVEFLOATINGPOINT' ...
, 'LatencyStrategy', 'Min',  'HandleDenormals', 'On' ...
);
hdlset_param('uz_pmsm_model_6LUT_pd', 'FloatingPointTargetConfiguration', fpconfig);
hdlset_param('uz_pmsm_model_6LUT_pd', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model_6LUT_pd', 'HDLSubsystem', 'uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear');
hdlset_param('uz_pmsm_model_6LUT_pd', 'LUTMapToRAM', 'off');
hdlset_param('uz_pmsm_model_6LUT_pd', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_6LUT_pd', 'Oversampling', 200);
hdlset_param('uz_pmsm_model_6LUT_pd', 'ProjectFolder', 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdl_prj');
hdlset_param('uz_pmsm_model_6LUT_pd', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_6LUT_pd', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_6LUT_pd', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_6LUT_pd', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_6LUT_pd', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_6LUT_pd', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1LV-i');
hdlset_param('uz_pmsm_model_6LUT_pd', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_6LUT_pd', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_6LUT_pd', 'TargetDirectory', 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdl_prj\hdlsrc');
hdlset_param('uz_pmsm_model_6LUT_pd', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_6LUT_pd', 'UseFloatingPoint', 'on');
hdlset_param('uz_pmsm_model_6LUT_pd', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear', 'IPCoreName', 'uz_pmsm_nonlinear');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/simulate_mechanical', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/simulate_nonlinear', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/simulate_nonlinear', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/reciprocal_J', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/reciprocal_J', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mu', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mu', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/M_n0', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/M_n0', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/R1', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/R1', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/polepairs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/polepairs', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/Ld', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/Ld', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/Lq', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/Lq', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/psi_pm', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/psi_pm', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/fitting_parameters', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/fitting_parameters', 'IOInterfaceMapping', 'x"180"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/inputs', 'IOInterfaceMapping', 'x"130"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/mechanical_system/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/outputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear/outputs', 'IOInterfaceMapping', 'x"150"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear_6LUT\hdl_prj';
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
hdlcoder.runWorkflow('uz_pmsm_model_6LUT_pd/uz_pmsm_model_nonlinear', hWC);
