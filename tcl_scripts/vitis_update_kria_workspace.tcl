#Author: Seray Oezcan
#Date: 19/05/2023

# fix python error 
# https://support.xilinx.com/s/article/72570?language=en_US
catch {unset ::env(PYTHONPATH)}
catch {unset ::env(PYTHONHOME)}


cd [getws]/../../tcl_scripts/

puts "Vitis workspace modification for Kria Starter Kits"
exec python kria_modify_vitis_script.py
puts "Updated the workspace!"