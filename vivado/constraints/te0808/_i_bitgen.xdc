#
# Common bitgen related settings
#

set_property BITSTREAM.CONFIG.USR_ACCESS TIMESTAMP [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

#
# Set unused pin pull direction: PULLNONE, PULLUP, PULLDOWN
#

set_property BITSTREAM.CONFIG.UNUSEDPIN PULLNONE [current_design]

