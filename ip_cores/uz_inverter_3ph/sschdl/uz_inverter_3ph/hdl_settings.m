%% Set Model 'gmStateSpaceHDL_uz_inverter_3ph' HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'FPToleranceValue', 1.000000e-03);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'FloatingPointTargetConfiguration', hdlcoder.createFloatingPointTargetConfig('NativeFloatingPoint' ...
, 'LatencyStrategy', 'Min') ...
);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'HDLSubsystem', 'gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/HDL Subsystem');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'MaskParameterAsGeneric', 'on');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'Oversampling', 25);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisTool', 'Xilinx Vivado');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolChipFamily', 'Zynq UltraScale+');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'SynthesisToolDeviceName', 'xazu11eg-ffvf1517-1-i');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'TargetDirectory', 'hdl_prj\hdlsrc');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'TargetFrequency', 100);
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'TargetPlatform', 'Generic Xilinx Platform');
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph', 'Workflow', 'IP Core Generation');

% Set SubSystem HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph', 'ProcessorFPGASynchronization', 'Free running');

% Set Inport HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/switch_pspl_abc', 'IOInterface', 'AXI4');

% Set Inport HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/switch_pspl_gate', 'IOInterface', 'AXI4');

% Set Inport HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/i_abc_ps', 'IOInterface', 'AXI4');

% Set Inport HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/i_abc_pl', 'IOInterface', 'AXI4');

% Set Inport HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/u_dc', 'IOInterface', 'AXI4');

% Set SubSystem HDL parameters
hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/HDL Subsystem', 'FlattenHierarchy', 'on');

hdlset_param('gmStateSpaceHDL_uz_inverter_3ph/uz_inverter_3ph/HDL Subsystem/HDL Algorithm/Mode Selection/Generate Mode Vector', 'Architecture', 'MATLAB Datapath');

