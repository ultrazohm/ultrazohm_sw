%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.11 (R2021b) at 14:09:16 on 16/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\valen\Documents\repos\UZ\ultrazohm_sw_working\ip_cores\uz_pmsm_model_6ph_dq\hdlworkflow_6ph_dq.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_pmsm_model_6ph_dq');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq');

%% Model HDL Parameters
%% Set Model 'uz_pmsm_model_6ph_dq' HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq', 'AdaptivePipelining', 'on');
hdlset_param('uz_pmsm_model_6ph_dq', 'CriticalPathEstimation', 'on');
hdlset_param('uz_pmsm_model_6ph_dq', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('uz_pmsm_model_6ph_dq', 'HDLSubsystem', 'uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq');
hdlset_param('uz_pmsm_model_6ph_dq', 'MapPipelineDelaysToRAM', 'on');
hdlset_param('uz_pmsm_model_6ph_dq', 'OptimizationReport', 'on');
hdlset_param('uz_pmsm_model_6ph_dq', 'Oversampling', 100);
hdlset_param('uz_pmsm_model_6ph_dq', 'ResetType', 'Synchronous');
hdlset_param('uz_pmsm_model_6ph_dq', 'ResourceReport', 'on');
hdlset_param('uz_pmsm_model_6ph_dq', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_pmsm_model_6ph_dq', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_pmsm_model_6ph_dq', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_pmsm_model_6ph_dq', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_pmsm_model_6ph_dq', 'SynthesisToolPackageName', '');
hdlset_param('uz_pmsm_model_6ph_dq', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_pmsm_model_6ph_dq', 'TargetDirectory', 'hdl_prj123\hdlsrc');
hdlset_param('uz_pmsm_model_6ph_dq', 'TargetFrequency', 100);
hdlset_param('uz_pmsm_model_6ph_dq', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_pmsm_model_6ph_dq', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq', 'FlattenHierarchy', 'on');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq', 'IPCoreName', 'uz_pmsm_model_6ph_dq');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/reset_integrators', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/reset_integrators', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/use_axi_input', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/use_axi_input', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/simulate_mechanical', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/simulate_mechanical', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/load_torque', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/load_torque', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/omega_mech', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/omega_mech', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/physical_parameters', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/physical_parameters', 'IOInterfaceMapping', 'x"170"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq_axi', 'IOInterfaceMapping', 'x"180"');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/Wrapped State DTI', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/mechanical_system', 'FlattenHierarchy', 'on');

% Set Inport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/mechanical_system/reciprocal_J', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/mechanical_system/reciprocal_J', 'IOInterfaceMapping', 'x"150"');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/mechanical_system/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator1', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator2', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator3', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator4', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/pmsm/integrator5', 'FlattenHierarchy', 'on');

% Set SubSystem HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/torque_calculation', 'FlattenHierarchy', 'on');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/theta_el_out_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/theta_el_out_axi', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/theta_el_out', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/theta_el_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/M_Mi_out_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/M_Mi_out_axi', 'IOInterfaceMapping', 'x"174"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/omega_mech_out_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/omega_mech_out_axi', 'IOInterfaceMapping', 'x"178"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/currents_dq_out_axi', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/currents_dq_out_axi', 'IOInterfaceMapping', 'x"200"');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/currents_dq_out', 'IOInterface', 'External Port');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/currents_dq_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq_out_axi_fb', 'IOInterface', 'AXI4');
hdlset_param('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq/voltage_input_dq_out_axi_fb', 'IOInterfaceMapping', 'x"280"');


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
hdlcoder.runWorkflow('uz_pmsm_model_6ph_dq/uz_pmsm_model_9ph_dq', hWC);
