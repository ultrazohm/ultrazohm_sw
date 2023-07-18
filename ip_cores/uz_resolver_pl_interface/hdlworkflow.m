%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 16:46:35 on 24/01/2023
% This script was generated using the following parameter values:
%     Filename  : 'C:\GIT\UltraZohm\software\ultrazohm_sw_PullRequests\ip_cores\uz_resolver_mech_rev_calc\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_resolver_pl_interface/uz_resolver_pl_interface'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_resolver_pl_interface/uz_resolver_pl_interface');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_resolver_pl_interface');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_resolver_pl_interface/uz_resolver_pl_interface');

%% Model HDL Parameters
%% Set Model 'uz_resolver_pl_interface' HDL parameters
hdlset_param('uz_resolver_pl_interface', 'CriticalPathEstimation', 'on');
hdlset_param('uz_resolver_pl_interface', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('uz_resolver_pl_interface', 'HDLGenerateWebview', 'on');
hdlset_param('uz_resolver_pl_interface', 'HDLSubsystem', 'uz_resolver_pl_interface/uz_resolver_pl_interface');
hdlset_param('uz_resolver_pl_interface', 'OptimizationReport', 'on');
hdlset_param('uz_resolver_pl_interface', 'ResetType', 'Synchronous');
hdlset_param('uz_resolver_pl_interface', 'ResourceReport', 'on');
hdlset_param('uz_resolver_pl_interface', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_resolver_pl_interface', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_resolver_pl_interface', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1-e');
hdlset_param('uz_resolver_pl_interface', 'SynthesisToolPackageName', '');
hdlset_param('uz_resolver_pl_interface', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_resolver_pl_interface', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('uz_resolver_pl_interface', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_resolver_pl_interface', 'Traceability', 'on');
hdlset_param('uz_resolver_pl_interface', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface', 'IPCoreName', 'uz_resolver_pl_interface');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_raw', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/resolver_polepairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/resolver_polepairs_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/cnt_reset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/cnt_reset_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_intmax_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_intmax_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/machine_polepairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/machine_polepairs_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/velocity_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/velocity_raw', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/bitToRPS_Factor_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/bitToRPS_Factor_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/theta_m_offset_rad_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/theta_m_offset_rad_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/trigger', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/trigger', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_raw', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_2pi', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_2pi', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_el_2pi', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_el_2pi', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/omega_mech_rad_s', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/omega_mech_rad_s', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/n_mech_rpm', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/n_mech_rpm', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/cnt_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/cnt_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/done', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_2pi_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_mech_2pi_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_el_2pi_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/position_el_2pi_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/omega_mech_rad_s_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/omega_mech_rad_s_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/n_mech_rpm_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_pl_interface/uz_resolver_pl_interface/n_mech_rpm_AXI', 'IOInterfaceMapping', 'x"128"');


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
hdlcoder.runWorkflow('uz_resolver_pl_interface/uz_resolver_pl_interface', hWC);
