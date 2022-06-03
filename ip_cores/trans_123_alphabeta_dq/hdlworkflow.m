%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 10:46:07 on 03/06/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\trans_123_alphabeta_dq\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12');
%--------------------------------------------------------------------------

%% Load the Model
load_system('trans_123_alphabeta_dq_V1');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12');

%% Model HDL Parameters
%% Set Model 'trans_123_alphabeta_dq_V1' HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1', 'CriticalPathEstimation', 'on');
hdlset_param('trans_123_alphabeta_dq_V1', 'HDLSubsystem', 'trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12');
hdlset_param('trans_123_alphabeta_dq_V1', 'OptimizationReport', 'on');
hdlset_param('trans_123_alphabeta_dq_V1', 'ReferenceDesign', 'Default system');
hdlset_param('trans_123_alphabeta_dq_V1', 'ResetType', 'Synchronous');
hdlset_param('trans_123_alphabeta_dq_V1', 'ResourceReport', 'on');
hdlset_param('trans_123_alphabeta_dq_V1', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('trans_123_alphabeta_dq_V1', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('trans_123_alphabeta_dq_V1', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('trans_123_alphabeta_dq_V1', 'SynthesisToolPackageName', '');
hdlset_param('trans_123_alphabeta_dq_V1', 'SynthesisToolSpeedValue', '');
hdlset_param('trans_123_alphabeta_dq_V1', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\trans_123_alphabeta_dq\hdlsrc');
hdlset_param('trans_123_alphabeta_dq_V1', 'TargetFrequency', 50);
hdlset_param('trans_123_alphabeta_dq_V1', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('trans_123_alphabeta_dq_V1', 'Traceability', 'on');
hdlset_param('trans_123_alphabeta_dq_V1', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12', 'InputPipeline', 1);
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12', 'IPCoreName', 'Trans_123_alphabeta_dq_V12_ip');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12', 'OutputPipeline', 1);
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph1', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph2', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph3', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i_ph3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/theta', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/theta', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/theta_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/theta_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/CurrentValid_in', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/CurrentValid_in', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Add3', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Compare Limit_High', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Compare Limit_Low', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Cosine', 'InputPipeline', 1);
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Cosine', 'OutputPipeline', 1);

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain1', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain2', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain4', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain5', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain6', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/Gain7', 'ConstMultiplierOptimization', 'auto');

% Set Gain HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ScaleTheta', 'ConstMultiplierOptimization', 'auto');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/id', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/id', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/iq', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/iq', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/id_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/id_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/iq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/iq_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/dq_Done', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/dq_Done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/sin', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/sin', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/cos', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/cos', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i1_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i2_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/i3_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ialpha', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ialpha', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ialpha_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ialpha_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ibeta', 'IOInterface', 'External Port');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ibeta', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ibeta_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12/ibeta_AXI', 'IOInterfaceMapping', 'x"11C"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\trans_123_alphabeta_dq';
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
hdlcoder.runWorkflow('trans_123_alphabeta_dq_V1/Trans_123_dq_fix_V12', hWC);
