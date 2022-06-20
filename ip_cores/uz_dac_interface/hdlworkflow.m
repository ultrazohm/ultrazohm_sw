%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 10:02:39 on 17/05/2022
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Dokumente/ultrazohm_testbench/fix_alloc/ultrazohm_sw/ip_cores/uz_dac_interface/hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_dac_spi_interface/uz_dac_spi_interface'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_dac_spi_interface/uz_dac_spi_interface');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_dac_spi_interface');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_dac_spi_interface/uz_dac_spi_interface');

%% Model HDL Parameters
%% Set Model 'uz_dac_spi_interface' HDL parameters
hdlset_param('uz_dac_spi_interface', 'CriticalPathEstimation', 'on');
hdlset_param('uz_dac_spi_interface', 'HDLSubsystem', 'uz_dac_spi_interface/uz_dac_spi_interface');
hdlset_param('uz_dac_spi_interface', 'OptimizationReport', 'on');
hdlset_param('uz_dac_spi_interface', 'ResetType', 'Synchronous');
hdlset_param('uz_dac_spi_interface', 'ResourceReport', 'on');
hdlset_param('uz_dac_spi_interface', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_dac_spi_interface', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_dac_spi_interface', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('uz_dac_spi_interface', 'SynthesisToolPackageName', '');
hdlset_param('uz_dac_spi_interface', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_dac_spi_interface', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('uz_dac_spi_interface', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_dac_spi_interface', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface', 'AXI4SlaveIDWidth', '12');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface', 'IPCoreName', 'uz_dac_spi_interface');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/trigger_write', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/trigger_write', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_1', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_1', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_2', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_2', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_3', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_3', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_4', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_4', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_5', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_5', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_6', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_6', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_7', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_7', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_8', 'IOInterface', 'AXI4');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/dac_data_8', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/spi_clk_out', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/spi_clk_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/cs_out', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/cs_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_1', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_2', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_3', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_4', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_5', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_6', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_7', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_8', 'IOInterface', 'External Port');
hdlset_param('uz_dac_spi_interface/uz_dac_spi_interface/data_out_8', 'IOInterfaceMapping', '');


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
hdlcoder.runWorkflow('uz_dac_spi_interface/uz_dac_spi_interface', hWC);
