set SynModuleInfo {
  {SRCNAME MatrixMultiplication_Pipeline_1 MODELNAME MatrixMultiplication_Pipeline_1 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_1
    SUBMODULES {
      {MODELNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init RTLNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME MatrixMultiplication_Pipeline_2 MODELNAME MatrixMultiplication_Pipeline_2 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_2}
  {SRCNAME MatrixMultiplication_Pipeline_3 MODELNAME MatrixMultiplication_Pipeline_3 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_3}
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_20_1 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_20_1 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_20_1}
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_24_2 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_24_2 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_24_2}
  {SRCNAME MatrixMultiplication_Pipeline_6 MODELNAME MatrixMultiplication_Pipeline_6 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_6}
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_31_5 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_31_5 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_31_5
    SUBMODULES {
      {MODELNAME MatrixMultiplication_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME MatrixMultiplication_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_34_6 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_34_6 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_34_6
    SUBMODULES {
      {MODELNAME MatrixMultiplication_fadd_32ns_32ns_32_5_full_dsp_1 RTLNAME MatrixMultiplication_fadd_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_41_7 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_41_7 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_41_7}
  {SRCNAME MatrixMultiplication MODELNAME MatrixMultiplication RTLNAME MatrixMultiplication IS_TOP 1
    SUBMODULES {
      {MODELNAME MatrixMultiplication_mul_3s_3s_3_1_1 RTLNAME MatrixMultiplication_mul_3s_3s_3_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME MatrixMultiplication_A_RAM_AUTO_1R1W RTLNAME MatrixMultiplication_A_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME MatrixMultiplication_B_RAM_AUTO_1R1W RTLNAME MatrixMultiplication_B_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME MatrixMultiplication_arrays_m_axi RTLNAME MatrixMultiplication_arrays_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME MatrixMultiplication_control_s_axi RTLNAME MatrixMultiplication_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
