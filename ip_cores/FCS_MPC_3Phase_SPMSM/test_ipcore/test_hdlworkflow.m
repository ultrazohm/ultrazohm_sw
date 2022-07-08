%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 13:10:05 on 08/07/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\test_ipcore\test_hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('FCS_MPC_3Phase_SPMSM_TEST1');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1');

%% Model HDL Parameters
%% Set Model 'FCS_MPC_3Phase_SPMSM_TEST1' HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'AdaptivePipelining', 'on');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'CriticalPathEstimation', 'on');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'HDLSubsystem', 'FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'OptimizationReport', 'on');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'Oversampling', 100);
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'ResetType', 'Synchronous');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'ResourceReport', 'on');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'SynthesisToolPackageName', '');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'SynthesisToolSpeedValue', '');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\test_ipcore\hdlsrc');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'TargetFrequency', 100);
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1', 'IPCoreName', 'Test_FCS_MPC_3Phase_SPMSM_IP_Core');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/dq_Done_123_alphabeta_dq', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/dq_Done_123_alphabeta_dq', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ialpha', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ialpha', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ibeta', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ibeta', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/u_dc_link_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/u_dc_link_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/SampleTime_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/SampleTime_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/theta_el', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/omega_m', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/omega_m', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/Rs_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/reciprocal_Ls_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/reciprocal_Ls_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/psiPM_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ialpha_ref', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ialpha_ref', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ibeta_ref', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/ibeta_ref', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/pole_pairs_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/Index', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/Index', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/done_MPC', 'IOInterface', 'External Port');
hdlset_param('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1/done_MPC', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\FCS_MPC_3Phase_SPMSM\test_ipcore';
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
hdlcoder.runWorkflow('FCS_MPC_3Phase_SPMSM_TEST1/Microcontroller Software/Subsystem1', hWC);
