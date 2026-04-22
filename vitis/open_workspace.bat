@echo off
:: Open the Vitis workspace
:: Adjust VITIS_VERSION and XILINX_ROOT if your installation differs

set VITIS_VERSION=2022.2
set XILINX_ROOT=C:\Xilinx
set VITIS=%XILINX_ROOT%\Vitis\%VITIS_VERSION%\bin\vitis.bat

if not exist "%VITIS%" (
    echo ERROR: Vitis not found at %VITIS%
    echo Edit VITIS_VERSION or XILINX_ROOT at the top of this script.
    pause
    exit /b 1
)

set WORKSPACE=%~dp0workspace

echo Launching Vitis with workspace: %WORKSPACE%
call "%VITIS%" -workspace "%WORKSPACE%"
pause
