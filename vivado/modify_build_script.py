# This script opens the generated _build.tcl and modifies it for adapting the project generation to
# different Trenz modules.
# 
# Author: Tomas P. Correa
# Date: check in git ;-)

from os import getcwd


# Get script dir and repo dir
# use low case for drive letter (this has to be improoved for linux machines)
cwd = getcwd().replace("\\","/")
cwd = cwd.replace(cwd[:2],cwd[:2].lower())
repo_dir = "/".join(cwd.split("/")[:-1])


skip_till_next_comment = False
# open generated board diagram tcl and replace what is necessary
with open("_build.tcl",'r') as f_in:
    with open("build.tcl",'w') as f_out:
        for line in f_in:
            # replace absolute paths with relative ones
            if cwd in line:
                line = line.replace(cwd,"${origin_dir}")
            if repo_dir in line:
                line = line.replace(repo_dir,"${origin_dir}/..")
            # process the lines, adapting what is necessary
            if skip_till_next_comment:
                if "# " in line:
                    f_out.write(line)
                    skip_till_next_comment = False
            elif "Add local files from the original project (-no_copy_sources specified)" in line:
                skip_till_next_comment = True
            elif "Set 'sources_1' fileset file properties for local files" in line:
                skip_till_next_comment = True
            elif "zusys.bd" in line:
                pass
            elif "create_project" in line:
                f_out.write("create_project ${_xil_proj_name_} ./project -part xczu9eg-ffvc900-1-e\n")
            elif "# Create 'synth_1' run (if not found)" in line:
                f_out.write("# Create block design\nsource $origin_dir/bd/zusys.tcl\nregenerate_bd_layout\n")
                break
            else:
                f_out.write(line)
            