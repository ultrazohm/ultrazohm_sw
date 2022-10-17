%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 15:21:16 on 17/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_cost_function\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_8_cost_function/HDL_DUT4'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_8_cost_function/HDL_DUT4');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_8_cost_function');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_8_cost_function/HDL_DUT4');

%% Model HDL Parameters
%% Set Model 'parallel_8_cost_function' HDL parameters
hdlset_param('parallel_8_cost_function', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_8_cost_function', 'HDLSubsystem', 'parallel_8_cost_function/HDL_DUT4');
hdlset_param('parallel_8_cost_function', 'OptimizationReport', 'on');
hdlset_param('parallel_8_cost_function', 'ResetType', 'Synchronous');
hdlset_param('parallel_8_cost_function', 'ResourceReport', 'on');
hdlset_param('parallel_8_cost_function', 'ScalarizePorts', 'DUTLevel');
hdlset_param('parallel_8_cost_function', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_8_cost_function', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_8_cost_function', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_8_cost_function', 'SynthesisToolPackageName', '');
hdlset_param('parallel_8_cost_function', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_8_cost_function', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_cost_function\hdlsrc');
hdlset_param('parallel_8_cost_function', 'TargetFrequency', 100);
hdlset_param('parallel_8_cost_function', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_8_cost_function', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4', 'IPCoreName', 'parallel_8_cost_function');
hdlset_param('parallel_8_cost_function/HDL_DUT4', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/valid_in', 'IOInterface', 'External Port');
hdlset_param('parallel_8_cost_function/HDL_DUT4/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/Prediction', 'IOInterface', 'External Port');
hdlset_param('parallel_8_cost_function/HDL_DUT4/Prediction', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_cost_function/HDL_DUT4/id_ref_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_cost_function/HDL_DUT4/iq_ref_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/ix_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_cost_function/HDL_DUT4/ix_ref_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/iy_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_8_cost_function/HDL_DUT4/iy_ref_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/done', 'IOInterface', 'External Port');
hdlset_param('parallel_8_cost_function/HDL_DUT4/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_8_cost_function/HDL_DUT4/J', 'IOInterface', 'External Port');
hdlset_param('parallel_8_cost_function/HDL_DUT4/J', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_cost_function';
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
hdlcoder.runWorkflow('parallel_8_cost_function/HDL_DUT4', hWC);
