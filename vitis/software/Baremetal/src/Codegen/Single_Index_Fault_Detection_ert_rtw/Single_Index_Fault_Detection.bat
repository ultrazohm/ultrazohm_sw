
set MATLAB=C:\Program Files\MATLAB\R2021b

cd .

chcp 1252

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2021b\bin\win64\gmake"  -f Single_Index_Fault_Detection.mk all) else ("C:\PROGRA~1\MATLAB\R2021b\bin\win64\gmake"  -f Single_Index_Fault_Detection.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1