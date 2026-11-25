@echo off
setlocal
rem Require a fresh action receipt even when XSCT exits zero.
if "%~1"=="" exit /b 1
if not defined XSCT set "XSCT=xsct.bat"
set "completion_dir=%TEMP%\uz-vitis-%RANDOM%-%RANDOM%"
rem Never reuse an existing directory or stale receipt.
if exist "%completion_dir%" exit /b 1
mkdir "%completion_dir%" || exit /b 1
set "UZ_VITIS_COMPLETION=%completion_dir%\completed"
call "%XSCT%" "%~dp0..\tcl_scripts\vitis_headless.tcl" %*
set "result=%ERRORLEVEL%"
if not "%result%"=="0" goto cleanup
set "completed="
if exist "%UZ_VITIS_COMPLETION%" set /p "completed=" < "%UZ_VITIS_COMPLETION%"
if "%completed%"=="%~1" goto cleanup
echo Vitis %~1 did not confirm completion; XSCT may have exited before running Tcl. >&2
set "result=1"
:cleanup
rmdir /s /q "%completion_dir%"
exit /b %result%
