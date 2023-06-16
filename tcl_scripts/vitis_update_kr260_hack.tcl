#Author: Seray Oezcan
#Date: 19/05/2023

# fix python error 
# https://support.xilinx.com/s/article/72570?language=en_US
catch {unset ::env(PYTHONPATH)}
catch {unset ::env(PYTHONHOME)}


cd [getws]/../../tcl_scripts/

puts "Vitis Hack modification for Kria KR260 Robotics"
puts "*****After every change in the BSP settings, run the tcl again*****"
exec python kria_modify_kr260_hack.py
puts "Updated the workspace!"