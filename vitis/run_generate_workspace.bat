@echo off
:: Run vitis_generate_UltraZohm_workspace.tcl via XSCT
:: Adjust VITIS_VERSION and XILINX_ROOT if your installation differs

set VITIS_VERSION=2022.2
set XILINX_ROOT=C:\Xilinx
set XSCT=%XILINX_ROOT%\Vitis\%VITIS_VERSION%\bin\xsct.bat

if not exist "%XSCT%" (
    echo ERROR: xsct not found at %XSCT%
    echo Edit VITIS_VERSION or XILINX_ROOT at the top of this script.
    pause
    exit /b 1
)

set SCRIPT=%~dp0..\tcl_scripts\vitis_generate_UltraZohm_workspace.tcl
set WORKSPACE=%~dp0workspace

:: Guard: workspace must be empty or contain only create_Vitis_workspace_here.txt
set UNEXPECTED=
for /f "delims=" %%F in ('dir /b "%WORKSPACE%" 2^>nul') do (
    if /i not "%%F"=="create_Vitis_workspace_here.txt" set UNEXPECTED=%%F
)
if defined UNEXPECTED (
    echo ERROR: Workspace is not empty.
    echo        Found unexpected item: %UNEXPECTED%
    echo        Clear the workspace folder before running this script.
    pause
    exit /b 1
)

if not exist "%WORKSPACE%" mkdir "%WORKSPACE%"

echo.
echo ========================================
echo Starting XSCT to generate workspace...
echo Workspace: %WORKSPACE%
echo ========================================
pushd "%WORKSPACE%"
call "%XSCT%" -eval "setws {%WORKSPACE%}; source {%SCRIPT%}"
popd

if %ERRORLEVEL% neq 0 (
    echo.
    echo Script finished with errors (exit code %ERRORLEVEL%).
    pause
    exit /b 1
)

call "%~dp0open_workspace.bat"
