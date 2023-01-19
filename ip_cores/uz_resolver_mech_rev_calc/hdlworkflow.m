%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 16:20:41 on 19/01/2023
% This script was generated using the following parameter values:
%     Filename  : 'C:\GIT\UltraZohm\software\ultrazohm_sw_PullRequests\ip_cores\uz_resolver_mech_rev_calc\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_resolver_mech_revolution_float');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc');

%% Model HDL Parameters
%% Set Model 'uz_resolver_mech_revolution_float' HDL parameters
hdlset_param('uz_resolver_mech_revolution_float', 'CriticalPathEstimation', 'on');
hdlset_param('uz_resolver_mech_revolution_float', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('uz_resolver_mech_revolution_float', 'HDLGenerateWebview', 'on');
hdlset_param('uz_resolver_mech_revolution_float', 'HDLSubsystem', 'uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc');
hdlset_param('uz_resolver_mech_revolution_float', 'OptimizationReport', 'on');
hdlset_param('uz_resolver_mech_revolution_float', 'ResetType', 'Synchronous');
hdlset_param('uz_resolver_mech_revolution_float', 'ResourceReport', 'on');
hdlset_param('uz_resolver_mech_revolution_float', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_resolver_mech_revolution_float', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_resolver_mech_revolution_float', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1-e');
hdlset_param('uz_resolver_mech_revolution_float', 'SynthesisToolPackageName', '');
hdlset_param('uz_resolver_mech_revolution_float', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_resolver_mech_revolution_float', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('uz_resolver_mech_revolution_float', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_resolver_mech_revolution_float', 'Traceability', 'on');
hdlset_param('uz_resolver_mech_revolution_float', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc', 'IPCoreName', 'uz_resolver_mech_rev_calc');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_raw', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/resolver_polepairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/resolver_polepairs_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/cnt_reset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/cnt_reset_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_intmax_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_intmax_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/machine_polepairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/machine_polepairs_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/velocity_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/velocity_raw', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/bitToRPS_Factor_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/bitToRPS_Factor_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/trigger', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/trigger', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_raw', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_raw', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_2pi', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_2pi', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_el_2pi', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_el_2pi', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/omega_mech', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/omega_mech', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/rpm_mech', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/rpm_mech', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/cnt_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/cnt_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/done', 'IOInterface', 'External Port');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_2pi_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_mech_2pi_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_el_2pi_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/position_el_2pi_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/omega_mech_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/omega_mech_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/rpm_mech_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc/rpm_mech_AXI', 'IOInterfaceMapping', 'x"120"');


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
hdlcoder.runWorkflow('uz_resolver_mech_revolution_float/uz_resolver_mech_rev_calc', hWC);
