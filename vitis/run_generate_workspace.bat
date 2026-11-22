@echo off
setlocal
rem Create/build an empty workspace, then open Vitis.
call "%~dp0run_xsct_checked.bat" generate-open %*
exit /b %ERRORLEVEL%
