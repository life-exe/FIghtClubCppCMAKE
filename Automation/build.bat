@echo off

REM check if python is installed
python --version >nul 2>&1
if %errorlevel% NEQ 0 (
    echo "Python is not installed. Please install Python to continue."
    exit /b 1
)

REM check args
if "%~1"=="" (
    echo "Usage: build.bat clean|generate|build_debug|build_release|clang_format"
    exit /b 1
)

python Automation/automation.py %~1