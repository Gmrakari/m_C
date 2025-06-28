#!/bin/bash

SCRIPT_PATH=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")
APP_NAME="app"

cmake_build() {
    BUILD_DIR="$SCRIPT_DIR/build"
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir "$BUILD_DIR"
    fi
    cd "$BUILD_DIR" || exit
    cmake -DCMAKE_BUILD_TYPE=Debug .. >/dev/null 2>&1
}

make_build() {
    make --silent -j10
    return $?
}

run_app() {
    cur_time=$(date +"%Y-%m-%d %H:%M:%S")
    echo "build app finish: $cur_time, use: $elapsed_time ms"
    BIN_DIR="$SCRIPT_DIR/bin"
    cd "$BIN_DIR" || exit
    ./${APP_NAME}
}

main() {
    start_time=$(date +%s%N)

    cmake_build

    make_build
    make_status=$?

    end_time=$(date +%s%N)
    elapsed_time=$(( ($end_time - $start_time) / 1000000 ))

    if [ $make_status -eq 0 ]; then
        run_app
    else
        echo "Build failed. Exiting."
        exit 1
    fi
}

main
