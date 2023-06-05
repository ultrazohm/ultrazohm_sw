
    wire dl_reset;
    wire dl_clock;
    assign dl_reset = ~ap_rst;
    assign dl_clock = ap_clk;
    wire [10:0] proc_0_data_FIFO_blk;
    wire [10:0] proc_0_data_PIPO_blk;
    wire [10:0] proc_0_start_FIFO_blk;
    wire [10:0] proc_0_TLF_FIFO_blk;
    wire [10:0] proc_0_input_sync_blk;
    wire [10:0] proc_0_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_0;
    reg [10:0] proc_dep_vld_vec_0_reg;
    wire [11:0] in_chan_dep_vld_vec_0;
    wire [287:0] in_chan_dep_data_vec_0;
    wire [11:0] token_in_vec_0;
    wire [10:0] out_chan_dep_vld_vec_0;
    wire [23:0] out_chan_dep_data_0;
    wire [10:0] token_out_vec_0;
    wire dl_detect_out_0;
    wire dep_chan_vld_1_0;
    wire [23:0] dep_chan_data_1_0;
    wire token_1_0;
    wire dep_chan_vld_2_0;
    wire [23:0] dep_chan_data_2_0;
    wire token_2_0;
    wire dep_chan_vld_3_0;
    wire [23:0] dep_chan_data_3_0;
    wire token_3_0;
    wire dep_chan_vld_4_0;
    wire [23:0] dep_chan_data_4_0;
    wire token_4_0;
    wire dep_chan_vld_5_0;
    wire [23:0] dep_chan_data_5_0;
    wire token_5_0;
    wire dep_chan_vld_6_0;
    wire [23:0] dep_chan_data_6_0;
    wire token_6_0;
    wire dep_chan_vld_12_0;
    wire [23:0] dep_chan_data_12_0;
    wire token_12_0;
    wire dep_chan_vld_13_0;
    wire [23:0] dep_chan_data_13_0;
    wire token_13_0;
    wire dep_chan_vld_14_0;
    wire [23:0] dep_chan_data_14_0;
    wire token_14_0;
    wire dep_chan_vld_15_0;
    wire [23:0] dep_chan_data_15_0;
    wire token_15_0;
    wire dep_chan_vld_16_0;
    wire [23:0] dep_chan_data_16_0;
    wire token_16_0;
    wire dep_chan_vld_17_0;
    wire [23:0] dep_chan_data_17_0;
    wire token_17_0;
    wire [10:0] proc_1_data_FIFO_blk;
    wire [10:0] proc_1_data_PIPO_blk;
    wire [10:0] proc_1_start_FIFO_blk;
    wire [10:0] proc_1_TLF_FIFO_blk;
    wire [10:0] proc_1_input_sync_blk;
    wire [10:0] proc_1_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_1;
    reg [10:0] proc_dep_vld_vec_1_reg;
    wire [11:0] in_chan_dep_vld_vec_1;
    wire [287:0] in_chan_dep_data_vec_1;
    wire [11:0] token_in_vec_1;
    wire [10:0] out_chan_dep_vld_vec_1;
    wire [23:0] out_chan_dep_data_1;
    wire [10:0] token_out_vec_1;
    wire dl_detect_out_1;
    wire dep_chan_vld_0_1;
    wire [23:0] dep_chan_data_0_1;
    wire token_0_1;
    wire dep_chan_vld_2_1;
    wire [23:0] dep_chan_data_2_1;
    wire token_2_1;
    wire dep_chan_vld_3_1;
    wire [23:0] dep_chan_data_3_1;
    wire token_3_1;
    wire dep_chan_vld_4_1;
    wire [23:0] dep_chan_data_4_1;
    wire token_4_1;
    wire dep_chan_vld_5_1;
    wire [23:0] dep_chan_data_5_1;
    wire token_5_1;
    wire dep_chan_vld_7_1;
    wire [23:0] dep_chan_data_7_1;
    wire token_7_1;
    wire dep_chan_vld_12_1;
    wire [23:0] dep_chan_data_12_1;
    wire token_12_1;
    wire dep_chan_vld_13_1;
    wire [23:0] dep_chan_data_13_1;
    wire token_13_1;
    wire dep_chan_vld_14_1;
    wire [23:0] dep_chan_data_14_1;
    wire token_14_1;
    wire dep_chan_vld_15_1;
    wire [23:0] dep_chan_data_15_1;
    wire token_15_1;
    wire dep_chan_vld_16_1;
    wire [23:0] dep_chan_data_16_1;
    wire token_16_1;
    wire dep_chan_vld_17_1;
    wire [23:0] dep_chan_data_17_1;
    wire token_17_1;
    wire [10:0] proc_2_data_FIFO_blk;
    wire [10:0] proc_2_data_PIPO_blk;
    wire [10:0] proc_2_start_FIFO_blk;
    wire [10:0] proc_2_TLF_FIFO_blk;
    wire [10:0] proc_2_input_sync_blk;
    wire [10:0] proc_2_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_2;
    reg [10:0] proc_dep_vld_vec_2_reg;
    wire [11:0] in_chan_dep_vld_vec_2;
    wire [287:0] in_chan_dep_data_vec_2;
    wire [11:0] token_in_vec_2;
    wire [10:0] out_chan_dep_vld_vec_2;
    wire [23:0] out_chan_dep_data_2;
    wire [10:0] token_out_vec_2;
    wire dl_detect_out_2;
    wire dep_chan_vld_0_2;
    wire [23:0] dep_chan_data_0_2;
    wire token_0_2;
    wire dep_chan_vld_1_2;
    wire [23:0] dep_chan_data_1_2;
    wire token_1_2;
    wire dep_chan_vld_3_2;
    wire [23:0] dep_chan_data_3_2;
    wire token_3_2;
    wire dep_chan_vld_4_2;
    wire [23:0] dep_chan_data_4_2;
    wire token_4_2;
    wire dep_chan_vld_5_2;
    wire [23:0] dep_chan_data_5_2;
    wire token_5_2;
    wire dep_chan_vld_8_2;
    wire [23:0] dep_chan_data_8_2;
    wire token_8_2;
    wire dep_chan_vld_12_2;
    wire [23:0] dep_chan_data_12_2;
    wire token_12_2;
    wire dep_chan_vld_13_2;
    wire [23:0] dep_chan_data_13_2;
    wire token_13_2;
    wire dep_chan_vld_14_2;
    wire [23:0] dep_chan_data_14_2;
    wire token_14_2;
    wire dep_chan_vld_15_2;
    wire [23:0] dep_chan_data_15_2;
    wire token_15_2;
    wire dep_chan_vld_16_2;
    wire [23:0] dep_chan_data_16_2;
    wire token_16_2;
    wire dep_chan_vld_17_2;
    wire [23:0] dep_chan_data_17_2;
    wire token_17_2;
    wire [10:0] proc_3_data_FIFO_blk;
    wire [10:0] proc_3_data_PIPO_blk;
    wire [10:0] proc_3_start_FIFO_blk;
    wire [10:0] proc_3_TLF_FIFO_blk;
    wire [10:0] proc_3_input_sync_blk;
    wire [10:0] proc_3_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_3;
    reg [10:0] proc_dep_vld_vec_3_reg;
    wire [11:0] in_chan_dep_vld_vec_3;
    wire [287:0] in_chan_dep_data_vec_3;
    wire [11:0] token_in_vec_3;
    wire [10:0] out_chan_dep_vld_vec_3;
    wire [23:0] out_chan_dep_data_3;
    wire [10:0] token_out_vec_3;
    wire dl_detect_out_3;
    wire dep_chan_vld_0_3;
    wire [23:0] dep_chan_data_0_3;
    wire token_0_3;
    wire dep_chan_vld_1_3;
    wire [23:0] dep_chan_data_1_3;
    wire token_1_3;
    wire dep_chan_vld_2_3;
    wire [23:0] dep_chan_data_2_3;
    wire token_2_3;
    wire dep_chan_vld_4_3;
    wire [23:0] dep_chan_data_4_3;
    wire token_4_3;
    wire dep_chan_vld_5_3;
    wire [23:0] dep_chan_data_5_3;
    wire token_5_3;
    wire dep_chan_vld_9_3;
    wire [23:0] dep_chan_data_9_3;
    wire token_9_3;
    wire dep_chan_vld_12_3;
    wire [23:0] dep_chan_data_12_3;
    wire token_12_3;
    wire dep_chan_vld_13_3;
    wire [23:0] dep_chan_data_13_3;
    wire token_13_3;
    wire dep_chan_vld_14_3;
    wire [23:0] dep_chan_data_14_3;
    wire token_14_3;
    wire dep_chan_vld_15_3;
    wire [23:0] dep_chan_data_15_3;
    wire token_15_3;
    wire dep_chan_vld_16_3;
    wire [23:0] dep_chan_data_16_3;
    wire token_16_3;
    wire dep_chan_vld_17_3;
    wire [23:0] dep_chan_data_17_3;
    wire token_17_3;
    wire [10:0] proc_4_data_FIFO_blk;
    wire [10:0] proc_4_data_PIPO_blk;
    wire [10:0] proc_4_start_FIFO_blk;
    wire [10:0] proc_4_TLF_FIFO_blk;
    wire [10:0] proc_4_input_sync_blk;
    wire [10:0] proc_4_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_4;
    reg [10:0] proc_dep_vld_vec_4_reg;
    wire [11:0] in_chan_dep_vld_vec_4;
    wire [287:0] in_chan_dep_data_vec_4;
    wire [11:0] token_in_vec_4;
    wire [10:0] out_chan_dep_vld_vec_4;
    wire [23:0] out_chan_dep_data_4;
    wire [10:0] token_out_vec_4;
    wire dl_detect_out_4;
    wire dep_chan_vld_0_4;
    wire [23:0] dep_chan_data_0_4;
    wire token_0_4;
    wire dep_chan_vld_1_4;
    wire [23:0] dep_chan_data_1_4;
    wire token_1_4;
    wire dep_chan_vld_2_4;
    wire [23:0] dep_chan_data_2_4;
    wire token_2_4;
    wire dep_chan_vld_3_4;
    wire [23:0] dep_chan_data_3_4;
    wire token_3_4;
    wire dep_chan_vld_5_4;
    wire [23:0] dep_chan_data_5_4;
    wire token_5_4;
    wire dep_chan_vld_10_4;
    wire [23:0] dep_chan_data_10_4;
    wire token_10_4;
    wire dep_chan_vld_12_4;
    wire [23:0] dep_chan_data_12_4;
    wire token_12_4;
    wire dep_chan_vld_13_4;
    wire [23:0] dep_chan_data_13_4;
    wire token_13_4;
    wire dep_chan_vld_14_4;
    wire [23:0] dep_chan_data_14_4;
    wire token_14_4;
    wire dep_chan_vld_15_4;
    wire [23:0] dep_chan_data_15_4;
    wire token_15_4;
    wire dep_chan_vld_16_4;
    wire [23:0] dep_chan_data_16_4;
    wire token_16_4;
    wire dep_chan_vld_17_4;
    wire [23:0] dep_chan_data_17_4;
    wire token_17_4;
    wire [10:0] proc_5_data_FIFO_blk;
    wire [10:0] proc_5_data_PIPO_blk;
    wire [10:0] proc_5_start_FIFO_blk;
    wire [10:0] proc_5_TLF_FIFO_blk;
    wire [10:0] proc_5_input_sync_blk;
    wire [10:0] proc_5_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_5;
    reg [10:0] proc_dep_vld_vec_5_reg;
    wire [11:0] in_chan_dep_vld_vec_5;
    wire [287:0] in_chan_dep_data_vec_5;
    wire [11:0] token_in_vec_5;
    wire [10:0] out_chan_dep_vld_vec_5;
    wire [23:0] out_chan_dep_data_5;
    wire [10:0] token_out_vec_5;
    wire dl_detect_out_5;
    wire dep_chan_vld_0_5;
    wire [23:0] dep_chan_data_0_5;
    wire token_0_5;
    wire dep_chan_vld_1_5;
    wire [23:0] dep_chan_data_1_5;
    wire token_1_5;
    wire dep_chan_vld_2_5;
    wire [23:0] dep_chan_data_2_5;
    wire token_2_5;
    wire dep_chan_vld_3_5;
    wire [23:0] dep_chan_data_3_5;
    wire token_3_5;
    wire dep_chan_vld_4_5;
    wire [23:0] dep_chan_data_4_5;
    wire token_4_5;
    wire dep_chan_vld_11_5;
    wire [23:0] dep_chan_data_11_5;
    wire token_11_5;
    wire dep_chan_vld_12_5;
    wire [23:0] dep_chan_data_12_5;
    wire token_12_5;
    wire dep_chan_vld_13_5;
    wire [23:0] dep_chan_data_13_5;
    wire token_13_5;
    wire dep_chan_vld_14_5;
    wire [23:0] dep_chan_data_14_5;
    wire token_14_5;
    wire dep_chan_vld_15_5;
    wire [23:0] dep_chan_data_15_5;
    wire token_15_5;
    wire dep_chan_vld_16_5;
    wire [23:0] dep_chan_data_16_5;
    wire token_16_5;
    wire dep_chan_vld_17_5;
    wire [23:0] dep_chan_data_17_5;
    wire token_17_5;
    wire [0:0] proc_6_data_FIFO_blk;
    wire [0:0] proc_6_data_PIPO_blk;
    wire [0:0] proc_6_start_FIFO_blk;
    wire [0:0] proc_6_TLF_FIFO_blk;
    wire [0:0] proc_6_input_sync_blk;
    wire [0:0] proc_6_output_sync_blk;
    wire [0:0] proc_dep_vld_vec_6;
    reg [0:0] proc_dep_vld_vec_6_reg;
    wire [0:0] in_chan_dep_vld_vec_6;
    wire [23:0] in_chan_dep_data_vec_6;
    wire [0:0] token_in_vec_6;
    wire [0:0] out_chan_dep_vld_vec_6;
    wire [23:0] out_chan_dep_data_6;
    wire [0:0] token_out_vec_6;
    wire dl_detect_out_6;
    wire dep_chan_vld_7_6;
    wire [23:0] dep_chan_data_7_6;
    wire token_7_6;
    wire [1:0] proc_7_data_FIFO_blk;
    wire [1:0] proc_7_data_PIPO_blk;
    wire [1:0] proc_7_start_FIFO_blk;
    wire [1:0] proc_7_TLF_FIFO_blk;
    wire [1:0] proc_7_input_sync_blk;
    wire [1:0] proc_7_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_7;
    reg [1:0] proc_dep_vld_vec_7_reg;
    wire [0:0] in_chan_dep_vld_vec_7;
    wire [23:0] in_chan_dep_data_vec_7;
    wire [0:0] token_in_vec_7;
    wire [1:0] out_chan_dep_vld_vec_7;
    wire [23:0] out_chan_dep_data_7;
    wire [1:0] token_out_vec_7;
    wire dl_detect_out_7;
    wire dep_chan_vld_8_7;
    wire [23:0] dep_chan_data_8_7;
    wire token_8_7;
    wire [1:0] proc_8_data_FIFO_blk;
    wire [1:0] proc_8_data_PIPO_blk;
    wire [1:0] proc_8_start_FIFO_blk;
    wire [1:0] proc_8_TLF_FIFO_blk;
    wire [1:0] proc_8_input_sync_blk;
    wire [1:0] proc_8_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_8;
    reg [1:0] proc_dep_vld_vec_8_reg;
    wire [0:0] in_chan_dep_vld_vec_8;
    wire [23:0] in_chan_dep_data_vec_8;
    wire [0:0] token_in_vec_8;
    wire [1:0] out_chan_dep_vld_vec_8;
    wire [23:0] out_chan_dep_data_8;
    wire [1:0] token_out_vec_8;
    wire dl_detect_out_8;
    wire dep_chan_vld_9_8;
    wire [23:0] dep_chan_data_9_8;
    wire token_9_8;
    wire [1:0] proc_9_data_FIFO_blk;
    wire [1:0] proc_9_data_PIPO_blk;
    wire [1:0] proc_9_start_FIFO_blk;
    wire [1:0] proc_9_TLF_FIFO_blk;
    wire [1:0] proc_9_input_sync_blk;
    wire [1:0] proc_9_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_9;
    reg [1:0] proc_dep_vld_vec_9_reg;
    wire [0:0] in_chan_dep_vld_vec_9;
    wire [23:0] in_chan_dep_data_vec_9;
    wire [0:0] token_in_vec_9;
    wire [1:0] out_chan_dep_vld_vec_9;
    wire [23:0] out_chan_dep_data_9;
    wire [1:0] token_out_vec_9;
    wire dl_detect_out_9;
    wire dep_chan_vld_10_9;
    wire [23:0] dep_chan_data_10_9;
    wire token_10_9;
    wire [1:0] proc_10_data_FIFO_blk;
    wire [1:0] proc_10_data_PIPO_blk;
    wire [1:0] proc_10_start_FIFO_blk;
    wire [1:0] proc_10_TLF_FIFO_blk;
    wire [1:0] proc_10_input_sync_blk;
    wire [1:0] proc_10_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_10;
    reg [1:0] proc_dep_vld_vec_10_reg;
    wire [0:0] in_chan_dep_vld_vec_10;
    wire [23:0] in_chan_dep_data_vec_10;
    wire [0:0] token_in_vec_10;
    wire [1:0] out_chan_dep_vld_vec_10;
    wire [23:0] out_chan_dep_data_10;
    wire [1:0] token_out_vec_10;
    wire dl_detect_out_10;
    wire dep_chan_vld_11_10;
    wire [23:0] dep_chan_data_11_10;
    wire token_11_10;
    wire [2:0] proc_11_data_FIFO_blk;
    wire [2:0] proc_11_data_PIPO_blk;
    wire [2:0] proc_11_start_FIFO_blk;
    wire [2:0] proc_11_TLF_FIFO_blk;
    wire [2:0] proc_11_input_sync_blk;
    wire [2:0] proc_11_output_sync_blk;
    wire [2:0] proc_dep_vld_vec_11;
    reg [2:0] proc_dep_vld_vec_11_reg;
    wire [0:0] in_chan_dep_vld_vec_11;
    wire [23:0] in_chan_dep_data_vec_11;
    wire [0:0] token_in_vec_11;
    wire [2:0] out_chan_dep_vld_vec_11;
    wire [23:0] out_chan_dep_data_11;
    wire [2:0] token_out_vec_11;
    wire dl_detect_out_11;
    wire dep_chan_vld_23_11;
    wire [23:0] dep_chan_data_23_11;
    wire token_23_11;
    wire [10:0] proc_12_data_FIFO_blk;
    wire [10:0] proc_12_data_PIPO_blk;
    wire [10:0] proc_12_start_FIFO_blk;
    wire [10:0] proc_12_TLF_FIFO_blk;
    wire [10:0] proc_12_input_sync_blk;
    wire [10:0] proc_12_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_12;
    reg [10:0] proc_dep_vld_vec_12_reg;
    wire [11:0] in_chan_dep_vld_vec_12;
    wire [287:0] in_chan_dep_data_vec_12;
    wire [11:0] token_in_vec_12;
    wire [10:0] out_chan_dep_vld_vec_12;
    wire [23:0] out_chan_dep_data_12;
    wire [10:0] token_out_vec_12;
    wire dl_detect_out_12;
    wire dep_chan_vld_0_12;
    wire [23:0] dep_chan_data_0_12;
    wire token_0_12;
    wire dep_chan_vld_1_12;
    wire [23:0] dep_chan_data_1_12;
    wire token_1_12;
    wire dep_chan_vld_2_12;
    wire [23:0] dep_chan_data_2_12;
    wire token_2_12;
    wire dep_chan_vld_3_12;
    wire [23:0] dep_chan_data_3_12;
    wire token_3_12;
    wire dep_chan_vld_4_12;
    wire [23:0] dep_chan_data_4_12;
    wire token_4_12;
    wire dep_chan_vld_5_12;
    wire [23:0] dep_chan_data_5_12;
    wire token_5_12;
    wire dep_chan_vld_13_12;
    wire [23:0] dep_chan_data_13_12;
    wire token_13_12;
    wire dep_chan_vld_14_12;
    wire [23:0] dep_chan_data_14_12;
    wire token_14_12;
    wire dep_chan_vld_15_12;
    wire [23:0] dep_chan_data_15_12;
    wire token_15_12;
    wire dep_chan_vld_16_12;
    wire [23:0] dep_chan_data_16_12;
    wire token_16_12;
    wire dep_chan_vld_17_12;
    wire [23:0] dep_chan_data_17_12;
    wire token_17_12;
    wire dep_chan_vld_18_12;
    wire [23:0] dep_chan_data_18_12;
    wire token_18_12;
    wire [10:0] proc_13_data_FIFO_blk;
    wire [10:0] proc_13_data_PIPO_blk;
    wire [10:0] proc_13_start_FIFO_blk;
    wire [10:0] proc_13_TLF_FIFO_blk;
    wire [10:0] proc_13_input_sync_blk;
    wire [10:0] proc_13_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_13;
    reg [10:0] proc_dep_vld_vec_13_reg;
    wire [11:0] in_chan_dep_vld_vec_13;
    wire [287:0] in_chan_dep_data_vec_13;
    wire [11:0] token_in_vec_13;
    wire [10:0] out_chan_dep_vld_vec_13;
    wire [23:0] out_chan_dep_data_13;
    wire [10:0] token_out_vec_13;
    wire dl_detect_out_13;
    wire dep_chan_vld_0_13;
    wire [23:0] dep_chan_data_0_13;
    wire token_0_13;
    wire dep_chan_vld_1_13;
    wire [23:0] dep_chan_data_1_13;
    wire token_1_13;
    wire dep_chan_vld_2_13;
    wire [23:0] dep_chan_data_2_13;
    wire token_2_13;
    wire dep_chan_vld_3_13;
    wire [23:0] dep_chan_data_3_13;
    wire token_3_13;
    wire dep_chan_vld_4_13;
    wire [23:0] dep_chan_data_4_13;
    wire token_4_13;
    wire dep_chan_vld_5_13;
    wire [23:0] dep_chan_data_5_13;
    wire token_5_13;
    wire dep_chan_vld_12_13;
    wire [23:0] dep_chan_data_12_13;
    wire token_12_13;
    wire dep_chan_vld_14_13;
    wire [23:0] dep_chan_data_14_13;
    wire token_14_13;
    wire dep_chan_vld_15_13;
    wire [23:0] dep_chan_data_15_13;
    wire token_15_13;
    wire dep_chan_vld_16_13;
    wire [23:0] dep_chan_data_16_13;
    wire token_16_13;
    wire dep_chan_vld_17_13;
    wire [23:0] dep_chan_data_17_13;
    wire token_17_13;
    wire dep_chan_vld_19_13;
    wire [23:0] dep_chan_data_19_13;
    wire token_19_13;
    wire [10:0] proc_14_data_FIFO_blk;
    wire [10:0] proc_14_data_PIPO_blk;
    wire [10:0] proc_14_start_FIFO_blk;
    wire [10:0] proc_14_TLF_FIFO_blk;
    wire [10:0] proc_14_input_sync_blk;
    wire [10:0] proc_14_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_14;
    reg [10:0] proc_dep_vld_vec_14_reg;
    wire [11:0] in_chan_dep_vld_vec_14;
    wire [287:0] in_chan_dep_data_vec_14;
    wire [11:0] token_in_vec_14;
    wire [10:0] out_chan_dep_vld_vec_14;
    wire [23:0] out_chan_dep_data_14;
    wire [10:0] token_out_vec_14;
    wire dl_detect_out_14;
    wire dep_chan_vld_0_14;
    wire [23:0] dep_chan_data_0_14;
    wire token_0_14;
    wire dep_chan_vld_1_14;
    wire [23:0] dep_chan_data_1_14;
    wire token_1_14;
    wire dep_chan_vld_2_14;
    wire [23:0] dep_chan_data_2_14;
    wire token_2_14;
    wire dep_chan_vld_3_14;
    wire [23:0] dep_chan_data_3_14;
    wire token_3_14;
    wire dep_chan_vld_4_14;
    wire [23:0] dep_chan_data_4_14;
    wire token_4_14;
    wire dep_chan_vld_5_14;
    wire [23:0] dep_chan_data_5_14;
    wire token_5_14;
    wire dep_chan_vld_12_14;
    wire [23:0] dep_chan_data_12_14;
    wire token_12_14;
    wire dep_chan_vld_13_14;
    wire [23:0] dep_chan_data_13_14;
    wire token_13_14;
    wire dep_chan_vld_15_14;
    wire [23:0] dep_chan_data_15_14;
    wire token_15_14;
    wire dep_chan_vld_16_14;
    wire [23:0] dep_chan_data_16_14;
    wire token_16_14;
    wire dep_chan_vld_17_14;
    wire [23:0] dep_chan_data_17_14;
    wire token_17_14;
    wire dep_chan_vld_20_14;
    wire [23:0] dep_chan_data_20_14;
    wire token_20_14;
    wire [10:0] proc_15_data_FIFO_blk;
    wire [10:0] proc_15_data_PIPO_blk;
    wire [10:0] proc_15_start_FIFO_blk;
    wire [10:0] proc_15_TLF_FIFO_blk;
    wire [10:0] proc_15_input_sync_blk;
    wire [10:0] proc_15_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_15;
    reg [10:0] proc_dep_vld_vec_15_reg;
    wire [11:0] in_chan_dep_vld_vec_15;
    wire [287:0] in_chan_dep_data_vec_15;
    wire [11:0] token_in_vec_15;
    wire [10:0] out_chan_dep_vld_vec_15;
    wire [23:0] out_chan_dep_data_15;
    wire [10:0] token_out_vec_15;
    wire dl_detect_out_15;
    wire dep_chan_vld_0_15;
    wire [23:0] dep_chan_data_0_15;
    wire token_0_15;
    wire dep_chan_vld_1_15;
    wire [23:0] dep_chan_data_1_15;
    wire token_1_15;
    wire dep_chan_vld_2_15;
    wire [23:0] dep_chan_data_2_15;
    wire token_2_15;
    wire dep_chan_vld_3_15;
    wire [23:0] dep_chan_data_3_15;
    wire token_3_15;
    wire dep_chan_vld_4_15;
    wire [23:0] dep_chan_data_4_15;
    wire token_4_15;
    wire dep_chan_vld_5_15;
    wire [23:0] dep_chan_data_5_15;
    wire token_5_15;
    wire dep_chan_vld_12_15;
    wire [23:0] dep_chan_data_12_15;
    wire token_12_15;
    wire dep_chan_vld_13_15;
    wire [23:0] dep_chan_data_13_15;
    wire token_13_15;
    wire dep_chan_vld_14_15;
    wire [23:0] dep_chan_data_14_15;
    wire token_14_15;
    wire dep_chan_vld_16_15;
    wire [23:0] dep_chan_data_16_15;
    wire token_16_15;
    wire dep_chan_vld_17_15;
    wire [23:0] dep_chan_data_17_15;
    wire token_17_15;
    wire dep_chan_vld_21_15;
    wire [23:0] dep_chan_data_21_15;
    wire token_21_15;
    wire [10:0] proc_16_data_FIFO_blk;
    wire [10:0] proc_16_data_PIPO_blk;
    wire [10:0] proc_16_start_FIFO_blk;
    wire [10:0] proc_16_TLF_FIFO_blk;
    wire [10:0] proc_16_input_sync_blk;
    wire [10:0] proc_16_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_16;
    reg [10:0] proc_dep_vld_vec_16_reg;
    wire [11:0] in_chan_dep_vld_vec_16;
    wire [287:0] in_chan_dep_data_vec_16;
    wire [11:0] token_in_vec_16;
    wire [10:0] out_chan_dep_vld_vec_16;
    wire [23:0] out_chan_dep_data_16;
    wire [10:0] token_out_vec_16;
    wire dl_detect_out_16;
    wire dep_chan_vld_0_16;
    wire [23:0] dep_chan_data_0_16;
    wire token_0_16;
    wire dep_chan_vld_1_16;
    wire [23:0] dep_chan_data_1_16;
    wire token_1_16;
    wire dep_chan_vld_2_16;
    wire [23:0] dep_chan_data_2_16;
    wire token_2_16;
    wire dep_chan_vld_3_16;
    wire [23:0] dep_chan_data_3_16;
    wire token_3_16;
    wire dep_chan_vld_4_16;
    wire [23:0] dep_chan_data_4_16;
    wire token_4_16;
    wire dep_chan_vld_5_16;
    wire [23:0] dep_chan_data_5_16;
    wire token_5_16;
    wire dep_chan_vld_12_16;
    wire [23:0] dep_chan_data_12_16;
    wire token_12_16;
    wire dep_chan_vld_13_16;
    wire [23:0] dep_chan_data_13_16;
    wire token_13_16;
    wire dep_chan_vld_14_16;
    wire [23:0] dep_chan_data_14_16;
    wire token_14_16;
    wire dep_chan_vld_15_16;
    wire [23:0] dep_chan_data_15_16;
    wire token_15_16;
    wire dep_chan_vld_17_16;
    wire [23:0] dep_chan_data_17_16;
    wire token_17_16;
    wire dep_chan_vld_22_16;
    wire [23:0] dep_chan_data_22_16;
    wire token_22_16;
    wire [10:0] proc_17_data_FIFO_blk;
    wire [10:0] proc_17_data_PIPO_blk;
    wire [10:0] proc_17_start_FIFO_blk;
    wire [10:0] proc_17_TLF_FIFO_blk;
    wire [10:0] proc_17_input_sync_blk;
    wire [10:0] proc_17_output_sync_blk;
    wire [10:0] proc_dep_vld_vec_17;
    reg [10:0] proc_dep_vld_vec_17_reg;
    wire [11:0] in_chan_dep_vld_vec_17;
    wire [287:0] in_chan_dep_data_vec_17;
    wire [11:0] token_in_vec_17;
    wire [10:0] out_chan_dep_vld_vec_17;
    wire [23:0] out_chan_dep_data_17;
    wire [10:0] token_out_vec_17;
    wire dl_detect_out_17;
    wire dep_chan_vld_0_17;
    wire [23:0] dep_chan_data_0_17;
    wire token_0_17;
    wire dep_chan_vld_1_17;
    wire [23:0] dep_chan_data_1_17;
    wire token_1_17;
    wire dep_chan_vld_2_17;
    wire [23:0] dep_chan_data_2_17;
    wire token_2_17;
    wire dep_chan_vld_3_17;
    wire [23:0] dep_chan_data_3_17;
    wire token_3_17;
    wire dep_chan_vld_4_17;
    wire [23:0] dep_chan_data_4_17;
    wire token_4_17;
    wire dep_chan_vld_5_17;
    wire [23:0] dep_chan_data_5_17;
    wire token_5_17;
    wire dep_chan_vld_12_17;
    wire [23:0] dep_chan_data_12_17;
    wire token_12_17;
    wire dep_chan_vld_13_17;
    wire [23:0] dep_chan_data_13_17;
    wire token_13_17;
    wire dep_chan_vld_14_17;
    wire [23:0] dep_chan_data_14_17;
    wire token_14_17;
    wire dep_chan_vld_15_17;
    wire [23:0] dep_chan_data_15_17;
    wire token_15_17;
    wire dep_chan_vld_16_17;
    wire [23:0] dep_chan_data_16_17;
    wire token_16_17;
    wire dep_chan_vld_23_17;
    wire [23:0] dep_chan_data_23_17;
    wire token_23_17;
    wire [0:0] proc_18_data_FIFO_blk;
    wire [0:0] proc_18_data_PIPO_blk;
    wire [0:0] proc_18_start_FIFO_blk;
    wire [0:0] proc_18_TLF_FIFO_blk;
    wire [0:0] proc_18_input_sync_blk;
    wire [0:0] proc_18_output_sync_blk;
    wire [0:0] proc_dep_vld_vec_18;
    reg [0:0] proc_dep_vld_vec_18_reg;
    wire [0:0] in_chan_dep_vld_vec_18;
    wire [23:0] in_chan_dep_data_vec_18;
    wire [0:0] token_in_vec_18;
    wire [0:0] out_chan_dep_vld_vec_18;
    wire [23:0] out_chan_dep_data_18;
    wire [0:0] token_out_vec_18;
    wire dl_detect_out_18;
    wire dep_chan_vld_19_18;
    wire [23:0] dep_chan_data_19_18;
    wire token_19_18;
    wire [1:0] proc_19_data_FIFO_blk;
    wire [1:0] proc_19_data_PIPO_blk;
    wire [1:0] proc_19_start_FIFO_blk;
    wire [1:0] proc_19_TLF_FIFO_blk;
    wire [1:0] proc_19_input_sync_blk;
    wire [1:0] proc_19_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_19;
    reg [1:0] proc_dep_vld_vec_19_reg;
    wire [0:0] in_chan_dep_vld_vec_19;
    wire [23:0] in_chan_dep_data_vec_19;
    wire [0:0] token_in_vec_19;
    wire [1:0] out_chan_dep_vld_vec_19;
    wire [23:0] out_chan_dep_data_19;
    wire [1:0] token_out_vec_19;
    wire dl_detect_out_19;
    wire dep_chan_vld_20_19;
    wire [23:0] dep_chan_data_20_19;
    wire token_20_19;
    wire [1:0] proc_20_data_FIFO_blk;
    wire [1:0] proc_20_data_PIPO_blk;
    wire [1:0] proc_20_start_FIFO_blk;
    wire [1:0] proc_20_TLF_FIFO_blk;
    wire [1:0] proc_20_input_sync_blk;
    wire [1:0] proc_20_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_20;
    reg [1:0] proc_dep_vld_vec_20_reg;
    wire [0:0] in_chan_dep_vld_vec_20;
    wire [23:0] in_chan_dep_data_vec_20;
    wire [0:0] token_in_vec_20;
    wire [1:0] out_chan_dep_vld_vec_20;
    wire [23:0] out_chan_dep_data_20;
    wire [1:0] token_out_vec_20;
    wire dl_detect_out_20;
    wire dep_chan_vld_21_20;
    wire [23:0] dep_chan_data_21_20;
    wire token_21_20;
    wire [1:0] proc_21_data_FIFO_blk;
    wire [1:0] proc_21_data_PIPO_blk;
    wire [1:0] proc_21_start_FIFO_blk;
    wire [1:0] proc_21_TLF_FIFO_blk;
    wire [1:0] proc_21_input_sync_blk;
    wire [1:0] proc_21_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_21;
    reg [1:0] proc_dep_vld_vec_21_reg;
    wire [0:0] in_chan_dep_vld_vec_21;
    wire [23:0] in_chan_dep_data_vec_21;
    wire [0:0] token_in_vec_21;
    wire [1:0] out_chan_dep_vld_vec_21;
    wire [23:0] out_chan_dep_data_21;
    wire [1:0] token_out_vec_21;
    wire dl_detect_out_21;
    wire dep_chan_vld_22_21;
    wire [23:0] dep_chan_data_22_21;
    wire token_22_21;
    wire [1:0] proc_22_data_FIFO_blk;
    wire [1:0] proc_22_data_PIPO_blk;
    wire [1:0] proc_22_start_FIFO_blk;
    wire [1:0] proc_22_TLF_FIFO_blk;
    wire [1:0] proc_22_input_sync_blk;
    wire [1:0] proc_22_output_sync_blk;
    wire [1:0] proc_dep_vld_vec_22;
    reg [1:0] proc_dep_vld_vec_22_reg;
    wire [0:0] in_chan_dep_vld_vec_22;
    wire [23:0] in_chan_dep_data_vec_22;
    wire [0:0] token_in_vec_22;
    wire [1:0] out_chan_dep_vld_vec_22;
    wire [23:0] out_chan_dep_data_22;
    wire [1:0] token_out_vec_22;
    wire dl_detect_out_22;
    wire dep_chan_vld_23_22;
    wire [23:0] dep_chan_data_23_22;
    wire token_23_22;
    wire [2:0] proc_23_data_FIFO_blk;
    wire [2:0] proc_23_data_PIPO_blk;
    wire [2:0] proc_23_start_FIFO_blk;
    wire [2:0] proc_23_TLF_FIFO_blk;
    wire [2:0] proc_23_input_sync_blk;
    wire [2:0] proc_23_output_sync_blk;
    wire [2:0] proc_dep_vld_vec_23;
    reg [2:0] proc_dep_vld_vec_23_reg;
    wire [0:0] in_chan_dep_vld_vec_23;
    wire [23:0] in_chan_dep_data_vec_23;
    wire [0:0] token_in_vec_23;
    wire [2:0] out_chan_dep_vld_vec_23;
    wire [23:0] out_chan_dep_data_23;
    wire [2:0] token_out_vec_23;
    wire dl_detect_out_23;
    wire dep_chan_vld_11_23;
    wire [23:0] dep_chan_data_11_23;
    wire token_11_23;
    wire [23:0] dl_in_vec;
    wire dl_detect_out;
    wire token_clear;
    reg [23:0] origin;

    reg ap_done_reg_0;// for module Block_entry1421_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_0 <= 'b0;
        end
        else begin
            ap_done_reg_0 <= Block_entry1421_proc_U0.ap_done & ~Block_entry1421_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_1;// for module Block_entry1422_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_1 <= 'b0;
        end
        else begin
            ap_done_reg_1 <= Block_entry1422_proc_U0.ap_done & ~Block_entry1422_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_2;// for module Block_entry1423_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_2 <= 'b0;
        end
        else begin
            ap_done_reg_2 <= Block_entry1423_proc_U0.ap_done & ~Block_entry1423_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_3;// for module Block_entry1424_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_3 <= 'b0;
        end
        else begin
            ap_done_reg_3 <= Block_entry1424_proc_U0.ap_done & ~Block_entry1424_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_4;// for module Block_entry1425_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_4 <= 'b0;
        end
        else begin
            ap_done_reg_4 <= Block_entry1425_proc_U0.ap_done & ~Block_entry1425_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_5;// for module Block_entry1426_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_5 <= 'b0;
        end
        else begin
            ap_done_reg_5 <= Block_entry1426_proc_U0.ap_done & ~Block_entry1426_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_6;// for module Block_entry1434_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_6 <= 'b0;
        end
        else begin
            ap_done_reg_6 <= Block_entry1434_proc_U0.ap_done & ~Block_entry1434_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_7;// for module Block_entry1435_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_7 <= 'b0;
        end
        else begin
            ap_done_reg_7 <= Block_entry1435_proc_U0.ap_done & ~Block_entry1435_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_8;// for module Block_entry1436_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_8 <= 'b0;
        end
        else begin
            ap_done_reg_8 <= Block_entry1436_proc_U0.ap_done & ~Block_entry1436_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_9;// for module Block_entry1437_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_9 <= 'b0;
        end
        else begin
            ap_done_reg_9 <= Block_entry1437_proc_U0.ap_done & ~Block_entry1437_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_10;// for module Block_entry1438_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_10 <= 'b0;
        end
        else begin
            ap_done_reg_10 <= Block_entry1438_proc_U0.ap_done & ~Block_entry1438_proc_U0.ap_continue;
        end
    end

    reg ap_done_reg_11;// for module Block_entry1439_proc_U0
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            ap_done_reg_11 <= 'b0;
        end
        else begin
            ap_done_reg_11 <= Block_entry1439_proc_U0.ap_done & ~Block_entry1439_proc_U0.ap_continue;
        end
    end

    // Process: multiply_1_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 0, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_0 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_0),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_0),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_0),
        .token_in_vec(token_in_vec_0),
        .dl_detect_in(dl_detect_out),
        .origin(origin[0]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_0),
        .out_chan_dep_data(out_chan_dep_data_0),
        .token_out_vec(token_out_vec_0),
        .dl_detect_out(dl_in_vec[0]));

    assign proc_0_data_FIFO_blk[0] = 1'b0;
    assign proc_0_data_PIPO_blk[0] = 1'b0;
    assign proc_0_start_FIFO_blk[0] = 1'b0;
    assign proc_0_TLF_FIFO_blk[0] = 1'b0;
    assign proc_0_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_0_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_0[0] = dl_detect_out ? proc_dep_vld_vec_0_reg[0] : (proc_0_data_FIFO_blk[0] | proc_0_data_PIPO_blk[0] | proc_0_start_FIFO_blk[0] | proc_0_TLF_FIFO_blk[0] | proc_0_input_sync_blk[0] | proc_0_output_sync_blk[0]);
    assign proc_0_data_FIFO_blk[1] = 1'b0;
    assign proc_0_data_PIPO_blk[1] = 1'b0;
    assign proc_0_start_FIFO_blk[1] = 1'b0;
    assign proc_0_TLF_FIFO_blk[1] = 1'b0;
    assign proc_0_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_0_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_0[1] = dl_detect_out ? proc_dep_vld_vec_0_reg[1] : (proc_0_data_FIFO_blk[1] | proc_0_data_PIPO_blk[1] | proc_0_start_FIFO_blk[1] | proc_0_TLF_FIFO_blk[1] | proc_0_input_sync_blk[1] | proc_0_output_sync_blk[1]);
    assign proc_0_data_FIFO_blk[2] = 1'b0;
    assign proc_0_data_PIPO_blk[2] = 1'b0;
    assign proc_0_start_FIFO_blk[2] = 1'b0;
    assign proc_0_TLF_FIFO_blk[2] = 1'b0;
    assign proc_0_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_0_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_0[2] = dl_detect_out ? proc_dep_vld_vec_0_reg[2] : (proc_0_data_FIFO_blk[2] | proc_0_data_PIPO_blk[2] | proc_0_start_FIFO_blk[2] | proc_0_TLF_FIFO_blk[2] | proc_0_input_sync_blk[2] | proc_0_output_sync_blk[2]);
    assign proc_0_data_FIFO_blk[3] = 1'b0;
    assign proc_0_data_PIPO_blk[3] = 1'b0;
    assign proc_0_start_FIFO_blk[3] = 1'b0;
    assign proc_0_TLF_FIFO_blk[3] = 1'b0;
    assign proc_0_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_0_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_0[3] = dl_detect_out ? proc_dep_vld_vec_0_reg[3] : (proc_0_data_FIFO_blk[3] | proc_0_data_PIPO_blk[3] | proc_0_start_FIFO_blk[3] | proc_0_TLF_FIFO_blk[3] | proc_0_input_sync_blk[3] | proc_0_output_sync_blk[3]);
    assign proc_0_data_FIFO_blk[4] = 1'b0;
    assign proc_0_data_PIPO_blk[4] = 1'b0;
    assign proc_0_start_FIFO_blk[4] = 1'b0;
    assign proc_0_TLF_FIFO_blk[4] = 1'b0;
    assign proc_0_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_0_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_0[4] = dl_detect_out ? proc_dep_vld_vec_0_reg[4] : (proc_0_data_FIFO_blk[4] | proc_0_data_PIPO_blk[4] | proc_0_start_FIFO_blk[4] | proc_0_TLF_FIFO_blk[4] | proc_0_input_sync_blk[4] | proc_0_output_sync_blk[4]);
    assign proc_0_data_FIFO_blk[5] = 1'b0;
    assign proc_0_data_PIPO_blk[5] = 1'b0;
    assign proc_0_start_FIFO_blk[5] = 1'b0;
    assign proc_0_TLF_FIFO_blk[5] = 1'b0;
    assign proc_0_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_0_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_0[5] = dl_detect_out ? proc_dep_vld_vec_0_reg[5] : (proc_0_data_FIFO_blk[5] | proc_0_data_PIPO_blk[5] | proc_0_start_FIFO_blk[5] | proc_0_TLF_FIFO_blk[5] | proc_0_input_sync_blk[5] | proc_0_output_sync_blk[5]);
    assign proc_0_data_FIFO_blk[6] = 1'b0;
    assign proc_0_data_PIPO_blk[6] = 1'b0;
    assign proc_0_start_FIFO_blk[6] = 1'b0;
    assign proc_0_TLF_FIFO_blk[6] = 1'b0;
    assign proc_0_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_0_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_0[6] = dl_detect_out ? proc_dep_vld_vec_0_reg[6] : (proc_0_data_FIFO_blk[6] | proc_0_data_PIPO_blk[6] | proc_0_start_FIFO_blk[6] | proc_0_TLF_FIFO_blk[6] | proc_0_input_sync_blk[6] | proc_0_output_sync_blk[6]);
    assign proc_0_data_FIFO_blk[7] = 1'b0;
    assign proc_0_data_PIPO_blk[7] = 1'b0;
    assign proc_0_start_FIFO_blk[7] = 1'b0;
    assign proc_0_TLF_FIFO_blk[7] = 1'b0;
    assign proc_0_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_0_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_0[7] = dl_detect_out ? proc_dep_vld_vec_0_reg[7] : (proc_0_data_FIFO_blk[7] | proc_0_data_PIPO_blk[7] | proc_0_start_FIFO_blk[7] | proc_0_TLF_FIFO_blk[7] | proc_0_input_sync_blk[7] | proc_0_output_sync_blk[7]);
    assign proc_0_data_FIFO_blk[8] = 1'b0;
    assign proc_0_data_PIPO_blk[8] = 1'b0;
    assign proc_0_start_FIFO_blk[8] = 1'b0;
    assign proc_0_TLF_FIFO_blk[8] = 1'b0;
    assign proc_0_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_0_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_0[8] = dl_detect_out ? proc_dep_vld_vec_0_reg[8] : (proc_0_data_FIFO_blk[8] | proc_0_data_PIPO_blk[8] | proc_0_start_FIFO_blk[8] | proc_0_TLF_FIFO_blk[8] | proc_0_input_sync_blk[8] | proc_0_output_sync_blk[8]);
    assign proc_0_data_FIFO_blk[9] = 1'b0;
    assign proc_0_data_PIPO_blk[9] = 1'b0;
    assign proc_0_start_FIFO_blk[9] = 1'b0;
    assign proc_0_TLF_FIFO_blk[9] = 1'b0;
    assign proc_0_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_0_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_0[9] = dl_detect_out ? proc_dep_vld_vec_0_reg[9] : (proc_0_data_FIFO_blk[9] | proc_0_data_PIPO_blk[9] | proc_0_start_FIFO_blk[9] | proc_0_TLF_FIFO_blk[9] | proc_0_input_sync_blk[9] | proc_0_output_sync_blk[9]);
    assign proc_0_data_FIFO_blk[10] = 1'b0;
    assign proc_0_data_PIPO_blk[10] = 1'b0;
    assign proc_0_start_FIFO_blk[10] = 1'b0;
    assign proc_0_TLF_FIFO_blk[10] = 1'b0;
    assign proc_0_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_1_U0_ap_ready & multiply_1_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_0_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_0[10] = dl_detect_out ? proc_dep_vld_vec_0_reg[10] : (proc_0_data_FIFO_blk[10] | proc_0_data_PIPO_blk[10] | proc_0_start_FIFO_blk[10] | proc_0_TLF_FIFO_blk[10] | proc_0_input_sync_blk[10] | proc_0_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_0_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_0_reg <= proc_dep_vld_vec_0;
        end
    end
    assign in_chan_dep_vld_vec_0[0] = dep_chan_vld_1_0;
    assign in_chan_dep_data_vec_0[23 : 0] = dep_chan_data_1_0;
    assign token_in_vec_0[0] = token_1_0;
    assign in_chan_dep_vld_vec_0[1] = dep_chan_vld_2_0;
    assign in_chan_dep_data_vec_0[47 : 24] = dep_chan_data_2_0;
    assign token_in_vec_0[1] = token_2_0;
    assign in_chan_dep_vld_vec_0[2] = dep_chan_vld_3_0;
    assign in_chan_dep_data_vec_0[71 : 48] = dep_chan_data_3_0;
    assign token_in_vec_0[2] = token_3_0;
    assign in_chan_dep_vld_vec_0[3] = dep_chan_vld_4_0;
    assign in_chan_dep_data_vec_0[95 : 72] = dep_chan_data_4_0;
    assign token_in_vec_0[3] = token_4_0;
    assign in_chan_dep_vld_vec_0[4] = dep_chan_vld_5_0;
    assign in_chan_dep_data_vec_0[119 : 96] = dep_chan_data_5_0;
    assign token_in_vec_0[4] = token_5_0;
    assign in_chan_dep_vld_vec_0[5] = dep_chan_vld_6_0;
    assign in_chan_dep_data_vec_0[143 : 120] = dep_chan_data_6_0;
    assign token_in_vec_0[5] = token_6_0;
    assign in_chan_dep_vld_vec_0[6] = dep_chan_vld_12_0;
    assign in_chan_dep_data_vec_0[167 : 144] = dep_chan_data_12_0;
    assign token_in_vec_0[6] = token_12_0;
    assign in_chan_dep_vld_vec_0[7] = dep_chan_vld_13_0;
    assign in_chan_dep_data_vec_0[191 : 168] = dep_chan_data_13_0;
    assign token_in_vec_0[7] = token_13_0;
    assign in_chan_dep_vld_vec_0[8] = dep_chan_vld_14_0;
    assign in_chan_dep_data_vec_0[215 : 192] = dep_chan_data_14_0;
    assign token_in_vec_0[8] = token_14_0;
    assign in_chan_dep_vld_vec_0[9] = dep_chan_vld_15_0;
    assign in_chan_dep_data_vec_0[239 : 216] = dep_chan_data_15_0;
    assign token_in_vec_0[9] = token_15_0;
    assign in_chan_dep_vld_vec_0[10] = dep_chan_vld_16_0;
    assign in_chan_dep_data_vec_0[263 : 240] = dep_chan_data_16_0;
    assign token_in_vec_0[10] = token_16_0;
    assign in_chan_dep_vld_vec_0[11] = dep_chan_vld_17_0;
    assign in_chan_dep_data_vec_0[287 : 264] = dep_chan_data_17_0;
    assign token_in_vec_0[11] = token_17_0;
    assign dep_chan_vld_0_1 = out_chan_dep_vld_vec_0[0];
    assign dep_chan_data_0_1 = out_chan_dep_data_0;
    assign token_0_1 = token_out_vec_0[0];
    assign dep_chan_vld_0_2 = out_chan_dep_vld_vec_0[1];
    assign dep_chan_data_0_2 = out_chan_dep_data_0;
    assign token_0_2 = token_out_vec_0[1];
    assign dep_chan_vld_0_3 = out_chan_dep_vld_vec_0[2];
    assign dep_chan_data_0_3 = out_chan_dep_data_0;
    assign token_0_3 = token_out_vec_0[2];
    assign dep_chan_vld_0_4 = out_chan_dep_vld_vec_0[3];
    assign dep_chan_data_0_4 = out_chan_dep_data_0;
    assign token_0_4 = token_out_vec_0[3];
    assign dep_chan_vld_0_5 = out_chan_dep_vld_vec_0[4];
    assign dep_chan_data_0_5 = out_chan_dep_data_0;
    assign token_0_5 = token_out_vec_0[4];
    assign dep_chan_vld_0_12 = out_chan_dep_vld_vec_0[5];
    assign dep_chan_data_0_12 = out_chan_dep_data_0;
    assign token_0_12 = token_out_vec_0[5];
    assign dep_chan_vld_0_13 = out_chan_dep_vld_vec_0[6];
    assign dep_chan_data_0_13 = out_chan_dep_data_0;
    assign token_0_13 = token_out_vec_0[6];
    assign dep_chan_vld_0_14 = out_chan_dep_vld_vec_0[7];
    assign dep_chan_data_0_14 = out_chan_dep_data_0;
    assign token_0_14 = token_out_vec_0[7];
    assign dep_chan_vld_0_15 = out_chan_dep_vld_vec_0[8];
    assign dep_chan_data_0_15 = out_chan_dep_data_0;
    assign token_0_15 = token_out_vec_0[8];
    assign dep_chan_vld_0_16 = out_chan_dep_vld_vec_0[9];
    assign dep_chan_data_0_16 = out_chan_dep_data_0;
    assign token_0_16 = token_out_vec_0[9];
    assign dep_chan_vld_0_17 = out_chan_dep_vld_vec_0[10];
    assign dep_chan_data_0_17 = out_chan_dep_data_0;
    assign token_0_17 = token_out_vec_0[10];

    // Process: multiply_224_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 1, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_1 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_1),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_1),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_1),
        .token_in_vec(token_in_vec_1),
        .dl_detect_in(dl_detect_out),
        .origin(origin[1]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_1),
        .out_chan_dep_data(out_chan_dep_data_1),
        .token_out_vec(token_out_vec_1),
        .dl_detect_out(dl_in_vec[1]));

    assign proc_1_data_FIFO_blk[0] = 1'b0;
    assign proc_1_data_PIPO_blk[0] = 1'b0;
    assign proc_1_start_FIFO_blk[0] = 1'b0;
    assign proc_1_TLF_FIFO_blk[0] = 1'b0;
    assign proc_1_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_1_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_1[0] = dl_detect_out ? proc_dep_vld_vec_1_reg[0] : (proc_1_data_FIFO_blk[0] | proc_1_data_PIPO_blk[0] | proc_1_start_FIFO_blk[0] | proc_1_TLF_FIFO_blk[0] | proc_1_input_sync_blk[0] | proc_1_output_sync_blk[0]);
    assign proc_1_data_FIFO_blk[1] = 1'b0;
    assign proc_1_data_PIPO_blk[1] = 1'b0;
    assign proc_1_start_FIFO_blk[1] = 1'b0;
    assign proc_1_TLF_FIFO_blk[1] = 1'b0;
    assign proc_1_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_1_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_1[1] = dl_detect_out ? proc_dep_vld_vec_1_reg[1] : (proc_1_data_FIFO_blk[1] | proc_1_data_PIPO_blk[1] | proc_1_start_FIFO_blk[1] | proc_1_TLF_FIFO_blk[1] | proc_1_input_sync_blk[1] | proc_1_output_sync_blk[1]);
    assign proc_1_data_FIFO_blk[2] = 1'b0;
    assign proc_1_data_PIPO_blk[2] = 1'b0;
    assign proc_1_start_FIFO_blk[2] = 1'b0;
    assign proc_1_TLF_FIFO_blk[2] = 1'b0;
    assign proc_1_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_1_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_1[2] = dl_detect_out ? proc_dep_vld_vec_1_reg[2] : (proc_1_data_FIFO_blk[2] | proc_1_data_PIPO_blk[2] | proc_1_start_FIFO_blk[2] | proc_1_TLF_FIFO_blk[2] | proc_1_input_sync_blk[2] | proc_1_output_sync_blk[2]);
    assign proc_1_data_FIFO_blk[3] = 1'b0;
    assign proc_1_data_PIPO_blk[3] = 1'b0;
    assign proc_1_start_FIFO_blk[3] = 1'b0;
    assign proc_1_TLF_FIFO_blk[3] = 1'b0;
    assign proc_1_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_1_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_1[3] = dl_detect_out ? proc_dep_vld_vec_1_reg[3] : (proc_1_data_FIFO_blk[3] | proc_1_data_PIPO_blk[3] | proc_1_start_FIFO_blk[3] | proc_1_TLF_FIFO_blk[3] | proc_1_input_sync_blk[3] | proc_1_output_sync_blk[3]);
    assign proc_1_data_FIFO_blk[4] = 1'b0;
    assign proc_1_data_PIPO_blk[4] = 1'b0;
    assign proc_1_start_FIFO_blk[4] = 1'b0;
    assign proc_1_TLF_FIFO_blk[4] = 1'b0;
    assign proc_1_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_1_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_1[4] = dl_detect_out ? proc_dep_vld_vec_1_reg[4] : (proc_1_data_FIFO_blk[4] | proc_1_data_PIPO_blk[4] | proc_1_start_FIFO_blk[4] | proc_1_TLF_FIFO_blk[4] | proc_1_input_sync_blk[4] | proc_1_output_sync_blk[4]);
    assign proc_1_data_FIFO_blk[5] = 1'b0;
    assign proc_1_data_PIPO_blk[5] = 1'b0;
    assign proc_1_start_FIFO_blk[5] = 1'b0;
    assign proc_1_TLF_FIFO_blk[5] = 1'b0;
    assign proc_1_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_1_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_1[5] = dl_detect_out ? proc_dep_vld_vec_1_reg[5] : (proc_1_data_FIFO_blk[5] | proc_1_data_PIPO_blk[5] | proc_1_start_FIFO_blk[5] | proc_1_TLF_FIFO_blk[5] | proc_1_input_sync_blk[5] | proc_1_output_sync_blk[5]);
    assign proc_1_data_FIFO_blk[6] = 1'b0;
    assign proc_1_data_PIPO_blk[6] = 1'b0;
    assign proc_1_start_FIFO_blk[6] = 1'b0;
    assign proc_1_TLF_FIFO_blk[6] = 1'b0;
    assign proc_1_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_1_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_1[6] = dl_detect_out ? proc_dep_vld_vec_1_reg[6] : (proc_1_data_FIFO_blk[6] | proc_1_data_PIPO_blk[6] | proc_1_start_FIFO_blk[6] | proc_1_TLF_FIFO_blk[6] | proc_1_input_sync_blk[6] | proc_1_output_sync_blk[6]);
    assign proc_1_data_FIFO_blk[7] = 1'b0;
    assign proc_1_data_PIPO_blk[7] = 1'b0;
    assign proc_1_start_FIFO_blk[7] = 1'b0;
    assign proc_1_TLF_FIFO_blk[7] = 1'b0;
    assign proc_1_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_1_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_1[7] = dl_detect_out ? proc_dep_vld_vec_1_reg[7] : (proc_1_data_FIFO_blk[7] | proc_1_data_PIPO_blk[7] | proc_1_start_FIFO_blk[7] | proc_1_TLF_FIFO_blk[7] | proc_1_input_sync_blk[7] | proc_1_output_sync_blk[7]);
    assign proc_1_data_FIFO_blk[8] = 1'b0;
    assign proc_1_data_PIPO_blk[8] = 1'b0;
    assign proc_1_start_FIFO_blk[8] = 1'b0;
    assign proc_1_TLF_FIFO_blk[8] = 1'b0;
    assign proc_1_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_1_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_1[8] = dl_detect_out ? proc_dep_vld_vec_1_reg[8] : (proc_1_data_FIFO_blk[8] | proc_1_data_PIPO_blk[8] | proc_1_start_FIFO_blk[8] | proc_1_TLF_FIFO_blk[8] | proc_1_input_sync_blk[8] | proc_1_output_sync_blk[8]);
    assign proc_1_data_FIFO_blk[9] = 1'b0;
    assign proc_1_data_PIPO_blk[9] = 1'b0;
    assign proc_1_start_FIFO_blk[9] = 1'b0;
    assign proc_1_TLF_FIFO_blk[9] = 1'b0;
    assign proc_1_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_1_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_1[9] = dl_detect_out ? proc_dep_vld_vec_1_reg[9] : (proc_1_data_FIFO_blk[9] | proc_1_data_PIPO_blk[9] | proc_1_start_FIFO_blk[9] | proc_1_TLF_FIFO_blk[9] | proc_1_input_sync_blk[9] | proc_1_output_sync_blk[9]);
    assign proc_1_data_FIFO_blk[10] = 1'b0;
    assign proc_1_data_PIPO_blk[10] = 1'b0;
    assign proc_1_start_FIFO_blk[10] = 1'b0;
    assign proc_1_TLF_FIFO_blk[10] = 1'b0;
    assign proc_1_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_224_U0_ap_ready & multiply_224_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_1_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_1[10] = dl_detect_out ? proc_dep_vld_vec_1_reg[10] : (proc_1_data_FIFO_blk[10] | proc_1_data_PIPO_blk[10] | proc_1_start_FIFO_blk[10] | proc_1_TLF_FIFO_blk[10] | proc_1_input_sync_blk[10] | proc_1_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_1_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_1_reg <= proc_dep_vld_vec_1;
        end
    end
    assign in_chan_dep_vld_vec_1[0] = dep_chan_vld_0_1;
    assign in_chan_dep_data_vec_1[23 : 0] = dep_chan_data_0_1;
    assign token_in_vec_1[0] = token_0_1;
    assign in_chan_dep_vld_vec_1[1] = dep_chan_vld_2_1;
    assign in_chan_dep_data_vec_1[47 : 24] = dep_chan_data_2_1;
    assign token_in_vec_1[1] = token_2_1;
    assign in_chan_dep_vld_vec_1[2] = dep_chan_vld_3_1;
    assign in_chan_dep_data_vec_1[71 : 48] = dep_chan_data_3_1;
    assign token_in_vec_1[2] = token_3_1;
    assign in_chan_dep_vld_vec_1[3] = dep_chan_vld_4_1;
    assign in_chan_dep_data_vec_1[95 : 72] = dep_chan_data_4_1;
    assign token_in_vec_1[3] = token_4_1;
    assign in_chan_dep_vld_vec_1[4] = dep_chan_vld_5_1;
    assign in_chan_dep_data_vec_1[119 : 96] = dep_chan_data_5_1;
    assign token_in_vec_1[4] = token_5_1;
    assign in_chan_dep_vld_vec_1[5] = dep_chan_vld_7_1;
    assign in_chan_dep_data_vec_1[143 : 120] = dep_chan_data_7_1;
    assign token_in_vec_1[5] = token_7_1;
    assign in_chan_dep_vld_vec_1[6] = dep_chan_vld_12_1;
    assign in_chan_dep_data_vec_1[167 : 144] = dep_chan_data_12_1;
    assign token_in_vec_1[6] = token_12_1;
    assign in_chan_dep_vld_vec_1[7] = dep_chan_vld_13_1;
    assign in_chan_dep_data_vec_1[191 : 168] = dep_chan_data_13_1;
    assign token_in_vec_1[7] = token_13_1;
    assign in_chan_dep_vld_vec_1[8] = dep_chan_vld_14_1;
    assign in_chan_dep_data_vec_1[215 : 192] = dep_chan_data_14_1;
    assign token_in_vec_1[8] = token_14_1;
    assign in_chan_dep_vld_vec_1[9] = dep_chan_vld_15_1;
    assign in_chan_dep_data_vec_1[239 : 216] = dep_chan_data_15_1;
    assign token_in_vec_1[9] = token_15_1;
    assign in_chan_dep_vld_vec_1[10] = dep_chan_vld_16_1;
    assign in_chan_dep_data_vec_1[263 : 240] = dep_chan_data_16_1;
    assign token_in_vec_1[10] = token_16_1;
    assign in_chan_dep_vld_vec_1[11] = dep_chan_vld_17_1;
    assign in_chan_dep_data_vec_1[287 : 264] = dep_chan_data_17_1;
    assign token_in_vec_1[11] = token_17_1;
    assign dep_chan_vld_1_0 = out_chan_dep_vld_vec_1[0];
    assign dep_chan_data_1_0 = out_chan_dep_data_1;
    assign token_1_0 = token_out_vec_1[0];
    assign dep_chan_vld_1_2 = out_chan_dep_vld_vec_1[1];
    assign dep_chan_data_1_2 = out_chan_dep_data_1;
    assign token_1_2 = token_out_vec_1[1];
    assign dep_chan_vld_1_3 = out_chan_dep_vld_vec_1[2];
    assign dep_chan_data_1_3 = out_chan_dep_data_1;
    assign token_1_3 = token_out_vec_1[2];
    assign dep_chan_vld_1_4 = out_chan_dep_vld_vec_1[3];
    assign dep_chan_data_1_4 = out_chan_dep_data_1;
    assign token_1_4 = token_out_vec_1[3];
    assign dep_chan_vld_1_5 = out_chan_dep_vld_vec_1[4];
    assign dep_chan_data_1_5 = out_chan_dep_data_1;
    assign token_1_5 = token_out_vec_1[4];
    assign dep_chan_vld_1_12 = out_chan_dep_vld_vec_1[5];
    assign dep_chan_data_1_12 = out_chan_dep_data_1;
    assign token_1_12 = token_out_vec_1[5];
    assign dep_chan_vld_1_13 = out_chan_dep_vld_vec_1[6];
    assign dep_chan_data_1_13 = out_chan_dep_data_1;
    assign token_1_13 = token_out_vec_1[6];
    assign dep_chan_vld_1_14 = out_chan_dep_vld_vec_1[7];
    assign dep_chan_data_1_14 = out_chan_dep_data_1;
    assign token_1_14 = token_out_vec_1[7];
    assign dep_chan_vld_1_15 = out_chan_dep_vld_vec_1[8];
    assign dep_chan_data_1_15 = out_chan_dep_data_1;
    assign token_1_15 = token_out_vec_1[8];
    assign dep_chan_vld_1_16 = out_chan_dep_vld_vec_1[9];
    assign dep_chan_data_1_16 = out_chan_dep_data_1;
    assign token_1_16 = token_out_vec_1[9];
    assign dep_chan_vld_1_17 = out_chan_dep_vld_vec_1[10];
    assign dep_chan_data_1_17 = out_chan_dep_data_1;
    assign token_1_17 = token_out_vec_1[10];

    // Process: multiply_325_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 2, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_2 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_2),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_2),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_2),
        .token_in_vec(token_in_vec_2),
        .dl_detect_in(dl_detect_out),
        .origin(origin[2]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_2),
        .out_chan_dep_data(out_chan_dep_data_2),
        .token_out_vec(token_out_vec_2),
        .dl_detect_out(dl_in_vec[2]));

    assign proc_2_data_FIFO_blk[0] = 1'b0;
    assign proc_2_data_PIPO_blk[0] = 1'b0;
    assign proc_2_start_FIFO_blk[0] = 1'b0;
    assign proc_2_TLF_FIFO_blk[0] = 1'b0;
    assign proc_2_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_2_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_2[0] = dl_detect_out ? proc_dep_vld_vec_2_reg[0] : (proc_2_data_FIFO_blk[0] | proc_2_data_PIPO_blk[0] | proc_2_start_FIFO_blk[0] | proc_2_TLF_FIFO_blk[0] | proc_2_input_sync_blk[0] | proc_2_output_sync_blk[0]);
    assign proc_2_data_FIFO_blk[1] = 1'b0;
    assign proc_2_data_PIPO_blk[1] = 1'b0;
    assign proc_2_start_FIFO_blk[1] = 1'b0;
    assign proc_2_TLF_FIFO_blk[1] = 1'b0;
    assign proc_2_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_2_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_2[1] = dl_detect_out ? proc_dep_vld_vec_2_reg[1] : (proc_2_data_FIFO_blk[1] | proc_2_data_PIPO_blk[1] | proc_2_start_FIFO_blk[1] | proc_2_TLF_FIFO_blk[1] | proc_2_input_sync_blk[1] | proc_2_output_sync_blk[1]);
    assign proc_2_data_FIFO_blk[2] = 1'b0;
    assign proc_2_data_PIPO_blk[2] = 1'b0;
    assign proc_2_start_FIFO_blk[2] = 1'b0;
    assign proc_2_TLF_FIFO_blk[2] = 1'b0;
    assign proc_2_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_2_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_2[2] = dl_detect_out ? proc_dep_vld_vec_2_reg[2] : (proc_2_data_FIFO_blk[2] | proc_2_data_PIPO_blk[2] | proc_2_start_FIFO_blk[2] | proc_2_TLF_FIFO_blk[2] | proc_2_input_sync_blk[2] | proc_2_output_sync_blk[2]);
    assign proc_2_data_FIFO_blk[3] = 1'b0;
    assign proc_2_data_PIPO_blk[3] = 1'b0;
    assign proc_2_start_FIFO_blk[3] = 1'b0;
    assign proc_2_TLF_FIFO_blk[3] = 1'b0;
    assign proc_2_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_2_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_2[3] = dl_detect_out ? proc_dep_vld_vec_2_reg[3] : (proc_2_data_FIFO_blk[3] | proc_2_data_PIPO_blk[3] | proc_2_start_FIFO_blk[3] | proc_2_TLF_FIFO_blk[3] | proc_2_input_sync_blk[3] | proc_2_output_sync_blk[3]);
    assign proc_2_data_FIFO_blk[4] = 1'b0;
    assign proc_2_data_PIPO_blk[4] = 1'b0;
    assign proc_2_start_FIFO_blk[4] = 1'b0;
    assign proc_2_TLF_FIFO_blk[4] = 1'b0;
    assign proc_2_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_2_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_2[4] = dl_detect_out ? proc_dep_vld_vec_2_reg[4] : (proc_2_data_FIFO_blk[4] | proc_2_data_PIPO_blk[4] | proc_2_start_FIFO_blk[4] | proc_2_TLF_FIFO_blk[4] | proc_2_input_sync_blk[4] | proc_2_output_sync_blk[4]);
    assign proc_2_data_FIFO_blk[5] = 1'b0;
    assign proc_2_data_PIPO_blk[5] = 1'b0;
    assign proc_2_start_FIFO_blk[5] = 1'b0;
    assign proc_2_TLF_FIFO_blk[5] = 1'b0;
    assign proc_2_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_2_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_2[5] = dl_detect_out ? proc_dep_vld_vec_2_reg[5] : (proc_2_data_FIFO_blk[5] | proc_2_data_PIPO_blk[5] | proc_2_start_FIFO_blk[5] | proc_2_TLF_FIFO_blk[5] | proc_2_input_sync_blk[5] | proc_2_output_sync_blk[5]);
    assign proc_2_data_FIFO_blk[6] = 1'b0;
    assign proc_2_data_PIPO_blk[6] = 1'b0;
    assign proc_2_start_FIFO_blk[6] = 1'b0;
    assign proc_2_TLF_FIFO_blk[6] = 1'b0;
    assign proc_2_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_2_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_2[6] = dl_detect_out ? proc_dep_vld_vec_2_reg[6] : (proc_2_data_FIFO_blk[6] | proc_2_data_PIPO_blk[6] | proc_2_start_FIFO_blk[6] | proc_2_TLF_FIFO_blk[6] | proc_2_input_sync_blk[6] | proc_2_output_sync_blk[6]);
    assign proc_2_data_FIFO_blk[7] = 1'b0;
    assign proc_2_data_PIPO_blk[7] = 1'b0;
    assign proc_2_start_FIFO_blk[7] = 1'b0;
    assign proc_2_TLF_FIFO_blk[7] = 1'b0;
    assign proc_2_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_2_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_2[7] = dl_detect_out ? proc_dep_vld_vec_2_reg[7] : (proc_2_data_FIFO_blk[7] | proc_2_data_PIPO_blk[7] | proc_2_start_FIFO_blk[7] | proc_2_TLF_FIFO_blk[7] | proc_2_input_sync_blk[7] | proc_2_output_sync_blk[7]);
    assign proc_2_data_FIFO_blk[8] = 1'b0;
    assign proc_2_data_PIPO_blk[8] = 1'b0;
    assign proc_2_start_FIFO_blk[8] = 1'b0;
    assign proc_2_TLF_FIFO_blk[8] = 1'b0;
    assign proc_2_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_2_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_2[8] = dl_detect_out ? proc_dep_vld_vec_2_reg[8] : (proc_2_data_FIFO_blk[8] | proc_2_data_PIPO_blk[8] | proc_2_start_FIFO_blk[8] | proc_2_TLF_FIFO_blk[8] | proc_2_input_sync_blk[8] | proc_2_output_sync_blk[8]);
    assign proc_2_data_FIFO_blk[9] = 1'b0;
    assign proc_2_data_PIPO_blk[9] = 1'b0;
    assign proc_2_start_FIFO_blk[9] = 1'b0;
    assign proc_2_TLF_FIFO_blk[9] = 1'b0;
    assign proc_2_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_2_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_2[9] = dl_detect_out ? proc_dep_vld_vec_2_reg[9] : (proc_2_data_FIFO_blk[9] | proc_2_data_PIPO_blk[9] | proc_2_start_FIFO_blk[9] | proc_2_TLF_FIFO_blk[9] | proc_2_input_sync_blk[9] | proc_2_output_sync_blk[9]);
    assign proc_2_data_FIFO_blk[10] = 1'b0;
    assign proc_2_data_PIPO_blk[10] = 1'b0;
    assign proc_2_start_FIFO_blk[10] = 1'b0;
    assign proc_2_TLF_FIFO_blk[10] = 1'b0;
    assign proc_2_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_325_U0_ap_ready & multiply_325_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_2_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_2[10] = dl_detect_out ? proc_dep_vld_vec_2_reg[10] : (proc_2_data_FIFO_blk[10] | proc_2_data_PIPO_blk[10] | proc_2_start_FIFO_blk[10] | proc_2_TLF_FIFO_blk[10] | proc_2_input_sync_blk[10] | proc_2_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_2_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_2_reg <= proc_dep_vld_vec_2;
        end
    end
    assign in_chan_dep_vld_vec_2[0] = dep_chan_vld_0_2;
    assign in_chan_dep_data_vec_2[23 : 0] = dep_chan_data_0_2;
    assign token_in_vec_2[0] = token_0_2;
    assign in_chan_dep_vld_vec_2[1] = dep_chan_vld_1_2;
    assign in_chan_dep_data_vec_2[47 : 24] = dep_chan_data_1_2;
    assign token_in_vec_2[1] = token_1_2;
    assign in_chan_dep_vld_vec_2[2] = dep_chan_vld_3_2;
    assign in_chan_dep_data_vec_2[71 : 48] = dep_chan_data_3_2;
    assign token_in_vec_2[2] = token_3_2;
    assign in_chan_dep_vld_vec_2[3] = dep_chan_vld_4_2;
    assign in_chan_dep_data_vec_2[95 : 72] = dep_chan_data_4_2;
    assign token_in_vec_2[3] = token_4_2;
    assign in_chan_dep_vld_vec_2[4] = dep_chan_vld_5_2;
    assign in_chan_dep_data_vec_2[119 : 96] = dep_chan_data_5_2;
    assign token_in_vec_2[4] = token_5_2;
    assign in_chan_dep_vld_vec_2[5] = dep_chan_vld_8_2;
    assign in_chan_dep_data_vec_2[143 : 120] = dep_chan_data_8_2;
    assign token_in_vec_2[5] = token_8_2;
    assign in_chan_dep_vld_vec_2[6] = dep_chan_vld_12_2;
    assign in_chan_dep_data_vec_2[167 : 144] = dep_chan_data_12_2;
    assign token_in_vec_2[6] = token_12_2;
    assign in_chan_dep_vld_vec_2[7] = dep_chan_vld_13_2;
    assign in_chan_dep_data_vec_2[191 : 168] = dep_chan_data_13_2;
    assign token_in_vec_2[7] = token_13_2;
    assign in_chan_dep_vld_vec_2[8] = dep_chan_vld_14_2;
    assign in_chan_dep_data_vec_2[215 : 192] = dep_chan_data_14_2;
    assign token_in_vec_2[8] = token_14_2;
    assign in_chan_dep_vld_vec_2[9] = dep_chan_vld_15_2;
    assign in_chan_dep_data_vec_2[239 : 216] = dep_chan_data_15_2;
    assign token_in_vec_2[9] = token_15_2;
    assign in_chan_dep_vld_vec_2[10] = dep_chan_vld_16_2;
    assign in_chan_dep_data_vec_2[263 : 240] = dep_chan_data_16_2;
    assign token_in_vec_2[10] = token_16_2;
    assign in_chan_dep_vld_vec_2[11] = dep_chan_vld_17_2;
    assign in_chan_dep_data_vec_2[287 : 264] = dep_chan_data_17_2;
    assign token_in_vec_2[11] = token_17_2;
    assign dep_chan_vld_2_0 = out_chan_dep_vld_vec_2[0];
    assign dep_chan_data_2_0 = out_chan_dep_data_2;
    assign token_2_0 = token_out_vec_2[0];
    assign dep_chan_vld_2_1 = out_chan_dep_vld_vec_2[1];
    assign dep_chan_data_2_1 = out_chan_dep_data_2;
    assign token_2_1 = token_out_vec_2[1];
    assign dep_chan_vld_2_3 = out_chan_dep_vld_vec_2[2];
    assign dep_chan_data_2_3 = out_chan_dep_data_2;
    assign token_2_3 = token_out_vec_2[2];
    assign dep_chan_vld_2_4 = out_chan_dep_vld_vec_2[3];
    assign dep_chan_data_2_4 = out_chan_dep_data_2;
    assign token_2_4 = token_out_vec_2[3];
    assign dep_chan_vld_2_5 = out_chan_dep_vld_vec_2[4];
    assign dep_chan_data_2_5 = out_chan_dep_data_2;
    assign token_2_5 = token_out_vec_2[4];
    assign dep_chan_vld_2_12 = out_chan_dep_vld_vec_2[5];
    assign dep_chan_data_2_12 = out_chan_dep_data_2;
    assign token_2_12 = token_out_vec_2[5];
    assign dep_chan_vld_2_13 = out_chan_dep_vld_vec_2[6];
    assign dep_chan_data_2_13 = out_chan_dep_data_2;
    assign token_2_13 = token_out_vec_2[6];
    assign dep_chan_vld_2_14 = out_chan_dep_vld_vec_2[7];
    assign dep_chan_data_2_14 = out_chan_dep_data_2;
    assign token_2_14 = token_out_vec_2[7];
    assign dep_chan_vld_2_15 = out_chan_dep_vld_vec_2[8];
    assign dep_chan_data_2_15 = out_chan_dep_data_2;
    assign token_2_15 = token_out_vec_2[8];
    assign dep_chan_vld_2_16 = out_chan_dep_vld_vec_2[9];
    assign dep_chan_data_2_16 = out_chan_dep_data_2;
    assign token_2_16 = token_out_vec_2[9];
    assign dep_chan_vld_2_17 = out_chan_dep_vld_vec_2[10];
    assign dep_chan_data_2_17 = out_chan_dep_data_2;
    assign token_2_17 = token_out_vec_2[10];

    // Process: multiply_426_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 3, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_3 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_3),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_3),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_3),
        .token_in_vec(token_in_vec_3),
        .dl_detect_in(dl_detect_out),
        .origin(origin[3]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_3),
        .out_chan_dep_data(out_chan_dep_data_3),
        .token_out_vec(token_out_vec_3),
        .dl_detect_out(dl_in_vec[3]));

    assign proc_3_data_FIFO_blk[0] = 1'b0;
    assign proc_3_data_PIPO_blk[0] = 1'b0;
    assign proc_3_start_FIFO_blk[0] = 1'b0;
    assign proc_3_TLF_FIFO_blk[0] = 1'b0;
    assign proc_3_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_3_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_3[0] = dl_detect_out ? proc_dep_vld_vec_3_reg[0] : (proc_3_data_FIFO_blk[0] | proc_3_data_PIPO_blk[0] | proc_3_start_FIFO_blk[0] | proc_3_TLF_FIFO_blk[0] | proc_3_input_sync_blk[0] | proc_3_output_sync_blk[0]);
    assign proc_3_data_FIFO_blk[1] = 1'b0;
    assign proc_3_data_PIPO_blk[1] = 1'b0;
    assign proc_3_start_FIFO_blk[1] = 1'b0;
    assign proc_3_TLF_FIFO_blk[1] = 1'b0;
    assign proc_3_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_3_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_3[1] = dl_detect_out ? proc_dep_vld_vec_3_reg[1] : (proc_3_data_FIFO_blk[1] | proc_3_data_PIPO_blk[1] | proc_3_start_FIFO_blk[1] | proc_3_TLF_FIFO_blk[1] | proc_3_input_sync_blk[1] | proc_3_output_sync_blk[1]);
    assign proc_3_data_FIFO_blk[2] = 1'b0;
    assign proc_3_data_PIPO_blk[2] = 1'b0;
    assign proc_3_start_FIFO_blk[2] = 1'b0;
    assign proc_3_TLF_FIFO_blk[2] = 1'b0;
    assign proc_3_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_3_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_3[2] = dl_detect_out ? proc_dep_vld_vec_3_reg[2] : (proc_3_data_FIFO_blk[2] | proc_3_data_PIPO_blk[2] | proc_3_start_FIFO_blk[2] | proc_3_TLF_FIFO_blk[2] | proc_3_input_sync_blk[2] | proc_3_output_sync_blk[2]);
    assign proc_3_data_FIFO_blk[3] = 1'b0;
    assign proc_3_data_PIPO_blk[3] = 1'b0;
    assign proc_3_start_FIFO_blk[3] = 1'b0;
    assign proc_3_TLF_FIFO_blk[3] = 1'b0;
    assign proc_3_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_3_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_3[3] = dl_detect_out ? proc_dep_vld_vec_3_reg[3] : (proc_3_data_FIFO_blk[3] | proc_3_data_PIPO_blk[3] | proc_3_start_FIFO_blk[3] | proc_3_TLF_FIFO_blk[3] | proc_3_input_sync_blk[3] | proc_3_output_sync_blk[3]);
    assign proc_3_data_FIFO_blk[4] = 1'b0;
    assign proc_3_data_PIPO_blk[4] = 1'b0;
    assign proc_3_start_FIFO_blk[4] = 1'b0;
    assign proc_3_TLF_FIFO_blk[4] = 1'b0;
    assign proc_3_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_3_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_3[4] = dl_detect_out ? proc_dep_vld_vec_3_reg[4] : (proc_3_data_FIFO_blk[4] | proc_3_data_PIPO_blk[4] | proc_3_start_FIFO_blk[4] | proc_3_TLF_FIFO_blk[4] | proc_3_input_sync_blk[4] | proc_3_output_sync_blk[4]);
    assign proc_3_data_FIFO_blk[5] = 1'b0;
    assign proc_3_data_PIPO_blk[5] = 1'b0;
    assign proc_3_start_FIFO_blk[5] = 1'b0;
    assign proc_3_TLF_FIFO_blk[5] = 1'b0;
    assign proc_3_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_3_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_3[5] = dl_detect_out ? proc_dep_vld_vec_3_reg[5] : (proc_3_data_FIFO_blk[5] | proc_3_data_PIPO_blk[5] | proc_3_start_FIFO_blk[5] | proc_3_TLF_FIFO_blk[5] | proc_3_input_sync_blk[5] | proc_3_output_sync_blk[5]);
    assign proc_3_data_FIFO_blk[6] = 1'b0;
    assign proc_3_data_PIPO_blk[6] = 1'b0;
    assign proc_3_start_FIFO_blk[6] = 1'b0;
    assign proc_3_TLF_FIFO_blk[6] = 1'b0;
    assign proc_3_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_3_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_3[6] = dl_detect_out ? proc_dep_vld_vec_3_reg[6] : (proc_3_data_FIFO_blk[6] | proc_3_data_PIPO_blk[6] | proc_3_start_FIFO_blk[6] | proc_3_TLF_FIFO_blk[6] | proc_3_input_sync_blk[6] | proc_3_output_sync_blk[6]);
    assign proc_3_data_FIFO_blk[7] = 1'b0;
    assign proc_3_data_PIPO_blk[7] = 1'b0;
    assign proc_3_start_FIFO_blk[7] = 1'b0;
    assign proc_3_TLF_FIFO_blk[7] = 1'b0;
    assign proc_3_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_3_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_3[7] = dl_detect_out ? proc_dep_vld_vec_3_reg[7] : (proc_3_data_FIFO_blk[7] | proc_3_data_PIPO_blk[7] | proc_3_start_FIFO_blk[7] | proc_3_TLF_FIFO_blk[7] | proc_3_input_sync_blk[7] | proc_3_output_sync_blk[7]);
    assign proc_3_data_FIFO_blk[8] = 1'b0;
    assign proc_3_data_PIPO_blk[8] = 1'b0;
    assign proc_3_start_FIFO_blk[8] = 1'b0;
    assign proc_3_TLF_FIFO_blk[8] = 1'b0;
    assign proc_3_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_3_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_3[8] = dl_detect_out ? proc_dep_vld_vec_3_reg[8] : (proc_3_data_FIFO_blk[8] | proc_3_data_PIPO_blk[8] | proc_3_start_FIFO_blk[8] | proc_3_TLF_FIFO_blk[8] | proc_3_input_sync_blk[8] | proc_3_output_sync_blk[8]);
    assign proc_3_data_FIFO_blk[9] = 1'b0;
    assign proc_3_data_PIPO_blk[9] = 1'b0;
    assign proc_3_start_FIFO_blk[9] = 1'b0;
    assign proc_3_TLF_FIFO_blk[9] = 1'b0;
    assign proc_3_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_3_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_3[9] = dl_detect_out ? proc_dep_vld_vec_3_reg[9] : (proc_3_data_FIFO_blk[9] | proc_3_data_PIPO_blk[9] | proc_3_start_FIFO_blk[9] | proc_3_TLF_FIFO_blk[9] | proc_3_input_sync_blk[9] | proc_3_output_sync_blk[9]);
    assign proc_3_data_FIFO_blk[10] = 1'b0;
    assign proc_3_data_PIPO_blk[10] = 1'b0;
    assign proc_3_start_FIFO_blk[10] = 1'b0;
    assign proc_3_TLF_FIFO_blk[10] = 1'b0;
    assign proc_3_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_426_U0_ap_ready & multiply_426_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_3_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_3[10] = dl_detect_out ? proc_dep_vld_vec_3_reg[10] : (proc_3_data_FIFO_blk[10] | proc_3_data_PIPO_blk[10] | proc_3_start_FIFO_blk[10] | proc_3_TLF_FIFO_blk[10] | proc_3_input_sync_blk[10] | proc_3_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_3_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_3_reg <= proc_dep_vld_vec_3;
        end
    end
    assign in_chan_dep_vld_vec_3[0] = dep_chan_vld_0_3;
    assign in_chan_dep_data_vec_3[23 : 0] = dep_chan_data_0_3;
    assign token_in_vec_3[0] = token_0_3;
    assign in_chan_dep_vld_vec_3[1] = dep_chan_vld_1_3;
    assign in_chan_dep_data_vec_3[47 : 24] = dep_chan_data_1_3;
    assign token_in_vec_3[1] = token_1_3;
    assign in_chan_dep_vld_vec_3[2] = dep_chan_vld_2_3;
    assign in_chan_dep_data_vec_3[71 : 48] = dep_chan_data_2_3;
    assign token_in_vec_3[2] = token_2_3;
    assign in_chan_dep_vld_vec_3[3] = dep_chan_vld_4_3;
    assign in_chan_dep_data_vec_3[95 : 72] = dep_chan_data_4_3;
    assign token_in_vec_3[3] = token_4_3;
    assign in_chan_dep_vld_vec_3[4] = dep_chan_vld_5_3;
    assign in_chan_dep_data_vec_3[119 : 96] = dep_chan_data_5_3;
    assign token_in_vec_3[4] = token_5_3;
    assign in_chan_dep_vld_vec_3[5] = dep_chan_vld_9_3;
    assign in_chan_dep_data_vec_3[143 : 120] = dep_chan_data_9_3;
    assign token_in_vec_3[5] = token_9_3;
    assign in_chan_dep_vld_vec_3[6] = dep_chan_vld_12_3;
    assign in_chan_dep_data_vec_3[167 : 144] = dep_chan_data_12_3;
    assign token_in_vec_3[6] = token_12_3;
    assign in_chan_dep_vld_vec_3[7] = dep_chan_vld_13_3;
    assign in_chan_dep_data_vec_3[191 : 168] = dep_chan_data_13_3;
    assign token_in_vec_3[7] = token_13_3;
    assign in_chan_dep_vld_vec_3[8] = dep_chan_vld_14_3;
    assign in_chan_dep_data_vec_3[215 : 192] = dep_chan_data_14_3;
    assign token_in_vec_3[8] = token_14_3;
    assign in_chan_dep_vld_vec_3[9] = dep_chan_vld_15_3;
    assign in_chan_dep_data_vec_3[239 : 216] = dep_chan_data_15_3;
    assign token_in_vec_3[9] = token_15_3;
    assign in_chan_dep_vld_vec_3[10] = dep_chan_vld_16_3;
    assign in_chan_dep_data_vec_3[263 : 240] = dep_chan_data_16_3;
    assign token_in_vec_3[10] = token_16_3;
    assign in_chan_dep_vld_vec_3[11] = dep_chan_vld_17_3;
    assign in_chan_dep_data_vec_3[287 : 264] = dep_chan_data_17_3;
    assign token_in_vec_3[11] = token_17_3;
    assign dep_chan_vld_3_0 = out_chan_dep_vld_vec_3[0];
    assign dep_chan_data_3_0 = out_chan_dep_data_3;
    assign token_3_0 = token_out_vec_3[0];
    assign dep_chan_vld_3_1 = out_chan_dep_vld_vec_3[1];
    assign dep_chan_data_3_1 = out_chan_dep_data_3;
    assign token_3_1 = token_out_vec_3[1];
    assign dep_chan_vld_3_2 = out_chan_dep_vld_vec_3[2];
    assign dep_chan_data_3_2 = out_chan_dep_data_3;
    assign token_3_2 = token_out_vec_3[2];
    assign dep_chan_vld_3_4 = out_chan_dep_vld_vec_3[3];
    assign dep_chan_data_3_4 = out_chan_dep_data_3;
    assign token_3_4 = token_out_vec_3[3];
    assign dep_chan_vld_3_5 = out_chan_dep_vld_vec_3[4];
    assign dep_chan_data_3_5 = out_chan_dep_data_3;
    assign token_3_5 = token_out_vec_3[4];
    assign dep_chan_vld_3_12 = out_chan_dep_vld_vec_3[5];
    assign dep_chan_data_3_12 = out_chan_dep_data_3;
    assign token_3_12 = token_out_vec_3[5];
    assign dep_chan_vld_3_13 = out_chan_dep_vld_vec_3[6];
    assign dep_chan_data_3_13 = out_chan_dep_data_3;
    assign token_3_13 = token_out_vec_3[6];
    assign dep_chan_vld_3_14 = out_chan_dep_vld_vec_3[7];
    assign dep_chan_data_3_14 = out_chan_dep_data_3;
    assign token_3_14 = token_out_vec_3[7];
    assign dep_chan_vld_3_15 = out_chan_dep_vld_vec_3[8];
    assign dep_chan_data_3_15 = out_chan_dep_data_3;
    assign token_3_15 = token_out_vec_3[8];
    assign dep_chan_vld_3_16 = out_chan_dep_vld_vec_3[9];
    assign dep_chan_data_3_16 = out_chan_dep_data_3;
    assign token_3_16 = token_out_vec_3[9];
    assign dep_chan_vld_3_17 = out_chan_dep_vld_vec_3[10];
    assign dep_chan_data_3_17 = out_chan_dep_data_3;
    assign token_3_17 = token_out_vec_3[10];

    // Process: multiply_527_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 4, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_4 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_4),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_4),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_4),
        .token_in_vec(token_in_vec_4),
        .dl_detect_in(dl_detect_out),
        .origin(origin[4]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_4),
        .out_chan_dep_data(out_chan_dep_data_4),
        .token_out_vec(token_out_vec_4),
        .dl_detect_out(dl_in_vec[4]));

    assign proc_4_data_FIFO_blk[0] = 1'b0;
    assign proc_4_data_PIPO_blk[0] = 1'b0;
    assign proc_4_start_FIFO_blk[0] = 1'b0;
    assign proc_4_TLF_FIFO_blk[0] = 1'b0;
    assign proc_4_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_4_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_4[0] = dl_detect_out ? proc_dep_vld_vec_4_reg[0] : (proc_4_data_FIFO_blk[0] | proc_4_data_PIPO_blk[0] | proc_4_start_FIFO_blk[0] | proc_4_TLF_FIFO_blk[0] | proc_4_input_sync_blk[0] | proc_4_output_sync_blk[0]);
    assign proc_4_data_FIFO_blk[1] = 1'b0;
    assign proc_4_data_PIPO_blk[1] = 1'b0;
    assign proc_4_start_FIFO_blk[1] = 1'b0;
    assign proc_4_TLF_FIFO_blk[1] = 1'b0;
    assign proc_4_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_4_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_4[1] = dl_detect_out ? proc_dep_vld_vec_4_reg[1] : (proc_4_data_FIFO_blk[1] | proc_4_data_PIPO_blk[1] | proc_4_start_FIFO_blk[1] | proc_4_TLF_FIFO_blk[1] | proc_4_input_sync_blk[1] | proc_4_output_sync_blk[1]);
    assign proc_4_data_FIFO_blk[2] = 1'b0;
    assign proc_4_data_PIPO_blk[2] = 1'b0;
    assign proc_4_start_FIFO_blk[2] = 1'b0;
    assign proc_4_TLF_FIFO_blk[2] = 1'b0;
    assign proc_4_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_4_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_4[2] = dl_detect_out ? proc_dep_vld_vec_4_reg[2] : (proc_4_data_FIFO_blk[2] | proc_4_data_PIPO_blk[2] | proc_4_start_FIFO_blk[2] | proc_4_TLF_FIFO_blk[2] | proc_4_input_sync_blk[2] | proc_4_output_sync_blk[2]);
    assign proc_4_data_FIFO_blk[3] = 1'b0;
    assign proc_4_data_PIPO_blk[3] = 1'b0;
    assign proc_4_start_FIFO_blk[3] = 1'b0;
    assign proc_4_TLF_FIFO_blk[3] = 1'b0;
    assign proc_4_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_4_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_4[3] = dl_detect_out ? proc_dep_vld_vec_4_reg[3] : (proc_4_data_FIFO_blk[3] | proc_4_data_PIPO_blk[3] | proc_4_start_FIFO_blk[3] | proc_4_TLF_FIFO_blk[3] | proc_4_input_sync_blk[3] | proc_4_output_sync_blk[3]);
    assign proc_4_data_FIFO_blk[4] = 1'b0;
    assign proc_4_data_PIPO_blk[4] = 1'b0;
    assign proc_4_start_FIFO_blk[4] = 1'b0;
    assign proc_4_TLF_FIFO_blk[4] = 1'b0;
    assign proc_4_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_4_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_4[4] = dl_detect_out ? proc_dep_vld_vec_4_reg[4] : (proc_4_data_FIFO_blk[4] | proc_4_data_PIPO_blk[4] | proc_4_start_FIFO_blk[4] | proc_4_TLF_FIFO_blk[4] | proc_4_input_sync_blk[4] | proc_4_output_sync_blk[4]);
    assign proc_4_data_FIFO_blk[5] = 1'b0;
    assign proc_4_data_PIPO_blk[5] = 1'b0;
    assign proc_4_start_FIFO_blk[5] = 1'b0;
    assign proc_4_TLF_FIFO_blk[5] = 1'b0;
    assign proc_4_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_4_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_4[5] = dl_detect_out ? proc_dep_vld_vec_4_reg[5] : (proc_4_data_FIFO_blk[5] | proc_4_data_PIPO_blk[5] | proc_4_start_FIFO_blk[5] | proc_4_TLF_FIFO_blk[5] | proc_4_input_sync_blk[5] | proc_4_output_sync_blk[5]);
    assign proc_4_data_FIFO_blk[6] = 1'b0;
    assign proc_4_data_PIPO_blk[6] = 1'b0;
    assign proc_4_start_FIFO_blk[6] = 1'b0;
    assign proc_4_TLF_FIFO_blk[6] = 1'b0;
    assign proc_4_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_4_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_4[6] = dl_detect_out ? proc_dep_vld_vec_4_reg[6] : (proc_4_data_FIFO_blk[6] | proc_4_data_PIPO_blk[6] | proc_4_start_FIFO_blk[6] | proc_4_TLF_FIFO_blk[6] | proc_4_input_sync_blk[6] | proc_4_output_sync_blk[6]);
    assign proc_4_data_FIFO_blk[7] = 1'b0;
    assign proc_4_data_PIPO_blk[7] = 1'b0;
    assign proc_4_start_FIFO_blk[7] = 1'b0;
    assign proc_4_TLF_FIFO_blk[7] = 1'b0;
    assign proc_4_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_4_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_4[7] = dl_detect_out ? proc_dep_vld_vec_4_reg[7] : (proc_4_data_FIFO_blk[7] | proc_4_data_PIPO_blk[7] | proc_4_start_FIFO_blk[7] | proc_4_TLF_FIFO_blk[7] | proc_4_input_sync_blk[7] | proc_4_output_sync_blk[7]);
    assign proc_4_data_FIFO_blk[8] = 1'b0;
    assign proc_4_data_PIPO_blk[8] = 1'b0;
    assign proc_4_start_FIFO_blk[8] = 1'b0;
    assign proc_4_TLF_FIFO_blk[8] = 1'b0;
    assign proc_4_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_4_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_4[8] = dl_detect_out ? proc_dep_vld_vec_4_reg[8] : (proc_4_data_FIFO_blk[8] | proc_4_data_PIPO_blk[8] | proc_4_start_FIFO_blk[8] | proc_4_TLF_FIFO_blk[8] | proc_4_input_sync_blk[8] | proc_4_output_sync_blk[8]);
    assign proc_4_data_FIFO_blk[9] = 1'b0;
    assign proc_4_data_PIPO_blk[9] = 1'b0;
    assign proc_4_start_FIFO_blk[9] = 1'b0;
    assign proc_4_TLF_FIFO_blk[9] = 1'b0;
    assign proc_4_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_4_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_4[9] = dl_detect_out ? proc_dep_vld_vec_4_reg[9] : (proc_4_data_FIFO_blk[9] | proc_4_data_PIPO_blk[9] | proc_4_start_FIFO_blk[9] | proc_4_TLF_FIFO_blk[9] | proc_4_input_sync_blk[9] | proc_4_output_sync_blk[9]);
    assign proc_4_data_FIFO_blk[10] = 1'b0;
    assign proc_4_data_PIPO_blk[10] = 1'b0;
    assign proc_4_start_FIFO_blk[10] = 1'b0;
    assign proc_4_TLF_FIFO_blk[10] = 1'b0;
    assign proc_4_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_527_U0_ap_ready & multiply_527_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_4_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_4[10] = dl_detect_out ? proc_dep_vld_vec_4_reg[10] : (proc_4_data_FIFO_blk[10] | proc_4_data_PIPO_blk[10] | proc_4_start_FIFO_blk[10] | proc_4_TLF_FIFO_blk[10] | proc_4_input_sync_blk[10] | proc_4_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_4_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_4_reg <= proc_dep_vld_vec_4;
        end
    end
    assign in_chan_dep_vld_vec_4[0] = dep_chan_vld_0_4;
    assign in_chan_dep_data_vec_4[23 : 0] = dep_chan_data_0_4;
    assign token_in_vec_4[0] = token_0_4;
    assign in_chan_dep_vld_vec_4[1] = dep_chan_vld_1_4;
    assign in_chan_dep_data_vec_4[47 : 24] = dep_chan_data_1_4;
    assign token_in_vec_4[1] = token_1_4;
    assign in_chan_dep_vld_vec_4[2] = dep_chan_vld_2_4;
    assign in_chan_dep_data_vec_4[71 : 48] = dep_chan_data_2_4;
    assign token_in_vec_4[2] = token_2_4;
    assign in_chan_dep_vld_vec_4[3] = dep_chan_vld_3_4;
    assign in_chan_dep_data_vec_4[95 : 72] = dep_chan_data_3_4;
    assign token_in_vec_4[3] = token_3_4;
    assign in_chan_dep_vld_vec_4[4] = dep_chan_vld_5_4;
    assign in_chan_dep_data_vec_4[119 : 96] = dep_chan_data_5_4;
    assign token_in_vec_4[4] = token_5_4;
    assign in_chan_dep_vld_vec_4[5] = dep_chan_vld_10_4;
    assign in_chan_dep_data_vec_4[143 : 120] = dep_chan_data_10_4;
    assign token_in_vec_4[5] = token_10_4;
    assign in_chan_dep_vld_vec_4[6] = dep_chan_vld_12_4;
    assign in_chan_dep_data_vec_4[167 : 144] = dep_chan_data_12_4;
    assign token_in_vec_4[6] = token_12_4;
    assign in_chan_dep_vld_vec_4[7] = dep_chan_vld_13_4;
    assign in_chan_dep_data_vec_4[191 : 168] = dep_chan_data_13_4;
    assign token_in_vec_4[7] = token_13_4;
    assign in_chan_dep_vld_vec_4[8] = dep_chan_vld_14_4;
    assign in_chan_dep_data_vec_4[215 : 192] = dep_chan_data_14_4;
    assign token_in_vec_4[8] = token_14_4;
    assign in_chan_dep_vld_vec_4[9] = dep_chan_vld_15_4;
    assign in_chan_dep_data_vec_4[239 : 216] = dep_chan_data_15_4;
    assign token_in_vec_4[9] = token_15_4;
    assign in_chan_dep_vld_vec_4[10] = dep_chan_vld_16_4;
    assign in_chan_dep_data_vec_4[263 : 240] = dep_chan_data_16_4;
    assign token_in_vec_4[10] = token_16_4;
    assign in_chan_dep_vld_vec_4[11] = dep_chan_vld_17_4;
    assign in_chan_dep_data_vec_4[287 : 264] = dep_chan_data_17_4;
    assign token_in_vec_4[11] = token_17_4;
    assign dep_chan_vld_4_0 = out_chan_dep_vld_vec_4[0];
    assign dep_chan_data_4_0 = out_chan_dep_data_4;
    assign token_4_0 = token_out_vec_4[0];
    assign dep_chan_vld_4_1 = out_chan_dep_vld_vec_4[1];
    assign dep_chan_data_4_1 = out_chan_dep_data_4;
    assign token_4_1 = token_out_vec_4[1];
    assign dep_chan_vld_4_2 = out_chan_dep_vld_vec_4[2];
    assign dep_chan_data_4_2 = out_chan_dep_data_4;
    assign token_4_2 = token_out_vec_4[2];
    assign dep_chan_vld_4_3 = out_chan_dep_vld_vec_4[3];
    assign dep_chan_data_4_3 = out_chan_dep_data_4;
    assign token_4_3 = token_out_vec_4[3];
    assign dep_chan_vld_4_5 = out_chan_dep_vld_vec_4[4];
    assign dep_chan_data_4_5 = out_chan_dep_data_4;
    assign token_4_5 = token_out_vec_4[4];
    assign dep_chan_vld_4_12 = out_chan_dep_vld_vec_4[5];
    assign dep_chan_data_4_12 = out_chan_dep_data_4;
    assign token_4_12 = token_out_vec_4[5];
    assign dep_chan_vld_4_13 = out_chan_dep_vld_vec_4[6];
    assign dep_chan_data_4_13 = out_chan_dep_data_4;
    assign token_4_13 = token_out_vec_4[6];
    assign dep_chan_vld_4_14 = out_chan_dep_vld_vec_4[7];
    assign dep_chan_data_4_14 = out_chan_dep_data_4;
    assign token_4_14 = token_out_vec_4[7];
    assign dep_chan_vld_4_15 = out_chan_dep_vld_vec_4[8];
    assign dep_chan_data_4_15 = out_chan_dep_data_4;
    assign token_4_15 = token_out_vec_4[8];
    assign dep_chan_vld_4_16 = out_chan_dep_vld_vec_4[9];
    assign dep_chan_data_4_16 = out_chan_dep_data_4;
    assign token_4_16 = token_out_vec_4[9];
    assign dep_chan_vld_4_17 = out_chan_dep_vld_vec_4[10];
    assign dep_chan_data_4_17 = out_chan_dep_data_4;
    assign token_4_17 = token_out_vec_4[10];

    // Process: multiply_628_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 5, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_5 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_5),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_5),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_5),
        .token_in_vec(token_in_vec_5),
        .dl_detect_in(dl_detect_out),
        .origin(origin[5]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_5),
        .out_chan_dep_data(out_chan_dep_data_5),
        .token_out_vec(token_out_vec_5),
        .dl_detect_out(dl_in_vec[5]));

    assign proc_5_data_FIFO_blk[0] = 1'b0;
    assign proc_5_data_PIPO_blk[0] = 1'b0;
    assign proc_5_start_FIFO_blk[0] = 1'b0;
    assign proc_5_TLF_FIFO_blk[0] = 1'b0;
    assign proc_5_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_5_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_5[0] = dl_detect_out ? proc_dep_vld_vec_5_reg[0] : (proc_5_data_FIFO_blk[0] | proc_5_data_PIPO_blk[0] | proc_5_start_FIFO_blk[0] | proc_5_TLF_FIFO_blk[0] | proc_5_input_sync_blk[0] | proc_5_output_sync_blk[0]);
    assign proc_5_data_FIFO_blk[1] = 1'b0;
    assign proc_5_data_PIPO_blk[1] = 1'b0;
    assign proc_5_start_FIFO_blk[1] = 1'b0;
    assign proc_5_TLF_FIFO_blk[1] = 1'b0;
    assign proc_5_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_5_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_5[1] = dl_detect_out ? proc_dep_vld_vec_5_reg[1] : (proc_5_data_FIFO_blk[1] | proc_5_data_PIPO_blk[1] | proc_5_start_FIFO_blk[1] | proc_5_TLF_FIFO_blk[1] | proc_5_input_sync_blk[1] | proc_5_output_sync_blk[1]);
    assign proc_5_data_FIFO_blk[2] = 1'b0;
    assign proc_5_data_PIPO_blk[2] = 1'b0;
    assign proc_5_start_FIFO_blk[2] = 1'b0;
    assign proc_5_TLF_FIFO_blk[2] = 1'b0;
    assign proc_5_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_5_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_5[2] = dl_detect_out ? proc_dep_vld_vec_5_reg[2] : (proc_5_data_FIFO_blk[2] | proc_5_data_PIPO_blk[2] | proc_5_start_FIFO_blk[2] | proc_5_TLF_FIFO_blk[2] | proc_5_input_sync_blk[2] | proc_5_output_sync_blk[2]);
    assign proc_5_data_FIFO_blk[3] = 1'b0;
    assign proc_5_data_PIPO_blk[3] = 1'b0;
    assign proc_5_start_FIFO_blk[3] = 1'b0;
    assign proc_5_TLF_FIFO_blk[3] = 1'b0;
    assign proc_5_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_5_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_5[3] = dl_detect_out ? proc_dep_vld_vec_5_reg[3] : (proc_5_data_FIFO_blk[3] | proc_5_data_PIPO_blk[3] | proc_5_start_FIFO_blk[3] | proc_5_TLF_FIFO_blk[3] | proc_5_input_sync_blk[3] | proc_5_output_sync_blk[3]);
    assign proc_5_data_FIFO_blk[4] = 1'b0;
    assign proc_5_data_PIPO_blk[4] = 1'b0;
    assign proc_5_start_FIFO_blk[4] = 1'b0;
    assign proc_5_TLF_FIFO_blk[4] = 1'b0;
    assign proc_5_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_5_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_5[4] = dl_detect_out ? proc_dep_vld_vec_5_reg[4] : (proc_5_data_FIFO_blk[4] | proc_5_data_PIPO_blk[4] | proc_5_start_FIFO_blk[4] | proc_5_TLF_FIFO_blk[4] | proc_5_input_sync_blk[4] | proc_5_output_sync_blk[4]);
    assign proc_5_data_FIFO_blk[5] = 1'b0;
    assign proc_5_data_PIPO_blk[5] = 1'b0;
    assign proc_5_start_FIFO_blk[5] = 1'b0;
    assign proc_5_TLF_FIFO_blk[5] = 1'b0;
    assign proc_5_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_5_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_5[5] = dl_detect_out ? proc_dep_vld_vec_5_reg[5] : (proc_5_data_FIFO_blk[5] | proc_5_data_PIPO_blk[5] | proc_5_start_FIFO_blk[5] | proc_5_TLF_FIFO_blk[5] | proc_5_input_sync_blk[5] | proc_5_output_sync_blk[5]);
    assign proc_5_data_FIFO_blk[6] = 1'b0;
    assign proc_5_data_PIPO_blk[6] = 1'b0;
    assign proc_5_start_FIFO_blk[6] = 1'b0;
    assign proc_5_TLF_FIFO_blk[6] = 1'b0;
    assign proc_5_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_5_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_5[6] = dl_detect_out ? proc_dep_vld_vec_5_reg[6] : (proc_5_data_FIFO_blk[6] | proc_5_data_PIPO_blk[6] | proc_5_start_FIFO_blk[6] | proc_5_TLF_FIFO_blk[6] | proc_5_input_sync_blk[6] | proc_5_output_sync_blk[6]);
    assign proc_5_data_FIFO_blk[7] = 1'b0;
    assign proc_5_data_PIPO_blk[7] = 1'b0;
    assign proc_5_start_FIFO_blk[7] = 1'b0;
    assign proc_5_TLF_FIFO_blk[7] = 1'b0;
    assign proc_5_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_5_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_5[7] = dl_detect_out ? proc_dep_vld_vec_5_reg[7] : (proc_5_data_FIFO_blk[7] | proc_5_data_PIPO_blk[7] | proc_5_start_FIFO_blk[7] | proc_5_TLF_FIFO_blk[7] | proc_5_input_sync_blk[7] | proc_5_output_sync_blk[7]);
    assign proc_5_data_FIFO_blk[8] = 1'b0;
    assign proc_5_data_PIPO_blk[8] = 1'b0;
    assign proc_5_start_FIFO_blk[8] = 1'b0;
    assign proc_5_TLF_FIFO_blk[8] = 1'b0;
    assign proc_5_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_5_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_5[8] = dl_detect_out ? proc_dep_vld_vec_5_reg[8] : (proc_5_data_FIFO_blk[8] | proc_5_data_PIPO_blk[8] | proc_5_start_FIFO_blk[8] | proc_5_TLF_FIFO_blk[8] | proc_5_input_sync_blk[8] | proc_5_output_sync_blk[8]);
    assign proc_5_data_FIFO_blk[9] = 1'b0;
    assign proc_5_data_PIPO_blk[9] = 1'b0;
    assign proc_5_start_FIFO_blk[9] = 1'b0;
    assign proc_5_TLF_FIFO_blk[9] = 1'b0;
    assign proc_5_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_5_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_5[9] = dl_detect_out ? proc_dep_vld_vec_5_reg[9] : (proc_5_data_FIFO_blk[9] | proc_5_data_PIPO_blk[9] | proc_5_start_FIFO_blk[9] | proc_5_TLF_FIFO_blk[9] | proc_5_input_sync_blk[9] | proc_5_output_sync_blk[9]);
    assign proc_5_data_FIFO_blk[10] = 1'b0;
    assign proc_5_data_PIPO_blk[10] = 1'b0;
    assign proc_5_start_FIFO_blk[10] = 1'b0;
    assign proc_5_TLF_FIFO_blk[10] = 1'b0;
    assign proc_5_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_628_U0_ap_ready & multiply_628_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_5_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_5[10] = dl_detect_out ? proc_dep_vld_vec_5_reg[10] : (proc_5_data_FIFO_blk[10] | proc_5_data_PIPO_blk[10] | proc_5_start_FIFO_blk[10] | proc_5_TLF_FIFO_blk[10] | proc_5_input_sync_blk[10] | proc_5_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_5_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_5_reg <= proc_dep_vld_vec_5;
        end
    end
    assign in_chan_dep_vld_vec_5[0] = dep_chan_vld_0_5;
    assign in_chan_dep_data_vec_5[23 : 0] = dep_chan_data_0_5;
    assign token_in_vec_5[0] = token_0_5;
    assign in_chan_dep_vld_vec_5[1] = dep_chan_vld_1_5;
    assign in_chan_dep_data_vec_5[47 : 24] = dep_chan_data_1_5;
    assign token_in_vec_5[1] = token_1_5;
    assign in_chan_dep_vld_vec_5[2] = dep_chan_vld_2_5;
    assign in_chan_dep_data_vec_5[71 : 48] = dep_chan_data_2_5;
    assign token_in_vec_5[2] = token_2_5;
    assign in_chan_dep_vld_vec_5[3] = dep_chan_vld_3_5;
    assign in_chan_dep_data_vec_5[95 : 72] = dep_chan_data_3_5;
    assign token_in_vec_5[3] = token_3_5;
    assign in_chan_dep_vld_vec_5[4] = dep_chan_vld_4_5;
    assign in_chan_dep_data_vec_5[119 : 96] = dep_chan_data_4_5;
    assign token_in_vec_5[4] = token_4_5;
    assign in_chan_dep_vld_vec_5[5] = dep_chan_vld_11_5;
    assign in_chan_dep_data_vec_5[143 : 120] = dep_chan_data_11_5;
    assign token_in_vec_5[5] = token_11_5;
    assign in_chan_dep_vld_vec_5[6] = dep_chan_vld_12_5;
    assign in_chan_dep_data_vec_5[167 : 144] = dep_chan_data_12_5;
    assign token_in_vec_5[6] = token_12_5;
    assign in_chan_dep_vld_vec_5[7] = dep_chan_vld_13_5;
    assign in_chan_dep_data_vec_5[191 : 168] = dep_chan_data_13_5;
    assign token_in_vec_5[7] = token_13_5;
    assign in_chan_dep_vld_vec_5[8] = dep_chan_vld_14_5;
    assign in_chan_dep_data_vec_5[215 : 192] = dep_chan_data_14_5;
    assign token_in_vec_5[8] = token_14_5;
    assign in_chan_dep_vld_vec_5[9] = dep_chan_vld_15_5;
    assign in_chan_dep_data_vec_5[239 : 216] = dep_chan_data_15_5;
    assign token_in_vec_5[9] = token_15_5;
    assign in_chan_dep_vld_vec_5[10] = dep_chan_vld_16_5;
    assign in_chan_dep_data_vec_5[263 : 240] = dep_chan_data_16_5;
    assign token_in_vec_5[10] = token_16_5;
    assign in_chan_dep_vld_vec_5[11] = dep_chan_vld_17_5;
    assign in_chan_dep_data_vec_5[287 : 264] = dep_chan_data_17_5;
    assign token_in_vec_5[11] = token_17_5;
    assign dep_chan_vld_5_0 = out_chan_dep_vld_vec_5[0];
    assign dep_chan_data_5_0 = out_chan_dep_data_5;
    assign token_5_0 = token_out_vec_5[0];
    assign dep_chan_vld_5_1 = out_chan_dep_vld_vec_5[1];
    assign dep_chan_data_5_1 = out_chan_dep_data_5;
    assign token_5_1 = token_out_vec_5[1];
    assign dep_chan_vld_5_2 = out_chan_dep_vld_vec_5[2];
    assign dep_chan_data_5_2 = out_chan_dep_data_5;
    assign token_5_2 = token_out_vec_5[2];
    assign dep_chan_vld_5_3 = out_chan_dep_vld_vec_5[3];
    assign dep_chan_data_5_3 = out_chan_dep_data_5;
    assign token_5_3 = token_out_vec_5[3];
    assign dep_chan_vld_5_4 = out_chan_dep_vld_vec_5[4];
    assign dep_chan_data_5_4 = out_chan_dep_data_5;
    assign token_5_4 = token_out_vec_5[4];
    assign dep_chan_vld_5_12 = out_chan_dep_vld_vec_5[5];
    assign dep_chan_data_5_12 = out_chan_dep_data_5;
    assign token_5_12 = token_out_vec_5[5];
    assign dep_chan_vld_5_13 = out_chan_dep_vld_vec_5[6];
    assign dep_chan_data_5_13 = out_chan_dep_data_5;
    assign token_5_13 = token_out_vec_5[6];
    assign dep_chan_vld_5_14 = out_chan_dep_vld_vec_5[7];
    assign dep_chan_data_5_14 = out_chan_dep_data_5;
    assign token_5_14 = token_out_vec_5[7];
    assign dep_chan_vld_5_15 = out_chan_dep_vld_vec_5[8];
    assign dep_chan_data_5_15 = out_chan_dep_data_5;
    assign token_5_15 = token_out_vec_5[8];
    assign dep_chan_vld_5_16 = out_chan_dep_vld_vec_5[9];
    assign dep_chan_data_5_16 = out_chan_dep_data_5;
    assign token_5_16 = token_out_vec_5[9];
    assign dep_chan_vld_5_17 = out_chan_dep_vld_vec_5[10];
    assign dep_chan_data_5_17 = out_chan_dep_data_5;
    assign token_5_17 = token_out_vec_5[10];

    // Process: Block_entry1421_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 6, 1, 1) uz_VSD_6ph_asym_hls_deadlock_detect_unit_6 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_6),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_6),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_6),
        .token_in_vec(token_in_vec_6),
        .dl_detect_in(dl_detect_out),
        .origin(origin[6]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_6),
        .out_chan_dep_data(out_chan_dep_data_6),
        .token_out_vec(token_out_vec_6),
        .dl_detect_out(dl_in_vec[6]));

    assign proc_6_data_FIFO_blk[0] = 1'b0;
    assign proc_6_data_PIPO_blk[0] = 1'b0;
    assign proc_6_start_FIFO_blk[0] = 1'b0;
    assign proc_6_TLF_FIFO_blk[0] = 1'b0 | (~products_0_U.if_empty_n & Block_entry1421_proc_U0.ap_idle & ~products_0_U.if_write);
    assign proc_6_input_sync_blk[0] = 1'b0;
    assign proc_6_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_6[0] = dl_detect_out ? proc_dep_vld_vec_6_reg[0] : (proc_6_data_FIFO_blk[0] | proc_6_data_PIPO_blk[0] | proc_6_start_FIFO_blk[0] | proc_6_TLF_FIFO_blk[0] | proc_6_input_sync_blk[0] | proc_6_output_sync_blk[0]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_6_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_6_reg <= proc_dep_vld_vec_6;
        end
    end
    assign in_chan_dep_vld_vec_6[0] = dep_chan_vld_7_6;
    assign in_chan_dep_data_vec_6[23 : 0] = dep_chan_data_7_6;
    assign token_in_vec_6[0] = token_7_6;
    assign dep_chan_vld_6_0 = out_chan_dep_vld_vec_6[0];
    assign dep_chan_data_6_0 = out_chan_dep_data_6;
    assign token_6_0 = token_out_vec_6[0];

    // Process: Block_entry1422_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 7, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_7 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_7),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_7),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_7),
        .token_in_vec(token_in_vec_7),
        .dl_detect_in(dl_detect_out),
        .origin(origin[7]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_7),
        .out_chan_dep_data(out_chan_dep_data_7),
        .token_out_vec(token_out_vec_7),
        .dl_detect_out(dl_in_vec[7]));

    assign proc_7_data_FIFO_blk[0] = 1'b0;
    assign proc_7_data_PIPO_blk[0] = 1'b0;
    assign proc_7_start_FIFO_blk[0] = 1'b0;
    assign proc_7_TLF_FIFO_blk[0] = 1'b0 | (~products_1_U.if_empty_n & Block_entry1422_proc_U0.ap_idle & ~products_1_U.if_write);
    assign proc_7_input_sync_blk[0] = 1'b0;
    assign proc_7_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_7[0] = dl_detect_out ? proc_dep_vld_vec_7_reg[0] : (proc_7_data_FIFO_blk[0] | proc_7_data_PIPO_blk[0] | proc_7_start_FIFO_blk[0] | proc_7_TLF_FIFO_blk[0] | proc_7_input_sync_blk[0] | proc_7_output_sync_blk[0]);
    assign proc_7_data_FIFO_blk[1] = 1'b0;
    assign proc_7_data_PIPO_blk[1] = 1'b0;
    assign proc_7_start_FIFO_blk[1] = 1'b0;
    assign proc_7_TLF_FIFO_blk[1] = 1'b0 | (~products_assign_load_loc_channel_U.if_empty_n & Block_entry1422_proc_U0.ap_idle & ~products_assign_load_loc_channel_U.if_write);
    assign proc_7_input_sync_blk[1] = 1'b0;
    assign proc_7_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_7[1] = dl_detect_out ? proc_dep_vld_vec_7_reg[1] : (proc_7_data_FIFO_blk[1] | proc_7_data_PIPO_blk[1] | proc_7_start_FIFO_blk[1] | proc_7_TLF_FIFO_blk[1] | proc_7_input_sync_blk[1] | proc_7_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_7_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_7_reg <= proc_dep_vld_vec_7;
        end
    end
    assign in_chan_dep_vld_vec_7[0] = dep_chan_vld_8_7;
    assign in_chan_dep_data_vec_7[23 : 0] = dep_chan_data_8_7;
    assign token_in_vec_7[0] = token_8_7;
    assign dep_chan_vld_7_1 = out_chan_dep_vld_vec_7[0];
    assign dep_chan_data_7_1 = out_chan_dep_data_7;
    assign token_7_1 = token_out_vec_7[0];
    assign dep_chan_vld_7_6 = out_chan_dep_vld_vec_7[1];
    assign dep_chan_data_7_6 = out_chan_dep_data_7;
    assign token_7_6 = token_out_vec_7[1];

    // Process: Block_entry1423_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 8, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_8 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_8),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_8),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_8),
        .token_in_vec(token_in_vec_8),
        .dl_detect_in(dl_detect_out),
        .origin(origin[8]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_8),
        .out_chan_dep_data(out_chan_dep_data_8),
        .token_out_vec(token_out_vec_8),
        .dl_detect_out(dl_in_vec[8]));

    assign proc_8_data_FIFO_blk[0] = 1'b0;
    assign proc_8_data_PIPO_blk[0] = 1'b0;
    assign proc_8_start_FIFO_blk[0] = 1'b0;
    assign proc_8_TLF_FIFO_blk[0] = 1'b0 | (~products_2_U.if_empty_n & Block_entry1423_proc_U0.ap_idle & ~products_2_U.if_write);
    assign proc_8_input_sync_blk[0] = 1'b0;
    assign proc_8_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_8[0] = dl_detect_out ? proc_dep_vld_vec_8_reg[0] : (proc_8_data_FIFO_blk[0] | proc_8_data_PIPO_blk[0] | proc_8_start_FIFO_blk[0] | proc_8_TLF_FIFO_blk[0] | proc_8_input_sync_blk[0] | proc_8_output_sync_blk[0]);
    assign proc_8_data_FIFO_blk[1] = 1'b0;
    assign proc_8_data_PIPO_blk[1] = 1'b0;
    assign proc_8_start_FIFO_blk[1] = 1'b0;
    assign proc_8_TLF_FIFO_blk[1] = 1'b0 | (~add_i_loc_channel_U.if_empty_n & Block_entry1423_proc_U0.ap_idle & ~add_i_loc_channel_U.if_write);
    assign proc_8_input_sync_blk[1] = 1'b0;
    assign proc_8_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_8[1] = dl_detect_out ? proc_dep_vld_vec_8_reg[1] : (proc_8_data_FIFO_blk[1] | proc_8_data_PIPO_blk[1] | proc_8_start_FIFO_blk[1] | proc_8_TLF_FIFO_blk[1] | proc_8_input_sync_blk[1] | proc_8_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_8_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_8_reg <= proc_dep_vld_vec_8;
        end
    end
    assign in_chan_dep_vld_vec_8[0] = dep_chan_vld_9_8;
    assign in_chan_dep_data_vec_8[23 : 0] = dep_chan_data_9_8;
    assign token_in_vec_8[0] = token_9_8;
    assign dep_chan_vld_8_2 = out_chan_dep_vld_vec_8[0];
    assign dep_chan_data_8_2 = out_chan_dep_data_8;
    assign token_8_2 = token_out_vec_8[0];
    assign dep_chan_vld_8_7 = out_chan_dep_vld_vec_8[1];
    assign dep_chan_data_8_7 = out_chan_dep_data_8;
    assign token_8_7 = token_out_vec_8[1];

    // Process: Block_entry1424_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 9, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_9 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_9),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_9),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_9),
        .token_in_vec(token_in_vec_9),
        .dl_detect_in(dl_detect_out),
        .origin(origin[9]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_9),
        .out_chan_dep_data(out_chan_dep_data_9),
        .token_out_vec(token_out_vec_9),
        .dl_detect_out(dl_in_vec[9]));

    assign proc_9_data_FIFO_blk[0] = 1'b0;
    assign proc_9_data_PIPO_blk[0] = 1'b0;
    assign proc_9_start_FIFO_blk[0] = 1'b0;
    assign proc_9_TLF_FIFO_blk[0] = 1'b0 | (~products_3_U.if_empty_n & Block_entry1424_proc_U0.ap_idle & ~products_3_U.if_write);
    assign proc_9_input_sync_blk[0] = 1'b0;
    assign proc_9_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_9[0] = dl_detect_out ? proc_dep_vld_vec_9_reg[0] : (proc_9_data_FIFO_blk[0] | proc_9_data_PIPO_blk[0] | proc_9_start_FIFO_blk[0] | proc_9_TLF_FIFO_blk[0] | proc_9_input_sync_blk[0] | proc_9_output_sync_blk[0]);
    assign proc_9_data_FIFO_blk[1] = 1'b0;
    assign proc_9_data_PIPO_blk[1] = 1'b0;
    assign proc_9_start_FIFO_blk[1] = 1'b0;
    assign proc_9_TLF_FIFO_blk[1] = 1'b0 | (~add3_i_loc_channel_U.if_empty_n & Block_entry1424_proc_U0.ap_idle & ~add3_i_loc_channel_U.if_write);
    assign proc_9_input_sync_blk[1] = 1'b0;
    assign proc_9_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_9[1] = dl_detect_out ? proc_dep_vld_vec_9_reg[1] : (proc_9_data_FIFO_blk[1] | proc_9_data_PIPO_blk[1] | proc_9_start_FIFO_blk[1] | proc_9_TLF_FIFO_blk[1] | proc_9_input_sync_blk[1] | proc_9_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_9_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_9_reg <= proc_dep_vld_vec_9;
        end
    end
    assign in_chan_dep_vld_vec_9[0] = dep_chan_vld_10_9;
    assign in_chan_dep_data_vec_9[23 : 0] = dep_chan_data_10_9;
    assign token_in_vec_9[0] = token_10_9;
    assign dep_chan_vld_9_3 = out_chan_dep_vld_vec_9[0];
    assign dep_chan_data_9_3 = out_chan_dep_data_9;
    assign token_9_3 = token_out_vec_9[0];
    assign dep_chan_vld_9_8 = out_chan_dep_vld_vec_9[1];
    assign dep_chan_data_9_8 = out_chan_dep_data_9;
    assign token_9_8 = token_out_vec_9[1];

    // Process: Block_entry1425_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 10, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_10 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_10),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_10),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_10),
        .token_in_vec(token_in_vec_10),
        .dl_detect_in(dl_detect_out),
        .origin(origin[10]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_10),
        .out_chan_dep_data(out_chan_dep_data_10),
        .token_out_vec(token_out_vec_10),
        .dl_detect_out(dl_in_vec[10]));

    assign proc_10_data_FIFO_blk[0] = 1'b0;
    assign proc_10_data_PIPO_blk[0] = 1'b0;
    assign proc_10_start_FIFO_blk[0] = 1'b0;
    assign proc_10_TLF_FIFO_blk[0] = 1'b0 | (~products_4_U.if_empty_n & Block_entry1425_proc_U0.ap_idle & ~products_4_U.if_write);
    assign proc_10_input_sync_blk[0] = 1'b0;
    assign proc_10_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_10[0] = dl_detect_out ? proc_dep_vld_vec_10_reg[0] : (proc_10_data_FIFO_blk[0] | proc_10_data_PIPO_blk[0] | proc_10_start_FIFO_blk[0] | proc_10_TLF_FIFO_blk[0] | proc_10_input_sync_blk[0] | proc_10_output_sync_blk[0]);
    assign proc_10_data_FIFO_blk[1] = 1'b0;
    assign proc_10_data_PIPO_blk[1] = 1'b0;
    assign proc_10_start_FIFO_blk[1] = 1'b0;
    assign proc_10_TLF_FIFO_blk[1] = 1'b0 | (~add5_i_loc_channel_U.if_empty_n & Block_entry1425_proc_U0.ap_idle & ~add5_i_loc_channel_U.if_write);
    assign proc_10_input_sync_blk[1] = 1'b0;
    assign proc_10_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_10[1] = dl_detect_out ? proc_dep_vld_vec_10_reg[1] : (proc_10_data_FIFO_blk[1] | proc_10_data_PIPO_blk[1] | proc_10_start_FIFO_blk[1] | proc_10_TLF_FIFO_blk[1] | proc_10_input_sync_blk[1] | proc_10_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_10_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_10_reg <= proc_dep_vld_vec_10;
        end
    end
    assign in_chan_dep_vld_vec_10[0] = dep_chan_vld_11_10;
    assign in_chan_dep_data_vec_10[23 : 0] = dep_chan_data_11_10;
    assign token_in_vec_10[0] = token_11_10;
    assign dep_chan_vld_10_4 = out_chan_dep_vld_vec_10[0];
    assign dep_chan_data_10_4 = out_chan_dep_data_10;
    assign token_10_4 = token_out_vec_10[0];
    assign dep_chan_vld_10_9 = out_chan_dep_vld_vec_10[1];
    assign dep_chan_data_10_9 = out_chan_dep_data_10;
    assign token_10_9 = token_out_vec_10[1];

    // Process: Block_entry1426_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 11, 1, 3) uz_VSD_6ph_asym_hls_deadlock_detect_unit_11 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_11),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_11),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_11),
        .token_in_vec(token_in_vec_11),
        .dl_detect_in(dl_detect_out),
        .origin(origin[11]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_11),
        .out_chan_dep_data(out_chan_dep_data_11),
        .token_out_vec(token_out_vec_11),
        .dl_detect_out(dl_in_vec[11]));

    assign proc_11_data_FIFO_blk[0] = 1'b0;
    assign proc_11_data_PIPO_blk[0] = 1'b0;
    assign proc_11_start_FIFO_blk[0] = 1'b0;
    assign proc_11_TLF_FIFO_blk[0] = 1'b0 | (~products_5_U.if_empty_n & Block_entry1426_proc_U0.ap_idle & ~products_5_U.if_write);
    assign proc_11_input_sync_blk[0] = 1'b0;
    assign proc_11_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_11[0] = dl_detect_out ? proc_dep_vld_vec_11_reg[0] : (proc_11_data_FIFO_blk[0] | proc_11_data_PIPO_blk[0] | proc_11_start_FIFO_blk[0] | proc_11_TLF_FIFO_blk[0] | proc_11_input_sync_blk[0] | proc_11_output_sync_blk[0]);
    assign proc_11_data_FIFO_blk[1] = 1'b0;
    assign proc_11_data_PIPO_blk[1] = 1'b0;
    assign proc_11_start_FIFO_blk[1] = 1'b0;
    assign proc_11_TLF_FIFO_blk[1] = 1'b0 | (~add7_i_loc_channel_U.if_empty_n & Block_entry1426_proc_U0.ap_idle & ~add7_i_loc_channel_U.if_write);
    assign proc_11_input_sync_blk[1] = 1'b0;
    assign proc_11_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_11[1] = dl_detect_out ? proc_dep_vld_vec_11_reg[1] : (proc_11_data_FIFO_blk[1] | proc_11_data_PIPO_blk[1] | proc_11_start_FIFO_blk[1] | proc_11_TLF_FIFO_blk[1] | proc_11_input_sync_blk[1] | proc_11_output_sync_blk[1]);
    assign proc_11_data_FIFO_blk[2] = 1'b0;
    assign proc_11_data_PIPO_blk[2] = 1'b0;
    assign proc_11_start_FIFO_blk[2] = 1'b0;
    assign proc_11_TLF_FIFO_blk[2] = 1'b0;
    assign proc_11_input_sync_blk[2] = 1'b0;
    assign proc_11_output_sync_blk[2] = 1'b0 | (ap_done_reg_5 & Block_entry1426_proc_U0.ap_done & ~Block_entry1439_proc_U0.ap_done);
    assign proc_dep_vld_vec_11[2] = dl_detect_out ? proc_dep_vld_vec_11_reg[2] : (proc_11_data_FIFO_blk[2] | proc_11_data_PIPO_blk[2] | proc_11_start_FIFO_blk[2] | proc_11_TLF_FIFO_blk[2] | proc_11_input_sync_blk[2] | proc_11_output_sync_blk[2]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_11_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_11_reg <= proc_dep_vld_vec_11;
        end
    end
    assign in_chan_dep_vld_vec_11[0] = dep_chan_vld_23_11;
    assign in_chan_dep_data_vec_11[23 : 0] = dep_chan_data_23_11;
    assign token_in_vec_11[0] = token_23_11;
    assign dep_chan_vld_11_5 = out_chan_dep_vld_vec_11[0];
    assign dep_chan_data_11_5 = out_chan_dep_data_11;
    assign token_11_5 = token_out_vec_11[0];
    assign dep_chan_vld_11_10 = out_chan_dep_vld_vec_11[1];
    assign dep_chan_data_11_10 = out_chan_dep_data_11;
    assign token_11_10 = token_out_vec_11[1];
    assign dep_chan_vld_11_23 = out_chan_dep_vld_vec_11[2];
    assign dep_chan_data_11_23 = out_chan_dep_data_11;
    assign token_11_23 = token_out_vec_11[2];

    // Process: multiply_7_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 12, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_12 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_12),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_12),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_12),
        .token_in_vec(token_in_vec_12),
        .dl_detect_in(dl_detect_out),
        .origin(origin[12]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_12),
        .out_chan_dep_data(out_chan_dep_data_12),
        .token_out_vec(token_out_vec_12),
        .dl_detect_out(dl_in_vec[12]));

    assign proc_12_data_FIFO_blk[0] = 1'b0;
    assign proc_12_data_PIPO_blk[0] = 1'b0;
    assign proc_12_start_FIFO_blk[0] = 1'b0;
    assign proc_12_TLF_FIFO_blk[0] = 1'b0;
    assign proc_12_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_12_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_12[0] = dl_detect_out ? proc_dep_vld_vec_12_reg[0] : (proc_12_data_FIFO_blk[0] | proc_12_data_PIPO_blk[0] | proc_12_start_FIFO_blk[0] | proc_12_TLF_FIFO_blk[0] | proc_12_input_sync_blk[0] | proc_12_output_sync_blk[0]);
    assign proc_12_data_FIFO_blk[1] = 1'b0;
    assign proc_12_data_PIPO_blk[1] = 1'b0;
    assign proc_12_start_FIFO_blk[1] = 1'b0;
    assign proc_12_TLF_FIFO_blk[1] = 1'b0;
    assign proc_12_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_12_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_12[1] = dl_detect_out ? proc_dep_vld_vec_12_reg[1] : (proc_12_data_FIFO_blk[1] | proc_12_data_PIPO_blk[1] | proc_12_start_FIFO_blk[1] | proc_12_TLF_FIFO_blk[1] | proc_12_input_sync_blk[1] | proc_12_output_sync_blk[1]);
    assign proc_12_data_FIFO_blk[2] = 1'b0;
    assign proc_12_data_PIPO_blk[2] = 1'b0;
    assign proc_12_start_FIFO_blk[2] = 1'b0;
    assign proc_12_TLF_FIFO_blk[2] = 1'b0;
    assign proc_12_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_12_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_12[2] = dl_detect_out ? proc_dep_vld_vec_12_reg[2] : (proc_12_data_FIFO_blk[2] | proc_12_data_PIPO_blk[2] | proc_12_start_FIFO_blk[2] | proc_12_TLF_FIFO_blk[2] | proc_12_input_sync_blk[2] | proc_12_output_sync_blk[2]);
    assign proc_12_data_FIFO_blk[3] = 1'b0;
    assign proc_12_data_PIPO_blk[3] = 1'b0;
    assign proc_12_start_FIFO_blk[3] = 1'b0;
    assign proc_12_TLF_FIFO_blk[3] = 1'b0;
    assign proc_12_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_12_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_12[3] = dl_detect_out ? proc_dep_vld_vec_12_reg[3] : (proc_12_data_FIFO_blk[3] | proc_12_data_PIPO_blk[3] | proc_12_start_FIFO_blk[3] | proc_12_TLF_FIFO_blk[3] | proc_12_input_sync_blk[3] | proc_12_output_sync_blk[3]);
    assign proc_12_data_FIFO_blk[4] = 1'b0;
    assign proc_12_data_PIPO_blk[4] = 1'b0;
    assign proc_12_start_FIFO_blk[4] = 1'b0;
    assign proc_12_TLF_FIFO_blk[4] = 1'b0;
    assign proc_12_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_12_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_12[4] = dl_detect_out ? proc_dep_vld_vec_12_reg[4] : (proc_12_data_FIFO_blk[4] | proc_12_data_PIPO_blk[4] | proc_12_start_FIFO_blk[4] | proc_12_TLF_FIFO_blk[4] | proc_12_input_sync_blk[4] | proc_12_output_sync_blk[4]);
    assign proc_12_data_FIFO_blk[5] = 1'b0;
    assign proc_12_data_PIPO_blk[5] = 1'b0;
    assign proc_12_start_FIFO_blk[5] = 1'b0;
    assign proc_12_TLF_FIFO_blk[5] = 1'b0;
    assign proc_12_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_12_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_12[5] = dl_detect_out ? proc_dep_vld_vec_12_reg[5] : (proc_12_data_FIFO_blk[5] | proc_12_data_PIPO_blk[5] | proc_12_start_FIFO_blk[5] | proc_12_TLF_FIFO_blk[5] | proc_12_input_sync_blk[5] | proc_12_output_sync_blk[5]);
    assign proc_12_data_FIFO_blk[6] = 1'b0;
    assign proc_12_data_PIPO_blk[6] = 1'b0;
    assign proc_12_start_FIFO_blk[6] = 1'b0;
    assign proc_12_TLF_FIFO_blk[6] = 1'b0;
    assign proc_12_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_12_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_12[6] = dl_detect_out ? proc_dep_vld_vec_12_reg[6] : (proc_12_data_FIFO_blk[6] | proc_12_data_PIPO_blk[6] | proc_12_start_FIFO_blk[6] | proc_12_TLF_FIFO_blk[6] | proc_12_input_sync_blk[6] | proc_12_output_sync_blk[6]);
    assign proc_12_data_FIFO_blk[7] = 1'b0;
    assign proc_12_data_PIPO_blk[7] = 1'b0;
    assign proc_12_start_FIFO_blk[7] = 1'b0;
    assign proc_12_TLF_FIFO_blk[7] = 1'b0;
    assign proc_12_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_12_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_12[7] = dl_detect_out ? proc_dep_vld_vec_12_reg[7] : (proc_12_data_FIFO_blk[7] | proc_12_data_PIPO_blk[7] | proc_12_start_FIFO_blk[7] | proc_12_TLF_FIFO_blk[7] | proc_12_input_sync_blk[7] | proc_12_output_sync_blk[7]);
    assign proc_12_data_FIFO_blk[8] = 1'b0;
    assign proc_12_data_PIPO_blk[8] = 1'b0;
    assign proc_12_start_FIFO_blk[8] = 1'b0;
    assign proc_12_TLF_FIFO_blk[8] = 1'b0;
    assign proc_12_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_12_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_12[8] = dl_detect_out ? proc_dep_vld_vec_12_reg[8] : (proc_12_data_FIFO_blk[8] | proc_12_data_PIPO_blk[8] | proc_12_start_FIFO_blk[8] | proc_12_TLF_FIFO_blk[8] | proc_12_input_sync_blk[8] | proc_12_output_sync_blk[8]);
    assign proc_12_data_FIFO_blk[9] = 1'b0;
    assign proc_12_data_PIPO_blk[9] = 1'b0;
    assign proc_12_start_FIFO_blk[9] = 1'b0;
    assign proc_12_TLF_FIFO_blk[9] = 1'b0;
    assign proc_12_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_12_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_12[9] = dl_detect_out ? proc_dep_vld_vec_12_reg[9] : (proc_12_data_FIFO_blk[9] | proc_12_data_PIPO_blk[9] | proc_12_start_FIFO_blk[9] | proc_12_TLF_FIFO_blk[9] | proc_12_input_sync_blk[9] | proc_12_output_sync_blk[9]);
    assign proc_12_data_FIFO_blk[10] = 1'b0;
    assign proc_12_data_PIPO_blk[10] = 1'b0;
    assign proc_12_start_FIFO_blk[10] = 1'b0;
    assign proc_12_TLF_FIFO_blk[10] = 1'b0;
    assign proc_12_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_7_U0_ap_ready & multiply_7_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_12_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_12[10] = dl_detect_out ? proc_dep_vld_vec_12_reg[10] : (proc_12_data_FIFO_blk[10] | proc_12_data_PIPO_blk[10] | proc_12_start_FIFO_blk[10] | proc_12_TLF_FIFO_blk[10] | proc_12_input_sync_blk[10] | proc_12_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_12_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_12_reg <= proc_dep_vld_vec_12;
        end
    end
    assign in_chan_dep_vld_vec_12[0] = dep_chan_vld_0_12;
    assign in_chan_dep_data_vec_12[23 : 0] = dep_chan_data_0_12;
    assign token_in_vec_12[0] = token_0_12;
    assign in_chan_dep_vld_vec_12[1] = dep_chan_vld_1_12;
    assign in_chan_dep_data_vec_12[47 : 24] = dep_chan_data_1_12;
    assign token_in_vec_12[1] = token_1_12;
    assign in_chan_dep_vld_vec_12[2] = dep_chan_vld_2_12;
    assign in_chan_dep_data_vec_12[71 : 48] = dep_chan_data_2_12;
    assign token_in_vec_12[2] = token_2_12;
    assign in_chan_dep_vld_vec_12[3] = dep_chan_vld_3_12;
    assign in_chan_dep_data_vec_12[95 : 72] = dep_chan_data_3_12;
    assign token_in_vec_12[3] = token_3_12;
    assign in_chan_dep_vld_vec_12[4] = dep_chan_vld_4_12;
    assign in_chan_dep_data_vec_12[119 : 96] = dep_chan_data_4_12;
    assign token_in_vec_12[4] = token_4_12;
    assign in_chan_dep_vld_vec_12[5] = dep_chan_vld_5_12;
    assign in_chan_dep_data_vec_12[143 : 120] = dep_chan_data_5_12;
    assign token_in_vec_12[5] = token_5_12;
    assign in_chan_dep_vld_vec_12[6] = dep_chan_vld_13_12;
    assign in_chan_dep_data_vec_12[167 : 144] = dep_chan_data_13_12;
    assign token_in_vec_12[6] = token_13_12;
    assign in_chan_dep_vld_vec_12[7] = dep_chan_vld_14_12;
    assign in_chan_dep_data_vec_12[191 : 168] = dep_chan_data_14_12;
    assign token_in_vec_12[7] = token_14_12;
    assign in_chan_dep_vld_vec_12[8] = dep_chan_vld_15_12;
    assign in_chan_dep_data_vec_12[215 : 192] = dep_chan_data_15_12;
    assign token_in_vec_12[8] = token_15_12;
    assign in_chan_dep_vld_vec_12[9] = dep_chan_vld_16_12;
    assign in_chan_dep_data_vec_12[239 : 216] = dep_chan_data_16_12;
    assign token_in_vec_12[9] = token_16_12;
    assign in_chan_dep_vld_vec_12[10] = dep_chan_vld_17_12;
    assign in_chan_dep_data_vec_12[263 : 240] = dep_chan_data_17_12;
    assign token_in_vec_12[10] = token_17_12;
    assign in_chan_dep_vld_vec_12[11] = dep_chan_vld_18_12;
    assign in_chan_dep_data_vec_12[287 : 264] = dep_chan_data_18_12;
    assign token_in_vec_12[11] = token_18_12;
    assign dep_chan_vld_12_0 = out_chan_dep_vld_vec_12[0];
    assign dep_chan_data_12_0 = out_chan_dep_data_12;
    assign token_12_0 = token_out_vec_12[0];
    assign dep_chan_vld_12_1 = out_chan_dep_vld_vec_12[1];
    assign dep_chan_data_12_1 = out_chan_dep_data_12;
    assign token_12_1 = token_out_vec_12[1];
    assign dep_chan_vld_12_2 = out_chan_dep_vld_vec_12[2];
    assign dep_chan_data_12_2 = out_chan_dep_data_12;
    assign token_12_2 = token_out_vec_12[2];
    assign dep_chan_vld_12_3 = out_chan_dep_vld_vec_12[3];
    assign dep_chan_data_12_3 = out_chan_dep_data_12;
    assign token_12_3 = token_out_vec_12[3];
    assign dep_chan_vld_12_4 = out_chan_dep_vld_vec_12[4];
    assign dep_chan_data_12_4 = out_chan_dep_data_12;
    assign token_12_4 = token_out_vec_12[4];
    assign dep_chan_vld_12_5 = out_chan_dep_vld_vec_12[5];
    assign dep_chan_data_12_5 = out_chan_dep_data_12;
    assign token_12_5 = token_out_vec_12[5];
    assign dep_chan_vld_12_13 = out_chan_dep_vld_vec_12[6];
    assign dep_chan_data_12_13 = out_chan_dep_data_12;
    assign token_12_13 = token_out_vec_12[6];
    assign dep_chan_vld_12_14 = out_chan_dep_vld_vec_12[7];
    assign dep_chan_data_12_14 = out_chan_dep_data_12;
    assign token_12_14 = token_out_vec_12[7];
    assign dep_chan_vld_12_15 = out_chan_dep_vld_vec_12[8];
    assign dep_chan_data_12_15 = out_chan_dep_data_12;
    assign token_12_15 = token_out_vec_12[8];
    assign dep_chan_vld_12_16 = out_chan_dep_vld_vec_12[9];
    assign dep_chan_data_12_16 = out_chan_dep_data_12;
    assign token_12_16 = token_out_vec_12[9];
    assign dep_chan_vld_12_17 = out_chan_dep_vld_vec_12[10];
    assign dep_chan_data_12_17 = out_chan_dep_data_12;
    assign token_12_17 = token_out_vec_12[10];

    // Process: multiply_829_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 13, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_13 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_13),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_13),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_13),
        .token_in_vec(token_in_vec_13),
        .dl_detect_in(dl_detect_out),
        .origin(origin[13]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_13),
        .out_chan_dep_data(out_chan_dep_data_13),
        .token_out_vec(token_out_vec_13),
        .dl_detect_out(dl_in_vec[13]));

    assign proc_13_data_FIFO_blk[0] = 1'b0;
    assign proc_13_data_PIPO_blk[0] = 1'b0;
    assign proc_13_start_FIFO_blk[0] = 1'b0;
    assign proc_13_TLF_FIFO_blk[0] = 1'b0;
    assign proc_13_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_13_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_13[0] = dl_detect_out ? proc_dep_vld_vec_13_reg[0] : (proc_13_data_FIFO_blk[0] | proc_13_data_PIPO_blk[0] | proc_13_start_FIFO_blk[0] | proc_13_TLF_FIFO_blk[0] | proc_13_input_sync_blk[0] | proc_13_output_sync_blk[0]);
    assign proc_13_data_FIFO_blk[1] = 1'b0;
    assign proc_13_data_PIPO_blk[1] = 1'b0;
    assign proc_13_start_FIFO_blk[1] = 1'b0;
    assign proc_13_TLF_FIFO_blk[1] = 1'b0;
    assign proc_13_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_13_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_13[1] = dl_detect_out ? proc_dep_vld_vec_13_reg[1] : (proc_13_data_FIFO_blk[1] | proc_13_data_PIPO_blk[1] | proc_13_start_FIFO_blk[1] | proc_13_TLF_FIFO_blk[1] | proc_13_input_sync_blk[1] | proc_13_output_sync_blk[1]);
    assign proc_13_data_FIFO_blk[2] = 1'b0;
    assign proc_13_data_PIPO_blk[2] = 1'b0;
    assign proc_13_start_FIFO_blk[2] = 1'b0;
    assign proc_13_TLF_FIFO_blk[2] = 1'b0;
    assign proc_13_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_13_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_13[2] = dl_detect_out ? proc_dep_vld_vec_13_reg[2] : (proc_13_data_FIFO_blk[2] | proc_13_data_PIPO_blk[2] | proc_13_start_FIFO_blk[2] | proc_13_TLF_FIFO_blk[2] | proc_13_input_sync_blk[2] | proc_13_output_sync_blk[2]);
    assign proc_13_data_FIFO_blk[3] = 1'b0;
    assign proc_13_data_PIPO_blk[3] = 1'b0;
    assign proc_13_start_FIFO_blk[3] = 1'b0;
    assign proc_13_TLF_FIFO_blk[3] = 1'b0;
    assign proc_13_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_13_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_13[3] = dl_detect_out ? proc_dep_vld_vec_13_reg[3] : (proc_13_data_FIFO_blk[3] | proc_13_data_PIPO_blk[3] | proc_13_start_FIFO_blk[3] | proc_13_TLF_FIFO_blk[3] | proc_13_input_sync_blk[3] | proc_13_output_sync_blk[3]);
    assign proc_13_data_FIFO_blk[4] = 1'b0;
    assign proc_13_data_PIPO_blk[4] = 1'b0;
    assign proc_13_start_FIFO_blk[4] = 1'b0;
    assign proc_13_TLF_FIFO_blk[4] = 1'b0;
    assign proc_13_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_13_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_13[4] = dl_detect_out ? proc_dep_vld_vec_13_reg[4] : (proc_13_data_FIFO_blk[4] | proc_13_data_PIPO_blk[4] | proc_13_start_FIFO_blk[4] | proc_13_TLF_FIFO_blk[4] | proc_13_input_sync_blk[4] | proc_13_output_sync_blk[4]);
    assign proc_13_data_FIFO_blk[5] = 1'b0;
    assign proc_13_data_PIPO_blk[5] = 1'b0;
    assign proc_13_start_FIFO_blk[5] = 1'b0;
    assign proc_13_TLF_FIFO_blk[5] = 1'b0;
    assign proc_13_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_13_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_13[5] = dl_detect_out ? proc_dep_vld_vec_13_reg[5] : (proc_13_data_FIFO_blk[5] | proc_13_data_PIPO_blk[5] | proc_13_start_FIFO_blk[5] | proc_13_TLF_FIFO_blk[5] | proc_13_input_sync_blk[5] | proc_13_output_sync_blk[5]);
    assign proc_13_data_FIFO_blk[6] = 1'b0;
    assign proc_13_data_PIPO_blk[6] = 1'b0;
    assign proc_13_start_FIFO_blk[6] = 1'b0;
    assign proc_13_TLF_FIFO_blk[6] = 1'b0;
    assign proc_13_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_13_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_13[6] = dl_detect_out ? proc_dep_vld_vec_13_reg[6] : (proc_13_data_FIFO_blk[6] | proc_13_data_PIPO_blk[6] | proc_13_start_FIFO_blk[6] | proc_13_TLF_FIFO_blk[6] | proc_13_input_sync_blk[6] | proc_13_output_sync_blk[6]);
    assign proc_13_data_FIFO_blk[7] = 1'b0;
    assign proc_13_data_PIPO_blk[7] = 1'b0;
    assign proc_13_start_FIFO_blk[7] = 1'b0;
    assign proc_13_TLF_FIFO_blk[7] = 1'b0;
    assign proc_13_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_13_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_13[7] = dl_detect_out ? proc_dep_vld_vec_13_reg[7] : (proc_13_data_FIFO_blk[7] | proc_13_data_PIPO_blk[7] | proc_13_start_FIFO_blk[7] | proc_13_TLF_FIFO_blk[7] | proc_13_input_sync_blk[7] | proc_13_output_sync_blk[7]);
    assign proc_13_data_FIFO_blk[8] = 1'b0;
    assign proc_13_data_PIPO_blk[8] = 1'b0;
    assign proc_13_start_FIFO_blk[8] = 1'b0;
    assign proc_13_TLF_FIFO_blk[8] = 1'b0;
    assign proc_13_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_13_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_13[8] = dl_detect_out ? proc_dep_vld_vec_13_reg[8] : (proc_13_data_FIFO_blk[8] | proc_13_data_PIPO_blk[8] | proc_13_start_FIFO_blk[8] | proc_13_TLF_FIFO_blk[8] | proc_13_input_sync_blk[8] | proc_13_output_sync_blk[8]);
    assign proc_13_data_FIFO_blk[9] = 1'b0;
    assign proc_13_data_PIPO_blk[9] = 1'b0;
    assign proc_13_start_FIFO_blk[9] = 1'b0;
    assign proc_13_TLF_FIFO_blk[9] = 1'b0;
    assign proc_13_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_13_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_13[9] = dl_detect_out ? proc_dep_vld_vec_13_reg[9] : (proc_13_data_FIFO_blk[9] | proc_13_data_PIPO_blk[9] | proc_13_start_FIFO_blk[9] | proc_13_TLF_FIFO_blk[9] | proc_13_input_sync_blk[9] | proc_13_output_sync_blk[9]);
    assign proc_13_data_FIFO_blk[10] = 1'b0;
    assign proc_13_data_PIPO_blk[10] = 1'b0;
    assign proc_13_start_FIFO_blk[10] = 1'b0;
    assign proc_13_TLF_FIFO_blk[10] = 1'b0;
    assign proc_13_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_829_U0_ap_ready & multiply_829_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_13_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_13[10] = dl_detect_out ? proc_dep_vld_vec_13_reg[10] : (proc_13_data_FIFO_blk[10] | proc_13_data_PIPO_blk[10] | proc_13_start_FIFO_blk[10] | proc_13_TLF_FIFO_blk[10] | proc_13_input_sync_blk[10] | proc_13_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_13_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_13_reg <= proc_dep_vld_vec_13;
        end
    end
    assign in_chan_dep_vld_vec_13[0] = dep_chan_vld_0_13;
    assign in_chan_dep_data_vec_13[23 : 0] = dep_chan_data_0_13;
    assign token_in_vec_13[0] = token_0_13;
    assign in_chan_dep_vld_vec_13[1] = dep_chan_vld_1_13;
    assign in_chan_dep_data_vec_13[47 : 24] = dep_chan_data_1_13;
    assign token_in_vec_13[1] = token_1_13;
    assign in_chan_dep_vld_vec_13[2] = dep_chan_vld_2_13;
    assign in_chan_dep_data_vec_13[71 : 48] = dep_chan_data_2_13;
    assign token_in_vec_13[2] = token_2_13;
    assign in_chan_dep_vld_vec_13[3] = dep_chan_vld_3_13;
    assign in_chan_dep_data_vec_13[95 : 72] = dep_chan_data_3_13;
    assign token_in_vec_13[3] = token_3_13;
    assign in_chan_dep_vld_vec_13[4] = dep_chan_vld_4_13;
    assign in_chan_dep_data_vec_13[119 : 96] = dep_chan_data_4_13;
    assign token_in_vec_13[4] = token_4_13;
    assign in_chan_dep_vld_vec_13[5] = dep_chan_vld_5_13;
    assign in_chan_dep_data_vec_13[143 : 120] = dep_chan_data_5_13;
    assign token_in_vec_13[5] = token_5_13;
    assign in_chan_dep_vld_vec_13[6] = dep_chan_vld_12_13;
    assign in_chan_dep_data_vec_13[167 : 144] = dep_chan_data_12_13;
    assign token_in_vec_13[6] = token_12_13;
    assign in_chan_dep_vld_vec_13[7] = dep_chan_vld_14_13;
    assign in_chan_dep_data_vec_13[191 : 168] = dep_chan_data_14_13;
    assign token_in_vec_13[7] = token_14_13;
    assign in_chan_dep_vld_vec_13[8] = dep_chan_vld_15_13;
    assign in_chan_dep_data_vec_13[215 : 192] = dep_chan_data_15_13;
    assign token_in_vec_13[8] = token_15_13;
    assign in_chan_dep_vld_vec_13[9] = dep_chan_vld_16_13;
    assign in_chan_dep_data_vec_13[239 : 216] = dep_chan_data_16_13;
    assign token_in_vec_13[9] = token_16_13;
    assign in_chan_dep_vld_vec_13[10] = dep_chan_vld_17_13;
    assign in_chan_dep_data_vec_13[263 : 240] = dep_chan_data_17_13;
    assign token_in_vec_13[10] = token_17_13;
    assign in_chan_dep_vld_vec_13[11] = dep_chan_vld_19_13;
    assign in_chan_dep_data_vec_13[287 : 264] = dep_chan_data_19_13;
    assign token_in_vec_13[11] = token_19_13;
    assign dep_chan_vld_13_0 = out_chan_dep_vld_vec_13[0];
    assign dep_chan_data_13_0 = out_chan_dep_data_13;
    assign token_13_0 = token_out_vec_13[0];
    assign dep_chan_vld_13_1 = out_chan_dep_vld_vec_13[1];
    assign dep_chan_data_13_1 = out_chan_dep_data_13;
    assign token_13_1 = token_out_vec_13[1];
    assign dep_chan_vld_13_2 = out_chan_dep_vld_vec_13[2];
    assign dep_chan_data_13_2 = out_chan_dep_data_13;
    assign token_13_2 = token_out_vec_13[2];
    assign dep_chan_vld_13_3 = out_chan_dep_vld_vec_13[3];
    assign dep_chan_data_13_3 = out_chan_dep_data_13;
    assign token_13_3 = token_out_vec_13[3];
    assign dep_chan_vld_13_4 = out_chan_dep_vld_vec_13[4];
    assign dep_chan_data_13_4 = out_chan_dep_data_13;
    assign token_13_4 = token_out_vec_13[4];
    assign dep_chan_vld_13_5 = out_chan_dep_vld_vec_13[5];
    assign dep_chan_data_13_5 = out_chan_dep_data_13;
    assign token_13_5 = token_out_vec_13[5];
    assign dep_chan_vld_13_12 = out_chan_dep_vld_vec_13[6];
    assign dep_chan_data_13_12 = out_chan_dep_data_13;
    assign token_13_12 = token_out_vec_13[6];
    assign dep_chan_vld_13_14 = out_chan_dep_vld_vec_13[7];
    assign dep_chan_data_13_14 = out_chan_dep_data_13;
    assign token_13_14 = token_out_vec_13[7];
    assign dep_chan_vld_13_15 = out_chan_dep_vld_vec_13[8];
    assign dep_chan_data_13_15 = out_chan_dep_data_13;
    assign token_13_15 = token_out_vec_13[8];
    assign dep_chan_vld_13_16 = out_chan_dep_vld_vec_13[9];
    assign dep_chan_data_13_16 = out_chan_dep_data_13;
    assign token_13_16 = token_out_vec_13[9];
    assign dep_chan_vld_13_17 = out_chan_dep_vld_vec_13[10];
    assign dep_chan_data_13_17 = out_chan_dep_data_13;
    assign token_13_17 = token_out_vec_13[10];

    // Process: multiply_930_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 14, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_14 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_14),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_14),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_14),
        .token_in_vec(token_in_vec_14),
        .dl_detect_in(dl_detect_out),
        .origin(origin[14]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_14),
        .out_chan_dep_data(out_chan_dep_data_14),
        .token_out_vec(token_out_vec_14),
        .dl_detect_out(dl_in_vec[14]));

    assign proc_14_data_FIFO_blk[0] = 1'b0;
    assign proc_14_data_PIPO_blk[0] = 1'b0;
    assign proc_14_start_FIFO_blk[0] = 1'b0;
    assign proc_14_TLF_FIFO_blk[0] = 1'b0;
    assign proc_14_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_14_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_14[0] = dl_detect_out ? proc_dep_vld_vec_14_reg[0] : (proc_14_data_FIFO_blk[0] | proc_14_data_PIPO_blk[0] | proc_14_start_FIFO_blk[0] | proc_14_TLF_FIFO_blk[0] | proc_14_input_sync_blk[0] | proc_14_output_sync_blk[0]);
    assign proc_14_data_FIFO_blk[1] = 1'b0;
    assign proc_14_data_PIPO_blk[1] = 1'b0;
    assign proc_14_start_FIFO_blk[1] = 1'b0;
    assign proc_14_TLF_FIFO_blk[1] = 1'b0;
    assign proc_14_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_14_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_14[1] = dl_detect_out ? proc_dep_vld_vec_14_reg[1] : (proc_14_data_FIFO_blk[1] | proc_14_data_PIPO_blk[1] | proc_14_start_FIFO_blk[1] | proc_14_TLF_FIFO_blk[1] | proc_14_input_sync_blk[1] | proc_14_output_sync_blk[1]);
    assign proc_14_data_FIFO_blk[2] = 1'b0;
    assign proc_14_data_PIPO_blk[2] = 1'b0;
    assign proc_14_start_FIFO_blk[2] = 1'b0;
    assign proc_14_TLF_FIFO_blk[2] = 1'b0;
    assign proc_14_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_14_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_14[2] = dl_detect_out ? proc_dep_vld_vec_14_reg[2] : (proc_14_data_FIFO_blk[2] | proc_14_data_PIPO_blk[2] | proc_14_start_FIFO_blk[2] | proc_14_TLF_FIFO_blk[2] | proc_14_input_sync_blk[2] | proc_14_output_sync_blk[2]);
    assign proc_14_data_FIFO_blk[3] = 1'b0;
    assign proc_14_data_PIPO_blk[3] = 1'b0;
    assign proc_14_start_FIFO_blk[3] = 1'b0;
    assign proc_14_TLF_FIFO_blk[3] = 1'b0;
    assign proc_14_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_14_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_14[3] = dl_detect_out ? proc_dep_vld_vec_14_reg[3] : (proc_14_data_FIFO_blk[3] | proc_14_data_PIPO_blk[3] | proc_14_start_FIFO_blk[3] | proc_14_TLF_FIFO_blk[3] | proc_14_input_sync_blk[3] | proc_14_output_sync_blk[3]);
    assign proc_14_data_FIFO_blk[4] = 1'b0;
    assign proc_14_data_PIPO_blk[4] = 1'b0;
    assign proc_14_start_FIFO_blk[4] = 1'b0;
    assign proc_14_TLF_FIFO_blk[4] = 1'b0;
    assign proc_14_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_14_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_14[4] = dl_detect_out ? proc_dep_vld_vec_14_reg[4] : (proc_14_data_FIFO_blk[4] | proc_14_data_PIPO_blk[4] | proc_14_start_FIFO_blk[4] | proc_14_TLF_FIFO_blk[4] | proc_14_input_sync_blk[4] | proc_14_output_sync_blk[4]);
    assign proc_14_data_FIFO_blk[5] = 1'b0;
    assign proc_14_data_PIPO_blk[5] = 1'b0;
    assign proc_14_start_FIFO_blk[5] = 1'b0;
    assign proc_14_TLF_FIFO_blk[5] = 1'b0;
    assign proc_14_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_14_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_14[5] = dl_detect_out ? proc_dep_vld_vec_14_reg[5] : (proc_14_data_FIFO_blk[5] | proc_14_data_PIPO_blk[5] | proc_14_start_FIFO_blk[5] | proc_14_TLF_FIFO_blk[5] | proc_14_input_sync_blk[5] | proc_14_output_sync_blk[5]);
    assign proc_14_data_FIFO_blk[6] = 1'b0;
    assign proc_14_data_PIPO_blk[6] = 1'b0;
    assign proc_14_start_FIFO_blk[6] = 1'b0;
    assign proc_14_TLF_FIFO_blk[6] = 1'b0;
    assign proc_14_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_14_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_14[6] = dl_detect_out ? proc_dep_vld_vec_14_reg[6] : (proc_14_data_FIFO_blk[6] | proc_14_data_PIPO_blk[6] | proc_14_start_FIFO_blk[6] | proc_14_TLF_FIFO_blk[6] | proc_14_input_sync_blk[6] | proc_14_output_sync_blk[6]);
    assign proc_14_data_FIFO_blk[7] = 1'b0;
    assign proc_14_data_PIPO_blk[7] = 1'b0;
    assign proc_14_start_FIFO_blk[7] = 1'b0;
    assign proc_14_TLF_FIFO_blk[7] = 1'b0;
    assign proc_14_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_14_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_14[7] = dl_detect_out ? proc_dep_vld_vec_14_reg[7] : (proc_14_data_FIFO_blk[7] | proc_14_data_PIPO_blk[7] | proc_14_start_FIFO_blk[7] | proc_14_TLF_FIFO_blk[7] | proc_14_input_sync_blk[7] | proc_14_output_sync_blk[7]);
    assign proc_14_data_FIFO_blk[8] = 1'b0;
    assign proc_14_data_PIPO_blk[8] = 1'b0;
    assign proc_14_start_FIFO_blk[8] = 1'b0;
    assign proc_14_TLF_FIFO_blk[8] = 1'b0;
    assign proc_14_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_14_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_14[8] = dl_detect_out ? proc_dep_vld_vec_14_reg[8] : (proc_14_data_FIFO_blk[8] | proc_14_data_PIPO_blk[8] | proc_14_start_FIFO_blk[8] | proc_14_TLF_FIFO_blk[8] | proc_14_input_sync_blk[8] | proc_14_output_sync_blk[8]);
    assign proc_14_data_FIFO_blk[9] = 1'b0;
    assign proc_14_data_PIPO_blk[9] = 1'b0;
    assign proc_14_start_FIFO_blk[9] = 1'b0;
    assign proc_14_TLF_FIFO_blk[9] = 1'b0;
    assign proc_14_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_14_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_14[9] = dl_detect_out ? proc_dep_vld_vec_14_reg[9] : (proc_14_data_FIFO_blk[9] | proc_14_data_PIPO_blk[9] | proc_14_start_FIFO_blk[9] | proc_14_TLF_FIFO_blk[9] | proc_14_input_sync_blk[9] | proc_14_output_sync_blk[9]);
    assign proc_14_data_FIFO_blk[10] = 1'b0;
    assign proc_14_data_PIPO_blk[10] = 1'b0;
    assign proc_14_start_FIFO_blk[10] = 1'b0;
    assign proc_14_TLF_FIFO_blk[10] = 1'b0;
    assign proc_14_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_930_U0_ap_ready & multiply_930_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_14_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_14[10] = dl_detect_out ? proc_dep_vld_vec_14_reg[10] : (proc_14_data_FIFO_blk[10] | proc_14_data_PIPO_blk[10] | proc_14_start_FIFO_blk[10] | proc_14_TLF_FIFO_blk[10] | proc_14_input_sync_blk[10] | proc_14_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_14_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_14_reg <= proc_dep_vld_vec_14;
        end
    end
    assign in_chan_dep_vld_vec_14[0] = dep_chan_vld_0_14;
    assign in_chan_dep_data_vec_14[23 : 0] = dep_chan_data_0_14;
    assign token_in_vec_14[0] = token_0_14;
    assign in_chan_dep_vld_vec_14[1] = dep_chan_vld_1_14;
    assign in_chan_dep_data_vec_14[47 : 24] = dep_chan_data_1_14;
    assign token_in_vec_14[1] = token_1_14;
    assign in_chan_dep_vld_vec_14[2] = dep_chan_vld_2_14;
    assign in_chan_dep_data_vec_14[71 : 48] = dep_chan_data_2_14;
    assign token_in_vec_14[2] = token_2_14;
    assign in_chan_dep_vld_vec_14[3] = dep_chan_vld_3_14;
    assign in_chan_dep_data_vec_14[95 : 72] = dep_chan_data_3_14;
    assign token_in_vec_14[3] = token_3_14;
    assign in_chan_dep_vld_vec_14[4] = dep_chan_vld_4_14;
    assign in_chan_dep_data_vec_14[119 : 96] = dep_chan_data_4_14;
    assign token_in_vec_14[4] = token_4_14;
    assign in_chan_dep_vld_vec_14[5] = dep_chan_vld_5_14;
    assign in_chan_dep_data_vec_14[143 : 120] = dep_chan_data_5_14;
    assign token_in_vec_14[5] = token_5_14;
    assign in_chan_dep_vld_vec_14[6] = dep_chan_vld_12_14;
    assign in_chan_dep_data_vec_14[167 : 144] = dep_chan_data_12_14;
    assign token_in_vec_14[6] = token_12_14;
    assign in_chan_dep_vld_vec_14[7] = dep_chan_vld_13_14;
    assign in_chan_dep_data_vec_14[191 : 168] = dep_chan_data_13_14;
    assign token_in_vec_14[7] = token_13_14;
    assign in_chan_dep_vld_vec_14[8] = dep_chan_vld_15_14;
    assign in_chan_dep_data_vec_14[215 : 192] = dep_chan_data_15_14;
    assign token_in_vec_14[8] = token_15_14;
    assign in_chan_dep_vld_vec_14[9] = dep_chan_vld_16_14;
    assign in_chan_dep_data_vec_14[239 : 216] = dep_chan_data_16_14;
    assign token_in_vec_14[9] = token_16_14;
    assign in_chan_dep_vld_vec_14[10] = dep_chan_vld_17_14;
    assign in_chan_dep_data_vec_14[263 : 240] = dep_chan_data_17_14;
    assign token_in_vec_14[10] = token_17_14;
    assign in_chan_dep_vld_vec_14[11] = dep_chan_vld_20_14;
    assign in_chan_dep_data_vec_14[287 : 264] = dep_chan_data_20_14;
    assign token_in_vec_14[11] = token_20_14;
    assign dep_chan_vld_14_0 = out_chan_dep_vld_vec_14[0];
    assign dep_chan_data_14_0 = out_chan_dep_data_14;
    assign token_14_0 = token_out_vec_14[0];
    assign dep_chan_vld_14_1 = out_chan_dep_vld_vec_14[1];
    assign dep_chan_data_14_1 = out_chan_dep_data_14;
    assign token_14_1 = token_out_vec_14[1];
    assign dep_chan_vld_14_2 = out_chan_dep_vld_vec_14[2];
    assign dep_chan_data_14_2 = out_chan_dep_data_14;
    assign token_14_2 = token_out_vec_14[2];
    assign dep_chan_vld_14_3 = out_chan_dep_vld_vec_14[3];
    assign dep_chan_data_14_3 = out_chan_dep_data_14;
    assign token_14_3 = token_out_vec_14[3];
    assign dep_chan_vld_14_4 = out_chan_dep_vld_vec_14[4];
    assign dep_chan_data_14_4 = out_chan_dep_data_14;
    assign token_14_4 = token_out_vec_14[4];
    assign dep_chan_vld_14_5 = out_chan_dep_vld_vec_14[5];
    assign dep_chan_data_14_5 = out_chan_dep_data_14;
    assign token_14_5 = token_out_vec_14[5];
    assign dep_chan_vld_14_12 = out_chan_dep_vld_vec_14[6];
    assign dep_chan_data_14_12 = out_chan_dep_data_14;
    assign token_14_12 = token_out_vec_14[6];
    assign dep_chan_vld_14_13 = out_chan_dep_vld_vec_14[7];
    assign dep_chan_data_14_13 = out_chan_dep_data_14;
    assign token_14_13 = token_out_vec_14[7];
    assign dep_chan_vld_14_15 = out_chan_dep_vld_vec_14[8];
    assign dep_chan_data_14_15 = out_chan_dep_data_14;
    assign token_14_15 = token_out_vec_14[8];
    assign dep_chan_vld_14_16 = out_chan_dep_vld_vec_14[9];
    assign dep_chan_data_14_16 = out_chan_dep_data_14;
    assign token_14_16 = token_out_vec_14[9];
    assign dep_chan_vld_14_17 = out_chan_dep_vld_vec_14[10];
    assign dep_chan_data_14_17 = out_chan_dep_data_14;
    assign token_14_17 = token_out_vec_14[10];

    // Process: multiply_1031_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 15, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_15 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_15),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_15),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_15),
        .token_in_vec(token_in_vec_15),
        .dl_detect_in(dl_detect_out),
        .origin(origin[15]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_15),
        .out_chan_dep_data(out_chan_dep_data_15),
        .token_out_vec(token_out_vec_15),
        .dl_detect_out(dl_in_vec[15]));

    assign proc_15_data_FIFO_blk[0] = 1'b0;
    assign proc_15_data_PIPO_blk[0] = 1'b0;
    assign proc_15_start_FIFO_blk[0] = 1'b0;
    assign proc_15_TLF_FIFO_blk[0] = 1'b0;
    assign proc_15_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_15_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_15[0] = dl_detect_out ? proc_dep_vld_vec_15_reg[0] : (proc_15_data_FIFO_blk[0] | proc_15_data_PIPO_blk[0] | proc_15_start_FIFO_blk[0] | proc_15_TLF_FIFO_blk[0] | proc_15_input_sync_blk[0] | proc_15_output_sync_blk[0]);
    assign proc_15_data_FIFO_blk[1] = 1'b0;
    assign proc_15_data_PIPO_blk[1] = 1'b0;
    assign proc_15_start_FIFO_blk[1] = 1'b0;
    assign proc_15_TLF_FIFO_blk[1] = 1'b0;
    assign proc_15_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_15_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_15[1] = dl_detect_out ? proc_dep_vld_vec_15_reg[1] : (proc_15_data_FIFO_blk[1] | proc_15_data_PIPO_blk[1] | proc_15_start_FIFO_blk[1] | proc_15_TLF_FIFO_blk[1] | proc_15_input_sync_blk[1] | proc_15_output_sync_blk[1]);
    assign proc_15_data_FIFO_blk[2] = 1'b0;
    assign proc_15_data_PIPO_blk[2] = 1'b0;
    assign proc_15_start_FIFO_blk[2] = 1'b0;
    assign proc_15_TLF_FIFO_blk[2] = 1'b0;
    assign proc_15_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_15_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_15[2] = dl_detect_out ? proc_dep_vld_vec_15_reg[2] : (proc_15_data_FIFO_blk[2] | proc_15_data_PIPO_blk[2] | proc_15_start_FIFO_blk[2] | proc_15_TLF_FIFO_blk[2] | proc_15_input_sync_blk[2] | proc_15_output_sync_blk[2]);
    assign proc_15_data_FIFO_blk[3] = 1'b0;
    assign proc_15_data_PIPO_blk[3] = 1'b0;
    assign proc_15_start_FIFO_blk[3] = 1'b0;
    assign proc_15_TLF_FIFO_blk[3] = 1'b0;
    assign proc_15_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_15_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_15[3] = dl_detect_out ? proc_dep_vld_vec_15_reg[3] : (proc_15_data_FIFO_blk[3] | proc_15_data_PIPO_blk[3] | proc_15_start_FIFO_blk[3] | proc_15_TLF_FIFO_blk[3] | proc_15_input_sync_blk[3] | proc_15_output_sync_blk[3]);
    assign proc_15_data_FIFO_blk[4] = 1'b0;
    assign proc_15_data_PIPO_blk[4] = 1'b0;
    assign proc_15_start_FIFO_blk[4] = 1'b0;
    assign proc_15_TLF_FIFO_blk[4] = 1'b0;
    assign proc_15_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_15_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_15[4] = dl_detect_out ? proc_dep_vld_vec_15_reg[4] : (proc_15_data_FIFO_blk[4] | proc_15_data_PIPO_blk[4] | proc_15_start_FIFO_blk[4] | proc_15_TLF_FIFO_blk[4] | proc_15_input_sync_blk[4] | proc_15_output_sync_blk[4]);
    assign proc_15_data_FIFO_blk[5] = 1'b0;
    assign proc_15_data_PIPO_blk[5] = 1'b0;
    assign proc_15_start_FIFO_blk[5] = 1'b0;
    assign proc_15_TLF_FIFO_blk[5] = 1'b0;
    assign proc_15_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_15_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_15[5] = dl_detect_out ? proc_dep_vld_vec_15_reg[5] : (proc_15_data_FIFO_blk[5] | proc_15_data_PIPO_blk[5] | proc_15_start_FIFO_blk[5] | proc_15_TLF_FIFO_blk[5] | proc_15_input_sync_blk[5] | proc_15_output_sync_blk[5]);
    assign proc_15_data_FIFO_blk[6] = 1'b0;
    assign proc_15_data_PIPO_blk[6] = 1'b0;
    assign proc_15_start_FIFO_blk[6] = 1'b0;
    assign proc_15_TLF_FIFO_blk[6] = 1'b0;
    assign proc_15_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_15_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_15[6] = dl_detect_out ? proc_dep_vld_vec_15_reg[6] : (proc_15_data_FIFO_blk[6] | proc_15_data_PIPO_blk[6] | proc_15_start_FIFO_blk[6] | proc_15_TLF_FIFO_blk[6] | proc_15_input_sync_blk[6] | proc_15_output_sync_blk[6]);
    assign proc_15_data_FIFO_blk[7] = 1'b0;
    assign proc_15_data_PIPO_blk[7] = 1'b0;
    assign proc_15_start_FIFO_blk[7] = 1'b0;
    assign proc_15_TLF_FIFO_blk[7] = 1'b0;
    assign proc_15_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_15_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_15[7] = dl_detect_out ? proc_dep_vld_vec_15_reg[7] : (proc_15_data_FIFO_blk[7] | proc_15_data_PIPO_blk[7] | proc_15_start_FIFO_blk[7] | proc_15_TLF_FIFO_blk[7] | proc_15_input_sync_blk[7] | proc_15_output_sync_blk[7]);
    assign proc_15_data_FIFO_blk[8] = 1'b0;
    assign proc_15_data_PIPO_blk[8] = 1'b0;
    assign proc_15_start_FIFO_blk[8] = 1'b0;
    assign proc_15_TLF_FIFO_blk[8] = 1'b0;
    assign proc_15_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_15_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_15[8] = dl_detect_out ? proc_dep_vld_vec_15_reg[8] : (proc_15_data_FIFO_blk[8] | proc_15_data_PIPO_blk[8] | proc_15_start_FIFO_blk[8] | proc_15_TLF_FIFO_blk[8] | proc_15_input_sync_blk[8] | proc_15_output_sync_blk[8]);
    assign proc_15_data_FIFO_blk[9] = 1'b0;
    assign proc_15_data_PIPO_blk[9] = 1'b0;
    assign proc_15_start_FIFO_blk[9] = 1'b0;
    assign proc_15_TLF_FIFO_blk[9] = 1'b0;
    assign proc_15_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_15_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_15[9] = dl_detect_out ? proc_dep_vld_vec_15_reg[9] : (proc_15_data_FIFO_blk[9] | proc_15_data_PIPO_blk[9] | proc_15_start_FIFO_blk[9] | proc_15_TLF_FIFO_blk[9] | proc_15_input_sync_blk[9] | proc_15_output_sync_blk[9]);
    assign proc_15_data_FIFO_blk[10] = 1'b0;
    assign proc_15_data_PIPO_blk[10] = 1'b0;
    assign proc_15_start_FIFO_blk[10] = 1'b0;
    assign proc_15_TLF_FIFO_blk[10] = 1'b0;
    assign proc_15_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_1031_U0_ap_ready & multiply_1031_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_15_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_15[10] = dl_detect_out ? proc_dep_vld_vec_15_reg[10] : (proc_15_data_FIFO_blk[10] | proc_15_data_PIPO_blk[10] | proc_15_start_FIFO_blk[10] | proc_15_TLF_FIFO_blk[10] | proc_15_input_sync_blk[10] | proc_15_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_15_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_15_reg <= proc_dep_vld_vec_15;
        end
    end
    assign in_chan_dep_vld_vec_15[0] = dep_chan_vld_0_15;
    assign in_chan_dep_data_vec_15[23 : 0] = dep_chan_data_0_15;
    assign token_in_vec_15[0] = token_0_15;
    assign in_chan_dep_vld_vec_15[1] = dep_chan_vld_1_15;
    assign in_chan_dep_data_vec_15[47 : 24] = dep_chan_data_1_15;
    assign token_in_vec_15[1] = token_1_15;
    assign in_chan_dep_vld_vec_15[2] = dep_chan_vld_2_15;
    assign in_chan_dep_data_vec_15[71 : 48] = dep_chan_data_2_15;
    assign token_in_vec_15[2] = token_2_15;
    assign in_chan_dep_vld_vec_15[3] = dep_chan_vld_3_15;
    assign in_chan_dep_data_vec_15[95 : 72] = dep_chan_data_3_15;
    assign token_in_vec_15[3] = token_3_15;
    assign in_chan_dep_vld_vec_15[4] = dep_chan_vld_4_15;
    assign in_chan_dep_data_vec_15[119 : 96] = dep_chan_data_4_15;
    assign token_in_vec_15[4] = token_4_15;
    assign in_chan_dep_vld_vec_15[5] = dep_chan_vld_5_15;
    assign in_chan_dep_data_vec_15[143 : 120] = dep_chan_data_5_15;
    assign token_in_vec_15[5] = token_5_15;
    assign in_chan_dep_vld_vec_15[6] = dep_chan_vld_12_15;
    assign in_chan_dep_data_vec_15[167 : 144] = dep_chan_data_12_15;
    assign token_in_vec_15[6] = token_12_15;
    assign in_chan_dep_vld_vec_15[7] = dep_chan_vld_13_15;
    assign in_chan_dep_data_vec_15[191 : 168] = dep_chan_data_13_15;
    assign token_in_vec_15[7] = token_13_15;
    assign in_chan_dep_vld_vec_15[8] = dep_chan_vld_14_15;
    assign in_chan_dep_data_vec_15[215 : 192] = dep_chan_data_14_15;
    assign token_in_vec_15[8] = token_14_15;
    assign in_chan_dep_vld_vec_15[9] = dep_chan_vld_16_15;
    assign in_chan_dep_data_vec_15[239 : 216] = dep_chan_data_16_15;
    assign token_in_vec_15[9] = token_16_15;
    assign in_chan_dep_vld_vec_15[10] = dep_chan_vld_17_15;
    assign in_chan_dep_data_vec_15[263 : 240] = dep_chan_data_17_15;
    assign token_in_vec_15[10] = token_17_15;
    assign in_chan_dep_vld_vec_15[11] = dep_chan_vld_21_15;
    assign in_chan_dep_data_vec_15[287 : 264] = dep_chan_data_21_15;
    assign token_in_vec_15[11] = token_21_15;
    assign dep_chan_vld_15_0 = out_chan_dep_vld_vec_15[0];
    assign dep_chan_data_15_0 = out_chan_dep_data_15;
    assign token_15_0 = token_out_vec_15[0];
    assign dep_chan_vld_15_1 = out_chan_dep_vld_vec_15[1];
    assign dep_chan_data_15_1 = out_chan_dep_data_15;
    assign token_15_1 = token_out_vec_15[1];
    assign dep_chan_vld_15_2 = out_chan_dep_vld_vec_15[2];
    assign dep_chan_data_15_2 = out_chan_dep_data_15;
    assign token_15_2 = token_out_vec_15[2];
    assign dep_chan_vld_15_3 = out_chan_dep_vld_vec_15[3];
    assign dep_chan_data_15_3 = out_chan_dep_data_15;
    assign token_15_3 = token_out_vec_15[3];
    assign dep_chan_vld_15_4 = out_chan_dep_vld_vec_15[4];
    assign dep_chan_data_15_4 = out_chan_dep_data_15;
    assign token_15_4 = token_out_vec_15[4];
    assign dep_chan_vld_15_5 = out_chan_dep_vld_vec_15[5];
    assign dep_chan_data_15_5 = out_chan_dep_data_15;
    assign token_15_5 = token_out_vec_15[5];
    assign dep_chan_vld_15_12 = out_chan_dep_vld_vec_15[6];
    assign dep_chan_data_15_12 = out_chan_dep_data_15;
    assign token_15_12 = token_out_vec_15[6];
    assign dep_chan_vld_15_13 = out_chan_dep_vld_vec_15[7];
    assign dep_chan_data_15_13 = out_chan_dep_data_15;
    assign token_15_13 = token_out_vec_15[7];
    assign dep_chan_vld_15_14 = out_chan_dep_vld_vec_15[8];
    assign dep_chan_data_15_14 = out_chan_dep_data_15;
    assign token_15_14 = token_out_vec_15[8];
    assign dep_chan_vld_15_16 = out_chan_dep_vld_vec_15[9];
    assign dep_chan_data_15_16 = out_chan_dep_data_15;
    assign token_15_16 = token_out_vec_15[9];
    assign dep_chan_vld_15_17 = out_chan_dep_vld_vec_15[10];
    assign dep_chan_data_15_17 = out_chan_dep_data_15;
    assign token_15_17 = token_out_vec_15[10];

    // Process: multiply_1132_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 16, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_16 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_16),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_16),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_16),
        .token_in_vec(token_in_vec_16),
        .dl_detect_in(dl_detect_out),
        .origin(origin[16]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_16),
        .out_chan_dep_data(out_chan_dep_data_16),
        .token_out_vec(token_out_vec_16),
        .dl_detect_out(dl_in_vec[16]));

    assign proc_16_data_FIFO_blk[0] = 1'b0;
    assign proc_16_data_PIPO_blk[0] = 1'b0;
    assign proc_16_start_FIFO_blk[0] = 1'b0;
    assign proc_16_TLF_FIFO_blk[0] = 1'b0;
    assign proc_16_input_sync_blk[0] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_16_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_16[0] = dl_detect_out ? proc_dep_vld_vec_16_reg[0] : (proc_16_data_FIFO_blk[0] | proc_16_data_PIPO_blk[0] | proc_16_start_FIFO_blk[0] | proc_16_TLF_FIFO_blk[0] | proc_16_input_sync_blk[0] | proc_16_output_sync_blk[0]);
    assign proc_16_data_FIFO_blk[1] = 1'b0;
    assign proc_16_data_PIPO_blk[1] = 1'b0;
    assign proc_16_start_FIFO_blk[1] = 1'b0;
    assign proc_16_TLF_FIFO_blk[1] = 1'b0;
    assign proc_16_input_sync_blk[1] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_16_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_16[1] = dl_detect_out ? proc_dep_vld_vec_16_reg[1] : (proc_16_data_FIFO_blk[1] | proc_16_data_PIPO_blk[1] | proc_16_start_FIFO_blk[1] | proc_16_TLF_FIFO_blk[1] | proc_16_input_sync_blk[1] | proc_16_output_sync_blk[1]);
    assign proc_16_data_FIFO_blk[2] = 1'b0;
    assign proc_16_data_PIPO_blk[2] = 1'b0;
    assign proc_16_start_FIFO_blk[2] = 1'b0;
    assign proc_16_TLF_FIFO_blk[2] = 1'b0;
    assign proc_16_input_sync_blk[2] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_16_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_16[2] = dl_detect_out ? proc_dep_vld_vec_16_reg[2] : (proc_16_data_FIFO_blk[2] | proc_16_data_PIPO_blk[2] | proc_16_start_FIFO_blk[2] | proc_16_TLF_FIFO_blk[2] | proc_16_input_sync_blk[2] | proc_16_output_sync_blk[2]);
    assign proc_16_data_FIFO_blk[3] = 1'b0;
    assign proc_16_data_PIPO_blk[3] = 1'b0;
    assign proc_16_start_FIFO_blk[3] = 1'b0;
    assign proc_16_TLF_FIFO_blk[3] = 1'b0;
    assign proc_16_input_sync_blk[3] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_16_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_16[3] = dl_detect_out ? proc_dep_vld_vec_16_reg[3] : (proc_16_data_FIFO_blk[3] | proc_16_data_PIPO_blk[3] | proc_16_start_FIFO_blk[3] | proc_16_TLF_FIFO_blk[3] | proc_16_input_sync_blk[3] | proc_16_output_sync_blk[3]);
    assign proc_16_data_FIFO_blk[4] = 1'b0;
    assign proc_16_data_PIPO_blk[4] = 1'b0;
    assign proc_16_start_FIFO_blk[4] = 1'b0;
    assign proc_16_TLF_FIFO_blk[4] = 1'b0;
    assign proc_16_input_sync_blk[4] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_16_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_16[4] = dl_detect_out ? proc_dep_vld_vec_16_reg[4] : (proc_16_data_FIFO_blk[4] | proc_16_data_PIPO_blk[4] | proc_16_start_FIFO_blk[4] | proc_16_TLF_FIFO_blk[4] | proc_16_input_sync_blk[4] | proc_16_output_sync_blk[4]);
    assign proc_16_data_FIFO_blk[5] = 1'b0;
    assign proc_16_data_PIPO_blk[5] = 1'b0;
    assign proc_16_start_FIFO_blk[5] = 1'b0;
    assign proc_16_TLF_FIFO_blk[5] = 1'b0;
    assign proc_16_input_sync_blk[5] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_16_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_16[5] = dl_detect_out ? proc_dep_vld_vec_16_reg[5] : (proc_16_data_FIFO_blk[5] | proc_16_data_PIPO_blk[5] | proc_16_start_FIFO_blk[5] | proc_16_TLF_FIFO_blk[5] | proc_16_input_sync_blk[5] | proc_16_output_sync_blk[5]);
    assign proc_16_data_FIFO_blk[6] = 1'b0;
    assign proc_16_data_PIPO_blk[6] = 1'b0;
    assign proc_16_start_FIFO_blk[6] = 1'b0;
    assign proc_16_TLF_FIFO_blk[6] = 1'b0;
    assign proc_16_input_sync_blk[6] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_16_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_16[6] = dl_detect_out ? proc_dep_vld_vec_16_reg[6] : (proc_16_data_FIFO_blk[6] | proc_16_data_PIPO_blk[6] | proc_16_start_FIFO_blk[6] | proc_16_TLF_FIFO_blk[6] | proc_16_input_sync_blk[6] | proc_16_output_sync_blk[6]);
    assign proc_16_data_FIFO_blk[7] = 1'b0;
    assign proc_16_data_PIPO_blk[7] = 1'b0;
    assign proc_16_start_FIFO_blk[7] = 1'b0;
    assign proc_16_TLF_FIFO_blk[7] = 1'b0;
    assign proc_16_input_sync_blk[7] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_16_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_16[7] = dl_detect_out ? proc_dep_vld_vec_16_reg[7] : (proc_16_data_FIFO_blk[7] | proc_16_data_PIPO_blk[7] | proc_16_start_FIFO_blk[7] | proc_16_TLF_FIFO_blk[7] | proc_16_input_sync_blk[7] | proc_16_output_sync_blk[7]);
    assign proc_16_data_FIFO_blk[8] = 1'b0;
    assign proc_16_data_PIPO_blk[8] = 1'b0;
    assign proc_16_start_FIFO_blk[8] = 1'b0;
    assign proc_16_TLF_FIFO_blk[8] = 1'b0;
    assign proc_16_input_sync_blk[8] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_16_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_16[8] = dl_detect_out ? proc_dep_vld_vec_16_reg[8] : (proc_16_data_FIFO_blk[8] | proc_16_data_PIPO_blk[8] | proc_16_start_FIFO_blk[8] | proc_16_TLF_FIFO_blk[8] | proc_16_input_sync_blk[8] | proc_16_output_sync_blk[8]);
    assign proc_16_data_FIFO_blk[9] = 1'b0;
    assign proc_16_data_PIPO_blk[9] = 1'b0;
    assign proc_16_start_FIFO_blk[9] = 1'b0;
    assign proc_16_TLF_FIFO_blk[9] = 1'b0;
    assign proc_16_input_sync_blk[9] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_16_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_16[9] = dl_detect_out ? proc_dep_vld_vec_16_reg[9] : (proc_16_data_FIFO_blk[9] | proc_16_data_PIPO_blk[9] | proc_16_start_FIFO_blk[9] | proc_16_TLF_FIFO_blk[9] | proc_16_input_sync_blk[9] | proc_16_output_sync_blk[9]);
    assign proc_16_data_FIFO_blk[10] = 1'b0;
    assign proc_16_data_PIPO_blk[10] = 1'b0;
    assign proc_16_start_FIFO_blk[10] = 1'b0;
    assign proc_16_TLF_FIFO_blk[10] = 1'b0;
    assign proc_16_input_sync_blk[10] = 1'b0 | (ap_sync_multiply_1132_U0_ap_ready & multiply_1132_U0.ap_idle & ~ap_sync_multiply33_U0_ap_ready);
    assign proc_16_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_16[10] = dl_detect_out ? proc_dep_vld_vec_16_reg[10] : (proc_16_data_FIFO_blk[10] | proc_16_data_PIPO_blk[10] | proc_16_start_FIFO_blk[10] | proc_16_TLF_FIFO_blk[10] | proc_16_input_sync_blk[10] | proc_16_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_16_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_16_reg <= proc_dep_vld_vec_16;
        end
    end
    assign in_chan_dep_vld_vec_16[0] = dep_chan_vld_0_16;
    assign in_chan_dep_data_vec_16[23 : 0] = dep_chan_data_0_16;
    assign token_in_vec_16[0] = token_0_16;
    assign in_chan_dep_vld_vec_16[1] = dep_chan_vld_1_16;
    assign in_chan_dep_data_vec_16[47 : 24] = dep_chan_data_1_16;
    assign token_in_vec_16[1] = token_1_16;
    assign in_chan_dep_vld_vec_16[2] = dep_chan_vld_2_16;
    assign in_chan_dep_data_vec_16[71 : 48] = dep_chan_data_2_16;
    assign token_in_vec_16[2] = token_2_16;
    assign in_chan_dep_vld_vec_16[3] = dep_chan_vld_3_16;
    assign in_chan_dep_data_vec_16[95 : 72] = dep_chan_data_3_16;
    assign token_in_vec_16[3] = token_3_16;
    assign in_chan_dep_vld_vec_16[4] = dep_chan_vld_4_16;
    assign in_chan_dep_data_vec_16[119 : 96] = dep_chan_data_4_16;
    assign token_in_vec_16[4] = token_4_16;
    assign in_chan_dep_vld_vec_16[5] = dep_chan_vld_5_16;
    assign in_chan_dep_data_vec_16[143 : 120] = dep_chan_data_5_16;
    assign token_in_vec_16[5] = token_5_16;
    assign in_chan_dep_vld_vec_16[6] = dep_chan_vld_12_16;
    assign in_chan_dep_data_vec_16[167 : 144] = dep_chan_data_12_16;
    assign token_in_vec_16[6] = token_12_16;
    assign in_chan_dep_vld_vec_16[7] = dep_chan_vld_13_16;
    assign in_chan_dep_data_vec_16[191 : 168] = dep_chan_data_13_16;
    assign token_in_vec_16[7] = token_13_16;
    assign in_chan_dep_vld_vec_16[8] = dep_chan_vld_14_16;
    assign in_chan_dep_data_vec_16[215 : 192] = dep_chan_data_14_16;
    assign token_in_vec_16[8] = token_14_16;
    assign in_chan_dep_vld_vec_16[9] = dep_chan_vld_15_16;
    assign in_chan_dep_data_vec_16[239 : 216] = dep_chan_data_15_16;
    assign token_in_vec_16[9] = token_15_16;
    assign in_chan_dep_vld_vec_16[10] = dep_chan_vld_17_16;
    assign in_chan_dep_data_vec_16[263 : 240] = dep_chan_data_17_16;
    assign token_in_vec_16[10] = token_17_16;
    assign in_chan_dep_vld_vec_16[11] = dep_chan_vld_22_16;
    assign in_chan_dep_data_vec_16[287 : 264] = dep_chan_data_22_16;
    assign token_in_vec_16[11] = token_22_16;
    assign dep_chan_vld_16_0 = out_chan_dep_vld_vec_16[0];
    assign dep_chan_data_16_0 = out_chan_dep_data_16;
    assign token_16_0 = token_out_vec_16[0];
    assign dep_chan_vld_16_1 = out_chan_dep_vld_vec_16[1];
    assign dep_chan_data_16_1 = out_chan_dep_data_16;
    assign token_16_1 = token_out_vec_16[1];
    assign dep_chan_vld_16_2 = out_chan_dep_vld_vec_16[2];
    assign dep_chan_data_16_2 = out_chan_dep_data_16;
    assign token_16_2 = token_out_vec_16[2];
    assign dep_chan_vld_16_3 = out_chan_dep_vld_vec_16[3];
    assign dep_chan_data_16_3 = out_chan_dep_data_16;
    assign token_16_3 = token_out_vec_16[3];
    assign dep_chan_vld_16_4 = out_chan_dep_vld_vec_16[4];
    assign dep_chan_data_16_4 = out_chan_dep_data_16;
    assign token_16_4 = token_out_vec_16[4];
    assign dep_chan_vld_16_5 = out_chan_dep_vld_vec_16[5];
    assign dep_chan_data_16_5 = out_chan_dep_data_16;
    assign token_16_5 = token_out_vec_16[5];
    assign dep_chan_vld_16_12 = out_chan_dep_vld_vec_16[6];
    assign dep_chan_data_16_12 = out_chan_dep_data_16;
    assign token_16_12 = token_out_vec_16[6];
    assign dep_chan_vld_16_13 = out_chan_dep_vld_vec_16[7];
    assign dep_chan_data_16_13 = out_chan_dep_data_16;
    assign token_16_13 = token_out_vec_16[7];
    assign dep_chan_vld_16_14 = out_chan_dep_vld_vec_16[8];
    assign dep_chan_data_16_14 = out_chan_dep_data_16;
    assign token_16_14 = token_out_vec_16[8];
    assign dep_chan_vld_16_15 = out_chan_dep_vld_vec_16[9];
    assign dep_chan_data_16_15 = out_chan_dep_data_16;
    assign token_16_15 = token_out_vec_16[9];
    assign dep_chan_vld_16_17 = out_chan_dep_vld_vec_16[10];
    assign dep_chan_data_16_17 = out_chan_dep_data_16;
    assign token_16_17 = token_out_vec_16[10];

    // Process: multiply33_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 17, 12, 11) uz_VSD_6ph_asym_hls_deadlock_detect_unit_17 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_17),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_17),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_17),
        .token_in_vec(token_in_vec_17),
        .dl_detect_in(dl_detect_out),
        .origin(origin[17]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_17),
        .out_chan_dep_data(out_chan_dep_data_17),
        .token_out_vec(token_out_vec_17),
        .dl_detect_out(dl_in_vec[17]));

    assign proc_17_data_FIFO_blk[0] = 1'b0;
    assign proc_17_data_PIPO_blk[0] = 1'b0;
    assign proc_17_start_FIFO_blk[0] = 1'b0;
    assign proc_17_TLF_FIFO_blk[0] = 1'b0;
    assign proc_17_input_sync_blk[0] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_1_U0_ap_ready);
    assign proc_17_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_17[0] = dl_detect_out ? proc_dep_vld_vec_17_reg[0] : (proc_17_data_FIFO_blk[0] | proc_17_data_PIPO_blk[0] | proc_17_start_FIFO_blk[0] | proc_17_TLF_FIFO_blk[0] | proc_17_input_sync_blk[0] | proc_17_output_sync_blk[0]);
    assign proc_17_data_FIFO_blk[1] = 1'b0;
    assign proc_17_data_PIPO_blk[1] = 1'b0;
    assign proc_17_start_FIFO_blk[1] = 1'b0;
    assign proc_17_TLF_FIFO_blk[1] = 1'b0;
    assign proc_17_input_sync_blk[1] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_224_U0_ap_ready);
    assign proc_17_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_17[1] = dl_detect_out ? proc_dep_vld_vec_17_reg[1] : (proc_17_data_FIFO_blk[1] | proc_17_data_PIPO_blk[1] | proc_17_start_FIFO_blk[1] | proc_17_TLF_FIFO_blk[1] | proc_17_input_sync_blk[1] | proc_17_output_sync_blk[1]);
    assign proc_17_data_FIFO_blk[2] = 1'b0;
    assign proc_17_data_PIPO_blk[2] = 1'b0;
    assign proc_17_start_FIFO_blk[2] = 1'b0;
    assign proc_17_TLF_FIFO_blk[2] = 1'b0;
    assign proc_17_input_sync_blk[2] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_325_U0_ap_ready);
    assign proc_17_output_sync_blk[2] = 1'b0;
    assign proc_dep_vld_vec_17[2] = dl_detect_out ? proc_dep_vld_vec_17_reg[2] : (proc_17_data_FIFO_blk[2] | proc_17_data_PIPO_blk[2] | proc_17_start_FIFO_blk[2] | proc_17_TLF_FIFO_blk[2] | proc_17_input_sync_blk[2] | proc_17_output_sync_blk[2]);
    assign proc_17_data_FIFO_blk[3] = 1'b0;
    assign proc_17_data_PIPO_blk[3] = 1'b0;
    assign proc_17_start_FIFO_blk[3] = 1'b0;
    assign proc_17_TLF_FIFO_blk[3] = 1'b0;
    assign proc_17_input_sync_blk[3] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_426_U0_ap_ready);
    assign proc_17_output_sync_blk[3] = 1'b0;
    assign proc_dep_vld_vec_17[3] = dl_detect_out ? proc_dep_vld_vec_17_reg[3] : (proc_17_data_FIFO_blk[3] | proc_17_data_PIPO_blk[3] | proc_17_start_FIFO_blk[3] | proc_17_TLF_FIFO_blk[3] | proc_17_input_sync_blk[3] | proc_17_output_sync_blk[3]);
    assign proc_17_data_FIFO_blk[4] = 1'b0;
    assign proc_17_data_PIPO_blk[4] = 1'b0;
    assign proc_17_start_FIFO_blk[4] = 1'b0;
    assign proc_17_TLF_FIFO_blk[4] = 1'b0;
    assign proc_17_input_sync_blk[4] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_527_U0_ap_ready);
    assign proc_17_output_sync_blk[4] = 1'b0;
    assign proc_dep_vld_vec_17[4] = dl_detect_out ? proc_dep_vld_vec_17_reg[4] : (proc_17_data_FIFO_blk[4] | proc_17_data_PIPO_blk[4] | proc_17_start_FIFO_blk[4] | proc_17_TLF_FIFO_blk[4] | proc_17_input_sync_blk[4] | proc_17_output_sync_blk[4]);
    assign proc_17_data_FIFO_blk[5] = 1'b0;
    assign proc_17_data_PIPO_blk[5] = 1'b0;
    assign proc_17_start_FIFO_blk[5] = 1'b0;
    assign proc_17_TLF_FIFO_blk[5] = 1'b0;
    assign proc_17_input_sync_blk[5] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_628_U0_ap_ready);
    assign proc_17_output_sync_blk[5] = 1'b0;
    assign proc_dep_vld_vec_17[5] = dl_detect_out ? proc_dep_vld_vec_17_reg[5] : (proc_17_data_FIFO_blk[5] | proc_17_data_PIPO_blk[5] | proc_17_start_FIFO_blk[5] | proc_17_TLF_FIFO_blk[5] | proc_17_input_sync_blk[5] | proc_17_output_sync_blk[5]);
    assign proc_17_data_FIFO_blk[6] = 1'b0;
    assign proc_17_data_PIPO_blk[6] = 1'b0;
    assign proc_17_start_FIFO_blk[6] = 1'b0;
    assign proc_17_TLF_FIFO_blk[6] = 1'b0;
    assign proc_17_input_sync_blk[6] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_7_U0_ap_ready);
    assign proc_17_output_sync_blk[6] = 1'b0;
    assign proc_dep_vld_vec_17[6] = dl_detect_out ? proc_dep_vld_vec_17_reg[6] : (proc_17_data_FIFO_blk[6] | proc_17_data_PIPO_blk[6] | proc_17_start_FIFO_blk[6] | proc_17_TLF_FIFO_blk[6] | proc_17_input_sync_blk[6] | proc_17_output_sync_blk[6]);
    assign proc_17_data_FIFO_blk[7] = 1'b0;
    assign proc_17_data_PIPO_blk[7] = 1'b0;
    assign proc_17_start_FIFO_blk[7] = 1'b0;
    assign proc_17_TLF_FIFO_blk[7] = 1'b0;
    assign proc_17_input_sync_blk[7] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_829_U0_ap_ready);
    assign proc_17_output_sync_blk[7] = 1'b0;
    assign proc_dep_vld_vec_17[7] = dl_detect_out ? proc_dep_vld_vec_17_reg[7] : (proc_17_data_FIFO_blk[7] | proc_17_data_PIPO_blk[7] | proc_17_start_FIFO_blk[7] | proc_17_TLF_FIFO_blk[7] | proc_17_input_sync_blk[7] | proc_17_output_sync_blk[7]);
    assign proc_17_data_FIFO_blk[8] = 1'b0;
    assign proc_17_data_PIPO_blk[8] = 1'b0;
    assign proc_17_start_FIFO_blk[8] = 1'b0;
    assign proc_17_TLF_FIFO_blk[8] = 1'b0;
    assign proc_17_input_sync_blk[8] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_930_U0_ap_ready);
    assign proc_17_output_sync_blk[8] = 1'b0;
    assign proc_dep_vld_vec_17[8] = dl_detect_out ? proc_dep_vld_vec_17_reg[8] : (proc_17_data_FIFO_blk[8] | proc_17_data_PIPO_blk[8] | proc_17_start_FIFO_blk[8] | proc_17_TLF_FIFO_blk[8] | proc_17_input_sync_blk[8] | proc_17_output_sync_blk[8]);
    assign proc_17_data_FIFO_blk[9] = 1'b0;
    assign proc_17_data_PIPO_blk[9] = 1'b0;
    assign proc_17_start_FIFO_blk[9] = 1'b0;
    assign proc_17_TLF_FIFO_blk[9] = 1'b0;
    assign proc_17_input_sync_blk[9] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_1031_U0_ap_ready);
    assign proc_17_output_sync_blk[9] = 1'b0;
    assign proc_dep_vld_vec_17[9] = dl_detect_out ? proc_dep_vld_vec_17_reg[9] : (proc_17_data_FIFO_blk[9] | proc_17_data_PIPO_blk[9] | proc_17_start_FIFO_blk[9] | proc_17_TLF_FIFO_blk[9] | proc_17_input_sync_blk[9] | proc_17_output_sync_blk[9]);
    assign proc_17_data_FIFO_blk[10] = 1'b0;
    assign proc_17_data_PIPO_blk[10] = 1'b0;
    assign proc_17_start_FIFO_blk[10] = 1'b0;
    assign proc_17_TLF_FIFO_blk[10] = 1'b0;
    assign proc_17_input_sync_blk[10] = 1'b0 | (ap_sync_multiply33_U0_ap_ready & multiply33_U0.ap_idle & ~ap_sync_multiply_1132_U0_ap_ready);
    assign proc_17_output_sync_blk[10] = 1'b0;
    assign proc_dep_vld_vec_17[10] = dl_detect_out ? proc_dep_vld_vec_17_reg[10] : (proc_17_data_FIFO_blk[10] | proc_17_data_PIPO_blk[10] | proc_17_start_FIFO_blk[10] | proc_17_TLF_FIFO_blk[10] | proc_17_input_sync_blk[10] | proc_17_output_sync_blk[10]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_17_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_17_reg <= proc_dep_vld_vec_17;
        end
    end
    assign in_chan_dep_vld_vec_17[0] = dep_chan_vld_0_17;
    assign in_chan_dep_data_vec_17[23 : 0] = dep_chan_data_0_17;
    assign token_in_vec_17[0] = token_0_17;
    assign in_chan_dep_vld_vec_17[1] = dep_chan_vld_1_17;
    assign in_chan_dep_data_vec_17[47 : 24] = dep_chan_data_1_17;
    assign token_in_vec_17[1] = token_1_17;
    assign in_chan_dep_vld_vec_17[2] = dep_chan_vld_2_17;
    assign in_chan_dep_data_vec_17[71 : 48] = dep_chan_data_2_17;
    assign token_in_vec_17[2] = token_2_17;
    assign in_chan_dep_vld_vec_17[3] = dep_chan_vld_3_17;
    assign in_chan_dep_data_vec_17[95 : 72] = dep_chan_data_3_17;
    assign token_in_vec_17[3] = token_3_17;
    assign in_chan_dep_vld_vec_17[4] = dep_chan_vld_4_17;
    assign in_chan_dep_data_vec_17[119 : 96] = dep_chan_data_4_17;
    assign token_in_vec_17[4] = token_4_17;
    assign in_chan_dep_vld_vec_17[5] = dep_chan_vld_5_17;
    assign in_chan_dep_data_vec_17[143 : 120] = dep_chan_data_5_17;
    assign token_in_vec_17[5] = token_5_17;
    assign in_chan_dep_vld_vec_17[6] = dep_chan_vld_12_17;
    assign in_chan_dep_data_vec_17[167 : 144] = dep_chan_data_12_17;
    assign token_in_vec_17[6] = token_12_17;
    assign in_chan_dep_vld_vec_17[7] = dep_chan_vld_13_17;
    assign in_chan_dep_data_vec_17[191 : 168] = dep_chan_data_13_17;
    assign token_in_vec_17[7] = token_13_17;
    assign in_chan_dep_vld_vec_17[8] = dep_chan_vld_14_17;
    assign in_chan_dep_data_vec_17[215 : 192] = dep_chan_data_14_17;
    assign token_in_vec_17[8] = token_14_17;
    assign in_chan_dep_vld_vec_17[9] = dep_chan_vld_15_17;
    assign in_chan_dep_data_vec_17[239 : 216] = dep_chan_data_15_17;
    assign token_in_vec_17[9] = token_15_17;
    assign in_chan_dep_vld_vec_17[10] = dep_chan_vld_16_17;
    assign in_chan_dep_data_vec_17[263 : 240] = dep_chan_data_16_17;
    assign token_in_vec_17[10] = token_16_17;
    assign in_chan_dep_vld_vec_17[11] = dep_chan_vld_23_17;
    assign in_chan_dep_data_vec_17[287 : 264] = dep_chan_data_23_17;
    assign token_in_vec_17[11] = token_23_17;
    assign dep_chan_vld_17_0 = out_chan_dep_vld_vec_17[0];
    assign dep_chan_data_17_0 = out_chan_dep_data_17;
    assign token_17_0 = token_out_vec_17[0];
    assign dep_chan_vld_17_1 = out_chan_dep_vld_vec_17[1];
    assign dep_chan_data_17_1 = out_chan_dep_data_17;
    assign token_17_1 = token_out_vec_17[1];
    assign dep_chan_vld_17_2 = out_chan_dep_vld_vec_17[2];
    assign dep_chan_data_17_2 = out_chan_dep_data_17;
    assign token_17_2 = token_out_vec_17[2];
    assign dep_chan_vld_17_3 = out_chan_dep_vld_vec_17[3];
    assign dep_chan_data_17_3 = out_chan_dep_data_17;
    assign token_17_3 = token_out_vec_17[3];
    assign dep_chan_vld_17_4 = out_chan_dep_vld_vec_17[4];
    assign dep_chan_data_17_4 = out_chan_dep_data_17;
    assign token_17_4 = token_out_vec_17[4];
    assign dep_chan_vld_17_5 = out_chan_dep_vld_vec_17[5];
    assign dep_chan_data_17_5 = out_chan_dep_data_17;
    assign token_17_5 = token_out_vec_17[5];
    assign dep_chan_vld_17_12 = out_chan_dep_vld_vec_17[6];
    assign dep_chan_data_17_12 = out_chan_dep_data_17;
    assign token_17_12 = token_out_vec_17[6];
    assign dep_chan_vld_17_13 = out_chan_dep_vld_vec_17[7];
    assign dep_chan_data_17_13 = out_chan_dep_data_17;
    assign token_17_13 = token_out_vec_17[7];
    assign dep_chan_vld_17_14 = out_chan_dep_vld_vec_17[8];
    assign dep_chan_data_17_14 = out_chan_dep_data_17;
    assign token_17_14 = token_out_vec_17[8];
    assign dep_chan_vld_17_15 = out_chan_dep_vld_vec_17[9];
    assign dep_chan_data_17_15 = out_chan_dep_data_17;
    assign token_17_15 = token_out_vec_17[9];
    assign dep_chan_vld_17_16 = out_chan_dep_vld_vec_17[10];
    assign dep_chan_data_17_16 = out_chan_dep_data_17;
    assign token_17_16 = token_out_vec_17[10];

    // Process: Block_entry1434_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 18, 1, 1) uz_VSD_6ph_asym_hls_deadlock_detect_unit_18 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_18),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_18),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_18),
        .token_in_vec(token_in_vec_18),
        .dl_detect_in(dl_detect_out),
        .origin(origin[18]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_18),
        .out_chan_dep_data(out_chan_dep_data_18),
        .token_out_vec(token_out_vec_18),
        .dl_detect_out(dl_in_vec[18]));

    assign proc_18_data_FIFO_blk[0] = 1'b0;
    assign proc_18_data_PIPO_blk[0] = 1'b0;
    assign proc_18_start_FIFO_blk[0] = 1'b0;
    assign proc_18_TLF_FIFO_blk[0] = 1'b0 | (~products_0_1_U.if_empty_n & Block_entry1434_proc_U0.ap_idle & ~products_0_1_U.if_write);
    assign proc_18_input_sync_blk[0] = 1'b0;
    assign proc_18_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_18[0] = dl_detect_out ? proc_dep_vld_vec_18_reg[0] : (proc_18_data_FIFO_blk[0] | proc_18_data_PIPO_blk[0] | proc_18_start_FIFO_blk[0] | proc_18_TLF_FIFO_blk[0] | proc_18_input_sync_blk[0] | proc_18_output_sync_blk[0]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_18_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_18_reg <= proc_dep_vld_vec_18;
        end
    end
    assign in_chan_dep_vld_vec_18[0] = dep_chan_vld_19_18;
    assign in_chan_dep_data_vec_18[23 : 0] = dep_chan_data_19_18;
    assign token_in_vec_18[0] = token_19_18;
    assign dep_chan_vld_18_12 = out_chan_dep_vld_vec_18[0];
    assign dep_chan_data_18_12 = out_chan_dep_data_18;
    assign token_18_12 = token_out_vec_18[0];

    // Process: Block_entry1435_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 19, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_19 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_19),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_19),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_19),
        .token_in_vec(token_in_vec_19),
        .dl_detect_in(dl_detect_out),
        .origin(origin[19]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_19),
        .out_chan_dep_data(out_chan_dep_data_19),
        .token_out_vec(token_out_vec_19),
        .dl_detect_out(dl_in_vec[19]));

    assign proc_19_data_FIFO_blk[0] = 1'b0;
    assign proc_19_data_PIPO_blk[0] = 1'b0;
    assign proc_19_start_FIFO_blk[0] = 1'b0;
    assign proc_19_TLF_FIFO_blk[0] = 1'b0 | (~products_1_1_U.if_empty_n & Block_entry1435_proc_U0.ap_idle & ~products_1_1_U.if_write);
    assign proc_19_input_sync_blk[0] = 1'b0;
    assign proc_19_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_19[0] = dl_detect_out ? proc_dep_vld_vec_19_reg[0] : (proc_19_data_FIFO_blk[0] | proc_19_data_PIPO_blk[0] | proc_19_start_FIFO_blk[0] | proc_19_TLF_FIFO_blk[0] | proc_19_input_sync_blk[0] | proc_19_output_sync_blk[0]);
    assign proc_19_data_FIFO_blk[1] = 1'b0;
    assign proc_19_data_PIPO_blk[1] = 1'b0;
    assign proc_19_start_FIFO_blk[1] = 1'b0;
    assign proc_19_TLF_FIFO_blk[1] = 1'b0 | (~products_assign_1_load_loc_channel_U.if_empty_n & Block_entry1435_proc_U0.ap_idle & ~products_assign_1_load_loc_channel_U.if_write);
    assign proc_19_input_sync_blk[1] = 1'b0;
    assign proc_19_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_19[1] = dl_detect_out ? proc_dep_vld_vec_19_reg[1] : (proc_19_data_FIFO_blk[1] | proc_19_data_PIPO_blk[1] | proc_19_start_FIFO_blk[1] | proc_19_TLF_FIFO_blk[1] | proc_19_input_sync_blk[1] | proc_19_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_19_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_19_reg <= proc_dep_vld_vec_19;
        end
    end
    assign in_chan_dep_vld_vec_19[0] = dep_chan_vld_20_19;
    assign in_chan_dep_data_vec_19[23 : 0] = dep_chan_data_20_19;
    assign token_in_vec_19[0] = token_20_19;
    assign dep_chan_vld_19_13 = out_chan_dep_vld_vec_19[0];
    assign dep_chan_data_19_13 = out_chan_dep_data_19;
    assign token_19_13 = token_out_vec_19[0];
    assign dep_chan_vld_19_18 = out_chan_dep_vld_vec_19[1];
    assign dep_chan_data_19_18 = out_chan_dep_data_19;
    assign token_19_18 = token_out_vec_19[1];

    // Process: Block_entry1436_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 20, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_20 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_20),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_20),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_20),
        .token_in_vec(token_in_vec_20),
        .dl_detect_in(dl_detect_out),
        .origin(origin[20]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_20),
        .out_chan_dep_data(out_chan_dep_data_20),
        .token_out_vec(token_out_vec_20),
        .dl_detect_out(dl_in_vec[20]));

    assign proc_20_data_FIFO_blk[0] = 1'b0;
    assign proc_20_data_PIPO_blk[0] = 1'b0;
    assign proc_20_start_FIFO_blk[0] = 1'b0;
    assign proc_20_TLF_FIFO_blk[0] = 1'b0 | (~products_2_1_U.if_empty_n & Block_entry1436_proc_U0.ap_idle & ~products_2_1_U.if_write);
    assign proc_20_input_sync_blk[0] = 1'b0;
    assign proc_20_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_20[0] = dl_detect_out ? proc_dep_vld_vec_20_reg[0] : (proc_20_data_FIFO_blk[0] | proc_20_data_PIPO_blk[0] | proc_20_start_FIFO_blk[0] | proc_20_TLF_FIFO_blk[0] | proc_20_input_sync_blk[0] | proc_20_output_sync_blk[0]);
    assign proc_20_data_FIFO_blk[1] = 1'b0;
    assign proc_20_data_PIPO_blk[1] = 1'b0;
    assign proc_20_start_FIFO_blk[1] = 1'b0;
    assign proc_20_TLF_FIFO_blk[1] = 1'b0 | (~add_i1_loc_channel_U.if_empty_n & Block_entry1436_proc_U0.ap_idle & ~add_i1_loc_channel_U.if_write);
    assign proc_20_input_sync_blk[1] = 1'b0;
    assign proc_20_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_20[1] = dl_detect_out ? proc_dep_vld_vec_20_reg[1] : (proc_20_data_FIFO_blk[1] | proc_20_data_PIPO_blk[1] | proc_20_start_FIFO_blk[1] | proc_20_TLF_FIFO_blk[1] | proc_20_input_sync_blk[1] | proc_20_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_20_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_20_reg <= proc_dep_vld_vec_20;
        end
    end
    assign in_chan_dep_vld_vec_20[0] = dep_chan_vld_21_20;
    assign in_chan_dep_data_vec_20[23 : 0] = dep_chan_data_21_20;
    assign token_in_vec_20[0] = token_21_20;
    assign dep_chan_vld_20_14 = out_chan_dep_vld_vec_20[0];
    assign dep_chan_data_20_14 = out_chan_dep_data_20;
    assign token_20_14 = token_out_vec_20[0];
    assign dep_chan_vld_20_19 = out_chan_dep_vld_vec_20[1];
    assign dep_chan_data_20_19 = out_chan_dep_data_20;
    assign token_20_19 = token_out_vec_20[1];

    // Process: Block_entry1437_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 21, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_21 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_21),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_21),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_21),
        .token_in_vec(token_in_vec_21),
        .dl_detect_in(dl_detect_out),
        .origin(origin[21]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_21),
        .out_chan_dep_data(out_chan_dep_data_21),
        .token_out_vec(token_out_vec_21),
        .dl_detect_out(dl_in_vec[21]));

    assign proc_21_data_FIFO_blk[0] = 1'b0;
    assign proc_21_data_PIPO_blk[0] = 1'b0;
    assign proc_21_start_FIFO_blk[0] = 1'b0;
    assign proc_21_TLF_FIFO_blk[0] = 1'b0 | (~products_3_1_U.if_empty_n & Block_entry1437_proc_U0.ap_idle & ~products_3_1_U.if_write);
    assign proc_21_input_sync_blk[0] = 1'b0;
    assign proc_21_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_21[0] = dl_detect_out ? proc_dep_vld_vec_21_reg[0] : (proc_21_data_FIFO_blk[0] | proc_21_data_PIPO_blk[0] | proc_21_start_FIFO_blk[0] | proc_21_TLF_FIFO_blk[0] | proc_21_input_sync_blk[0] | proc_21_output_sync_blk[0]);
    assign proc_21_data_FIFO_blk[1] = 1'b0;
    assign proc_21_data_PIPO_blk[1] = 1'b0;
    assign proc_21_start_FIFO_blk[1] = 1'b0;
    assign proc_21_TLF_FIFO_blk[1] = 1'b0 | (~add3_i1_loc_channel_U.if_empty_n & Block_entry1437_proc_U0.ap_idle & ~add3_i1_loc_channel_U.if_write);
    assign proc_21_input_sync_blk[1] = 1'b0;
    assign proc_21_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_21[1] = dl_detect_out ? proc_dep_vld_vec_21_reg[1] : (proc_21_data_FIFO_blk[1] | proc_21_data_PIPO_blk[1] | proc_21_start_FIFO_blk[1] | proc_21_TLF_FIFO_blk[1] | proc_21_input_sync_blk[1] | proc_21_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_21_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_21_reg <= proc_dep_vld_vec_21;
        end
    end
    assign in_chan_dep_vld_vec_21[0] = dep_chan_vld_22_21;
    assign in_chan_dep_data_vec_21[23 : 0] = dep_chan_data_22_21;
    assign token_in_vec_21[0] = token_22_21;
    assign dep_chan_vld_21_15 = out_chan_dep_vld_vec_21[0];
    assign dep_chan_data_21_15 = out_chan_dep_data_21;
    assign token_21_15 = token_out_vec_21[0];
    assign dep_chan_vld_21_20 = out_chan_dep_vld_vec_21[1];
    assign dep_chan_data_21_20 = out_chan_dep_data_21;
    assign token_21_20 = token_out_vec_21[1];

    // Process: Block_entry1438_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 22, 1, 2) uz_VSD_6ph_asym_hls_deadlock_detect_unit_22 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_22),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_22),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_22),
        .token_in_vec(token_in_vec_22),
        .dl_detect_in(dl_detect_out),
        .origin(origin[22]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_22),
        .out_chan_dep_data(out_chan_dep_data_22),
        .token_out_vec(token_out_vec_22),
        .dl_detect_out(dl_in_vec[22]));

    assign proc_22_data_FIFO_blk[0] = 1'b0;
    assign proc_22_data_PIPO_blk[0] = 1'b0;
    assign proc_22_start_FIFO_blk[0] = 1'b0;
    assign proc_22_TLF_FIFO_blk[0] = 1'b0 | (~products_4_1_U.if_empty_n & Block_entry1438_proc_U0.ap_idle & ~products_4_1_U.if_write);
    assign proc_22_input_sync_blk[0] = 1'b0;
    assign proc_22_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_22[0] = dl_detect_out ? proc_dep_vld_vec_22_reg[0] : (proc_22_data_FIFO_blk[0] | proc_22_data_PIPO_blk[0] | proc_22_start_FIFO_blk[0] | proc_22_TLF_FIFO_blk[0] | proc_22_input_sync_blk[0] | proc_22_output_sync_blk[0]);
    assign proc_22_data_FIFO_blk[1] = 1'b0;
    assign proc_22_data_PIPO_blk[1] = 1'b0;
    assign proc_22_start_FIFO_blk[1] = 1'b0;
    assign proc_22_TLF_FIFO_blk[1] = 1'b0 | (~add5_i1_loc_channel_U.if_empty_n & Block_entry1438_proc_U0.ap_idle & ~add5_i1_loc_channel_U.if_write);
    assign proc_22_input_sync_blk[1] = 1'b0;
    assign proc_22_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_22[1] = dl_detect_out ? proc_dep_vld_vec_22_reg[1] : (proc_22_data_FIFO_blk[1] | proc_22_data_PIPO_blk[1] | proc_22_start_FIFO_blk[1] | proc_22_TLF_FIFO_blk[1] | proc_22_input_sync_blk[1] | proc_22_output_sync_blk[1]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_22_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_22_reg <= proc_dep_vld_vec_22;
        end
    end
    assign in_chan_dep_vld_vec_22[0] = dep_chan_vld_23_22;
    assign in_chan_dep_data_vec_22[23 : 0] = dep_chan_data_23_22;
    assign token_in_vec_22[0] = token_23_22;
    assign dep_chan_vld_22_16 = out_chan_dep_vld_vec_22[0];
    assign dep_chan_data_22_16 = out_chan_dep_data_22;
    assign token_22_16 = token_out_vec_22[0];
    assign dep_chan_vld_22_21 = out_chan_dep_vld_vec_22[1];
    assign dep_chan_data_22_21 = out_chan_dep_data_22;
    assign token_22_21 = token_out_vec_22[1];

    // Process: Block_entry1439_proc_U0
    uz_VSD_6ph_asym_hls_deadlock_detect_unit #(24, 23, 1, 3) uz_VSD_6ph_asym_hls_deadlock_detect_unit_23 (
        .reset(dl_reset),
        .clock(dl_clock),
        .proc_dep_vld_vec(proc_dep_vld_vec_23),
        .in_chan_dep_vld_vec(in_chan_dep_vld_vec_23),
        .in_chan_dep_data_vec(in_chan_dep_data_vec_23),
        .token_in_vec(token_in_vec_23),
        .dl_detect_in(dl_detect_out),
        .origin(origin[23]),
        .token_clear(token_clear),
        .out_chan_dep_vld_vec(out_chan_dep_vld_vec_23),
        .out_chan_dep_data(out_chan_dep_data_23),
        .token_out_vec(token_out_vec_23),
        .dl_detect_out(dl_in_vec[23]));

    assign proc_23_data_FIFO_blk[0] = 1'b0;
    assign proc_23_data_PIPO_blk[0] = 1'b0;
    assign proc_23_start_FIFO_blk[0] = 1'b0;
    assign proc_23_TLF_FIFO_blk[0] = 1'b0 | (~products_5_1_U.if_empty_n & Block_entry1439_proc_U0.ap_idle & ~products_5_1_U.if_write);
    assign proc_23_input_sync_blk[0] = 1'b0;
    assign proc_23_output_sync_blk[0] = 1'b0;
    assign proc_dep_vld_vec_23[0] = dl_detect_out ? proc_dep_vld_vec_23_reg[0] : (proc_23_data_FIFO_blk[0] | proc_23_data_PIPO_blk[0] | proc_23_start_FIFO_blk[0] | proc_23_TLF_FIFO_blk[0] | proc_23_input_sync_blk[0] | proc_23_output_sync_blk[0]);
    assign proc_23_data_FIFO_blk[1] = 1'b0;
    assign proc_23_data_PIPO_blk[1] = 1'b0;
    assign proc_23_start_FIFO_blk[1] = 1'b0;
    assign proc_23_TLF_FIFO_blk[1] = 1'b0 | (~add7_i1_loc_channel_U.if_empty_n & Block_entry1439_proc_U0.ap_idle & ~add7_i1_loc_channel_U.if_write);
    assign proc_23_input_sync_blk[1] = 1'b0;
    assign proc_23_output_sync_blk[1] = 1'b0;
    assign proc_dep_vld_vec_23[1] = dl_detect_out ? proc_dep_vld_vec_23_reg[1] : (proc_23_data_FIFO_blk[1] | proc_23_data_PIPO_blk[1] | proc_23_start_FIFO_blk[1] | proc_23_TLF_FIFO_blk[1] | proc_23_input_sync_blk[1] | proc_23_output_sync_blk[1]);
    assign proc_23_data_FIFO_blk[2] = 1'b0;
    assign proc_23_data_PIPO_blk[2] = 1'b0;
    assign proc_23_start_FIFO_blk[2] = 1'b0;
    assign proc_23_TLF_FIFO_blk[2] = 1'b0;
    assign proc_23_input_sync_blk[2] = 1'b0;
    assign proc_23_output_sync_blk[2] = 1'b0 | (ap_done_reg_11 & Block_entry1439_proc_U0.ap_done & ~Block_entry1426_proc_U0.ap_done);
    assign proc_dep_vld_vec_23[2] = dl_detect_out ? proc_dep_vld_vec_23_reg[2] : (proc_23_data_FIFO_blk[2] | proc_23_data_PIPO_blk[2] | proc_23_start_FIFO_blk[2] | proc_23_TLF_FIFO_blk[2] | proc_23_input_sync_blk[2] | proc_23_output_sync_blk[2]);
    always @ (negedge dl_reset or posedge dl_clock) begin
        if (~dl_reset) begin
            proc_dep_vld_vec_23_reg <= 'b0;
        end
        else begin
            proc_dep_vld_vec_23_reg <= proc_dep_vld_vec_23;
        end
    end
    assign in_chan_dep_vld_vec_23[0] = dep_chan_vld_11_23;
    assign in_chan_dep_data_vec_23[23 : 0] = dep_chan_data_11_23;
    assign token_in_vec_23[0] = token_11_23;
    assign dep_chan_vld_23_17 = out_chan_dep_vld_vec_23[0];
    assign dep_chan_data_23_17 = out_chan_dep_data_23;
    assign token_23_17 = token_out_vec_23[0];
    assign dep_chan_vld_23_22 = out_chan_dep_vld_vec_23[1];
    assign dep_chan_data_23_22 = out_chan_dep_data_23;
    assign token_23_22 = token_out_vec_23[1];
    assign dep_chan_vld_23_11 = out_chan_dep_vld_vec_23[2];
    assign dep_chan_data_23_11 = out_chan_dep_data_23;
    assign token_23_11 = token_out_vec_23[2];


`include "uz_VSD_6ph_asym_hls_deadlock_report_unit.vh"
