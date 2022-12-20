%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 14:32:03 on 12/10/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\test_cost_function_only\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'cost_function_only/HDL_DUT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','cost_function_only/HDL_DUT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('cost_function_only');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('cost_function_only/HDL_DUT');

%% Model HDL Parameters
%% Set Model 'cost_function_only' HDL parameters
hdlset_param('cost_function_only', 'CriticalPathEstimation', 'on');
hdlset_param('cost_function_only', 'HDLSubsystem', 'cost_function_only/HDL_DUT');
hdlset_param('cost_function_only', 'OptimizationReport', 'on');
hdlset_param('cost_function_only', 'ResetType', 'Synchronous');
hdlset_param('cost_function_only', 'ResourceReport', 'on');
hdlset_param('cost_function_only', 'ScalarizePorts', 'DUTLevel');
hdlset_param('cost_function_only', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('cost_function_only', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('cost_function_only', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1LV-i');
hdlset_param('cost_function_only', 'SynthesisToolPackageName', '');
hdlset_param('cost_function_only', 'SynthesisToolSpeedValue', '');
hdlset_param('cost_function_only', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\test_cost_function_only\hdlsrc');
hdlset_param('cost_function_only', 'TargetFrequency', 100);
hdlset_param('cost_function_only', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('cost_function_only', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('cost_function_only/HDL_DUT', 'IPCoreName', 'test_cost_function_only');
hdlset_param('cost_function_only/HDL_DUT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/valid_in', 'IOInterface', 'External Port');
hdlset_param('cost_function_only/HDL_DUT/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/Prediction', 'IOInterface', 'External Port');
hdlset_param('cost_function_only/HDL_DUT/Prediction', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('cost_function_only/HDL_DUT/id_ref_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('cost_function_only/HDL_DUT/iq_ref_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/ix_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('cost_function_only/HDL_DUT/ix_ref_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/iy_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('cost_function_only/HDL_DUT/iy_ref_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/done', 'IOInterface', 'External Port');
hdlset_param('cost_function_only/HDL_DUT/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('cost_function_only/HDL_DUT/J', 'IOInterface', 'External Port');
hdlset_param('cost_function_only/HDL_DUT/J', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\test_cost_function_only';
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
hdlcoder.runWorkflow('cost_function_only/HDL_DUT', hWC);
