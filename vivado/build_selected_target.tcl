# To generate the project targeting a different TE0808 or TE0803 board,
# just modify the board_part variable with the proper board name (see Trenz csv files)

set board_part "trenz.biz:te0803_2eg_1e:part0:1.0"

set argv [list --board_part $board_part]
set argc 2

source build.tcl

puts "Adapt iobufds_inst contants."
if {[string first "te0803" $board_part] != -1} {
    # Inverted differential pairs: 10-11 and 12-13 (bits 5 and 6)
    set_property -dict [list CONFIG.CONST_VAL {0x60}] [get_bd_cells A1_inv_input]
    # Inverted differential pairs: 0-1, 2-3, 4-5 (bits 0, 1 and 2)
    set_property -dict [list CONFIG.CONST_VAL {0x07}] [get_bd_cells A2_inv_input]
    # Inverted differential pairs: 0-1, 4-5, 6-7 (bits 0, 2 and 3)
    set_property -dict [list CONFIG.CONST_VAL {0x0D}] [get_bd_cells A3_inv_input]
} else {
    # It is not necessary to invert the diff signals
    set_property -dict [list CONFIG.CONST_VAL {0x00}] [get_bd_cells A1_inv_input]
    set_property -dict [list CONFIG.CONST_VAL {0x00}] [get_bd_cells A2_inv_input]
    set_property -dict [list CONFIG.CONST_VAL {0x00}] [get_bd_cells A3_inv_input]    
}

puts "##### ATTENTION: the constraints files have to be overwritten manually!"

