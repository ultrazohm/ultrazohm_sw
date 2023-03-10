%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.11 (R2021b) at 11:06:01 on 17/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_ninephase_VSD_transformation\hdlworkflow_trans.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_ninephase_VSD_transformation/abc_to_dq'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_ninephase_VSD_transformation/abc_to_dq');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_ninephase_VSD_transformation');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_ninephase_VSD_transformation/abc_to_dq');

%% Model HDL Parameters
%% Set Model 'uz_ninephase_VSD_transformation' HDL parameters
hdlset_param('uz_ninephase_VSD_transformation', 'AdaptivePipelining', 'on');
hdlset_param('uz_ninephase_VSD_transformation', 'CriticalPathEstimation', 'on');
hdlset_param('uz_ninephase_VSD_transformation', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('uz_ninephase_VSD_transformation', 'HDLSubsystem', 'uz_ninephase_VSD_transformation/abc_to_dq');
hdlset_param('uz_ninephase_VSD_transformation', 'MapPipelineDelaysToRAM', 'on');
hdlset_param('uz_ninephase_VSD_transformation', 'OptimizationReport', 'on');
hdlset_param('uz_ninephase_VSD_transformation', 'Oversampling', 100);
hdlset_param('uz_ninephase_VSD_transformation', 'ResetType', 'Synchronous');
hdlset_param('uz_ninephase_VSD_transformation', 'ResourceReport', 'on');
hdlset_param('uz_ninephase_VSD_transformation', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_ninephase_VSD_transformation', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_ninephase_VSD_transformation', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_ninephase_VSD_transformation', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_ninephase_VSD_transformation', 'SynthesisToolPackageName', '');
hdlset_param('uz_ninephase_VSD_transformation', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_ninephase_VSD_transformation', 'TargetDirectory', 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_ninephase_VSD_transformation\hdl_proj\hdlsrc');
hdlset_param('uz_ninephase_VSD_transformation', 'TargetFrequency', 100);
hdlset_param('uz_ninephase_VSD_transformation', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_ninephase_VSD_transformation', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq', 'IPCoreName', 'uz_ninephase_VSD_transformation');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq', 'IPCoreVersion', '1.0');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_in_dq', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_in_dq', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/theta_el', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/trigger_new_values', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/trigger_new_values', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc1_ll_pl', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc1_ll_pl', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc2_ll_pl', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc2_ll_pl', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc3_ll_pl', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc3_ll_pl', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Line-Line to Phase voltage', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Line-Line to Phase voltage1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Line-Line to Phase voltage2', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Transformation', 'FlattenHierarchy', 'on');

hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Transformation/MatrixMultiply', 'Architecture', 'Matrix Multiply');
% Set Product HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/Transformation/MatrixMultiply', 'DotProductStrategy', 'Parallel Multiply-Accumulate');

% Set SubSystem HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/inverse Transformation', 'FlattenHierarchy', 'on');

hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/inverse Transformation/MatrixMultiply', 'Architecture', 'Matrix Multiply');
% Set Product HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/inverse Transformation/MatrixMultiply', 'DotProductStrategy', 'Serial Multiply-Accumulate');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/theta_el_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/theta_el_axi', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_out_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_out_axi', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_1', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_2', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_3', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_abc_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_out_dq', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/x_out_dq', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/refresh_values', 'IOInterface', 'External Port');
hdlset_param('uz_ninephase_VSD_transformation/abc_to_dq/refresh_values', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw\ip_cores\uz_ninephase_VSD_transformation\hdl_proj';
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
hdlcoder.runWorkflow('uz_ninephase_VSD_transformation/abc_to_dq', hWC);
