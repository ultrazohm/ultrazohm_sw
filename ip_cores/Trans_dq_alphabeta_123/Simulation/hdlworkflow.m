%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:33:56 on 27/05/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\Trans_dq_alphabeta_123\Simulation\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('Transformation_dq_alphabeta_123_V1');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1');

%% Model HDL Parameters
%% Set Model 'Transformation_dq_alphabeta_123_V1' HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1', 'CriticalPathEstimation', 'on');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'HDLSubsystem', 'Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'OptimizationReport', 'on');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'ReferenceDesign', 'Default system');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'ResetType', 'Synchronous');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'ResourceReport', 'on');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'SynthesisToolPackageName', '');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'SynthesisToolSpeedValue', '');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\Trans_dq_alphabeta_123\Simulation\hdlsrc');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'TargetFrequency', 50);
hdlset_param('Transformation_dq_alphabeta_123_V1', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'Traceability', 'on');
hdlset_param('Transformation_dq_alphabeta_123_V1', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1', 'InputPipeline', 1);
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1', 'IPCoreName', 'Trans_dq_alphabeta_123_ip');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1', 'OutputPipeline', 1);
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/theta', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/theta', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/theta_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/theta_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/CurrentValid_in', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/CurrentValid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Id_ref_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Iq_ref_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Sum HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Add3', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Compare Limit_High', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Compare Limit_Low', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Cosine', 'InputPipeline', 1);
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/Cosine', 'OutputPipeline', 1);

% Set Gain HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ScaleTheta', 'ConstMultiplierOptimization', 'auto');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/dq_Done', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/dq_Done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/sin', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/sin', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/cos', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/cos', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ialpha', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ialpha', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ialpha_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ialpha_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ibeta', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ibeta', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ibeta_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/ibeta_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i1', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i1_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i2', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i2_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i3', 'IOInterface', 'External Port');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1/i3_AXI', 'IOInterfaceMapping', 'x"124"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\Trans_dq_alphabeta_123\Simulation';
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
hdlcoder.runWorkflow('Transformation_dq_alphabeta_123_V1/Trans_dq_alphabeta_123_fix_V1', hWC);
