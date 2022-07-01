%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.11 (R2021b) at 11:04:45 on 08/06/2022
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/ultrazohm_sw/ip_cores/uz_pmsm_model_9ph/hdlworkflow_9ph_dq.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph');
%--------------------------------------------------------------------------

%% Load the Model
load_system('Copy_of_uz_pmsm_model_9ph_21b_all_double');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph');

%% Model HDL Parameters
%% Set Model 'Copy_of_uz_pmsm_model_9ph_21b_all_double' HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'CriticalPathEstimation', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'HDLSubsystem', 'Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'MapPipelineDelaysToRAM', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'OptimizationReport', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'Oversampling', 100);
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ResetType', 'Synchronous');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ResourceReport', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'ScalarizePorts', 'DUTLevel');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolPackageName', '');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'SynthesisToolSpeedValue', '');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'TargetDirectory', 'hdl_prj123/hdlsrc');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph', 'AXI4SlaveIDWidth', '12');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph', 'FlattenHierarchy', 'on');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph', 'IPCoreName', 'uz_pmsm_model_9ph_only_dq2');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/load_torque', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/load_torque', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/<reset_integrators>', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/<reset_integrators>', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/simulate_mechanical', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/omega_mech', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/omega_mech', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/physical_parameters', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/physical_parameters', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/use_axi_input', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/use_axi_input', 'IOInterfaceMapping', 'x"154"');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq_axi', 'IOInterfaceMapping', 'x"1C0"');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/Wrapped State DTI', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/mechanical_system/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator2', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator3', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator4', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator5', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator6', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator7', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/pmsm/integrator8', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/currents_dq_output_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/currents_dq_output_axi', 'IOInterfaceMapping', 'x"240"');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/theta_el_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/theta_el_axi', 'IOInterfaceMapping', 'x"190"');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/M_Mi_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/M_Mi_axi', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/omega_out_axi', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/omega_out_axi', 'IOInterfaceMapping', 'x"150"');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/currents_dq_output', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/currents_dq_output', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/theta_el1', 'IOInterface', 'External Port');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/theta_el1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq_axi_fb', 'IOInterface', 'AXI4');
hdlset_param('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph/voltage_input_dq_axi_fb', 'IOInterfaceMapping', 'x"340"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj123';
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
hdlcoder.runWorkflow('Copy_of_uz_pmsm_model_9ph_21b_all_double/uz_pmsm_model_9ph/dq_model_9ph', hWC);
