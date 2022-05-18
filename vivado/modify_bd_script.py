# This script opens the generated _zusys.tcl and modifies it for adapting the block diagram to
# different Trenz modules.
# 
# Author: Tomas P. Correa
# Date: check in git ;-)

# Board file path
board_files_path = "TE0808_9EG_1E/3.0/preset.xml"

# Open board preset.xml and get all the parameters that it sets, such that we can remove them from the block diagram tcl.
with open("board_files/" + board_files_path) as f_preset:
    preset = f_preset.read().split("\n")

preset_parameters = []
for line in preset:
    if "<user_parameter  name" in line:
        str = line.split("\"")
        preset_parameters.append(str[1]) 

# open generated board diagram tcl and replace what is necessary
ps_properties = False
with open("bd/_zusys.tcl",'r') as f_in:
    with open("bd/zusys.tcl",'w') as f_out:
        for line in f_in:
            if "set origin_dir ./project" in line:
                f_out.write("  set origin_dir .\n")
            elif "set str_bd_folder" in line:
                f_out.write("  set str_bd_folder [file normalize ${origin_dir}]/project\n")
            # if reached the inclusion of the ps, call the board preset before setting the properties one by one
            # Obs.: the properties present in the preset are moved from the list    
            elif "set zynq_ultra_ps_e_0" in line: 
                f_out.write(line)
                f_out.write("  apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset \"1\" }  [get_bd_cells zynq_ultra_ps_e_0]\n")
                ps_properties = True
            elif ps_properties:
                # check if at the end of set_property -dict and include the UART0 IO to MIO 18 and 19
                if "] $zynq_ultra_ps_e_0" in line: 
                    f_out.write("   CONFIG.PSU__UART0__PERIPHERAL__IO {MIO 18 .. 19} \\\n")
                    f_out.write(line)
                    ps_properties = False
                # if the parameter is present at the board preset, skip it 
                elif any(x in line for x in preset_parameters):
                    pass
                # otherwise include the parameter in the list
                else:
                    f_out.write(line)
                
            else:
                f_out.write(line)
