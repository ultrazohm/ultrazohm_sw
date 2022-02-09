%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 13:24:28 on 30/08/2021
% This script was generated using the following parameter values:
%     Filename  : 'C:\ZynqUltra\60_Software\ultrazohm_sw_1\ip_cores\mux_axi\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'mux_axi/mux_axi'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','mux_axi/mux_axi');
%--------------------------------------------------------------------------

%% Load the Model
load_system('mux_axi');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('mux_axi/mux_axi');

%% Model HDL Parameters
%% Set Model 'mux_axi' HDL parameters
hdlset_param('mux_axi', 'AdaptivePipelining', 'off');
hdlset_param('mux_axi', 'BalanceDelays', 'off');
hdlset_param('mux_axi', 'CriticalPathEstimation', 'on');
hdlset_param('mux_axi', 'HDLGenerateWebview', 'on');
hdlset_param('mux_axi', 'HDLSubsystem', 'mux_axi/mux_axi');
hdlset_param('mux_axi', 'OptimizationReport', 'on');
hdlset_param('mux_axi', 'ResetType', 'Synchronous');
hdlset_param('mux_axi', 'ResourceReport', 'on');
hdlset_param('mux_axi', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('mux_axi', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('mux_axi', 'SynthesisToolDeviceName', 'xqzu9eg-ffrc900-1-i');
hdlset_param('mux_axi', 'SynthesisToolPackageName', '');
hdlset_param('mux_axi', 'SynthesisToolSpeedValue', '');
hdlset_param('mux_axi', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('mux_axi', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('mux_axi', 'Traceability', 'on');
hdlset_param('mux_axi', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('mux_axi/mux_axi', 'AXI4RegisterReadback', 'on');
hdlset_param('mux_axi/mux_axi', 'IPCoreVersion', '1.1');
hdlset_param('mux_axi/mux_axi', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('mux_axi/mux_axi/select_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('mux_axi/mux_axi/select_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('mux_axi/mux_axi/select_n_th_adc_interrupt', 'IOInterface', 'AXI4-Lite');
hdlset_param('mux_axi/mux_axi/select_n_th_adc_interrupt', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('mux_axi/mux_axi/interrupts_in', 'IOInterface', 'External Port');
hdlset_param('mux_axi/mux_axi/interrupts_in', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('mux_axi/mux_axi/interrupt_out_adc', 'IOInterface', 'External Port');
hdlset_param('mux_axi/mux_axi/interrupt_out_adc', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('mux_axi/mux_axi/interrupt_out_isr', 'IOInterface', 'External Port');
hdlset_param('mux_axi/mux_axi/interrupt_out_isr', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('mux_axi/mux_axi/select_out', 'IOInterface', 'External Port');
hdlset_param('mux_axi/mux_axi/select_out', 'IOInterfaceMapping', '');


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
hdlcoder.runWorkflow('mux_axi/mux_axi', hWC);
