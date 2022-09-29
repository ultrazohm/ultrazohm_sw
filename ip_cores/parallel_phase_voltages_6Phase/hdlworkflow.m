%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.12 (R2022a) at 14:36:08 on 29/09/2022
% This script was generated using the following parameter values:
%     Filename  : 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');
%--------------------------------------------------------------------------

%% Load the Model
load_system('parallel_phase_voltages_per_switching_state_6');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');

%% Model HDL Parameters
%% Set Model 'parallel_phase_voltages_per_switching_state_6' HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'CriticalPathEstimation', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint'));
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'HDLSubsystem', 'parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'OptimizationReport', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'ResetType', 'Synchronous');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'ResourceReport', 'on');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1L-i');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolPackageName', '');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'SynthesisToolSpeedValue', '');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetDirectory', 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\hdlsrc');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetFrequency', 100);
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('parallel_phase_voltages_per_switching_state_6', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', 'IPCoreName', 'Parallel_phase_voltages_6Phase');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_offset_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_offset_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/u_dc_link_voltage_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/u_dc_link_voltage_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/use_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/use_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/theta_el_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Index_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_delay_compensation', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_delay_compensation', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_min_cost_function-and_vopt', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_min_cost_function-and_vopt', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_ADC', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/valid_in_ADC', 'IOInterfaceMapping', '');

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add1', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add2', 'OutputPipeline', 1);

% Set Sum HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Add3', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Compare Limit_High', 'OutputPipeline', 1);

% Set SubSystem HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/Compare Limit_Low', 'OutputPipeline', 1);

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/done', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/done', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_1', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_1', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_1', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_1', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_1', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_1', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_1', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_1', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_1', 'IOInterfaceMapping', 'x"120"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_2', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_2', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_2', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_2', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_2', 'IOInterfaceMapping', 'x"124"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_2', 'IOInterfaceMapping', 'x"128"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_2', 'IOInterfaceMapping', 'x"12C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_2', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_2', 'IOInterfaceMapping', 'x"130"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_3', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_3', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_3', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_3', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_3', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_3', 'IOInterfaceMapping', 'x"138"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_3', 'IOInterfaceMapping', 'x"13C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_3', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_3', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_4', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_4', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_4', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_4', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_4', 'IOInterfaceMapping', 'x"144"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_4', 'IOInterfaceMapping', 'x"148"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_4', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_4', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_4', 'IOInterfaceMapping', 'x"150"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_5', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_5', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_5', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_5', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_5', 'IOInterfaceMapping', 'x"154"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_5', 'IOInterfaceMapping', 'x"158"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_5', 'IOInterfaceMapping', 'x"15C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_5', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_5', 'IOInterfaceMapping', 'x"160"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_6', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_6', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_6', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_6', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_6', 'IOInterfaceMapping', 'x"164"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_6', 'IOInterfaceMapping', 'x"168"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_6', 'IOInterfaceMapping', 'x"16C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_6', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_6', 'IOInterfaceMapping', 'x"170"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_7', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_7', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_7', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_7', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_7', 'IOInterfaceMapping', 'x"174"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_7', 'IOInterfaceMapping', 'x"178"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_7', 'IOInterfaceMapping', 'x"17C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_7', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_7', 'IOInterfaceMapping', 'x"180"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_8', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_8', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_8', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_8', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_8', 'IOInterfaceMapping', 'x"184"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_8', 'IOInterfaceMapping', 'x"188"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_8', 'IOInterfaceMapping', 'x"18C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_8', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_8', 'IOInterfaceMapping', 'x"190"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_9', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_9', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_9', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_9', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_9', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_9', 'IOInterfaceMapping', 'x"194"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_9', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_9', 'IOInterfaceMapping', 'x"198"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_9', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_9', 'IOInterfaceMapping', 'x"19C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_9', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_9', 'IOInterfaceMapping', 'x"1A0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_10', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_10', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_10', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_10', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_10', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_10', 'IOInterfaceMapping', 'x"1A4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_10', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_10', 'IOInterfaceMapping', 'x"1A8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_10', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_10', 'IOInterfaceMapping', 'x"1AC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_10', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_10', 'IOInterfaceMapping', 'x"1B0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_11', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_11', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_11', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_11', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_11', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_11', 'IOInterfaceMapping', 'x"1B4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_11', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_11', 'IOInterfaceMapping', 'x"1B8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_11', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_11', 'IOInterfaceMapping', 'x"1BC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_11', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_11', 'IOInterfaceMapping', 'x"1C0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_12', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_12', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_12', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_12', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_12', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_12', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_12', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_12', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_12', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_12', 'IOInterfaceMapping', 'x"1C4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_12', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_12', 'IOInterfaceMapping', 'x"1C8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_12', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_12', 'IOInterfaceMapping', 'x"1CC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_12', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_12', 'IOInterfaceMapping', 'x"1D0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_13', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_13', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_13', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_13', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_13', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_13', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_13', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_13', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_13', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_13', 'IOInterfaceMapping', 'x"1D4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_13', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_13', 'IOInterfaceMapping', 'x"1D8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_13', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_13', 'IOInterfaceMapping', 'x"1DC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_13', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_13', 'IOInterfaceMapping', 'x"1E0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_14', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_14', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_14', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_14', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_14', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_14', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_14', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_14', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_14', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_14', 'IOInterfaceMapping', 'x"1E4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_14', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_14', 'IOInterfaceMapping', 'x"1E8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_14', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_14', 'IOInterfaceMapping', 'x"1EC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_14', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_14', 'IOInterfaceMapping', 'x"1F0"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_15', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_15', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_15', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_15', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_15', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_15', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_15', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_15', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_15', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_15', 'IOInterfaceMapping', 'x"1F4"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_15', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_15', 'IOInterfaceMapping', 'x"1F8"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_15', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_15', 'IOInterfaceMapping', 'x"1FC"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_15', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_15', 'IOInterfaceMapping', 'x"200"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_16', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_16', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_16', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_16', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_16', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_16', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_16', 'IOInterface', 'External Port');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_16', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_16', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/d_voltage_per_switching_state_AXI_16', 'IOInterfaceMapping', 'x"204"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_16', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/q_voltage_per_switching_state_AXI_16', 'IOInterfaceMapping', 'x"208"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_16', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/x_voltage_per_switching_state_AXI_16', 'IOInterfaceMapping', 'x"20C"');

% Set Outport HDL parameters
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_16', 'IOInterface', 'AXI4-Lite');
hdlset_param('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state/y_voltage_per_switching_state_AXI_16', 'IOInterfaceMapping', 'x"210"');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase';
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
hdlcoder.runWorkflow('parallel_phase_voltages_per_switching_state_6/Phase_voltages_per_switching_state', hWC);
