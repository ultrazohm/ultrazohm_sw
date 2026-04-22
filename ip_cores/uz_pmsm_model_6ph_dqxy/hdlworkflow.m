%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 10:12:28 on 30/07/2021
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Documents/ultrazohm_sw/ip_cores/uz_pmsm_model/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_6ph_dqxy/uz_pmsm_model'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_6ph_dqxy/uz_pmsm_model');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_6ph_dqxy');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_6ph_dqxy/uz_pmsm_model');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model' HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy', 'CriticalPathEstimation', 'on');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'MIN',  'HandleDenormals', 'on') ...
);
hdlset_param('uz_pmsm_model_6ph_dqxy', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'HDLSubsystem', 'uz_pmsm_model_6ph_dqxy/uz_pmsm_model');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'HierarchicalDistPipelining', 'on');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'LUTMapToRAM', 'off');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'Oversampling', 50);
hdlset_param('uz_pmsm_model_6ph_dqxy', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_6ph_dqxy', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model', 'IPCoreName', 'uz_pmsm_model_6ph_dqxy');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/simulate_mechanical', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mu', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mu', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/M_n0', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/M_n0', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_d', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_d', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_q', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_q', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/R1', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/R1', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/polepairs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/polepairs', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/psi_pm', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/psi_pm', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_x', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_x', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_y', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/reciprocal_L_y', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/inputs', 'IOInterfaceMapping', 'x"140"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mechanical_system', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/mechanical_system/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/pmsm/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/pmsm/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/outputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dqxy/uz_pmsm_model/outputs', 'IOInterfaceMapping', 'x"180"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');
hWC.AllowUnsupportedToolVersion = true;

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
hdlcoder.runWorkflow('uz_pmsm_model_6ph_dqxy/uz_pmsm_model', hWC);
