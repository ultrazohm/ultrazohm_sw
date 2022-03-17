# To generate the project targeting a different TE0808 or TE0803 board,
# just modify the argv parameter with the proper board name (see Trenz csv files)
set argv [list --board_part trenz.biz:te0803_2eg_1e:part0:1.0]
set argc 2
source build.tcl