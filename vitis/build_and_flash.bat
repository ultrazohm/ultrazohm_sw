@echo off
setlocal
rem Incrementally build, then program and run over JTAG.
rem Optional argument: Run_UltraZohm (the Tcl default).
call "%~dp0run_xsct_checked.bat" flash %*
exit /b %ERRORLEVEL%
