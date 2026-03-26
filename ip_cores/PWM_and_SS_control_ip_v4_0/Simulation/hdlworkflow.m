%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 9.14 (R2023a) at 16:06:13 on 26/03/2026
% This script was generated using the following parameter values:
%     Filename  : '/home/ts/Documents/pr_review/can/ultrazohm_sw/ip_cores/PWM_and_SS_control_ip_v4_0/hdlworkflow.m'
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
hdlset_param('IP_Core_SS_Switch_and_PWM', 'TargetDirectory', 'hdl_prj/hdlsrc');
hdlset_param('IP_Core_SS_Switch_and_PWM', 'Traceability', 'on');

% Set SubSystem HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', 'IPCoreName', 'PWM_and_SS_control_V4_ip');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', 'IPCoreVersion', '4.4');
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
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/TriState_HB_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_in', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/count_src_ext_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB1_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB2_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_shift_HB3_AXI', 'IOInterfaceMapping', 'x"138"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_trigger_source_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_trigger_source_AXI', 'IOInterfaceMapping', 'x"13C"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/pwm_counter_rst', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/pwm_counter_rst', 'IOInterfaceMapping', '');

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
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_in', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/count_src_ext_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB1_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB2_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_shift_HB3_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_trigger_source_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/PWM_trigger_source_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/counter_reset', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/counter_reset', 'IOInterfaceMapping', 'x"100"');

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
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/GenPWM/triangle_out', 'IOInterfaceMapping', '');

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
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_en_rd_AXI', 'IOInterfaceMapping', 'x"140"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterfaceMapping', 'x"144"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterfaceMapping', 'x"148"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterfaceMapping', 'x"14C"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_enb_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/PWM_enb_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Mode_rd_AXI', 'IOInterfaceMapping', 'x"150"');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Max', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Max', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Min', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/Triangular_Min', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/triangle_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/dir_out', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/dir_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/applied_new_reference_value', 'IOInterface', 'External Port');
hdlset_param('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control/applied_new_reference_value', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','No synthesis tool specified','TargetWorkflow','Generic ASIC/FPGA');

% Specify the top level project directory
hWC.ProjectFolder = 'hdl_prj';

% Set Workflow tasks to run
hWC.RunTaskGenerateRTLCodeAndTestbench = true;
hWC.RunTaskVerifyWithHDLCosimulation = false;
hWC.RunTaskCreateProject = true;
hWC.RunTaskPerformLogicSynthesis = true;
hWC.RunTaskPerformMapping = true;
hWC.RunTaskPerformPlaceAndRoute = false;
hWC.RunTaskAnnotateModelWithSynthesisResult = true;

% Set properties related to 'RunTaskGenerateRTLCodeAndTestbench' Task
hWC.GenerateRTLCode = true;
hWC.GenerateTestbench = false;
hWC.GenerateValidationModel = false;

% Set properties related to 'RunTaskCreateProject' Task
hWC.Objective = hdlcoder.Objective.None;
hWC.AdditionalProjectCreationTclFiles = '';

% Set properties related to 'RunTaskPerformMapping' Task
hWC.SkipPreRouteTimingAnalysis = false;

% Set properties related to 'RunTaskPerformPlaceAndRoute' Task
hWC.IgnorePlaceAndRouteErrors = false;

% Set properties related to 'RunTaskAnnotateModelWithSynthesisResult' Task
hWC.CriticalPathSource = 'pre-route';
hWC.CriticalPathNumber =  1;
hWC.ShowAllPaths = false;
hWC.ShowDelayData = true;
hWC.ShowUniquePaths = false;
hWC.ShowEndsOnly = false;
hWC.AnnotateModel = 'generated';

% Validate the Workflow Configuration Object
hWC.validate;

%% Run the workflow
hdlcoder.runWorkflow('IP_Core_SS_Switch_and_PWM/PWM_and_Switching_Signal_Control', hWC);
