@echo off
if defined UZ_WORKSPACE_LOG goto :run_generate_workspace
setlocal
set "UZ_WORKSPACE_LOG_DIR=%~dp0logs"
if not exist "%UZ_WORKSPACE_LOG_DIR%" mkdir "%UZ_WORKSPACE_LOG_DIR%"
set "UZ_LOG_STAMP=%DATE%_%TIME%"
set "UZ_LOG_STAMP=%UZ_LOG_STAMP: =0%"
set "UZ_LOG_STAMP=%UZ_LOG_STAMP::=-%"
set "UZ_LOG_STAMP=%UZ_LOG_STAMP:/=-%"
set "UZ_LOG_STAMP=%UZ_LOG_STAMP:.=-%"
set "UZ_LOG_STAMP=%UZ_LOG_STAMP:,=-%"
set "UZ_WORKSPACE_LOG=%UZ_WORKSPACE_LOG_DIR%\generate_workspace_%UZ_LOG_STAMP%.log"
echo Logging generate workspace output to:
echo %UZ_WORKSPACE_LOG%
echo.
echo Log file: %UZ_WORKSPACE_LOG% > "%UZ_WORKSPACE_LOG%"
echo Started: %DATE% %TIME% >> "%UZ_WORKSPACE_LOG%"
echo. >> "%UZ_WORKSPACE_LOG%"
powershell -NoProfile -ExecutionPolicy Bypass -Command "& { & $env:ComSpec /d /c 'call ""%~f0""' 2>&1 | Tee-Object -FilePath '%UZ_WORKSPACE_LOG%' -Append; if ($LASTEXITCODE) { exit $LASTEXITCODE } else { exit 0 } }"
if errorlevel 1 (
    set "UZ_LOG_EXIT=1"
) else (
    set "UZ_LOG_EXIT=0"
)
echo.
echo Finished with exit code %UZ_LOG_EXIT%.
echo Log file:
echo %UZ_WORKSPACE_LOG%
pause
exit /b %UZ_LOG_EXIT%

:run_generate_workspace
setlocal
:: Run vitis_generate_UltraZohm_workspace.tcl via XSCT
:: Adjust VITIS_VERSION and XILINX_ROOT if your installation differs

set "VITIS_VERSION=2022.2"
set "XILINX_ROOT=C:\Xilinx"
set "SCRIPT_DIR=%~dp0"
set "XSCT=%XILINX_ROOT%\Vitis\%VITIS_VERSION%\bin\xsct.bat"

if not exist "%XSCT%" (
    echo ERROR: xsct not found at %XSCT%
    echo Edit VITIS_VERSION or XILINX_ROOT at the top of this script.
    if not defined UZ_WORKSPACE_LOG pause
    exit /b 1
)

set "SCRIPT=%SCRIPT_DIR%..\tcl_scripts\vitis_generate_UltraZohm_workspace.tcl"
set "WORKSPACE=%SCRIPT_DIR%workspace"

:: Guard: workspace must be empty or contain only create_Vitis_workspace_here.txt
set "UNEXPECTED="
for /f "delims=" %%F in ('dir /b "%WORKSPACE%" 2^>nul') do (
    if /i not "%%F"=="create_Vitis_workspace_here.txt" set "UNEXPECTED=%%F"
)
if defined UNEXPECTED (
    echo ERROR: Workspace is not empty.
    echo        Found unexpected item: %UNEXPECTED%
    echo        Clear the workspace folder before running this script.
    if not defined UZ_WORKSPACE_LOG pause
    exit /b 1
)

if not exist "%WORKSPACE%" mkdir "%WORKSPACE%"

echo.
echo ========================================
echo Starting XSCT to generate workspace...
echo Workspace:
echo %WORKSPACE%
echo ========================================
pushd "%WORKSPACE%"
%ComSpec% /d /c call "%XSCT%" -eval "setws {%WORKSPACE%}; source {%SCRIPT%}"
popd

echo.
echo ========================================
echo Opening Vitis workspace...
echo Workspace:
echo %WORKSPACE%
echo ========================================
start "Open Vitis Workspace" /D "%SCRIPT_DIR%" "%ComSpec%" /k call "%SCRIPT_DIR%open_workspace.bat"
echo.
echo open_workspace.bat was started in a new command window.
echo.
echo You can close this terminal now.
if not defined UZ_WORKSPACE_LOG pause
endlocal
exit /b 0
