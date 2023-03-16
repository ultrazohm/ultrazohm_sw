%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 16:43:37 on 17/03/2021
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Documents/uz_develop/ultrazohm_sw/ip_cores/uz_mlp_three_layer/simulation/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_mlp_three_layer/uz_mlp_three_layer'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_mlp_three_layer/uz_mlp_three_layer');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_mlp_three_layer');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_mlp_three_layer/uz_mlp_three_layer');

%% Model HDL Parameters
%% Set Model 'uz_mlp_three_layer' HDL parameters
hdlset_param('uz_mlp_three_layer', 'CriticalPathEstimation', 'on');
hdlset_param('uz_mlp_three_layer', 'HDLSubsystem', 'uz_mlp_three_layer/uz_mlp_three_layer');
hdlset_param('uz_mlp_three_layer', 'OptimizationReport', 'on');
hdlset_param('uz_mlp_three_layer', 'ResetType', 'Synchronous');
hdlset_param('uz_mlp_three_layer', 'ResourceReport', 'on');
hdlset_param('uz_mlp_three_layer', 'ScalarizePorts', 'DUTLevel');
hdlset_param('uz_mlp_three_layer', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_mlp_three_layer', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_mlp_three_layer', 'SynthesisToolDeviceName', 'xczu9eg-ffvb1156-1L-i');
hdlset_param('uz_mlp_three_layer', 'SynthesisToolPackageName', '');
hdlset_param('uz_mlp_three_layer', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_mlp_three_layer', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_mlp_three_layer', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_mlp_three_layer', 'Traceability', 'on');
hdlset_param('uz_mlp_three_layer', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer', 'IPCoreName', 'uz_mlp_three_layer');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer', 'IPCoreVersion', '3.0');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/enable_nn', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/enable_nn', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_enable_nn', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_enable_nn', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x1', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x2', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x3', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x4', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x5', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x6', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x6', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x7', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x7', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x8', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x8', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x9', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x9', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x10', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x10', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x11', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x11', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x12', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x12', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x13', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x13', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x14', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x14', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x15', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x15', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x16', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/x16', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_bias', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_bias', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_weight', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_weight', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_bias_addr', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_bias_addr', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_weight_addr', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_weight_addr', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_wrEnBias', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_wrEnBias', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_wrEnWeights', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_wrEnWeights', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_layerNr', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_layerNr', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/use_axi_input', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/use_axi_input', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_x_input', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_x_input', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_number_of_inputs', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_number_of_inputs', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_output_number_configuration', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_output_number_configuration', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/disable_pl_trigger', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/disable_pl_trigger', 'IOInterfaceMapping', 'x"12C"');

% Set SubSystem HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/external_enable', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/external_enable', 'IOInterfaceMapping', '');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/Subsystem1/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/Subsystem8/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/layer_rdy', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/LastLayer/layer_rdy', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/external_enable', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/external_enable', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/ram_rd_addr', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/ram_rd_addr', 'IOInterfaceMapping', '');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/MAC/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/MAC1/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/MAC2/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/MAC3/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/layer_rdy', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_4Parallel/layer_rdy', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/external_enable', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/external_enable', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/ram_rd_addr', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/ram_rd_addr', 'IOInterfaceMapping', '');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC1/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC2/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC3/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC4/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC5/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC6/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/MAC7/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/layer_rdy', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel/layer_rdy', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/external_enable', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/external_enable', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/ram_rd_addr', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/ram_rd_addr', 'IOInterfaceMapping', '');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC1/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC3/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC4/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC5/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC6/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC7/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Gain HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/MAC8/Gain', 'ConstMultiplierOptimization', 'csd');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/layer_rdy', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/reluLayer_8Parallel1/layer_rdy', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/finished', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/finished', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out1', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out2', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out3', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out4', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out5', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out6', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out7', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/out7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasData', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasData', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasWriteAddr', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasWriteAddr', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasWriteEnable', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/biasWriteEnable', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/valid_output', 'IOInterface', 'External Port');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/valid_output', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_nn_output', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_nn_output', 'IOInterfaceMapping', 'x"1A0"');

% Set Outport HDL parameters
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_valid_output', 'IOInterface', 'AXI4');
hdlset_param('uz_mlp_three_layer/uz_mlp_three_layer/axi_valid_output', 'IOInterfaceMapping', 'x"130"');


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
hdlcoder.runWorkflow('uz_mlp_three_layer/uz_mlp_three_layer', hWC);
