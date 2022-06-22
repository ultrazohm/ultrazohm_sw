# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__SIM_MATHHLS__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../foc/tb_foc.c ../../../../foc/uz_space_vector_limitation.c ../../../../foc/uz_signals.c ../../../../foc/uz_piController.c ../../../../foc/uz_linear_decoupling.c ../../../../foc/uz_Transformation.c ../../../../foc/uz_FOC.c

override TARGET := csim.exe

AUTOPILOT_ROOT := C:/Xilinx/Vitis/2020.1
AUTOPILOT_MACH := win64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
ifndef AP_GCC_PATH
  AP_GCC_PATH := C:/Xilinx/Vitis/2020.1/tps/win64/msys64/mingw64/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_ROOT}/tps/win64/msys64/mingw64/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_TOOL}/systemc/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -D__SIM_FPO__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E2__
IFLAG += -Wno-unknown-pragmas 
IFLAG += -g
IFLAG += -DNT
LFLAG += -Wl,--enable-auto-import 
DFLAG += -DAUTOCC
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += -Werror=return-type
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



AUTOCC := cmd //c apcc.bat  

$(ObjDir)/tb_foc.o: ../../../../foc/tb_foc.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/tb_foc.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD -Wno-unknown-pragmas -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/tb_foc.d

$(ObjDir)/uz_space_vector_limitation.o: ../../../../foc/uz_space_vector_limitation.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_space_vector_limitation.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_space_vector_limitation.d

$(ObjDir)/uz_signals.o: ../../../../foc/uz_signals.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_signals.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_signals.d

$(ObjDir)/uz_piController.o: ../../../../foc/uz_piController.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_piController.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_piController.d

$(ObjDir)/uz_linear_decoupling.o: ../../../../foc/uz_linear_decoupling.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_linear_decoupling.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_linear_decoupling.d

$(ObjDir)/uz_Transformation.o: ../../../../foc/uz_Transformation.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_Transformation.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_Transformation.d

$(ObjDir)/uz_FOC.o: ../../../../foc/uz_FOC.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../foc/uz_FOC.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/uz_FOC.d
