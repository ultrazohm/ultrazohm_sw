%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 13:25:00 on 15/08/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\VSD_and_Park_transformation_6Phase\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'VSD_and_Park_transformation_6Phase/vsd_and_park_tra'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','VSD_and_Park_transformation_6Phase/vsd_and_park_tra');
%--------------------------------------------------------------------------

%% Load the Model
load_system('VSD_and_Park_transformation_6Phase');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('VSD_and_Park_transformation_6Phase/vsd_and_park_tra');

%% Model HDL Parameters
%% Set Model 'VSD_and_Park_transformation_6Phase' HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase', 'CriticalPathEstimation', 'on');
hdlset_param('VSD_and_Park_transformation_6Phase', 'HDLSubsystem', 'VSD_and_Park_transformation_6Phase/vsd_and_park_tra');
hdlset_param('VSD_and_Park_transformation_6Phase', 'OptimizationReport', 'on');
hdlset_param('VSD_and_Park_transformation_6Phase', 'PackagePostfix', '_pac');
hdlset_param('VSD_and_Park_transformation_6Phase', 'ResetInputPort', 'reset_x');
hdlset_param('VSD_and_Park_transformation_6Phase', 'ResetType', 'Synchronous');
hdlset_param('VSD_and_Park_transformation_6Phase', 'ResourceReport', 'on');
hdlset_param('VSD_and_Park_transformation_6Phase', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('VSD_and_Park_transformation_6Phase', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('VSD_and_Park_transformation_6Phase', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('VSD_and_Park_transformation_6Phase', 'SynthesisToolPackageName', '');
hdlset_param('VSD_and_Park_transformation_6Phase', 'SynthesisToolSpeedValue', '');
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\VSD_and_Park_transformation_6Phase\hdlsrc');
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetFrequency', 100);
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('VSD_and_Park_transformation_6Phase', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra', 'IPCoreName', 'VSD_and_Park_transformation');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_a1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_a1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_b1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_b1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_c1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_c1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_a2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_a2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_b2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_b2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_c2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_c2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/theta_el', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/theta_el_offset_', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/theta_el_offset_', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/curent_valid_in', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/curent_valid_in', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/Add3', 'OutputPipeline', 1);

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_alpha', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_alpha', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_alpha_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_alpha_axi', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_beta', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_beta', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_beta_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_beta_axi', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_d', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_d', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_d_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_d_axi', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_q', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_q', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_q_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_q_axi', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_x', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_x', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_x_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_x_axi', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_y', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_y', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_y_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_y_axi', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_plus', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_plus', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_plus_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_plus_axi', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_minus', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_minus', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_minus_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/i_0_minus_axi', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/done', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra/done', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\VSD_and_Park_transformation_6Phase';
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
hdlcoder.runWorkflow('VSD_and_Park_transformation_6Phase/vsd_and_park_tra', hWC);
