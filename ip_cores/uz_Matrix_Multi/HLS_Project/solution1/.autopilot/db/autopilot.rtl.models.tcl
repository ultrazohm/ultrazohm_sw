set SynModuleInfo {
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_16_1 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_16_1 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_16_1
    SUBMODULES {
      {MODELNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init RTLNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME MatrixMultiplication_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME MatrixMultiplication_Pipeline_2 MODELNAME MatrixMultiplication_Pipeline_2 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_2}
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_22_4 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_22_4 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_22_4
    SUBMODULES {
      {MODELNAME MatrixMultiplication_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME MatrixMultiplication_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME MatrixMultiplication_Pipeline_VITIS_LOOP_25_5 MODELNAME MatrixMultiplication_Pipeline_VITIS_LOOP_25_5 RTLNAME MatrixMultiplication_MatrixMultiplication_Pipeline_VITIS_LOOP_25_5
    SUBMODULES {
      {MODELNAME MatrixMultiplication_fadd_32ns_32ns_32_5_full_dsp_1 RTLNAME MatrixMultiplication_fadd_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME MatrixMultiplication MODELNAME MatrixMultiplication RTLNAME MatrixMultiplication IS_TOP 1
    SUBMODULES {
      {MODELNAME MatrixMultiplication_mul_3s_3s_3_1_1 RTLNAME MatrixMultiplication_mul_3s_3s_3_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME MatrixMultiplication_acc_RAM_AUTO_1R1W RTLNAME MatrixMultiplication_acc_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME MatrixMultiplication_control_s_axi RTLNAME MatrixMultiplication_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
