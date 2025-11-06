@echo off
rem 获取当前脚本所在的目录
setlocal enabledelayedexpansion
set "SCRIPT_PATH=%~f0"
set "SCRIPT_DIR=%~dp0"
set "SCRIPT_DIR=!SCRIPT_DIR:~0,-1!"

set "APP_NAME=app"

rem 检测是否存在 build 目录，如果不存在则创建
set "BUILD_DIR=%SCRIPT_DIR%\build"
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

rem 进入 build 目录
cd /d "%BUILD_DIR%" || (
    echo "Failed to enter build directory. Exiting."
    exit /b 1
)

rem 使用 cmake 和 mingw32-make 编译项目（假设使用 MinGW）
cmake -G "MinGW Makefiles" .. >nul 2>&1
mingw32-make --silent -j10

echo.

rem 检查是否编译成功
if %errorlevel% equ 0 (
    rem 进入 ../bin/ 目录并执行 app
    set "BIN_DIR=!SCRIPT_DIR!\bin"
    echo "SCRIPT_DIR: !SCRIPT_DIR!"
    echo "BIN_DIR: !BIN_DIR!"
    cd /d "!BIN_DIR!" || (
        echo "Failed to enter bin directory. Exiting."
        exit /b 1
    )
    .\!APP_NAME!.exe
) else (
    echo "Build failed. Exiting."
    exit /b 1
)

endlocal