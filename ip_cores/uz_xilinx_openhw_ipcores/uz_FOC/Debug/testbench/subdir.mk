################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../testbench.cpp 

OBJS += \
./testbench/testbench.o 

CPP_DEPS += \
./testbench/testbench.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/testbench.o: C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_FOC/testbench.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -IC:/Xilinx/Vitis_HLS/2022.2/include/ap_sysc -IC:/Xilinx/Vitis_HLS/2022.2/win64/tools/systemc/include -IC:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores -IC:/Xilinx/Vitis_HLS/2022.2/include/etc -IC:/Xilinx/Vitis_HLS/2022.2/win64/tools/auto_cc/include -IC:/Xilinx/Vitis_HLS/2022.2/include -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/testbench.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


