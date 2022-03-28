# This script opens the generated _build.tcl and modifies it for adapting the project generation to
# different Trenz modules.
# 
# Author: Tomas P. Correa
# Date: check in git ;-)

from os import getcwd


# Get script dir and repo dir
cwd = getcwd().replace("\\","/")
repo_dir = "/".join(cwd.split("/")[:-1])


# open generated board diagram tcl and replace what is necessary
skip_till_next_comment = False
with open("_build.tcl",'r') as f_in:
    with open("build.tcl",'w') as f_out:
        for line in f_in:
            # replace absolute paths with relative ones
            # Vivado sometimes may use upper or lower case for drive letter, so it got a bit more complicated 
            if cwd.lower() in line.lower():
                idx = line.lower().find(cwd.lower()) 
                line = line[:idx] + "${origin_dir}" + line[idx+len(cwd):]
            elif repo_dir.lower() in line.lower():
                idx = line.lower().find(repo_dir.lower())
                line = line[:idx] + "${origin_dir}/.." + line[idx+len(repo_dir):]

            # process the lines, adapting what is necessary
            # skips an entire region when skip_till_next_comment 
            if skip_till_next_comment:
                if "registered_with_manager" in line:
                    #f_out.write(line)
                    skip_till_next_comment = False
            # related to .bd file (that is not added, because we use the zusys.tcl instead)
            elif "Set 'sources_1' fileset file properties for local files" in line:
                f_out.write("# Set 'sources_1' fileset file properties for local files")
                skip_till_next_comment = True
            elif "zusys.bd" in line:
                pass
            # set default board variable

            # set default board variable
            elif "set origin_dir \".\"" in line:
                f_out.write(line + "\n")
                f_out.write("# Set default board part\n")
                f_out.write("set board_part \"trenz.biz:te0808_9eg_1e:part0:3.0\"\n")
            # change project dir to "/project" instead of "ultrazohm"
            elif "create_project" in line:
                f_out.write("create_project ${_xil_proj_name_} ./project -force\n\n")
                f_out.write("# set board_family variable, so the right constraints are loaded\n")
                f_out.write("if {[string first \"te0808\" $board_part] != -1} {\n")
                f_out.write("  set board_family \"te0808\"\n")
                f_out.write("} else {\n")
                f_out.write("  set board_family \"te0803\"\n")
                f_out.write("}\n")
            # replace board part with variable, so it can be passed as an argument to the script
            elif "\"board_part\"" in line:
                f_out.write("set_property -name \"board_part\" -value $board_part -objects $obj\n")
            # add board_part to arguments that can be passed to the script
            elif "switch -regexp -- $option {" in line:
                f_out.write(line)
                f_out.write("      \"--board_part\"   { incr i; set board_part [lindex $::argv $i] }\n")
            # I believe we don't really need to set this property manually
            elif "\"platform.board_id\"" in line:
                #f_out.write("set_property -name \"platform.board_id\" -value $board_id -objects $obj\n")
                pass
            # Replace the constraints folder with the board_family variable content
            elif "\"$origin_dir/constraints/" in line:
                line = line.replace("te0808","$board_family")
                line = line.replace("te0803","$board_family")
                f_out.write(line)
            # after this point, we don't need to add content, because vivado will auto-generate it anyway
            elif "# Create 'synth_1' run (if not found)" in line:
                f_out.write("# Check if block design already exists\n")
                f_out.write("set bd_path {./project/zusys/zusys.bd} \n")
                f_out.write("set bd_path_backup {./project/zusys/zusys_backup.bd} \n")
                f_out.write("set bd_exists [file isfile $bd_path] \n\n")
                
                f_out.write("# Create backup of existing block design file \n")
                f_out.write("if {$bd_exists == 1} { \n")
                f_out.write("  puts \"UZ: Block design file already exists at $bd_path \\r \" \n")
                f_out.write("  file rename -force $bd_path $bd_path_backup \n")
                f_out.write("  puts \"UZ: Created backup copy at $bd_path_backup \\r \" \n}\n\n"  )
                
                f_out.write("# Create block design\nsource $origin_dir/bd/zusys.tcl\nregenerate_bd_layout\n\n")

                f_out.write("# Warn user again at the end about backup block design  \n")
                f_out.write("if {$bd_exists == 1} { \n")                
                f_out.write("  puts \" \\n UZ: The current block design was overwritten, a temporary backup exists at $bd_path_backup \\n \" \n}\n\n"  )
                break
            else:
                f_out.write(line)
            
