# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
# ==============================================================
proc generate {drv_handle} {
    xdefine_include_file $drv_handle "xparameters.h" "XMultilayerperceptrondecoupled" \
        "NUM_INSTANCES" \
        "DEVICE_ID" \
        "C_S_AXI_CONTROL_BASEADDR" \
        "C_S_AXI_CONTROL_HIGHADDR" \
        "C_S_AXI_CONFIGURATION_BASEADDR" \
        "C_S_AXI_CONFIGURATION_HIGHADDR"

    xdefine_config_file $drv_handle "xmultilayerperceptrondecoupled_g.c" "XMultilayerperceptrondecoupled" \
        "DEVICE_ID" \
        "C_S_AXI_CONTROL_BASEADDR" \
        "C_S_AXI_CONFIGURATION_BASEADDR"

    xdefine_canonical_xpars $drv_handle "xparameters.h" "XMultilayerperceptrondecoupled" \
        "DEVICE_ID" \
        "C_S_AXI_CONTROL_BASEADDR" \
        "C_S_AXI_CONTROL_HIGHADDR" \
        "C_S_AXI_CONFIGURATION_BASEADDR" \
        "C_S_AXI_CONFIGURATION_HIGHADDR"
}

