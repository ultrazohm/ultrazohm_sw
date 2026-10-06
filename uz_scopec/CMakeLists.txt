cmake_minimum_required(VERSION 3.21)
project(uz_scopec LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(UZ_SCOPEC_BUILD_APP "Build the GUI application" ON)
option(UZ_SCOPEC_BUILD_TESTS "Build the unit tests" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

include(FetchContent)

# --- dependencies (all fetched at configure time, no system packages) --------

FetchContent_Declare(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(nlohmann_json)

if(UZ_SCOPEC_BUILD_APP)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE)

  # Docking branch release: dockspaces + multi-viewport (tear-off OS windows).
  FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b-docking
    GIT_SHALLOW TRUE)

  FetchContent_Declare(implot
    GIT_REPOSITORY https://github.com/epezent/implot.git
    GIT_TAG v0.17
    GIT_SHALLOW TRUE)

  FetchContent_MakeAvailable(glfw imgui implot)

  add_library(imgui_bundle STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${implot_SOURCE_DIR}/implot.cpp
    ${implot_SOURCE_DIR}/implot_items.cpp
    ${implot_SOURCE_DIR}/implot_demo.cpp)
  target_include_directories(imgui_bundle PUBLIC
    ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends ${implot_SOURCE_DIR})
  target_link_libraries(imgui_bundle PUBLIC glfw)
  find_package(OpenGL REQUIRED)
  target_link_libraries(imgui_bundle PUBLIC OpenGL::GL)
endif()

# --- core library (protocol/net/ring/trigger/logging, no GUI dependency) -----

add_library(uz_scopec_core STATIC
  src/core/protocol.cpp
  src/core/header_parser.cpp
  src/core/config.cpp
  src/core/ring.cpp
  src/core/acquisition.cpp
  src/core/slowdata.cpp
  src/core/netclient.cpp
  src/core/capture_log.cpp
  src/core/commands.cpp
  src/core/state.cpp
  src/core/state_commands.cpp)
target_include_directories(uz_scopec_core PUBLIC src)
target_link_libraries(uz_scopec_core PUBLIC nlohmann_json::nlohmann_json)
if(WIN32)
  target_link_libraries(uz_scopec_core PUBLIC ws2_32)
else()
  find_package(Threads REQUIRED)
  target_link_libraries(uz_scopec_core PUBLIC Threads::Threads)
endif()

# --- application -------------------------------------------------------------

if(UZ_SCOPEC_BUILD_APP)
  add_executable(uz_scopec
    src/app/main.cpp
    src/app/app.cpp
    src/app/panels/plot_windows.cpp
    src/app/panels/channels.cpp
    src/app/panels/control.cpp
    src/app/panels/trigger.cpp
    src/app/panels/slowdata_panel.cpp
    src/app/panels/logging_panel.cpp
    src/app/panels/diagnostics.cpp
    src/app/panels/console_panel.cpp
    src/app/panels/statusbar.cpp)
  target_link_libraries(uz_scopec PRIVATE uz_scopec_core imgui_bundle)
  if(WIN32)
    # GUI subsystem: no console window behind the scope (WinMain shim).
    set_target_properties(uz_scopec PROPERTIES WIN32_EXECUTABLE TRUE)
    target_sources(uz_scopec PRIVATE src/app/win32_main_shim.cpp)
  endif()
endif()

# --- tests -------------------------------------------------------------------

if(UZ_SCOPEC_BUILD_TESTS)
  FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(doctest)
  enable_testing()
  add_executable(uz_scopec_tests
    tests/test_main.cpp
    tests/test_protocol.cpp
    tests/test_header_parser.cpp
    tests/test_config.cpp
    tests/test_ring.cpp
    tests/test_lifecheck.cpp
    tests/test_acquisition.cpp
    tests/test_capture_log.cpp
    tests/test_commands.cpp)
  target_link_libraries(uz_scopec_tests PRIVATE uz_scopec_core doctest::doctest)
  # Tests parse the real javascope.h when the repo checkout is available.
  target_compile_definitions(uz_scopec_tests PRIVATE
    UZ_REPO_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/..")
  add_test(NAME uz_scopec_tests COMMAND uz_scopec_tests)
endif()
