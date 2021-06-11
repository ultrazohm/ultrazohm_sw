set base_address 80000000
set adc_cr 80000000
set adc_spi_cr 80000004
set adc_spi_cfgr 80000008
set adc_master_channel 8000000C
set adc_channel 80000010
set adc_master_finish 80000014
set adc_master_si_finish 80000018
set adc_master_busy 8000001C
set adc_conv_value 80000020

proc write_value {data address} {
    create_hw_axi_txn write_txn [get_hw_axis hw_axi_1] -type WRITE -data $data -address $address -force
    run_hw_axi [get_hw_axi_txns write_txn]
}

proc read_value {address} {
    create_hw_axi_txn read_txn [get_hw_axis hw_axi_1] -type READ -address $address -force
    run_hw_axi [get_hw_axi_txns read_txn]
}

proc set_conv {value masters channels} {
    global adc_conv_value
    global adc_master_channel
    global adc_channel
    global adc_cr
    write_value $value $adc_conv_value 
    write_value $masters $adc_master_channel
    write_value $channels $adc_channel
    write_value 00000018 $adc_cr
    read_value $adc_cr
}

proc set_offset {value masters channels} {
    global adc_conv_value
    global adc_master_channel
    global adc_channel
    global adc_cr
    write_value $value $adc_conv_value 
    write_value $masters $adc_master_channel
    write_value $channels $adc_channel
    write_value 00000008 $adc_cr
    read_value $adc_cr
}

reset_hw_axi [get_hw_axis hw_axi_1]

set_conv 00000002 00000001 000000FF
set_offset 0000000A 00000001 000000FF
#set_conv 00001111 00000001 000000F0

#write_value 00000008 $adc_spi_cfgr
#write_value 00000002 $adc_cr
#write_value 00000002 $adc_cr
#write_value 00000011 $adc_spi_cr
#write_value 00000004 $adc_cr