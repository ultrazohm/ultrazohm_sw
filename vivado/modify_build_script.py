# This script opens the generated _build.tcl and modifies it for adapting the project generation to
# different Trenz modules.
# 
# Author: Tomas P. Correa
# Date: check in git ;-)

from os import getcwd


# Get script dir and repo dir
cwd = getcwd().replace("\\","/")
# Vivado uses lower case for drive letter
if cwd[0] != "/":
    cwd = cwd.replace(cwd[:2],cwd[:2].lower())
repo_dir = "/".join(cwd.split("/")[:-1])


# open generated board diagram tcl and replace what is necessary
skip_till_next_comment = False
with open("_build.tcl",'r') as f_in:
    with open("build.tcl",'w') as f_out:
        for line in f_in:
            # replace absolute paths with relative ones
            if cwd in line:
                line = line.replace(cwd,"${origin_dir}")
            if repo_dir in line:
                line = line.replace(repo_dir,"${origin_dir}/..")

            # process the lines, adapting what is necessary
            # skips an entire region when skip_till_next_comment 
            if skip_till_next_comment:
                if "# " in line:
                    f_out.write(line)
                    skip_till_next_comment = False
            # related to .bd file (that is not added, because we use the zusys.tcl instead)
            elif "Add local files from the original project (-no_copy_sources specified)" in line:
                skip_till_next_comment = True
            elif "Set 'sources_1' fileset file properties for local files" in line:
                skip_till_next_comment = True
            elif "zusys.bd" in line:
                pass
            # set default board variable
            elif "set origin_dir \".\"" in line:
                f_out.write(line + "\n")
                f_out.write("# Set default board part\n")
                f_out.write("set board_part \"trenz.biz:te0808_9eg_1e:part0:3.0\"\n")
            # change project dir to "/project" instead of "ultrazohm"
            elif "create_project" in line:
                f_out.write("create_project ${_xil_proj_name_} ./project\n\n")
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
            # after this point, we don't need to add content, because vivado will auto-generate it anyway
            elif "# Create 'synth_1' run (if not found)" in line:
                f_out.write("# Create block design\nsource $origin_dir/bd/zusys.tcl\nregenerate_bd_layout\n")
                break
            else:
                f_out.write(line)
            