################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../uz_FOC.cpp 

OBJS += \
./source/uz_FOC.o 

CPP_DEPS += \
./source/uz_FOC.d 


# Each subdirectory must supply rules for building sources it contributes
source/uz_FOC.o: C:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores/uz_FOC/uz_FOC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Xilinx/Vitis_HLS/2022.2/include/ap_sysc -IC:/Xilinx/Vitis_HLS/2022.2/win64/tools/systemc/include -IC:/Users/valen/Documents/repos/UZ/ultrazohm_sw/ip_cores/uz_xilinx_openhw_ipcores -IC:/Xilinx/Vitis_HLS/2022.2/include/etc -IC:/Xilinx/Vitis_HLS/2022.2/win64/tools/auto_cc/include -IC:/Xilinx/Vitis_HLS/2022.2/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


