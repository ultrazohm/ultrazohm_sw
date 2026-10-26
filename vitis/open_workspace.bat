@echo off
setlocal
rem Open Vitis for the existing workspace.
if not defined XSCT set "XSCT=xsct.bat"
call "%XSCT%" -nodisp "%~dp0..\tcl_scripts\vitis_headless.tcl" open %*
exit /b %ERRORLEVEL%
