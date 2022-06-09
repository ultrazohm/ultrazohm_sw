%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.11 (R2021b) at 11:11:47 on 08/06/2022
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/ultrazohm_sw/ip_cores/uz_pmsm_model_9ph/hdlworkflow_trans.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq');
%--------------------------------------------------------------------------

%% Load the Model
load_system('Copy_of_uz_pmsm_model_9ph_21b_all_double');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq');

%% Model HDL Parameters
%% Set Model 'Copy_of_uz_pmsm_model_9ph_21b_all_double' HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'AdaptivePipelining', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'CriticalPathEstimation', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'HDLSubsystem', 'Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'MapPipelineDelaysToRAM', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'OptimizationReport', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ResetType', 'Synchronous');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ResourceReport', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ScalarizePorts', 'DUTLevel');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolPackageName', '');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolSpeedValue', '');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'TargetDirectory', 'hdl_prj123/hdlsrc');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'TargetFrequency', 100);
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq', 'AXI4SlaveIDWidth', '12');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq', 'IPCoreName', 'uz_pmsm9ph_trans_100mhz');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/current_in_dq', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/current_in_dq', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/theta_el1', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/theta_el1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/trigger_new_values', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/trigger_new_values', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc1_pl', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc1_pl', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc2_pl', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc2_pl', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc3_pl', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/u_abc3_pl', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Line-Line to Phase voltage', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Line-Line to Phase voltage1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Line-Line to Phase voltage2', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation', 'FlattenHierarchy', 'on');

hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation/MatrixMultiply', 'Architecture', 'Matrix Multiply');
% Set Product HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation/MatrixMultiply', 'DotProductStrategy', 'Parallel Multiply-Accumulate');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation1', 'FlattenHierarchy', 'on');

hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation1/MatrixMultiply', 'Architecture', 'Matrix Multiply');
% Set Product HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/Transformation1/MatrixMultiply', 'DotProductStrategy', 'Serial Multiply-Accumulate');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_1', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_2', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_3', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/voltage_out_dq_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/i_abc_out_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/i_abc_out_axi', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_1', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_2', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_3', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/I_abc_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/theta_el_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq/theta_el_axi', 'IOInterfaceMapping', 'x"100"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj123';
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
hdlcoder.runWorkflow('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/abc_to_dq', hWC);
