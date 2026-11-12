@echo off
setlocal
rem Create/build an empty workspace, then open Vitis.
if not defined XSCT set "XSCT=xsct.bat"
call "%XSCT%" -nodisp "%~dp0..\tcl_scripts\vitis_headless.tcl" generate-open %*
exit /b %ERRORLEVEL%
