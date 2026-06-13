%--------------------------------------------------------------------------
% HDL Workflow Script
% Generated with MATLAB 24.1 (R2024a) at 15:26:40 on 13/06/2026
% This script was generated using the following parameter values:
%     Filename  : 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\SVPWM_6ph\hdlworkflow.m'
%     Overwrite : true
%     Comments  : true
%     Headers   : true
%     DUT       : 'uz_SVPWM_6ph/SVPWM_and_Signal_Control'
% To view changes after modifying the workflow, run the following command:
% >> hWC.export('DUT','uz_SVPWM_6ph/SVPWM_and_Signal_Control');
%--------------------------------------------------------------------------

%% Load the Model
load_system('uz_SVPWM_6ph');

%% Restore the Model to default HDL parameters
%hdlrestoreparams('uz_SVPWM_6ph/SVPWM_and_Signal_Control');

%% Model HDL Parameters
%% Set Model 'uz_SVPWM_6ph' HDL parameters
hdlset_param('uz_SVPWM_6ph', 'CriticalPathEstimation', 'on');
hdlset_param('uz_SVPWM_6ph', 'HDLSubsystem', 'uz_SVPWM_6ph/SVPWM_and_Signal_Control');
hdlset_param('uz_SVPWM_6ph', 'ProjectFolder', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\SVPWM_6ph\hdl_prj');
hdlset_param('uz_SVPWM_6ph', 'ResetType', 'Synchronous');
hdlset_param('uz_SVPWM_6ph', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('uz_SVPWM_6ph', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('uz_SVPWM_6ph', 'SynthesisToolDeviceName', 'xczu9eg-ffvc900-1-i');
hdlset_param('uz_SVPWM_6ph', 'SynthesisToolPackageName', '');
hdlset_param('uz_SVPWM_6ph', 'SynthesisToolSpeedValue', '');
hdlset_param('uz_SVPWM_6ph', 'TargetDirectory', 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\SVPWM_6ph\hdl_prj\hdlsrc');
hdlset_param('uz_SVPWM_6ph', 'TargetFrequency', 100);
hdlset_param('uz_SVPWM_6ph', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('uz_SVPWM_6ph', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control', 'IPCoreName', 'SVPWM_6ph_ip');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control', 'IPCoreVersion', '1.0');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_en_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_en_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Mode_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Mode_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Scal_f_carrier_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Scal_f_carrier_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Scal_T_carrier_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Scal_T_carrier_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_min_SV_time_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_min_SV_time_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T1', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T2', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T3', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T4', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T5', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV1', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV1', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV2', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV2', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV3', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV3', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV4', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV4', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV5', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV5', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T1_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T2_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T3_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T4_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T4_AXI', 'IOInterfaceMapping', 'x"120"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T5_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_T5_AXI', 'IOInterfaceMapping', 'x"124"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV1_AXI', 'IOInterfaceMapping', 'x"128"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV2_AXI', 'IOInterfaceMapping', 'x"12C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV3_AXI', 'IOInterfaceMapping', 'x"130"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV4_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV4_AXI', 'IOInterfaceMapping', 'x"134"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV5_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/in_SV5_AXI', 'IOInterfaceMapping', 'x"138"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/triangle_in', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/triangle_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/count_src_ext_AXI', 'IOInterfaceMapping', 'x"13C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_trigger_source_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_trigger_source_AXI', 'IOInterfaceMapping', 'x"140"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/pwm_counter_rst', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/pwm_counter_rst', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS0_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS0_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS1_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS1_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS2_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS2_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS3_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS3_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS4_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS4_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS5_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS5_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS6_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS6_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS7_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS7_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS8_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS8_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS9_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS9_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS10_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS10_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS11_IN_External', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS11_IN_External', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB1_AXI', 'IOInterfaceMapping', 'x"144"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB2_AXI', 'IOInterfaceMapping', 'x"148"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB3_AXI', 'IOInterfaceMapping', 'x"14C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB4_AXI1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB4_AXI1', 'IOInterfaceMapping', 'x"150"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB5_AXI1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB5_AXI1', 'IOInterfaceMapping', 'x"154"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB6_AXI1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/TriState_HB6_AXI1', 'IOInterfaceMapping', 'x"158"');

% Set SubSystem HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM', 'InputPipeline', 1);
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM', 'IPCoreName', 'GenPWM_v0_ip');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM', 'OutputPipeline', 1);
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_en_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_en_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/f_carrier_kHz_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/f_carrier_kHz_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/T_carrier_us_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/T_carrier_us_AXI', 'IOInterfaceMapping', 'x"108"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/min_SV_time_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/min_SV_time_AXI', 'IOInterfaceMapping', 'x"10C"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/triangle_in', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/triangle_in', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/count_src_ext_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/count_src_ext_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_trigger_source_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_trigger_source_AXI', 'IOInterfaceMapping', 'x"100"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/counter_reset', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/counter_reset', 'IOInterfaceMapping', 'x"100"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_en_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/PWM_en_rd_AXI', 'IOInterfaceMapping', 'x"110"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/f_carrier_kHz_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/f_carrier_kHz_rd_AXI', 'IOInterfaceMapping', 'x"114"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/T_carrier_us_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/T_carrier_us_rd_AXI', 'IOInterfaceMapping', 'x"118"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/min_SV_time_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/min_SV_time_rd_AXI', 'IOInterfaceMapping', 'x"11C"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/enb_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/enb_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/triangle_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/triangle_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/dir_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/dir_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S1', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S1', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S2', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S2', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S3', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S3', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S4', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S4', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S5', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S5', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S6', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S6', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S7', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S7', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S8', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S8', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S9', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S9', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S10', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S10', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S11', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S11', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S12', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/GenSVPWM/S12', 'IOInterfaceMapping', '');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB1_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB1_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB2_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB2_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB3_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB3_AXI', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB4_AXI1', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB4_AXI1', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB5_AXI2', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB5_AXI2', 'IOInterfaceMapping', 'x"104"');

% Set Inport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB6_AXI3', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/VSI Control Signal Switch/TriState_HB6_AXI3', 'IOInterfaceMapping', 'x"104"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_en_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_en_rd_AXI', 'IOInterfaceMapping', 'x"15C"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_f_carrier_kHz_rd_AXI', 'IOInterfaceMapping', 'x"160"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_T_carrier_us_rd_AXI', 'IOInterfaceMapping', 'x"164"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_min_pulse_width_rd_AXI', 'IOInterfaceMapping', 'x"168"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_enb_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/PWM_enb_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Mode_rd_AXI', 'IOInterface', 'AXI4-Lite');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Mode_rd_AXI', 'IOInterfaceMapping', 'x"16C"');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Triangular_Max', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Triangular_Max', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Triangular_Min', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/Triangular_Min', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/triangle_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/triangle_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/dir_out', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/dir_out', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/applied_new_reference_value', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/applied_new_reference_value', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS0_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS0_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS1_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS1_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS2_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS2_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS3_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS3_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS4_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS4_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS5_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS5_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS6_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS6_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS7_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS7_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS8_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS8_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS9_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS9_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS10_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS10_OUT', 'IOInterfaceMapping', '');

% Set Outport HDL parameters
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS11_OUT', 'IOInterface', 'External Port');
hdlset_param('uz_SVPWM_6ph/SVPWM_and_Signal_Control/SS11_OUT', 'IOInterfaceMapping', '');


%% Workflow Configuration Settings
% Construct the Workflow Configuration Object with default settings
hWC = hdlcoder.WorkflowConfig('SynthesisTool','Xilinx Vivado','TargetWorkflow','IP Core Generation');

% Specify the top level project directory
hWC.ProjectFolder = 'C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\SVPWM_6ph\hdl_prj';
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
hWC.OperatingSystem = '';
hWC.HostTargetInterface = '';
hWC.GenerateHostInterfaceModel = false;
hWC.GenerateHostInterfaceScript = false;

% Set properties related to 'RunTaskBuildFPGABitstream' Task
hWC.RunExternalBuild = true;
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
hdlcoder.runWorkflow('uz_SVPWM_6ph/SVPWM_and_Signal_Control', hWC);
