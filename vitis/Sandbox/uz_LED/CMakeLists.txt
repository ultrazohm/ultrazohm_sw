cmake_minimum_required(VERSION 3.0.0)
project(LED_testbench VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(../../export/Baremetal/uz/)

add_executable(LED_testbench uz_LED_testbench.c uz_LED.h uz_LED.c ../../export/Baremetal/uz/uz_HAL.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
