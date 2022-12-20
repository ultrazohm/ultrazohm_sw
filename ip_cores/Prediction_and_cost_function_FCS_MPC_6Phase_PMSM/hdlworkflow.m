%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 11:28:34 on 01/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\Prediction_and_cost_function_FCS_MPC_6Phase_PMSM\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT');

%% Model HDL Parameters
%% Set Model 'Prediction_and_cost_function_FCS_MPC_6Phase_PMSM' HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'CriticalPathEstimation', 'on');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'HDLSubsystem', 'Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'OptimizationReport', 'on');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'ResetType', 'Synchronous');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'ResourceReport', 'on');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'SynthesisToolPackageName', '');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'SynthesisToolSpeedValue', '');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\Prediction_and_cost_function_FCS_MPC_6Phase_PMSM\hdlsrc');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'TargetFrequency', 100);
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT', 'IPCoreName', 'Prediction_and_cost_FCS_MPC_6Phase_PMSM');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Lq_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Ld_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Ld_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Ld_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Lq_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Lq_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Lx_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Lx_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Ly_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/SampleTime_div_Ly_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_k_1', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_k_1', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_k_1', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_k_1', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_k_1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Rs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Rs_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/omega_m_measured', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/omega_m_measured', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/pole_pairs_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/pole_pairs_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/psiPM_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/psiPM_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_ref_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_ref_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_ref_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_ref_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_ref_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/d_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/d_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/q_voltage_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/q_voltage_per_switching_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/x_volatge_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/x_volatge_per_switching_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/y_phase_volatge_per_switching_state', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/y_phase_volatge_per_switching_state', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/use_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/use_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/id_k_1_AXI', 'IOInterfaceMapping', 'x"138"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iq_k_1_AXI', 'IOInterfaceMapping', 'x"13C"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/ix_k_1_AXI', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_k_1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/iy_k_1_AXI', 'IOInterfaceMapping', 'x"144"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/omega_m_measured_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/omega_m_measured_AXI', 'IOInterfaceMapping', 'x"148"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/d_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/d_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"14C"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/q_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/q_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"150"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/x_voltage_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/x_voltage_per_switching_state_AXI', 'IOInterfaceMapping', 'x"154"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/y_volatge_per_switching_state_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/y_volatge_per_switching_state_AXI', 'IOInterfaceMapping', 'x"158"');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/valid_in', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/valid_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Reset', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Reset', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/J', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/J', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/J_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/J_AXI', 'IOInterfaceMapping', 'x"15C"');

% Set Outport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/done', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Index', 'IOInterface', 'External Port');
hdlset_param('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT/Index', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\Prediction_and_cost_function_FCS_MPC_6Phase_PMSM';
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
hdlcoder.runWorkflow('Prediction_and_cost_function_FCS_MPC_6Phase_PMSM/HDL_DUT', hWC);
