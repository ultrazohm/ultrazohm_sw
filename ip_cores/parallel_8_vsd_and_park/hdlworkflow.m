%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 09:18:33 on 16/11/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_8_vsd_and_park\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'VSD_and_Park_transformation_6Phase/vsd_and_park_tra1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','VSD_and_Park_transformation_6Phase/vsd_and_park_tra1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('VSD_and_Park_transformation_6Phase');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1');

%% Model HDL Parameters
%% Set Model 'VSD_and_Park_transformation_6Phase' HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase', 'CriticalPathEstimation', 'on');
hdlset_param('VSD_and_Park_transformation_6Phase', 'HDLSubsystem', 'VSD_and_Park_transformation_6Phase/vsd_and_park_tra1');
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
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_8_vsd_and_park\hdlsrc');
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetFrequency', 100);
hdlset_param('VSD_and_Park_transformation_6Phase', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('VSD_and_Park_transformation_6Phase', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1', 'IPCoreName', 'parallel_8_sim_vsd_and_park');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c1', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c2', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/theta_el', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/theta_el_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/theta_el_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/curent_valid_in', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/curent_valid_in', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/Add3', 'OutputPipeline', 1);

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_alpha', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_alpha', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_beta', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_beta', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_d', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_d', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_q', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_q', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_x', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_x', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_y', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_y', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_0_plus', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_0_plus', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_0_minus', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_0_minus', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/done_vsd_and_park', 'IOInterface', 'External Port');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/done_vsd_and_park', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a1_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a1_axi', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b1_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b1_axi', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c1_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c1_axi', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a2_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_a2_axi', 'IOInterfaceMapping', 'x"130"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b2_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_b2_axi', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c2_axi', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_c2_axi', 'IOInterfaceMapping', 'x"138"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_d_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_d_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_q_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_q_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_x_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_x_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_y_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1/i_y_AXI', 'IOInterfaceMapping', 'x"110"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_8_vsd_and_park';
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
hdlcoder.runWorkflow('VSD_and_Park_transformation_6Phase/vsd_and_park_tra1', hWC);
