%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.9 (R2020b) at 21:23:17 on 27/04/2021
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\Michael Hoerner\Documents\MATLAB\UltraZohm\UZ_D_GaN_Inverter\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'UZ_D_GaN_Inverter/UZ_D_GaN_Inverter'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','UZ_D_GaN_Inverter/UZ_D_GaN_Inverter');
%--------------------------------------------------------------------------

% hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','C:/Xilinx/Vivado/2020.1/bin')

%% Load the Model
load_system('UZ_D_GaN_Inverter');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter');

%% Model HDL Parameters
%% Set Model 'UZ_D_GaN_Inverter' HDL parameters
hdlset_param('UZ_D_GaN_Inverter', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter', 'CriticalPathEstimation', 'on');
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
hdlset_param('UZ_D_GaN_Inverter', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('UZ_D_GaN_Inverter', 'Traceability', 'on');
hdlset_param('UZ_D_GaN_Inverter', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp1', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp2', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp3', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp4', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp5', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp6', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_Temp6', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H1', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L1', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H2', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L2', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H3', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_H3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L3', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_FAULT_L3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H1', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L1', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H2', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L2', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H3', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_H3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L3', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/GaN_OC_L3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I_DIAG', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I_DIAG', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I1_DIAG', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I1_DIAG', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I2_DIAG', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I2_DIAG', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I3_DIAG', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/I3_DIAG', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_PWM_Enable', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_PWM_Enable', 'IOInterfaceMapping', 'x"1A0"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection1/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection2/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection3/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection4/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set SubSystem HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'AdaptivePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'BalanceDelays', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'ClockRatePipelining', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'FlattenHierarchy', 'off');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'IPCoreName', 'PWMdutyFreqDetection');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/PWMin', 'IOInterface', 'External Port');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/PWMin', 'IOInterfaceMapping', '');

hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/HDL Reciprocal', 'Architecture', 'ReciprocalNewtonSingleRate');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_freq', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_hightime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_hightime', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_lowtime', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_lowtime', 'IOInterfaceMapping', 'x"108"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_dutycyc', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/PWMdutycycFreqDetection5/AXI_dutycyc', 'IOInterfaceMapping', 'x"10C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_1_freq', 'IOInterfaceMapping', 'x"100"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_2_freq', 'IOInterfaceMapping', 'x"110"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_3_freq', 'IOInterfaceMapping', 'x"120"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_4_freq', 'IOInterfaceMapping', 'x"130"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_5_freq', 'IOInterfaceMapping', 'x"140"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_freq', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_Gan_Temp_6_freq', 'IOInterfaceMapping', 'x"150"');

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
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H1', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H1', 'IOInterfaceMapping', 'x"160"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L1', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L1', 'IOInterfaceMapping', 'x"164"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H2', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H2', 'IOInterfaceMapping', 'x"168"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L2', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L2', 'IOInterfaceMapping', 'x"16C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H3', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_H3', 'IOInterfaceMapping', 'x"170"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L3', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_FAULT_L3', 'IOInterfaceMapping', 'x"174"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H1', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H1', 'IOInterfaceMapping', 'x"178"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L1', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L1', 'IOInterfaceMapping', 'x"17C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H2', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H2', 'IOInterfaceMapping', 'x"180"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L2', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L2', 'IOInterfaceMapping', 'x"184"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H3', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_H3', 'IOInterfaceMapping', 'x"188"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L3', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_GaN_OC_L3', 'IOInterfaceMapping', 'x"18C"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I_DIAG', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I_DIAG', 'IOInterfaceMapping', 'x"190"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I1_DIAG', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I1_DIAG', 'IOInterfaceMapping', 'x"194"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I2_DIAG', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I2_DIAG', 'IOInterfaceMapping', 'x"198"');

% Set Outport HDL parameters
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I3_DIAG', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_D_GaN_Inverter/UZ_D_GaN_Inverter/AXI_I3_DIAG', 'IOInterfaceMapping', 'x"19C"');

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
