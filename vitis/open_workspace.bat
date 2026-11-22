@echo off
setlocal
rem Open Vitis for the existing workspace.
call "%~dp0run_xsct_checked.bat" open %*
exit /b %ERRORLEVEL%
