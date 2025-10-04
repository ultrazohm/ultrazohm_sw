%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 24.1 (R2024a) at 21:20:16 on 09/06/2024
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\Simulink_Model\hdlworkflow_ABZ_addon.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'UZ_EnDat/UZ_ENDAT_ABZ_ADDON'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','UZ_EnDat/UZ_ENDAT_ABZ_ADDON');
%--------------------------------------------------------------------------

%% Load the Model
load_system('UZ_EnDat');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('UZ_EnDat/UZ_ENDAT_ABZ_ADDON');

%% Model HDL Parameters
%% Set Model 'UZ_EnDat' HDL parameters
hdlset_param('UZ_EnDat', 'AdaptivePipelining', 'on');
hdlset_param('UZ_EnDat', 'BalanceClockRateOutputPorts', 'on');
hdlset_param('UZ_EnDat', 'ClockRatePipelineOutputPorts', 'on');
hdlset_param('UZ_EnDat', 'CriticalPathEstimation', 'on');
hdlset_param('UZ_EnDat', 'DeleteUnusedPorts', 'off');
hdlset_param('UZ_EnDat', 'DistributedPipelining', 'on');
fpconfig = hdlcoder.createFloatingPointTargetConfig('NATIVEFLOATINGPOINT' ...
, 'LatencyStrategy', 'Min',  'HandleDenormals', 'Off' ...
);
hdlset_param('UZ_EnDat', 'FloatingPointTargetConfiguration', fpconfig);
hdlset_param('UZ_EnDat', 'HDLSubsystem', 'UZ_EnDat/UZ_ENDAT_ABZ_ADDON');
hdlset_param('UZ_EnDat', 'LUTMapToRAM', 'off');
hdlset_param('UZ_EnDat', 'MulticyclePathConstraints', 'on');
hdlset_param('UZ_EnDat', 'MultiplierPromotionThreshold', 1);
hdlset_param('UZ_EnDat', 'PackagePostfix', '_pac');
hdlset_param('UZ_EnDat', 'ProjectFolder', 'C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj');
hdlset_param('UZ_EnDat', 'RAMMappingThreshold', '1');
hdlset_param('UZ_EnDat', 'ResetInputPort', 'reset_x');
hdlset_param('UZ_EnDat', 'ResetType', 'Synchronous');
hdlset_param('UZ_EnDat', 'ShareAtomicSubsystems', 'off');
hdlset_param('UZ_EnDat', 'ShareFloatingPointIPs', 'off');
hdlset_param('UZ_EnDat', 'ShareMATLABBlocks', 'off');
hdlset_param('UZ_EnDat', 'ShareMultipliers', 'off');
hdlset_param('UZ_EnDat', 'ShareMultiplyAdds', 'off');
hdlset_param('UZ_EnDat', 'SubsystemReuse', 'Atomic and Virtual');
hdlset_param('UZ_EnDat', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('UZ_EnDat', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('UZ_EnDat', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1-e');
hdlset_param('UZ_EnDat', 'SynthesisToolPackageName', '');
hdlset_param('UZ_EnDat', 'SynthesisToolSpeedValue', '');
hdlset_param('UZ_EnDat', 'TargetDirectory', 'C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj\hdlsrc');
hdlset_param('UZ_EnDat', 'TargetFrequency', 100);
hdlset_param('UZ_EnDat', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('UZ_EnDat', 'UseFloatingPoint', 'on');
hdlset_param('UZ_EnDat', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON', 'GenerateDefaultAXI4Slave', 'off');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON', 'IPCoreName', 'uz_EnDat_ABZ_addon');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON', 'IPCoreVersion', '1.0');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/POS', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/POS', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/ATRACK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/ATRACK', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/BTRACK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/BTRACK', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/ZTRACK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT_ABZ_ADDON/ZTRACK', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\hdl_prj';
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
hWC.IPCoreRepository = '';
hWC.GenerateIPCoreReport = true;

% Set properties related to 'RunTaskCreateProject' Task
hWC.Objective = hdlcoder.Objective.None;
hWC.AdditionalProjectCreationTclFiles = '';
hWC.EnableIPCaching = false;

% Set properties related to 'RunTaskGenerateSoftwareInterface' Task
hWC.GenerateSoftwareInterfaceModel = false;
hWC.OperatingSystem = 'Linux';
hWC.HostTargetInterface = '';
hWC.GenerateHostInterfaceModel = false;
hWC.GenerateHostInterfaceScript = false;

% Set properties related to 'RunTaskBuildFPGABitstream' Task
hWC.RunExternalBuild = false;
hWC.EnableDesignCheckpoint = false;
hWC.TclFileForSynthesisBuild = hdlcoder.BuildOption.Default;
hWC.CustomBuildTclFile = '';
hWC.DefaultCheckpointFile = 'Custom';
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
hdlcoder.runWorkflow('UZ_EnDat/UZ_ENDAT_ABZ_ADDON', hWC);
