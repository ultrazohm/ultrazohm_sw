%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 11:45:47 on 07/05/2021
% This script was generated using the following parameter values:
%     Filename  : 'C:\ZynqUltra\60_Software\ultrazohm_sw\ip_cores\UZ_D_GaN_Inverter\Driver\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'UZ_D_GaN_Inverter/UZ_D_GaN_Inverter'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','UZ_D_GaN_Inverter/UZ_D_GaN_Inverter');
%--------------------------------------------------------------------------

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','C:/Xilinx/Vivado/2020.1/bin')

%% Load the Model
load_system('UZ_D_GaN_Inverter');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter');

%% Model HDL Parameters
%% Set Model 'UZ_D_GaN_Inverter' HDL parameters
hdlset_param('UZ_D_GaN_Inverter', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter', 'CriticalPathEstimation', 'on');
hdlset_param('UZ_D_GaN_Inverter', 'GenerateHDLTestBench', 'off');
hdlset_param('UZ_D_GaN_Inverter', 'HDLSubsystem', 'UZ_D_GaN_Inverter/UZ_D_GaN_Inverter');
hdlset_param('UZ_D_GaN_Inverter', 'OptimizationReport', 'on');
hdlset_param('UZ_D_GaN_Inverter', 'ResetType', 'Synchronous');
hdlset_param('UZ_D_GaN_Inverter', 'ResourceReport', 'on');
hdlset_param('UZ_D_GaN_Inverter', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('UZ_D_GaN_Inverter', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('UZ_D_GaN_Inverter', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1-e');
hdlset_param('UZ_D_GaN_Inverter', 'SynthesisToolPackageName', '');
hdlset_param('UZ_D_GaN_Inverter', 'SynthesisToolSpeedValue', '');
hdlset_param('UZ_D_GaN_Inverter', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('UZ_D_GaN_Inverter', 'TargetFrequency', 100);
hdlset_param('UZ_D_GaN_Inverter', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('UZ_D_GaN_Inverter', 'Traceability', 'on');
hdlset_param('UZ_D_GaN_Inverter', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'IPCoreName', 'UZ_D_GaN_Inverter');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I_DIAG', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I_DIAG', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_PWM_Enable', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_PWM_Enable', 'IOInterfaceMapping', 'x"1A0"');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_PWM_Enable', 'IOInterfaceOptions', {'RegisterInitialValue','0'});

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutyFreqDetection/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_period', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_period', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_hightime', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_lowtime', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_dutycyc', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_period', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_hightime', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_lowtime', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_dutycyc', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_period', 'IOInterfaceMapping', 'x"130"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_hightime', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_lowtime', 'IOInterfaceMapping', 'x"138"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_dutycyc', 'IOInterfaceMapping', 'x"13C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_period', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_hightime', 'IOInterfaceMapping', 'x"144"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_lowtime', 'IOInterfaceMapping', 'x"148"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_dutycyc', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_period', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_period', 'IOInterfaceMapping', 'x"150"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_hightime', 'IOInterfaceMapping', 'x"154"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_lowtime', 'IOInterfaceMapping', 'x"158"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_dutycyc', 'IOInterfaceMapping', 'x"15C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT', 'IOInterfaceMapping', 'x"160"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC', 'IOInterfaceMapping', 'x"178"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I_DIAG', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I_DIAG', 'IOInterfaceMapping', 'x"190"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWM_EN', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWM_EN', 'IOInterfaceMapping', '');


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
hdlcoder.runWorkflow('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', hWC);
