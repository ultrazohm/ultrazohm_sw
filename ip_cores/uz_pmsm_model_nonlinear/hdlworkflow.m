%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 23.2 (R2023b) at 13:52:18 on 23/05/2024
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\Philipp\uz_temp\ultrazohm_sw\ip_cores\uz_pmsm_model\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model/uz_pmsm_model'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model/uz_pmsm_model');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model/uz_pmsm_model');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model' HDL parameters
hdlset_param('uz_pmsm_model', 'CriticalPathEstimation', 'on');
fpconfig = hdlcoder.createFloatingPointTargetConfig('NATIVEFLOATINGPOINT' ...
, 'LatencyStrategy', 'Min',  'HandleDenormals', 'On' ...
);
hdlset_param('uz_pmsm_model', 'FloatingPointTargetConfiguration', fpconfig);
hdlset_param('uz_pmsm_model', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model', 'HDLSubsystem', 'uz_pmsm_model/uz_pmsm_model');
hdlset_param('uz_pmsm_model', 'LUTMapToRAM', 'off');
hdlset_param('uz_pmsm_model', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model', 'Oversampling', 200);
hdlset_param('uz_pmsm_model', 'ProjectFolder', 'hdl_prj');
hdlset_param('uz_pmsm_model', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-3-e');
hdlset_param('uz_pmsm_model', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('uz_pmsm_model', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model', 'UseFloatingPoint', 'on');
hdlset_param('uz_pmsm_model', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'IPCoreName', 'uz_pmsm_model');
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_mechanical', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_nonlinear', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_nonlinear', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_J', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_J', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/mu', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/mu', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/M_n0', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/M_n0', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/L_d', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/L_d', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/L_q', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/L_q', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/R1', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/R1', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/polepairs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/polepairs', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/psi_pm', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/psi_pm', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/fitting_parameter', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/fitting_parameter', 'IOInterfaceMapping', 'x"180"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/inputs', 'IOInterfaceMapping', 'x"130"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/mechanical_system/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/outputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model/uz_pmsm_model/outputs', 'IOInterfaceMapping', 'x"150"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj';
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
hdlcoder.runWorkflow('uz_pmsm_model/uz_pmsm_model', hWC);
