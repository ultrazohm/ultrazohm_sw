@echo off
setlocal
:: Open the Vitis workspace
:: Adjust VITIS_VERSION and XILINX_ROOT if your installation differs

set "VITIS_VERSION=2022.2"
set "XILINX_ROOT=C:\Xilinx"
set "WORKSPACE=%~dp0workspace"
set "VITIS=%XILINX_ROOT%\Vitis\%VITIS_VERSION%\bin\vitis.bat"

if not exist "%VITIS%" (
    echo ERROR: Vitis not found at %VITIS%
    echo Edit VITIS_VERSION or XILINX_ROOT at the top of this script.
    if not defined UZ_WORKSPACE_LOG pause
    exit /b 1
)

if not exist "%WORKSPACE%" (
    echo ERROR: Workspace folder not found: %WORKSPACE%
    if not defined UZ_WORKSPACE_LOG pause
    exit /b 1
)

echo.
echo ========================================
echo Starting Vitis...
echo Workspace:
echo %WORKSPACE%
echo ========================================
pushd "%WORKSPACE%"
%ComSpec% /d /c call "%VITIS%" -workspace "%WORKSPACE%"
popd
echo.
echo You can close this terminal now.
if not defined UZ_WORKSPACE_LOG pause
exit /b 0
