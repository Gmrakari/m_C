@echo off
rem 获取当前脚本所在的目录
set "SCRIPT_PATH=%~f0"
set "SCRIPT_DIR=%~dp0"
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

set "BUILD_DIR=%SCRIPT_DIR%\build"
set "BIN_DIR=%SCRIPT_DIR%\bin"

rem 删除 build 目录
if exist "%BUILD_DIR%" (
    echo Deleting build directory...
    rd /s /q "%BUILD_DIR%"
    if %errorlevel% equ 0 (
        echo Build directory deleted successfully.
    ) else (
        echo Failed to delete build directory.
        exit /b 1
    )
) else (
    echo Build directory does not exist.
)

echo.

rem 删除 bin 目录
if exist "%BIN_DIR%" (
    echo Deleting bin directory...
    rd /s /q "%BIN_DIR%"
    if %errorlevel% equ 0 (
        echo Bin directory deleted successfully.
    ) else (
        echo Failed to delete bin directory.
        exit /b 1
    )
) else (
    echo Bin directory does not exist.
)