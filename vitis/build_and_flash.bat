@echo off
setlocal
rem Incrementally build, then program and run over JTAG.
rem Optional argument: Run_UltraZohm (the Tcl default).
if not defined XSCT set "XSCT=xsct.bat"
call "%XSCT%" -nodisp "%~dp0..\tcl_scripts\vitis_headless.tcl" flash %*
exit /b %ERRORLEVEL%
