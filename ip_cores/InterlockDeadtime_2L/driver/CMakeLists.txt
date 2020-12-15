cmake_minimum_required(VERSION 3.0.0)
project(testproject VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(/home/ts/Dokumente/00_Master_Arbeit/1_Diss/ultrazohm_sw/vitis/workspace/UltraZohm/psu_cortexr5_0/Baremetal_domain/bsp/psu_cortexr5_0/include)

add_executable(main main.c 
InterlockDeadtime_hw.c 
InterlockDeadtime_hw.h 
InterlockDeadtime.c 
InterlockDeadtime.h
interlock_ip_addr.h
/home/ts/Dokumente/00_Master_Arbeit/1_Diss/ultrazohm_sw/vitis/workspace/UltraZohm/psu_cortexr5_0/Baremetal_domain/bsp/psu_cortexr5_0/libsrc/standalone_v7_2/src/common/xil_assert.c)



target_link_libraries(main m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
