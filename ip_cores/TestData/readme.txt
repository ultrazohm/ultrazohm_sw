# start the xilinx command prompt window
# cd into uz_sw/ip_cores/TestData HLS project folder
# execute the following command to create the project from the sources

vitis_hls -f "TestData_PL/solution1/script.tcl"

# after script is finished you can open HLS in GUI mode and open the project folder via GUI or by using the following command
 
vitis_hls -p TestData_PL


# for exporting IP to RTL correctly following patch has to be installed:
	https://support.xilinx.com/s/article/76960?language=en_US
# otherwise "ERROR: [IMPL 213-28] Failed to generate IP" may lead to failure of IP generation (make sure patch is installed!)


# please note: after generating & exporting the bitstream and regenerating the vitis workspace there might be following error
# 	" Failed to build the bsp sources for domain - FreeRTOS domain "
# 	" Failed to generate the platform "
# in this case  - open uz_sw/vitis/vivado_exported_xsa/zusys_wrapper.xsa with 7-Zip
		- navigate to drivers/test_data_signal_generation_v1_0/src
		- delete the Makefile
		- copy following file into this directory: ultrazohm_sw/ip_cores/TestData/Makefile 
		
# after c simulation, the results.dat file with the testbench results can be found under:
	C:\UltraZohm\ultrazohm_sw\ip_cores\TestData\TestData_PL\solution1\csim\build
	
