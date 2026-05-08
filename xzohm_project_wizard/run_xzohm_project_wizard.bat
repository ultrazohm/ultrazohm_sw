@echo off
setlocal

cd /d "%~dp0"

where python >nul 2>nul
if errorlevel 1 (
    where py >nul 2>nul
    if errorlevel 1 (
        echo Python was not found in PATH and py.exe was not found.
        echo Please install Python or add it to PATH, then run this file again.
        pause
        exit /b 1
    )
    set "PYTHON_CMD=py -3"
) else (
    set "PYTHON_CMD=python"
)

%PYTHON_CMD% -c "import PyQt6" >nul 2>nul
if errorlevel 1 (
    echo PyQt6 is not installed for the selected Python environment.
    echo.
    echo Run this once from this folder:
    echo   %PYTHON_CMD% -m pip install -r requirements.txt
    echo.
    pause
    exit /b 1
)

%PYTHON_CMD% "%~dp0main.py"
if errorlevel 1 (
    echo.
    echo xZohm Project Wizard exited with an error.
    pause
    exit /b 1
)

endlocal
