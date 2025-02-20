%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.11 (R2021b) at 11:04:08 on 09/01/2023
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_3ph_dq\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_3ph_dq');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model_3ph_dq' HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq', 'AdaptivePipelining', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'CriticalPathEstimation', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min',  'HandleDenormals', 'On') ...
);
hdlset_param('uz_pmsm_model_3ph_dq', 'GenerateValidationModel', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'HDLSubsystem', 'uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq');
hdlset_param('uz_pmsm_model_3ph_dq', 'HierarchicalDistPipelining', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'Oversampling', 100);
hdlset_param('uz_pmsm_model_3ph_dq', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_3ph_dq', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_3ph_dq', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_3ph_dq', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_3ph_dq', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_3ph_dq', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model_3ph_dq', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_3ph_dq', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_3ph_dq', 'TargetDirectory', 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_3ph_dq\hdl_prj\hdlsrc');
hdlset_param('uz_pmsm_model_3ph_dq', 'TargetFrequency', 100);
hdlset_param('uz_pmsm_model_3ph_dq', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_3ph_dq', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq', 'IPCoreName', 'uz_pmsm_model_3ph_dq');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq', 'IPCoreVersion', '1.0');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/simulate_mechanical', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_J', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_J', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mu', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mu', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/M_n0', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/M_n0', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_L_d', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_L_d', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_L_q', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/reciprocal_L_q', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/R1', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/R1', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/polepairs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/polepairs', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/psi_pm', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/psi_pm', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/inputs', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/use_axi_input', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/use_axi_input', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/voltage_input_dq', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/voltage_input_dq', 'IOInterfaceMapping', '');

% Set DataTypeConversion HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Data Type Conversion1', 'InputPipeline', 10);
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Data Type Conversion1', 'OutputPipeline', 10);

% Set DataTypeConversion HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Data Type Conversion18', 'InputPipeline', 10);
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Data Type Conversion18', 'OutputPipeline', 10);

% Set Mux HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Mux', 'InputPipeline', 10);
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Mux', 'OutputPipeline', 10);

% Set Switch HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Switch2', 'InputPipeline', 10);
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Switch2', 'OutputPipeline', 10);

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/Wrapped State DTI', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/mechanical_system/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/pmsm', 'FlattenHierarchy', 'on');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/pmsm', 'InputPipeline', 10);
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/pmsm', 'OutputPipeline', 10);

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/pmsm/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/pmsm/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/outputs', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/outputs', 'IOInterfaceMapping', 'x"1A0"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/voltage_input_dq_out_axi_fb', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/voltage_input_dq_out_axi_fb', 'IOInterfaceMapping', 'x"280"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/currents_dq_out', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/currents_dq_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/theta_el_out', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/theta_el_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/omega_mech_out', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq/omega_mech_out', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_3ph_dq\hdl_prj';
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
hdlcoder.runWorkflow('uz_pmsm_model_3ph_dq/uz_pmsm_model_3ph_dq', hWC);
