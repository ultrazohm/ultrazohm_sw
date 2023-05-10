# start the HLS Command Prompt Window
# cd into HLS project folder
# execute the following command

#for Vitis HLS > 2020.x
# vitis_hls -f PROJECT_NAME/SOLUTION_NAME/script.tcl
vitis_hls -f fcs_mpc/uz_9eg/script.tcl

#after script is finished you can open HLS in GUI mode and open the project folder 
#or use the following command to open the project 
#vitis_hls -p PROJECT_NAME
vitis_hls -p fcs_mpc

# see also for further references
http://venividiwiki.ee.virginia.edu/mediawiki/index.php/Exporting_your_HLS_project_as_a_TCL_file