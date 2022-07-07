%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021b) at 14:22:40 on 10/03/2022
% This script was generated using the following parameter values:
%     Filename  : '/ultrazohm_sw/ip_cores/uz_inverter_3ph/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_inverter_3ph/uz_inverter_3ph'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph');
%--------------------------------------------------------------------------

%% Load the Model
load_system('gmStateSpaceHDL_uz_inverter_3ph');

%% Restore the Model to default HDL parameters
%%hdlrestoreparams('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model' HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'CriticalPathEstimation', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'MIN',  'HandleDenormals', 'on') ...
);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'GenerateValidationModel', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'HDLSubsystem', 'gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'HierarchicalDistPipelining', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'LUTMapToRAM', 'off');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'OptimizationReport', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'Oversampling', 50);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'ResetType', 'Synchronous');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'ResourceReport', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'ScalarizePorts', 'DUTLevel');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolPackageName', '');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolSpeedValue', '');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'Workflow', 'IP Core Generation');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'MaskParameterAsGeneric', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'FPToleranceValue', 1.000000e-03);


% Set SubSystem HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', 'AXI4SlaveIDWidth', '12');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', 'IPCoreName', 'uz_inverter_3ph');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters Gate Signals 6
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/gate_ps', 'IOInterface', 'AXI4');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/gate_ps', 'IOInterfaceMapping', 'x"160"');

% Set Inport HDL parameters Iabc 3
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/i_abc_ps', 'IOInterface', 'AXI4');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/i_abc_ps', 'IOInterfaceMapping', 'x"140"');

% Set SubSystem HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters Uab_bc
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/u_abc_ps', 'IOInterface', 'AXI4');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/u_abc_ps', 'IOInterfaceMapping', 'x"110"');


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
hdlcoder.runWorkflow('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', hWC);