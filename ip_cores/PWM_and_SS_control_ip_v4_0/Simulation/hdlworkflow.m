%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.10 (R2021a) at 14:48:53 on 29/09/2021
% This script was generated using the following parameter values:
%     Filename  : 'C:\GIT\UltraZohm\Software\ultrazohm_sw_PullRequests\ip_cores\PWM_and_SS_control_ip_v3_0\Simulation\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control');
%--------------------------------------------------------------------------

%% Load the Model
load_system('IP_Core_SS_Switch_and_PWM');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control');

%% Model HDL Parameters
%% Set Model 'IP_Core_SS_Switch_and_PWM' HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM', 'CriticalPathEstimation', 'on');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'HDLSubsystem', 'IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'OptimizationReport', 'on');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'ResetType', 'Synchronous');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'ResourceReport', 'on');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'SynthesisToolDeviceName', 'xczu9cg-ffvc900-1-e');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'SynthesisToolPackageName', '');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'SynthesisToolSpeedValue', '');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'Traceability', 'on');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', 'IPCoreName', 'PWM_and_SS_control_V4_ip');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', 'IPCoreVersion', '4.0');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_en_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_en_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Scal_f_carrier_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Scal_f_carrier_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Scal_T_carrier_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Scal_T_carrier_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u1_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u1_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u2_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u2_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u3_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u3_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u1_norm_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u1_norm_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u2_norm_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u2_norm_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u3_norm_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/m_u3_norm_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS0_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS0_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS1_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS1_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS2_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS2_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS3_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS3_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS4_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS4_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS5_IN_External', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS5_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB1_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB2_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB3_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_in', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_src_ext_AXI', 'IOInterfaceMapping', 'x"130"');

% Set SubSystem HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM', 'InputPipeline', 1);
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM', 'IPCoreName', 'GenPWM_v0_ip');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM', 'OutputPipeline', 1);
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_en_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_en_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/f_carrier_kHz_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/f_carrier_kHz_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/T_carrier_us_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/T_carrier_us_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/min_pulse_width_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/min_pulse_width_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U1_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U1_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U2_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U2_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U3_norm', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/U3_norm', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_in', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_src_ext_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S1', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S2', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S3', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S4', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S5', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S6', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/S6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_en_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_en_rd_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/f_carrier_kHz_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/f_carrier_kHz_rd_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/T_carrier_us_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/T_carrier_us_rd_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/min_pulse_width_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/min_pulse_width_rd_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/enb_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/enb_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/dir_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/dir_out', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB1_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB2_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/VSI Control Signal Switch/TriState_HB3_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS0_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS0_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS1_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS1_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS2_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS2_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS3_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS3_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS4_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS4_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS5_OUT', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/SS5_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_en_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_en_rd_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterfaceMapping', 'x"138"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterfaceMapping', 'x"13C"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_enb_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_enb_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_rd_AXI', 'IOInterfaceMapping', 'x"144"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Max', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Max', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Min', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Min', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/dir_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/dir_out', 'IOInterfaceMapping', '');


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
hdlcoder.runWorkflow('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', hWC);
