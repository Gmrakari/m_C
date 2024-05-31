#!/bin/bash

# 获取当前脚本的目录
SCRIPT_PATH=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

APP_NAME="app"

# 检测是否存在目录 build
BUILD_DIR="$SCRIPT_DIR/build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# 进入 build 目录
cd "$BUILD_DIR" || exit

# 使用 cmake 和 make 编译项目，并忽略输出
cmake .. >/dev/null 2>&1
make --silent || {
    echo "Build failed. Exiting."
    exit 1
}

echo ""

echo "Build succeeded."

OUTPUT_DIR="$SCRIPT_DIR/output"
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir "$OUTPUT_DIR"
fi

# 检查是否需要运行测试
if [ "$1" == "test" ]; then
    # 运行 ctest -V 进行测试
    ctest -V

    # 检查是否所有测试都通过
    if [ $? -eq 0 ]; then
        echo "All tests passed."
    else
        echo "Some tests failed. Check the output above for details."
        exit 1
    fi
fi

# 进入 ../bin/ 目录并执行 app
BIN_DIR="$SCRIPT_DIR/bin"
cd "$BIN_DIR" || exit
./${APP_NAME}
