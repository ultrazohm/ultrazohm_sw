%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 16:19:30 on 21/06/2021
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/ultrazohm_sw/ip_cores/uz_pmsm_model/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model/uz_pmsm_model'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model/uz_pmsm_model');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model/uz_pmsm_model');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model' HDL parameters
hdlset_param('uz_pmsm_model', 'CriticalPathEstimation', 'on');
hdlset_param('uz_pmsm_model', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('uz_pmsm_model', 'HDLSubsystem', 'uz_pmsm_model/uz_pmsm_model');
hdlset_param('uz_pmsm_model', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model', 'Oversampling', 100);
hdlset_param('uz_pmsm_model', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_pmsm_model', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'IPCoreName', 'uz_pmsm_model');
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'OutputPipeline', 10);
hdlset_param('uz_pmsm_model/uz_pmsm_model', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/u_d', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/u_d', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/u_q', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/u_q', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/R1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/R1', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/polepairs', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/polepairs', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/psi_pm', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/psi_pm', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/recirprocal_L_d', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/recirprocal_L_d', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_L_q', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_L_q', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/reset_integrators', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/reset_integrators', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/mu', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/mu', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/M_n0', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/M_n0', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/in_omega_mech', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/in_omega_mech', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_mechanical', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/simulate_mechanical', 'IOInterfaceMapping', 'x"138"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/Subsystem', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/Subsystem/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/Subsystem/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/Subsystem/integrator2', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/integrator1', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/i_d', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/i_d', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/i_q', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/i_q', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/torque', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/torque', 'IOInterfaceMapping', 'x"144"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model/uz_pmsm_model/omega_mech', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model/uz_pmsm_model/omega_mech', 'IOInterfaceMapping', 'x"130"');


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
hWC.TclFileForSynthesisBuild = hdlcoder.BuildOption.Default;
hWC.CustomBuildTclFile = '';

% Set properties related to 'RunTaskProgramTargetDevice' Task
hWC.ProgrammingMethod = hdlcoder.ProgrammingMethod.JTAG;
hWC.IPAddress = '';
hWC.SSHUsername = '';
hWC.SSHPassword = '';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('uz_pmsm_model/uz_pmsm_model', hWC);
