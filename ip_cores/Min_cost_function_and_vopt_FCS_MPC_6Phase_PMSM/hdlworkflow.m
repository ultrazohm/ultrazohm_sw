%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 09:59:54 on 01/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\Min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1');
%--------------------------------------------------------------------------

%% Load the Model
load_system('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1');

%% Model HDL Parameters
%% Set Model 'min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM' HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'CriticalPathEstimation', 'on');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'HDLSubsystem', 'min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'OptimizationReport', 'on');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'ResetType', 'Synchronous');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'ResourceReport', 'on');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'SynthesisToolPackageName', '');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'SynthesisToolSpeedValue', '');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\Min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM\hdlsrc');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'TargetFrequency', 100);
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1', 'IPCoreName', 'min_cost_function_and_vopt_FCS_MPC_6Phase');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/J_in', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/J_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/d_phase_voltage_per_switchimng_state', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/d_phase_voltage_per_switchimng_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/q_phase_voltage_per_switchimng_state', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/q_phase_voltage_per_switchimng_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/x_phase_voltage_per_switchimng_state', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/x_phase_voltage_per_switchimng_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/y_phase_voltage_per_switchimng_state', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/y_phase_voltage_per_switchimng_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_in', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/use_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/use_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/J_in_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/J_in_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_in_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_in_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/d_phase_voltage_per_switchimng_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/d_phase_voltage_per_switchimng_state_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/q_phase_voltage_per_switchimng_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/q_phase_voltage_per_switchimng_state_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/x_phase_voltage_per_switchimng_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/x_phase_voltage_per_switchimng_state_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/y_phase_voltage_per_switchimng_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/y_phase_voltage_per_switchimng_state_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/valid_in_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/valid_in_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/valid_in', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/valid_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_out', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ud', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ud', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uq', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uq', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ux', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ux', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uy', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uy', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uy_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uy_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ux_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ux_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_uq_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ud_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/last_applied_optimal_voltage_ud_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_out_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/Index_out_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done_complete', 'IOInterface', 'External Port');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done_complete', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done_complete_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1/done_complete_AXI', 'IOInterfaceMapping', 'x"130"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\Min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM';
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
hdlcoder.runWorkflow('min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/HDL_DUT1', hWC);
