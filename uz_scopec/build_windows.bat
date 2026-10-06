@echo off
rem Build uz_scopec on Windows: app + tests, Release.
rem
rem Prerequisites (one-time):
rem   - Visual Studio 2022 with the "Desktop development with C++" workload
rem   - CMake 3.21+ (ships with Visual Studio, or https://cmake.org)
rem   - Git (FetchContent clones GLFW/ImGui/ImPlot at configure time)
rem
rem Run from a "x64 Native Tools Command Prompt for VS 2022" or any shell
rem where cmake.exe is on PATH.
setlocal
cd /d "%~dp0"

cmake -B build -S . -A x64 %*
if errorlevel 1 exit /b 1
cmake --build build --config Release --parallel
if errorlevel 1 exit /b 1
ctest --test-dir build -C Release --output-on-failure
if errorlevel 1 exit /b 1

echo.
echo Build OK: %~dp0build\Release\uz_scopec.exe
echo Run:      build\Release\uz_scopec.exe [--ip ^<addr^>] [--port ^<port^>] [--connect]
endlocal
