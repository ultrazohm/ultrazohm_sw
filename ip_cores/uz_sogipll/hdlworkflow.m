%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 26.2 (R2026b) at 12:05:54 on 27/11/2026
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Documents/compare_repo/ultrazohm_sw/ip_cores/uz_sogipll/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_sogipll/uz_sogipll'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_sogipll/uz_sogipll');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_sogipll');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_sogipll/uz_sogipll');

%% Model HDL Parameters
%% Set Model 'uz_sogipll' HDL parameters
hdlset_param('uz_sogipll', 'CriticalPathEstimation', 'on');
hdlset_param('uz_sogipll', 'HDLSubsystem', 'uz_sogipll/uz_sogipll');
hdlset_param('uz_sogipll', 'Oversampling', 200);
hdlset_param('uz_sogipll', 'ProjectFolder', '/home/ts/Documents/compare_repo/ultrazohm_sw/ip_cores/uz_sogipll/hdl_prj');
hdlset_param('uz_sogipll', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_sogipll', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_sogipll', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_sogipll', 'SynthesisToolPackageName', '');
hdlset_param('uz_sogipll', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_sogipll', 'TargetDirectory', '/home/ts/Documents/compare_repo/ultrazohm_sw/ip_cores/uz_sogipll/hdl_prj/hdlsrc');
hdlset_param('uz_sogipll', 'TargetFrequency', 100);
hdlset_param('uz_sogipll', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_sogipll', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_sogipll/uz_sogipll', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_rst', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_rst', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_v', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_v', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_omega_ff', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_omega_ff', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_k', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_k', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_kp', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_kp', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_ki', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_ki', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_t_sample', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_t_sample', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/in_v_scaling', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/in_v_scaling', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_v_est', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_v_est', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_qv_est', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_qv_est', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_v_d', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_v_d', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_v_q', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_v_q', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_theta_est', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_theta_est', 'IOInterfaceMapping', 'x"130"');

% Set Outport HDL parameters
hdlset_param('uz_sogipll/uz_sogipll/out_omega_est', 'IOInterface', 'AXI4');
hdlset_param('uz_sogipll/uz_sogipll/out_omega_est', 'IOInterfaceMapping', 'x"134"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = '/home/ts/Documents/compare_repo/ultrazohm_sw/ip_cores/uz_sogipll/hdl_prj';
hWC.AllowUnsupportedToolVersion = true;
hWC.ReferenceDesignToolVersion = '';
hWC.IgnoreToolVersionMismatch = false;

% Set Workflow tasks to run
hWC.RunTaskGenerateRTLCodeAndIPCore = true;
hWC.RunTaskCreateProject = false;
hWC.RunTaskGenerateSoftwareInterface = false;
hWC.RunTaskBuildFPGABitstream = false;
hWC.RunTaskProgramTargetDevice = false;

% Set properties related to 'RunTaskGenerateRTLCodeAndIPCore' Task
hWC.GenerateIPCoreReport = true;

% Set properties related to 'RunTaskCreateProject' Task
hWC.Objective = hdlcoder.Objective.None;
hWC.AdditionalProjectCreationTclFiles = '';
hWC.EnableIPCaching = false;

% Set properties related to 'RunTaskGenerateSoftwareInterface' Task
hWC.GenerateSoftwareInterfaceModel = false;
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
hWC.MaxNumOfCoresForBuild = 'synthesis tool default';

% Set properties related to 'RunTaskProgramTargetDevice' Task
hWC.ProgrammingMethod = hdlcoder.ProgrammingMethod.JTAG;
hWC.IPAddress = '';
hWC.SSHUsername = '';
hWC.SSHPassword = '';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('uz_sogipll/uz_sogipll', hWC);
