%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 24.1 (R2024a) at 10:59:34 on 28/06/2024
% This script was generated using the following parameter values:
%     Filename  : 'C:\Users\ELSYS_PC\Documents\repos\ultrazohm_sw\ip_cores\uz_EnDat_IPCore\Simulink_Model\hdlworkflow_uz_EnDat.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'UZ_EnDat/UZ_ENDAT'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','UZ_EnDat/UZ_ENDAT');
%--------------------------------------------------------------------------

%% Load the Model
load_system('UZ_EnDat');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('UZ_EnDat/UZ_ENDAT');

%% Model HDL Parameters
%% Set Model 'UZ_EnDat' HDL parameters
hdlset_param('UZ_EnDat', 'AdaptivePipelining', 'on');
hdlset_param('UZ_EnDat', 'BalanceClockRateOutputPorts', 'on');
hdlset_param('UZ_EnDat', 'ClockRatePipelineOutputPorts', 'on');
hdlset_param('UZ_EnDat', 'CriticalPathEstimation', 'on');
hdlset_param('UZ_EnDat', 'DeleteUnusedPorts', 'off');
hdlset_param('UZ_EnDat', 'DistributedPipelining', 'on');
hdlset_param('UZ_EnDat', 'HDLSubsystem', 'UZ_EnDat/UZ_ENDAT');
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
hdlset_param('UZ_EnDat', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT', 'IPCoreName', 'uz_EnDat');
hdlset_param('UZ_EnDat/UZ_ENDAT', 'IPCoreVersion', '10.0');
hdlset_param('UZ_EnDat/UZ_ENDAT', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DIVIDER', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/DIVIDER', 'IOInterfaceMapping', 'x"800"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CLK50MHZ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CLK50MHZ', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CONTROLWORD', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/CONTROLWORD', 'IOInterfaceMapping', 'x"808"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAIN', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAIN', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT1DATAFLOW', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT1DATAFLOW', 'IOInterfaceMapping', 'x"804"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT2RECOVERYTIME', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT2RECOVERYTIME', 'IOInterfaceMapping', 'x"80C"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT3INITIALOFF', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT3INITIALOFF', 'IOInterfaceMapping', 'x"810"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT4DATACLKSYNC', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT4DATACLKSYNC', 'IOInterfaceMapping', 'x"814"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT5TELEGRAMLEN', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT5TELEGRAMLEN', 'IOInterfaceMapping', 'x"818"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT6SYNCRESPONSE', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT6SYNCRESPONSE', 'IOInterfaceMapping', 'x"890"');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT7EXTRASHIFT', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/FKT7EXTRASHIFT', 'IOInterfaceMapping', 'x"894"');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/8BIT_SPLITTER', 'ProcessorFPGASynchronization', 'Free running');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CONTROLWORDRAW/WORDTOBOOL', 'ProcessorFPGASynchronization', 'Free running');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CONTROLWORDSTORED/WORDTOBOOL', 'ProcessorFPGASynchronization', 'Free running');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check', 'ProcessorFPGASynchronization', 'Free running');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/CLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/CLK', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/J', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/J', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/RST', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/K', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/K', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF1/JKFF/NOQ', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/CLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/CLK', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/J', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/J', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/RST', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/K', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/K', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF2/JKFF/NOQ', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/CLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/CLK', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/J', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/J', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/RST', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/K', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/K', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF3/JKFF/NOQ', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/CLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/CLK', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/J', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/J', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/RST', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/K', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/K', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF4/JKFF/NOQ', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/CLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/CLK', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/J', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/J', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/RST', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/K', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/K', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRC_Check/DFF5/JKFF/NOQ', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DIFFBUILDER', 'ProcessorFPGASynchronization', 'Free running');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/SET', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/SET', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/RST', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/RST', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/OQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/OQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/NOQ', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/FF1/NOQ', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg2', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg1', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/dbg1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/beginrecieving', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualDeserialize/beginrecieving', 'IOInterfaceMapping', '');

% Set SubSystem HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/ManualSerializeWrap/ManualSerializer/WORDTOBOOL', 'ProcessorFPGASynchronization', 'Free running');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CLK_OUT', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CLK_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/STATUSWORD', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/STATUSWORD', 'IOInterfaceMapping', 'x"844"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAOUT', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAOUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CLKWR', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CLKWR', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAWR', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DATAWR', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED0', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED0', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS0', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS0', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCFFSTORED', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCFFSTORED', 'IOInterfaceMapping', 'x"848"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS0BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS0BUS', 'IOInterfaceMapping', 'x"82C"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED1', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS1', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS1BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS1BUS', 'IOInterfaceMapping', 'x"828"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED2', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/CRCEXTRACTED2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS2', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POS2BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/POS2BUS', 'IOInterfaceMapping', 'x"824"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGTIMEELAPSED', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGTIMEELAPSED', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T1', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T2', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T1BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T1BUS', 'IOInterfaceMapping', 'x"850"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T2BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/TIMEELASPEDT0T2BUS', 'IOInterfaceMapping', 'x"860"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGACTIVENUMBER', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGACTIVENUMBER', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGREADPULSES', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGREADPULSES', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGWRITEOKPULSE', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGWRITEOKPULSE', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/SENSORERROR', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/SENSORERROR', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGTOTALBITSREAD', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGTOTALBITSREAD', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGPOSRAW', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGPOSRAW', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATAIN', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATAIN', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGPOSSLICED', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGPOSSLICED', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGCLK', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGCLK', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATWRITE', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATWRITE', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATAOUT', 'IOInterface', 'External Port');
hdlset_param('UZ_EnDat/UZ_ENDAT/DBGDATAOUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/RESPONSELENBUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/RESPONSELENBUS', 'IOInterfaceMapping', 'x"898"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DIFT0T1BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/DIFT0T1BUS', 'IOInterfaceMapping', 'x"8A0"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/DIFT0T2BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/DIFT0T2BUS', 'IOInterfaceMapping', 'x"8B0"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/POSAGET0BUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/POSAGET0BUS', 'IOInterfaceMapping', 'x"8C0"');

% Set Outport HDL parameters
hdlset_param('UZ_EnDat/UZ_ENDAT/SYNCQUALITYBUS', 'IOInterface', 'AXI4-Lite');
hdlset_param('UZ_EnDat/UZ_ENDAT/SYNCQUALITYBUS', 'IOInterfaceMapping', 'x"8D0"');


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
hdlcoder.runWorkflow('UZ_EnDat/UZ_ENDAT', hWC);
